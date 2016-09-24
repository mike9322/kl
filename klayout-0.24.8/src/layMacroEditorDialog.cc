
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2016 Matthias Koefferlein

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/


#include "MacroTemplateSelectionDialog.h"
#include "layMacroEditorTree.h"
#include "layMacroEditorDialog.h"
#include "layMacroEditorSetupDialog.h"
#include "layMacroPropertiesDialog.h"
#include "layMacroInterpreter.h"
#include "layFileDialog.h"
#include "layMainWindow.h"
#include "layHelpDialog.h"
#include "tlString.h"
#include "tlClassRegistry.h"
#include "layExceptions.h"
#include "layApplication.h"
#include "layBrowserPanel.h"
#include "layTipDialog.h"
#include "layQtTools.h"
#include "layConfig.h"

#include <cstdio>
#include <limits>
#include <set>
#include <map>
#include <vector>
#include <memory>

#include <QtGui/QMessageBox>
#include <QtGui/QKeyEvent>
#include <QtGui/QItemDelegate>
#include <QtGui/QInputDialog>
#include <QtGui/QFileDialog>
#include <QtGui/QHeaderView>
#include <QtCore/QResource>

const std::string cfg_macro_editor_styles ("macro-editor-styles");
const std::string cfg_macro_editor_save_all_on_run ("macro-editor-save-all-on-run");
const std::string cfg_macro_editor_stop_on_exception ("macro-editor-stop-on-exception");
const std::string cfg_macro_editor_font_family ("macro-editor-font-family");
const std::string cfg_macro_editor_font_size ("macro-editor-font-size");
const std::string cfg_macro_editor_tab_width ("macro-editor-tab-width");
const std::string cfg_macro_editor_indent ("macro-editor-indent");
const std::string cfg_macro_editor_window_state ("macro-editor-window-state");
const std::string cfg_macro_editor_console_mru ("macro-editor-console-mru");
const std::string cfg_macro_editor_console_interpreter ("macro-editor-console-interpreter");
const std::string cfg_macro_editor_open_macros ("macro-editor-open-macros");
const std::string cfg_macro_editor_current_macro ("macro-editor-current-macro");
const std::string cfg_macro_editor_active_macro ("macro-editor-active-macro");
const std::string cfg_macro_editor_watch_expressions ("macro-editor-watch-expressions");
const std::string cfg_macro_editor_debugging_enabled ("macro-editor-debugging-enabled");

