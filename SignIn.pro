#-------------------------------------------------
#
# Project created by QtCreator 2017-03-21T16:14:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SignIn
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dialog.cpp \
    mytitlebar.cpp

HEADERS  += widget.h \
    dialog.h \
    mytitlebar.h

FORMS    += widget.ui \
    dialog.ui

RESOURCES += \
    SingIn.qrc
