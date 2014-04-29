#
# Unit Test Project for CuteMarkEd
#
# Github : https://github.com/cloose/CuteMarkEd
#

QT += testlib

TARGET = unittest
CONFIG += console testcase

SOURCES += \
    main.cpp \
    snippettest.cpp \
    jsonsnippettranslatortest.cpp \
    snippetcollectiontest.cpp \
    snippetlistmodeltest.cpp \
    dictionarytest.cpp

HEADERS += \
    snippettest.h \
    jsonsnippettranslatortest.h \
    snippetcollectiontest.h \
    snippetlistmodeltest.h \
    dictionarytest.h

target.CONFIG += no_default_install

INCLUDEPATH += $$PWD/../../app-static
DEPENDPATH += $$PWD/../../app-static
LIBS += -L$$PWD/../../libs

include(../../app-static.pri)