namespace lay
{

// -----------------------------------------------------------------------------------------
//  Implementation of the macro template selection dialog

class MacroTemplateSelectionDialog
  : public QDialog, private Ui::MacroTemplateSelectionDialog
{
public:
  MacroTemplateSelectionDialog (QWidget *parent, const std::vector<lay::Macro *> &templates, const std::string &cat)
    : QDialog (parent)
  {
    setupUi (this);

#if QT_VERSION >= 0x040300
    templateView->setWordWrap (true);
#endif
    templateView->header ()->hide ();

    m_template_count = 0;
    m_default_id = -1;

    //  Build a tree from the templates. Groups are formed by prepending a group title in the description
    //  separated from the actual description by ";;"
    int index = 0;
    for (std::vector<lay::Macro *>::const_iterator t = templates.begin (); t != templates.end (); ++t, ++index) {

      const std::string &c = (*t)->category ();

      bool take = false;
      if ((cat.empty () || cat == "macros") && c.empty ()) {
        //  take ones without explicit category in "macros" category 
        take = true;
      } else if (! c.empty ()) {
        //  others are checked whether the category name is part of the category list
        std::vector<std::string> cc = tl::split (c, ",");
        for (std::vector<std::string>::const_iterator ic = cc.begin (); ic != cc.end () && !take; ++ic) {
          if (*ic == cat) {
            take = true;
          }
        }
      }

      if (! take) {
        continue;
      }

      std::string group_title;
      std::string description = (*t)->description ();
      if (description.empty ()) {
        description = (*t)->name ();
      }

      size_t sep = description.find (";;");
      if (sep != std::string::npos) {
        group_title = std::string (description, 0, sep);
        description = std::string (description, sep + 2);
      } 

      QTreeWidgetItem *item = 0;
      if (group_title.empty ()) {
        item = new QTreeWidgetItem (templateView);
      } else {
        QString gt = tl::to_qstring (group_title);
        for (int i = 0; i < templateView->topLevelItemCount (); ++i) {
          if (templateView->topLevelItem (i)->text (0) == gt) {
            item = new QTreeWidgetItem (templateView->topLevelItem (i));
            break;
          }
        }
        if (! item) {
          QTreeWidgetItem *group = new QTreeWidgetItem (templateView);
          group->setText (0, gt);
          QFont f (templateView->font ());
          f.setWeight (QFont::Bold);
          group->setData (0, Qt::FontRole, f);
          item = new QTreeWidgetItem (group);
        }
      }

      m_default_id = index;
      ++m_template_count;

      item->setData (0, Qt::UserRole, QVariant (index));
      QString qd = tl::to_qstring (description + "\n");
      qd.replace (QString::fromAscii ("\\n"), QString::fromAscii ("\n"));
      item->setText (0, qd);

    }

    templateView->expandAll ();
  }

  int exec_dialog ()
  {
    templateView->setCurrentItem (0);
    if (m_template_count <= 1) {
      return m_default_id;
    } else if (exec ()) {
      if (templateView->currentItem () && templateView->currentItem ()->data (0, Qt::UserRole) != QVariant ()) { 
        return templateView->currentItem ()->data (0, Qt::UserRole).toInt ();
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }

private:
  int m_default_id;
  size_t m_template_count;
};

// -----------------------------------------------------------------------------------------
//  A custom delegate that uses UserRole + 2 for getting and setting the text

class EditRoleDelegate
  : public QItemDelegate
{
public:
  EditRoleDelegate (QWidget *parent)
    : QItemDelegate (parent)
  {
    //  .. nothing yet ..
  }

  void setEditorData (QWidget *widget, const QModelIndex &index) const
  {
    QLineEdit *editor = dynamic_cast<QLineEdit *> (widget);
    if (editor) {
      editor->setText (index.model ()->data (index, Qt::UserRole).toString ());
    }
  }

  void setModelData (QWidget *widget, QAbstractItemModel *model, const QModelIndex &index) const
  {
    QLineEdit *editor = dynamic_cast<QLineEdit *> (widget);
    if (editor) {
      model->setData (index, QVariant (editor->text ()), Qt::UserRole);
    }
  }
};

// ----------------------------------------------------------------------------------------------
//  MacroEditorDialog implementation

static lay::MacroEditorDialog *s_macro_editor_instance = 0;

MacroEditorDialog::MacroEditorDialog (QWidget *parent, lay::MacroCollection *root)
  : QDialog (0 /*show as individual top widget*/, Qt::Window),
    mp_root (root),
    m_first_show (true), m_in_processing (false), m_debugging_on (true),
    mp_run_macro (0),
    md_update_console_text (this, &MacroEditorDialog::update_console_text),
    md_apply_search (this, &MacroEditorDialog::apply_search),
    m_in_event_handler (false),
    m_os (OS_none),
    m_new_line (true),
    m_in_exec (false), 
    m_in_breakpoint (false), 
    mp_exec_controller (0),
    mp_current_interpreter (0),
    m_continue (false),
    m_trace_count (0), m_current_stack_depth (-1), m_stop_stack_depth (-1),
    m_eval_context (-1),
    m_process_events_interval (0.0),
    m_window_closed (true),
    m_ntab (8), m_nindent (2), m_save_all_on_run (false), m_stop_on_exception (true), m_font_size (0)
{
  Ui::MacroEditorDialog::setupUi (this);

  connect (mp_root, SIGNAL (macro_changed (Macro *)), this, SLOT (macro_changed (Macro *)));
  connect (mp_root, SIGNAL (macro_deleted (Macro *)), this, SLOT (macro_deleted (Macro *)));

  m_categories = lay::Application::instance ()->macro_categories ();

  treeTab->clear ();

  for (size_t i = 0; i < m_categories.size (); ++i) {

    lay::MacroEditorTree *macro_tree = new lay::MacroEditorTree (treeTab, m_categories [i].first);
    m_macro_trees.push_back (macro_tree);

    treeTab->addTab(macro_tree, tl::to_qstring (m_categories [i].second));

    macro_tree->setup (this);

    macro_tree->setSortingEnabled (true);
    macro_tree->sortByColumn (0, Qt::AscendingOrder);
    macro_tree->setObjectName (tl::to_qstring (m_categories [i].first) + QString::fromUtf8 ("_tree"));

    macro_tree->setContextMenuPolicy (Qt::ActionsContextMenu);

    macro_tree->addAction (actionRefresh);
    QAction *s0 = new QAction (macro_tree);
    s0->setSeparator (true);
    macro_tree->addAction (s0);
    macro_tree->addAction (actionAddLocation);
    macro_tree->addAction (actionRemoveLocation);
    QAction *s1 = new QAction (macro_tree);
    s1->setSeparator (true);
    macro_tree->addAction (s1);
    macro_tree->addAction (actionNewFolder);
    QAction *s2 = new QAction (macro_tree);
    s2->setSeparator (true);
    macro_tree->addAction (s2);
    macro_tree->addAction (actionAddMacro);
    macro_tree->addAction (actionDelete);
    macro_tree->addAction (actionRename);
    macro_tree->addAction (actionImport);
    QAction *s3 = new QAction (macro_tree);
    s3->setSeparator (true);
    macro_tree->addAction (s3);
    macro_tree->addAction (actionSaveAll);
    macro_tree->addAction (actionSave);

    macro_tree->header ()->hide ();

    macro_tree->setItemDelegate (new EditRoleDelegate (macro_tree));

    connect (macro_tree, SIGNAL (macro_double_clicked (lay::Macro *)), this, SLOT (item_double_clicked (lay::Macro *)));
    connect (macro_tree, SIGNAL (move_macro (lay::Macro *, lay::MacroCollection *)), this, SLOT (move_macro (lay::Macro *, lay::MacroCollection *)));
    connect (macro_tree, SIGNAL (move_folder (lay::MacroCollection *, lay::MacroCollection *)), this, SLOT (move_folder (lay::MacroCollection *, lay::MacroCollection *)));

  }

  setObjectName (QString::fromAscii ("MacroEditorDialog"));

  QHBoxLayout *layout = new QHBoxLayout(consoleTextFrame);
  layout->setMargin (0);
  consoleTextFrame->setLayout(layout);
  mp_console_text = new TextEditWidget(consoleTextFrame);
  mp_console_text->setReadOnly(true);
  mp_console_text->setFont(consoleTextFrame->font());
  mp_console_text->setWordWrapMode(QTextOption::NoWrap);
  layout->addWidget(mp_console_text);

  m_stdout_format = mp_console_text->currentCharFormat();
  m_echo_format = m_stdout_format;
  m_echo_format.setForeground (QColor (0, 0, 255));
  m_stderr_format = m_stdout_format;
  m_stderr_format.setForeground (QColor (255, 0, 0));
  m_stderr_format.setFontWeight (QFont::Bold);

  input_field->setCompleter (0);

  connect (clear_button, SIGNAL (clicked ()), this, SLOT (clear_log ()));
  connect (input_field, SIGNAL (editTextChanged (const QString &)), this, SLOT (edit_text_changed (const QString &)));

  m_history_index = -1;

#if QT_VERSION >= 0x040500
  tabWidget->setMovable (true);
  tabWidget->setTabsClosable (true);
  connect (tabWidget, SIGNAL (tabCloseRequested (int)), this, SLOT (tab_close_requested (int)));
  closeButton->hide ();
  closeButtonSeparator->hide ();
#endif

  dbgOn->setEnabled (true);
  runButton->setEnabled (true);
  runThisButton->setEnabled (true);
  pauseButton->setEnabled (false);
  stopButton->setEnabled (false);
  singleStepButton->setEnabled (true);
  nextStepButton->setEnabled (true);
  runtimeFrame->hide ();

  watchList->setContextMenuPolicy (Qt::ActionsContextMenu);
  watchList->addAction (actionAddWatch);
  watchList->addAction (actionEditWatch);
  watchList->addAction (actionDeleteWatches);
  watchList->addAction (actionClearWatches);

  connect (actionAddWatch, SIGNAL (triggered ()), this, SLOT (add_watch ()));
  connect (actionAddWatch, SIGNAL (triggered ()), this, SLOT (add_watch ()));
  connect (actionEditWatch, SIGNAL (triggered ()), this, SLOT (edit_watch ()));
  connect (actionDeleteWatches, SIGNAL (triggered ()), this, SLOT (del_watches ()));
  connect (actionClearWatches, SIGNAL (triggered ()), this, SLOT (clear_watches ()));
  connect (actionRefresh, SIGNAL (triggered ()), this, SLOT (refresh ()));
  connect (actionAddLocation, SIGNAL (triggered ()), this, SLOT (add_location ()));
  connect (actionRemoveLocation, SIGNAL (triggered ()), this, SLOT (remove_location ()));
  connect (helpButton, SIGNAL (clicked ()), this, SLOT (help_button_clicked ()));
  connect (addButton, SIGNAL (clicked ()), this, SLOT (add_button_clicked ()));
  connect (actionAddMacro, SIGNAL (triggered ()), this, SLOT (add_button_clicked ()));
  connect (closeButton, SIGNAL (clicked ()), this, SLOT (close_button_clicked ()));
  connect (deleteButton, SIGNAL (clicked ()), this, SLOT (delete_button_clicked ()));
  connect (actionDelete, SIGNAL (triggered ()), this, SLOT (delete_button_clicked ()));
  connect (renameButton, SIGNAL (clicked ()), this, SLOT (rename_button_clicked ()));
  connect (actionRename, SIGNAL (triggered ()), this, SLOT (rename_button_clicked ()));
  connect (importButton, SIGNAL (clicked ()), this, SLOT (import_button_clicked ()));
  connect (actionImport, SIGNAL (triggered ()), this, SLOT (import_button_clicked ()));
  connect (newFolderButton, SIGNAL (clicked ()), this, SLOT (new_folder_button_clicked ()));
  connect (actionNewFolder, SIGNAL (triggered ()), this, SLOT (new_folder_button_clicked ()));
  connect (saveAllButton, SIGNAL (clicked ()), this, SLOT (save_all_button_clicked ()));
  connect (actionSaveAll, SIGNAL (triggered ()), this, SLOT (save_all_button_clicked ()));
  connect (saveButton, SIGNAL (clicked ()), this, SLOT (save_button_clicked ()));
  connect (actionSave, SIGNAL (triggered ()), this, SLOT (save_button_clicked ()));
  connect (dbgOn, SIGNAL (clicked (bool)), this, SLOT (set_debugging_on (bool)));
  connect (runButton, SIGNAL (clicked ()), this, SLOT (run_button_clicked ()));
  connect (runThisButton, SIGNAL (clicked ()), this, SLOT (run_this_button_clicked ()));
  connect (pauseButton, SIGNAL (clicked ()), this, SLOT (pause_button_clicked ()));
  connect (stopButton, SIGNAL (clicked ()), this, SLOT (stop_button_clicked ()));
  connect (breakpointButton, SIGNAL (clicked ()), this, SLOT (breakpoint_button_clicked ()));
  connect (clearBreakpointsButton, SIGNAL (clicked ()), this, SLOT (clear_breakpoints_button_clicked ()));
  connect (propertiesButton, SIGNAL (clicked ()), this, SLOT (properties_button_clicked ()));
  connect (setupButton, SIGNAL (clicked ()), this, SLOT (setup_button_clicked ()));
  connect (tabWidget, SIGNAL (currentChanged (int)), this, SLOT (current_tab_changed (int)));
  connect (callStack, SIGNAL (itemDoubleClicked (QListWidgetItem *)), this, SLOT (stack_element_double_clicked (QListWidgetItem *)));
  connect (singleStepButton, SIGNAL (clicked ()), this, SLOT (single_step_button_clicked ()));
  connect (nextStepButton, SIGNAL (clicked ()), this, SLOT (next_step_button_clicked ()));
  connect (searchEditBox, SIGNAL (returnPressed ()), this, SLOT (search_edited ()));
  connect (replaceModeButton, SIGNAL (clicked ()), this, SLOT (replace_mode_button_clicked ()));
  connect (replaceNextButton, SIGNAL (clicked ()), this, SLOT (replace_next_button_clicked ()));
  connect (findNextButton, SIGNAL (clicked ()), this, SLOT (find_next_button_clicked ()));
  connect (replaceAllButton, SIGNAL (clicked ()), this, SLOT (replace_all_button_clicked ()));
  connect (allVariables, SIGNAL (clicked (bool)), variableList, SLOT (set_show_all (bool)));

  splitter->setCollapsible (1, false);
  replaceFrame->hide ();

  tabWidget->clear ();

  //  add standard templates
  QResource res (QString::fromAscii (":/macro-templates/index.txt"));
  QByteArray data;
  if (res.isCompressed ()) {
    data = qUncompress ((const unsigned char *)res.data (), (int)res.size ());
  } else {
    data = QByteArray ((const char *)res.data (), (int)res.size ());
  }

  //  Read standard templates from :/macro-templates/x
  std::vector<std::string> lines = tl::split (std::string (data.constData (), data.size ()), "\n");
  std::string description_prefix;
  std::string category;
  for (std::vector<std::string>::const_iterator l = lines.begin (); l != lines.end (); ++l) {

    std::string ll = tl::trim (*l);
    if (! ll.empty () && ll [0] != '#') {

      if (ll [0] == '[') {

        size_t closing = ll.find ("]");
        if (closing != std::string::npos) {
          category = tl::trim (std::string (ll, 1, closing - 1));
        }

      } else if (ll [0] == ':') {

        description_prefix = tl::trim (std::string (ll, 1));

      } else {

        std::string description;
        size_t colon = ll.find (":");
        if (colon != std::string::npos) {
          description = tl::trim (std::string (ll, colon + 1));
          ll = tl::trim (std::string (ll, 0, colon));
        }

        std::string url = ":/macro-templates/" + ll;
        QResource res (tl::to_qstring (url));
        if (res.size () > 0) {

          QByteArray data;
          if (res.isCompressed ()) {
            data = qUncompress ((const unsigned char *)res.data (), (int)res.size ());
          } else {
            data = QByteArray ((const char *)res.data (), (int)res.size ());
          }

          Macro *m = new Macro ();
          try {

            m->rename (tl::to_string (QFileInfo (QUrl (tl::to_qstring (url)).path ()).baseName ()));
            m->load_from_string (std::string (data.constData (), data.size ()), url);
            if (! description.empty ()) {
              m->set_description (description_prefix + description);
            } else {
              m->set_description (description_prefix + m->description ());
            }
            m->set_readonly (true);
            if (! category.empty ()) {
              m->set_category (category);
            }
            m_macro_templates.push_back (m);

            if (tl::verbosity () >= 20) {
              tl::info << "Using macro template from " << url << " (with name " << m->name () << ")";
            }

          } catch (tl::Exception &ex) {
            delete m;
            tl::error << "Reading " << url << ": " << ex.msg ();
          }

        } else {
          tl::error << "Macro template resource " << url << " not found";
        }

      }

    }
  }

  //  scan macro templates
  for (std::vector<std::string>::const_iterator p = lay::Application::instance ()->klayout_path ().begin (); p != lay::Application::instance ()->klayout_path ().end (); ++p) {

    QDir dir (QDir (tl::to_qstring (*p)).filePath (tl::to_qstring ("macro-templates")));

    QStringList filters;
    filters << QString::fromAscii ("*.lym");
    filters << QString::fromAscii ("*.txt");
    filters << QString::fromAscii ("*.rb");
    filters << QString::fromAscii ("*.py");

    //  add the suffixes in the DSL interpreter declarations
    for (tl::Registrar<lay::MacroInterpreter>::iterator cls = tl::Registrar<lay::MacroInterpreter>::begin (); cls != tl::Registrar<lay::MacroInterpreter>::end (); ++cls) {
      if (! cls->suffix ().empty ()) {
        filters << tl::to_qstring ("*." + cls->suffix ());
      }
    }

    QStringList files = dir.entryList (filters, QDir::Files);
    for (QStringList::ConstIterator f = files.begin (); f != files.end (); ++f) {

      Macro *m = new Macro ();
      try {

        m->rename (tl::to_string (QFileInfo (*f).baseName ()));
        m->load_from (tl::to_string (dir.filePath (*f)));
        m->set_readonly (true);
        m_macro_templates.push_back (m);
        if (tl::verbosity () >= 20) {
          tl::info << "Using macro template from " << tl::to_string (dir.filePath (*f)) << " (with name " << m->name () << ")";
        }

      } catch (...) {
        delete m;
      }

    }

  }

  //  finally fetch the templates of the DSL interpreters
  for (tl::Registrar<lay::MacroInterpreter>::iterator cls = tl::Registrar<lay::MacroInterpreter>::begin (); cls != tl::Registrar<lay::MacroInterpreter>::end (); ++cls) {
    size_t n = m_macro_templates.size ();
    cls->get_templates (m_macro_templates);
    if (tl::verbosity () >= 20) {
      for (std::vector<lay::Macro *>::const_iterator t = m_macro_templates.begin () + n; t != m_macro_templates.end (); ++t) {
        tl::info << "Using DSL macro template for " << (*t)->dsl_interpreter () << " with name " << (*t)->name ();
      }
    }
  }

  QTimer *timer = new QTimer (this);
  connect (timer, SIGNAL (timeout ()), this, SLOT (commit ()));
  timer->start (500);

  mainHSplitter->setStretchFactor (1, 1);

  //  Install a global event filter that allows us to lock out the application while a script is running
  //  or we are inside a breakpoint and other modifications.
  QCoreApplication::instance ()->installEventFilter (this);

  if (! s_macro_editor_instance) {
    s_macro_editor_instance = this;
  }
}

MacroEditorDialog::~MacroEditorDialog ()
{
  if (s_macro_editor_instance == this) {
    s_macro_editor_instance = 0;
  }

  for (std::vector<lay::Macro *>::iterator t = m_macro_templates.begin (); t != m_macro_templates.end (); ++t) {
    delete *t;
  }
  m_macro_templates.clear ();
}

MacroEditorDialog *
MacroEditorDialog::instance () 
{
  return s_macro_editor_instance;
}

void
MacroEditorDialog::select_category (const std::string &cat)
{
  for (size_t i = 0; i < m_categories.size (); ++i) {
    if (m_categories [i].first == cat) {
      treeTab->setCurrentIndex (int (i));
    }
  }
}

void
MacroEditorDialog::clear_log ()
{
  mp_console_text->clear ();
  m_new_line = true;
  m_os = OS_none;
}

void 
MacroEditorDialog::show (const std::string &cat, bool force_add)
{
BEGIN_PROTECTED

  if (isMinimized ()) {
    QDialog::showNormal ();
  } else {
    QDialog::show ();
  }
  activateWindow ();
  raise ();

  if (m_first_show) {

    m_first_show = false;

    if (! cat.empty ()) {
      select_category (cat);
    }

    lay::MacroEditorTree *ct = current_macro_tree ();
    MacroCollection *collection = ct->current_macro_collection ();

    //  Select the first writeable collection if none is selected
    if (! collection || collection->is_readonly ()) {
      for (lay::MacroCollection::const_child_iterator c = mp_root->begin_children (); c != mp_root->end_children (); ++c) {
        if (c->second->category () == ct->category () && ! c->second->is_readonly ()) {
          ct->set_current (c->second);
          collection = c->second;
          break;
        }
      }
    }

    if (collection && (force_add || (collection->begin () == collection->end () && collection->begin_children () == collection->end_children ()))) {
      lay::Macro *m = new_macro ();
      if (force_add && m) {
        set_run_macro (m);
      }
    }

    if (cat == "drc") {
      TipDialog td (this, lay::MainWindow::instance (), 
                    tl::to_string (QObject::tr ("<html><body>To get started with the DRC feature, read the documentation provided: <a href=\"int:/manual/drc.xml\">Design Rule Checks (DRC)</a>.</body></html>")), 
                    "macro-editor-drc-tips");
      td.exec_dialog ();
    } else {
      TipDialog td (this, lay::MainWindow::instance (), 
                    tl::to_string (QObject::tr ("<html><body>To get started with the macro development feature, read the documentation provided: <a href=\"int:/about/macro_editor.xml\">About Macro Development</a>.</body></html>")), 
                    "macro-editor-basic-tips");
      td.exec_dialog ();
    }

  } else if (force_add) {

    if (! cat.empty ()) {
      select_category (cat);
    }

    lay::Macro *m = new_macro ();
    if (force_add && m) {
      set_run_macro (m);
    }

  }

END_PROTECTED
}

lay::MacroEditorTree *
MacroEditorDialog::current_macro_tree ()
{
  lay::MacroEditorTree *t = dynamic_cast<lay::MacroEditorTree *> (treeTab->currentWidget ());
  tl_assert (t != 0);
  return t;
}

void 
MacroEditorDialog::showEvent (QShowEvent *)
{
  if (! m_window_closed) {
    //  show after showNormal
    return;
  }

  m_window_closed = false;

  //  read configuration
  std::string styles;
  if (MainWindow::instance ()->config_get (cfg_macro_editor_styles, styles)) {
    m_highlighters.load (styles);
  }
  MainWindow::instance ()->config_get (cfg_macro_editor_save_all_on_run, m_save_all_on_run);
  MainWindow::instance ()->config_get (cfg_macro_editor_stop_on_exception, m_stop_on_exception);
  MainWindow::instance ()->config_get (cfg_macro_editor_font_family, m_font_family);
  MainWindow::instance ()->config_get (cfg_macro_editor_font_size, m_font_size);
  MainWindow::instance ()->config_get (cfg_macro_editor_tab_width, m_ntab);
  MainWindow::instance ()->config_get (cfg_macro_editor_indent, m_nindent);
  MainWindow::instance ()->config_get (cfg_macro_editor_debugging_enabled, m_debugging_on);

  std::string ws;
  MainWindow::instance ()->config_get (cfg_macro_editor_window_state, ws);
  lay::restore_dialog_state (this, ws);

  input_field->clear ();

  try {
    std::string hi;
    MainWindow::instance ()->config_get (cfg_macro_editor_console_mru, hi);
    tl::Extractor ex (hi.c_str ());
    while (! ex.at_end ()) {
      std::string h;
      ex.read_word_or_quoted (h);
      ex.test (";");
      input_field->addItem (tl::to_qstring (h));
    }
  } catch (...) { }
  m_history_index = -1;
  input_field->clearEditText ();

  lay::Application::instance ()->ruby_interpreter ().push_console (this);
  if (m_debugging_on) {
    lay::Application::instance ()->ruby_interpreter ().push_exec_handler (this);
  }
  lay::Application::instance ()->python_interpreter ().push_console (this);
  if (m_debugging_on) {
    lay::Application::instance ()->python_interpreter ().push_exec_handler (this);
  }

  std::string ci;
  MainWindow::instance ()->config_get (cfg_macro_editor_console_interpreter, ci);
  if (ci == "ruby") {
    pythonLangSel->setChecked (false);
    rubyLangSel->setChecked (true);
  } else if (ci == "python") {
    pythonLangSel->setChecked (true);
    rubyLangSel->setChecked (false);
  }

  try {

    m_watch_expressions.clear ();

    std::string we;
    MainWindow::instance ()->config_get (cfg_macro_editor_watch_expressions, we);
    tl::Extractor ex (we.c_str ());
    while (! ex.at_end ()) {

      std::string ip, expr;
      ex.read_word (ip);
      ex.test (":");
      ex.read_word_or_quoted (expr);
      ex.test (";");

      if (ip == "ruby") {
        m_watch_expressions.push_back (std::make_pair (&lay::Application::instance ()->ruby_interpreter (), expr));
      } else if (ip == "python") {
        m_watch_expressions.push_back (std::make_pair (&lay::Application::instance ()->python_interpreter (), expr));
      }

    }

  } catch (...) { }

  try {
    std::string om;
    MainWindow::instance ()->config_get (cfg_macro_editor_open_macros, om);
    tl::Extractor ex (om.c_str ());
    while (! ex.at_end ()) {
      std::string h;
      ex.read_word_or_quoted (h);
      ex.test (";");
      //  this will open an editor for the macro with path h
      editor_for_file (h); 
    }
  } catch (...) { }

  std::string am;
  MainWindow::instance ()->config_get (cfg_macro_editor_active_macro, am);
  if (! am.empty ()) {
    lay::Macro *macro = mp_root->find_macro (am);
    if (macro) {
      set_run_macro (macro);
    }
  }

  dbgOn->setChecked (m_debugging_on);

  std::string cm;
  MainWindow::instance ()->config_get (cfg_macro_editor_current_macro, cm);
  if (! cm.empty ()) {
    //  this will make that macro the current one
    editor_for_file (cm);
  }

  for (std::map <Macro *, MacroEditorPage *>::const_iterator page = m_tab_widgets.begin (); page != m_tab_widgets.end (); ++page) {
    page->second->set_debugging_on (m_debugging_on);
  }
}

void
MacroEditorDialog::reject ()
{
  closeEvent (0);
  QDialog::reject ();
}
  
void
MacroEditorDialog::accept ()
{
  closeEvent (0);
  QDialog::accept ();
}
  
void 
MacroEditorDialog::closeEvent (QCloseEvent *)
{
  //  save the debugging enabled state
  MainWindow::instance ()->config_set (cfg_macro_editor_debugging_enabled, m_debugging_on);

  //  save the window state
  MainWindow::instance ()->config_set (cfg_macro_editor_window_state, lay::save_dialog_state (this));

  //  save the console history (at maximum the last 200 entries)
  std::string hi;
  for (int i = std::max (0, input_field->count () - 200); i < input_field->count (); ++i) {
    if (! hi.empty ()) {
      hi += ";";
    }
    hi += tl::to_quoted_string (tl::to_string (input_field->itemText (i)));
  }
  MainWindow::instance ()->config_set (cfg_macro_editor_console_mru, hi);

  //  save the open macro list
  std::string om;
  for (int i = 0; i < tabWidget->count (); ++i) {
    MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->widget (i));
    if (page && page->macro ()) {
      if (! om.empty ()) {
        om += ";";
      }
      om += tl::to_quoted_string (page->macro ()->path ());
    }
  }
  MainWindow::instance ()->config_set (cfg_macro_editor_open_macros, om);

  //  save the watch expressions
  std::string we;
  for (std::vector<std::pair<gsi::Interpreter *, std::string> >::const_iterator i = m_watch_expressions.begin (); i != m_watch_expressions.end (); ++i) {
    if (! om.empty ()) {
      om += ";";
    }
    if (i->first == &lay::Application::instance ()->ruby_interpreter ()) {
      we += "ruby";
    } else if (i->first == &lay::Application::instance ()->python_interpreter ()) {
      we += "python";
    }
    we += ":";
    we += tl::to_quoted_string (i->second);
  }
  MainWindow::instance ()->config_set (cfg_macro_editor_watch_expressions, we);

  //  save the active (run) macro
  MainWindow::instance ()->config_set (cfg_macro_editor_active_macro, mp_run_macro ? mp_run_macro->path () : std::string ());

  //  save the current macro
  MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->currentWidget ());
  std::string cm = page && page->macro () ? page->macro ()->path () : std::string ();
  MainWindow::instance ()->config_set (cfg_macro_editor_current_macro, cm);

  //  save the current interpreter in the console
  std::string ci;
  if (rubyLangSel->isChecked ()) {
    ci = "ruby";
  } else if (pythonLangSel->isChecked ()) {
    ci = "python";
  }
  MainWindow::instance ()->config_set (cfg_macro_editor_console_interpreter, ci);

  //  stop execution when the window is closed
  m_in_exec = false;
  m_window_closed = true;

  lay::Application::instance ()->ruby_interpreter ().remove_console (this);
  lay::Application::instance ()->ruby_interpreter ().remove_exec_handler (this);
  lay::Application::instance ()->python_interpreter ().remove_console (this);
  lay::Application::instance ()->python_interpreter ().remove_exec_handler (this);
}

void 
MacroEditorDialog::set_debugging_on (bool on)
{
  if (m_debugging_on != on) {

    m_debugging_on = on;

    for (std::map <Macro *, MacroEditorPage *>::const_iterator page = m_tab_widgets.begin (); page != m_tab_widgets.end (); ++page) {
      page->second->set_debugging_on (m_debugging_on);
    }

    if (isVisible ()) {
      if (on) {
        lay::Application::instance ()->ruby_interpreter ().push_exec_handler (this);
        lay::Application::instance ()->python_interpreter ().push_exec_handler (this);
      } else {
        lay::Application::instance ()->ruby_interpreter ().remove_exec_handler (this);
        lay::Application::instance ()->python_interpreter ().remove_exec_handler (this);
      }
    }

  }
}

void
MacroEditorDialog::process_events (QEventLoop::ProcessEventsFlags flags)
{
  if (lay::Application::instance ()) {
    //  disable execution of deferred methods to avoid undesired execution of 
    //  code while we are inside a Ruby callback through the silent mode
    bool last_processing = m_in_processing;
    m_in_processing = true;
    lay::Application::instance ()->process_events (flags, true /*silent*/);
    m_in_processing = last_processing;
  }
}

static bool  
any_modified(MacroCollection *parent)
{
  for (MacroCollection::child_iterator c = parent->begin_children (); c != parent->end_children (); ++c) {
    if (any_modified (c->second)) {
      return true;
    }
  }
  for (MacroCollection::iterator c = parent->begin (); c != parent->end (); ++c) {
    if (c->second->is_modified ()) {
      return true;
    }
  }
  return false;
}

bool
MacroEditorDialog::can_exit ()
{
  if (any_modified (mp_root)) {
    if (QMessageBox::question (this, QObject::tr ("Save Macros"), 
                                     QObject::tr ("Some macros are modified. Do you want to save them?"),
                                     QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
      save_all_button_clicked ();
    }
  }

  //  simulate close event so we do a clean shut down and save the console MRU list for example
  if (isVisible ()) {
    closeEvent (0);
  }

  return true;
}

void 
MacroEditorDialog::edit_text_changed (const QString &text)
{
  m_history_index = -1;
  if (! m_in_event_handler) {
    m_edit_text = text;
  }
}

void
MacroEditorDialog::execute (const QString &cmd)
{
  try {

    write_str ("> ", OS_echo);
    write_str (tl::to_string (cmd).c_str (), OS_echo);
    write_str ("\n", OS_echo);

    gsi::Interpreter *interpreter = 0;
    if (rubyLangSel->isChecked ()) {
      interpreter = &lay::Application::instance ()->ruby_interpreter ();
    } else if (pythonLangSel->isChecked ()) {
      interpreter = &lay::Application::instance ()->python_interpreter ();
    }

    if (interpreter) {
      int context = m_in_breakpoint ? m_eval_context : -1;
      interpreter->eval_string_and_print (tl::to_string (cmd).c_str (), 0, 1, context);
    }

    update_inspected ();

  } catch (gsi::RuntimeError &ex) {

    handle_error (ex);
    write_str (ex.msg ().c_str (), OS_stderr);
    write_str ("\n", OS_stderr);

  } catch (tl::CancelException &ex) {

    //  ignore CancelException
    
  } catch (tl::Exception &ex) {

    write_str (ex.msg ().c_str (), OS_stderr);
    write_str ("\n", OS_stderr);

  } catch (std::runtime_error &ex) {

    write_str (ex.what (), OS_stderr);
    write_str ("\n", OS_stderr);

  } catch (...) {
    write_str ("Unknown error\n", OS_stderr);
  }
}

void 
MacroEditorDialog::update_inspected ()
{
  if (! m_in_breakpoint || ! m_in_exec || ! mp_current_interpreter) {
    variableList->set_inspector (0);
  } else {

    std::auto_ptr<gsi::Inspector> ci (mp_current_interpreter->inspector (m_eval_context));
    variableListFrame->setVisible (ci.get () != 0);
    variableList->set_inspector (ci.release ());

    update_watches ();

  }
}

void 
MacroEditorDialog::update_watches ()
{
  std::set <std::string> expressions;
  for (std::vector<std::pair<gsi::Interpreter *, std::string> >::const_iterator w = m_watch_expressions.begin (); w != m_watch_expressions.end (); ++w) {
    expressions.insert (w->second);
  }

  for (int i = 0; i < watchList->topLevelItemCount (); ) {
    if (expressions.find (tl::to_string (watchList->topLevelItem (i)->text (0))) == expressions.end ()) {
      delete watchList->takeTopLevelItem (i);
    } else {
      ++i;
    }
  }

  int i = 0;
  for (std::vector<std::pair<gsi::Interpreter *, std::string> >::const_iterator w = m_watch_expressions.begin (); w != m_watch_expressions.end (); ++w, ++i) {

    QString value;
    if (w->first != mp_current_interpreter) {
      value = tr ("(inactive)");
    } else {
      try {
        value = pretty_print (w->first->eval_expr (w->second.c_str (), 0, 1, m_eval_context));
      } catch (gsi::RuntimeError &ex) {
        value = tr ("Error") + QString::fromUtf8 (": ") + tl::to_qstring (ex.basic_msg ());
      } catch (tl::Exception &ex) {
        value = tr ("Error") + QString::fromUtf8 (": ") + tl::to_qstring (ex.msg ());
      } catch (...) {
        value = tr ("Error (unspecific)");
      }
    }

    if (i == watchList->topLevelItemCount ()) {

      QTreeWidgetItem *item = new QTreeWidgetItem ();
      item->setText (0, tl::to_qstring (w->second));
      QFont f (item->font (0));
      f.setWeight (QFont::Bold);
      item->setFont (0, f);
      item->setText (1, value);
      item->setToolTip (1, value);

      watchList->addTopLevelItem (item);

    } else {

      QTreeWidgetItem *item = watchList->topLevelItem (i);

      item->setText (0, tl::to_qstring (w->second));

      if (item->text (1) != value) {
        QFont f (item->font (1));
        f.setWeight (QFont::Bold);
        item->setFont (1, f);
        item->setText (1, value);
      } else {
        QFont f (item->font (1));
        f.setWeight (QFont::Normal);
        item->setFont (1, f);
      }

    }

    watchList->topLevelItem (i)->setDisabled (w->first != mp_current_interpreter);
    
  }
}

static QString s_watch_expr;

void
MacroEditorDialog::edit_watch ()
{
  int index = watchList->indexOfTopLevelItem (watchList->currentItem ());
  if (index >= 0) {

    bool ok = false;
    QString we = QInputDialog::getText (this, tr ("Add Watch Expressions"), tr ("Enter expression to evaluate:"), QLineEdit::Normal, watchList->currentItem ()->text (0), &ok);
    if (ok && ! we.isEmpty()) {
      s_watch_expr = we;
      m_watch_expressions [index].second = tl::to_string (we);
      update_watches ();
    }

  }
}

void
MacroEditorDialog::add_watch ()
{
  if (mp_current_interpreter) {

    bool ok = false;
    QString we = QInputDialog::getText (this, tr ("Add Watch Expressions"), tr ("Enter expression to evaluate:"), QLineEdit::Normal, s_watch_expr, &ok);
    if (ok && ! we.isEmpty()) {
      s_watch_expr = we;
      m_watch_expressions.push_back (std::make_pair (mp_current_interpreter, tl::to_string (we)));
    }

    update_watches ();

    watchList->setCurrentItem (watchList->topLevelItem (int (m_watch_expressions.size ()) - 1));

  }
}

void
MacroEditorDialog::del_watches ()
{
  for (int i = 0; i < watchList->topLevelItemCount (); ) {
    if (watchList->topLevelItem (i)->isSelected ()) {
      delete watchList->takeTopLevelItem (i);
      m_watch_expressions.erase (m_watch_expressions.begin () + i);
    } else {
      ++i;
    }
  }
}

void
MacroEditorDialog::clear_watches ()
{
  watchList->clear ();
  m_watch_expressions.clear ();
}

bool 
MacroEditorDialog::eventFilter (QObject *obj, QEvent *event)
{
  //  do not handle events that are not targeted towards widgets
  QWidget *rec = dynamic_cast <QWidget *> (obj);
  if (! rec) {
    return false;
  }

  //  do not handle events if a modal widget is active (i.e. a message box)
  if (QApplication::activeModalWidget () && QApplication::activeModalWidget () != this) {
    return false;
  }

  if (m_in_processing && (m_in_breakpoint || m_in_exec) && (dynamic_cast <QInputEvent *> (event) != 0 || dynamic_cast <QPaintEvent *> (event) != 0)) {
    //  In breakpoint or execution mode and while processing the events from the debugger, 
    //  ignore all input or paint events targeted to widgets which are not children of this or the assistant dialog.
    //  Ignoring the paint event is required because otherwise a repaint action would be triggered on a layout which 
    //  is potentially unstable or inconsistent.
    QObject *rec = obj;
    while (rec && (rec != this && rec != lay::MainWindow::instance ()->assistant ())) {
      rec = rec->parent ();
    }
    if (! rec) {
      //  TODO: reschedule the paint events (?)
      return true;
    }
  } else if (! m_in_processing && m_in_exec) {
    //  While no explicit event processing is in progress and we are executing, this is an indication that
    //  "real" events are processed. In that case, we can postpone excplit processing. This avoids interference
    //  with GUI code run in the debugger.
    m_last_process_events = tl::Clock::current ();
  }

  if (obj == input_field && event->type() == QEvent::KeyPress) {

    QKeyEvent *key_event = dynamic_cast<QKeyEvent *> (event);
    if (key_event && key_event->key () == Qt::Key_Return) {

      QString cmd = input_field->currentText ();
      if (! cmd.isEmpty ()) {

        if (m_history_index >= 0 && m_history_index < input_field->count () && cmd == input_field->itemText (m_history_index)) {
          input_field->removeItem (m_history_index);
        } 
        input_field->addItem (cmd);

        execute (cmd);

        input_field->clearEditText ();
        m_edit_text = QString ();
        m_history_index = -1;

      }

      return true;

    } else if (key_event && key_event->key () == Qt::Key_Up) {

      m_in_event_handler = true; // prevent setting of m_edit_text

      int hi = m_history_index;
      if (hi < 0) {
        if (input_field->count () > 0) {
          hi = input_field->count () - 1;
          input_field->setCurrentIndex (hi);
        }
      } else if (hi > 0 && hi <= input_field->count ()) {
        --hi;
        input_field->setCurrentIndex (hi);
      }
        
      m_in_event_handler = false;
      m_history_index = hi;

      return true;

    } else if (key_event && key_event->key () == Qt::Key_Down) {

      m_in_event_handler = true; // prevent setting of m_edit_text

      int hi = m_history_index;
      if (hi < 0) {
        if (input_field->count () > 0) {
          hi = input_field->count () - 1;
          input_field->setCurrentIndex (hi);
        }
      } else if (hi < input_field->count () - 1) {
        ++hi;
        input_field->setCurrentIndex (hi);
      } else {
        hi = input_field->count ();
        input_field->setEditText (m_edit_text);
      }
        
      m_in_event_handler = false;
      m_history_index = hi;

      return true;

    }

  } 

  return QDialog::eventFilter(obj, event);
}

void
MacroEditorDialog::flush ()
{
  if (! m_new_line) {
    //  insert a new line if the stream changes ..
    write_str ("\n", m_os);
  }
}

void 
MacroEditorDialog::write_str (const char *text, output_stream os)
{
  if (! mp_console_text->textCursor ().atEnd ()) {
    QTextCursor c = mp_console_text->textCursor ();
    c.movePosition (QTextCursor::End);
    mp_console_text->setTextCursor (c);
  }

  if (m_os != OS_none && os != m_os) {
    //  flush if the stream changes ..
    flush ();
  }

  if (m_os != os) {
    if (os == OS_stdout) {
      mp_console_text->setCurrentCharFormat(m_stdout_format);
    } else if (os == OS_echo) {
      mp_console_text->setCurrentCharFormat(m_echo_format);
    } else if (os == OS_stderr) {
      mp_console_text->setCurrentCharFormat(m_stderr_format);
    } 
  }

  m_os = os;

  for (const char *t = text; *t; ) {

    const char *t0 = t;
    for ( ; *t && *t != '\n'; ++t)
      ;

    mp_console_text->insertPlainText (QString::fromUtf8 (t0, t - t0));

    if (*t == '\n') {
      ++t;
      //  new line: terminate line
      mp_console_text->insertPlainText (QString::fromUtf8 ("\n"));
      m_new_line = true;
    } else {
      m_new_line = false;
    }

  }

  md_update_console_text ();
}

void
MacroEditorDialog::update_console_text ()
{
  mp_console_text->ensureCursorVisible ();
}

void
MacroEditorDialog::commit ()
{
  for (std::map <Macro *, MacroEditorPage *>::const_iterator page = m_tab_widgets.begin (); page != m_tab_widgets.end (); ++page) {
    if (page->second->is_modified ()) {
      page->second->commit ();
    }
  }
}

void
MacroEditorDialog::macro_deleted (lay::Macro *macro)
{
  if (mp_run_macro == macro) {
    mp_run_macro = 0;
  }

  std::map <Macro *, MacroEditorPage *>::iterator page = m_tab_widgets.find (macro);
  if (page != m_tab_widgets.end ()) {
    page->second->connect_macro (0);
    tabWidget->blockSignals (true); // blockSignals prevents a reentrant call into set_current of the tree
    tabWidget->removeTab (tabWidget->indexOf (page->second));
    tabWidget->blockSignals (false);
    delete page->second;
    m_tab_widgets.erase (page);
  }
}

void
MacroEditorDialog::macro_changed (lay::Macro *macro)
{
  std::map <Macro *, MacroEditorPage *>::iterator page = m_tab_widgets.find (macro);
  if (page != m_tab_widgets.end ()) {
    int index = tabWidget->indexOf (page->second);
    QString tt = tl::to_qstring (macro->summary ());
    QString title = tl::to_qstring (macro->name ());
    if (tabWidget->tabToolTip (index) != tt) {
      tabWidget->setTabToolTip (index, tt);
    }
    if (tabWidget->tabText (index) != title) {
      tabWidget->setTabText (index, title);
    }
  }
}

void 
MacroEditorDialog::current_tab_changed (int index)
{
  MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->widget (index));
  if (page) {
    int tab_index = 0;
    for (std::vector<lay::MacroEditorTree *>::const_iterator mt = m_macro_trees.begin (); mt != m_macro_trees.end (); ++mt, ++tab_index) {
      if ((*mt)->set_current (page->macro ())) {
        treeTab->setCurrentIndex (tab_index);
        break;
      }
    }
  }

  //  clear the search
  searchEditBox->clear ();
  apply_search ();

  update_ui_to_run_mode ();
}

lay::Macro *MacroEditorDialog::create_macro_here(const char *prefix)
{
  lay::MacroEditorTree *mt = current_macro_tree ();
  MacroCollection *collection = mt->current_macro_collection ();
  if (! collection) {
    Macro *m = mt->current_macro ();
    if (m) {
      collection = m->parent ();
    }
  }

  if (! collection || collection->is_readonly ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("Cannot add a macro here - the folder is read-only")));
  } 
  return collection->create (prefix);
}

