#include "dak/QtAdditions/QHeaderViewWithWidgets.h"

#include <QtWidgets/qapplication>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qtablewidget.h>

using namespace dak::QtAdditions;

int main(int argc, char **argv)
{
   /////////////////////////////////////////////////////////////////////////
   //
   // Prepare the application.

   QScopedPointer<QApplication> app(new QApplication(argc, argv));

   /////////////////////////////////////////////////////////////////////////
   //
   // Create combo-box for the header.

   auto col1_check = new QCheckBox("Words");
   auto col2_combo = new QComboBox;
   col2_combo->addItems({"Letters", "Alphabet", "Grades"});

   /////////////////////////////////////////////////////////////////////////
   //
   // Create the table list with a combo-box column.

   auto list = new QTableWidget;

   /////////////////////////////////////////////////////////////////////////
   //
   // Create the header view with combo-boxes.

   auto header = new QHeaderViewWithWidgets(Qt::Orientation::Horizontal, list);
   header->addSectionWidget(1, col1_check);
   header->addSectionWidget(2, col2_combo);
   header->setMinimumSectionSize(100);

   // Create columns header labels and some other non-essential settings.
   list->setColumnCount(3);
   list->setHorizontalHeaderLabels(QStringList({ "Normal Column 1", "", "" }));
   list->verticalHeader()->hide();
   list->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

   /////////////////////////////////////////////////////////////////////////
   //
   // Fill the list with a few items.

   const char* items[5][3] =
   {
      { "First",  "Citizen",  "C" },
      { "Second", "Thoughts", "D" },
      { "Third",  "Time",     "A" },
      { "Fourth", "Wheel",    "B" },
      { "Fifth",  "Element",  "C" },
   };

   for (const auto item : items)
   {
      const int row = list->rowCount();
      list->setRowCount(row + 1);
      for (int col = 0; col < 3; ++col)
      {
         auto list_item = new QTableWidgetItem(item[col]);
         list->setItem(row, col, list_item);
         if (col > 0)
         {
            list_item->setCheckState(Qt::CheckState::Unchecked);
         }
      }
   }

   list->resizeColumnsToContents();

   /////////////////////////////////////////////////////////////////////////
   //
   // Create the main window.

   QMainWindow* mainWindow = new QMainWindow;
   mainWindow->setCentralWidget(list);

   /////////////////////////////////////////////////////////////////////////
   //
   // Connect a signal to show user interaction in the window title.

   auto updateAllColumnItems = [](QTableWidget* list, int column, int checkState)
   {
      if (!list)
         return;

      for (int row = 0; row < list->rowCount(); ++row)
      {
         if (QTableWidgetItem* item = list->item(row, column))
         {
            item->setCheckState((Qt::CheckState)checkState);
         }
      }
   };

   col1_check->connect(col1_check, &QCheckBox::stateChanged,
      [list, updateAllColumnItems](int checkState)
      { updateAllColumnItems(list, 1, checkState); });

   list->connect(list, &QTableWidget::itemChanged, [&](QTableWidgetItem * item)
   {
      mainWindow->setWindowTitle(
         QString::asprintf("Changed checkmark of row %d, column %d to %s",
            item->row(),
            item->column(),
            item->checkState() == Qt::CheckState::Checked ? "checked" : "unchecked"));
   });

   list->connect(list, &QTableWidget::currentItemChanged, [&](QTableWidgetItem * item)
   {
      mainWindow->setWindowTitle(
         QString::asprintf("Changed selection to row %d, column %d",
            item->row(),
            item->column()));
   });

   /////////////////////////////////////////////////////////////////////////
   //
   // Show window and execute app.

   mainWindow->resize(700, 400);
   mainWindow->show();

   return app->exec();
}

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, wchar_t* lpCmdLine, int nCmdShow)
{
   return main(0, 0);
}

