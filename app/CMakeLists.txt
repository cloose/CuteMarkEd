### cutemarked application ###

set(cutemarked_SRCS
    aboutdialog.cpp
    exporthtmldialog.cpp
    exportpdfdialog.cpp
    highlightworkerthread.cpp
    htmlhighlighter.cpp
    htmlpreviewgenerator.cpp
    imagetooldialog.cpp
    main.cpp
    mainwindow.cpp
    markdowneditor.cpp
    markdownhighlighter.cpp
    markdownmanipulator.cpp
    options.cpp
    optionsdialog.cpp
    snippetcompleter.cpp
    tabletooldialog.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/app-static
                    ${CMAKE_SOURCE_DIR}/peg-markdown-highlight)

qt5_wrap_ui(cutemarked_SRCS aboutdialog.ui
                            exporthtmldialog.ui
                            exportpdfdialog.ui
                            imagetooldialog.ui
                            mainwindow.ui
                            optionsdialog.ui
                            tabletooldialog.ui)

add_executable(cutemarked ${cutemarked_SRCS})
target_link_libraries(cutemarked 
                      app-static
                      Qt5::Network
                      Qt5::PrintSupport
                      Qt5::WebKitWidgets
                      Qt5::Widgets)
