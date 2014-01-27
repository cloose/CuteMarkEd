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

##################################################
# Use internal static library: app-static
##################################################
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../app-static/release/ -lapp-static
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../app-static/debug/ -lapp-static
else:unix: LIBS += -L$$OUT_PWD/../../app-static/ -lapp-static

INCLUDEPATH += $$PWD/../../app-static
DEPENDPATH += $$PWD/../../app-static

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../app-static/release/libapp-static.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../app-static/debug/libapp-static.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../app-static/libapp-static.a
