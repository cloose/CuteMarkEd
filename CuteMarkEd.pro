#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T11:40:15
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuteMarkEd
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        markdownparser.cpp \
        textbuffer.cpp

HEADERS  += mainwindow.h \
            markdownparser.h \
            textbuffer.h

FORMS    += mainwindow.ui

include(sundown/sundown.pri)

RESOURCES += \
    styles.qrc

OTHER_FILES += \
    github.css
