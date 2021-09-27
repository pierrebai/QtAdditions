cmake_minimum_required(VERSION 3.7.0)

project(ExampleWidgetList)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

# Qt 5 stuff

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)

add_executable(ExampleWidgetList WIN32
   Main.cpp
   MainWindow.cpp          MainWindow.h
   ExampleListItem.cpp     ExampleListItem.h
   README.md
)

target_link_libraries(ExampleWidgetList PUBLIC
   QtAdditions
   Qt5::Widgets Qt5::Gui Qt5::Core
)

target_compile_features(ExampleWidgetList PUBLIC
   cxx_std_20
)

target_include_directories(ExampleWidgetList PUBLIC
   "${PROJECT_SOURCE_DIR}/include"
)

add_custom_command(TARGET ExampleWidgetList POST_BUILD
   COMMAND "${Qt5_DIR}/../../../bin/windeployqt.exe" --no-webkit2 --no-angle --no-system-d3d-compiler --no-opengl-sw "$<TARGET_FILE:ExampleWidgetList>"
)

