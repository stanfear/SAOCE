#-------------------------------------------------
#
# Project created by QtCreator 2014-03-19T17:57:03
#
#-------------------------------------------------

QT       += core gui positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SAOCE
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    association.cpp \
    participant.cpp \
    disponibility.cpp \
    participantslist.cpp \
    associationlist.cpp \
    associationmotor.cpp \
    dialogcreateparticipant.cpp \
    treeitemparticipant.cpp

HEADERS  += mainwindow.h \
    association.h \
    participant.h \
    disponibility.h \
    participantslist.h \
    associationlist.h \
    associationmotor.h \
    dialogcreateparticipant.h \
    treeitemparticipant.h

FORMS    += mainwindow.ui \
    dialogcreateparticipant.ui
