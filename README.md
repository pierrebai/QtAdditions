# QtAdditions

A group of additional classes and functions that are useful when creating user 
interfaces in Qt.

# Contents

These are the classes a functions found in the `include` and `src` folders.

## QWidgetListWidget

A Qt list  widget containing complex sub-widgets.

The QWidgetListWidget class is a list widget that can contain a list of arbitrary widgets as items.
The items can have any control put into them. The list widget supports scrolling, selection and drag-and-drop.

Here is an example showing how the widget looks:

![example app](https://github.com/pierrebai/QtAdditions/blob/main/list-widget.png "Example App")

## QTableWidgetWithComboBox

Allow putting a comb-box widget inside a multi-column list widget.

## QHeaderViewWithWidgets

Allow putting widgets in the header row of a table view.

## QtUtilities

Various functions to create toolbar buttons, create actions, use the open or save dialogs,
ask questions, create pixmap from Windows bitmap resources. 


# Examples

The `examples` folder contains multiple simple example application for many of these classes.
They also contain more extensive documentation about the design of each Qt utility classes.


# Dependencies and Build

The project requires Qt. It was built using Qt 5.15. It uses CMake to build the project. CMake 3.7 was used.

A script to generate a Visual-Studio solution is provided. In order for CMake to find Qt,
the environment variable QT5_DIR must be defined and must point to the Qt 5.15 directory.
For example:

        QT5_DIR=C:\Tools\Qt\5.15.0\msvc2019_64

Alternatively, to invoke cmake directly, it needs to be told where to find Qt.
It needs the environment variable CMAKE_PREFIX_PATH set to the location of Qt.
For example:

        CMAKE_PREFIX_PATH=C:\Tools\Qt\5.15.0\msvc2019_64

