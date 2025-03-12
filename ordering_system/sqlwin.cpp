#include "sqlwin.h"
#include "ui_sqlwin.h"
#include <QTimer>
#include <QHeaderView>
#include <QFileDialog>

SqlWin::SqlWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SqlWin)
{
    ui->setupUi(this);
    Sql_Init();
    this->_tcp_server = new TcpServer(this);
    this->All_DiySignal_Connect();
    ui->tabWidget->setTabEnabled(0, false);
    ui->tabWidget->setTabEnabled(1, false);
}

SqlWin::~SqlWin()
{
    delete ui;
}

// 部分槽信号绑定(省的构造函数难看)
void SqlWin::All_DiySignal_Connect() {
    // 绑定菜单右键槽函数
    connect(sql_view_food, &QTableView::customContextMenuRequested, this,
            &SqlWin::sqlView_customContextMenuRequested_food);

    // 菜单修改数据同步给客户端
    connect(sql_model_food, &QSqlTableModel::dataChanged, this, &this->sql_dataChanged_slot);

    // 绑定订单右键槽函数

    // 同步数据给客户端
    connect(this, SIGNAL(update_Client_Sql_Signal(QString,int)),
            this, SLOT(update_Client_Sql_Slot(QString,int)));

}

QTextBrowser * SqlWin::getTextBrowser() {
    return ui->textBrowser_tcp;
}

// 创建/打开数据库,创建/读取表格,更新显示
void SqlWin::Sql_Init() {
    // 创建数据库对象,指定数据库驱动
    this->sql_base = new QSqlDatabase;
    *this->sql_base = QSqlDatabase::addDatabase("QSQLITE");

    // 设置数据库
    sql_base->setDatabaseName("./order.db");

    // 打开数据库
    if(!this->sql_base->open()) {
        qDebug() << "打开数据库失败" << sql_base->lastError();
    }

    Sql_Init_Food(); 	// 食品表格初始化
    Sql_Init_Order(); 	// 订单表格初始化
}

/*
 * Sql_Init_Food
 * ① 创建数据库表格<food_table>
 * ② 实例化数据模型和视图,并设置参数
 */
void SqlWin::Sql_Init_Food() {
    // 创建数据库表格
    QSqlQuery query; // 实例化一个数据库表格操作对象
    QString cmd; // 创建表格(表格存在就不做任何事)

    // 菜单
    cmd = QString("CREATE TABLE IF NOT EXISTS food_table ("
                FOOD_TABLE_TAB_1"TEXT,"
                FOOD_TABLE_TAB_2"TEXT,"
                FOOD_TABLE_TAB_3"REAL,"
                FOOD_TABLE_TAB_4"TEXT"
                ")");
    query.exec(cmd);

#if OS_SQLDATADIS
    if(query.exec("SELECT * FROM food_table")) {
        while(query.next()) {
            qDebug() << query.value(0).toString()
                     << query.value(1).toString()
                     << query.value(2).toFloat()
                     << query.value(3).toString();
        }
    }
#endif

    // 实例化一个数据视图中的数据模型
    this->sql_model_food = new QSqlTableModel;
    sql_model_food->setTable("food_table"); // 设置被用来填充模型的数据
    sql_model_food->setEditStrategy(QSqlTableModel::OnFieldChange); // 设置更新方式(文件更改就更新)
    sql_model_food->select();

    // 实例化一个数据库数据模型视图对象
    this->sql_view_food = new QTableView;
    sql_view_food->verticalHeader()->setDefaultSectionSize(120); // 固定行高120
    sql_view_food->setModel(this->sql_model_food); // 对接数据模型
    sql_view_food->setSelectionBehavior(QAbstractItemView::SelectRows); // 设置选择整行
    sql_view_food->setSelectionMode(QAbstractItemView::SingleSelection); // 单选模式
    sql_view_food->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自动调整列宽
    sql_view_food->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sql_view_food->horizontalHeader()->setStretchLastSection(true); // 最后一列填满
    sql_view_food->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents); // 无空白边框
    ui->vBoxLayout_food->addWidget(sql_view_food); // 将视图添加到布局
    sql_view_food->setContextMenuPolicy(Qt::CustomContextMenu); // 右键菜单

    Sql_ModelAndView_Update_Food();
}

