#include "dak/QtAdditions/QTableWidgetWithComboBox.h"

#include <QtCore/qtimer.h>

#include <QtWidgets/qapplication.h>
#include <QtWidgets/qstyle.h>

namespace dak::QtAdditions
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // A QStyledItemDelegate containing a combo-box that appears
   // immediately on mouse-click.
   //
   // To work the custom item delegate must:
   //
   //     - Pop-up the combo-box content immediately in the delegate
   //       when creating the editor.
   //
   //     - Commit the data and end the editor immediately when
   //       when an item is selected in the popped-up combo-box.
   //
   //     - Use custom paint in the delegate to draw the data
   //       with the look of a combo-box. (So the user knows that
   //       there is a usable combo-box there.)
   //
   //     - Use a custom sizing hint in the delegate to make sure
   //       the item can fit the combo-box and its widest text.
   //

   // Create the delegate with the combo-box items list.
   QItemDelegateWithComboBox::QItemDelegateWithComboBox(const QStringList& items, QObject* parent)
      : QStyledItemDelegate(parent), combo_items(items)
   {
   }

   // Create the combo-box and populate it.
   QWidget* QItemDelegateWithComboBox::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
   {
      QComboBox* cb = new QComboBox(parent);
      const int row = index.row();
      for (const auto text : combo_items)
         cb->addItem(text);
      cb->connect(cb, &QComboBox::currentTextChanged, [self = this, cb = cb, index = index](const QString& text)
      {
         if (cb->isVisible())
         {
            const_cast<QItemDelegateWithComboBox*>(self)->commitData(cb);
            const_cast<QItemDelegateWithComboBox*>(self)->closeEditor(cb);
         }
      });
      return cb;
   }

   // Get the index of the text in the combo-box that matches the current value of the item.
   // If it is valid, adjust the combo-box.
   void QItemDelegateWithComboBox::setEditorData(QWidget* editor, const QModelIndex& index) const
   {
      QComboBox* cb = qobject_cast<QComboBox*>(editor);
      if (!cb)
         return;

      const QString currentText = index.data(Qt::EditRole).toString();
      const int cbIndex = cb->findText(currentText);
      if (cbIndex >= 0)
         cb->setCurrentIndex(cbIndex);
      cb->showPopup();
   }

   // Save combo-box data in the view item.
   void QItemDelegateWithComboBox::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
   {
      QComboBox* cb = qobject_cast<QComboBox*>(editor);
      if (!cb)
         return;

      model->setData(index, cb->currentText(), Qt::EditRole);
   }

   void QItemDelegateWithComboBox::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
   {
      QStyleOptionComboBox box;
      box.state = option.state;

      box.rect = option.rect;
      box.currentText = index.data(Qt::EditRole).toString();

      QApplication::style()->drawComplexControl(QStyle::CC_ComboBox, &box, painter, 0);
      QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel, &box, painter, 0);
   }

   QSize QItemDelegateWithComboBox::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
   {
      QStyleOptionComboBox box;
      box.state = option.state;

      box.rect = option.rect;

      QSize size(0, 0);
      for (const auto text : combo_items)
      {
         box.currentText = text;
         QRect rect = QApplication::style()->itemTextRect(option.fontMetrics, option.rect, Qt::AlignCenter, true, text);
         size = size.expandedTo(QApplication::style()->sizeFromContents(QStyle::ContentsType::CT_ComboBox, &box, rect.size(), option.widget));
      }
      return size;
   }

   ////////////////////////////////////////////////////////////////////////////
   //
   // A QTableWidget containing a combo-box that appears
   // immediately on mouse-click.
   //
   // To work we need a custom table widget and a custom item delegate:
   //
   //     - Override mouse-processing in the table to show the
   //       combo-box editor on the first click.
   //
   //     - Pop-up the combo-box content immediately in the delegate
   //       when creating the editor.
   //
   //     - Commit the data and end the editor immediately when
   //       when an item is selected in the popped-up combo-box.
   //
   //     - Use custom paint in the delegate to draw the data
   //       with the look of a combo-box. (So the user knows that
   //       there is a usable combo-box there.)
   //
   //     - Use a custom sizing hint in the delegate to make sure
   //       the item can fit the combo-box and its widest text.
   //

   // Create the table widget with the combo-box items list.
   QTableWidgetWithComboBox::QTableWidgetWithComboBox(int col, const QStringList& items, QWidget* parent)
      : QTableWidget(parent), combo_column(col), combo_items(items)
   {
      setColumnCount(col + 1);
      setItemDelegateForColumn(col, new QItemDelegateWithComboBox(items, this));
   }

   // Process mouse events to create the combo-box on the first mouse click.
   void QTableWidgetWithComboBox::mousePressEvent(QMouseEvent* event)
   {
      if (event->button() == Qt::LeftButton)
      {
         const QModelIndex index = indexAt(event->pos());
         if (index.column() == combo_column)
         {
            if (auto selection = selectionModel())
            {
               const QModelIndex other_index = model()->index(index.row(), combo_column > 0 ? 0 : 1);
               selection->setCurrentIndex(other_index, QItemSelectionModel::SelectionFlag::ClearAndSelect);
            }
            QTimer::singleShot(1, [self = this, index = index]()
            {
               self->edit(index);
            });
            event->setAccepted(true);
            return;
         }
      }
      QTableWidget::mousePressEvent(event);
   }
}

// vim: sw=3 : sts=3 : et : sta : 