void 
MacroEditorDialog::move_macro (lay::Macro *source, lay::MacroCollection *target)
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  if (source->parent () != target) {

    lay::Macro *m = target->create (source->name ().c_str (), source->format ());
    m->assign (*source);
    m->set_readonly (false);
    m->save ();

    std::map <Macro *, MacroEditorPage *>::iterator page = m_tab_widgets.find (source);
    if (page != m_tab_widgets.end ()) {
      MacroEditorPage *w = page->second;
      w->connect_macro (m);
      m_tab_widgets.erase (page);
      m_tab_widgets.insert (std::make_pair (m, w));
      tabWidget->setTabToolTip (tabWidget->indexOf (w), tl::to_qstring (m->summary ()));
      tabWidget->setTabText (tabWidget->indexOf (w), tl::to_qstring (m->name ()));
    }

    if (! source->is_readonly ()) {
      MacroCollection *collection = source->parent ();
      if (collection && ! collection->is_readonly ()) {
        if (source->del ()) {
          collection->erase (source);
        }
      }
    }

    for (std::vector<lay::MacroEditorTree *>::const_iterator mt = m_macro_trees.begin (); mt != m_macro_trees.end (); ++mt) {
      (*mt)->set_current (m);
    }

  }

END_PROTECTED
}

void  
MacroEditorDialog::move_subfolder (lay::MacroCollection *source, lay::MacroCollection *target)
{
  lay::MacroCollection *mt = target->create_folder (source->name ().c_str ());
  if (! mt) {
    return;
  }

  std::vector <MacroCollection::iterator> m_del;

  for (MacroCollection::iterator mm = source->begin (); mm != source->end (); ++mm) {

    lay::Macro *m = mt->create (mm->second->name ().c_str ());
    if (!m) {
      continue;
    }

    m->assign (*mm->second);
    m->set_readonly (false);
    m->save ();

    std::map <Macro *, MacroEditorPage *>::iterator page = m_tab_widgets.find (mm->second);
    if (page != m_tab_widgets.end ()) {
      MacroEditorPage *w = page->second;
      w->connect_macro (m);
      m_tab_widgets.erase (page);
      m_tab_widgets.insert (std::make_pair (m, w));
      tabWidget->setTabToolTip (tabWidget->indexOf (w), tl::to_qstring (m->summary ()));
      tabWidget->setTabText (tabWidget->indexOf (w), tl::to_qstring (m->name ()));
    }

    if (! mm->second->is_readonly ()) {
      if (mm->second->del ()) {
        m_del.push_back (mm);
      }
    }
  }

  for (std::vector <MacroCollection::iterator>::const_iterator d = m_del.begin (); d != m_del.end (); ++d) {
    source->erase (*d);
  }

  std::vector <MacroCollection::child_iterator> mc_del;

  for (MacroCollection::child_iterator m = source->begin_children (); m != source->end_children (); ++m) {
    move_subfolder (m->second, mt);
    if (! m->second->is_readonly ()) {
      if (m->second->del ()) {
        mc_del.push_back (m);
      }
    }
  }

  for (std::vector <MacroCollection::child_iterator>::const_iterator d = mc_del.begin (); d != mc_del.end (); ++d) {
    source->erase (*d);
  }
}

