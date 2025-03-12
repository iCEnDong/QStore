/********************************************************************************
** Form generated from reading UI file 'food_management.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOOD_MANAGEMENT_H
#define UI_FOOD_MANAGEMENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FoodManagement
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_name;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBox_kind;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_price;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lineEdit_imgPath;
    QPushButton *pBtn_imgPath;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pBtn_enter;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pBtn_cancel;
    QSpacerItem *horizontalSpacer_9;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FoodManagement)
    {
        if (FoodManagement->objectName().isEmpty())
            FoodManagement->setObjectName("FoodManagement");
        FoodManagement->resize(491, 536);
        centralwidget = new QWidget(FoodManagement);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(40, 0, 411, 501));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(28);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        lineEdit_name = new QLineEdit(layoutWidget);
        lineEdit_name->setObjectName("lineEdit_name");

        horizontalLayout->addWidget(lineEdit_name);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 20);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        comboBox_kind = new QComboBox(layoutWidget);
        comboBox_kind->addItem(QString());
        comboBox_kind->addItem(QString());
        comboBox_kind->addItem(QString());
        comboBox_kind->addItem(QString());
        comboBox_kind->addItem(QString());
        comboBox_kind->addItem(QString());
        comboBox_kind->addItem(QString());
        comboBox_kind->addItem(QString());
        comboBox_kind->setObjectName("comboBox_kind");

        horizontalLayout_2->addWidget(comboBox_kind);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 16);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        lineEdit_price = new QLineEdit(layoutWidget);
        lineEdit_price->setObjectName("lineEdit_price");

        horizontalLayout_3->addWidget(lineEdit_price);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(2, 16);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        horizontalLayout_5->addWidget(label_5);

        lineEdit_imgPath = new QLineEdit(layoutWidget);
        lineEdit_imgPath->setObjectName("lineEdit_imgPath");
        lineEdit_imgPath->setDragEnabled(false);

        horizontalLayout_5->addWidget(lineEdit_imgPath);

        pBtn_imgPath = new QPushButton(layoutWidget);
        pBtn_imgPath->setObjectName("pBtn_imgPath");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
        pBtn_imgPath->setIcon(icon);

        horizontalLayout_5->addWidget(pBtn_imgPath);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        pBtn_enter = new QPushButton(layoutWidget);
        pBtn_enter->setObjectName("pBtn_enter");

        horizontalLayout_4->addWidget(pBtn_enter);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        pBtn_cancel = new QPushButton(layoutWidget);
        pBtn_cancel->setObjectName("pBtn_cancel");

        horizontalLayout_4->addWidget(pBtn_cancel);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        horizontalLayout_4->setStretch(0, 3);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 5);
        horizontalLayout_4->setStretch(3, 1);
        horizontalLayout_4->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout_4);

        FoodManagement->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(FoodManagement);
        statusbar->setObjectName("statusbar");
        FoodManagement->setStatusBar(statusbar);

        retranslateUi(FoodManagement);

        QMetaObject::connectSlotsByName(FoodManagement);
    } // setupUi

    void retranslateUi(QMainWindow *FoodManagement)
    {
        FoodManagement->setWindowTitle(QCoreApplication::translate("FoodManagement", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("FoodManagement", "\346\267\273\345\212\240\350\217\234\345\223\201", nullptr));
        label_2->setText(QCoreApplication::translate("FoodManagement", "\346\226\260\350\217\234\345\220\215", nullptr));
        label_3->setText(QCoreApplication::translate("FoodManagement", "\350\217\234\345\223\201", nullptr));
        comboBox_kind->setItemText(0, QCoreApplication::translate("FoodManagement", "\350\224\254\350\217\234", nullptr));
        comboBox_kind->setItemText(1, QCoreApplication::translate("FoodManagement", "\350\202\211\351\243\237", nullptr));
        comboBox_kind->setItemText(2, QCoreApplication::translate("FoodManagement", "\346\260\264\344\272\247", nullptr));
        comboBox_kind->setItemText(3, QCoreApplication::translate("FoodManagement", "\350\261\206\345\210\266\345\223\201", nullptr));
        comboBox_kind->setItemText(4, QCoreApplication::translate("FoodManagement", "\344\270\273\351\243\237", nullptr));
        comboBox_kind->setItemText(5, QCoreApplication::translate("FoodManagement", "\346\261\244", nullptr));
        comboBox_kind->setItemText(6, QCoreApplication::translate("FoodManagement", "\346\260\264\346\236\234", nullptr));
        comboBox_kind->setItemText(7, QCoreApplication::translate("FoodManagement", "\351\205\222\346\260\264", nullptr));

        label_4->setText(QCoreApplication::translate("FoodManagement", "\344\273\267\346\240\274", nullptr));
        label_5->setText(QCoreApplication::translate("FoodManagement", "\345\261\225\347\244\272\345\233\276", nullptr));
        lineEdit_imgPath->setText(QCoreApplication::translate("FoodManagement", ":/resource/images/", nullptr));
        pBtn_imgPath->setText(QString());
        pBtn_enter->setText(QCoreApplication::translate("FoodManagement", "\347\241\256\350\256\244", nullptr));
        pBtn_cancel->setText(QCoreApplication::translate("FoodManagement", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FoodManagement: public Ui_FoodManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOOD_MANAGEMENT_H
