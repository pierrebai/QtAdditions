
# **Widgets in the Header of List Views**

## The Problem

It's often useful to be able to place additional widgets in tghe header row of
a list view or table view. A common example is to place a check-mark in the
header to turn on and off an entire column. Unfortunately, Qt 5 does no support
this feature natively.

A quick search will find some solutions, but they all have limitations. For
example the solution outlined [in this stack overflow question](https://stackoverflow.com/questions/37542803/how-to-implement-checkbox-in-header-of-qtreeview)
only support check-box and only one per table. Another [proposed solution](https://www.qt.io/blog/2012/09/28/qt-support-weekly-27-widgets-on-a-header)
also only support check-box, but form a good base to start.

Taking inspiration from the second source, we want to improve the solution
to achieve these goals:

- Support any type of widget.
- Support multiple columns, each having its own widget.
- Be simple to use.

## How it Works

The trick is to have a custom header view (`QHeaderView`) that can be set on
a table (`QTableWidget`) or list (`QListWidget`). The custom header view tracks
the widgets that are placed at the top of each column. It also handles placing
and resizing the widgets so that they fit within the header.

Since the widgets are placed on top of the header, it is recommended to *not*
set any title for that column and instead use a widget that has a label. Since
we support any widget, you can create a container to place an additional label
if the widget you want to use does not have a label.

The trick of placing the widget on top works because Qt paints parent widgets
before their children. Since the additional widgets are children of the header
view, they get painted after the header and thus appear on top of it.

The API to use the custom header is very simple. You simply create an instance
of `QHeaderViewWithWidgets`, add the widgets to the column (called sectin in Qt),
and set the header view on your table. In short, it looks like this:

```C++
   // Create a combo-box for the header.
   auto col1_check = new QCheckBox("My checkbox");

   // Create the header view with the combo-box for coulmn 1.
   auto header = new QHeaderViewWithWidgets(Qt::Orientation::Horizontal);
   header->addSectionWidget(1, col1_check);

   // Create the table and set the custom header.
   auto list = new QTableWidget;
   list->setHorizontalHeader(header);
```

## The Code

The C++ code needed to put widgets in the header of a table widget is available
in this public repository on github:

[https://github.com/pierrebai/QtAdditions](https://github.com/pierrebai/QtAdditions)

An example of an application using the custom header view with sub-widgets is provided
in this same project, found in the `examples\ExampleListHeaderWidget` folder.


