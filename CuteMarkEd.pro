#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T11:40:15
#
#-------------------------------------------------

TEMPLATE = subdirs

CONFIG += c++11

SUBDIRS = \
    3rdparty \
    libs \
    app-static \
    app \
    fontawesomeicon \
    test

app.depends = libs app-static
libs.depends = 3rdparty
test.depends = libs app-static
