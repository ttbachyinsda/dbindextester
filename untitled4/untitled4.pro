QT += core
QT -= gui

CONFIG += c++11

TARGET = untitled4
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    interface.cpp \
    naivedb.cpp \
    naivemultidb.cpp

HEADERS += \
    interface.h \
    naivedb.h \
    naivemultidb.h
