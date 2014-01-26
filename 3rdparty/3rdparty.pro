TEMPLATE = subdirs

SUBDIRS += \
    discount \
    hunspell

with_hoedown {
    message("3rdparty: Build hoedown markdown converter library")
    DEFINES += ENABLE_HOEDOWN
    SUBDIRS += hoedown
}
