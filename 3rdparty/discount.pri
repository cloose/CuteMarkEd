#
# Discount library
#
win32 {
    INCLUDEPATH += $$PWD/../3rdparty/discount
    DEPENDPATH += $$PWD/../3rdparty/discount
}
unix {
    INCLUDEPATH += /usr/include
}

LIBS += -ldiscount

