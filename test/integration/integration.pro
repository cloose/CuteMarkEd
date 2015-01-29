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
    main.cpp \
    pmhmarkdownparsertest.cpp \
    revealmarkdownconvertertest.cpp

HEADERS += \
    discountmarkdownconvertertest.h \
    jsonsnippetfiletest.h \
    pmhmarkdownparsertest.h \
    revealmarkdownconvertertest.h

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

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../app-static/release/libapp-static.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../app-static/debug/libapp-static.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../app-static/libapp-static.a

#
# PEG Markdown Highlight adapter library
#
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/peg-markdown-highlight/release/ -lpmh-adapter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/peg-markdown-highlight/debug/ -lpmh-adapter
else:unix: LIBS += -L$$OUT_PWD/../../libs/peg-markdown-highlight/ -lpmh-adapter

INCLUDEPATH += $$PWD/../../libs/peg-markdown-highlight
DEPENDPATH += $$PWD/../../libs/peg-markdown-highlight

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/peg-markdown-highlight/release/libpmh-adapter.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/peg-markdown-highlight/debug/libpmh-adapter.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libs/peg-markdown-highlight/libpmh-adapter.a

#
# peg-markdown-highlight
#
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/peg-markdown-highlight/release/ -lpmh
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/peg-markdown-highlight/debug/ -lpmh
else:unix: LIBS += -L$$OUT_PWD/../../3rdparty/peg-markdown-highlight/ -lpmh

INCLUDEPATH += $$PWD/../../3rdparty/peg-markdown-highlight
DEPENDPATH += $$PWD/../../3rdparty/peg-markdown-highlight

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/peg-markdown-highlight/release/libpmh.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/peg-markdown-highlight/debug/libpmh.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/peg-markdown-highlight/libpmh.a

#
# Discount library
#
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/discount/release/ -ldiscount
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../3rdparty/discount/debug/ -ldiscount
else:unix: LIBS += -L$$OUT_PWD/../../3rdparty/discount/ -lmarkdown

INCLUDEPATH += $$PWD/../../3rdparty/
DEPENDPATH += $$PWD/../../3rdparty/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/discount/release/libdiscount.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/discount/debug/libdiscount.a

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

    win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/hoedown/release/libhoedown.a
    else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../3rdparty/hoedown/debug/libhoedown.a
}
