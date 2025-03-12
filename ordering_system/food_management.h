#ifndef FOOD_MANAGEMENT_H
#define FOOD_MANAGEMENT_H

#include "os_config.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>
#include <QResource>

namespace Ui {
class FoodManagement;
}

class FoodManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit FoodManagement(QWidget *parent = nullptr);
    ~FoodManagement();

private slots:
    void on_pBtn_enter_clicked();

    void on_pBtn_cancel_clicked();

    void on_pBtn_imgPath_clicked();

    void on_lineEdit_price_returnPressed();

    void on_lineEdit_name_textChanged(const QString &arg1);

private:
    Ui::FoodManagement *ui;
};

#endif // FOOD_MANAGEMENT_H
