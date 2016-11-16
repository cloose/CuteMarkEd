#
# Unit Test Project for CuteMarkEd
#
# Github : https://github.com/cloose/CuteMarkEd
#

QT += testlib

TARGET = unittest
CONFIG += console testcase
CONFIG += c++11

SOURCES += \
    main.cpp \
    completionlistmodeltest.cpp \
    snippettest.cpp \
    jsonsnippettranslatortest.cpp \
    jsonthemetranslatortest.cpp \
    jsontranslatorfactorytest.cpp \
    slidelinemappingtest.cpp \
    snippetcollectiontest.cpp \
    dictionarytest.cpp \
    yamlheadercheckertest.cpp \
    themetest.cpp \
    themecollectiontest.cpp \
    stylemanagertest.cpp

HEADERS += \
    completionlistmodeltest.h \
    snippettest.h \
    jsonsnippettranslatortest.h \
    jsonthemetranslatortest.h \
    jsontranslatorfactorytest.h \
    slidelinemappingtest.h \
    snippetcollectiontest.h \
    dictionarytest.h \
    yamlheadercheckertest.h \
    themetest.h \
    themecollectiontest.h \
    stylemanagertest.h

target.CONFIG += no_default_install

#
# JSON configuration library
#
INCLUDEPATH += $$PWD/../../libs/jsonconfig

##################################################
# Use internal static library: app-static
##################################################
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../app-static/release/ -lapp-static
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../app-static/debug/ -lapp-static
else:unix: LIBS += -L$$OUT_PWD/../../app-static/ -lapp-static

INCLUDEPATH += $$PWD/../../app-static
DEPENDPATH += $$PWD/../../app-static

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../app-static/release/libapp-static.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../app-static/debug/libapp-static.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../app-static/release/app-static.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../app-static/debug/app-static.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../app-static/libapp-static.a
