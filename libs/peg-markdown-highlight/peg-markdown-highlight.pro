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

INCLUDEPATH += $$PWD/../../3rdparty/peg-markdown-highlight
