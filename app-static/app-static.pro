#
# Application Static Libary Project for CuteMarkEd
#
# Github : https://github.com/cloose/CuteMarkEd
#

QT += gui network

TARGET = app-static
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    snippets/jsonsnippettranslator.cpp \
    snippets/snippetcollection.cpp \
    snippets/jsonsnippetfile.cpp \
    snippets/snippetlistmodel.cpp \
    converter/discountmarkdownconverter.cpp \
    converter/hoedownmarkdownconverter.cpp \
    spellchecker/dictionary.cpp \
    converter/textpreprocessor.cpp \
    converter/markdownconverter.cpp \
    converter/htmlpostprocessor.cpp \
    converter/embeddedmediapreprocessor.cpp \
    converter/embeddedmediapostprocessor.cpp

HEADERS += \
    snippets/snippet.h \
    snippets/jsonsnippettranslator.h \
    snippets/snippetcollection.h \
    snippets/jsonsnippetfile.h \
    snippets/snippetlistmodel.h \
    converter/markdownconverter.h \
    converter/markdowndocument.h \
    converter/discountmarkdownconverter.h \
    converter/hoedownmarkdownconverter.h \
    spellchecker/dictionary.h \
    converter/textpreprocessor.h \
    converter/htmlpostprocessor.h \
    converter/embeddedmediapreprocessor.h \
    converter/embeddedmediapostprocessor.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

##################################################
# Dependencies
##################################################

#
# Discount library
#
win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/release/ -ldiscount
else:win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/debug/ -ldiscount
else:win32-msvc*:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/release/ -llibdiscount
else:win32-msvc*:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/debug/ -llibdiscount
else:unix: LIBS += -L/usr/lib -lmarkdown

INCLUDEPATH += $$PWD/../3rdparty/
DEPENDPATH += $$PWD/../3rdparty/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/discount/release/libdiscount.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/discount/debug/libdiscount.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/discount/release/libdiscount.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/discount/debug/libdiscount.lib

#
# Hoedown library
#
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hoedown/release/ -lhoedown
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hoedown/debug/ -lhoedown
else:unix: LIBS += -L$$OUT_PWD/../3rdparty/hoedown/ -lhoedown

INCLUDEPATH += $$PWD/../3rdparty/hoedown
DEPENDPATH += $$PWD/../3rdparty/hoedown

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/hoedown/release/libhoedown.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/hoedown/debug/libhoedown.a
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/hoedown/libhoedown.a

#
# qoembed library
#
unix|win32: LIBS += -L$$PWD/../3rdparty/qoembed/build/src/ -llibqoembed

INCLUDEPATH += $$PWD/../3rdparty/qoembed/src
DEPENDPATH += $$PWD/../3rdparty/qoembed/src
