#ifndef ORDER_MENU_H
#define ORDER_MENU_H

#include "playui.h"
#include "tcp_client.h"
#include "v4l2_camera.h"
#include "camera.h"
#include <QMainWindow>
#include <QCheckBox>


QT_BEGIN_NAMESPACE
namespace Ui {
class OrderMenu;
}
QT_END_NAMESPACE

class OrderMenu : public QMainWindow
{
    Q_OBJECT

public:
    OrderMenu(QWidget *parent = nullptr);
    ~OrderMenu();
    void Tcp_Init();
    void TableWidget_Init();
    void set_category_connect();
    void filter_table_by_category();
    void payResult(bool result);

    QTableWidget * getMenuTableWidget();
    PlayUi * getPlayUi();
    QList<OrderData> *orderList;
    QList<MenuData *> menuList;

signals:
    void send_order_signal(QString account);
    void wait_for_payment_signal();
private slots:
    void wait_for_payment_slot();
    void on_pBtn_play_clicked();
    void on_pBtn_shopping_clicked();

private:
    Ui::OrderMenu *ui;

    TcpClient * tcpClient; // 套接字
    QList<QCheckBox *> checkBoxs; // 类别复选框
    PlayUi * playUi; // 支付界面
    // V4L2Camera * cameraWin;
    Camera * camera;

    bool shoppingCar = false; // 购物车模式
};


#endif // ORDER_MENU_H
