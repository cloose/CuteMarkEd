#-------------------------------------------------
#
# Project created by QtCreator 2013-04-24T19:50:18
#
#-------------------------------------------------

QT       -= core gui

TARGET = pmh
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    pmh_parser.cpp \
    pmh_styleparser.cpp

HEADERS += \
    pmh_styleparser.h \
    pmh_parser.h \
    pmh_definitions.h

#unix:!symbian {
#    maemo5 {
#        target.path = /opt/usr/lib
#    } else {
#        target.path = /usr/lib
#    }
#    INSTALLS += target
#}
