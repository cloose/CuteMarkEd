#
# hunspell
#
win32 {
    INCLUDEPATH += $$PWD/../3rdparty/hunspell/src
    DEPENDPATH += $$PWD/../3rdparty/hunspell/src
    LIBS += -L$$PWD/../libs
}
unix {
    PKGCONFIG += hunspell
}
LIBS += -lhunspell

