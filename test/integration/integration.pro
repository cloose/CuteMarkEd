#
# Integration Test Project for CuteMarkEd
#
# Github : https://github.com/cloose/CuteMarkEd
#

QT       += testlib
QT       -= gui

TARGET = integrationtest
CONFIG += console testcase

SOURCES += \
    discountmarkdownconvertertest.cpp \
    jsonsnippetfiletest.cpp \
    main.cpp

HEADERS += \
    discountmarkdownconvertertest.h \
    jsonsnippetfiletest.h

target.CONFIG += no_default_install

##################################################
# Use internal static library: app-static
##################################################

LIBS += -L$$PWD/../../libs

include(../../app-static.pri)

include(../../3rdparty/discount.pri)
include(../../3rdparty/hunspell.pri)

with_hoedown {
    include(../../3rdparty/hoedown.pri)
}
