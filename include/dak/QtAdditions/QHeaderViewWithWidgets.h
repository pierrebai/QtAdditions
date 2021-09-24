#pragma once

#ifndef QT_ADDITIONS_QHEADER_VIEW_WITH_WIDGETS_H
#define QT_ADDITIONS_QHEADER_VIEW_WITH_WIDGETS_H

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qheaderview.h>

#include <map>

namespace dak::QtAdditions
{
   /////////////////////////////////////////////////////////////////////////
   //
   // Complex widget kept in a list widget.

   struct QHeaderViewWithWidgets : QHeaderView
   {
      // Create an item.
      QHeaderViewWithWidgets(Qt::Orientation orientation, QWidget* parent = nullptr);
      ~QHeaderViewWithWidgets();

      // Add widgets to the header of a section.
      void addSectionWidget(int section, QWidget* widget);
      QWidget* getSectionWidget(int section) const;

   protected:
      void handleSectionResized(int section, int oldSize, int newSize);
      void handleSectionMoved(int section, int oldVisualIndex, int newVisualIndex);

      void showEvent(QShowEvent* event) override;

      void fixWidgetPosition(int section);
      void fixWidgetPositions();

      std::map<int, QWidget*> my_widgets;

      Q_OBJECT;
   };
}

#endif
