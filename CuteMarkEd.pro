#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T11:40:15
#
#-------------------------------------------------

TEMPLATE = subdirs

win32 {
    SUBDIRS = 3rdparty \
        peg-markdown-highlight \
        libs \
        app \
        fontawesomeicon

    app.depends = 3rdparty peg-markdown-highlight libs app-static
}

unix {
    SUBDIRS = peg-markdown-highlight \
        libs \
        app \
        fontawesomeicon

    app.depends = peg-markdown-highlight libs app-static
}

SUBDIRS += \
    test \
    app-static