/*
 * Sql_Init_Order
 * ① 创建数据库表格<OrderTable> <OrderPage>
 * ② 实例化数据模型和视图,并设置参数
 * ③ 绑定槽函数order_clicked_show
 */
void SqlWin::Sql_Init_Order() {
    // 创建数据库表格
    QSqlQuery query; // 实例化一个数据库表格操作对象
    QString cmd; // 创建表格(表格存在就不做任何事)

    // query.exec("DROP TABLE OrderTable");
    // query.exec("DROP TABLE OrderPage");
    // ---订单表
    cmd = QString("CREATE TABLE IF NOT EXISTS OrderTable ("
                ORDER_TABLE_TAB_1"TEXT,"
                ORDER_TABLE_TAB_2"INTEGER,"
                ORDER_TABLE_TAB_3"TEXT,"
                ORDER_TABLE_TAB_4"TEXT"
                ")");
    query.exec(cmd);

    // ---订单详表
    cmd = QString("CREATE TABLE IF NOT EXISTS OrderPage ("
                PAGE_TABLE_TAB_1"INTEGER PRIMARY KEY AUTOINCREMENT,"
                PAGE_TABLE_TAB_2"TEXT,"
                PAGE_TABLE_TAB_3"TEXT,"
                PAGE_TABLE_TAB_4"REAL,"
                PAGE_TABLE_TAB_5"INTEGER"
                ")");
    query.exec(cmd);

    // 实例化模型
    this->sql_mode_order = new QSqlTableModel;
    sql_mode_order->setTable("OrderTable"); // 设置数据表源
    sql_mode_order->setEditStrategy(QSqlTableModel::OnManualSubmit);
    sql_mode_order->select(); // 加载数据

    this->sql_view_order = new QTableView;
    sql_view_order->setModel(sql_mode_order); // 绑定模型
    sql_view_order->setSelectionBehavior(QAbstractItemView::SelectRows); // 选择整行
    sql_view_order->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自动调整列宽
    sql_view_order->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sql_view_order->horizontalHeader()->setStretchLastSection(true); // 最后一列填满
    sql_view_order->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents); // 无空白边框
    sql_view_order->setColumnHidden(3, true); // 隐藏付款账号

    this->textBrowser_order = new QTextBrowser;
    ui->stackedWidget->addWidget(sql_view_order);
    ui->stackedWidget->addWidget(textBrowser_order);
    ui->stackedWidget->setCurrentWidget(sql_view_order);
    ui->pBtn_orderBack->setHidden(true);
    ui->pBtn_orderBack->setEnabled(false);

    connect(sql_view_order, &QTableView::clicked, this, SqlWin::order_clicked_show);
    Sql_ModelAndView_Update_Order();
}

/*
 * order_clicked_show
 * 根据点击的订单索引显示对应的订单详情
 * @index 订单表格的索引
 */
void SqlWin::order_clicked_show(const QModelIndex &index) {
    // 更新下先
    Sql_ModelAndView_Update_Order(); 	// 更新订单
    this->textBrowser_order->clear(); 	// 清空

    // 订单id
    QString orderId = sql_mode_order->data(sql_mode_order->index(index.row(), 0)).toString();

    // 查询订单的详细
    QSqlQuery query;
    QString cmd;
    cmd = QString("SELECT * FROM OrderPage WHERE"
                PAGE_TABLE_TAB_2
                "= :id");
    query.prepare(cmd);
    query.bindValue(":id", orderId);
    query.exec();

    while(query.next()) {
        QString dishName = query.value(2).toString();
        float price = query.value(3).toFloat();
        QString num = query.value(4).toString();

        this->textBrowser_order->append("<h3>" + dishName + "</h3>");
        this->textBrowser_order->append(QString::number(price) + "	\t" + "x" + num);
    }
    ui->stackedWidget->setCurrentWidget(textBrowser_order);
    ui->pBtn_orderBack->setHidden(false);
    ui->pBtn_orderBack->setEnabled(true);
}

/*
 * Sql_ModelAndView_Update_Food
 * ① 更新<food_table>的模型和视图
 * ② 在视图的第四列显示图片
 */
