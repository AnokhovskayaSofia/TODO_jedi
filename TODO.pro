QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qevent.cpp \
    qeventmodel.cpp \
    qinfo.cpp \
    qinfomodel.cpp \
    qlistmodel.cpp \
    qproject.cpp \
    qprojectmodel.cpp \
    qtask.cpp \
    qtaskdeligate.cpp

HEADERS += \
    mainwindow.h \
    qevent.h \
    qeventmodel.h \
    qinfo.h \
    qinfomodel.h \
    qlistmodel.h \
    qproject.h \
    qprojectmodel.h \
    qtask.h \
    qtaskdeligate.h

FORMS += \
    mainwindow.ui \
    settings_info.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    apps-free-icon-font.png \
    apps-free-icon-font.png \
    bookmark-free-icon-font.png \
    bookmark-free-icon-font.png \
    calendar-free-icon-font.png \
    calendar-free-icon-font.png \
    home-free-icon-font.png \
    home-free-icon-font.png \
    list-check-free-icon-font.png \
    list-check-free-icon-font.png \
    plus-free-icon-font (1).png \
    plus-free-icon-font (1).png

RESOURCES += \
    res.qrc
