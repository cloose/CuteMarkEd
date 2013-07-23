#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T11:40:15
#
#-------------------------------------------------

QT       += core gui webkitwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cutemarked
TEMPLATE = app

TRANSLATIONS += \
    translations/cutemarked_cs.ts \
    translations/cutemarked_de.ts

RC_FILE = cutemarked.rc

INCLUDEPATH += $$PWD

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    markdowneditor.cpp \
    controls/linenumberarea.cpp \
    controls/activelabel.cpp \
    controls/findreplacewidget.cpp \
    controls/recentfilesmenu.cpp \
    discount/parser.cpp \
    discount/document.cpp \
    htmlpreviewgenerator.cpp \
    markdownhighlighter.cpp \
    highlightworkerthread.cpp \
    peg-markdown-highlight/styleparser.cpp \
    markdownmanipulator.cpp \
    exportpdfdialog.cpp \
    exporthtmldialog.cpp \
    htmlhighlighter.cpp \
    optionsdialog.cpp \
    options.cpp \
    hunspell/spellchecker.cpp \
    hunspell/dictionary.cpp

HEADERS  += \
    mainwindow.h \
    markdowneditor.h \
    controls/linenumberarea.h \
    controls/activelabel.h \
    controls/findreplacewidget.h \
    controls/recentfilesmenu.h \
    discount/parser.h \
    discount/document.h \
    htmlpreviewgenerator.h \
    markdownhighlighter.h \
    highlightworkerthread.h \
    peg-markdown-highlight/styleparser.h \
    peg-markdown-highlight/definitions.h \
    markdownmanipulator.h \
    exportpdfdialog.h \
    exporthtmldialog.h \
    htmlhighlighter.h \
    optionsdialog.h \
    options.h \
    hunspell/spellchecker.h \
    hunspell/dictionary.h

FORMS    += \
    mainwindow.ui \
    controls/findreplacewidget.ui \
    exportpdfdialog.ui \
    exporthtmldialog.ui \
    optionsdialog.ui

RESOURCES += \
    resources.qrc \
    translations.qrc

# translations
lrelease.input         = TRANSLATIONS
lrelease.output        = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
lrelease.CONFIG       += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease

# discount
win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../discount/release/ -ldiscount
else:win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../discount/debug/ -ldiscount
else:win32-msvc*:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../discount/release/ -llibdiscount
else:win32-msvc*:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../discount/debug/ -llibdiscount
else:unix: LIBS += -L/usr/lib -lmarkdown

win32:INCLUDEPATH += $$PWD/../discount
unix:INCLUDEPATH += /usr/include
win32:DEPENDPATH += $$PWD/../discount

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/release/libdiscount.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/debug/libdiscount.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/release/libdiscount.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/debug/libdiscount.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../discount/libdiscount.a

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
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../hunspell/lib/ -lhunspell
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../hunspell/lib/ -lhunspell
else:unix: LIBS += -lhunspell

INCLUDEPATH += $$PWD/../hunspell/src
DEPENDPATH += $$PWD/../hunspell/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../hunspell/lib/libhunspell.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../hunspell/lib/libhunspell.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../hunspell/lib/libhunspell.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../hunspell/lib/libhunspell.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../hunspell/libhunspell.a

OTHER_FILES += \
    template.html \
    cutemarked.desktop \
    syntax.html \
    cutemarked.rc \
    syntax_de.html

message("Using INCLUDEPATH=$$INCLUDEPATH")
message("Using LIBS=$$LIBS")

## INSTALLATION

unix {
   # install desktop file
   desktop.path = /usr/share/applications
   desktop.files += cutemarked.desktop

   # install application
   target.path = $$[QT_INSTALL_BINS]
   INSTALLS += target desktop
   message("The project will be installed in $$[QT_INSTALL_BINS]")
}
