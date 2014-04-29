#
# Discount library
#
win32 {
    INCLUDEPATH += $$PWD/../3rdparty/discount
    DEPENDPATH += $$PWD/../3rdparty/discount
    LIBS += -L$$PWD/../libs
}
unix {
    INCLUDEPATH += /usr/include
    LIBS += -L/usr/lib
}

LIBS += -ldiscount

