### cutemarked application ###

set(cutemarked_SRCS
    htmlpreviewgenerator.cpp
    main.cpp
    mainwindow.cpp
    markdowneditor.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/app-static)
qt5_wrap_ui(cutemarked_SRCS mainwindow.ui)

add_executable(cutemarked ${cutemarked_SRCS})
target_link_libraries(cutemarked 
                      app-static
                      Qt5::Network
                      Qt5::PrintSupport
                      Qt5::WebKitWidgets
                      Qt5::Widgets)
