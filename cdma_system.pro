#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T15:59:50
#
#-------------------------------------------------

QT       += core gui

LIBS += -LC:\mymysql\mysql\lib -llibmysql

TARGET = cdma_system
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindlg.cpp \
    scriptdlg.cpp \
    mymysql.cpp

HEADERS  += mainwindow.h \
    logindlg.h \
    scriptdlg.h \
    mymysql.h
