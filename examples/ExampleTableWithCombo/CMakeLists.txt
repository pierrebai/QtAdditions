# Qt 5 stuff

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)

add_executable(ExampleTableWithCombo WIN32
   Main.cpp
   README.md
)

target_link_libraries(ExampleTableWithCombo PUBLIC
   QtAdditions
   Qt5::Widgets Qt5::Gui Qt5::Core
)

target_compile_features(ExampleTableWithCombo PUBLIC
   cxx_std_20
)

target_include_directories(ExampleTableWithCombo PUBLIC
   "${PROJECT_SOURCE_DIR}/include"
)

add_custom_command(TARGET ExampleTableWithCombo POST_BUILD
   COMMAND "${Qt5_DIR}/../../../bin/windeployqt.exe" --no-webkit2 --no-angle --no-system-d3d-compiler --no-opengl-sw "$<TARGET_FILE:ExampleTableWithCombo>"
)