void 
MacroEditorDialog::move_folder (lay::MacroCollection *source, lay::MacroCollection *target)
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  if (source->parent () != target) {

    move_subfolder (source, target);
    if (source->parent () && ! source->is_readonly ()) {
      if (source->del ()) {
        source->parent ()->erase (source);
      }
    }

  }

END_PROTECTED
}

void  
MacroEditorDialog::replace_mode_button_clicked ()
{
  if (replaceFrame->isVisible ()) {
    replaceFrame->hide ();
    replaceModeButton->setArrowType (Qt::RightArrow);
  } else {
    replaceFrame->show ();
    replaceText->setFocus ();
    replaceModeButton->setArrowType (Qt::LeftArrow);
  }
}

void  
MacroEditorDialog::find_next_button_clicked ()
{
  MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->currentWidget ());
  if (! page) {
    return;
  }

  apply_search (true);

  page->find_next ();
}

void  
MacroEditorDialog::replace_next_button_clicked ()
{
  MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->currentWidget ());
  if (! page) {
    return;
  }

  apply_search (true);

  page->replace_and_find_next (replaceText->text ());
}

void  
MacroEditorDialog::replace_all_button_clicked ()
{
  MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->currentWidget ());
  if (! page) {
    return;
  }

  apply_search (true);

  if (searchEditBox->text ().size () > 0) {
    page->set_search (QRegExp (searchEditBox->text (), Qt::CaseSensitive, regExpCheckBox->isChecked () ? QRegExp::RegExp : QRegExp::FixedString));
  } else {
    //  this is really a "null" regexp:
    page->set_search (QRegExp ());
  }

  page->replace_all (replaceText->text ());
}

