QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HandTalk
TEMPLATE = app

HEADERS += \
    src/parser/gamerecord.h \
    src/parser/sgfparser.h \
    src/board.h \
    src/mainwindow.h \
    src/gametreemodel.h

SOURCES += \
    src/parser/sgfparser.cpp \
    src/board.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/gametreemodel.cpp \
    src/parser/gamerecord.cpp

FORMS += \
    src/mainwindow.ui

RESOURCES += \
    resources.qrc
