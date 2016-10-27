#-------------------------------------------------
#
# Project created by QtCreator 2016-09-16T13:39:09
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += webenginewidgets
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
    src/client/areadata.cpp \
    src/cammanager.cpp \
    src/gldrawer.cpp \
    src/videoproccsor.cpp \
    webv.cpp

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
    header/client/areadata.h \
    header/cammanager.h \
    header/gldrawer.h \
    header/videoprocessor.h \
    webv.h

FORMS    += ui/mainwindow.ui \
    webv.ui

DISTFILES += \
    metaData/testData.txt \
    metaData/AreaData_B207.JSON \
    metaData/01.png \
DESTDIR = $$PWD

LIBS += opengl32.lib

LIBS       += -lVLCQtCore -lVLCQtWidgets

win32:CONFIG(release, debug|release): LIBS += -LC:/openCV/opencv/build/x64/vc14/lib/ -lopencv_world310
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/openCV/opencv/build/x64/vc14/lib/ -lopencv_world310d
else:unix:!macx: LIBS += -LC:/openCV/opencv/build/x64/vc14/lib/ -lopencv_world310

INCLUDEPATH += C:/openCV/opencv/build/include
DEPENDPATH += C:/openCV/opencv/build/include
