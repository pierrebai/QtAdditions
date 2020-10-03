#pragma once

#include <functional>
#include <filesystem>
#include <string>

#include <QtGui/qicon.h>
#include <QtGui/qpixmap.h>
#include <QtGui/qbitmap.h>

#include <QtWidgets/qaction.h>
#include <QtWidgets/qtoolbutton.h>

namespace dak::QtAdditions
{
   ////////////////////////////////////////////////////////////////////////////
   //
   // Create toolbar buttons.
   // note: icon is a bitmap resource ID.

   QToolButton* CreateToolButton(const QString& text, int icon = 0, QKeySequence key = QKeySequence(), const QString& tooltip = nullptr, std::function<void()> = nullptr);
   QToolButton* CreateToolButton(QAction* action);
   QToolButton* CreateToolButton();

   ////////////////////////////////////////////////////////////////////////////
   //
   // Create action.
   // note: icon is a bitmap resource ID.

   QAction* CreateAction(const QString& text, int icon = 0, QKeySequence key = QKeySequence(), const QString& tooltip = nullptr, std::function<void()> = nullptr);

   ////////////////////////////////////////////////////////////////////////////
   //
   // Create pixmap from a bitmap resource. A mask will automatically be created.

   QPixmap CreatePixmapFromResource(int res);

   ////////////////////////////////////////////////////////////////////////////
   //
   // Show a dialog to open or save something.

   std::filesystem::path AskOpen(const QString& title, const QString& file_types, QWidget* parent);
   std::filesystem::path AskSave(const QString& title, const QString& file_types, const QString& initialContent, QWidget* parent);

   ////////////////////////////////////////////////////////////////////////////
   //
   // Ask for text.

   std::wstring AskForText(const QString& title, const QString& label, const QString& initialContent, QWidget* parent);

   ////////////////////////////////////////////////////////////////////////////
   //
   // Ask yes/no/cancel.

   enum class YesNoCancel
   {
      No = 0,
      Yes = 1,
      Cancel = 2,
   };

   YesNoCancel AskYesNoCancel(const QString& title, const QString& text, QWidget* parent);

   ////////////////////////////////////////////////////////////////////////////
   //
   // Disable feedback in a widget.

   struct DisableFeedback
   {
      DisableFeedback(QWidget* widget, int& recursionCounter)
      : _widget(widget), _recursionCounter(recursionCounter)
      {
         if (_widget)
         {
            _recursionCounter++;
            _widget->blockSignals(_recursionCounter > 0);
         }
      }

      ~DisableFeedback()
      {
         if (_widget)
         {
            _recursionCounter--;
            _widget->blockSignals(_recursionCounter > 0);
         }
      }

   private:
      QWidget* _widget;
      int& _recursionCounter;
   };
}

// vim: sw=3 : sts=3 : et : sta : 
