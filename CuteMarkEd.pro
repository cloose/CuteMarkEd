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
        textbuffer.cpp \
    markdowneditor.cpp

HEADERS  += mainwindow.h \
            markdownparser.h \
            textbuffer.h \
    markdowneditor.h

FORMS    += mainwindow.ui

include(sundown/sundown.pri)

RESOURCES += \
    styles.qrc

OTHER_FILES += \
    github.css \
    GitHub2.css \
    Clearness.css \
    Clearness Dark.css \
    Clearness_Dark.css
