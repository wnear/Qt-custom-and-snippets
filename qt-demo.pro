######################################################################
# Automatically generated by qmake (3.1) Mon Jun 13 11:54:54 2022
######################################################################

QT += widgets network

config += qt
CONFIG += debug_and_release

TEMPLATE = app
TARGET = qt-demo
INCLUDEPATH += .
VERSION = 23.01.04

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += \
        graphicspageview.h \
        listwidget.h \
        mainwindow.h \
        thread.h \
        viewdelegate.h \
        textbrowser.h \
        treewidget.h \
        treemodel.h \
        treeitem.h \
        dataitem.h \
        regex.h \
        youdao.h \
        struct.h \



SOURCES += \
        graphicspageview.cc \
        listwidget.cc \
        main.cc  \
        mainwindow.cc \
        thread.cc \
        viewdelegate.cc \
        textbrowser.cc \
        treewidget.cc \
        treemodel.cc \
        treeitem.cc \
        dataitem.cc \
        regex.cc \
        youdao.cc \
        struct.cc \

# NOTE: how to define the version in the project file and pass it to code.
# 1. define version in a variable of `.pro`.
# 2. use `DEFINES` to pass the variable to macro, which can be accessed from the code.

DEFINES += PROGRAM_VERSION=\\\"$$VERSION\\\"

# NOTE: conditional build.
CONFIG += contest
CONFIG(contest){
    DEFINES += PROGRAMX
}

