#-------------------------------------------------
#
# Project created by QtCreator 2016-09-16T13:39:09
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WIFI_tracker_MTK
TEMPLATE = app


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/devicelist.cpp \
    src/deviceitem.cpp

HEADERS  += header/mainwindow.h \
    header/deviceitem.h \
    header/devicelist.h

FORMS    += ui/mainwindow.ui
