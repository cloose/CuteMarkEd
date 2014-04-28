#
# Discount library
#
win32 {
    INCLUDEPATH += $$PWD/../3rdparty/discount
    DEPENDPATH += $$PWD/../3rdparty/discount
    CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/release/
    CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/discount/debug/
}
unix {
    INCLUDEPATH += /usr/include
    LIBS += -L/usr/lib
}

LIBS += -ldiscount

