cmake_minimum_required(VERSION 2.8.11)

project(cutemarked)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

### Dependencies ###

# Find the Qt5 library
find_package(Qt5Network REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)
find_package(Qt5Widgets REQUIRED)

### Subdirs ###

add_subdirectory(app-static)
add_subdirectory(app)