void SqlWin::Sql_ModelAndView_Update_Food() {
    this->sql_model_food->select();
    this->sql_view_food->update();

    // 设置图片列的委托（假设图片路径在第 4 列）
    ImageDelegate *imageDelegate = new ImageDelegate(this->sql_view_food);
    sql_view_food->setItemDelegateForColumn(3, imageDelegate); // 第 4 列为图片路径
}

// 更新订单的模型和视图
void SqlWin::Sql_ModelAndView_Update_Order() {
    this->sql_mode_order->select();
    this->sql_view_order->update();
}

/*
 * sqlView_customContextMenuRequested_food
 * ① 槽函数,当右键<food_table>视图时弹出上下文菜单
 * ② 为上下文菜单添加选项并绑定相应的槽函数
 * @pos 鼠标位置坐标
 */
void SqlWin::sqlView_customContextMenuRequested_food(const QPoint &pos)
{
    // 创建右键菜单
    QMenu contextMenu(this);

    // 添加上移选项,并绑定槽函数
    QAction *moveUpAction = contextMenu.addAction("上移一行");
    connect(moveUpAction, &QAction::triggered, this, &SqlWin::on_pBtn_foodUp_clicked);

    // 添加上移选项,并绑定槽函数
    QAction *swapAction = contextMenu.addAction("交换一行");
    connect(swapAction, &QAction::triggered, this, &SqlWin::on_pBtn_foodSwap_clicked);

    // 添加下移选项,并绑定槽函数
    QAction *moveDownAction = contextMenu.addAction("下移一行");
    connect(moveDownAction, &QAction::triggered, this, &SqlWin::on_pBtn_foodDown_clicked);

    // 添加添加选项,并绑定槽函数
    QAction *addAction = contextMenu.addAction("添加行");
    connect(addAction, &QAction::triggered, this, &SqlWin::on_pBtn_foodAdd_clicked);

    // 添加删除选项,并绑定槽函数
    QAction *deleteAction = contextMenu.addAction("删除选中行");
    connect(deleteAction, &QAction::triggered, this, &SqlWin::on_pBtn_foodDel_clicked);

    // 弹出菜单
    contextMenu.exec(this->sql_view_food->viewport()->mapToGlobal(pos));
}

/*
 * swapRowsInDatabase
 * ① 合法的前提下交换数据库模型的指定两行的数据
 * ② 提交更新到数据库及视图
 * @row1 主动移动行
 * @row2 被动移动行
 */
void SqlWin::swapRowsInDatabase(int row1, int row2) {
    // 判断移动是否合法
    if (row1 == row2 || row1 < 0 || row2 < 0 || row1 >= sql_model_food->rowCount() || row2 >= sql_model_food->rowCount()) {
        QMessageBox::information(this, tr("提示"), tr("非法移动"));
        return;
    }

    // 获取第一行和第二行的所有列数据
    int columnCount = sql_model_food->columnCount();
    QVariantList row1Data;
    QVariantList row2Data;

    for (int col = 0; col < columnCount; ++col) {
        row1Data.append(sql_model_food->data(sql_model_food->index(row1, col)));
        row2Data.append(sql_model_food->data(sql_model_food->index(row2, col)));
    }

    // 交换数据
    for (int col = 0; col < columnCount; ++col) {
        // 设置 row1 行为 row2 数据
        sql_model_food->setData(sql_model_food->index(row1, col), row2Data.at(col));
        // 设置 row2 行为 row1 数据
        sql_model_food->setData(sql_model_food->index(row2, col), row1Data.at(col));
    }

    // 提交更改并刷新模型
    this->Sql_ModelAndView_Update_Food();
}

/*
 * sql_dataChanged_slot
 * ① 槽函数,被动触发将改变的数据同步到客户端
 * ② 只是简单的调用删除和添加来达到目的
 * @topLeft 受影响的项
 */
void SqlWin::sql_dataChanged_slot(const QModelIndex &topLeft) {
    // 输出相关信息
    qDebug() << "Data modified at row:" << topLeft.row()
             << "data" << topLeft.data().toByteArray();

    // 简单地调用删除和添加
    emit this->update_Client_Sql_Signal(MSG_TYPE_DEL, topLeft.row());
    emit this->update_Client_Sql_Signal(MSG_TYPE_ADD, topLeft.row());
}

