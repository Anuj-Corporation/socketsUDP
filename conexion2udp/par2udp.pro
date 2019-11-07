#-------------------------------------------------
#
# Project created by electronfer
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = par2udp
TEMPLATE = app


SOURCES += main.cpp\
        conexion_2.cpp

HEADERS  += conexion_2.h

FORMS    += conexion_2.ui
