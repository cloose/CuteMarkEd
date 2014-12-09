### app-static library ###

set(app-static_SRCS
    converter/discountmarkdownconverter.cpp
    converter/revealmarkdownconverter.cpp
    snippets/jsonsnippetfile.cpp
    snippets/jsonsnippettranslator.cpp
    snippets/snippetcollection.cpp
    snippets/snippetlistmodel.cpp
    spellchecker/dictionary.cpp
    template/htmltemplate.cpp
    template/presentationtemplate.cpp
    datalocation.cpp
    htmlviewsynchronizer.cpp
    revealviewsynchronizer.cpp
    slidelinemapping.cpp
    viewsynchronizer.cpp
)

add_library(app-static STATIC ${app-static_SRCS})
target_link_libraries(app-static 
                      Qt5::WebKitWidgets
                      Qt5::Widgets)

