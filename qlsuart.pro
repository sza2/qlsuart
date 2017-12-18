#-------------------------------------------------
#
# Project created by QtCreator 2017-12-17T18:30:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qlsuart
TEMPLATE = app
QT += widgets serialport
CONFIG += c++11


SOURCES += main.cpp\
        qlsuart.cpp \
    qlsconfig.cpp

HEADERS  += qlsuart.h \
    qlsconfig.h

FORMS    += qlsuart.ui \
    qlsconfig.ui