void 
MacroEditorDialog::search_edited ()
{
  //  since we want to move the focus to the text field, we have to do this in the deferred method
  //  (this method is called from an event handler and setFocus does not have an effect then)
  md_apply_search ();
}

void
MacroEditorDialog::apply_search (bool if_needed)
{
  MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->currentWidget ());
  if (! page) {
    return;
  }

  if (searchEditBox->text ().size () > 0) {
    QRegExp re (searchEditBox->text (), Qt::CaseSensitive, regExpCheckBox->isChecked () ? QRegExp::RegExp : QRegExp::FixedString);
    if (! if_needed || page->get_search () != re) {
      page->set_search (re);
    }
  } else {
    if (! if_needed || page->get_search () != QRegExp ()) {
      //  this is really a "null" regexp:
      page->set_search (QRegExp ());
    }
  }
}

void  
MacroEditorDialog::save_button_clicked ()
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  Macro *m = current_macro_tree ()->current_macro ();
  if (m) {
    m->save ();
  } else if (tabWidget->currentWidget ()) {
    MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->currentWidget ());
    if (page && page->macro ()) {
      page->macro ()->save ();
    }
  }
   
END_PROTECTED
}

void  
MacroEditorDialog::setup_button_clicked ()
{
  if (m_in_exec) {
    return;
  }

  //  fill data

  lay::MacroEditorSetupDialogData data;
  data.tab_width = m_ntab;
  data.indent = m_nindent;
  data.save_all_on_run = m_save_all_on_run;
  data.stop_on_exception = m_stop_on_exception;
  data.font_family = m_font_family;
  data.font_size = m_font_size;

  if (m_highlighters.basic_attributes ()) {
    data.basic_attributes.assign (*m_highlighters.basic_attributes ());
  }
  for (MacroEditorHighlighters::const_iterator a = m_highlighters.begin (); a != m_highlighters.end (); ++a) {
    data.specific_attributes.push_back (std::make_pair (a->first, GenericSyntaxHighlighterAttributes (& data.basic_attributes)));
    data.specific_attributes.back ().second.assign (a->second);
  }
  
  lay::MacroEditorSetupDialog dialog (this);
  if (dialog.exec (data)) {

    m_ntab = data.tab_width;
    m_nindent = data.indent;
    m_stop_on_exception = data.stop_on_exception;
    m_font_family = data.font_family;
    m_font_size = data.font_size;

    if (m_highlighters.basic_attributes ()) {
      m_highlighters.basic_attributes ()->assign (data.basic_attributes);
    }

    for (MacroEditorHighlighters::iterator a = m_highlighters.begin (); a != m_highlighters.end (); ++a) {
      for (std::vector< std::pair<std::string, GenericSyntaxHighlighterAttributes> >::const_iterator i = data.specific_attributes.begin (); i != data.specific_attributes.end (); ++i) {
        if (i->first == a->first) {
          a->second.assign (i->second);
          break;
        }
      }
    }

    m_save_all_on_run = data.save_all_on_run;

    for (std::map<Macro *, MacroEditorPage *>::const_iterator f = m_tab_widgets.begin (); f != m_tab_widgets.end (); ++f) {
      f->second->set_ntab (m_ntab);
      f->second->set_nindent (m_nindent);
      f->second->apply_attributes ();
      f->second->set_font (m_font_family, m_font_size);
    }

    //  write configuration
    MainWindow::instance ()->config_set (cfg_macro_editor_styles, m_highlighters.to_string ());
    MainWindow::instance ()->config_set (cfg_macro_editor_save_all_on_run, m_save_all_on_run);
    MainWindow::instance ()->config_set (cfg_macro_editor_stop_on_exception, m_stop_on_exception);
    MainWindow::instance ()->config_set (cfg_macro_editor_tab_width, m_ntab);
    MainWindow::instance ()->config_set (cfg_macro_editor_indent, m_nindent);
    MainWindow::instance ()->config_set (cfg_macro_editor_font_family, m_font_family);
    MainWindow::instance ()->config_set (cfg_macro_editor_font_size, m_font_size);
    MainWindow::instance ()->config_end ();

  }
}

void  
MacroEditorDialog::properties_button_clicked ()
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  if (! tabWidget->currentWidget ()) {
    return;
  }

  MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->currentWidget ());
  if (! page || ! page->macro ()) {
    return;
  }

  Macro *macro = page->macro ();
  if (macro->format () == lay::Macro::PlainTextWithHashAnnotationsFormat) {
    page->commit ();
  }

  lay::MacroPropertiesDialog dia (this);

  if (dia.exec (macro)) {
    macro->sync_text_with_properties ();
  }

END_PROTECTED
}

void 
MacroEditorDialog::help_requested(const QString &s)
{
  lay::MainWindow::instance ()->show_assistant_topic (tl::to_string (s));
}

void 
MacroEditorDialog::help_button_clicked()
{
  lay::MainWindow::instance ()->show_assistant_url ("int:/code/index.xml");
}

void 
MacroEditorDialog::add_button_clicked()
{
BEGIN_PROTECTED
  new_macro ();
END_PROTECTED
}

lay::Macro *
MacroEditorDialog::new_macro()
{
  ensure_writeable_collection_selected ();

  lay::MacroEditorTree *ct = current_macro_tree ();

  if (! ct->current_macro () && ! ct->current_macro_collection ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("Select a position where to add the macro")));
  }

  //  ask for a template
  std::string cat;
  if (treeTab->currentIndex () < int (m_categories.size ())) {
    cat = m_categories [treeTab->currentIndex ()].first;
  }
  lay::MacroTemplateSelectionDialog template_dialog (this, m_macro_templates, cat);
  int template_index = template_dialog.exec_dialog ();
  if (template_index < 0) {
    return 0;
  }

  Macro *m = create_macro_here (m_macro_templates [template_index]->name ().c_str ());
  m->assign (*m_macro_templates [template_index]);
  m->set_readonly (false);
  //  we don't want to keep the template's description
  m->set_description (std::string ());

  MacroEditorPage *page = create_page (m);
  int index = tabWidget->addTab (page, tl::to_qstring (m->name ()));
  tabWidget->setTabToolTip (index, tl::to_qstring (m->summary ()));
  tabWidget->setCurrentWidget (page);
  m_tab_widgets.insert (std::make_pair (m, page));

  ct->set_current (m);
  if (ct->currentIndex ().isValid () && (ct->model ()->flags (ct->currentIndex ()) & Qt::ItemIsEditable)) {
    ct->edit (ct->currentIndex ());
  }

  return m;
}

void
MacroEditorDialog::tab_close_requested (int index)
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  if (! tabWidget->widget (index)) {
    return;
  }

  MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->widget (index));
  if (! page || ! page->macro ()) {
    delete tabWidget->currentWidget ();
    return;
  }

  std::map <Macro *, MacroEditorPage *>::iterator p = m_tab_widgets.find (page->macro ());
  if (p != m_tab_widgets.end ()) {
    m_tab_widgets.erase (p);
  }

  page->connect_macro (0);
  delete page;

END_PROTECTED
}

void 
MacroEditorDialog::close_button_clicked ()
{
  tab_close_requested (tabWidget->currentIndex ());
}

