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
    ui/camview.cpp \
    ui/cammanager.cpp \
    gldrawer.cpp \
    datatransfer.cpp

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
    ui/camview.h \
    ui/cammanager.h \
    gldrawer.h \
    datatransfer.h

FORMS    += ui/mainwindow.ui \
    ui/camview.ui

DISTFILES += \
    metaData/testData.txt \
    metaData/AreaData_B207.JSON \
    metaData/01.png \
DESTDIR = $$PWD

LIBS += opengl32.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../openCV/opencv/build/x64/vc14/lib/ -lopencv_world310
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../openCV/opencv/build/x64/vc14/lib/ -lopencv_world310d

INCLUDEPATH += $$PWD/../../../../openCV/opencv/build/include
DEPENDPATH += $$PWD/../../../../openCV/opencv/build/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../openCV/opencv/build/x64/vc14/lib/libopencv_world310.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../openCV/opencv/build/x64/vc14/lib/libopencv_world310d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../openCV/opencv/build/x64/vc14/lib/opencv_world310.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../openCV/opencv/build/x64/vc14/lib/opencv_world310d.lib
