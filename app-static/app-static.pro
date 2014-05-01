#
# Application Static Libary Project for CuteMarkEd
#
# Github : https://github.com/cloose/CuteMarkEd
#

QT     += gui
CONFIG += staticlib

TARGET = app-static
TEMPLATE = lib
DESTDIR = $$PWD/../libs

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../3rdparty/hunspell/src
INCLUDEPATH += $$PWD/../3rdparty/discount

SOURCES += \
    snippets/jsonsnippettranslator.cpp \
    snippets/snippetcollection.cpp \
    snippets/jsonsnippetfile.cpp \
    snippets/snippetlistmodel.cpp \
    converter/discountmarkdownconverter.cpp \
    spellchecker/dictionary.cpp

HEADERS += \
    snippets/snippet.h \
    snippets/jsonsnippettranslator.h \
    snippets/snippetcollection.h \
    snippets/jsonsnippetfile.h \
    snippets/snippetlistmodel.h \
    converter/markdownconverter.h \
    converter/markdowndocument.h \
    converter/discountmarkdownconverter.h \
    spellchecker/dictionary.h

#unix:!symbian {
#    maemo5 {
#        target.path = /opt/usr/lib
#    } else {
#        target.path = /usr/lib
#    }
#    INSTALLS += target
#}

