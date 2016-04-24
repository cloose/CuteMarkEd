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
CONFIG += c++11

unix:!macx {
  CONFIG += link_pkgconfig
}

TRANSLATIONS += \
    translations/cutemarked_cs.ts \
    translations/cutemarked_da.ts \
    translations/cutemarked_de.ts \
    translations/cutemarked_el.ts \
    translations/cutemarked_es.ts \
    translations/cutemarked_fr.ts \
    translations/cutemarked_hu_HU.ts \
    translations/cutemarked_id.ts \
    translations/cutemarked_ja.ts \
    translations/cutemarked_pl.ts \
    translations/cutemarked_pt_BR.ts \
    translations/cutemarked_ru.ts \
    translations/cutemarked_zh_CN.ts

win32:RC_FILE = cutemarked.rc
macx {
    ICON = app-icon.icns
    QMAKE_INFO_PLIST = Info.plist
}

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
    snippetstablemodel.cpp \
    aboutdialog.cpp \
    statusbarwidget.cpp

win32 {
    SOURCES += \
        hunspell/spellchecker_win.cpp
}

macx {
    SOURCES += \
        hunspell/spellchecker_macx.cpp
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
    snippetstablemodel.h \
    aboutdialog.h \
    statusbarwidget.h \
    savefileadapter.h

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
    syntax_da.html \
    syntax_de.html \
    syntax_el.html \
    syntax_es.html \
    syntax_hu_HU.html \
    syntax_id.html \
    syntax_ja.html \
    syntax_pt_BR.html \
    syntax_zh_CN.html \
    styles/solarized-dark.css \
    styles/markdown.css \
    styles/github.css \
    styles/clearness-dark.css \
    styles/clearness.css \
    styles/byword-dark.css \
    styles/solarized-light.css \
    markdown-snippets.json \
    builtin-htmlpreview-themes.json

# translations
lrelease.input         = TRANSLATIONS
lrelease.output        = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
lrelease.CONFIG       += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease

###################################################################################################
## DEPENDENCIES
###################################################################################################

#
# Add search paths below /usr/local for Mac OSX
#
macx {
  LIBS += -L/usr/local/lib
  INCLUDEPATH += /usr/local/include
}

#
# JSON configuration library
#
INCLUDEPATH += $$PWD/../libs/jsonconfig

# Use internal static library: app-static
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../app-static/release/ -lapp-static
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../app-static/debug/ -lapp-static
else:unix: LIBS += -L$$OUT_PWD/../app-static/ -lapp-static

INCLUDEPATH += $$PWD/../app-static
DEPENDPATH += $$PWD/../app-static

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../app-static/release/libapp-static.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../app-static/debug/libapp-static.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../app-static/release/app-static.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../app-static/debug/app-static.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../app-static/libapp-static.a

# discount
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/release/ -ldiscount
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/debug/ -ldiscount
else:unix: LIBS += -L/usr/lib -lmarkdown

win32:INCLUDEPATH += $$PWD/../3rdparty/discount
win32:DEPENDPATH += $$PWD/../3rdparty/discount

# peg-markdown-highlight adapter
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/peg-markdown-highlight/release/ -lpmh-adapter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/peg-markdown-highlight/debug/ -lpmh-adapter
else:unix: LIBS += -L$$OUT_PWD/../libs/peg-markdown-highlight/ -lpmh-adapter

INCLUDEPATH += $$PWD/../libs/
DEPENDPATH += $$PWD/../libs/peg-markdown-highlight

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/peg-markdown-highlight/release/libpmh-adapter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/peg-markdown-highlight/debug/libpmh-adapter.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/peg-markdown-highlight/release/pmh-adapter.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/peg-markdown-highlight/debug/pmh-adapter.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libs/peg-markdown-highlight/libpmh-adapter.a

# peg-markdown-highlight
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/peg-markdown-highlight/release/ -lpmh
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/peg-markdown-highlight/debug/ -lpmh
else:unix: LIBS += -L$$OUT_PWD/../3rdparty/peg-markdown-highlight/ -lpmh

INCLUDEPATH += $$PWD/../3rdparty/peg-markdown-highlight
DEPENDPATH += $$PWD/../3rdparty/peg-markdown-highlight

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/peg-markdown-highlight/release/libpmh.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/peg-markdown-highlight/debug/libpmh.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/peg-markdown-highlight/release/pmh.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/peg-markdown-highlight/debug/pmh.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../3rdparty/peg-markdown-highlight/libpmh.a

# hunspell
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hunspell/lib/ -lhunspell
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hunspell/lib/ -lhunspell

unix:!macx {
  PKGCONFIG += hunspell
}

macx {
  LIBS += -lhunspell
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
}

message("Using INCLUDEPATH=$$INCLUDEPATH")
message("Using LIBS=$$LIBS")

## INSTALLATION

unix:!macx {
   isEmpty(PREFIX): PREFIX = /usr
   DATADIR = $${PREFIX}/share

   # install desktop file
   desktop.path = $${DATADIR}/applications
   desktop.files += cutemarked.desktop

   # install icons
   icon16.path = $${DATADIR}/icons/hicolor/16x16/apps
   icon16.files = icons/16x16/cutemarked.png

   icon32.path = $${DATADIR}/icons/hicolor/32x32/apps
   icon32.files = icons/32x32/cutemarked.png

   icon48.path = $${DATADIR}/icons/hicolor/48x48/apps
   icon48.files = icons/48x48/cutemarked.png

   icon64.path = $${DATADIR}/icons/hicolor/64x64/apps
   icon64.files = icons/64x64/cutemarked.png

   icon128.path = $${DATADIR}/icons/hicolor/128x128/apps
   icon128.files = icons/128x128/cutemarked.png

   iconsvg.path = $${DATADIR}/icons/hicolor/scalable/apps
   iconsvg.files = icons/scalable/cutemarked.svg

   # install application
   target.path = $${PREFIX}/bin

   INSTALLS += target desktop icon16 icon32 icon48 icon64 icon128 iconsvg
   message("The project will be installed in prefix $${PREFIX}")
}
