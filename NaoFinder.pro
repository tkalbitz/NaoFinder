#-------------------------------------------------
#
# Project created by QtCreator 2013-05-08T21:39:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NaoFinder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    robotwidget.cpp \
    infocast.cpp

HEADERS  += mainwindow.h \
    robotwidget.h \
    infocast.h

FORMS    += mainwindow.ui \
    robotwidget.ui

RESOURCES += \
    images.qrc
