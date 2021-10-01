#pragma once

#ifndef QT_ADDITIONS_QHEADER_VIEW_WITH_WIDGETS_H
#define QT_ADDITIONS_QHEADER_VIEW_WITH_WIDGETS_H

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qheaderview.h>

#include <map>

class QTableView;
class QTreeView;

namespace dak::QtAdditions
{
   /////////////////////////////////////////////////////////////////////////
   //
   // A list widget header view that can contains widgets in the header.

   struct QHeaderViewWithWidgets : QHeaderView
   {
      // Create an header view.
      QHeaderViewWithWidgets(Qt::Orientation orientation, QTableView* parent);
      QHeaderViewWithWidgets(Qt::Orientation orientation, QTreeView* parent);
      ~QHeaderViewWithWidgets();

      // Add widgets to the header of a section.
      void addSectionWidget(int section, QWidget* widget);
      QWidget* getSectionWidget(int section) const;

   protected:
      QHeaderViewWithWidgets(Qt::Orientation orientation);

      void handleSectionResized(int section, int oldSize, int newSize);
      void handleSectionMoved(int section, int oldVisualIndex, int newVisualIndex);

      void showEvent(QShowEvent* event) override;

      // Reposition the widgets over the headers.
      void fixWidgetPosition(int section);
      void fixWidgetPositions();

      std::map<int, QWidget*> my_widgets;

      Q_OBJECT;
   };
}

#endif
