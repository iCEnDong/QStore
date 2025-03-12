#include <QApplication>
#include "sqlwin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SqlWin win;
    win.show();
    return a.exec();
}
