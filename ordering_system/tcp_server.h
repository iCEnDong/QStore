#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QList>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTextBrowser>

#define MSG_LENGTH 		4
#define MSG_TYPE_ADD 	"ADD@" // 消息类别,添加菜单行
#define MSG_TYPE_DEL 	"DEL@" // 删除菜单行
#define MSG_TYPE_RECEIPT"REC@" // 回执单
#define MSG_TYPE_ORDER  "ORD@" // 接收订单
#define MSG_TYPE_OVER 	"OVE@" // 结束接收

#pragma pack(push, 1)
struct MenuData {
    QString name; 	// 菜名
    QString kind; 	// 品类
    float price; 	// 价格
    QString img; 	// 展示图

    // 重载操作符
    friend QDataStream &operator<<(QDataStream &out, const MenuData &data) {
        out << data.name << data.kind << data.price << data.img;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, MenuData &data) {
        in >> data.name >> data.kind >> data.price >> data.img;
        return in;
    }
};
struct OrderData {
    QString id; 	// 订单id
    QString name;	// 菜名
    float price; 	// 价格
    int num; 		// 数量

    // 重载操作符
    friend QDataStream &operator<<(QDataStream &out, const OrderData &data) {
        out << data.id << data.name << data.price << data.num;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, OrderData &data) {
        in >> data.id >> data.name >> data.price >> data.num;
        return in;
    }
};
#pragma pack(pop)

class TcpServer : public QWidget {
    Q_OBJECT
public:
    explicit TcpServer(QWidget *parent = nullptr);
    void Tcp_Server_Start(QString& port);
    bool isShutdown() {return shutdown;}
    void setShutdown();

signals:
public slots:
    void getClient_and_sendMenu();
    void Analysis_Msg();
    bool Analysis_Mag_To_Add(QByteArray &msg);
    bool Analysis_Mag_To_End(QByteArray &msg, int index);
    bool Send_Message(QTcpSocket *client, QByteArray &msg, QString msgType);
    void Board_Message(QByteArray &msg, QString msgType);
private:
    QTcpServer * _server;
    QList<QTcpSocket *> _clients;
    QTextBrowser * msgWin; // 服务器系统消息显示

    int receipt_id; // 回执
    bool shutdown; // 关机
};

#endif // TCP_SERVER_H
