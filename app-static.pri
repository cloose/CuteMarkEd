#
# Use internal static library: app-static
#
INCLUDEPATH += $$PWD/app-static
DEPENDPATH += $$PWD/app-static

LIBS += -L$$PWD/../libs
LIBS += -lapp-static

