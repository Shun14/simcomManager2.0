#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T17:04:51
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simcom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog_findlog.cpp \
    dialog_devicelog.cpp \
    dialog_devicelist.cpp

HEADERS  += mainwindow.h \
    dialog_findlog.h \
    dialog_devicelog.h \
    dialog_devicelist.h

FORMS    += mainwindow.ui \
    dialog_findlog.ui \
    dialog_devicelog.ui \
    dialog_devicelist.ui

DISTFILES +=

RESOURCES += \
    icon.qrc
RC_FILE=xiaoanbao.rc
