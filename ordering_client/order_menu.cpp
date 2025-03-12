#include "order_menu.h"
#include "ui_ordermenu.h"
#include <QSpinBox>
#include <QCheckBox>

OrderMenu::OrderMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OrderMenu)
{
    ui->setupUi(this);

    Tcp_Init(); // tcp服务启动
    TableWidget_Init(); // 菜单初始化
    orderList = new QList<OrderData>; // 订单链表
    connect(this, SIGNAL(wait_for_payment_signal()), this, SLOT(wait_for_payment_slot()));
}

OrderMenu::~OrderMenu()
{
    delete ui;
}

// 初始化tcp,绑定提交订单槽函数
void OrderMenu::Tcp_Init() {
    tcpClient = new TcpClient(this);

    // 提交订单
    connect(this, SIGNAL(send_order_signal(QString)), tcpClient, SLOT(send_order_slot(QString)));
}

/*
 * TableWidget_Init
 * ① 绘制菜单界面,设置基本参数
 * ② 调用set_category_connect绑定类别复选框槽函数
 */
void OrderMenu::TableWidget_Init() {
    QStringList horHeaderLabes;
    horHeaderLabes << "展示图" << "菜名" << "品类" << "价格";
    ui->tableWidget->setHorizontalHeaderLabels(horHeaderLabes); // 表头
    ui->tableWidget->setColumnCount(5); // 4列
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(120); // 固定行高120
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自动调整
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); // 最后一列填满
    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents); // 无白边框
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); // 单行选择
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
    ui->tableWidget->setSortingEnabled(true); // 点击列头自动排序

    // 为所有复选框绑定槽函数
    set_category_connect();
}

/*
 * set_category_connect
 * ① 将所有类别复选框存入checkBoxs中
 * ② 为所有类别复选框绑定槽函数
 */
void OrderMenu::set_category_connect() {
    // 获取groupBox中的所有子控件(即所有的复选框)
    for(auto child : ui->groupBox->children()) {
        QCheckBox *checkBox = qobject_cast<QCheckBox *>(child);
        if(checkBox && checkBox != ui->checkBox_all) { // 是复选框且全选除外
            connect(checkBox, &QCheckBox::stateChanged,
                    this, &OrderMenu::filter_table_by_category);
            checkBoxs.append(checkBox);
        }
    }
    // 全选复选框绑定槽函数
    connect(ui->checkBox_all, &QCheckBox::clicked, this, [&]() {
        bool flag = false;
        if(ui->checkBox_all->isChecked()) {
            flag = true;
        }

        for(auto it = checkBoxs.begin();it != checkBoxs.end();it++) {
            (*it)->setChecked(flag);
        }
    });
}

/*
 * filter_table_by_category
 * ① 根据类别复选框来决定菜单显示内容
 * ② 响应购物车模式来决定菜单显示内容
 * ③ 根据复选框选择情况来更新全选复选框
 */
void OrderMenu::filter_table_by_category() {
    // 遍历所有行
    int rowCout = ui->tableWidget->rowCount();
    for(int row = 0;row < rowCout;row++) {
        // 获取第三列的值
        QString kind = ui->tableWidget->item(row, 2)->text();

        // 根据类别综合复选框来决定是否隐藏
        bool shouldHide = true; // 默认隐藏

        // 遍历所有复选框,如果是勾选状态则对比当前列的类型
        for(auto checkBox : checkBoxs) {
            if(checkBox->isChecked() && kind == checkBox->text()) {
                shouldHide = false; // 比对成功,显示
                break;
            }
        }

        // 购物车模式
        if(this->shoppingCar) {
            QSpinBox *spinBox = qobject_cast<QSpinBox *>(ui->tableWidget->cellWidget(row, 4));
            int value = spinBox->value();
            if(value == 0) { // 购买值为0,不予显示
                shouldHide = true;
            }
        }

        // 依据上述判断设置行的可见性
        ui->tableWidget->setRowHidden(row, shouldHide);
    }

    // 更新"全选"复选框状态
    for(auto it = checkBoxs.begin();it != checkBoxs.end();it++) {
        if(!(*it)->isChecked()) { // 如果有未勾选的项就退出
            ui->checkBox_all->setChecked(false);
            return;
        }
    }
    // 全选
    ui->checkBox_all->setChecked(true);
}

// 订单界面
void OrderMenu::on_pBtn_play_clicked()
{
    playUi = new PlayUi(this);
    playUi->show();
}

// 获取菜单控件
QTableWidget* OrderMenu::getMenuTableWidget() {
    return ui->tableWidget;
}

// 购物车/继续购物 切换
void OrderMenu::on_pBtn_shopping_clicked()
{
    shoppingCar = !shoppingCar;
    if(shoppingCar) {
        ui->pBtn_shopping->setText("继续购物");
    }else {
        ui->pBtn_shopping->setText("购物车");
    }
    this->filter_table_by_category();
}

// 扫码界面
void OrderMenu::wait_for_payment_slot() {
#if 0
    cameraWin = new V4L2Camera(this);
    cameraWin->show();
#else
    camera = new Camera(this);
    camera->show();
#endif
}

// 支付结果
void OrderMenu::payResult(bool result) {
    this->playUi->setPayResult(result);
}
