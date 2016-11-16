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

INCLUDEPATH += $$PWD

SOURCES += \
    snippets/jsonsnippettranslator.cpp \
    snippets/snippetcollection.cpp \
    converter/discountmarkdownconverter.cpp \
    spellchecker/dictionary.cpp \
    converter/revealmarkdownconverter.cpp \
    template/htmltemplate.cpp \
    template/presentationtemplate.cpp \
    themes/jsonthemetranslator.cpp \
    themes/stylemanager.cpp \
    themes/theme.cpp \
    themes/themecollection.cpp \
    completionlistmodel.cpp \
    datalocation.cpp \
    slidelinemapping.cpp \
    viewsynchronizer.cpp \
    revealviewsynchronizer.cpp \
    htmlpreviewcontroller.cpp \
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
    themes/jsonthemetranslator.h \
    themes/jsonthemetranslatorfactory.h \
    themes/stylemanager.h \
    themes/theme.h \
    themes/themecollection.h \
    completionlistmodel.h \
    datalocation.h \
    slidelinemapping.h \
    viewsynchronizer.h \
    revealviewsynchronizer.h \
    htmlpreviewcontroller.h \
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
macx:INCLUDEPATH += /usr/local/include

#
# JSON configuration library
#
INCLUDEPATH += $$PWD/../libs/jsonconfig

#
# Discount library
#
win32:INCLUDEPATH += $$PWD/../3rdparty/discount

#
# Hoedown library
#
with_hoedown {
    message("app-static: Enable hoedown markdown converter support")

    DEFINES += ENABLE_HOEDOWN
    SOURCES += converter/hoedownmarkdownconverter.cpp
    HEADERS += converter/hoedownmarkdownconverter.h

    win32:INCLUDEPATH += $$PWD/../3rdparty/hoedown
}
