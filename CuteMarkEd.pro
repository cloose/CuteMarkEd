#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T11:40:15
#
#-------------------------------------------------

TEMPLATE = subdirs

CONFIG += c++11 ordered

SUBDIRS = \
    3rdparty \
    libs \
    app-static \
    app \
    fontawesomeicon \
    test

app.depends = 3rdparty libs app-static
