#-------------------------------------------------
#
# Project created by QtCreator 2016-09-16T13:39:09
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WIFI_tracker_MTK
TEMPLATE = app


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/nodemanagement.cpp \
    src/nodethread.cpp \
    src/tree/sorttreemodel.cpp \
    src/tree/treeitem.cpp \
    src/tree/treemodel.cpp \
    src/devicemap.cpp \
    src/devicedata.cpp \
    src/client/nodedata.cpp \
    src/client/machine.cpp \
    src/client/areadata.cpp

HEADERS  += header/mainwindow.h \
    header/nodemanagement.h \
    header/nodethread.h \
    header/tree/sorttreemodel.h \
    header/tree/treeitem.h \
    header/tree/treemodel.h \
    header/devicedata.h \
    header/devicemap.h \
    header/globalvariable.h \
    header/client/nodedata.h \
    header/client/machine.h \
    header/client/areadata.h

FORMS    += ui/mainwindow.ui

DISTFILES += \
    metaData/testData.txt \
    metaData/AreaData_B207.JSON \
    metaData/01.png \
    metaData/¦Ê³f½d¨Ò.JSON
DESTDIR = $$PWD
