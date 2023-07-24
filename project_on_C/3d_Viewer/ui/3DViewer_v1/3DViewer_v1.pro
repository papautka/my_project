QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(../../QtGifImage-master/src/gifimage/qtgifimage.pri)
TARGET = 3DViewer
TEMPLATE = app

QMAKE_CXXFLAGS += -Wno-deprecated

SOURCES += main.cpp\
    ../../c_files/parser.c \
    ../../c_files/affine.c \
        mainwindow.cpp \
    oglwidget.cpp

HEADERS  += mainwindow.h \
    ../../c_files/3D_Viewer.h \
    oglwidget.h

FORMS    += mainwindow.ui

DISTFILES += \
    ../../obj_files/cube.obj
