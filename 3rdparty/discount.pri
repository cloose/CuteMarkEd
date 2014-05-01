#
# Discount library
#
win32 {
    INCLUDEPATH += $$PWD/../3rdparty/discount
    DEPENDPATH += $$PWD/../3rdparty/discount
    LIBS += -ldiscount
}
unix {
    INCLUDEPATH += /usr/include
    LIBS += -lmarkdown
}


