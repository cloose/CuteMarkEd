#
# Integration Test Project for CuteMarkEd
#
# Github : https://github.com/cloose/CuteMarkEd
#

QT       += testlib
QT       += gui webkitwidgets

TARGET = integrationtest
CONFIG += console testcase
CONFIG += c++11

SOURCES += \
    discountmarkdownconvertertest.cpp \
    htmlpreviewcontrollertest.cpp \
    htmltemplatetest.cpp \
    jsonsnippetfiletest.cpp \
    jsonthemefiletest.cpp \
    main.cpp \
    pmhmarkdownparsertest.cpp \
    revealmarkdownconvertertest.cpp \
    themecollectiontest.cpp

HEADERS += \
    discountmarkdownconvertertest.h \
    htmlpreviewcontrollertest.h \
    htmltemplatetest.h \
    jsonsnippetfiletest.h \
    jsonthemefiletest.h \
    pmhmarkdownparsertest.h \
    revealmarkdownconvertertest.h \
    themecollectiontest.h

target.CONFIG += no_default_install

#
# JSON configuration library
#
INCLUDEPATH += $$PWD/../../libs/jsonconfig

#
# Add search paths below /usr/local for Mac OSX
#
macx {
  LIBS += -L/usr/local/lib
  INCLUDEPATH += /usr/local/include
}

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

#
# PEG Markdown Highlight adapter library
#
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/peg-markdown-highlight/release/ -lpmh-adapter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/peg-markdown-highlight/debug/ -lpmh-adapter
else:unix: LIBS += -L$$OUT_PWD/../../libs/peg-markdown-highlight/ -lpmh-adapter

INCLUDEPATH += $$PWD/../../libs/peg-markdown-highlight
DEPENDPATH += $$PWD/../../libs/peg-markdown-highlight

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/peg-markdown-highlight/release/libpmh-adapter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/peg-markdown-highlight/debug/libpmh-adapter.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/peg-markdown-highlight/release/pmh-adapter.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/peg-markdown-highlight/debug/pmh-adapter.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libs/peg-markdown-highlight/libpmh-adapter.a

#
# peg-markdown-highlight
#
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/peg-markdown-highlight/release/ -lpmh
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/peg-markdown-highlight/debug/ -lpmh
else:unix: LIBS += -L$$OUT_PWD/../../3rdparty/peg-markdown-highlight/ -lpmh

INCLUDEPATH += $$PWD/../../3rdparty/peg-markdown-highlight
DEPENDPATH += $$PWD/../../3rdparty/peg-markdown-highlight

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/peg-markdown-highlight/release/libpmh.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/peg-markdown-highlight/debug/libpmh.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/peg-markdown-highlight/release/pmh.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/peg-markdown-highlight/debug/pmh.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/peg-markdown-highlight/libpmh.a

#
# Discount library
#
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/discount/release/ -ldiscount
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/discount/debug/ -ldiscount
else:unix: LIBS += -L$$OUT_PWD/../../3rdparty/discount/ -lmarkdown

INCLUDEPATH += $$PWD/../../3rdparty/
DEPENDPATH += $$PWD/../../3rdparty/

#win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/discount/release/libdiscount.a
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/discount/debug/libdiscount.a

#
# hoedown
#
with_hoedown {
    DEFINES += ENABLE_HOEDOWN
    SOURCES += hoedownmarkdownconvertertest.cpp
    HEADERS += hoedownmarkdownconvertertest.h

    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/hoedown/release/ -lhoedown
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/hoedown/debug/ -lhoedown
    else:unix: LIBS += -L$$OUT_PWD/../../3rdparty/hoedown/ -lhoedown

    INCLUDEPATH += $$PWD/../../3rdparty/hoedown
    DEPENDPATH += $$PWD/../../3rdparty/hoedown

    #win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/hoedown/release/libhoedown.a
    #else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/hoedown/debug/libhoedown.a
}