/*
 * update_Client_Sql_Slot
 * ① 槽函数,主动同步改变到客户端
 * @msgType 此次操作的类型
 * @rowCount 要操作的行,缺省为-1即为最后一行
 */
void SqlWin::update_Client_Sql_Slot(QString msgType, int rowCount) {
    QByteArray message; // 存放序列化数据
    MenuData data;

    // 实例序列化对象
    QDataStream out(&message, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);

    int row = rowCount;
    if(rowCount == -1)
        row = sql_model_food->rowCount() - 1;

    data.name 	= sql_model_food->data(sql_model_food->index(row, 0)).toString();
    data.kind 	= sql_model_food->data(sql_model_food->index(row, 1)).toString();
    data.price 	= sql_model_food->data(sql_model_food->index(row, 2)).toFloat();
    data.img 	= sql_model_food->data(sql_model_food->index(row, 3)).toString();
    out << data;

    // 群发,每个客户端都要更新
    this->_tcp_server->Board_Message(message, msgType);
}

/*
 * Sql_Recv_Update_Order_Page
 * ① 将订单详情存放到订单详情表中
 * ② 调用Sql_ModeAndView_Update_Order更新数据
 * @data 存放着订单信息的结构体
 */
void SqlWin::Sql_Recv_Update_Order_Page(OrderData &data) {
    QSqlQuery query;
    QString cmd;
    cmd = QString("INSERT INTO OrderPage ("
                  PAGE_TABLE_TAB_2","
                  PAGE_TABLE_TAB_3","
                  PAGE_TABLE_TAB_4","
                  PAGE_TABLE_TAB_5
                  ") VALUES (:arg1, :arg2, :arg3, :arg4)");
    query.prepare(cmd);
    query.bindValue(":arg1", data.id);
    query.bindValue(":arg2", data.name);
    query.bindValue(":arg3", data.price);
    query.bindValue(":arg4", data.num);
    query.exec();

    // 更新
    Sql_ModelAndView_Update_Order();
}

/*
 * Sql_Recv_Update_Order_Page
 * ① 将订单详情存放到订单详情表中
 * ② 调用Sql_ModeAndView_Update_Order更新数据
 * @order_id 订单的编号
 * @custom_id 客户的序号
 * @account 订单的支付账号
 */
void SqlWin::Sql_Recv_Update_Order_Tab(QString order_id, int custom_id, QString account) {
    QSqlQuery query;
    QString cmd;
    cmd = QString("INSERT INTO OrderTable ("
                  ORDER_TABLE_TAB_1","
                  ORDER_TABLE_TAB_2","
                  ORDER_TABLE_TAB_3","
                  ORDER_TABLE_TAB_4
                  ") VALUES (:arg1, :arg2, :arg3, :arg4)");
    query.prepare(cmd);
    query.bindValue(":arg1", order_id);
    query.bindValue(":arg2", custom_id);
    query.bindValue(":arg3", QDateTime::currentDateTime().toString(Qt::ISODate));
    query.bindValue(":arg4", account);
    query.exec();

    // 更新
    Sql_ModelAndView_Update_Order();
}
/* ====================================================================================== */
// 添加行
void SqlWin::on_pBtn_foodAdd_clicked()
{
    FoodManagement * win = new FoodManagement(this);
    win->show();
}

// 删除行
void SqlWin::on_pBtn_foodDel_clicked()
{
    // 获取当前选中行
    QItemSelectionModel *selectLine = this->sql_view_food->selectionModel();
    if(!selectLine->hasSelection()) {
        QMessageBox::warning(this, "警告", "请先选择要删除的一行");
        return;
    }

    // 获取选择行的索引
    QModelIndex index = selectLine->currentIndex();
    int row = index.row();

    emit update_Client_Sql_Signal(MSG_TYPE_DEL, row); // 客户端数据同步

    // 删除模型中的行
    if(sql_model_food->removeRow(row)) {
        if(sql_model_food->submitAll()) {
            QMessageBox::information(this, "成功", "删除成功");
            Sql_ModelAndView_Update_Food(); // 服务器视图更新
        }else {
            QMessageBox::information(this, "失败", "删除失败");
            sql_model_food->revertAll();
        }
    }
}

