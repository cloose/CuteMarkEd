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
    htmlpreviewgenerator.cpp

HEADERS  += mainwindow.h \
            markdowneditor.h \
            controls/linenumberarea.h \
            discount/parser.h \
    discount/document.h \
    htmlpreviewgenerator.h

FORMS    += mainwindow.ui

RESOURCES += \
    styles.qrc

OTHER_FILES += \
    github.css \
    GitHub2.css \
    Clearness.css \
    Clearness Dark.css \
    Clearness_Dark.css

win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../discount/release/ -llibdiscount
else:win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../discount/debug/ -llibdiscount
else:win32-msvc*:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../discount/release/ -llibdiscount
else:win32-msvc*:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../discount/debug/ -llibdiscount
else:unix: LIBS += -L$$OUT_PWD/../discount/ -llibdiscount

INCLUDEPATH += $$PWD/../discount
DEPENDPATH += $$PWD/../discount

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/release/libdiscount.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/debug/libdiscount.a
else:win32-msvc*:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/release/libdiscount.lib
else:win32-msvc*:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../discount/debug/libdiscount.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../discount/liblibdiscount.a
