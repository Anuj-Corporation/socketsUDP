#-------------------------------------------------
#
# Project created by electronfer
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = par1udp
TEMPLATE = app


SOURCES += main.cpp\
        conexion_1.cpp

HEADERS  += conexion_1.h

FORMS    += conexion_1.ui
