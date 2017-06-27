#-------------------------------------------------
#
# Project created by QtCreator 2017-06-25T13:20:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualTrackingUI
TEMPLATE = app

#include(G:/opt/qt/QtitanRibbon Demo/src/shared/qtitanribbon.pri)
#include($$quote(G:/opt/qt/QtitanRibbon Demo/src/shared/qtitannavigation.pri))

INCLUDEPATH += G:/opt/opencv-2.4.13/build/include
INCLUDEPATH += $$quote(G:/opt/qt/QtitanRibbon Demo/include)
INCLUDEPATH += $$quote(G:/opt/qt/QtitanNavigation Demo/include)

LIBS += G:/opt/opencv-2.4.13/build/x64/mingw/lib/libopencv_core2413.dll.a
LIBS += G:/opt/opencv-2.4.13/build/x64/mingw/lib/libopencv_highgui2413.dll.a
LIBS += G:/opt/opencv-2.4.13/build/x64/mingw/lib/libopencv_imgproc2413.dll.a
LIBS += G:/opt/opencv-2.4.13/build/x64/mingw/lib/libopencv_photo2413.dll.a
LIBS += G:/opt/opencv-2.4.13/build/x86/mingw/lib/libopencv_core2413.dll.a
LIBS += G:/opt/opencv-2.4.13/build/x86/mingw/lib/libopencv_highgui2413.dll.a
LIBS += G:/opt/opencv-2.4.13/build/x86/mingw/lib/libopencv_imgproc2413.dll.a
LIBS += G:/opt/opencv-2.4.13/build/x86/mingw/lib/libopencv_photo2413.dll.a
LIBS += $$quote(G:/opt/qt/QtitanRibbon Demo/bin/libqtnribbon4.a)
LIBS += $$quote(G:/opt/qt/QtitanNavigation Demo/bin/libqtnnavigation1.a)


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    imageconvert.cpp \
    aboutdialog.cpp \
    paintwidget.cpp \
    tabwidget_1.cpp
#    window.cpp

HEADERS += \
        mainwindow.h \
    imageconvert.h \
    aboutdialog.h \
    paintwidget.h \
    tabwidget_1.h
#    window.h

FORMS += \
        mainwindow.ui \
    aboutdialog.ui \
    tabwidget_1.ui

RESOURCES += \
    resource.qrc
