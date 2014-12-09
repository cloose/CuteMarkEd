### cutemarked application ###

set(cutemarked_SRCS
    controls/activelabel.cpp
    controls/fileexplorerwidget.cpp
    controls/findreplacewidget.cpp
    controls/languagemenu.cpp 
    controls/linenumberarea.cpp
    controls/recentfilesmenu.cpp
    hunspell/spellchecker.cpp
    hunspell/spellchecker_unix.cpp
    peg-markdown-highlight/styleparser.cpp
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

pkg_check_modules(HUNSPELL hunspell)

include_directories(${DISCOUNT_INCLUDES}
                    ${HUNSPELL_INCLUDE_DIRS}
                    ${CMAKE_SOURCE_DIR}/3rdparty/hunspell/src
                    ${CMAKE_SOURCE_DIR}/app-static
                    ${CMAKE_SOURCE_DIR}/peg-markdown-highlight)

qt5_wrap_ui(cutemarked_SRCS
            controls/fileexplorerwidget.ui
            controls/findreplacewidget.ui
            aboutdialog.ui
            exporthtmldialog.ui
            exportpdfdialog.ui
            imagetooldialog.ui
            mainwindow.ui
            optionsdialog.ui
            tabletooldialog.ui)

add_executable(cutemarked ${cutemarked_SRCS})
target_link_libraries(cutemarked 
                      ${DISCOUNT_LIBRARIES}
                      ${HUNSPELL_LIBRARIES}
                      app-static
                      peg-markdown-highlight
                      Qt5::Network
                      Qt5::PrintSupport
                      Qt5::WebKitWidgets
                      Qt5::Widgets)
