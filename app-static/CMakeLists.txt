### app-static library ###

set(app-static_SRCS
    snippets/snippetcollection.cpp
)

add_library(app-static STATIC ${app-static_SRCS})
target_link_libraries(app-static 
                      Qt5::WebKitWidgets
                      Qt5::Widgets)

