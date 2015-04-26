#
# PEG Markdown Highlight Adapter Static Libary Project for CuteMarkEd
#
# Github : https://github.com/cloose/CuteMarkEd
#

QT += core gui widgets

TARGET = pmh-adapter
TEMPLATE = lib
CONFIG += staticlib 
CONFIG += c++11

SOURCES += \
    pmhmarkdownparser.cpp \
    styleparser.cpp 

HEADERS  += \
    pmhmarkdownparser.h \
    styleparser.h \
    definitions.h 

###################################################################################################
## DEPENDENCIES
###################################################################################################

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

