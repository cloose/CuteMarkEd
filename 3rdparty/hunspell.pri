#
# hunspell
#
win32 {
    INCLUDEPATH += $$PWD/../3rdparty/hunspell/src
    DEPENDPATH += $$PWD/../3rdparty/hunspell/src
    LIBS += -L$$OUT_PWD/../3rdparty/hunspell/lib/
#    CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hunspell/lib/
#    CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hunspell/lib/
}
unix {
    PKGCONFIG += hunspell
}
LIBS += -lhunspell

