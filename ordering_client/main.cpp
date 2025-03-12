#include "order_menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OrderMenu w;
    Camera *camera = new Camera(&w);
    camera->show();
    w.show();
    return a.exec();
}
