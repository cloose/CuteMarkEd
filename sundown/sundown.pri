INCLUDEPATH += $$PWD\..

HEADERS += \
    sundown/markdown.h \
    sundown/buffer.h \
    sundown/autolink.h \
    sundown/stack.h \
    sundown/html_blocks.h \
    sundown/html.h \
    sundown/houdini.h

SOURCES += \
    sundown/markdown.c \
    sundown/buffer.c \
    sundown/autolink.c \
    sundown/stack.c \
    sundown/html.c \
    sundown/houdini_html_e.c \
    sundown/houdini_href_e.c
