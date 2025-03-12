#include "tcp_server.h"
#include "sqlwin.h"
#include <QThread>
#include <QDateTime>

TcpServer::TcpServer(QWidget *parent) :
    QWidget(parent)
{
    SqlWin *sqlWin = (SqlWin *)this->parent();
    this->msgWin = sqlWin->getTextBrowser();
    this->receipt_id = 0;
    this->shutdown = true;
}

// 启动服务器
void TcpServer::Tcp_Server_Start(QString &port) {
    // 实例化对象
    this->_server = new QTcpServer();
    this->shutdown = true;

    // 保证设置了端口
    if(port.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请输入端口"));
        return;
    }

    // 绑定及监听
    if(this->_server->listen(QHostAddress::Any, port.toInt()) == true) {
        msgWin->append("<p style=\"background-color: #66bfbf;\">服务器开启\t"
                       + QDateTime::currentDateTime().toString(Qt::ISODate));
    }

    // 有客户端连接
    connect(_server, &QTcpServer::newConnection, this, &TcpServer::getClient_and_sendMenu);

    this->shutdown = false;
}

// 获取客户端套接字并发送菜单
void TcpServer::getClient_and_sendMenu() {
    QTcpSocket *client = this->_server->nextPendingConnection();
    if(!client) {
        qDebug() << "未能成功获取客户端连接";
    }
    _clients.append(client);

    qDebug() << "连接成功";

    // 设置信息接收
    connect(client, &QTcpSocket::readyRead, this, &TcpServer::Analysis_Msg);

    // 监听客户端断开连接
    connect(client, &QTcpSocket::disconnected, [this, client]() {
        qDebug() << "客户端断开连接";
        _clients.removeAll(client);
        client->deleteLater();
    });

    QSqlQuery query;
    if (!query.exec("SELECT * FROM food_table")) {
        qDebug() << "查询执行失败:" << query.lastError().text();
        return;
    }

    // 检查是否有数据
    if (!query.next()) {
        qDebug() << "没有符合条件的记录";
        return;
    }

    do {
        QByteArray message; // 存放序列化数据
        MenuData data; 		// 菜单结构体

        // 实例序列化对象
        QDataStream out(&message, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

        data.name 	= query.value(0).toString();   	// 第1列
        data.kind 	= query.value(1).toString();   	// 第2列
        data.price  = query.value(2).toFloat();    	// 第3列
        data.img 	= query.value(3).toString();  	// 第4列
        out << data; // 载入序列化

        // 检查客户端有效性并发送数据
        if (client == nullptr) {
            qDebug() << "客户端未初始化";
            return;
        }

        // 发送数据
        if(Send_Message(client, message, MSG_TYPE_ADD) == false) {
            return;
        }
    } while (query.next());  //  确保能至少执行一次
}

/*
 * Send_Message
 * ① 计算序列化后的数据的长度
 * ② 将数据长度和数据类型和数据进行拼接并发送
 * @client 要发送的客户端套接字
 * @msg 序列化后的数据
 * @msgType 此信息的类型
 */
bool TcpServer::Send_Message(QTcpSocket *client, QByteArray &msg, QString msgType) {
    // 包长
    QByteArray msgLength = QString::number(msg.size() +
                                           QString(msgType).size()).toUtf8().data();
    msgLength.resize(4);
    // 包头:包长类别@ 包体:数据
    QByteArray message = msgLength + msgType.toUtf8().data() + msg;

    // 发送消息
    if((client == nullptr) || (client->write(message) == -1)) {
        qDebug() << "发送失败";
        return false;
    }
    client->flush();

    return true;
}

// 群体发送发送(调用Send_Message)
void TcpServer::Board_Message(QByteArray &msg, QString msgType) {
    // 遍历客户端链表发送消息
    for(auto it = _clients.begin(); it != _clients.end(); it++) {
        if(*it == nullptr) {
            qDebug() << "客户端异常";
            continue;
        }

        Send_Message(*it, msg, msgType);
    }
}

/*
 * Analysis_Msg
 * ① 读取客户端发来的信息
 * ② 按照约定的规则读取包头,其中存放的是包长
 * ③ 根据包长读取相应的内容,根据消息类别交给不同的信息处理函数
 */
void TcpServer::Analysis_Msg() {
    // 锁定发送者
    QTcpSocket * target = (QTcpSocket *)sender();
    do{
        // 包头:包长
        QByteArray msgLength = target->read(MSG_LENGTH);
        QByteArray msg = target->read(msgLength.toInt());

        // 包头:类别
        if(msg.startsWith(MSG_TYPE_ORDER)) {
            qDebug() << "添加";
            if(!Analysis_Mag_To_Add(msg)) return;
        } else if(msg.startsWith(MSG_TYPE_OVER)) {
            qDebug() << "结束";
            if(!Analysis_Mag_To_End(msg, _clients.indexOf(target))) return;
        }

    }while(target->bytesAvailable() !=0);
}

/*
 * Analysis_Msg_To_Add
 * ① 信息类型为<添加订单详细信息>时处理函数
 * ② 按照约定的规则解析包体并将数据添加到数据库<OrderPage>
 * @msg Analysis_Msg传来的包体
 */
bool TcpServer::Analysis_Mag_To_Add(QByteArray &msg) {
    // 截取包体
    msg = msg.mid(msg.indexOf('@') + 1);

    // 检查接收到的数据
    if (msg.isEmpty()) {
    qDebug() << "接收到的消息为空！";
    return false;
    }

    // 输出接收到的数据长度
    qDebug() << "接收到的数据长度：" << msg.size();

    // 解包数据
    OrderData data;
    QDataStream in(&msg, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    in >> data; // 从流中读取数据到结构体

    // 数据有误
    if(data.name.isEmpty() || data.id.isEmpty()
        || data.price == 0 || data.num == 0) {
        qDebug() << "数据有误";
        return false;
    }

    // 更新模型和视图
    SqlWin *sqlWin = (SqlWin *)this->parent();
    sqlWin->Sql_Recv_Update_Order_Page(data);

    return true;
}

/*
 * Analysis_Msg_To_End
 * ① 信息类型为<订单信息结束>时处理函数
 * ② 按照约定的规则解析包体并将数据添加到数据库<OrderTable>
 * ③ 发送回执
 * @msg Analysis_Msg传来的包体
 * @index 要执行回执的客户在_clients中的索引
 */
bool TcpServer::Analysis_Mag_To_End(QByteArray &msg, int index) {
    // 截取包体
    msg = msg.mid(msg.indexOf('@') + 1);
    QString message = msg;
    QStringList part = message.split('@');

    SqlWin *sqlWin = (SqlWin *)this->parent();
    sqlWin->Sql_Recv_Update_Order_Tab(part.at(0), receipt_id, part.at(1));

    // 发送回执单(订单号@排队号)
    QByteArray receipt = QString(part.at(0) + "@" + QString::number(this->receipt_id++)).toUtf8();
    Send_Message(_clients.at(index), receipt, MSG_TYPE_RECEIPT);
    return true;
}

// 关机
void TcpServer::setShutdown() {
    this->shutdown = true;
    if(_server->isListening()) {
        _server->close();
        delete _server;
        qDebug() << "关闭服务器成功";
        msgWin->append("<p style=\"background-color: #f76b8a;\">服务器关闭\t"
                       + QDateTime::currentDateTime().toString(Qt::ISODate));
    }
}
