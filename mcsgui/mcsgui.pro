#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T19:47:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mcsgui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
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
    mcsgraph.cpp \
    newdialog.cpp \
    pipe.cpp \
    widthmodifydialog.cpp \
    calc.cpp \
    generdialog.cpp

HEADERS += \
        mainwindow.h \
    mcsgraph.h \
    newdialog.h \
    pipenum.h \
    pipe.h \
    widthmodifydialog.h \
    calc.h \
    generdialog.h

FORMS += \
        mainwindow.ui \
    newdialog.ui \
    widthmodify.ui \
    generdialog.ui

RESOURCES += \
    icon.qrc
