/********************************************************************************
** Form generated from reading UI file 'v4l2_camera.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_V4L2_CAMERA_H
#define UI_V4L2_CAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_V4L2Camera
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *V4L2Camera)
    {
        if (V4L2Camera->objectName().isEmpty())
            V4L2Camera->setObjectName(QStringLiteral("V4L2Camera"));
        V4L2Camera->resize(800, 600);
        centralwidget = new QWidget(V4L2Camera);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        V4L2Camera->setCentralWidget(centralwidget);
        menubar = new QMenuBar(V4L2Camera);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 29));
        V4L2Camera->setMenuBar(menubar);
        statusbar = new QStatusBar(V4L2Camera);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        V4L2Camera->setStatusBar(statusbar);

        retranslateUi(V4L2Camera);

        QMetaObject::connectSlotsByName(V4L2Camera);
    } // setupUi

    void retranslateUi(QMainWindow *V4L2Camera)
    {
        V4L2Camera->setWindowTitle(QApplication::translate("V4L2Camera", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class V4L2Camera: public Ui_V4L2Camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_V4L2_CAMERA_H
