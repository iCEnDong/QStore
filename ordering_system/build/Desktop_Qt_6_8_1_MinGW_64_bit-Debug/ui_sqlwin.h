/********************************************************************************
** Form generated from reading UI file 'sqlwin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQLWIN_H
#define UI_SQLWIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SqlWin
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_food;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_search;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pBtn_foodSwap;
    QPushButton *pBtn_foodUp;
    QPushButton *pBtn_foodDown;
    QPushButton *pBtn_foodDel;
    QPushButton *pBtn_foodAdd;
    QComboBox *comboBox;
    QVBoxLayout *vBoxLayout_food;
    QWidget *tab_order;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pBtn_orderBack;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QRadioButton *radioButton_account;
    QPushButton *pBtn_orderSwap;
    QPushButton *pBtn_orderClear;
    QVBoxLayout *vBoxLayout_order;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QWidget *tab_tcp;
    QWidget *widget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *lineEdit_passwd;
    QPushButton *pBtn_tcpEnter;
    QTextBrowser *textBrowser_tcp;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_tcpPort;
    QPushButton *pBtn_tcpOpen;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_serverTitle;
    QLabel *label_serverSta;

    void setupUi(QMainWindow *SqlWin)
    {
        if (SqlWin->objectName().isEmpty())
            SqlWin->setObjectName("SqlWin");
        SqlWin->setEnabled(true);
        SqlWin->resize(824, 627);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SqlWin->sizePolicy().hasHeightForWidth());
        SqlWin->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(SqlWin);
        centralwidget->setObjectName("centralwidget");
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab_food = new QWidget();
        tab_food->setObjectName("tab_food");
        sizePolicy.setHeightForWidth(tab_food->sizePolicy().hasHeightForWidth());
        tab_food->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(tab_food);
        gridLayout->setObjectName("gridLayout");
        lineEdit_search = new QLineEdit(tab_food);
        lineEdit_search->setObjectName("lineEdit_search");
        lineEdit_search->setStyleSheet(QString::fromUtf8(""));
        lineEdit_search->setClearButtonEnabled(true);

        gridLayout->addWidget(lineEdit_search, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pBtn_foodSwap = new QPushButton(tab_food);
        pBtn_foodSwap->setObjectName("pBtn_foodSwap");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pBtn_foodSwap->sizePolicy().hasHeightForWidth());
        pBtn_foodSwap->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pBtn_foodSwap);

        pBtn_foodUp = new QPushButton(tab_food);
        pBtn_foodUp->setObjectName("pBtn_foodUp");

        verticalLayout->addWidget(pBtn_foodUp);

        pBtn_foodDown = new QPushButton(tab_food);
        pBtn_foodDown->setObjectName("pBtn_foodDown");

        verticalLayout->addWidget(pBtn_foodDown);

        pBtn_foodDel = new QPushButton(tab_food);
        pBtn_foodDel->setObjectName("pBtn_foodDel");

        verticalLayout->addWidget(pBtn_foodDel);

        pBtn_foodAdd = new QPushButton(tab_food);
        pBtn_foodAdd->setObjectName("pBtn_foodAdd");

        verticalLayout->addWidget(pBtn_foodAdd);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        comboBox = new QComboBox(tab_food);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        vBoxLayout_food = new QVBoxLayout();
        vBoxLayout_food->setSpacing(0);
        vBoxLayout_food->setObjectName("vBoxLayout_food");

        gridLayout->addLayout(vBoxLayout_food, 1, 0, 1, 1);

        gridLayout->setColumnStretch(0, 9);
        tabWidget->addTab(tab_food, QString());
        tab_order = new QWidget();
        tab_order->setObjectName("tab_order");
        gridLayout_3 = new QGridLayout(tab_order);
        gridLayout_3->setObjectName("gridLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pBtn_orderBack = new QPushButton(tab_order);
        pBtn_orderBack->setObjectName("pBtn_orderBack");
        pBtn_orderBack->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);"));
        pBtn_orderBack->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditUndo));
        pBtn_orderBack->setIcon(icon);

        horizontalLayout_4->addWidget(pBtn_orderBack);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 9);

        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        radioButton_account = new QRadioButton(tab_order);
        radioButton_account->setObjectName("radioButton_account");
        radioButton_account->setEnabled(true);
        radioButton_account->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);"));
        radioButton_account->setChecked(true);

        verticalLayout_2->addWidget(radioButton_account);

        pBtn_orderSwap = new QPushButton(tab_order);
        pBtn_orderSwap->setObjectName("pBtn_orderSwap");

        verticalLayout_2->addWidget(pBtn_orderSwap);

        pBtn_orderClear = new QPushButton(tab_order);
        pBtn_orderClear->setObjectName("pBtn_orderClear");

        verticalLayout_2->addWidget(pBtn_orderClear);


        gridLayout_3->addLayout(verticalLayout_2, 0, 1, 1, 1);

        vBoxLayout_order = new QVBoxLayout();
        vBoxLayout_order->setObjectName("vBoxLayout_order");
        stackedWidget = new QStackedWidget(tab_order);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        vBoxLayout_order->addWidget(stackedWidget);


        gridLayout_3->addLayout(vBoxLayout_order, 0, 0, 1, 1);

        gridLayout_3->setColumnStretch(0, 9);
        gridLayout_3->setColumnStretch(1, 1);
        tabWidget->addTab(tab_order, QString());
        tab_tcp = new QWidget();
        tab_tcp->setObjectName("tab_tcp");
        widget = new QWidget(tab_tcp);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(12, 12, 781, 551));
        widget->setStyleSheet(QString::fromUtf8(""));
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(180, 30, 591, 34));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        horizontalLayout_3->addWidget(label_5);

        lineEdit_passwd = new QLineEdit(layoutWidget);
        lineEdit_passwd->setObjectName("lineEdit_passwd");
        lineEdit_passwd->setEchoMode(QLineEdit::EchoMode::Password);
        lineEdit_passwd->setClearButtonEnabled(true);

        horizontalLayout_3->addWidget(lineEdit_passwd);

        pBtn_tcpEnter = new QPushButton(layoutWidget);
        pBtn_tcpEnter->setObjectName("pBtn_tcpEnter");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::UserAvailable));
        pBtn_tcpEnter->setIcon(icon1);

        horizontalLayout_3->addWidget(pBtn_tcpEnter);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 10);
        horizontalLayout_3->setStretch(2, 1);
        textBrowser_tcp = new QTextBrowser(widget);
        textBrowser_tcp->setObjectName("textBrowser_tcp");
        textBrowser_tcp->setGeometry(QRect(180, 120, 591, 381));
        layoutWidget1 = new QWidget(widget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(180, 70, 591, 34));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        lineEdit_tcpPort = new QLineEdit(layoutWidget1);
        lineEdit_tcpPort->setObjectName("lineEdit_tcpPort");
        lineEdit_tcpPort->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(lineEdit_tcpPort);

        pBtn_tcpOpen = new QPushButton(layoutWidget1);
        pBtn_tcpOpen->setObjectName("pBtn_tcpOpen");
        pBtn_tcpOpen->setEnabled(false);

        horizontalLayout->addWidget(pBtn_tcpOpen);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 15);
        verticalLayoutWidget = new QWidget(widget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 230, 160, 87));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_serverTitle = new QLabel(verticalLayoutWidget);
        label_serverTitle->setObjectName("label_serverTitle");
        QFont font;
        font.setPointSize(26);
        label_serverTitle->setFont(font);

        verticalLayout_3->addWidget(label_serverTitle);

        label_serverSta = new QLabel(verticalLayoutWidget);
        label_serverSta->setObjectName("label_serverSta");
        label_serverSta->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);\n"
"color: rgb(255, 255, 255);"));

        verticalLayout_3->addWidget(label_serverSta);

        tabWidget->addTab(tab_tcp, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        SqlWin->setCentralWidget(centralwidget);

        retranslateUi(SqlWin);

        tabWidget->setCurrentIndex(2);
        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SqlWin);
    } // setupUi

    void retranslateUi(QMainWindow *SqlWin)
    {
        SqlWin->setWindowTitle(QCoreApplication::translate("SqlWin", "MainWindow", nullptr));
        lineEdit_search->setPlaceholderText(QCoreApplication::translate("SqlWin", "\346\220\234\347\264\242", nullptr));
        pBtn_foodSwap->setText(QCoreApplication::translate("SqlWin", "\344\272\244\346\215\242", nullptr));
        pBtn_foodUp->setText(QCoreApplication::translate("SqlWin", "\344\270\212\347\247\273", nullptr));
        pBtn_foodDown->setText(QCoreApplication::translate("SqlWin", "\344\270\213\347\247\273", nullptr));
        pBtn_foodDel->setText(QCoreApplication::translate("SqlWin", "\345\210\240\351\231\244", nullptr));
        pBtn_foodAdd->setText(QCoreApplication::translate("SqlWin", "\346\267\273\345\212\240", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SqlWin", "\350\217\234\345\220\215", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SqlWin", "\345\223\201\347\261\273", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_food), QCoreApplication::translate("SqlWin", "\350\217\234\345\223\201", nullptr));
        pBtn_orderBack->setText(QString());
        radioButton_account->setText(QCoreApplication::translate("SqlWin", "\351\232\220\350\227\217\350\264\246\345\217\267", nullptr));
        pBtn_orderSwap->setText(QCoreApplication::translate("SqlWin", "\345\257\274\345\207\272", nullptr));
        pBtn_orderClear->setText(QCoreApplication::translate("SqlWin", "\346\270\205\347\251\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_order), QCoreApplication::translate("SqlWin", "\350\256\242\345\215\225", nullptr));
        label_5->setText(QCoreApplication::translate("SqlWin", "\350\256\270\345\217\257\350\257\201", nullptr));
        lineEdit_passwd->setText(QCoreApplication::translate("SqlWin", "I am passwd", nullptr));
        pBtn_tcpEnter->setText(QString());
        label_3->setText(QCoreApplication::translate("SqlWin", "port", nullptr));
        lineEdit_tcpPort->setText(QCoreApplication::translate("SqlWin", "8888", nullptr));
        pBtn_tcpOpen->setText(QCoreApplication::translate("SqlWin", "\350\220\245\344\270\232", nullptr));
        label_serverTitle->setText(QCoreApplication::translate("SqlWin", "\346\234\215\345\212\241\345\231\250", nullptr));
        label_serverSta->setText(QCoreApplication::translate("SqlWin", "\345\205\263\346\234\272\344\270\255...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_tcp), QCoreApplication::translate("SqlWin", "\350\277\220\350\220\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SqlWin: public Ui_SqlWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQLWIN_H
