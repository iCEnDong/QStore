QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    main.cpp \
    order_menu.cpp \
    playui.cpp \
    tcp_client.cpp \
    v4l2_camera.cpp

HEADERS += \
    camera.h \
    order_menu.h \
    override_painter.h \
    playui.h \
    tcp_client.h \
    v4l2_camera.h

FORMS += \
    camera.ui \
    ordermenu.ui \
    playui.ui \
    v4l2camera.ui

include(QZXing/QZXing.pri)
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
