#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T18:39:22
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewGUITest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    movie.cpp \
    dbmanager.cpp \
    moviemanager.cpp

HEADERS  += mainwindow.h \
    movie.h \
    dbmanager.h \
    moviemanager.h

FORMS    += mainwindow.ui
