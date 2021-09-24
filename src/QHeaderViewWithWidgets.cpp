#include "dak/QtAdditions/QHeaderViewWithWidgets.h"

#include <QtWidgets/qcombobox.h>

namespace dak::QtAdditions
{
   using namespace std;

   QHeaderViewWithWidgets::QHeaderViewWithWidgets(Qt::Orientation orientation, QWidget* parent)
      : QHeaderView(orientation, parent)
   {
      connect(this, &QHeaderViewWithWidgets::sectionResized, [self = this](int section, int oldSize, int newSize) { self->handleSectionResized(section, oldSize, newSize); });
      connect(this, &QHeaderViewWithWidgets::sectionMoved, [self = this](int section, int oldVisualIndex, int newVisualIndex) { self->handleSectionMoved(section, oldVisualIndex, newVisualIndex); });
      connect(this, &QHeaderViewWithWidgets::geometriesChanged, [self = this]() { self->fixWidgetPositions(); });
   }

   QHeaderViewWithWidgets::~QHeaderViewWithWidgets()
   {
   }

   void QHeaderViewWithWidgets::addSectionWidget(int section, QWidget* widget)
   {
      if (!widget)
         return;

      if (section < 0)
         return;

      QWidget* old = my_widgets[section];
      my_widgets[section] = widget;
      widget->setParent(this);
      delete old;
   }

   QWidget* QHeaderViewWithWidgets::getSectionWidget(int section) const
   {
      auto iter = my_widgets.find(section);
      if (iter == my_widgets.end())
         return nullptr;

      return iter->second;
   }

   void QHeaderViewWithWidgets::showEvent(QShowEvent* event)
   {
      QHeaderView::showEvent(event);

      for (int section = 0; section < count(); ++section)
      {
         QWidget* widget = getSectionWidget(section);
         if (!widget)
            continue;

         fixWidgetPosition(section);

         widget->show();
      }
   }

   void QHeaderViewWithWidgets::handleSectionResized(int section, int oldSize, int newSize)
   {
      for (int i = visualIndex(section); i < count(); ++i)
      {
         const int section = logicalIndex(i);
         fixWidgetPosition(section);
      }
   }

   void QHeaderViewWithWidgets::handleSectionMoved(int section, int oldVisualIndex, int newVisualIndex)
   {

      for (int i = qMin(oldVisualIndex, newVisualIndex); i < count(); ++i)
      {
         const int section = logicalIndex(i);
         fixWidgetPosition(section);
      }
   }

   void QHeaderViewWithWidgets::fixWidgetPosition(int section)
   {
      QWidget* widget = getSectionWidget(section);
      if (!widget)
         return;

      widget->setGeometry(sectionViewportPosition(section) + 3, 0, sectionSize(section) - 6, height());
   }

   void QHeaderViewWithWidgets::fixWidgetPositions()
   {
      for (int section = 0; section < count(); ++section)
         fixWidgetPosition(section);
   }
}

