#-------------------------------------------------
#
# Project created by QtCreator 2017-03-21T16:14:30
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SignIn
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dialog.cpp \
    mytitlebar.cpp \
    personlist.cpp \
    personlistbuddy.cpp \
    contact.cpp \
    database.cpp

HEADERS  += widget.h \
    dialog.h \
    mytitlebar.h \
    personlist.h \
    personlistbuddy.h \
    contact.h \
    database.h

FORMS    += widget.ui \
    dialog.ui \
    contact.ui

RESOURCES += \
    SingIn.qrc
