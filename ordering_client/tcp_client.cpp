#include "tcp_client.h"
#include "order_menu.h"
#include <QDateTime>
#include <QTextBrowser>
#include <QLabel>
#include <QZXing>
#include <QPushButton>
#include <QFormLayout>
#include <QAbstractSocket>

TcpClient::TcpClient(QWidget *parent) :
    QWidget(parent)
{
    Tcp_Init();
}

void TcpClient::Tcp_Init() {
    // 获取菜单
    OrderMenu *orderMenu = (OrderMenu *)this->parent();
    tableWidget = orderMenu->getMenuTableWidget();

    this->_client = new QTcpSocket;	// 实例化对象

    // 创建加载显示
    _overlay = new QWidget(orderMenu);
    _reconnectTimer = new QTimer(this); // 重连定时器
    _loadingLabel = new QLabel("断线重连中...", _overlay);
    _loadingMovie = new QMovie(":/icons/loading.gif");

    _overlay->setStyleSheet("background-color: rgba(0, 0, 0, 50);");
    _overlay->setGeometry(orderMenu->rect());
    _overlay->hide();
    _reconnectTimer->setInterval(3000);
    _loadingLabel->setScaledContents(false);
    _loadingLabel->setGeometry(_overlay->rect());
    _loadingLabel->setAlignment(Qt::AlignCenter);
    _loadingLabel->setMovie(_loadingMovie);
    // _loadingLabel->hide(); // 默认隐藏

    // 连接失败开始重连
    connect(_reconnectTimer, &QTimer::timeout, this, [&]() {
        if(_client->state() != QTcpSocket::ConnectedState) {
            qDebug() << "Reconnection attempt...";
            _overlay->show();
            _loadingMovie->start();
            _client->connectToHost("192.168.63.26", 8888); // 连接
        }
    });

    // 判断连接服务器是否成功
    connect(this->_client, &QTcpSocket::connected, this, [&]() {
        qDebug() << "attempt success.";
        _reconnectTimer->stop();
        _loadingMovie->stop();
        _overlay->hide();
        connect(_client, &QTcpSocket::readyRead, this, &TcpClient::Analysis_Msg);
    });

    // 断开连接开始重连
    connect(this->_client, &QTcpSocket::disconnected, this, [&]() {
        _reconnectTimer->start();
    });
    _reconnectTimer->start();
}

/*
 * Analysis_Msg
 * ① 读取服务器发来的信息
 * ② 按照约定的规则读取包头,其中存放的是包长
 * ③ 根据包长读取相应的内容,根据消息类别交给不同的信息处理函数
 */
void TcpClient::Analysis_Msg() {
    do{
        // 包头:包长
        QByteArray msgLength = _client->read(MSG_LENGTH);
        QByteArray msg = _client->read(msgLength.toInt());

        // 包头:类别
        if(msg.startsWith(MSG_TYPE_ADD)) {
            qDebug() << "添加数据";
            if(!Analysis_Msg_To_Add(msg)) return;
        } else if(msg.startsWith(MSG_TYPE_DEL)) {
            qDebug() << "删除数据";
            if(!Analysis_Msg_To_Del(msg)) return;
        } else if(msg.startsWith(MSG_TYPE_RECEIPT)) {
            if(!Analysis_Msg_To_Receipt(msg)) return;
            qDebug() << "回执单";
        }
    }while(_client->bytesAvailable() !=0);
}

/*
 * Analysis_Msg_To_Add
 * ① 信息类型为<添加菜单行>时处理函数
 * ② 按照约定的规则解析包体并将其绘制到菜单控件
 * @msg Analysis_Msg传来的包体
 */
