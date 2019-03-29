#-------------------------------------------------
#
# Project created by QtCreator 2019-01-28T19:26:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quiz_for_genetic
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += app_bundle  # to remove, do CONFIG -= app_bundle

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    welcome.cpp \
    instruction.cpp \
    form.cpp \
    quiz.cpp \
    question.cpp \
    final.cpp

HEADERS += \
        mainwindow.h \
    welcome.h \
    instruction.h \
    form.h \
    quiz.h \
    question.h \
    answer.h \
    final.h

FORMS += \
        mainwindow.ui \
    welcome.ui \
    instruction.ui \
    form.ui \
    quiz.ui \
    final.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    quests.qrc \
    picts.qrc
