cmake_minimum_required(VERSION 2.8.11)

project(cutemarked)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

### Dependencies ###

# TODO: only on unix
find_package(PkgConfig)

# Find the Qt5 library
find_package(Qt5Network REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)
find_package(Qt5Widgets REQUIRED)

# TODO: Should be moved to find module
find_path(DISCOUNT_INCLUDES mkdio.h)
find_library(DISCOUNT_LIBRARIES markdown)

### Subdirs ###

#add_subdirectory(3rdparty)
add_subdirectory(peg-markdown-highlight)
add_subdirectory(app-static)
add_subdirectory(app)

