#include "dak/QtAdditions/QTableWidgetWithComboBox.h"

#include <QtWidgets/qapplication>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qheaderview.h>

using namespace dak::QtAdditions;

int main(int argc, char **argv)
{
   /////////////////////////////////////////////////////////////////////////
   //
   // Prepare the application.

   QScopedPointer<QApplication> app(new QApplication(argc, argv));

   /////////////////////////////////////////////////////////////////////////
   //
   // Create the table list with a combo-box column.

   constexpr int combo_column = 2;
   const QStringList combo_items({ "A", "B", "C", "D", "E", "F" });
   auto list = new QTableWidgetWithComboBox(combo_column,combo_items);

   // Create columns header labels and some other non-essential settings.
   list->setColumnCount(3);
   list->setHorizontalHeaderLabels(QStringList({ "Normal Column 1", "Normal Column 2", "Combo Column" }));
   list->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
   list->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
   list->setEditTriggers(QAbstractItemView::EditTrigger::EditKeyPressed | QAbstractItemView::EditTrigger::SelectedClicked | QAbstractItemView::EditTrigger::AnyKeyPressed);
   list->verticalHeader()->hide();

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

   list->connect(list, &QTableWidget::itemChanged, [&](QTableWidgetItem * item)
   {
      mainWindow->setWindowTitle(QString::asprintf("Changed combo-box element of row %d to %s", item->row(), item->text().data()));
   });

   list->connect(list, &QTableWidget::currentItemChanged, [&](QTableWidgetItem * item)
   {
      mainWindow->setWindowTitle(QString::asprintf("Changed selection to element of row %d, column %d", item->row(), item->column()));
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

