#
# Application Static Libary Project for CuteMarkEd
#
# Github : https://github.com/cloose/CuteMarkEd
#

QT += gui webkitwidgets

TARGET = app-static
TEMPLATE = lib
CONFIG += staticlib 
CONFIG += c++11

SOURCES += \
    snippets/jsonsnippettranslator.cpp \
    snippets/snippetcollection.cpp \
    converter/discountmarkdownconverter.cpp \
    spellchecker/dictionary.cpp \
    converter/revealmarkdownconverter.cpp \
    template/htmltemplate.cpp \
    template/presentationtemplate.cpp \
    completionlistmodel.cpp \
    datalocation.cpp \
    slidelinemapping.cpp \
    viewsynchronizer.cpp \
    revealviewsynchronizer.cpp \
    htmlviewsynchronizer.cpp \
    yamlheaderchecker.cpp

HEADERS += \
    snippets/snippet.h \
    snippets/jsonsnippettranslator.h \
    snippets/jsonsnippettranslatorfactory.h \
    snippets/snippetcollection.h \
    converter/markdownconverter.h \
    converter/markdowndocument.h \
    converter/discountmarkdownconverter.h \
    spellchecker/dictionary.h \
    converter/revealmarkdownconverter.h \
    template/template.h \
    template/htmltemplate.h \
    template/presentationtemplate.h \
    completionlistmodel.h \
    datalocation.h \
    slidelinemapping.h \
    viewsynchronizer.h \
    revealviewsynchronizer.h \
    htmlviewsynchronizer.h \
    yamlheaderchecker.h

#unix:!symbian {
#    maemo5 {
#        target.path = /opt/usr/lib
#    } else {
#        target.path = /usr/lib
#    }
#    INSTALLS += target
#}

##################################################
# Dependencies
##################################################

#
# Add search paths below /usr/local for Mac OSX
#
macx {
  LIBS += -L/usr/local/lib
  INCLUDEPATH += /usr/local/include
}

#
# JSON configuration library
#
INCLUDEPATH += $$PWD/../libs/jsonconfig

#
# Discount library
#
win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/release/ -ldiscount
else:win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/debug/ -ldiscount
else:win32-msvc*:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/release/ -llibdiscount
else:win32-msvc*:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/debug/ -llibdiscount
else:unix: LIBS += -L/usr/lib -lmarkdown

win32:INCLUDEPATH += $$PWD/../3rdparty/discount
unix:INCLUDEPATH += /usr/include
win32:DEPENDPATH += $$PWD/../3rdparty/discount

#
# Hoedown library
#
with_hoedown {
    message("app-static: Enable hoedown markdown converter support")

    DEFINES += ENABLE_HOEDOWN
    SOURCES += converter/hoedownmarkdownconverter.cpp
    HEADERS += converter/hoedownmarkdownconverter.h

    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hoedown/release/ -lhoedown
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hoedown/debug/ -lhoedown
    else:unix: LIBS += -L/usr/lib -lhoedown

    win32 {
        INCLUDEPATH += $$PWD/../3rdparty/hoedown
        DEPENDPATH += $$PWD/../3rdparty/hoedown
    }

    unix {
        INCLUDEPATH += /usr/include
    }
}
