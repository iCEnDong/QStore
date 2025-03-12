#include "playui.h"
#include "ui_playui.h"
#include "order_menu.h"
#include <QSpinBox>
#include <QMessageBox>


PlayUi::PlayUi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlayUi)
{
    ui->setupUi(this);

    Play_Ui_Init();
}

PlayUi::~PlayUi()
{
    delete ui;
}

// 初始化订单界面
void PlayUi::Play_Ui_Init() {
    // 获取菜单控件
    OrderMenu *orderMenu = (OrderMenu *)this->parent();
    QTableWidget * menuTab = orderMenu->getMenuTableWidget();
    float total = 0; // 总价

    // 遍历所有行
    int rowCout = menuTab->rowCount();
    for(int row = 0;row < rowCout;row++) {
        // 未购买不显示
        QSpinBox *spinBox = qobject_cast<QSpinBox *>(menuTab->cellWidget(row, 4));
        int value = spinBox->value();
        if(value == 0) continue;

        // 获取: 菜名 单价 数量
        QString item1 = menuTab->item(row, 1)->text();
        QString item2 = menuTab->item(row, 3)->text();
        QString item3 = QString::number(value);

        // 以一定的格式显示
        ui->textBrowser->append("<h3>" + item1 + "</h3>");
        ui->textBrowser->append(item2 + "   \t" + "x" + item3);
        total += item2.toFloat() * item3.toInt();

        // 将订单存放到订单链表中
        OrderData data;
        data.name = item1;
        data.price = item2.toFloat();
        data.num = item3.toInt();
        orderMenu->orderList->append(data);
    }

    ui->label_money->setText(QString::number(total));
}

// 取消付款
void PlayUi::on_pBtn_cancle_clicked()
{
    this->close();
    delete this;
}

// 确定付款
void PlayUi::on_pBtn_play_clicked()
{
    OrderMenu *orderMenu = (OrderMenu *)this->parent();
    emit orderMenu->wait_for_payment_signal();
}

// 设置支付结果
void PlayUi::setPayResult(bool result) {
    if(result) {
        this->close();
        delete this;
    } else {
        QMessageBox::information(this, tr("支付结果"), tr("支付失败请重试"));
    }
}