// 上移当前行
void SqlWin::on_pBtn_foodUp_clicked()
{
    // 获取当前选中行
    QItemSelectionModel *selectLine = this->sql_view_food->selectionModel();
    if(!selectLine->hasSelection()) {
        QMessageBox::warning(this, "警告", "请先选择要移动的一行");
        return;
    }

    // 获取选择行的索引
    QModelIndex index = selectLine->currentIndex();
    int row = index.row();

    this->swapRowsInDatabase(row - 1, row);
}

// 向下移动当前行
void SqlWin::on_pBtn_foodDown_clicked()
{
    // 获取当前选中行
    QItemSelectionModel *selectLine = this->sql_view_food->selectionModel();
    if(!selectLine->hasSelection()) {
        QMessageBox::warning(this, "警告", "请先选择要移动的一行");
        return;
    }

    // 获取选择行的索引
    QModelIndex index = selectLine->currentIndex();
    int row = index.row();

    this->swapRowsInDatabase(row, row + 1);
}

// 交换两行
void SqlWin::on_pBtn_foodSwap_clicked()
{
    // 获取当前选中行
    QItemSelectionModel *selectLine = this->sql_view_food->selectionModel();
    if (!selectLine->hasSelection()) {
        QMessageBox::warning(this, "警告", "请先选择要移动的一行");
        return;
    }

    // 获取选择行的索引
    QModelIndex index = selectLine->currentIndex();
    int row1 = index.row();

    // 提示用户选择目标行
    QLabel tip("选择交换到", ui->tabWidget);
    // tip.move(QPoint(ui->tableView_food->width()/2, ui->tableView_food->y()));
    tip.setStyleSheet("background-color: rgb(115, 255, 190);"
"font: 14pt ""幼圆"";padding: 5px;border-radius: 10px");
    tip.show();

    // 创建一个事件循环，等待用户选择目标行
    QEventLoop eventLoop;

    // 连接目标行选择信号和退出事件循环
    connect(selectLine, &QItemSelectionModel::selectionChanged, &eventLoop, &QEventLoop::quit);

    // 设置一个定时器，防止无限等待
    QTimer::singleShot(30000, &eventLoop, &QEventLoop::quit);  // 设置30秒超时

    // 启动事件循环等待用户选择
    eventLoop.exec();

    // 检查是否有选择目标行
    if (!selectLine->hasSelection()) {
        QMessageBox::warning(this, "警告", "选择超时，请重新尝试");
        return;
    }

    // 获取目标行索引
    QModelIndex targetIndex = selectLine->currentIndex();
    int row2 = targetIndex.row();

    // 如果源行和目标行相同，不进行任何操作
    if (row1 == row2) {
        QMessageBox::information(this, "提示", "源行和目标行相同，无法交换");
        return;
    }

    // 交换数据
    swapRowsInDatabase(row1, row2);
}

// 验证许可
void SqlWin::on_pBtn_tcpEnter_clicked()
{
    QString passwd = ui->lineEdit_passwd->text();
    if(passwd == "I am passwd") {
        ui->pBtn_tcpEnter->setStyleSheet("background-color: green");
        ui->pBtn_tcpOpen->setEnabled(true);
        ui->tabWidget->setTabEnabled(0, true);
        ui->tabWidget->setTabEnabled(1, true);
    } else {
        ui->pBtn_tcpEnter->setStyleSheet("background-color: red");
        ui->pBtn_tcpOpen->setEnabled(false);
        ui->tabWidget->setTabEnabled(0, false);
        ui->tabWidget->setTabEnabled(1, false);
    }
    // 允许运行服务器
}

// 运行服务器
void SqlWin::on_pBtn_tcpOpen_clicked()
{
    QString port = ui->lineEdit_tcpPort->text();
    this->_tcp_server->Tcp_Server_Start(port);

    // 成功运行就绑定'打烊'槽函数并改变按钮样式
    if(_tcp_server->isShutdown() == false) {
        ui->pBtn_tcpOpen->setText("打烊");
        ui->pBtn_tcpOpen->setStyleSheet("color: red");
        ui->label_serverSta->setStyleSheet("background-color: green;");
        ui->label_serverSta->setText("运行中...");
        disconnect(ui->pBtn_tcpOpen, nullptr, nullptr, nullptr);

        connect(ui->pBtn_tcpOpen, &QPushButton::clicked, [&]() {
            _tcp_server->setShutdown();
            ui->pBtn_tcpOpen->setText("营业");
            ui->pBtn_tcpOpen->setStyleSheet("color: black");
            ui->label_serverSta->setStyleSheet("background-color: red;");
            ui->label_serverSta->setText("关机中...");
            disconnect(ui->pBtn_tcpOpen, nullptr, nullptr, nullptr);
            connect(ui->pBtn_tcpOpen,  &QPushButton::clicked, this, on_pBtn_tcpOpen_clicked);
        });
    }
}

