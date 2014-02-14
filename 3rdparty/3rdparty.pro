TEMPLATE = subdirs

SUBDIRS += \
    discount \
    hoedown \
    hunspell \
    quazip-0.6

with_hoedown {
    message("3rdparty: Build hoedown markdown converter library")
    DEFINES += ENABLE_HOEDOWN
    SUBDIRS += hoedown
}
