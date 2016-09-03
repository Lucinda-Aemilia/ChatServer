#-------------------------------------------------
#
# Project created by QtCreator 2016-09-03T19:31:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configdialog.cpp \
    chatserver.cpp \
    chatthread.cpp

HEADERS  += mainwindow.h \
    configdialog.h \
    chatserver.h \
    chatthread.h

FORMS    += mainwindow.ui \
    configdialog.ui
