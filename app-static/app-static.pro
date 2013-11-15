#
# Application Static Libary Project for CuteMarkEd
#
# Github : https://github.com/cloose/CuteMarkEd
#

QT       -= gui

TARGET = app-static
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    snippets/jsonsnippettranslator.cpp \
    snippets/snippetcollection.cpp

HEADERS += \
    snippets/snippet.h \
    snippets/jsonsnippettranslator.h \
    snippets/snippetcollection.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
