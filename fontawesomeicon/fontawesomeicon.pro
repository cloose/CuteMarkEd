#-------------------------------------------------
#
# Project created by QtCreator 2013-05-06T20:13:32
#
#-------------------------------------------------

QT       += core gui

TARGET = fontawesomeicon
TEMPLATE = lib
CONFIG += plugin

debug:DESTDIR = $$OUT_PWD/../app/debug/iconengines
release:DESTDIR = $$OUT_PWD/../app/release/iconengines

SOURCES += fontawesomeiconengineplugin.cpp \
    fontawesomeiconengine.cpp

HEADERS += fontawesomeiconengineplugin.h \
    fontawesomeiconengine.h
OTHER_FILES += fontawesomeicon.json \
    fontawesome.ttf

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES += \
    fontawesomeicon.qrc
