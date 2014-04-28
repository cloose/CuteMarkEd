#
# hoedown
#
message("app: Enable hoedown markdown converter support")

DEFINES += ENABLE_HOEDOWN


INCLUDEPATH += $$PWD/../3rdparty/hoedown
DEPENDPATH += $$PWD/../3rdparty/hoedown

LIBS +=

win32 {
CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hoedown/release/ -lhoedown
	CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/hoedown/debug/
}
unix {
	LIBS += -L$$OUT_PWD/../3rdparty/hoedown/
}

LIBS += -Lhoedown

