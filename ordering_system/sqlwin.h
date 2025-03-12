#ifndef SQLWIN_H
#define SQLWIN_H

#include "os_config.h"
#include "food_management.h"
#include "tcp_server.h"
#include "override_painter.h"
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QMenu>
#include <QAction>
#include <QSqlError>
#include <QVBoxLayout>
#include <QStandardItem>
#include <QRect>

#include <QTcpServer>
#include <QTcpSocket>

#define FOOD_TABLE_TAB_1 " 菜名 "
#define FOOD_TABLE_TAB_2 " 品类 "
#define FOOD_TABLE_TAB_3 " 价格 "
#define FOOD_TABLE_TAB_4 " 图片 "

#define ORDER_TABLE_TAB_1 " 订单编号 "
#define ORDER_TABLE_TAB_2 " 客户ID "
#define ORDER_TABLE_TAB_3 " 订单时间 "
#define ORDER_TABLE_TAB_4 " 付款账号 "

#define PAGE_TABLE_TAB_1 " item_id "
#define PAGE_TABLE_TAB_2 " 订单编号 "
#define PAGE_TABLE_TAB_3 " 菜名 "
#define PAGE_TABLE_TAB_4 " 单价 "
#define PAGE_TABLE_TAB_5 " 数量 "

QT_BEGIN_NAMESPACE
namespace Ui {
class SqlWin;
}
QT_END_NAMESPACE

class SqlWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit SqlWin(QWidget *parent = nullptr);
    ~SqlWin();
    void Sql_Init();
    void Sql_Init_Food();
    void Sql_Init_Order();
    void All_DiySignal_Connect();
    void Sql_ModelAndView_Update_Food();
    void Sql_ModelAndView_Update_Order();
    void swapRowsInDatabase(int row1, int row2);
    void Sql_Recv_Update_Order_Page( OrderData &data);
    void Sql_Recv_Update_Order_Tab(QString order_id, int custom_id, QString account);
    QTextBrowser * getTextBrowser();
    friend class FoodManagement;

signals:
    void update_Client_Sql_Signal(QString msgType, int rowCount = -1);

public slots:
    void sqlView_customContextMenuRequested_food(const QPoint &pos);
    void sql_dataChanged_slot(const QModelIndex &topLeft);
    void update_Client_Sql_Slot(QString msgType, int rowCount = -1);
    void order_clicked_show(const QModelIndex &index);

private slots:
    void on_pBtn_foodAdd_clicked();
    void on_pBtn_foodDel_clicked();
    void on_pBtn_foodUp_clicked();
    void on_pBtn_foodDown_clicked();
    void on_pBtn_foodSwap_clicked();
    void on_pBtn_tcpEnter_clicked();
    void on_pBtn_tcpOpen_clicked();
    void on_pBtn_orderBack_clicked();
    void on_pBtn_orderSwap_clicked();
    void on_pBtn_orderClear_clicked();
    void on_lineEdit_search_textChanged(const QString &arg1);
    void on_radioButton_account_toggled(bool checked);

private:
    Ui::SqlWin *ui;

    QSqlDatabase * sql_base;
    QSqlTableModel * sql_model_food;
    QTableView * sql_view_food;

    QSqlTableModel * sql_mode_order;
    QTableView * sql_view_order;
    QTextBrowser * textBrowser_order;

    TcpServer * _tcp_server;
};




#endif // SQLWIN_H
