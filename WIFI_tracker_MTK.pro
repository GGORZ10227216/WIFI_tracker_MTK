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
    src/deviceitem.cpp \
    src/nodemanagement.cpp \
    src/nodethread.cpp \
    src/devicemap.cpp \
    src/devicedata.cpp

HEADERS  += header/mainwindow.h \
    header/deviceitem.h \
    header/devicelist.h \
    header/nodemanagement.h \
    header/nodethread.h \
    header/devicemap.h \
    header/devicedata.h

FORMS    += ui/mainwindow.ui

DISTFILES += \
    metaData/testData.txt \
    metaData/AreaData_B207.JSON \
    metaData/01.png
DESTDIR = $$PWD
