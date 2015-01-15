#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T11:40:15
#
#-------------------------------------------------

TEMPLATE = subdirs

CONFIG += c++11

win32 {
    SUBDIRS = 3rdparty \
        libs \
        app \
        fontawesomeicon

    app.depends = 3rdparty libs app-static
}

unix {
    SUBDIRS = libs \
        app \
        fontawesomeicon

    app.depends = libs app-static
}

SUBDIRS += \
    test \
    app-static