void 
MacroEditorDialog::delete_button_clicked()
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  lay::MacroEditorTree *ct = current_macro_tree ();

  MacroCollection *collection = ct->current_macro_collection ();
  Macro *m = ct->current_macro ();

  if (collection) {

    if (collection->virtual_mode ()) {
      throw tl::Exception ("Can't delete this folder - it is a macro group");
    }
    if (collection->is_readonly ()) {
      throw tl::Exception ("Can't delete this folder - it is read-only");
    }
    if (collection->begin () != collection->end () || collection->begin_children () != collection->end_children ()) {
      throw tl::Exception ("Can't delete this folder - it is not empty");
    }

    MacroCollection *p = collection->parent ();

    if (p) {

      if (QMessageBox::question (this, QObject::tr ("Delete Folder"), 
                                       tl::to_qstring (tl::to_string (QObject::tr ("Are you sure to delete the folder ")) + collection->path () + "?"),
                                       QMessageBox::Ok, QMessageBox::Cancel) != QMessageBox::Ok) {
        return;
      }

      if (! collection->del ()) {
        throw tl::Exception ("Can't delete this folder - there may still be some other files inside it");
      }
      p->erase (collection);

    }

    ct->set_current (p);

 } else if (m) {

    MacroCollection *collection = m->parent ();
    if (m->is_readonly ()) {
      throw tl::Exception ("Can't delete this macro - it is readonly");
    }
    if (collection) {

      if (QMessageBox::question (this, QObject::tr ("Delete Macro File"), 
                                       tl::to_qstring (tl::to_string (QObject::tr ("Are you sure to delete the macro file ")) + m->path () + "?"),
                                       QMessageBox::Ok, QMessageBox::Cancel) != QMessageBox::Ok) {
        return;
      }

      if (! m->del ()) {
        throw tl::Exception ("Can't delete this macro");
      }

      collection->erase (m);

    }

    ct->set_current (collection);

  }

END_PROTECTED
}

void 
MacroEditorDialog::rename_button_clicked()
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  lay::MacroEditorTree *ct = current_macro_tree ();
  QModelIndex index = ct->currentIndex ();
  if (index.isValid ()) {
    if (ct->model ()->flags (index) & Qt::ItemIsEditable) {
      ct->edit (index);
    } else {
      throw tl::Exception (tl::to_string (QObject::tr ("Cannot edit this item's name")));
    }
  }

END_PROTECTED
}

void
MacroEditorDialog::ensure_writeable_collection_selected ()
{
  lay::MacroEditorTree *ct = current_macro_tree ();
  MacroCollection *collection = ct->current_macro_collection ();
  if (! collection) {
    Macro *macro = ct->current_macro ();
    if (macro) {
      collection = macro->parent ();
    }
  } 

  //  Select the first writeable collection if none is selected
  if (! collection || collection->is_readonly ()) {
    for (lay::MacroCollection::const_child_iterator c = mp_root->begin_children (); c != mp_root->end_children (); ++c) {
      if (c->second->category () == ct->category () && ! c->second->is_readonly ()) {
        ct->set_current (c->second);
        collection = c->second;
        break;
      }
    }
  }

  if (! collection) {
    throw tl::Exception (tl::to_string (QObject::tr ("Cannot perform that operation - no place selected")));
  }
  if (collection->is_readonly ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("Cannot perform that operation here - this place is read-only")));
  }
}

static std::vector<std::pair<std::string, std::string> > 
get_custom_paths ()
{
  std::vector <std::pair<std::string, std::string> > paths;

  std::string mp;
  MainWindow::instance ()->config_get (cfg_custom_macro_paths, mp);

  try {

    tl::Extractor ex (mp.c_str ());
    while (! ex.at_end ()) {

      paths.push_back (std::make_pair (std::string (), std::string ("macros")));
      ex.read_word_or_quoted (paths.back ().first);
      if (ex.test (":")) {
        ex.read_word (paths.back ().second);
      }

      ex.test (";");

    }

  } catch (...) { }

  return paths;
}

static void
set_custom_paths (const std::vector<std::pair<std::string, std::string> > &paths)
{
  std::string mp;

  //  add paths from our category
  for (std::vector<std::pair<std::string, std::string> >::const_iterator p = paths.begin (); p != paths.end (); ++p) {
    if (! mp.empty ()) {
      mp += ";";
    } 
    mp += tl::to_quoted_string (p->first);
    mp += ":";
    mp += p->second;
  }

  MainWindow::instance ()->config_set (cfg_custom_macro_paths, mp);
}

bool 
MacroEditorDialog::sync_macros (lay::MacroCollection *current, lay::MacroCollection *actual)
{
  bool ret = false;

  if (actual) {
    current->make_readonly (actual->is_readonly ());
  }

  std::vector<lay::MacroCollection *> folders_to_delete;

  for (lay::MacroCollection::child_iterator m = current->begin_children (); m != current->end_children (); ++m) {
    lay::MacroCollection *cm = actual ? actual->folder_by_name (m->first) : 0;
    if (! cm) {
      folders_to_delete.push_back (m->second);
    }
  }

  if (actual) {
    for (lay::MacroCollection::child_iterator m = actual->begin_children (); m != actual->end_children (); ++m) {
      lay::MacroCollection *cm = current->folder_by_name (m->first);
      if (! cm) {
        cm = current->create_folder (m->first.c_str (), false);
        ret = true;
      }
      if (sync_macros(cm, m->second)) {
        ret = true;
      }
    }
  }

  //  delete folders which do no longer exist
  for (std::vector<lay::MacroCollection *>::iterator m = folders_to_delete.begin (); m != folders_to_delete.end (); ++m) {
    ret = true;
    sync_macros (*m, 0);
    current->erase (*m);
  }

  std::vector<lay::Macro *> macros_to_delete;

  for (lay::MacroCollection::iterator m = current->begin (); m != current->end (); ++m) {
    lay::Macro *cm = actual ? actual->macro_by_name (m->first, m->second->format ()) : 0;
    if (! cm) {
      macros_to_delete.push_back (m->second);
    }
  }

  if (actual) {
    for (lay::MacroCollection::iterator m = actual->begin (); m != actual->end (); ++m) {
      lay::Macro *cm = current->macro_by_name (m->first, m->second->format ());
      if (cm) {
        if (*cm != *m->second) {
          cm->assign (*m->second);
        }
        cm->set_readonly (m->second->is_readonly ());
      } else {
        cm = current->create (m->first.c_str (), m->second->format ());
        cm->assign (*m->second);
        cm->set_readonly (m->second->is_readonly ());
        ret = true;
      }
    }
  }

  //  erase macros from collection which are no longer used
  for (std::vector<lay::Macro *>::const_iterator m = macros_to_delete.begin (); m != macros_to_delete.end (); ++m) {
    current->erase (*m);
    ret = true;
  }

  return ret;
}

void 
MacroEditorDialog::refresh ()
{
BEGIN_PROTECTED

  lay::MacroCollection new_root;

  //  save all so that we don't get differences in the text
  commit ();
  mp_root->save ();

  //  create a new root
  for (lay::MacroCollection::child_iterator c = mp_root->begin_children (); c != mp_root->end_children (); ++c) {
    new_root.add_folder (c->second->description (), c->second->path (), c->second->category (), c->second->is_readonly ());
  }

  //  and synchronize current with the actual one
  sync_macros (mp_root, &new_root);

END_PROTECTED
}

void 
MacroEditorDialog::add_location ()
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  QString new_dir = QFileDialog::getExistingDirectory (this, QObject::tr ("Add Location"));
  if (new_dir.isNull ()) {
    return;
  }

  std::string cat = current_macro_tree ()->category ();

  std::vector <std::pair<std::string, std::string> > paths = get_custom_paths ();
  std::string new_path = tl::to_string (QFileInfo (new_dir).absoluteFilePath ());
  paths.push_back (std::make_pair (new_path, cat));

  lay::MacroCollection *c = mp_root->add_folder (tl::to_string (QObject::tr ("Project")) + " - " + new_path, new_path, cat, false);
  if (!c) {
    throw tl::Exception (tl::to_string (QObject::tr ("The selected directory is already installed as custom location")));
  }

  set_custom_paths (paths);

  if (c->has_autorun ()) {
    if (QMessageBox::question (this, QObject::tr ("Run Macros"), QObject::tr ("The selected folder has macros configured to run automatically.\n\nChoose 'Yes' to run these macros now. Choose 'No' to not run them."), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
      c->autorun ();
    }
  }

END_PROTECTED
}

void 
MacroEditorDialog::remove_location ()
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  lay::MacroEditorTree *ct = current_macro_tree ();
  MacroCollection *collection = ct->current_macro_collection ();
  if (! collection) {
    Macro *m = ct->current_macro ();
    if (m) {
      collection = m->parent ();
    }
  }

  if (! collection) {
    throw tl::Exception (tl::to_string (QObject::tr ("Select tree location to remove")));
  } 

  std::vector <std::pair <std::string, std::string> > paths = get_custom_paths ();

  bool found = false;

  //  locate the location in the set of paths
  for (std::vector <std::pair <std::string, std::string> >::iterator p = paths.begin (); p != paths.end (); ++p) {
    if (p->first == collection->path () && p->second == ct->category ()) {
      paths.erase (p);
      found = true;
      break;
    }
  }

  if (! found) {
    throw tl::Exception (tl::to_string (QObject::tr ("Unable to remove that location")));
  } 

  //  close the tab pages related to the collection we want to delete
  std::set <lay::Macro *> used_macros;
  std::set <lay::MacroCollection *> used_collections;
  collection->collect_used_nodes (used_macros, used_collections);

  for (std::set <lay::Macro *>::iterator mc = used_macros.begin (); mc != used_macros.end (); ++mc) {

    std::map <Macro *, MacroEditorPage *>::iterator p = m_tab_widgets.find (*mc);
    if (p != m_tab_widgets.end ()) {
      p->second->connect_macro (0);
      delete p->second;
      m_tab_widgets.erase (p);
    }

  }

  //  actually remove the collection
  mp_root->erase (collection);

  //  save the new paths
  set_custom_paths (paths);

END_PROTECTED
}

void 
MacroEditorDialog::import_button_clicked ()
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  ensure_writeable_collection_selected ();

  lay::MacroEditorTree *ct = current_macro_tree ();
  if (! ct->current_macro () && ! ct->current_macro_collection ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("Select a position where to import the macro")));
  }

  static lay::FileDialog *file_dialog = 0;
  if (! file_dialog) {

    std::string filters = tl::to_string (QObject::tr ("All files (*);;KLayout macro files (*.lym);;Ruby files (*.rb);;Python files (*.py)"));

    //  add the suffixes in the DSL interpreter declarations
    for (tl::Registrar<lay::MacroInterpreter>::iterator cls = tl::Registrar<lay::MacroInterpreter>::begin (); cls != tl::Registrar<lay::MacroInterpreter>::end (); ++cls) {
      if (! cls->suffix ().empty ()) {
        filters += ";;";
        if (! cls->description ().empty ()) {
          filters += cls->description () + " ";
        }
        filters += "(*.";
        filters += cls->suffix ();
        filters += ")";
      }
    }

    file_dialog = new lay::FileDialog (lay::MainWindow::instance (), tl::to_string (QObject::tr ("Import Macro File")), filters, "lym");

  }

  std::string fn;
  if (file_dialog->get_open (fn)) {

    //  create a new macro and use the new name as the base name
    Macro *m = create_macro_here (tl::to_string (QFileInfo (tl::to_qstring (fn)).baseName ()).c_str ());

    try {
      m->load_from (fn);
    } catch (...) {
      //  On error delete the macro
      if (m->parent ()) {
        m->parent ()->erase (m);
      }
      throw;
    }

    ct->set_current (m);

  }

END_PROTECTED
}

void
MacroEditorDialog::new_folder_button_clicked()
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED

  ensure_writeable_collection_selected ();

  lay::MacroEditorTree *ct = current_macro_tree ();
  MacroCollection *collection = ct->current_macro_collection ();
  if (! collection) {
    Macro *m = ct->current_macro ();
    if (m) {
      collection = m->parent ();
    }
  }

  if (! collection || collection->is_readonly ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("Cannot create a folder here")));
  } 

  MacroCollection *mm = collection->create_folder ();
  if (! mm) {
    throw tl::Exception (tl::to_string (QObject::tr ("Failed to create the folder here")));
  }

  ct->set_current (mm);
  if (ct->currentIndex ().isValid () && (ct->model ()->flags (ct->currentIndex ()) & Qt::ItemIsEditable)) {
    ct->edit (ct->currentIndex ());
  }