bool TcpClient::Analysis_Msg_To_Add(QByteArray &msg) {
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
    MenuData data;
    QDataStream in(&msg, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    in >> data; // 从流中读取数据到结构体
    // 数据有误
    if(data.img.isEmpty() || data.name.isEmpty()
        || data.kind.isEmpty() || data.price == 0) {
        return false;
    }
#if 0
    // 输出解包后的数据
    qDebug() << "Name:" << data.name;
    qDebug() << "Kind:" << data.kind;
    qDebug() << "Price:" << data.price;
    qDebug() << "Image path:" << data.img;
#endif

    int rowCount = this->tableWidget->rowCount();
    tableWidget->insertRow(rowCount); // 添加新行
    tableWidget->setItem(rowCount, 0, new QTableWidgetItem(data.img));
    tableWidget->setItem(rowCount, 1, new QTableWidgetItem(data.name));
    tableWidget->setItem(rowCount, 2, new QTableWidgetItem(data.kind));
    tableWidget->setItem(rowCount, 3, new QTableWidgetItem(QString::number(data.price)));
    // OrderMenu * orderMenu = (OrderMenu *)this->parent();
    // orderMenu->menuList.append(new MenuData(data));

    // 创建一个按钮在最后一列
    QSpinBox *spinBox = new QSpinBox();
    tableWidget->setCellWidget(rowCount, 4, spinBox);
    tableWidget->setColumnWidth(4, tableWidget->columnWidth(3) / 2);

    // 重绘第一列为图片
    ImageDelegate *imageDelegate = new ImageDelegate(tableWidget);
    tableWidget->setItemDelegateForColumn(0, imageDelegate);
    return true;
}

/*
 * Analysis_Msg_To_Del
 * ① 信息类型为<删除菜单行>时处理函数
 * ② 按照约定的规则解析包体并删除指定的一行菜单数据
 * @msg Analysis_Msg传来的包体
 */
bool TcpClient::Analysis_Msg_To_Del(QByteArray &msg) {
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
    MenuData data;
    QDataStream in(&msg, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    in >> data; // 从流中读取数据到结构体

#if 0
    // 输出解包后的数据
    qDebug() << "Name:" << data.name;
    qDebug() << "Kind:" << data.kind;
    qDebug() << "Price:" << data.price;
    qDebug() << "Image path:" << data.img;
#endif

    // 从表格的最后一行开始，向上遍历，避免删除行后索引变化影响后续遍历
    for (int row = tableWidget->rowCount() - 1; row >= 0; --row) {

        // 假设我们要匹配第一列的值
        QString cellValue1 = tableWidget->item(row, 0)->text();
        QString cellValue2 = tableWidget->item(row, 1)->text();

        // 如果找到匹配的行，删除该行
        if (cellValue1 == data.img || cellValue2 == data.name) {
            tableWidget->removeRow(row);
        }
    }
    return true;
}

/*
 * Analysis_Msg_To_Change
 * ① 信息类型为<修改菜单行>时处理函数
 * ② 按照约定的规则解析包体并修改一行菜单数据
 * ③ !此修改为删除一行再添加一行的伪修改!
 * @msg Analysis_Msg传来的包体
 */
bool TcpClient::Analysis_Msg_To_Change(QByteArray &msg) {
    // 暂存
    QByteArray msg_data = msg;

    Analysis_Msg_To_Del(msg); // 删除
    Analysis_Msg_To_Add(msg_data); // 添加

    return true;
}

/*
 * Analysis_Msg_To_Receipt
 * ① 信息类型为<订单回执>时处理函数
 * ② 按照约定的规则解析包体并将回执信息以二维码方式呈现
 * @msg Analysis_Msg传来的包体
 */
bool TcpClient::Analysis_Msg_To_Receipt(QByteArray &msg) {
    // 截取包体
    msg = msg.mid(msg.indexOf('@') + 1);
    QString message = msg;
    QStringList part = message.split('@');

    // 显示回执信息的载体控件
    QWidget *win = new QWidget;
    win->resize(QSize(800, 480));
    QFormLayout layout(win);

    // 绘制回执信息界面
    QString receipt = "订单回执:" + part.at(0) + "取餐号:" + part.at(1);
    QZXing encoder;
    QImage qrCodeImage = encoder.encodeData(receipt); // 指定二维码存放的信息
    QLabel *title = new QLabel("<h3>支付成功 扫描二维码获取回执信息</h3>", win);
    title->setStyleSheet("color: write;background-color: rgb(0, 170, 255);");
    QLabel *qrCodeLabel = new QLabel(win);
    QPushButton *closeBtn = new QPushButton("关闭", win);
    layout.addWidget(title);
    layout.addWidget(qrCodeLabel);
    layout.addWidget(closeBtn);
    qrCodeLabel->setPixmap(QPixmap::fromImage(qrCodeImage)); // 将生成的二维码放入label显示

    // 创建定时器计时关闭
    QTimer *timer = new QTimer(win);
    QLabel *timerLabel = new QLabel(win);
    layout.addWidget(timerLabel);
    timerLabel->setStyleSheet("font-size: 28px");
    timer->setInterval(1000);
    int *count = new int(120);
    connect(timer, &QTimer::timeout, win, [count, win, timerLabel]() {
        if((*count)-- == 0) {
            win->close();
            delete count;
        }
        else timerLabel->setText("界面将于" + QString::number(*count) + "s后关闭,请及时扫描获取回执");
    });
    timer->start();

    // 绑定关闭槽函数
    connect(closeBtn, &QPushButton::clicked, win, [count, timer, win]() {
        timer->stop();
        win->close();
        delete count;
    });

    OrderMenu *orderMenu = (OrderMenu *)this->parent();
    orderMenu->payResult(true);
    win->show();
    return true;
}

/*
 * send_order_slot
 * ① 根据时间戳拼接后3位随机数生成订单编号
 * ② 序列化订单编号和订单链表发送给服务器
 * ③ 发送结束标志并附带付款账号
 * ④ 重置选餐信息
 */
void TcpClient::send_order_slot(QString account) {
    OrderMenu *orderMenu = (OrderMenu *)this->parent();
    qDebug() << "提交订单";
    srand(time(NULL));
    unsigned long long id = QDateTime::currentMSecsSinceEpoch() * 1000 + rand() % 1000;
    qDebug() << id;
    for(auto it = orderMenu->orderList->begin();it != orderMenu->orderList->end();it++) {
        QByteArray message; // 存放序列化数据
        OrderData data; 	// 订单结构体
        data.id = QString::number(id);
        data.name = (*it).name;
        data.price = (*it).price;
        data.num = (*it).num;

        // 实例序列化对象
        QDataStream out(&message, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
        out << data;

        // 检查套接字
        if (_client == nullptr) {
            qDebug() << "发送失败";
            return;
        }

        // 发送数据
        if(Send_Message(message, MSG_TYPE_ORDER) == false) {
            return;
        }
    }

    // 结束标志@订单编号@付款账号
    QByteArray endMsg =  (QString::number(id) + "@" +
                         account).toUtf8();
    Send_Message(endMsg, MSG_TYPE_OVER);

    // 重置
    orderMenu->orderList->clear();
    QTableWidget * menuTab = orderMenu->getMenuTableWidget();
    int rowCout = menuTab->rowCount();
    for(int row = 0;row < rowCout;row++) {
        // 未购买不显示
        QSpinBox *spinBox = qobject_cast<QSpinBox *>(menuTab->cellWidget(row, 4));
        spinBox->setValue(0);
    }
}

/*
 * Send_Message
 * ① 计算序列化后的数据长度
 * ② 拼接数据长度和类型和数据并发送
 * @msg 序列化后的数据(要发送给服务器的数据)
 * @msgType 这份数据的类型
 */
bool TcpClient::Send_Message(QByteArray &msg, QString msgType) {
    // 包长
    QByteArray msgLength = QString::number(msg.size() +
                                           QString(msgType).size()).toUtf8().data();
    msgLength.resize(4);
    // 包头:包长类别@ 包体:数据
    QByteArray message = msgLength + msgType.toUtf8().data() + msg;

    // 发送消息
    if((_client == nullptr) || (_client->write(message) == -1)) {
        qDebug() << "发送失败";
        return false;
    }
    _client->flush();

    return true;
}















