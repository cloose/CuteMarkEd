#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T11:40:15
#
#-------------------------------------------------

QT       += core gui webkitwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32: QT += winextras

TARGET = cutemarked
TEMPLATE = app

unix {
  CONFIG += link_pkgconfig
}

TRANSLATIONS += \
    translations/cutemarked_cs.ts \
    translations/cutemarked_de.ts \
    translations/cutemarked_el.ts \
    translations/cutemarked_es.ts \
    translations/cutemarked_fr.ts \
    translations/cutemarked_ja.ts \
    translations/cutemarked_pt_BR.ts \
    translations/cutemarked_ru.ts \
    translations/cutemarked_zh_CN.ts

RC_FILE = cutemarked.rc

INCLUDEPATH += $$PWD

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    markdowneditor.cpp \
    controls/linenumberarea.cpp \
    controls/activelabel.cpp \
    controls/fileexplorerwidget.cpp \
    controls/findreplacewidget.cpp \
    controls/recentfilesmenu.cpp \
    htmlpreviewgenerator.cpp \
    markdownhighlighter.cpp \
    highlightworkerthread.cpp \
    peg-markdown-highlight/styleparser.cpp \
    markdownmanipulator.cpp \
    exportpdfdialog.cpp \
    exporthtmldialog.cpp \
    htmlhighlighter.cpp \
    options.cpp \
    optionsdialog.cpp \
    hunspell/spellchecker.cpp \
    controls/languagemenu.cpp \
    tabletooldialog.cpp \
    imagetooldialog.cpp \
    snippetcompleter.cpp \
    aboutdialog.cpp

win32 {
    SOURCES += \
        hunspell/spellchecker_win.cpp
}

unix {
    SOURCES += \
        hunspell/spellchecker_unix.cpp
}

HEADERS  += \
    mainwindow.h \
    markdowneditor.h \
    controls/linenumberarea.h \
    controls/activelabel.h \
    controls/fileexplorerwidget.h \
    controls/findreplacewidget.h \
    controls/recentfilesmenu.h \
    htmlpreviewgenerator.h \
    markdownhighlighter.h \
    highlightworkerthread.h \
    peg-markdown-highlight/styleparser.h \
    peg-markdown-highlight/definitions.h \
    markdownmanipulator.h \
    exportpdfdialog.h \
    exporthtmldialog.h \
    htmlhighlighter.h \
    options.h \
    optionsdialog.h \
    hunspell/spellchecker.h \
    controls/languagemenu.h \
    tabletooldialog.h \
    imagetooldialog.h \
    snippetcompleter.h \
    aboutdialog.h

FORMS    += \
    mainwindow.ui \
    controls/fileexplorerwidget.ui \
    controls/findreplacewidget.ui \
    exportpdfdialog.ui \
    exporthtmldialog.ui \
    optionsdialog.ui \
    tabletooldialog.ui \
    imagetooldialog.ui \
    aboutdialog.ui

RESOURCES += \
    resources.qrc \
    translations.qrc

OTHER_FILES += \
    template.html \
    template_presentation.html \
    cutemarked.desktop \
    syntax.html \
    cutemarked.rc \
    syntax_cs.html \
    syntax_de.html \
    syntax_el.html \
    syntax_ja.html \
    syntax_zh_CN.html \
    styles/solarized-dark.css \
    styles/markdown.css \
    styles/github.css \
    styles/clearness-dark.css \
    styles/clearness.css \
    styles/byword-dark.css \
    styles/solarized-light.css \
    markdown-snippets.json

# translations
lrelease.input         = TRANSLATIONS
lrelease.output        = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
lrelease.CONFIG       += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease

###################################################################################################
## DEPENDENCIES
###################################################################################################

# Use internal static library: app-static
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../app-static/release/ -lapp-static
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../app-static/debug/ -lapp-static
else:unix: LIBS += -L$$OUT_PWD/../app-static/ -lapp-static

INCLUDEPATH += $$PWD/../app-static
DEPENDPATH += $$PWD/../app-static

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../app-static/release/libapp-static.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../app-static/debug/libapp-static.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../app-static/libapp-static.a

# discount
win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/release/ -ldiscount
else:win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/debug/ -ldiscount
else:win32-msvc*:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/release/ -llibdiscount
else:win32-msvc*:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/debug/ -llibdiscount
else:unix: LIBS += -L/usr/lib -lmarkdown

win32:INCLUDEPATH += $$PWD/../3rdparty/discount
unix:INCLUDEPATH += /usr/include
win32:DEPENDPATH += $$PWD/../3rdparty/discount

# peg-markdown-highlight
win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../peg-markdown-highlight/release/ -lpmh
else:win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../peg-markdown-highlight/debug/ -lpmh
else:win32-msvc*:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../peg-markdown-highlight/release/ -llibpmh
else:win32-msvc*:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../peg-markdown-highlight/debug/ -llibpmh
else:unix: LIBS += -L$$OUT_PWD/../peg-markdown-highlight/ -lpmh

INCLUDEPATH += $$PWD/../peg-markdown-highlight
DEPENDPATH += $$PWD/../peg-markdown-highlight

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/release/libpmh.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/debug/libpmh.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/release/libpmh.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/debug/libpmh.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/libpmh.a

# hunspell
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hunspell/lib/ -lhunspell
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hunspell/lib/ -lhunspell

unix {
  PKGCONFIG += hunspell
}

win32:INCLUDEPATH += $$PWD/../3rdparty/hunspell/src
win32:DEPENDPATH += $$PWD/../3rdparty/hunspell/src

# hoedown
with_hoedown {
    message("app: Enable hoedown markdown converter support")
    DEFINES += ENABLE_HOEDOWN

    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hoedown/release/ -lhoedown
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hoedown/debug/ -lhoedown
    else:unix: LIBS += -L/usr/lib -lhoedown

    win32 {
        INCLUDEPATH += $$PWD/../3rdparty/hoedown
        DEPENDPATH += $$PWD/../3rdparty/hoedown
    }

    unix {
        INCLUDEPATH += /usr/include
    }
}

message("Using INCLUDEPATH=$$INCLUDEPATH")
message("Using LIBS=$$LIBS")

## INSTALLATION

unix {
   isEmpty(PREFIX): PREFIX = /usr

   # install desktop file
   desktop.path = $${PREFIX}/share/applications
   desktop.files += cutemarked.desktop

   # install application
   target.path = $${PREFIX}/bin

   INSTALLS += target desktop
   message("The project will be installed in prefix $${PREFIX}")
}