END_PROTECTED
}

void
MacroEditorDialog::save_all_button_clicked()
{
  if (m_in_exec) {
    return;
  }

BEGIN_PROTECTED
  commit ();
  mp_root->save ();
END_PROTECTED
}

void 
MacroEditorDialog::item_double_clicked(lay::Macro *m)
{
BEGIN_PROTECTED

  std::map <Macro *, MacroEditorPage *>::iterator page = m_tab_widgets.find (m);
  if (page == m_tab_widgets.end ()) {

    MacroEditorPage *page = create_page (m);
    m_tab_widgets.insert (std::make_pair (m, page));
    int index = tabWidget->addTab (page, tl::to_qstring (m->name ()));
    tabWidget->setTabToolTip (index, tl::to_qstring (m->summary ()));
    tabWidget->setCurrentWidget (page);

  } else {
    tabWidget->setCurrentIndex (tabWidget->indexOf (page->second));
  }

END_PROTECTED
}

void
MacroEditorDialog::start_exec (gsi::Interpreter *ec)
{
  //  ignore calls from other interpreters
  if (m_in_exec) {
    tl_assert (ec != mp_exec_controller);
    return;
  }

  m_file_to_widget.clear ();

  m_last_process_events = tl::Clock::current ();

  m_in_exec = true;
  mp_exec_controller = ec;
  m_in_breakpoint = false;
  m_continue = true;
  m_trace_count = 0;
  m_current_stack_depth = -1;
  m_process_events_interval = 0.05;

  for (std::map<Macro *, MacroEditorPage *>::const_iterator f = m_tab_widgets.begin (); f != m_tab_widgets.end (); ++f) {
    f->second->exec_model ()->set_current_line (-1);
    f->second->exec_model ()->set_run_mode (true);
  }

  update_ui_to_run_mode ();
}

void
MacroEditorDialog::end_exec (gsi::Interpreter *ec)
{
  //  ignore calls from other interpreters
  if (m_in_exec && ec != mp_exec_controller) {
    return;
  }

  if (QApplication::activeModalWidget () == this) {
    //  close this window if it was shown in modal mode
    QDialog::accept ();
  }

  m_in_exec = false;
  mp_exec_controller = 0;
  m_continue = false;
  m_current_stack_depth = -1;

  for (std::map<Macro *, MacroEditorPage *>::const_iterator f = m_tab_widgets.begin (); f != m_tab_widgets.end (); ++f) {
    f->second->exec_model ()->set_run_mode (false);
  }

  update_ui_to_run_mode ();
}


size_t   
MacroEditorDialog::id_for_path (gsi::Interpreter *, const std::string &path)
{
  for (std::map <Macro *, MacroEditorPage *>::const_iterator m = m_tab_widgets.begin (); m != m_tab_widgets.end (); ++m) {
    if (m->first->path () == path) {
      m_file_to_widget.push_back (*m);
      return m_file_to_widget.size ();
    }
  }

  lay::Macro *macro = mp_root->find_macro (path);
  if (macro) {
    m_file_to_widget.push_back (std::make_pair (macro, (MacroEditorPage *) 0));
    return m_file_to_widget.size ();
  } else {
    return 0;
  }
}

void   
MacroEditorDialog::exception_thrown (gsi::Interpreter *interpreter, size_t file_id, int line, const std::string &eclass, const std::string &emsg, const gsi::StackTraceProvider *stack_trace_provider)
{
  //  no action if stop on exception is disabled
  if (!m_stop_on_exception) {
    return;
  }

  if (!m_in_exec) {
    throw gsi::ExitException ();
  }

  //  avoid recursive breakpoints and exception catches from the console while in a breakpoint or exception stop
  if (m_in_processing) {
    return;
  }

  try {

    //  If the exception is thrown in code that is inside a file managed by the macro collection, 
    //  offer to stop the debugger there.
    std::vector<gsi::BacktraceElement> bt = stack_trace_provider->stack_trace ();
    size_t scope_index = stack_trace_provider->scope_index ();
    if (bt.empty () || !mp_root->find_macro (bt [scope_index].file)) {
      return;
    }

    if (QMessageBox::critical (this, QObject::tr ("Exception Caught"), 
                                     tl::to_qstring (tl::to_string (QObject::tr ("Caught the following exception:\n")) + emsg + " (Class " + eclass + ")\n\n" + tl::to_string (QObject::tr ("Press 'Ok' to continue and 'Cancel' to stop in the debugger"))),
                                     QMessageBox::Cancel, QMessageBox::Ok) == QMessageBox::Ok) {
      return;
    }

    write_str (emsg.c_str (), OS_stderr);
    write_str ("\n", OS_stderr);

    if (file_id > 0 && file_id <= m_file_to_widget.size () && m_file_to_widget [file_id - 1].second) {
      m_file_to_widget [file_id - 1].second->set_error_line (line - 1);
    }

    enter_breakpoint_mode (interpreter, stack_trace_provider);

    if (QApplication::activeModalWidget () && QApplication::activeModalWidget () != this) {

      //  apparently that is the only way to override the event handling mechanism of Qt:
      //  if the breakpoint is issued from inside an event handler of a modal dialog, the 
      //  editor window does not receive events, not even if we requested filtering.
      hide ();
      exec ();
      show ();

    } else {

      while (m_in_breakpoint && m_in_exec)
      {
        process_events (QEventLoop::WaitForMoreEvents);
      }

    }

    leave_breakpoint_mode ();

  } catch (...) {
    leave_breakpoint_mode ();
    throw;
  }

  if (! m_in_exec) {
    throw gsi::ExitException ();
  }
}

void   
MacroEditorDialog::trace (gsi::Interpreter *interpreter, size_t file_id, int line, const gsi::StackTraceProvider *stack_trace_provider)
{
  if (!m_in_exec) {
    throw gsi::ExitException ();
  }

  //  avoid recursive breakpoints and exception catches from the console while in a breakpoint or exception stop
  if (m_in_processing) {
    return;
  }

  //  adjust the current stack level after an exception
  if (m_current_stack_depth < 0) {
    m_current_stack_depth = stack_trace_provider->stack_depth ();
  }

  //  Note: only scripts running in the context of the execution controller (the one who called start_exec)
  //  can be interrupted and single-stepped, but breakpoints can make the debugger stop in other interpreters.
  if (file_id > 0 && ((interpreter == mp_exec_controller && m_stop_stack_depth >= 0 && stack_trace_provider->stack_depth () <= m_stop_stack_depth) || 
                      (interpreter == mp_exec_controller && ! m_continue) || 
                      (file_id <= m_file_to_widget.size () && m_file_to_widget [file_id - 1].second && m_file_to_widget [file_id - 1].second->exec_model ()->is_breakpoint (line)))) {

    try {

      enter_breakpoint_mode (interpreter, stack_trace_provider);

      if (QApplication::activeModalWidget () && QApplication::activeModalWidget () != this) {

        //  apparently that is the only way to override the event handling mechanism of Qt:
        //  if the breakpoint is issued from inside an event handler of a modal dialog, the 
        //  editor window does not receive events, not even if we requested filtering.
        hide ();
        exec ();
        show ();

      } else {

        while (m_in_breakpoint && m_in_exec) {
          process_events (QEventLoop::WaitForMoreEvents);
        }

      }

      leave_breakpoint_mode ();

    } catch (...) {
      leave_breakpoint_mode ();
      throw;
    }

    if (! m_in_exec) {
      throw gsi::ExitException ();
    }

  } else if (++m_trace_count == 20) {

    m_trace_count = 0;

    if ((tl::Clock::current () - m_last_process_events).seconds () > m_process_events_interval) {

      tl::Clock start = tl::Clock::current ();

      process_events ();

      //  adjust the process events interval
      m_last_process_events = tl::Clock::current ();
      m_process_events_interval = std::max (0.05, std::min (2.0, (m_last_process_events - start).seconds () * 5.0));

      if (!m_in_exec) {
        throw gsi::ExitException ();
      }

    }

  }
}

void 
MacroEditorDialog::enter_breakpoint_mode (gsi::Interpreter *interpreter, const gsi::StackTraceProvider *stack_trace_provider)
{
  m_in_breakpoint = true;
  m_eval_context = -1;
  mp_current_interpreter = interpreter;

  if (isMinimized ()) {
    showNormal ();
  }
  activateWindow ();
  raise ();
  show ();

  size_t scope_index = stack_trace_provider->scope_index ();

  callStack->clear ();
  std::vector<gsi::BacktraceElement> bt = stack_trace_provider->stack_trace ();
  for (std::vector<gsi::BacktraceElement>::const_iterator b = bt.begin (); b != bt.end (); ++b) {
    QListWidgetItem *item = new QListWidgetItem (callStack);
    item->setText (tl::to_qstring (b->to_string ()));
    item->setData (Qt::UserRole, tl::to_qstring (b->file));
    item->setData (Qt::UserRole + 1, b->line);
    item->setData (Qt::UserRole + 2, int (b - bt.begin ()));
    callStack->addItem (item);
  }

  callStack->setCurrentRow (int (scope_index));

  //  Adjust the current stack level
  m_current_stack_depth = int (bt.size ());

  update_ui_to_run_mode ();

  //  Hint: apparently it's necessary to process the events to make the layout system
  //  recognize that we have hidden parts from the edit field by the runtime frame.
  process_events (QEventLoop::ExcludeUserInputEvents);

  if (! bt.empty ()) {
    set_exec_point (&bt[scope_index].file, bt[scope_index].line, int (scope_index));
  }

  update_inspected ();
}

void 
MacroEditorDialog::leave_breakpoint_mode ()
{
  m_in_breakpoint = false;
  m_eval_context = -1;
  mp_current_interpreter = 0;
  update_ui_to_run_mode ();
  set_exec_point (0, -1, -1);
}

