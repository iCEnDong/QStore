#include "food_management.h"
#include "ui_food_management.h"
#include "sqlwin.h"
#include "sqlwin.h"
#include <QSqlQuery>
#include <QFileDialog>

FoodManagement::FoodManagement(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FoodManagement)
{
    ui->setupUi(this);
}

FoodManagement::~FoodManagement()
{
    delete ui;
}

// 确认添加
void FoodManagement::on_pBtn_enter_clicked()
{
    // 获取父类指针对象
    SqlWin * sqlWin = (SqlWin *)this->parent();

    // 获取文本框内容
    QString food_name = ui->lineEdit_name->text();
    QString food_kind = ui->comboBox_kind->currentText();
    QString food_price = ui->lineEdit_price->text();
    QString food_imgPath = ui->lineEdit_imgPath->text();

    // 确保格式正确
    if(food_name.isEmpty()) {
        QMessageBox::information(this, tr("警告"), tr("请正确填写菜名"));
        return;
    }else if(food_kind.isEmpty()) {
        QMessageBox::information(this, tr("警告"), tr("请正确填写菜品"));
        return;
    }else if(food_price.isEmpty()) {
        QMessageBox::information(this, tr("警告"), tr("请正确填写价格"));
        return;
    }else if(food_imgPath.isEmpty()) {
        QMessageBox::information(this, tr("警告"), tr("请正确填写图片路径"));
        return;
    }


    // 更新数据库
    QSqlQuery  query;
    QString cmd = QString("INSERT INTO food_table ("
                  FOOD_TABLE_TAB_1","
                  FOOD_TABLE_TAB_2","
                  FOOD_TABLE_TAB_3","
                  FOOD_TABLE_TAB_4
                  ") VALUES (:name, :kind, :price, :imgPath)");
    query.prepare(cmd);
    query.bindValue(":name", food_name);
    query.bindValue(":kind", food_kind);
    query.bindValue(":price", food_price);
    query.bindValue(":imgPath", food_imgPath);

#if OS_SQLADDDEBUG
    if(query.exec()) {
        qDebug() << "success";
    }else {
        qDebug() << "failed" << query.lastError();
    }
#endif

    sqlWin->Sql_ModelAndView_Update_Food();
    emit sqlWin->update_Client_Sql_Signal(MSG_TYPE_ADD);
    this->close();
}

// 取消添加
void FoodManagement::on_pBtn_cancel_clicked()
{
    qDebug() << "取消添加";
    this->close();
}

// 选手展示图片
void FoodManagement::on_pBtn_imgPath_clicked()
{
    // 打开文件对话框，选择图片
    QString filePath = QFileDialog::getOpenFileName(
        nullptr, "选择图片", "../../images", "Images (*.png *.jpg *.jpeg *.bmp *.gif);;所有文件 (*.*)"
        );

    // 如果文件路径不为空，则将路径写入 QLineEdit
    if (!filePath.isEmpty()) {
        ui->lineEdit_imgPath->setText(":/images/"+filePath.section('/', -1));
    }
}

// 回车确认添加
void FoodManagement::on_lineEdit_price_returnPressed()
{
    on_pBtn_enter_clicked();
}

// 判断菜名是否冲突
void FoodManagement::on_lineEdit_name_textChanged(const QString &arg1)
{
    SqlWin *sqlWin = (SqlWin *)(this->parent());

    // 遍历所有行
    int rowCount = sqlWin->sql_model_food->rowCount();
    for(int row = 0;row < rowCount;row++) {
        // 获取对应的列数据
        QString itemData = sqlWin->sql_model_food->data(sqlWin->sql_model_food->index(row, 0)).toString();
        if(arg1 == itemData) {
            ui->lineEdit_name->setStyleSheet("QLineEdit { color: red; }");
            ui->pBtn_enter->setEnabled(false);
            break;
        } else {
            ui->lineEdit_name->setStyleSheet("QLineEdit { color: green; }");
            ui->pBtn_enter->setEnabled(true);
        }
    }
}

