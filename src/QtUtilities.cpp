#include "dak/QtAdditions/QtUtilities.h"

#ifdef WIN32
#include <QtWinExtras/qwinfunctions.h>
#endif

#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qerrormessage.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qinputdialog.h>

#include <fstream>

namespace dak::QtAdditions
{
   using namespace std;

   QPixmap CreatePixmapFromResource(int res)
   {
      #ifdef WIN32
         QPixmap pixmap = QtWin::fromHBITMAP((HBITMAP)::LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(res)), QtWin::HBitmapNoAlpha);
         pixmap.setMask(pixmap.createMaskFromColor(QColor(255, 255, 255, 255)));
         return pixmap;
      #else
         return QPixmap();
      #endif
   }

   QToolButton* CreateToolButton()
   {
      QToolButton* button = new QToolButton;
      button->setIconSize(QSize(64, 64));
      button->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
      return button;
   }

   QToolButton* CreateToolButton(const QString& text, int icon, QKeySequence key, const QString& tooltip, function<void()> callback)
   {
      return CreateToolButton(CreateAction(text, icon, key, tooltip, callback));
   }

   QToolButton* CreateToolButton(const wchar_t* text, int icon, QKeySequence key, const wchar_t* tooltip, std::function<void()> callback)
   {
      return CreateToolButton(QString::fromWCharArray(text ? text : L""), icon, key, QString::fromWCharArray(tooltip ? tooltip : L""), callback);
   }

   QToolButton* CreateToolButton(QAction* action)
   {
      QToolButton* button = CreateToolButton();
      button->setDefaultAction(action);
      return button;
   }

   QAction* CreateAction(const QString& text, int icon, QKeySequence key, const QString& tooltip, function<void()> callback)
   {
      QAction* action = new QAction;
      if (!text.isEmpty())
         action->setText(text);
      if (icon > 0)
         action->setIcon(QIcon(CreatePixmapFromResource(icon)));
      if (!key.isEmpty())
         action->setShortcut(key);
      if (!tooltip.isEmpty())
         action->setToolTip(tooltip);
      if (callback)
         action->connect(action, &QAction::triggered, callback);
      return action;
   }

   QAction* CreateAction(const wchar_t* text, int icon, QKeySequence key, const wchar_t* tooltip, function<void()> callback)
   {
      return CreateAction(QString::fromWCharArray(text ? text : L""), icon, key, QString::fromWCharArray(tooltip ? tooltip : L""), callback);
   }

   QAction* CreateToggle(const QString& text, int icon, QKeySequence key, const QString& tooltip, std::function<void()> callback)
   {
      QAction* action = CreateAction(text, icon, key, tooltip, callback);
      action->setCheckable(true);
      return action;
   }

   QAction* CreateToggle(const wchar_t* text, int icon, QKeySequence key, const wchar_t* tooltip, std::function<void()> callback)
   {
      return CreateToggle(QString::fromWCharArray(text ? text : L""), icon, key, QString::fromWCharArray(tooltip ? tooltip : L""), callback);
   }

   filesystem::path AskOpen(const QString& title, const QString& file_types, QWidget* parent)
   {
      return AskOpen(title, file_types, QString(), parent);
   }

   filesystem::path AskOpen(const QString& title, const QString& file_types, const QString& initialContent, QWidget* parent)
   {
      const QString qfn = QFileDialog::getOpenFileName(parent, title, initialContent , file_types);

      return qfn.toStdWString();
   }

   filesystem::path AskSave(const QString& title, const QString& file_types, const QString& initialContent, QWidget* parent)
   {
      const QString qfn = QFileDialog::getSaveFileName(parent, title, initialContent, file_types);

      return qfn.toStdWString();
   }

   // Ask yes/no/cancel.
   YesNoCancel AskYesNoCancel(const QString& title, const QString& text, QWidget* parent)
   {
      QMessageBox box;
      box.setWindowTitle(title);
      box.setText(text);
      box.setStandardButtons(QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::Cancel | QMessageBox::StandardButton::No );
      box.setDefaultButton(QMessageBox::StandardButton::Cancel);
      switch (box.exec())
      {
         case QMessageBox::StandardButton::Yes:
            return YesNoCancel::Yes;
         case QMessageBox::StandardButton::No:
            return YesNoCancel::No;
         case QMessageBox::StandardButton::Cancel:
         default:
            return YesNoCancel::Cancel;
      }
   }

   wstring AskForText(const QString& title, const QString& label, const QString& initialContent, QWidget* parent)
   {
      QString text = QInputDialog::getText(parent, title, label, QLineEdit::Normal, initialContent);

      return text.toStdWString();
   }
}

// vim: sw=3 : sts=3 : et : sta : 