void 
MacroEditorDialog::update_ui_to_run_mode ()
{
  double alpha = 0.95;

  MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->currentWidget ());

  dbgOn->setEnabled (! m_in_exec);
  runButton->setEnabled ((! m_in_exec && (mp_run_macro || (page && page->macro ()->interpreter () != lay::Macro::None))) || m_in_breakpoint);
  runThisButton->setEnabled ((! m_in_exec && page && page->macro ()->interpreter () != lay::Macro::None) || m_in_breakpoint);
  singleStepButton->setEnabled (! m_in_exec || m_in_breakpoint);
  nextStepButton->setEnabled (! m_in_exec || m_in_breakpoint);
  stopButton->setEnabled (m_in_exec);
  pauseButton->setEnabled (m_in_exec && ! m_in_breakpoint);

  for (std::vector<lay::MacroEditorTree *>::const_iterator mt = m_macro_trees.begin (); mt != m_macro_trees.end (); ++mt) {
    (*mt)->setEditTriggers (m_in_exec ? QAbstractItemView::NoEditTriggers : QAbstractItemView::SelectedClicked);
  }

  addButton->setEnabled (! m_in_exec);
  actionAddMacro->setEnabled (! m_in_exec);
  closeButton->setEnabled (! m_in_exec);
  deleteButton->setEnabled (! m_in_exec);
  actionDelete->setEnabled (! m_in_exec);
  renameButton->setEnabled (! m_in_exec);
  actionRename->setEnabled (! m_in_exec);
  importButton->setEnabled (! m_in_exec);
  actionImport->setEnabled (! m_in_exec);
  newFolderButton->setEnabled (! m_in_exec);
  actionNewFolder->setEnabled (! m_in_exec);
  saveAllButton->setEnabled (! m_in_exec);
  actionSaveAll->setEnabled (! m_in_exec);
  saveButton->setEnabled (! m_in_exec);
  actionSave->setEnabled (! m_in_exec);
  actionRefresh->setEnabled (! m_in_exec);
  actionAddLocation->setEnabled (! m_in_exec);
  actionRemoveLocation->setEnabled (! m_in_exec);
  propertiesButton->setEnabled (! m_in_exec && page && page->macro () && (page->macro ()->format () == Macro::MacroFormat || page->macro ()->format () == Macro::PlainTextWithHashAnnotationsFormat));
  setupButton->setEnabled (! m_in_exec);
  langSelFrame->setEnabled (! m_in_exec);

  //  Force language type to match the current execution context
  if (m_in_breakpoint && mp_current_interpreter) {
    if (mp_current_interpreter == &lay::Application::instance ()->python_interpreter ()) {
      pythonLangSel->setChecked (true);
      rubyLangSel->setChecked (false);
    } else {
      pythonLangSel->setChecked (false);
      rubyLangSel->setChecked (true);
    }
  }

  QColor base_color = qApp->palette ().color (QPalette::Base);
  QColor alt_base_color = qApp->palette ().color (QPalette::AlternateBase);

  if (m_in_exec) {

    if (m_in_breakpoint && mp_current_interpreter) {

      base_color = QColor (base_color.red (), int (0.5 + base_color.green () * alpha), int (0.5 + base_color.blue () * alpha));
      alt_base_color = QColor (alt_base_color.red (), int (0.5 + alt_base_color.green () * alpha), int (0.5 + alt_base_color.blue () * alpha));
      runtimeFrame->show ();

    } else {

      base_color = QColor (int (0.5 + base_color.red () * alpha), base_color.green (), int (0.5 + base_color.blue () * alpha));
      alt_base_color = QColor (int (0.5 + alt_base_color.red () * alpha), alt_base_color.green (), int (0.5 + alt_base_color.blue () * alpha));
      runtimeFrame->hide ();

    }

  } else {

    variableListFrame->setVisible (false);
    variableList->set_inspector (0);
    runtimeFrame->hide ();

  }

  QPalette p = palette ();
  p.setColor (QPalette::Base, base_color);
  p.setColor (QPalette::AlternateBase, alt_base_color);
  setPalette (p);

  //  for some reason, callStack, variableList and watchList don't inherit the palette ...
  callStack->setPalette (p);
  variableList->setPalette (p);
  watchList->setPalette (p);

  std::map <Macro *, MacroEditorPage *>::const_iterator t = m_tab_widgets.find (mp_run_macro);
  if (t != m_tab_widgets.end ()) {
    int index = tabWidget->indexOf (t->second);
    if (index >= 0) {
      tabWidget->setTabIcon (index, QIcon (QString::fromAscii (m_in_exec ? (m_in_breakpoint ? ":/pause.png" : ":/stop.png") : ":/run.png")));
    }
  }
}

void 
MacroEditorDialog::stack_element_double_clicked (QListWidgetItem *item)
{
  std::string f = tl::to_string (item->data (Qt::UserRole).toString ());

  int context = item->data (Qt::UserRole + 2).toInt ();
  set_exec_point (&f, item->data (Qt::UserRole + 1).toInt (), context);

  update_inspected ();
}

MacroEditorPage *
MacroEditorDialog::create_page (Macro *macro)
{
  std::auto_ptr<MacroEditorPage> editor (new MacroEditorPage (this, &m_highlighters));
  editor->set_ntab (m_ntab);
  editor->set_nindent (m_nindent);
  editor->set_font (m_font_family, m_font_size);
  editor->exec_model ()->set_run_mode (m_in_exec);
  editor->connect_macro (macro);
  connect (editor.get (), SIGNAL (help_requested (const QString &)), this, SLOT (help_requested (const QString &)));
  return editor.release ();
}

MacroEditorPage *
MacroEditorDialog::editor_for_macro (Macro *macro)
{
  for (std::vector<lay::MacroEditorTree *>::const_iterator mt = m_macro_trees.begin (); mt != m_macro_trees.end (); ++mt) {
    (*mt)->set_current (macro); 
  }

  MacroEditorPage *editor = 0;

  std::map <Macro *, MacroEditorPage *>::iterator page = m_tab_widgets.find (macro);
  if (page == m_tab_widgets.end ()) {

    editor = create_page (macro);
    int index = tabWidget->addTab (editor, tl::to_qstring (macro->name ()));
    tabWidget->setTabToolTip (index, tl::to_qstring (macro->summary ()));
    if (macro == mp_run_macro) {
      tabWidget->setTabIcon (index, QIcon (QString::fromAscii (m_in_exec ? (m_in_breakpoint ? ":/pause.png" : ":/stop.png") : ":/run.png")));
    }
    tabWidget->setCurrentWidget (editor);
    m_tab_widgets.insert (std::make_pair (macro, editor));

    for (std::vector <std::pair<Macro *, MacroEditorPage *> >::iterator f = m_file_to_widget.begin (); f != m_file_to_widget.end (); ++f) {
      if (f->first == macro) {
        f->second = editor;
        break;
      }
    }

  } else {
    editor = page->second;
    tabWidget->setCurrentIndex (tabWidget->indexOf (editor));
  }

  return editor;
}

MacroEditorPage *
MacroEditorDialog::editor_for_file (const std::string &path)
{
  lay::Macro *macro = mp_root->find_macro (path);
  if (macro) {
    return editor_for_macro (macro);
  } else {
    return 0;
  }
}

void
MacroEditorDialog::set_exec_point (const std::string *file, int line, int eval_context)
{
  MacroEditorPage *editor = 0;
  if (file) {
    editor = editor_for_file (*file);
  }

  for (std::map<Macro *, MacroEditorPage *>::const_iterator f = m_tab_widgets.begin (); f != m_tab_widgets.end (); ++f) {
    f->second->exec_model ()->set_current_line (f->second == editor ? line : -1, true);
  }

  m_eval_context = eval_context;
}

void
MacroEditorDialog::handle_error (gsi::RuntimeError &re)
{
  //  navigate to the file/line
  MacroEditorPage *editor = editor_for_file (re.sourcefile ());
  if (editor) {
    editor->set_error_line (re.line () - 1);
  }
}
 
void 
MacroEditorDialog::breakpoint_button_clicked ()
{
  MacroEditorPage *page = dynamic_cast <MacroEditorPage *> (tabWidget->currentWidget ());
  if (! page) {
    return;
  }

  page->exec_model ()->toggle_breakpoint (page->current_line ());
}

void 
MacroEditorDialog::clear_breakpoints_button_clicked ()
{
  for (std::map<Macro *, MacroEditorPage *>::const_iterator f = m_tab_widgets.begin (); f != m_tab_widgets.end (); ++f) {
    f->second->exec_model ()->set_breakpoints (std::set <int> ());
  }
}

void
MacroEditorDialog::pause_button_clicked ()
{
  m_continue = false;
}

void  
MacroEditorDialog::stop_button_clicked ()
{
  if (QApplication::activeModalWidget () == this) {
    //  close this window if it was shown in modal mode
    accept ();
  }

  m_in_exec = false;
  m_continue = false;
}

void
MacroEditorDialog::next_step_button_clicked ()
{
BEGIN_PROTECTED
  run (m_in_exec ? std::max (0, m_current_stack_depth) : std::numeric_limits <int>::max (), current_run_macro ());
END_PROTECTED
}

void 
MacroEditorDialog::single_step_button_clicked ()
{
BEGIN_PROTECTED
  run (std::numeric_limits <int>::max (), current_run_macro ());
END_PROTECTED
}

void  
MacroEditorDialog::run_button_clicked ()
{
BEGIN_PROTECTED
  run (-1, current_run_macro ());
END_PROTECTED
}

void  
MacroEditorDialog::run_this_button_clicked ()
{
BEGIN_PROTECTED
  run (-1, 0);
END_PROTECTED
}

lay::Macro *
MacroEditorDialog::current_run_macro ()
{
  //  validate the current run macro against the macros present in the collection and
  //  return 0 if invalid (that takes the current one)

  std::set<lay::Macro *> macros;
  std::set<lay::MacroCollection *> macro_collections;
  mp_root->collect_used_nodes (macros, macro_collections);

  if (macros.find (mp_run_macro) != macros.end ()) {
    return mp_run_macro;
  } else {
    return 0;
  }
}

void   
MacroEditorDialog::run (int stop_stack_depth, lay::Macro *macro)
{
  m_stop_stack_depth = stop_stack_depth;
  m_continue = true;

  if (m_in_breakpoint) {

    if (QApplication::activeModalWidget () == this) {
      //  close this window if it was shown in modal mode
      accept ();
    }

    //  in a breakpoint
    m_in_breakpoint = false;

  } else {

    if (! macro) {

      //  initial -> run
      if (! tabWidget->currentWidget ()) {
        return;
      }

      MacroEditorPage *page = dynamic_cast<MacroEditorPage *> (tabWidget->currentWidget ());
      if (! page || ! page->macro ()) {
        return;
      }
      macro = page->macro ();

    } else {
      //  TODO: clarify whether we should switch to the page which is run - this
      //  is annoying sometimes:
      //  editor_for_macro (macro);
    }

    if (! m_save_all_on_run && any_modified (mp_root)) {
      if (QMessageBox::question (this, QObject::tr ("Save Macros"), 
                                       QObject::tr ("Some files are modified and need to be saved before running the macro. Do you want to save them?"),
                                       QMessageBox::Yes, QMessageBox::Cancel) == QMessageBox::Cancel) {
        return;
      }
    }

    //  save all macros
    //  Hint: although it looks like to touch decision, it's important to save every change since
    //  files may be included/loaded/required by other files.
    commit ();
    mp_root->save ();

    set_run_macro (macro);

    try {
      macro->run ();
      m_stop_stack_depth = -1;
    } catch (gsi::ExitException &) {
      m_stop_stack_depth = -1;
      //  .. ignore exit exceptions ..
    } catch (gsi::RuntimeError &re) {
      m_stop_stack_depth = -1;
      handle_error (re);
      throw;
    } catch (...) {
      m_stop_stack_depth = -1;
      throw;
    }

    //  TODO: clarify whether we should switch to the page which is run - this
    //  is annoying sometimes:
#if 0
    if (mp_run_macro) {
      std::map <Macro *, MacroEditorPage *>::const_iterator t = m_tab_widgets.find (mp_run_macro);
      if (t != m_tab_widgets.end ()) {
        tabWidget->setCurrentWidget (t->second);
      }
    }
#endif

  }
}

void
MacroEditorDialog::set_run_macro (lay::Macro *m)
{
  if (m != mp_run_macro) {

    std::map <Macro *, MacroEditorPage *>::const_iterator t = m_tab_widgets.find (mp_run_macro);
    if (t != m_tab_widgets.end ()) {
      int index = tabWidget->indexOf (t->second);
      if (index >= 0) {
        tabWidget->setTabIcon (index, QIcon ());
      }
    }

    mp_run_macro = m;

    t = m_tab_widgets.find (mp_run_macro);
    if (t != m_tab_widgets.end ()) {
      int index = tabWidget->indexOf (t->second);
      if (index >= 0) {
        tabWidget->setTabIcon (index, QIcon (QString::fromAscii (":/run.png")));
      }
    }

    for (std::vector<lay::MacroEditorTree *>::const_iterator mt = m_macro_trees.begin (); mt != m_macro_trees.end (); ++mt) {
      (*mt)->update_data (); //  to switch icon
    }

  }
}

// -----------------------------------------------------------------------------------------
//  The plugin declaration that enables persistency though configuration options

class MacroEditorPluginDeclaration
  : public lay::PluginDeclaration
{
public:
  virtual void get_options (std::vector < std::pair<std::string, std::string> > &options) const
  {
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_styles, ""));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_save_all_on_run, "false"));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_tab_width, "8"));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_indent, "2"));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_window_state, ""));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_console_mru, ""));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_console_interpreter, ""));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_open_macros, ""));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_current_macro, ""));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_active_macro, ""));
    options.push_back (std::pair<std::string, std::string> (cfg_macro_editor_watch_expressions, ""));
  }
};

static tl::RegisteredClass<lay::PluginDeclaration> config_decl (new MacroEditorPluginDeclaration (), 1500, "MacroEditor");

}

