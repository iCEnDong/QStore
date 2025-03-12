#ifndef PLAYUI_H
#define PLAYUI_H

#include "tcp_client.h"
#include <QMainWindow>
#include <QZXing>

namespace Ui {
class PlayUi;
}

class PlayUi : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayUi(QWidget *parent = nullptr);
    ~PlayUi();
    void Play_Ui_Init();
    void setPayResult(bool result);

private slots:
    void on_pBtn_cancle_clicked();

    void on_pBtn_play_clicked();

private:
    Ui::PlayUi *ui;

};

#endif // PLAYUI_H
