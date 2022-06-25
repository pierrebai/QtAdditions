cmake_minimum_required(VERSION 3.7.0)

project(QtAdditions)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

# Qt 5 stuff

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)

# QtAdditions

add_library(QtAdditions
   README.md
   src/QHeaderViewWithWIdgets.cpp   include/dak/QtAdditions/QHeaderViewWithWIdgets.h
   src/QtUtilities.cpp              include/dak/QtAdditions/QtUtilities.h
   src/QWidgetListItem.cpp          include/dak/QtAdditions/QWidgetListItem.h
   src/QWidgetScrollListWidget.cpp  include/dak/QtAdditions/QWidgetScrollListWidget.h
   src/QWidgetListWidget.cpp        include/dak/QtAdditions/QWidgetListWidget.h
   src/QTableWidgetWithComboBox.cpp include/dak/QtAdditions/QTableWidgetWithComboBox.h
                                    include/dak/QtAdditions/QWidgetListMimeData.h
)

target_compile_features(QtAdditions PUBLIC
   cxx_std_20
)

target_include_directories(QtAdditions PUBLIC
   include
)

target_include_directories(QtAdditions PUBLIC
   "${Qt5Core_INCLUDE_DIRS}"
   "${Qt5Widgets_INCLUDE_DIRS}"
   "${Qt5Gui_INCLUDE_DIRS}"
)

if (WIN32)

find_package(Qt5 COMPONENTS WinExtras REQUIRED)

target_include_directories(QtAdditions PUBLIC
   "${Qt5WinExtras_INCLUDE_DIRS}"
)

endif()

add_subdirectory(examples/ExampleTableWithCombo EXCLUDE_FROM_ALL)
add_subdirectory(examples/ExampleWidgetList EXCLUDE_FROM_ALL)
add_subdirectory(examples/ExampleListHeaderWidget EXCLUDE_FROM_ALL)

