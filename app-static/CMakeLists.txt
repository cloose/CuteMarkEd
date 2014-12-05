### app-static library ###

set(app-static_SRCS
    converter/discountmarkdownconverter.cpp
    converter/revealmarkdownconverter.cpp
    snippets/jsonsnippetfile.cpp
    snippets/jsonsnippettranslator.cpp
    snippets/snippetcollection.cpp
    snippets/snippetlistmodel.cpp
    datalocation.cpp
)

add_library(app-static STATIC ${app-static_SRCS})
target_link_libraries(app-static 
                      Qt5::WebKitWidgets
                      Qt5::Widgets)

