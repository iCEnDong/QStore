QT = core \
    widgets \
    sql \
    network

CONFIG += c++17 #cmdline

SOURCES += \
        food_management.cpp \
        main.cpp \
        sqlwin.cpp \
        tcp_server.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    food_management.h \
    os_config.h \
    override_painter.h \
    sqlwin.h \
    tcp_server.h

FORMS += \
    food_management.ui \
    sqlwin.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    images/可乐.jpg
