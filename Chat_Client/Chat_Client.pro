#-------------------------------------------------
#
# Project created by QtCreator 2017-11-15T09:10:45
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat_Client
TEMPLATE = app


SOURCES += \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    reg.cpp \
    setting.cpp

HEADERS  += \
    login.h \
    mainwindow.h \
    reg.h \
    setting.h

FORMS    += mainwindow.ui \
    login.ui \
    reg.ui \
    setting.ui
