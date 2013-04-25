#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T11:40:15
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CuteMarkEd
TEMPLATE = app

INCLUDEPATH += $$PWD
message($$INCLUDEPATH)

SOURCES += main.cpp\
        mainwindow.cpp \
        markdowneditor.cpp \
        controls/linenumberarea.cpp \
        discount/parser.cpp \
    discount/document.cpp \
    htmlpreviewgenerator.cpp \
    controls/activelabel.cpp \
    markdownhighlighter.cpp \
    highlightworkerthread.cpp \
    peg-markdown-highlight/styleparser.cpp

HEADERS  += mainwindow.h \
            markdowneditor.h \
            controls/linenumberarea.h \
            discount/parser.h \
    discount/document.h \
    htmlpreviewgenerator.h \
    controls/activelabel.h \
    markdownhighlighter.h \
    highlightworkerthread.h \
    peg-markdown-highlight/styleparser.h \
    peg-markdown-highlight/definitions.h

FORMS    += mainwindow.ui

RESOURCES += \
    styles.qrc

OTHER_FILES += \
    github.css \
    GitHub2.css \
    Clearness.css \
    Clearness Dark.css \
    Clearness_Dark.css \
    solarized-dark.style

# discount
win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../discount/release/ -ldiscount
else:win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../discount/debug/ -ldiscount
else:win32-msvc*:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../discount/release/ -llibdiscount
else:win32-msvc*:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../discount/debug/ -llibdiscount
else:unix: LIBS += -L$$OUT_PWD/../discount/ -llibdiscount

INCLUDEPATH += $$PWD/../discount
DEPENDPATH += $$PWD/../discount

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/release/libdiscount.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/debug/libdiscount.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/release/libdiscount.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/debug/libdiscount.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../discount/libdiscount.a

# peg-markdown-highlight
win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../peg-markdown-highlight/release/ -lpmh
else:win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../peg-markdown-highlight/debug/ -lpmh
else:win32-msvc*:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../peg-markdown-highlight/release/ -llibpmh
else:win32-msvc*:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../peg-markdown-highlight/debug/ -llibpmh
else:unix: LIBS += -L$$OUT_PWD/../peg-markdown-highlight/ -llibpmh

INCLUDEPATH += $$PWD/../peg-markdown-highlight
DEPENDPATH += $$PWD/../peg-markdown-highlight

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/release/libpmh.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/debug/libpmh.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/release/libpmh.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/debug/libpmh.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../peg-markdown-highlight/libpmh.a