// 返回订单列表
void SqlWin::on_pBtn_orderBack_clicked()
{
    ui->stackedWidget->setCurrentWidget(sql_view_order);
    ui->pBtn_orderBack->setHidden(true);
    ui->pBtn_orderBack->setEnabled(false);
}

// 将订单导出
void SqlWin::on_pBtn_orderSwap_clicked()
{
    // 打开文件保存对话框,选择保存路径
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "",
                                                    "CSV Files (*.csv);;All Files (*)");
    // 取消保存
    if(fileName.isEmpty()) {
        return;
    }

    // 打开文件写入
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件";
        return;
    }

    QTextStream out(&file);

    // 获取模型中的数据并写入文件(CVS格式)
    int rowCount = sql_mode_order->rowCount();
    int columnCount = sql_mode_order->columnCount();

    // 写入CSV文件表头
    for(int col = 0; col < columnCount;col++) {
        out << sql_mode_order->headerData(col, Qt::Horizontal).toString();
        if(col < columnCount - 1) {
            out << "		\t";
        }
    }
    out << "\n";

    // 查询订单的详细
    QSqlQuery query;
    QString cmd;
    cmd = QString("SELECT * FROM OrderPage WHERE"
                PAGE_TABLE_TAB_2
                "= :id");


    // 写入表格数据
    for(int row = 0;row < rowCount;row++) {
        for(int col = 0;col < columnCount;col++) {
            out << sql_mode_order->data(sql_mode_order->index(row, col)).toString();
            if(col < columnCount - 1) {
                out << "	\t";
            }
        }
        out << "\n";

        // 订单id
        QString orderId = sql_mode_order->data(sql_mode_order->index(row, 0)).toString();
        query.prepare(cmd);
        query.bindValue(":id", orderId);
        query.exec();

        // 订单详情
        int line_feed = 0;
        while(query.next()) {
            QByteArray dishName = query.value(2).toString().toUtf8();
            QByteArray price = QString::number(query.value(3).toFloat()).toUtf8();
            QByteArray num = query.value(4).toString().toUtf8();

            out << dishName << "\t" << price << "	\tx" << num;
            if(line_feed % 4 == 0) out << "\n";
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(this, tr("提示"), tr("数据已导出"));
}

// 清空订单信息
void SqlWin::on_pBtn_orderClear_clicked()
{
    // 询问是否清空
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, tr("请求确认"), tr("确定要清空订单数据吗?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        // 清空表
        QSqlQuery query;
        query.exec("DELETE FROM OrderTable");
        query.exec("DELETE FROM OrderPage");
    }

    Sql_ModelAndView_Update_Order();
}

// 检索
void SqlWin::on_lineEdit_search_textChanged(const QString &arg1)
{
    // 获取搜索依据
    QString kind = ui->comboBox->currentText();
    int col = 0;
    if(kind == "菜名") col = 0;
    else if(kind == "品类") col = 1;

    // 遍历所有行
    int rowCount = this->sql_model_food->rowCount();
    for(int row = 0;row < rowCount;row++) {
        // 获取对应的列数据
        QString itemData = sql_model_food->data(sql_model_food->index(row, col)).toString();

        // 默认为隐藏
        bool shouldHide = true;
        if(itemData == arg1 || arg1.isEmpty()) {
            shouldHide = false;
        }
        this->sql_view_food->setRowHidden(row, shouldHide);
    }
}

// 隐藏账号列
void SqlWin::on_radioButton_account_toggled(bool checked)
{
    if(checked)
        sql_view_order->setColumnHidden(3, true); // 隐藏付款账号
    else
        sql_view_order->setColumnHidden(3, false); // 显示付款账号
}

