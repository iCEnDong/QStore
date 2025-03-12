#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include "override_painter.h"
#include <QTableWidget>
#include <QSpinBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QMovie>

#define MSG_LENGTH 4 // 包头长度
#define MSG_TYPE_ADD 	"ADD@" // 消息类别,添加菜单行
#define MSG_TYPE_DEL 	"DEL@" // 删除菜单行
#define MSG_TYPE_RECEIPT"REC@" // 回执单
#define MSG_TYPE_ORDER  "ORD@" // 发送订单
#define MSG_TYPE_OVER 	"OVE@" // 发送完毕

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

class TcpClient : public QWidget
{
    Q_OBJECT
public:
    explicit TcpClient(QWidget *parent = nullptr);
    void Tcp_Init();
    bool Analysis_Msg_To_Add(QByteArray &msg);
    bool Analysis_Msg_To_Del(QByteArray &msg);
    bool Analysis_Msg_To_Change(QByteArray &msg);
    bool Analysis_Msg_To_Receipt(QByteArray &msg);
    bool Send_Message(QByteArray &msg, QString msgType);

public slots:
    void Analysis_Msg();
    void send_order_slot(QString account);

private:
    QTcpSocket * _client; // 套接字
    QTableWidget * tableWidget; // 菜单界面

    QWidget * _overlay;
    QTimer * _reconnectTimer;
    QLabel * _loadingLabel;
    QMovie * _loadingMovie;
};

#endif // TCP_CLIENT_H
