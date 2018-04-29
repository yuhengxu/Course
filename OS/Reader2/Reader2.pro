#-------------------------------------------------
#
# Project created by QtCreator 2018-04-20T17:17:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reader2
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

win32:RC_ICONS += avator.ico

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    readerwriter.cpp \
    config.cpp \
    overlap.cpp \
    Action.cpp \
    ActionList.cpp \
    Counter.cpp \
    Semaphore.cpp \
    Thread.cpp

HEADERS += \
        mainwindow.h \
    readerwriter.h \
    config.h \
    overlap.h \
    Action.h \
    ACTION_OPERATION.h \
    ACTION_TYPE.h \
    ActionList.h \
    Counter.h \
    Semaphore.h \
    Thread.h

FORMS += \
        mainwindow.ui
