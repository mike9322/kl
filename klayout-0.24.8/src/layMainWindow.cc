
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


#include <QtGui/QWindowsStyle>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QStatusBar>
#include <QtGui/QInputDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QMainWindow>
#include <QtGui/QPainter>
#include <QtGui/QDockWidget>
#include <QtGui/QShortcut>
#include <QtGui/QPrintDialog>
#include <QtCore/QFileInfo>
#include <QtCore/QDateTime>
#include <QtCore/QUrl>

#if defined(__APPLE__)
// A workaround for the issue of Qt 4.8.x when handling "File Reference URL" in OSX
// By Kazunari Sekigawa (November 12, 2015)
// Search down for my name for more details!
# include <CoreFoundation/CoreFoundation.h>
#endif

#include "tlInternational.h"
#include "tlTimer.h"
#include "tlLog.h"
#include "tlAssert.h"
#include "tlDeferredExecution.h"
#include "tlStream.h"
#include "dbMemStatistics.h"
#include "dbManager.h"
#include "dbStream.h"
#include "dbSaveLayoutOptions.h"
#include "dbClipboard.h"
#include "dbLibraryManager.h"
#include "dbLibrary.h"
#include "dbStatic.h"
#include "edtConfig.h"
#include "laySession.h"
#include "layApplication.h"
#include "layVersion.h"
#include "layConverters.h"
#include "layCellSelectionForm.h"
#include "layDialogs.h"
#include "layConfig.h"
#include "layMainWindow.h"
#include "layMacroEditorDialog.h"
#include "layHelpDialog.h"
#include "layHelpSource.h" // because of escape_xml
#include "layMacro.h"
#include "layNavigator.h"
#include "layProgress.h"
#include "layProgressWidget.h"
#include "layStream.h"
#include "layLayerControlPanel.h" // because of LabelWithBackground
#include "layFileDialog.h"
#include "layMainConfigPages.h"
#include "layAbstractMenu.h"
#include "layExceptions.h"
#include "laySaveLayoutOptionsDialog.h"
#include "layLoadLayoutOptionsDialog.h"
#include "layLogViewerDialog.h"
#include "layLayerToolbox.h"
#include "laySettingsForm.h"
#include "laySettingsForm.h"
#include "layTechSetupDialog.h"
#include "layTipDialog.h"
#include "laySelectCellViewForm.h"
#include "layLayoutPropertiesForm.h"
#include "layLayoutStatisticsForm.h"
#include "HelpAboutDialog.h"
#include "gsi.h"
#include "gtf.h"

namespace lay
{

const int max_dirty_files = 15;

// -------------------------------------------------------------

class ProgressDialog
  : public QDialog
{
public:
  ProgressDialog (QWidget *parent, lay::ProgressReporter *pr)
    : QDialog (parent), mp_pr (pr)
  {
    QVBoxLayout *vbl = new QVBoxLayout (this);
    vbl->setMargin (0);
    vbl->setSpacing (0);

    mp_progress_widget = new ProgressWidget (pr, this, true);
    mp_progress_widget->setObjectName (QString::fromAscii ("progress"));
    vbl->addWidget (mp_progress_widget);

    setWindowTitle (QObject::tr ("Progress"));
    setWindowModality (Qt::WindowModal);
  }

  void closeEvent (QCloseEvent *event)
  {
#if 0
    //  NOTE: We don't kill on close for now. This creates a too easy way to scrap results.
    if (mp_pr) {
      mp_pr->signal_break ();
    }
#endif
  }

  void set_can_cancel (bool f)
  {
    mp_progress_widget->set_can_cancel (f);
  }

  void set_text (const std::string &text)
  {
    mp_progress_widget->set_text (text);
  }

  void set_value (double v, const std::string &value)
  {
    mp_progress_widget->set_value (v, value);
  }

private:
  lay::ProgressWidget *mp_progress_widget;
  lay::ProgressReporter *mp_pr;
};

// -------------------------------------------------------------

class ControlWidgetStack 
  : public QFrame
{
public:
  ControlWidgetStack (QWidget *parent = 0, const char *name = 0)
    : QFrame (parent)
  {
    setObjectName (QString::fromAscii (name));

    //  Background ist a simple label without a text currently
    mp_bglabel = new QLabel (this);
    mp_bglabel->setAutoFillBackground (true);
    mp_bglabel->setAlignment (Qt::AlignVCenter | Qt::AlignHCenter);
    mp_bglabel->show ();
  }

  void addWidget (QWidget *w)
  {
    m_widgets.push_back (w);
    w->setParent (this);
    resize_children ();
    raiseWidget (m_widgets.size () - 1);

    int mw = 0;
    for (size_t i = 0; i < m_widgets.size (); ++i) {
      mw = std::max (m_widgets [i]->sizeHint ().width (), mw);
      mw = std::max (m_widgets [i]->minimumWidth (), mw);
    }

    if (mw > minimumWidth ()) {
      setMinimumWidth (mw);
      resize (minimumWidth (), height ());
    }
  }

  QSize sizeHint () const
  {
    int w = 0;
    for (size_t i = 0; i < m_widgets.size (); ++i) {
      w = std::max (m_widgets [i]->sizeHint ().width (), w);
    }
    return QSize (w, 0);
  }

  void removeWidget (size_t index)
  {
    if (index < m_widgets.size ()) {
      m_widgets.erase (m_widgets.begin () + index);
    }
    if (m_widgets.size () == 0) {
      mp_bglabel->show ();
    }
  }

  void raiseWidget (size_t index)
  {
    bool any_visible = false;
    for (size_t i = 0; i < m_widgets.size (); ++i) {
      if (m_widgets [i]) {
        if (i == index) {
          m_widgets [i]->show ();
          any_visible = true;
        } else {
          m_widgets [i]->hide ();
        }
      }
    }

    if (! any_visible) {
      mp_bglabel->show ();
    } else {
      mp_bglabel->hide ();
    }
  }
  
  QWidget *widget (size_t index)
  {
    if (index < m_widgets.size ()) {
      return m_widgets [index];
    } else {
      return 0;
    }
  }

  QWidget *background_widget ()
  {
    return mp_bglabel;
  }

protected:
  virtual void resizeEvent (QResizeEvent *)
  {
    resize_children ();
  }

  void resize_children ()
  {
    //  set the geometry of all children 
    for (std::vector <QWidget *>::iterator child = m_widgets.begin (); child != m_widgets.end (); ++child) {
      if (*child) {
        (*child)->setGeometry (0, 0, width (), height ());
      }
    }
    mp_bglabel->setGeometry (0, 0, width (), height ());
  }

  std::vector <QWidget *> m_widgets;
  QLabel *mp_bglabel;
};

// -------------------------------------------------------------

class ViewWidgetStack 
  : public QWidget
{
public:
  ViewWidgetStack (QWidget *parent = 0, const char *name = 0)
    : QWidget (parent)
  {
    setObjectName (QString::fromAscii (name));

    mp_bglabel = new QLabel (this);
    mp_bglabel->setAutoFillBackground (true);
    mp_bglabel->setText (QObject::tr ("<html><body><p><img src=\":/logo.png\"/></p><p>Use File/Open to open a layout</p></body></html>"));
    mp_bglabel->setAlignment (Qt::AlignVCenter | Qt::AlignHCenter);
    mp_bglabel->show ();
  }

  void addWidget (LayoutView *w)
  {
    m_widgets.push_back (w);
    w->setParent (this);
    resize_children ();
    raiseWidget (m_widgets.size () - 1);

    updateGeometry ();
  }

  void removeWidget (size_t index)
  {
    if (index < m_widgets.size ()) {
      m_widgets.erase (m_widgets.begin () + index);
    }
    if (m_widgets.size () == 0) {
      mp_bglabel->show ();
    }
  }

  void raiseWidget (size_t index)
  {
    size_t i;
    i = 0;
    for (std::vector <LayoutView *>::iterator child = m_widgets.begin (); child != m_widgets.end (); ++child, ++i) {
      if (i != index) {
        (*child)->deactivate ();
      }
    }

    if (index < m_widgets.size ()) {
      mp_bglabel->hide ();
      m_widgets [index]->activate ();
      m_widgets [index]->show ();
    } else {
      mp_bglabel->show ();
    }

    i = 0;
    for (std::vector <LayoutView *>::iterator child = m_widgets.begin (); child != m_widgets.end (); ++child, ++i) {
      if (i != index) {
        (*child)->hide ();
      }
    }
  }
  
  LayoutView *widget (size_t index)
  {
    if (index < m_widgets.size ()) {
      return m_widgets [index];
    } else {
      return 0;
    }
  }

  QWidget *background_widget ()
  {
    return mp_bglabel;
  }

protected:
  virtual void resizeEvent (QResizeEvent *)
  {
    resize_children ();
  }

  void resize_children ()
  {
    //  set the geometry of all children 
    for (std::vector <LayoutView *>::iterator child = m_widgets.begin (); child != m_widgets.end (); ++child) {
      (*child)->setGeometry (0, 0, width (), height ());
    }
    mp_bglabel->setGeometry (0, 0, width (), height ());
  }

  std::vector <LayoutView *> m_widgets;
  QLabel *mp_bglabel;
};

// -------------------------------------------------------------

static MainWindow *mw_instance = 0;

MainWindow *
MainWindow::instance ()
{
  return mw_instance; 
}

// -----------------------------------

MainWindow::MainWindow (QApplication *app, const char *name)
    : QMainWindow (0),
      lay::TextProgress (10 /*verbosity threshold*/),
      m_mode (std::numeric_limits<unsigned int>::max ()),
      mp_setup_form (0),
      m_current_view (std::numeric_limits<size_t>::max ()),
      m_open_mode (0),
      m_edits_enabled (true),
      m_disable_tab_selected (false),
      m_exited (false),
      dm_do_update_menu_with_macros (this, &MainWindow::do_update_menu_with_macros),
      dm_do_update_menu (this, &MainWindow::do_update_menu),
      m_grid_micron (0.001), 
      m_default_grids_updated (true),
      m_new_cell_window_size (2.0),
      m_new_layout_current_panel (false),
      m_default_dbu (0.001),
      m_synchronized_views (false),
      m_synchronous (false),
      m_disabled_edits (0),
      m_busy (false),
      m_work_in_progress (false),
      m_libraries_changed_observer (this, &MainWindow::libraries_changed),
      mp_app (app)
{
  setObjectName (QString::fromAscii (name));

  if (mw_instance != 0) {
    throw tl::Exception (tl::to_string (QObject::tr ("Only one instance of MainWindow may be created")));
  }
  mw_instance = this;

  mp_setup_form = new SettingsForm (0, this, "setup_form"),

  db::LibraryManager::instance ().add_observer (m_libraries_changed_observer);

  init_menu ();

  connect (&lay::MacroCollection::root (), SIGNAL (menu_needs_update ()), this, SLOT (update_menu_with_macros ()));
  connect (&lay::MacroCollection::root (), SIGNAL (macro_collection_changed (MacroCollection *)), this, SLOT (update_menu_with_macros ()));

  mp_macro_editor = new lay::MacroEditorDialog (this, &lay::MacroCollection::root ());
  mp_macro_editor->setModal (false);

  mp_assistant = new lay::HelpDialog (this);

  mp_pr = new lay::ProgressReporter ();
  mp_pr->set_progress_bar (this);

  mp_main_stack_widget = new QStackedWidget (this);
  mp_main_stack_widget->setObjectName (QString::fromAscii ("main_stack"));
  setCentralWidget (mp_main_stack_widget);

  mp_main_frame = new QFrame (mp_main_stack_widget);
  mp_main_frame->setObjectName (QString::fromAscii ("main_frame"));
  mp_main_stack_widget->addWidget (mp_main_frame);

  mp_progress_widget = new ProgressWidget (mp_pr, mp_main_stack_widget);
  mp_progress_widget->setObjectName (QString::fromAscii ("progress"));
  mp_main_stack_widget->addWidget (mp_progress_widget);

  mp_main_stack_widget->setCurrentIndex (0);

  QVBoxLayout *vbl = new QVBoxLayout (mp_main_frame);
  vbl->setMargin (0);
  vbl->setSpacing (0);

  mp_tab_bar = new QTabBar (mp_main_frame);
  vbl->addWidget (mp_tab_bar);
  connect (mp_tab_bar, SIGNAL (currentChanged (int)), this, SLOT (view_selected (int)));
#if QT_VERSION >= 0x040500
  mp_tab_bar->setTabsClosable(true);
  connect (mp_tab_bar, SIGNAL (tabCloseRequested (int)), this, SLOT (tab_close_requested (int)));
#endif

  mp_hp_dock_widget = new QDockWidget (QObject::tr ("Cells"), this);
  mp_hp_dock_widget->setObjectName (QString::fromAscii ("hp_dock_widget"));
  mp_hp_stack = new ControlWidgetStack (mp_hp_dock_widget, "hp_stack");
  mp_hp_dock_widget->setWidget (mp_hp_stack);
  connect (mp_hp_dock_widget, SIGNAL (visibilityChanged (bool)), this, SLOT (dock_widget_visibility_changed (bool)));
  m_hp_visible = true;

  mp_view_stack = new ViewWidgetStack (mp_main_frame);
  mp_view_stack->setObjectName (QString::fromAscii ("view_stack"));
  vbl->addWidget (mp_view_stack);

  mp_layer_toolbox_dock_widget = new QDockWidget (QObject::tr ("Layer Toolbox"), this);
  mp_layer_toolbox_dock_widget->setObjectName (QString::fromAscii ("lt_dock_widget"));
  mp_layer_toolbox = new LayerToolbox (mp_layer_toolbox_dock_widget, "layer_toolbox");
  mp_layer_toolbox_dock_widget->setWidget (mp_layer_toolbox);
  connect (mp_layer_toolbox_dock_widget, SIGNAL (visibilityChanged (bool)), this, SLOT (dock_widget_visibility_changed (bool)));
  m_layer_toolbox_visible = true;

  mp_lp_dock_widget = new QDockWidget (QObject::tr ("Layers"), this);
  mp_lp_dock_widget->setObjectName (QString::fromAscii ("lp_dock_widget"));
  mp_lp_stack = new ControlWidgetStack (mp_lp_dock_widget, "lp_stack");
  mp_lp_dock_widget->setWidget (mp_lp_stack);
  connect (mp_lp_dock_widget, SIGNAL (visibilityChanged (bool)), this, SLOT (dock_widget_visibility_changed (bool)));
  m_lp_visible = true;

  mp_navigator_dock_widget = new QDockWidget (QObject::tr ("Navigator"), this);
  mp_navigator_dock_widget->setObjectName (QString::fromAscii ("navigator_dock_widget"));
  mp_navigator = new Navigator (this);
  mp_navigator_dock_widget->setWidget (mp_navigator);
  connect (mp_navigator_dock_widget, SIGNAL (visibilityChanged (bool)), this, SLOT (dock_widget_visibility_changed (bool)));
  m_navigator_visible = true;

  //  Add dock widgets
#if QT_VERSION >= 0x040500
  setTabPosition (Qt::AllDockWidgetAreas, QTabWidget::North);
#endif
  addDockWidget(Qt::LeftDockWidgetArea, mp_navigator_dock_widget);
  addDockWidget(Qt::LeftDockWidgetArea, mp_hp_dock_widget);
  addDockWidget(Qt::RightDockWidgetArea, mp_lp_dock_widget);
  addDockWidget(Qt::RightDockWidgetArea, mp_layer_toolbox_dock_widget);

  mp_tool_bar = new QToolBar (this);
  mp_tool_bar->setWindowTitle (QObject::tr ("Toolbar"));
  mp_tool_bar->setObjectName (QString::fromAscii ("toolbar"));
  mp_tool_bar->setMovable (false);
  mp_tool_bar->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);
  addToolBar (Qt::TopToolBarArea, mp_tool_bar);

  QMenuBar *mbar = menuBar ();
  mbar->setObjectName (QString::fromAscii ("menubar"));

  mp_menu->build (mbar, mp_tool_bar);

  connect (mp_menu, SIGNAL (changed ()), this, SLOT (menu_changed ()));

  mp_status_bar = statusBar ();
  mp_status_bar->setObjectName (QString::fromAscii ("status_bar"));

  QLabel *tech_status_icon = new QLabel (mp_status_bar);
  tech_status_icon->setText(QString::fromAscii ("<html>&nbsp;<b>T</b></html>"));
  mp_status_bar->addWidget (tech_status_icon);

  mp_tech_status_label = new QLabel (mp_status_bar);
  mp_tech_status_label->setObjectName (QString::fromAscii ("tech_status_label"));
  mp_tech_status_label->setMinimumSize (QSize (100, 0));
  mp_tech_status_label->setToolTip (QObject::tr ("Current technology")); 
  mp_status_bar->addWidget (mp_tech_status_label);

  QLabel *sel_status_icon = new QLabel (mp_status_bar);
  sel_status_icon->setText(QString::fromAscii ("<html><b>&nbsp;&nbsp;G</b></html>"));
  mp_status_bar->addWidget (sel_status_icon);

  mp_msg_label = new QLabel (mp_status_bar);
  mp_msg_label->setObjectName (QString::fromAscii ("msg_label"));
  mp_msg_label->setToolTip (QObject::tr ("General status")); 
  mp_status_bar->addWidget (mp_msg_label, 1);

  QLabel *xy_status_icon = new QLabel (mp_status_bar);
  xy_status_icon->setText(QString::fromAscii ("<html><b>&nbsp;&nbsp;xy</b></html>"));
  mp_status_bar->addWidget (xy_status_icon);

  mp_cp_frame = new QFrame (mp_status_bar);
  mp_status_bar->addWidget (mp_cp_frame);

  QHBoxLayout *cp_frame_ly = new QHBoxLayout (mp_cp_frame);
  cp_frame_ly->setMargin (0);
  cp_frame_ly->setSpacing (0);
  mp_cpx_label = new QLabel (mp_cp_frame);
  mp_cpx_label->setObjectName (QString::fromAscii ("cpx_label"));
  mp_cpx_label->setAlignment (Qt::AlignVCenter | Qt::AlignRight);
  mp_cpx_label->setMinimumSize (100, 0);
  mp_cpx_label->setToolTip (QObject::tr ("Current cursor position (x)")); 
  cp_frame_ly->addWidget (mp_cpx_label);
  cp_frame_ly->insertSpacing (-1, 6);
  mp_cpy_label = new QLabel (mp_cp_frame);
  mp_cpy_label->setObjectName (QString::fromAscii ("cpy_label"));
  mp_cpy_label->setAlignment (Qt::AlignVCenter | Qt::AlignRight);
  mp_cpy_label->setMinimumSize (100, 0);
  mp_cpy_label->setToolTip (QObject::tr ("Current cursor position (y)")); 
  cp_frame_ly->addWidget (mp_cpy_label);
  cp_frame_ly->insertSpacing (-1, 6);

  //  connect to the menus to provide the dynamic parts
  QMenu *edit_menu = mp_menu->menu ("edit_menu");
  tl_assert (edit_menu != 0);
  connect (edit_menu, SIGNAL (aboutToShow ()), this, SLOT (popup_menu_show ()));
  connect (edit_menu, SIGNAL (aboutToHide ()), this, SLOT (popup_menu_hide ()));

  QMenu *zoom_menu = mp_menu->menu ("zoom_menu");
  tl_assert (zoom_menu != 0);
  connect (zoom_menu, SIGNAL (aboutToShow ()), this, SLOT (popup_menu_show ()));
  connect (zoom_menu, SIGNAL (aboutToHide ()), this, SLOT (popup_menu_hide ()));

  QMenu *bookmark_menu = mp_menu->menu ("bookmark_menu");
  tl_assert (bookmark_menu != 0);
  connect (bookmark_menu, SIGNAL (aboutToShow ()), this, SLOT (bookmark_menu_show ()));

  QMenu *file_menu = mp_menu->menu ("file_menu");
  tl_assert (file_menu != 0);
  connect (file_menu, SIGNAL (aboutToShow ()), this, SLOT (file_menu_show ()));

  //  select the default mode
  select_mode (lay::LayoutView::default_mode ());

  //  create file dialogs:

  //  session file dialog
  mp_session_fdia = new lay::FileDialog (this, 
                          tl::to_string (QObject::tr ("Session File")), 
                          tl::to_string (QObject::tr ("Session files (*.lys);;All files (*)")), 
                          "lys");

  //  bookmarks file dialog
  mp_bookmarks_fdia = new lay::FileDialog (this, 
                            tl::to_string (QObject::tr ("Bookmarks File")), 
                            tl::to_string (QObject::tr ("Bookmark files (*.lyb);;All files (*)")), 
                            "lyb");
  //  layer properties
  mp_lprops_fdia = new lay::FileDialog (this, 
                            tl::to_string (QObject::tr ("Layer Properties File")), 
                            tl::to_string (QObject::tr ("Layer properties files (*.lyp);;All files (*)")), 
                            "lyp");
  //  screenshots
  mp_screenshot_fdia = new lay::FileDialog (this, 
                            tl::to_string (QObject::tr ("Screenshot")), 
                            tl::to_string (QObject::tr ("PNG files (*.png);;All files (*)")), 
                            "png");

  
  //  layout file dialog
  std::string fmts = tl::to_string (QObject::tr ("All layout files ("));
  for (tl::Registrar<db::StreamFormatDeclaration>::iterator rdr = tl::Registrar<db::StreamFormatDeclaration>::begin (); rdr != tl::Registrar<db::StreamFormatDeclaration>::end (); ++rdr) {
    if (rdr != tl::Registrar<db::StreamFormatDeclaration>::begin ()) {
      fmts += " ";
    }
    std::string f = rdr->file_format ();
    const char *fp = f.c_str ();
    while (*fp && *fp != '(') {
      ++fp;
    }
    if (*fp) {
      ++fp;
    }
    while (*fp && *fp != ')') {
      fmts += *fp++;
    }
  }
  fmts += ");;";
  for (tl::Registrar<db::StreamFormatDeclaration>::iterator rdr = tl::Registrar<db::StreamFormatDeclaration>::begin (); rdr != tl::Registrar<db::StreamFormatDeclaration>::end (); ++rdr) {
    fmts += rdr->file_format ();
    fmts += ";;";
  }
  fmts += tl::to_string (QObject::tr ("All files (*)"));
  mp_layout_fdia = new lay::FileDialog (this, tl::to_string (QObject::tr ("Layout File")), fmts);

  //  save & load layout options
  mp_layout_save_as_options = new lay::SaveLayoutAsOptionsDialog (this, tl::to_string (QObject::tr ("Save Layout Options")));
  mp_layout_save_options = new lay::SaveLayoutOptionsDialog (this, tl::to_string (QObject::tr ("Layout Writer Options")));
  mp_layout_load_options = new lay::LoadLayoutOptionsDialog (this, tl::to_string (QObject::tr ("Layout Reader Options")));

  //  log viewer dialog
  mp_log_viewer_dialog = new lay::LogViewerDialog (0);

  //  install timer for message timeout
  connect (&m_message_timer, SIGNAL (timeout ()), this, SLOT (message_timer ()));
  m_message_timer.setSingleShot (true);

  //  make the main window accept drops
  setAcceptDrops (true);
}

MainWindow::~MainWindow ()
{
  //  uninitialize the plugins (this should be the first action in the constructor since the
  //  main window should be functional still.
  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    lay::PluginDeclaration *pd = const_cast<lay::PluginDeclaration *> (&*cls);
    pd->uninitialize (this);
  }

  //  since the configuration actions unregister themselves, we need to do this before the main
  //  window is gone:
  m_ca_collection.clear ();

  mw_instance = 0;

  //  explicitly delete the views here. Otherwise they
  //  are deleted by ~QWidget, which is too late since then
  //  the manager does not exist any longer.
  m_view_closed_observers.remove_observers (); // don't send events
  close_all ();

  //  delete the Menu after the views because they may want to access them in the destructor

  delete mp_menu;
  mp_menu = 0;

  delete mp_pr;
  mp_pr = 0;

  delete mp_setup_form;
  mp_setup_form = 0;

  delete mp_log_viewer_dialog;
  mp_log_viewer_dialog = 0;

  delete mp_macro_editor;
  mp_macro_editor = 0;

  delete mp_assistant;
  mp_assistant = 0;

  mp_progress_dialog.reset (0);
}

void 
MainWindow::init_menu ()
{
  //  default menu layout
  
  MenuLayoutEntry empty_menu [] = {
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry file_menu [] = {
    MenuLayoutEntry ("new_layout:edit:edit_mode",       tl::to_string (QObject::tr ("New Layout")),                       SLOT (cm_new_layout ())),
    MenuLayoutEntry ("new_panel:edit:edit_mode",        tl::to_string (QObject::tr ("New Panel")),                        SLOT (cm_new_panel ())),
    MenuLayoutEntry::separator ("post_new_group:edit_mode"),
    MenuLayoutEntry ("open:edit",                       tl::to_string (QObject::tr ("Open")),                             SLOT (cm_open ())),
    MenuLayoutEntry ("open_same_panel:edit",            tl::to_string (QObject::tr ("Open In Same Panel(Shift+Ctrl+O)")), SLOT (cm_open_too ())),
    MenuLayoutEntry ("open_new_panel:edit",             tl::to_string (QObject::tr ("Open In New Panel(Ctrl+O)")),        SLOT (cm_open_new_view ())),
    MenuLayoutEntry ("close:edit",                      tl::to_string (QObject::tr ("Close(Ctrl+W)")),                    SLOT (cm_close ())),
    MenuLayoutEntry ("close_all:edit",                  tl::to_string (QObject::tr ("Close All(Shift+Ctrl+W)")),          SLOT (cm_close_all ())),
    MenuLayoutEntry ("clone",                           tl::to_string (QObject::tr ("Clone Panel")),                      SLOT (cm_clone ())),
    MenuLayoutEntry ("reload:edit",                     tl::to_string (QObject::tr ("Reload(Ctrl+R)")),                   SLOT (cm_reload ())),
    MenuLayoutEntry ("pull_in:edit",                    tl::to_string (QObject::tr ("Pull In Other Layout")),             SLOT (cm_pull_in ())),
    MenuLayoutEntry ("reader_options",                  tl::to_string (QObject::tr ("Reader Options")),                   SLOT (cm_reader_options ())),
    MenuLayoutEntry::separator ("open_recent_group"),
    MenuLayoutEntry ("open_recent_menu:edit",           tl::to_string (QObject::tr ("Open Recent")),                      empty_menu),
    MenuLayoutEntry::separator ("import_group"),
    MenuLayoutEntry ("import_menu:edit",                tl::to_string (QObject::tr ("Import")),                           empty_menu),
    MenuLayoutEntry::separator ("save_group"),
    MenuLayoutEntry ("save:hide_vo",                    tl::to_string (QObject::tr ("Save")),                             SLOT (cm_save ())),
    MenuLayoutEntry ("save_as:hide_vo",                 tl::to_string (QObject::tr ("Save As")),                          SLOT (cm_save_as ())),
    MenuLayoutEntry ("save_all:hide_vo",                tl::to_string (QObject::tr ("Save All")),                         SLOT (cm_save_all ())),
    MenuLayoutEntry ("writer_options:hide_vo",          tl::to_string (QObject::tr ("Writer Options")),                   SLOT (cm_writer_options ())),
    MenuLayoutEntry::separator ("setup_group"),
    MenuLayoutEntry ("setup:edit",                      tl::to_string (QObject::tr ("Setup")),                            SLOT (cm_setup ())),
    MenuLayoutEntry::separator ("misc_group"),
    MenuLayoutEntry ("screenshot:edit",                 tl::to_string (QObject::tr ("Screenshot(Print)")),                SLOT (cm_screenshot ())),
    MenuLayoutEntry ("layout_props",                    tl::to_string (QObject::tr ("Layout Properties")),                SLOT (cm_layout_props ())),
    MenuLayoutEntry ("layout_stats",                    tl::to_string (QObject::tr ("Layout Statistics")),                SLOT (cm_layout_stats ())),
    MenuLayoutEntry::separator ("layer_group"),
    MenuLayoutEntry ("load_layer_props:edit",           tl::to_string (QObject::tr ("Load Layer Properties")),            SLOT (cm_load_layer_props ())),
    MenuLayoutEntry ("save_layer_props:edit",           tl::to_string (QObject::tr ("Save Layer Properties")),            SLOT (cm_save_layer_props ())),
    MenuLayoutEntry::separator ("session_group"),
    MenuLayoutEntry ("restore_session",                 tl::to_string (QObject::tr ("Restore Session")),                  SLOT (cm_restore_session ())),
    MenuLayoutEntry ("save_session",                    tl::to_string (QObject::tr ("Save Session")),                     SLOT (cm_save_session ())),
    MenuLayoutEntry::separator ("log_group"),
    MenuLayoutEntry ("view_log",                        tl::to_string (QObject::tr ("Log Viewer")),                       SLOT (cm_view_log ())),
    MenuLayoutEntry::separator ("print_group"),
    MenuLayoutEntry ("print",                           tl::to_string (QObject::tr ("Print(Ctrl+P)")),                    SLOT (cm_print ())),
    MenuLayoutEntry::separator ("exit_group"),
    MenuLayoutEntry ("exit",                            tl::to_string (QObject::tr ("Exit(Ctrl+Q)")),                     SLOT (cm_exit ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry edit_utilities_menu [] = {
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry edit_layout_menu [] = {
    MenuLayoutEntry ("lay_flip_x:edit_mode",            tl::to_string (QObject::tr ("Flip Horizontally")),                SLOT (cm_lay_flip_x ())),
    MenuLayoutEntry ("lay_flip_y:edit_mode",            tl::to_string (QObject::tr ("Flip Vertically")),                  SLOT (cm_lay_flip_y ())),
    MenuLayoutEntry ("lay_rot_cw:edit_mode",            tl::to_string (QObject::tr ("Rotate Clockwise")),                 SLOT (cm_lay_rot_cw ())),
    MenuLayoutEntry ("lay_rot_ccw:edit_mode",           tl::to_string (QObject::tr ("Rotate Counterclockwise")),          SLOT (cm_lay_rot_ccw ())),
    MenuLayoutEntry ("lay_free_rot:edit_mode",          tl::to_string (QObject::tr ("Rotation By Angle")),                SLOT (cm_lay_free_rot ())),
    MenuLayoutEntry ("lay_scale:edit_mode",             tl::to_string (QObject::tr ("Scale")),                            SLOT (cm_lay_scale ())),
    MenuLayoutEntry ("lay_move:edit_mode",              tl::to_string (QObject::tr ("Move By")),                          SLOT (cm_lay_move ())),
    MenuLayoutEntry::separator ("cellop_group"),
    MenuLayoutEntry ("lay_convert_to_static:edit_mode", tl::to_string (QObject::tr ("Convert All Cells To Static")),      SLOT (cm_lay_convert_to_static ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry edit_cell_menu [] = {
    MenuLayoutEntry ("new_cell:edit:edit_mode",         tl::to_string (QObject::tr ("New Cell")),                         SLOT (cm_new_cell ())),
    MenuLayoutEntry ("delete_cell:edit:edit_mode",      tl::to_string (QObject::tr ("Delete Cell")),                      SLOT (cm_cell_delete ())),
    MenuLayoutEntry ("rename_cell:edit:edit_mode",      tl::to_string (QObject::tr ("Rename Cell")),                      SLOT (cm_cell_rename ())),
    MenuLayoutEntry ("replace_cell:edit:edit_mode",     tl::to_string (QObject::tr ("Replace Cell")),                     SLOT (cm_cell_replace ())),
    MenuLayoutEntry ("flatten_cell:edit:edit_mode",     tl::to_string (QObject::tr ("Flatten Cell")),                     SLOT (cm_cell_flatten ())),
    MenuLayoutEntry::separator ("ops_group"),
    MenuLayoutEntry ("adjust_cell_origin:edit:edit_mode", tl::to_string (QObject::tr ("Adjust Origin")),                  SLOT (cm_adjust_origin ())),
    MenuLayoutEntry ("convert_cell_to_static:edit_mode", tl::to_string (QObject::tr ("Convert Cell To Static")),          SLOT (cm_cell_convert_to_static ())),
    MenuLayoutEntry::separator ("props_group"),
    MenuLayoutEntry ("user_properties",                 tl::to_string (QObject::tr ("User Properties")),                  SLOT (cm_cell_user_properties ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry edit_layer_menu [] = {
    MenuLayoutEntry ("new_layer:edit:edit_mode",        tl::to_string (QObject::tr ("New Layer")),                        SLOT (cm_new_layer ())),
    MenuLayoutEntry ("clear_layer:edit:edit_mode",      tl::to_string (QObject::tr ("Clear Layer")),                      SLOT (cm_clear_layer ())),
    MenuLayoutEntry ("delete_layer:edit:edit_mode",     tl::to_string (QObject::tr ("Delete Layer")),                     SLOT (cm_delete_layer ())),
    MenuLayoutEntry ("copy_layer:edit:edit_mode",       tl::to_string (QObject::tr ("Copy Layer")),                       SLOT (cm_copy_layer ())),
    MenuLayoutEntry ("edit_layer:edit:edit_mode",       tl::to_string (QObject::tr ("Edit Layer Specification")),         SLOT (cm_edit_layer ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry edit_selection_menu [] = {
    MenuLayoutEntry ("sel_flip_x:edit_mode",            tl::to_string (QObject::tr ("Flip Horizontally")),                SLOT (cm_sel_flip_x ())),
    MenuLayoutEntry ("sel_flip_y:edit_mode",            tl::to_string (QObject::tr ("Flip Vertically")),                  SLOT (cm_sel_flip_y ())),
    MenuLayoutEntry ("sel_rot_cw:edit_mode",            tl::to_string (QObject::tr ("Rotate Clockwise")),                 SLOT (cm_sel_rot_cw ())),
    MenuLayoutEntry ("sel_rot_ccw:edit_mode",           tl::to_string (QObject::tr ("Rotate Counterclockwise")),          SLOT (cm_sel_rot_ccw ())),
    MenuLayoutEntry ("sel_free_rot:edit_mode",          tl::to_string (QObject::tr ("Rotation By Angle")),                SLOT (cm_sel_free_rot ())),
    MenuLayoutEntry ("sel_scale:edit_mode",             tl::to_string (QObject::tr ("Scale")),                            SLOT (cm_sel_scale ())),
    MenuLayoutEntry ("sel_move:edit_mode",              tl::to_string (QObject::tr ("Move By")),                          SLOT (cm_sel_move ())),
    MenuLayoutEntry ("sel_move_to:edit_mode",           tl::to_string (QObject::tr ("Move To")),                          SLOT (cm_sel_move_to ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry view_menu [] = {
    MenuLayoutEntry ("show_grid",                       tl::to_string (QObject::tr ("Show Grid")),                        std::make_pair (cfg_grid_visible, "?")),
    MenuLayoutEntry ("default_grid:default_grids_group", tl::to_string (QObject::tr ("Grid")),                            empty_menu),
    MenuLayoutEntry::separator ("layout_group"),
    MenuLayoutEntry ("show_texts",                      tl::to_string (QObject::tr ("Show Texts")),                       std::make_pair (cfg_text_visible, "?")),
    MenuLayoutEntry ("show_cell_boxes",                 tl::to_string (QObject::tr ("Show Cell Frames")),                 std::make_pair (cfg_cell_box_visible, "?")),
    MenuLayoutEntry ("no_stipples",                     tl::to_string (QObject::tr ("Show Layers Without Fill")),         std::make_pair (cfg_no_stipple, "?")),
    MenuLayoutEntry ("synchronized_views", tl::to_string (QObject::tr ("Synchronized Views")),   std::make_pair (cfg_synchronized_views, "?")),
    MenuLayoutEntry ("edit_top_level_selection:edit_mode", tl::to_string (QObject::tr ("Select Top Level Objects")),   std::make_pair (edt::cfg_edit_top_level_selection, "?")),
    MenuLayoutEntry::separator ("panels_group"),
    MenuLayoutEntry ("show_toolbar",                    tl::to_string (QObject::tr ("Toolbar")),                          std::make_pair (cfg_show_toolbar, "?")),
    MenuLayoutEntry ("show_navigator",                  tl::to_string (QObject::tr ("Navigator")),                        std::make_pair (cfg_show_navigator, "?")),
    MenuLayoutEntry ("show_layer_panel",                tl::to_string (QObject::tr ("Layers")),                           std::make_pair (cfg_show_layer_panel, "?")),
    MenuLayoutEntry ("show_layer_toolbox",              tl::to_string (QObject::tr ("Layer Toolbox")),                    std::make_pair (cfg_show_layer_toolbox, "?")),
    MenuLayoutEntry ("show_hierarchy_panel",            tl::to_string (QObject::tr ("Cells")),                            std::make_pair (cfg_show_hierarchy_panel, "?")),
    MenuLayoutEntry::separator ("selection_group"),
    MenuLayoutEntry ("transient_selection",             tl::to_string (QObject::tr ("Highlight Object Under Mouse")),     std::make_pair (cfg_sel_transient_mode, "?")),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry edit_select_menu [] = {
    MenuLayoutEntry ("select_all",                      tl::to_string (QObject::tr ("Select All")),                       SLOT (cm_select_all ())),
    MenuLayoutEntry ("unselect_all",                    tl::to_string (QObject::tr ("Unselect All")),                     SLOT (cm_unselect_all ())),
    MenuLayoutEntry::separator ("edit_select_basic_group"),
    MenuLayoutEntry ("enable_all",                      tl::to_string (QObject::tr ("Enable All")),                       SLOT (enable_all ())),
    MenuLayoutEntry ("disable_all",                     tl::to_string (QObject::tr ("Disable All")),                      SLOT (disable_all ())),
    MenuLayoutEntry::separator ("edit_select_individual_group"),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry edit_menu [] = {
    MenuLayoutEntry ("undo:edit",                       tl::to_string (QObject::tr ("Undo(Ctrl+Z)")),                     SLOT (cm_undo ())),
    MenuLayoutEntry ("redo:edit",                       tl::to_string (QObject::tr ("Redo(Ctrl+Y)")),                     SLOT (cm_redo ())),
    MenuLayoutEntry::separator ("basic_group"),
    MenuLayoutEntry ("layout_menu:edit:edit_mode",      tl::to_string (QObject::tr ("Layout")),                           edit_layout_menu),
    MenuLayoutEntry ("cell_menu:edit:edit_mode",        tl::to_string (QObject::tr ("Cell")),                             edit_cell_menu),
    MenuLayoutEntry ("layer_menu:edit:edit_mode",       tl::to_string (QObject::tr ("Layer")),                            edit_layer_menu),
    MenuLayoutEntry ("selection_menu:edit:edit_mode",   tl::to_string (QObject::tr ("Selection")),                        edit_selection_menu),
    MenuLayoutEntry::separator ("utils_group"),
    MenuLayoutEntry ("utils_menu:edit:edit_mode",       tl::to_string (QObject::tr ("Utilities")),                        edit_utilities_menu),
    MenuLayoutEntry::separator ("misc_group") ,
    MenuLayoutEntry ("delete:edit",                     tl::to_string (QObject::tr ("Delete(Del)")),                      SLOT (cm_delete ())),
    MenuLayoutEntry ("show_properties:edit",            tl::to_string (QObject::tr ("Properties(Q)")),                    SLOT (cm_show_properties ())),
    MenuLayoutEntry::separator ("cpc_group"),
    MenuLayoutEntry ("copy:edit",                       tl::to_string (QObject::tr ("Copy(Ctrl+C)")),                     SLOT (cm_copy ())),
    MenuLayoutEntry ("cut:edit",                        tl::to_string (QObject::tr ("Cut(Ctrl+X)")),                      SLOT (cm_cut ())),
    MenuLayoutEntry ("paste:edit",                      tl::to_string (QObject::tr ("Paste(Ctrl+V)")),                    SLOT (cm_paste ())),
    MenuLayoutEntry ("duplicate:edit",                  tl::to_string (QObject::tr ("Duplicate(Ctrl+B)")),                SLOT (cm_duplicate ())),
    MenuLayoutEntry::separator ("modes_group"),
    MenuLayoutEntry ("mode_menu",                       tl::to_string (QObject::tr ("Mode")),                             empty_menu),
    MenuLayoutEntry ("select_menu",                     tl::to_string (QObject::tr ("Select")),                           edit_select_menu),
    MenuLayoutEntry::separator ("cancel_group"),
    MenuLayoutEntry ("cancel",                          tl::to_string (QObject::tr ("Cancel(Esc)")),                      SLOT (cm_cancel ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry bookmark_menu [] = {
    MenuLayoutEntry ("goto_bookmark_menu",              tl::to_string (QObject::tr ("Goto Bookmark")),                    empty_menu),
    MenuLayoutEntry ("bookmark_view",                   tl::to_string (QObject::tr ("Bookmark This View")),               SLOT (cm_bookmark_view ())),
    MenuLayoutEntry::separator ("bookmark_mgm_group"),
    MenuLayoutEntry ("manage_bookmarks",                tl::to_string (QObject::tr ("Manage Bookmarks")),                 SLOT (cm_manage_bookmarks ())),
    MenuLayoutEntry ("load_bookmarks",                  tl::to_string (QObject::tr ("Load Bookmarks")),                   SLOT (cm_load_bookmarks ())),
    MenuLayoutEntry ("save_bookmarks",                  tl::to_string (QObject::tr ("Save Bookmarks")),                   SLOT (cm_save_bookmarks ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry global_trans_menu [] = {
    MenuLayoutEntry ("r0",                              tl::to_string (QObject::tr ("\\(r0\\)<:/r0.png>")),               std::make_pair (cfg_global_trans, "?r0 *1 0,0")),
    MenuLayoutEntry ("r90",                             tl::to_string (QObject::tr ("\\(r90\\)<:/r90.png>")),             std::make_pair (cfg_global_trans, "?r90 *1 0,0")),
    MenuLayoutEntry ("r180",                            tl::to_string (QObject::tr ("\\(r180\\)<:/r180.png>")),           std::make_pair (cfg_global_trans, "?r180 *1 0,0")),
    MenuLayoutEntry ("r270",                            tl::to_string (QObject::tr ("\\(r270\\)<:/r270.png>")),           std::make_pair (cfg_global_trans, "?r270 *1 0,0")),
    MenuLayoutEntry ("m0",                              tl::to_string (QObject::tr ("\\(m0\\)<:/m0.png>")),               std::make_pair (cfg_global_trans, "?m0 *1 0,0")),
    MenuLayoutEntry ("m45",                             tl::to_string (QObject::tr ("\\(m45\\)<:/m45.png>")),             std::make_pair (cfg_global_trans, "?m45 *1 0,0")),
    MenuLayoutEntry ("m90",                             tl::to_string (QObject::tr ("\\(m90\\)<:/m90.png>")),             std::make_pair (cfg_global_trans, "?m90 *1 0,0")),
    MenuLayoutEntry ("m135",                            tl::to_string (QObject::tr ("\\(m135\\)<:/m135.png>")),           std::make_pair (cfg_global_trans, "?m135 *1 0,0")),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry zoom_menu [] = {
    MenuLayoutEntry ("global_trans",                    tl::to_string (QObject::tr ("Global Transformation")),            global_trans_menu),
    MenuLayoutEntry ("synchronized_views",              tl::to_string (QObject::tr ("Synchronized Views")),               std::make_pair (cfg_synchronized_views, "?")),
    MenuLayoutEntry::separator ("hier_group"),
    MenuLayoutEntry ("max_hier",                        tl::to_string (QObject::tr ("Full Hierarchy(*)")),                SLOT (cm_max_hier ())),
    MenuLayoutEntry ("max_hier_0",                      tl::to_string (QObject::tr ("Box Only(0)")),                      SLOT (cm_max_hier_0 ())),
    MenuLayoutEntry ("max_hier_1",                      tl::to_string (QObject::tr ("Top Level Only(1)")),                SLOT (cm_max_hier_1 ())),
    MenuLayoutEntry ("inc_max_hier",                    tl::to_string (QObject::tr ("Increment Hierarchy(+)")),           SLOT (cm_inc_max_hier ())),
    MenuLayoutEntry ("dec_max_hier",                    tl::to_string (QObject::tr ("Decrement Hierarchy(-)")),           SLOT (cm_dec_max_hier ())),
    MenuLayoutEntry::separator ("zoom_group"),
    MenuLayoutEntry ("zoom_fit",                        tl::to_string (QObject::tr ("Zoom Fit(F2)")),                     SLOT (cm_zoom_fit ())),
    MenuLayoutEntry ("zoom_fit_sel",                    tl::to_string (QObject::tr ("Zoom Fit Selection(Shift+F2)")),     SLOT (cm_zoom_fit_sel ())),
    MenuLayoutEntry ("zoom_in",                         tl::to_string (QObject::tr ("Zoom In(Return)")),                  SLOT (cm_zoom_in ())),
    MenuLayoutEntry ("zoom_out",                        tl::to_string (QObject::tr ("Zoom Out(Shift+Return)")),           SLOT (cm_zoom_out ())),
    /* disabled because that interferes with the use of the arrow keys for moving the selection
    MenuLayoutEntry::separator ("pan_group"),
    MenuLayoutEntry ("pan_up",                          tl::to_string (QObject::tr ("Pan Up(Up)")),                       SLOT (cm_pan_up ())),
    MenuLayoutEntry ("pan_down",                        tl::to_string (QObject::tr ("Pan Down(Down)")),                   SLOT (cm_pan_down ())),
    MenuLayoutEntry ("pan_left",                        tl::to_string (QObject::tr ("Pan Left(Left)")),                   SLOT (cm_pan_left ())),
    MenuLayoutEntry ("pan_right",                       tl::to_string (QObject::tr ("Pan Right(Right)")),                 SLOT (cm_pan_right ())),
    */
    MenuLayoutEntry::separator ("redraw_group"),
    MenuLayoutEntry ("redraw",                          tl::to_string (QObject::tr ("Redraw")),                           SLOT (cm_redraw ())),
    MenuLayoutEntry::separator ("state_group"),
    MenuLayoutEntry ("last_display_state",              tl::to_string (QObject::tr ("Previous State(Shift+Tab)")),        SLOT (cm_last_display_state ())),
    MenuLayoutEntry ("next_display_state",              tl::to_string (QObject::tr ("Next State(Tab)")),                  SLOT (cm_next_display_state ())),
    MenuLayoutEntry::separator ("select_group"),
    MenuLayoutEntry ("select_cell:edit",                tl::to_string (QObject::tr ("Select Cell")),                      SLOT (cm_select_cell ())),
    MenuLayoutEntry ("select_current_cell",             tl::to_string (QObject::tr ("Show As New Top(Ctrl+S)")),          SLOT (cm_select_current_cell ())),
    MenuLayoutEntry ("goto_position",                   tl::to_string (QObject::tr ("Goto Position(Ctrl+G)")),            SLOT (cm_goto_position ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry help_menu [] = {
    MenuLayoutEntry ("show_all_tips",                   tl::to_string (QObject::tr ("Show All Tips")),                    SLOT (cm_show_all_tips ())),
    MenuLayoutEntry::separator ("help_topics_group"),
    MenuLayoutEntry ("assistant",                       tl::to_string (QObject::tr ("Assistant")),                        SLOT (cm_show_assistant ())),
    MenuLayoutEntry ("about",                           tl::to_string (QObject::tr ("About")),                            SLOT (cm_help_about ())),
    MenuLayoutEntry ("about_qt",                        tl::to_string (QObject::tr ("About Qt")),                         SLOT (cm_help_about_qt ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry drc_menu [] = {
    MenuLayoutEntry ("new_script",                      tl::to_string (QObject::tr ("New DRC Script")),                   SLOT (cm_new_drc_script ())),
    MenuLayoutEntry ("edit_script",                     tl::to_string (QObject::tr ("Edit DRC Script")),                  SLOT (cm_edit_drc_scripts ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry tools_menu [] = {
    MenuLayoutEntry ("technologies",                    tl::to_string (QObject::tr ("Manage Technologies")),              SLOT (cm_technologies ())),
    MenuLayoutEntry::separator ("verification_group"),
    MenuLayoutEntry ("drc",                             tl::to_string (QObject::tr ("DRC")),                              drc_menu),
    MenuLayoutEntry::separator ("post_verification_group"),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry macros_menu [] = {
    MenuLayoutEntry ("macro_development",               tl::to_string (QObject::tr ("Macro Development(F5)")),            SLOT (cm_macro_editor ())),
    MenuLayoutEntry::separator ("macros_group"),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry main_menu [] = {
    MenuLayoutEntry ("file_menu",                       tl::to_string (QObject::tr ("&File")),                            file_menu),
    MenuLayoutEntry ("edit_menu",                       tl::to_string (QObject::tr ("&Edit")),                            edit_menu),
    MenuLayoutEntry ("view_menu",                       tl::to_string (QObject::tr ("&View")),                            view_menu),
    MenuLayoutEntry ("bookmark_menu",                   tl::to_string (QObject::tr ("&Bookmarks")),                       bookmark_menu),
    MenuLayoutEntry ("zoom_menu",                       tl::to_string (QObject::tr ("&Display")),                         zoom_menu),
    MenuLayoutEntry ("tools_menu",                      tl::to_string (QObject::tr ("&Tools")),                           tools_menu),
    MenuLayoutEntry ("macros_menu",                     tl::to_string (QObject::tr ("&Macros")),                          macros_menu),
    MenuLayoutEntry::separator ("help_group"),
    MenuLayoutEntry ("help_menu",                       tl::to_string (QObject::tr ("&Help")),                            help_menu),
    MenuLayoutEntry ("@toolbar",                        "",                                                 empty_menu),
    MenuLayoutEntry::last ()
  };

  mp_menu = new AbstractMenu (this);
  mp_menu->init (main_menu);

  lay::LayoutView::init_menu (*mp_menu);
  lay::Navigator::init_menu (*mp_menu);

  //  Fill the mode menu file items from the intrinsic mouse modes 

  std::vector <std::string> mode_titles;
  lay::LayoutView::intrinsic_mouse_modes (&mode_titles);

  int mode_id = 0;
  for (std::vector <std::string>::const_iterator t = mode_titles.begin (); t != mode_titles.end (); ++t, --mode_id) {

    if (! t->empty ()) {

      //  extract first part, which is the name, separated by a tab from the title.
      std::string name = tl::sprintf ("mode_i%d", 1 - mode_id);
      std::string title = *t;
      const char *tab = strchr (t->c_str (), '\t');
      if (tab) {
        name = std::string (*t, 0, tab - t->c_str ());
        title = tab + 1;
      } 

      Action action (AbstractMenu::create_action (title));
      action.set_checkable (true);
      action.qaction ()->setData (QVariant (mode_id));
      action.add_to_exclusive_group (mp_menu, "mouse_mode_exclusive_group");

      mp_menu->insert_item ("edit_menu.mode_menu.end", name, action);
      mp_menu->insert_item ("@toolbar.end", name, action);

      gtf::action_connect (action.qaction (), SIGNAL (triggered ()), this, SLOT (mode ()));

    }

  }

  //  make the plugins create their menu items
  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    //  TODO: get rid of the const_cast hack
    const_cast <lay::PluginDeclaration *> (&*cls)->init_menu (this);
  }

  //  if in "viewer-only mode", hide all entries in the "hide_vo" group
  if ((lay::Application::instance () && lay::Application::instance ()->is_vo_mode ())) {
    std::vector<std::string> hide_vo_grp = mp_menu->group ("hide_vo");
    for (std::vector<std::string>::const_iterator g = hide_vo_grp.begin (); g != hide_vo_grp.end (); ++g) {
      mp_menu->action (*g).set_visible (false);
    }
  }

  //  if not in editable mode, hide all entries from "edit_mode" group
  if (! lay::Application::instance ()->is_editable ()) {
    std::vector<std::string> edit_mode_grp = mp_menu->group ("edit_mode");
    for (std::vector<std::string>::const_iterator g = edit_mode_grp.begin (); g != edit_mode_grp.end (); ++g) {
      mp_menu->action (*g).set_visible (false);
    }
  }

  //  get and store the initial (default) key bindings for restore in the setup dialog
  KeyBindingsConfigPage::set_default ();
}

void 
MainWindow::dock_widget_visibility_changed (bool visible)
{
  if (sender () == mp_lp_dock_widget) {
    config_set (cfg_show_layer_panel, tl::to_string (!mp_lp_dock_widget->isHidden ()));
  } else if (sender () == mp_hp_dock_widget) {
    config_set (cfg_show_hierarchy_panel, tl::to_string (!mp_hp_dock_widget->isHidden ()));
  } else if (sender () == mp_navigator_dock_widget) {
    config_set (cfg_show_navigator, tl::to_string (!mp_navigator_dock_widget->isHidden ()));
  } else if (sender () == mp_layer_toolbox_dock_widget) {
    config_set (cfg_show_layer_toolbox, tl::to_string (!mp_layer_toolbox_dock_widget->isHidden ()));
  }
}

void
MainWindow::close_all ()
{
  mp_layer_toolbox->set_view (0);

  //  try a smooth shutdown of the current view
  if (current_view ()) {
    current_view ()->deactivate ();
  }
  m_current_view = mp_views.size ();

  for (unsigned int i = 0; i < mp_views.size (); ++i) {
    mp_views [i]->stop ();
  }

  m_manager.clear ();

  //  Clear the tab bar
  bool f = m_disable_tab_selected;
  m_disable_tab_selected = true;
  while (mp_tab_bar->count () > 0) {
    mp_tab_bar->removeTab (mp_tab_bar->count () - 1);
  }
  m_disable_tab_selected = f;

  //  First pop the mp_views vector and then delete. This way,
  //  any callbacks issued during the deleting of the views do
  //  not find any invalid view pointers but rather nothing.
  while (mp_views.size () > 0) {

    m_view_closed_observers.signal_observers (int (mp_views.size () - 1));

    lay::LayoutView *view = mp_views.back ();
    mp_views.pop_back ();
    mp_lp_stack->removeWidget (mp_views.size ());
    mp_hp_stack->removeWidget (mp_views.size ());
    mp_view_stack->removeWidget (mp_views.size ());

    delete view;

  }

  update_dock_widget_state ();
}

void
MainWindow::about_to_exec ()
{
  //  do this now since we have a window where we can show the progress on the first call ..
  HelpDialog::build_index ();

  //  Give the plugins a change to do some last-minute initialisation and checks
  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    lay::PluginDeclaration *pd = const_cast<lay::PluginDeclaration *> (&*cls);
    pd->initialized (this);
  }

  bool f;

  if (! lay::Application::instance ()->is_editable ()) {
    TipDialog td (this, 
                  tl::to_string (QObject::tr ("KLayout has been started in viewer mode. In this mode, editor functions are not available.\n\nTo enable these functions, start KLayout in editor mode by using the \"-e\" command line switch or select it as the default mode in the setup dialog. Choose \"Setup\" in the \"File\" menu and check \"Use editing mode by default\" on the \"Editing Mode\" page in the \"Application\" section.")), 
                  "editor-mode");
    if (td.exec_dialog ()) {
      //  Don't bother the user with more dialogs.
      return;
    }
  }

  f = false;
  config_get (cfg_no_stipple, f);
  if (f) {
    TipDialog td (this, 
                  tl::to_string (QObject::tr ("Layers are shown without fill because fill has been intentionally turned off. This can be confusing since selecting a stipple does not have an effect in this case.\n\nTo turn this feature off, uncheck \"Show Layers Without Fill\" in the \"View\" menu.")), 
                  "no-stipple");
    if (td.exec_dialog ()) {
      //  Don't bother the user with more dialogs.
      return;
    }
  }

  f = false;
  config_get (cfg_hide_empty_layers, f);
  if (f) {
    TipDialog td (this, 
                  tl::to_string (QObject::tr ("The \"Hide Empty Layers\" feature is enabled. This can be confusing, in particular in edit mode, because layers are not shown although they are actually present.\n\nTo disable this feature, uncheck \"Hide Empty Layers\" in the layer panel's context menu.")), 
                  "hide-empty-layers");
    if (td.exec_dialog ()) {
      //  Don't bother the user with more dialogs.
      return;
    }
  }

  //  TODO: other tip-of-the-day dialogs?
}

void 
MainWindow::tech_message (const std::string &s)
{
  mp_tech_status_label->setText(tl::to_qstring (s));
}

void 
MainWindow::format_message ()
{
  QFontMetrics fm (mp_msg_label->font ());

  std::string full_message;
  for (const char *c = m_message.c_str (); *c; ++c) {
    if (*c == '\\' && (c[1] == '(' || c[1] == ')')) {
      ++c;
    } else {
      full_message += *c;
    }
  }

  std::string short_message;
  size_t ndrop = 0;
  size_t prev_len = 0;
  bool use_ellipsis = true;

  do {

    size_t nsection = 0;
    bool in_drop = false;
    prev_len = ndrop > 0 ? short_message.size () : std::numeric_limits<size_t>::max ();

    short_message.clear ();

    for (const char *c = m_message.c_str (); *c; ++c) {
      if (*c == '\\' && c[1] == '(') {
        if (nsection++ < ndrop) {
          in_drop = true;
          if (use_ellipsis) {
            short_message += "...";
            use_ellipsis = false;
          }
        }
        ++c;
      } else if (*c == '\\' && c[1] == ')') {
        in_drop = false;
        ++c;
      } else if (! in_drop) {
        use_ellipsis = true;
        short_message += *c;
      }
    }

    ++ndrop;

  } while (short_message.size () < prev_len && fm.width (QString::fromAscii (" ") + tl::to_qstring (short_message)) > mp_msg_label->width ());

  mp_msg_label->setText (QString::fromAscii (" ") + tl::to_qstring (short_message));
  mp_msg_label->setToolTip (tl::to_qstring (full_message));
}

void 
MainWindow::message (const std::string &s, int ms)
{
  m_message = s;
  format_message ();
  m_message_timer.start (ms);
}

void 
MainWindow::message_timer ()
{
  m_message.clear ();
  format_message ();
}

void
MainWindow::config_finalize ()
{
  lay::get_from_config (m_reader_options, this);

  // Not set the window state: this ensures we have handled cfg_window_geometry 
  // before we restore the state
  if (! m_config_window_state.empty ()) {
    QByteArray state = QByteArray::fromBase64 (m_config_window_state.c_str ());
    m_config_window_state.clear ();
    restoreState (state);
  }

  // Update the default grids menu if necessary
  if (m_default_grids_updated) {

    m_default_grids_updated = false;

    std::vector<std::string> group = menu ().group ("default_grids_group");

    for (std::vector<std::string>::const_iterator t = group.begin (); t != group.end (); ++t) {
      std::vector<std::string> items = menu ().items (*t);        
      for (std::vector<std::string>::const_iterator i = items.begin (); i != items.end (); ++i) {
        menu ().delete_item (*i);
      }
    }

    for (std::vector<lay::Action *>::iterator a = m_default_grid_actions.begin (); a != m_default_grid_actions.end (); ++a) {
      delete *a;
    }
    m_default_grid_actions.clear ();

    int i = 1;
    for (std::vector<double>::const_iterator g = m_default_grids.begin (); g != m_default_grids.end (); ++g, ++i) {

      std::string name = "default_grid_" + tl::to_string (i);

      m_default_grid_actions.push_back (create_config_action (tl::to_string (*g) + tl::to_string (QObject::tr (" um")), cfg_grid, tl::to_string (*g)));

      m_default_grid_actions.back ()->set_checkable (true);
      m_default_grid_actions.back ()->set_checked (fabs (*g - m_grid_micron) < 1e-10);

      for (std::vector<std::string>::const_iterator t = group.begin (); t != group.end (); ++t) {
        menu ().insert_item (*t + ".end", name, *m_default_grid_actions.back ());
      }

    }

    //  re-apply key bindings for the default grids
    apply_key_bindings ();

  }

  //  make the changes visible in the setup form if the form is visible 
  mp_setup_form->setup ();
}

bool 
MainWindow::configure (const std::string &name, const std::string &value)
{
  std::map<std::string, std::vector<lay::ConfigureAction *> >::iterator ca = m_configuration_actions.find (name);
  if (ca != m_configuration_actions.end ()) {
    for (std::vector<lay::ConfigureAction *>::const_iterator a = ca->second.begin (); a != ca->second.end (); ++a) {
      (*a)->configure (value);
    }
  }

  if (name == cfg_grid) {

    double g = 0.0;
    tl::from_string (value, g);
    m_grid_micron = g;
    m_default_grids_updated = true;
    return false; // not taken - let others set it too.

  } else if (name == cfg_circle_points) {

    //  pseudo-configuration: set db::set_num_circle_points 
    int cp = 16;
    tl::from_string (value, cp);
    if (cp != int (db::num_circle_points ())) {
      db::set_num_circle_points (cp);
      redraw ();
    }
    return true;

  } else if (name == cfg_default_grids) {

    tl::Extractor ex (value.c_str ());
    m_default_grids.clear ();
    m_default_grids_updated = true;

    //  convert the list of grids to a list of doubles 
    while (! ex.at_end ()) {
      double g = 0.0;
      if (! ex.try_read (g)) {
        break;
      }
      m_default_grids.push_back (g);
      ex.test (",");
    }

    return true;

  } else if (name == cfg_stipple_palette) {

    lay::StipplePalette palette = lay::StipplePalette::default_palette ();

    try {
      //  empty string means: default palette
      if (! value.empty ()) {
        palette.from_string (value);
      }
    } catch (...) {
      //  ignore errors: just reset the palette 
      palette = lay::StipplePalette::default_palette ();
    }

    mp_layer_toolbox->set_palette (palette);

    // others need this property too ..
    return false;

  } else if (name == cfg_color_palette) {

    lay::ColorPalette palette = lay::ColorPalette::default_palette ();

    try {
      //  empty string means: default palette
      if (! value.empty ()) {
        palette.from_string (value);
      }
    } catch (...) {
      //  ignore errors: just reset the palette 
      palette = lay::ColorPalette::default_palette ();
    }

    mp_layer_toolbox->set_palette (palette);

    // others need this property too ..
    return false;

  } else if (name == cfg_mru) {

    tl::Extractor ex (value.c_str ());

    m_mru.clear ();
    while (! ex.at_end ()) {
      m_mru.push_back (std::make_pair (std::string (), std::string ()));
      ex.read_quoted (m_mru.back ().first);
      if (ex.test ("@")) {
        ex.read_quoted (m_mru.back ().second);
      }
    }

    return true;

  } else if (name == cfg_micron_digits) {

    unsigned int d = 5;
    tl::from_string (value, d);
    tl::set_micron_resolution (d);

    return true;

  } else if (name == cfg_dbu_digits) {

    unsigned int d = 2;
    tl::from_string (value, d);
    tl::set_db_resolution (d);

    return true;

  } else if (name == cfg_window_state) {

    //  restore the state on config_finalize to ensure we have handled it after 
    //  restoring the geometry
    m_config_window_state = value;
    return true;

  } else if (name == cfg_window_geometry) {

    if (! value.empty ()) {
      QByteArray state = QByteArray::fromBase64 (value.c_str ());
      restoreGeometry (state);
    }

    return true;

  } else if (name == cfg_show_layer_toolbox) {

    tl::from_string (value, m_layer_toolbox_visible);
    if (m_layer_toolbox_visible) {
      mp_layer_toolbox_dock_widget->show ();
    } else {
      mp_layer_toolbox_dock_widget->hide ();
    }

    return true;

  } else if (name == cfg_reader_options_show_always) {

    bool f = false;
    tl::from_string (value, f);
    mp_layout_load_options->show_always (f);

    return true;

  } else if (name == cfg_show_navigator) {

    tl::from_string (value, m_navigator_visible);
    if (m_navigator_visible) {
      mp_navigator_dock_widget->show ();
    } else {
      mp_navigator_dock_widget->hide ();
    }

    return true;

  } else if (name == cfg_navigator_show_images) {

    bool flag = false;
    tl::from_string (value, flag);
    mp_navigator->show_images (flag);

    return true;

  } else if (name == cfg_navigator_all_hier_levels) {

    bool flag = false;
    tl::from_string (value, flag);
    mp_navigator->all_hier_levels (flag);

    return true;

  } else if (name == cfg_show_toolbar) {

    bool flag = false;
    tl::from_string (value, flag);
    if (flag) {
      mp_tool_bar->show ();
    } else {
      mp_tool_bar->hide ();
    }

    return true;

  } else if (name == cfg_show_hierarchy_panel) {

    tl::from_string (value, m_hp_visible);
    if (m_hp_visible) {
      mp_hp_dock_widget->show ();
    } else {
      mp_hp_dock_widget->hide ();
    }

    return true;

  } else if (name == cfg_show_layer_panel) {

    tl::from_string (value, m_lp_visible);
    if (m_lp_visible) {
      mp_lp_dock_widget->show ();
    } else {
      mp_lp_dock_widget->hide ();
    }

    return true;

  } else if (name == cfg_synchronized_views) {

    bool flag = false;
    tl::from_string (value, flag);
    m_synchronized_views = flag;
    return true;

  } else if (name == cfg_default_dbu) {

    double d = 0.0;
    tl::from_string (value, d);
    m_default_dbu = d;
    return false; // not taken - let others set it too.

  } else if (name == cfg_key_bindings) {

    m_key_bindings = unpack_key_binding (value);
    apply_key_bindings ();
    return true;

  } else if (name == cfg_background_color) {

    if (mp_navigator) {
      QColor color;
      ColorConverter ().from_string (value, color);
      mp_navigator->background_color (color);
    }

    //  do not take - let others receive the background color events as well
    return false;

  } else if (name == cfg_initial_technology) {

    m_initial_technology = value;
    return true;

  } else {
    return false;
  }

}

void
MainWindow::apply_key_bindings ()
{
  for (std::vector<std::pair<std::string, std::string> >::const_iterator kb = m_key_bindings.begin (); kb != m_key_bindings.end (); ++kb) {

    if (menu ().is_valid (kb->first)) {

      lay::Action a = menu ().action (kb->first);
      a.set_shortcut (kb->second);

      if (m_action_to_macro.find (a.qaction ()) != m_action_to_macro.end ()) {
        m_action_to_macro [a.qaction ()]->set_shortcut (kb->second);
      }

    }

  }
}

void 
MainWindow::enable_edits (bool enable)
{
  if (enable) {
    if (m_disabled_edits > 0) {
      --m_disabled_edits;
    }
    enable = (m_disabled_edits == 0);
  } else {
    ++m_disabled_edits;
  }

  std::vector<std::string> edit_grp = mp_menu->group ("edit");
  for (std::vector<std::string>::const_iterator g = edit_grp.begin (); g != edit_grp.end (); ++g) {
    mp_menu->action (*g).set_enabled (enable);
  }

  for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
    (*vp)->enable_edits (enable);
  }
  
  m_edits_enabled = enable;

  //  call this to establish a consistent set of options on the menu entries
  popup_menu_show ();
}

void 
MainWindow::libraries_changed ()
{
  //  if the libraries have changed, remove all selections and cancel any operations to avoid 
  //  that the view refers to an invalid instance or shape
  for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
    (*vp)->clear_selection ();
    (*vp)->cancel ();
  }
}

void
MainWindow::read_dock_widget_state ()
{
  config_set (cfg_show_layer_panel, tl::to_string (!mp_lp_dock_widget->isHidden ()));
  config_set (cfg_show_hierarchy_panel, tl::to_string (!mp_hp_dock_widget->isHidden ()));
  config_set (cfg_show_navigator, tl::to_string (!mp_navigator_dock_widget->isHidden ()));
  config_set (cfg_show_layer_toolbox, tl::to_string (!mp_layer_toolbox_dock_widget->isHidden ()));
}

void 
MainWindow::update_dock_widget_state ()
{
  if (m_hp_visible) {
    mp_hp_dock_widget->show ();
  } else {
    mp_hp_dock_widget->hide ();
  }

  if (m_lp_visible) {
    mp_lp_dock_widget->show ();
  } else {
    mp_lp_dock_widget->hide ();
  }

  if (m_navigator_visible) {
    mp_navigator_dock_widget->show ();
  } else {
    mp_navigator_dock_widget->hide ();
  }

  if (m_layer_toolbox_visible) {
    mp_layer_toolbox_dock_widget->show ();
  } else {
    mp_layer_toolbox_dock_widget->hide ();
  }
}

void
MainWindow::exit ()
{
  m_exited = true;
  do_close ();
  QMainWindow::close ();
}

int 
MainWindow::dirty_files (std::string &dirty_files)
{
  int dirty_layouts = 0;

  if (lay::Application::instance ()->is_editable ()) {
    std::vector <std::string> names;
    lay::LayoutHandle::get_names (names);
    for (std::vector <std::string>::const_iterator n = names.begin (); n != names.end (); ++n) {
      lay::LayoutHandle *handle = lay::LayoutHandle::find (*n);
      if (handle && handle->is_dirty ()) {
        ++dirty_layouts;
        if (dirty_layouts == max_dirty_files) {
          dirty_files += "\n  ...";
        } else if (dirty_layouts < max_dirty_files) {
          if (! dirty_files.empty ()) {
            dirty_files += "\n";
          }
          dirty_files += "  ";
          dirty_files += handle->name ();
        }
      }
    }
  }

  return dirty_layouts;
}

bool
MainWindow::can_close ()
{
  if (m_busy) {

    bool can_close = false;

    can_close = (QMessageBox::warning (this, 
      QObject::tr ("Application Busy"),
      QObject::tr ("The application is busy.\nYou can close the application now, but any unsaved data will be lost.\n\nPress 'Yes' to end the application now."),
      QMessageBox::Yes | QMessageBox::No,
      QMessageBox::Yes) == QMessageBox::Yes);

    return can_close;

  }

  if (! mp_macro_editor->can_exit ()) {
    return false;
  }

  std::string df_list;
  int dirty_layouts = dirty_files (df_list);

  if (dirty_layouts == 0) {
    return true;
  } else {

    QMessageBox mbox (this);
    mbox.setText (tl::to_qstring (tl::to_string (QObject::tr ("The following layouts need saving:\n\n")) + df_list + "\n\nPress 'Exit Without Saving' to exit anyhow and discard changes."));
    mbox.setWindowTitle (QObject::tr ("Save Needed"));
    mbox.setIcon (QMessageBox::Warning);
    QAbstractButton *exit_button = mbox.addButton (QObject::tr ("Exit Without Saving"), QMessageBox::YesRole);
    mbox.addButton (QMessageBox::Cancel);

    mbox.exec ();

    return mbox.clickedButton() == exit_button;

  }
}

void
MainWindow::do_close ()
{
  //  don't close if busy in processEvents
  if (m_busy) {
    return;
  }

  //  close all views
  close_all ();

  save_state_to_config ();
}

void
MainWindow::save_state_to_config ()
{
  //  save the dock widget state with all views closed (that state can be 
  //  used for staring klayout without any layout)
  config_set (cfg_window_geometry, (const char *) saveGeometry ().toBase64 ().data ());
  config_set (cfg_window_state, (const char *) saveState ().toBase64 ().data ());
}

void
MainWindow::resizeEvent (QResizeEvent *event)
{
  format_message ();
}

void 
MainWindow::closeEvent (QCloseEvent *event)
{
  if (! m_exited) {

    BEGIN_PROTECTED

    if (mp_pr) {
      mp_pr->signal_break ();
    }

    if (! can_close ()) {
      event->ignore ();
    } else {
      do_close ();
      emit closed ();
    }

    END_PROTECTED

  }
}

void
MainWindow::cm_navigator_freeze ()
{
  BEGIN_PROTECTED
  if (mp_navigator) {
    mp_navigator->freeze_clicked ();
  }
  END_PROTECTED
}

void
MainWindow::cm_navigator_close ()
{
  BEGIN_PROTECTED
  if (mp_navigator) {
    mp_navigator->close ();
  }
  END_PROTECTED
}

void
MainWindow::cm_view_log ()
{
  BEGIN_PROTECTED
  mp_log_viewer_dialog->show ();
  END_PROTECTED
}

void
MainWindow::cm_print ()
{
  BEGIN_PROTECTED

  //  Late-initialize the printer to save time on startup
  if (! mp_printer.get ()) {
    mp_printer.reset (new QPrinter ());
  }

  std::string v = std::string (lay::Version::name ()) + " " + lay::Version::version ();
  mp_printer->setCreator (tl::to_qstring (v));
  mp_printer->setDocName (tl::to_qstring ("klayout_printout"));

  QPrintDialog print_dialog (mp_printer.get (), this);
  if (print_dialog.exec() == QDialog::Accepted) {

    if (current_view ()) {

      //  choose a resolution around 300dpi
      double rf = floor (0.5 + 300.0 / mp_printer->resolution ());
      mp_printer->setResolution (int (floor (0.5 + mp_printer->resolution () * rf)));

      QPainter painter;

      painter.begin (mp_printer.get ());

      QFont header_font (QString::fromAscii ("Helvetica"), 8);
      int hh = QFontMetrics (header_font, mp_printer.get ()).height ();

      QRect page_rect = mp_printer->pageRect ();
      page_rect.moveTo (0, 0);

      int b = std::min (page_rect.width (), page_rect.height ()) / 50;
      page_rect.setLeft (page_rect.left () + b);
      page_rect.setRight (page_rect.right () - b);
      page_rect.setTop (page_rect.top () + b);
      page_rect.setBottom (page_rect.bottom () - b);

      QRect text_rect = page_rect;
      text_rect.setLeft (text_rect.left () + hh / 2);
      text_rect.setRight (text_rect.right () - hh / 2);
      text_rect.setBottom (text_rect.bottom () - hh / 2);
      text_rect.setTop (text_rect.top () + hh / 2);

      QImage img = current_view ()->get_image_with_options (page_rect.width (), page_rect.height () - 4 * hh, 2, 1, 1.0 / 3.0, Qt::white, Qt::black, Qt::black, db::DBox (), false);

      painter.drawImage (QPoint (page_rect.left (), page_rect.top () + hh * 2), img);
      painter.setFont (header_font);
      painter.drawRect (page_rect);

      painter.drawText (text_rect, Qt::AlignLeft | Qt::AlignTop, tl::to_qstring (v));
      painter.drawText (text_rect, Qt::AlignHCenter | Qt::AlignTop, tl::to_qstring (current_view ()->title ()));
      painter.drawText (text_rect, Qt::AlignLeft | Qt::AlignBottom, QDateTime::currentDateTime ().toString ());

      db::DBox vp = current_view ()->viewport ().box ();
      std::string vp_string = "(" + tl::micron_to_string (vp.left ()) + ", " + tl::micron_to_string (vp.bottom ()) + " ... " +
                                    tl::micron_to_string (vp.right ()) + ", " + tl::micron_to_string (vp.top ()) + ")";
      painter.drawText (text_rect, Qt::AlignRight | Qt::AlignBottom, tl::to_qstring (vp_string));

      painter.end ();

    } else {
      throw tl::Exception (tl::to_string (QObject::tr ("No view open to print")));
    }

  }

  END_PROTECTED
}

void
MainWindow::cm_exit ()
{
  BEGIN_PROTECTED
  if (can_close ()) {
    //  actually exit.
    exit ();
  }
  END_PROTECTED
}

lay::LayoutView *
MainWindow::view (int index)
{
  if (index >= 0 && index < int (mp_views.size ())) {
    return mp_views [index];
  } else {
    return 0;
  }
}

const lay::LayoutView *
MainWindow::view (int index) const
{
  if (index >= 0 && index < int (mp_views.size ())) {
    return mp_views [index];
  } else {
    return 0;
  }
}

int 
MainWindow::current_view_index () const
{
  if (m_current_view >= mp_views.size ()) {
    return -1;
  } else {
    return int (m_current_view);
  }
}

lay::LayoutView *
MainWindow::current_view ()
{
  if (m_current_view >= mp_views.size ()) {
    return 0;
  } else {
    return mp_views [m_current_view];
  }
}

const lay::LayoutView *
MainWindow::current_view () const
{
  if (m_current_view >= mp_views.size ()) {
    return 0;
  } else {
    return mp_views [m_current_view];
  }
}

void 
MainWindow::cm_show_properties ()
{
  if (current_view ()) {
    current_view ()->show_properties (this);
  }
}

void 
MainWindow::cm_delete ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->del ();
    //  because a "delete" might involve objects currently edited, we cancel the edit after we have deleted the object
    current_view ()->cancel ();
    current_view ()->clear_selection ();
  }

  END_PROTECTED
}

void 
MainWindow::cm_lv_paste ()
{
  BEGIN_PROTECTED
  current_view ()->cm_layer_paste ();
  END_PROTECTED
}

void 
MainWindow::cm_lv_cut ()
{
  BEGIN_PROTECTED
  current_view ()->cm_layer_cut ();
  END_PROTECTED
}

void 
MainWindow::cm_lv_copy ()
{
  BEGIN_PROTECTED
  current_view ()->cm_layer_copy ();
  END_PROTECTED
}

void 
MainWindow::cm_cell_paste ()
{
  BEGIN_PROTECTED
  current_view ()->cm_cell_paste ();
  END_PROTECTED
}

void 
MainWindow::cm_cell_cut ()
{
  BEGIN_PROTECTED
  current_view ()->cm_cell_cut ();
  END_PROTECTED
}

void 
MainWindow::cm_cell_copy ()
{
  BEGIN_PROTECTED
  current_view ()->cm_cell_copy ();
  END_PROTECTED
}

void 
MainWindow::cm_duplicate ()
{
  BEGIN_PROTECTED

  if (current_view () && current_view ()->has_selection ()) {

    //  Do duplicate simply by concatenating copy & paste currently. 
    //  Save the clipboard state before in order to preserve the current content
    db::Clipboard saved_clipboard;
    db::Clipboard::instance ().swap (saved_clipboard);

    try {
      current_view ()->copy ();
      current_view ()->clear_selection ();
      current_view ()->cancel ();
      current_view ()->paste ();
      db::Clipboard::instance ().swap (saved_clipboard);
    } catch (...) {
      db::Clipboard::instance ().swap (saved_clipboard);
      throw;
    }

  }

  END_PROTECTED
}

void 
MainWindow::cm_copy ()
{
  BEGIN_PROTECTED

  if (current_view () && current_view ()->has_selection ()) {
    current_view ()->copy ();
    current_view ()->clear_selection ();
  }

  END_PROTECTED
}

void 
MainWindow::cm_paste ()
{
  BEGIN_PROTECTED

  if (current_view () && ! db::Clipboard::instance ().empty ()) {
    current_view ()->cancel ();
    current_view ()->clear_selection ();
    current_view ()->paste ();
  }

  END_PROTECTED
}

void 
MainWindow::cm_cut ()
{
  BEGIN_PROTECTED

  if (current_view () && current_view ()->has_selection ()) {
    current_view ()->cut ();
    current_view ()->cancel (); //  see del() for reason why cancel is after cut
    current_view ()->clear_selection ();
  }

  END_PROTECTED
}

void 
MainWindow::mode ()
{
  QAction *action = dynamic_cast<QAction *> (sender ());
  if (action) {
    select_mode (action->data ().toInt ());
  }
}

void
MainWindow::select_mode (int m)
{
  if (m_mode != m) {

    m_mode = m;
    for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
      (*vp)->mode (m);
    }

    //  update the actions by checking the one that is selected programmatically. Use the toolbar menu for reference.
    std::vector<std::string> items = menu ().items ("@toolbar");
    for (std::vector<std::string>::const_iterator i = items.begin (); i != items.end (); ++i) {
      Action a = menu ().action (*i);
      if (a.qaction ()->data ().toInt () == m_mode) {
        a.set_checked (true);
        break;
      }
    }

  }
}

void 
MainWindow::enable_all ()
{
  BEGIN_PROTECTED

  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    cls->set_editable_enabled (true);
  }

  END_PROTECTED
}

void 
MainWindow::disable_all ()
{
  BEGIN_PROTECTED

  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    cls->set_editable_enabled (false);
  }

  END_PROTECTED
}

void 
MainWindow::enable ()
{
  BEGIN_PROTECTED

  QAction *action = dynamic_cast <QAction *> (sender ());
  tl_assert (action);

  int m = action->data ().toInt ();
  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    if (cls->id () == m) {
      cls->set_editable_enabled (! cls->editable_enabled ());
      break;
    }
  }

  END_PROTECTED
}

void 
MainWindow::cm_unselect_all ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->select (db::DBox (), lay::Editable::Reset);
  }

  END_PROTECTED
}

void 
MainWindow::cm_select_all ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    //  TODO: "select all" with an empty box is not well implemented in most services. 
    //  Hence we use the overlapp box currently.
    current_view ()->select (current_view ()->full_box (), lay::Editable::Replace);
  }

  END_PROTECTED
}

void 
MainWindow::cm_undo ()
{
  BEGIN_PROTECTED

  if (current_view () && m_manager.available_undo ().first) {
    for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
      (*vp)->clear_selection ();
      (*vp)->cancel ();
    }
    m_manager.undo ();
    current_view ()->update_content ();
  }

  END_PROTECTED
}

void
MainWindow::cm_redo ()
{
  BEGIN_PROTECTED

  if (current_view () && m_manager.available_redo ().first) {
    for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
      (*vp)->clear_selection ();
      (*vp)->cancel ();
    }
    m_manager.redo ();
    current_view ()->update_content ();
  }

  END_PROTECTED
}

void
MainWindow::add_macro_items_to_menu (lay::MacroCollection &collection, int &n, std::set<std::string> &groups, const lay::Technology *tech)
{
  for (lay::MacroCollection::child_iterator c = collection.begin_children (); c != collection.end_children (); ++c) {

    //  check whether the macro collection is associated with the selected technology (if there is one)
    bool consider = false; 
    if (! tech || c->second->virtual_mode () != lay::MacroCollection::TechFolder) {
      consider = true;
    } else {
      const std::vector<std::pair<std::string, std::string> > &mc = lay::Application::instance ()->macro_categories ();
      for (std::vector<std::pair<std::string, std::string> >::const_iterator cc = mc.begin (); cc != mc.end () && !consider; ++cc) {
        consider = (c->second->path () == tl::to_string (QDir (tl::to_qstring (tech->base_path ())).filePath (tl::to_qstring (cc->first))));
      }
    }

    if (consider) {
      add_macro_items_to_menu (*c->second, n, groups, 0 /*don't check 2nd level and below*/);
    }

  }

  for (lay::MacroCollection::iterator c = collection.begin (); c != collection.end (); ++c) {

    std::string sc = tl::trim (c->second->shortcut ());

    if (c->second->show_in_menu ()) {

      std::string mp = tl::trim (c->second->menu_path ());
      if (mp.empty ()) {
        mp = "macros_menu.end";
      }

      std::string gn = tl::trim (c->second->group_name ());
      if (! gn.empty () && groups.find (gn) == groups.end ()) {
        groups.insert (gn);
        lay::Action as;
        as.set_separator (true);
        m_macro_actions.push_back (as);
        menu ().insert_item (mp, "macro_in_menu_" + tl::to_string (n++), as);
      }

      lay::Action a;
      if (c->second->description ().empty ()) {
        a.set_title (c->second->path ());
      } else {
        a.set_title (c->second->description ());
      }
      a.set_shortcut (sc);
      m_macro_actions.push_back (a);
      menu ().insert_item (mp, "macro_in_menu_" + tl::to_string (n++), a);

      m_action_to_macro.insert (std::make_pair (a.qaction (), c->second));

      MacroSignalAdaptor *adaptor = new MacroSignalAdaptor (a.qaction (), c->second);
      QObject::connect (a.qaction (), SIGNAL (triggered ()), adaptor, SLOT (run ()));

    } else if (! sc.empty ()) {

      //  Create actions for shortcut-only actions too and add them to the main window 
      //  to register their shortcut.

      lay::Action a;
      if (c->second->description ().empty ()) {
        a.set_title (c->second->path ());
      } else {
        a.set_title (c->second->description ());
      }
      a.set_shortcut (sc);
      m_macro_actions.push_back (a);

      addAction (a.qaction ());
      MacroSignalAdaptor *adaptor = new MacroSignalAdaptor (a.qaction (), c->second);
      QObject::connect (a.qaction (), SIGNAL (triggered ()), adaptor, SLOT (run ()));

    }

  }
}

void
MainWindow::update_menu_with_macros ()
{
  //  empty action to macro table now we know it's invalid
  m_action_to_macro.clear ();
  dm_do_update_menu_with_macros ();
}

void
MainWindow::do_update_menu_with_macros ()
{
  const lay::Technology *tech = 0;
  if (current_view () && current_view ()->active_cellview_index () >= 0 &&  current_view ()->active_cellview_index () <= int (current_view ()->cellviews ())) {
    std::string active_tech = current_view ()->active_cellview ()->tech_name ();
    tech = lay::Technologies::instance ()->technology_by_name (active_tech);
  }

  //  delete all existing items
  for (std::vector<lay::Action>::iterator a = m_macro_actions.begin (); a != m_macro_actions.end (); ++a) {
    menu ().delete_items (*a);
  }
  m_macro_actions.clear ();
  m_action_to_macro.clear ();

  int n = 1;
  std::set<std::string> groups;
  add_macro_items_to_menu (m_temp_macros, n, groups, tech);
  add_macro_items_to_menu (lay::MacroCollection::root (), n, groups, tech);
}

void 
MainWindow::bookmark_menu_show ()
{
  if (mp_menu->is_valid ("bookmark_menu.goto_bookmark_menu")) {

    Action goto_bookmark_action = mp_menu->action ("bookmark_menu.goto_bookmark_menu");
    bool has_bookmarks = current_view () && current_view ()->bookmarks ().size () > 0;

    if (has_bookmarks && m_edits_enabled) {

      goto_bookmark_action.set_enabled (true);

      QMenu *goto_bookmark_menu = goto_bookmark_action.qaction ()->menu ();
      if (goto_bookmark_menu) {

        goto_bookmark_menu->clear ();

        if (current_view ()) {
          const lay::BookmarkList &bookmarks = current_view ()->bookmarks ();
          for (size_t i = 0; i < bookmarks.size (); ++i) {
            QAction *action = goto_bookmark_menu->addAction (tl::to_qstring (bookmarks.name (i)));
            action->setObjectName (tl::to_qstring (tl::sprintf ("bookmark_%d", i + 1)));
            gtf::action_connect (action, SIGNAL (triggered ()), this, SLOT (goto_bookmark ()));
            action->setData (QVariant (int (i))); 
          }
        }

      }

    } else {
      goto_bookmark_action.set_enabled (false);
    }

  }
}

void
MainWindow::goto_bookmark ()
{
  BEGIN_PROTECTED

  QAction *action = dynamic_cast <QAction *> (sender ());
  tl_assert (action);
  size_t id = size_t (action->data ().toInt ());
  if (current_view () && current_view ()->bookmarks ().size () > id) {
    current_view ()->goto_view (current_view ()->bookmarks ().state (id));
  }

  END_PROTECTED
}

void
MainWindow::cm_goto_position ()
{
  BEGIN_PROTECTED

  if (current_view ()) {

    while (true) {

      bool ok = false;

      db::DBox box (current_view ()->box ());
      std::string pos;
      pos += tl::micron_to_string (box.center ().x ()) + "," + tl::micron_to_string (box.center ().y ());
      pos += ",";
      pos += tl::micron_to_string (std::min (box.width (), box.height ()));

      QString text = QInputDialog::getText (this, QObject::tr ("Enter Position"), QObject::tr ("Enter position either as pair (x,y) or with window size (x,y,s)\n(x,y) will be the new window center position, s (if given) the new window size"),
                                            QLineEdit::Normal, tl::to_qstring (pos), &ok);

      if (! ok) {

        break;

      } else if (text.isEmpty ()) {

        throw tl::Exception (tl::to_string (QObject::tr ("Enter the position")));

      } else {

        double x = 0.0, y = 0.0, s = 0.0;
        std::string tt (tl::to_string (text));
        tl::Extractor ex (tt.c_str ());
        ex >> x >> "," >> y;
        if (! ex.at_end ()) {
          ex >> "," >> s >> tl::Extractor::end ();
          current_view ()->goto_window (db::DPoint (x, y), s);
        } else {
          current_view ()->goto_window (db::DPoint (x, y));
        }
        break;

      }

    }

  }

  END_PROTECTED
}

void
MainWindow::cm_manage_bookmarks ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->manage_bookmarks ();
  }

  END_PROTECTED
}

void
MainWindow::cm_bookmark_view ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    while (true) {
      bool ok = false;
      QString text = QInputDialog::getText (this, QObject::tr ("Enter Bookmark Name"), QObject::tr ("Bookmark name"),
                                            QLineEdit::Normal, QString::null, &ok);
      if (! ok) {
        break;
      } else if (text.isEmpty ()) {
        QMessageBox::critical (this, QObject::tr ("Error"), QObject::tr ("Enter a name for the bookmark"));
      } else {
        current_view ()->bookmark_view (tl::to_string (text));
        break;
      }
    }
  }

  END_PROTECTED
}

void
MainWindow::update_content ()
{
  BEGIN_PROTECTED

  mp_setup_form->setup ();
  if (current_view ()) {
    current_view ()->update_content ();
  }

  END_PROTECTED
}

void
MainWindow::cm_zoom_fit_sel ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->zoom_fit_sel ();
  }

  END_PROTECTED
}

void
MainWindow::cm_zoom_fit ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->zoom_fit ();
  }

  END_PROTECTED
}

void
MainWindow::cm_pan_left ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->pan_left ();
  }

  END_PROTECTED
}

void
MainWindow::cm_pan_right ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->pan_right ();
  }

  END_PROTECTED
}

void
MainWindow::cm_pan_up ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->pan_up ();
  }

  END_PROTECTED
}

void
MainWindow::cm_pan_down ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->pan_down ();
  }

  END_PROTECTED
}

void
MainWindow::cm_zoom_in ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->zoom_in ();
  }

  END_PROTECTED
}

void
MainWindow::cm_zoom_out ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    current_view ()->zoom_out ();
  }

  END_PROTECTED
}

void 
MainWindow::popup_menu_hide ()
{
  //  Enable all menu items as far as required on closing of the menu. Otherwise,
  //  keyboard shortcuts are not effective when the window is closed and the actions are
  //  left disabled.

  BEGIN_PROTECTED

  if (mp_menu->is_valid ("edit_menu.undo")) {
    Action undo_action = mp_menu->action ("edit_menu.undo");
    undo_action.set_enabled (m_edits_enabled);
  }

  if (mp_menu->is_valid ("edit_menu.redo")) {
    Action redo_action = mp_menu->action ("edit_menu.redo");
    redo_action.set_enabled (m_edits_enabled);
  }

  if (mp_menu->is_valid ("edit_menu.copy")) {
    Action copy_action = mp_menu->action ("edit_menu.copy");
    copy_action.set_enabled (m_edits_enabled);
  }

  if (mp_menu->is_valid ("edit_menu.cut")) {
    Action cut_action = mp_menu->action ("edit_menu.cut");
    cut_action.set_enabled (m_edits_enabled);
  }

  if (mp_menu->is_valid ("edit_menu.paste")) {
    Action paste_action = mp_menu->action ("edit_menu.paste");
    paste_action.set_enabled (m_edits_enabled);
  }

  if (mp_menu->is_valid ("edit_menu.duplicate")) {
    Action paste_action = mp_menu->action ("edit_menu.duplicate");
    paste_action.set_enabled (m_edits_enabled);
  }

  if (mp_menu->is_valid ("zoom_menu.next_display_state")) {
    Action next_display_state_action = mp_menu->action ("zoom_menu.next_display_state");
    next_display_state_action.set_enabled (true);
  } 

  if (mp_menu->is_valid ("zoom_menu.last_display_state")) {
    Action last_display_state_action = mp_menu->action ("zoom_menu.last_display_state");
    last_display_state_action.set_enabled (true);
  }

  END_PROTECTED
}

void 
MainWindow::popup_menu_show ()
{
  BEGIN_PROTECTED

  if (mp_menu->is_valid ("edit_menu.undo")) {

    Action undo_action = mp_menu->action ("edit_menu.undo");

    std::string undo_txt (tl::to_string (QObject::tr ("&Undo")));
    bool undo_enable = false;
    if (current_view () && m_manager.available_undo ().first) {
      undo_txt += " - " + m_manager.available_undo ().second;
      undo_enable = true;
    }
    undo_action.set_title (undo_txt); 
    undo_action.set_enabled (undo_enable && m_edits_enabled);

  }

  if (mp_menu->is_valid ("edit_menu.redo")) {

    Action redo_action = mp_menu->action ("edit_menu.redo");

    std::string redo_txt (tl::to_string (QObject::tr ("&Redo")));
    bool redo_enable = false;
    if (current_view () && m_manager.available_redo ().first) {
      redo_txt += " - " + m_manager.available_redo ().second;
      redo_enable = true;
    }
    redo_action.set_title (redo_txt); 
    redo_action.set_enabled (redo_enable && m_edits_enabled);

  }

  if (mp_menu->is_valid ("edit_menu.copy")) {
    Action copy_action = mp_menu->action ("edit_menu.copy");
    copy_action.set_enabled (current_view () && current_view ()->has_selection () && m_edits_enabled);
  }

  if (mp_menu->is_valid ("edit_menu.duplicate")) {
    Action copy_action = mp_menu->action ("edit_menu.duplicate");
    copy_action.set_enabled (current_view () && current_view ()->has_selection () && m_edits_enabled);
  }

  if (mp_menu->is_valid ("edit_menu.cut")) {
    Action cut_action = mp_menu->action ("edit_menu.cut");
    cut_action.set_enabled (current_view () && current_view ()->has_selection () && m_edits_enabled);
  }

  if (mp_menu->is_valid ("edit_menu.paste")) {
    Action paste_action = mp_menu->action ("edit_menu.paste");
    paste_action.set_enabled (! db::Clipboard::instance ().empty () && m_edits_enabled);
  }

  if (mp_menu->is_valid ("zoom_menu.next_display_state")) {
    Action next_display_state_action = mp_menu->action ("zoom_menu.next_display_state");
    next_display_state_action.set_enabled (has_next_display_state ());
  } 

  if (mp_menu->is_valid ("zoom_menu.last_display_state")) {
    Action last_display_state_action = mp_menu->action ("zoom_menu.last_display_state");
    last_display_state_action.set_enabled (has_last_display_state ());
  }

  END_PROTECTED
}

void
MainWindow::cm_redraw ()
{
  BEGIN_PROTECTED 
  redraw ();
  END_PROTECTED
}

void
MainWindow::redraw ()
{
  if (current_view ()) {
    current_view ()->redraw ();
  }
}

void
MainWindow::cm_cancel ()
{
  BEGIN_PROTECTED 
  cancel ();
  select_mode (lay::LayoutView::default_mode ());
  END_PROTECTED
}

/**
 *  @brief Commits any operations, cancels any pending edit operations and clears the selection.
 */
void
MainWindow::cancel ()
{
  BEGIN_PROTECTED 

  //  if any transaction is pending (this may happen when an operation threw an exception)
  //  close transactions.
  if (m_manager.transacting ()) {
    m_manager.commit ();
  }

  for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
    (*vp)->cancel ();
  }

  END_PROTECTED
}

void
MainWindow::cm_save_layer_props ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    std::string fn;
    if (mp_lprops_fdia->get_save (fn)) {
      current_view ()->save_layer_props (fn);
    }
  } else {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to save the layer properties from")));
  }

  END_PROTECTED
}

void
MainWindow::load_layer_properties (const std::string &fn, bool all_views, bool add_default)
{
  if (all_views) {
    for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
      (*vp)->load_layer_props (fn, add_default);
    }
  } else if (current_view ()) {
    current_view ()->load_layer_props (fn, add_default);
  }
}

void
MainWindow::load_layer_properties (const std::string &fn, int cv_index, bool all_views, bool add_default)
{
  if (all_views) {
    for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
      (*vp)->load_layer_props (fn, cv_index, add_default);
    }
  } else if (current_view ()) {
    current_view ()->load_layer_props (fn, cv_index, add_default);
  }
}

bool 
MainWindow::is_single_cv_layer_properties_file (const std::string &fn)
{
  //  If the file contains information for a single layout but we have multiple ones, 
  //  show the dialog to determine what layout to apply the information to.
  std::vector<lay::LayerPropertiesList> props;
  try {
    tl::XMLFileSource in (fn);
    props.push_back (lay::LayerPropertiesList ());
    props.back ().load (in);
  } catch (...) {
    props.clear ();
    tl::XMLFileSource in (fn);
    lay::LayerPropertiesList::load (in, props);
  }

  //  Collect all cv indices in the layer properties 
  std::set <int> cv;
  for (std::vector<lay::LayerPropertiesList>::const_iterator p = props.begin (); p != props.end (); ++p) {
    for (lay::LayerPropertiesConstIterator lp = p->begin_const_recursive (); ! lp.at_end (); ++lp) {
      if (! lp->has_children ()) {
        cv.insert (lp->source (true).cv_index ());
        if (cv.size () >= 2) {
          break;
        }
      }
    }
  }

  return (cv.size () == 1);
}

void
MainWindow::cm_load_layer_props ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    std::string fn;
    if (mp_lprops_fdia->get_open (fn)) {

      int target_cv_index = -2;

      if (current_view ()->cellviews () > 1 && is_single_cv_layer_properties_file (fn)) {

        QStringList items;
        items << QString (QObject::tr ("Take it as it is"));
        items << QString (QObject::tr ("Apply to all layouts"));
        for (unsigned int i = 0; i < current_view ()->cellviews (); ++i) {
          items << QString (tl::to_qstring (tl::to_string (QObject::tr ("Apply to ")) + current_view ()->cellview (i)->name () + " (@" + tl::to_string (i + 1) + ")"));
        }

        bool ok;
        QString item = QInputDialog::getItem(this, QObject::tr ("Apply Layer Properties File"),
                                                   QObject::tr ("There are multiple layouts in that panel but the layer properties file contains properties for a single one.\nWhat should be done?"),
                                                   items, 1, false, &ok);
        if (!ok || item.isEmpty()) {
          return;
        }

        target_cv_index = items.indexOf (item) - 2;

      }

      if (target_cv_index > -2) {
        load_layer_properties (fn, target_cv_index, false /*current view only*/, false /*don't add default*/);
      } else {
        load_layer_properties (fn, false /*current view only*/, false /*don't add default*/);
      }

    }
  } else {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to load the layer properties for")));
  }

  END_PROTECTED
}

void
MainWindow::save_session (const std::string &fn)
{
  m_current_session = fn;
  lay::Session session;
  session.fetch (*this);
  session.save (fn);
}

void
MainWindow::restore_session (const std::string &fn)
{
  m_current_session = fn;
  lay::Session session;
  session.load (fn);
  session.restore (*this);
  read_dock_widget_state ();
}

void
MainWindow::cm_save_session ()
{
  BEGIN_PROTECTED

  std::string df_list;
  int dirty_layouts = dirty_files (df_list);

  if (dirty_layouts == 0 || 
    QMessageBox::warning (this, 
      QObject::tr ("Save Needed For Some Layouts"),
      tl::to_qstring (tl::to_string (QObject::tr ("The following layouts need saving.\nThese layouts must be saved manually:\n\n")) + df_list + "\n\nPress 'Ok' to continue."),
      QMessageBox::Ok | QMessageBox::Cancel,
      QMessageBox::Cancel) == QMessageBox::Ok) {

    std::string fn = m_current_session;
    if (mp_session_fdia->get_save (fn)) {
      save_session (fn);
    }

  }

  END_PROTECTED
}

void
MainWindow::cm_restore_session ()
{
  BEGIN_PROTECTED

  std::string fn = m_current_session;
  if (mp_session_fdia->get_open (fn)) {

    std::string df_list;
    int dirty_layouts = dirty_files (df_list);

    if (dirty_layouts == 0) {
      restore_session (fn);
    } else {

      QMessageBox mbox (this);
      mbox.setText (tl::to_qstring (tl::to_string (QObject::tr ("The following layouts need saving:\n\n")) + df_list + "\n\nPress 'Discard Changes' to close them anyhow and discard changes."));
      mbox.setWindowTitle (QObject::tr ("Save Needed"));
      mbox.setIcon (QMessageBox::Warning);
      QAbstractButton *discard_button = mbox.addButton (QObject::tr ("Discard Changes"), QMessageBox::YesRole);
      mbox.addButton (QMessageBox::Cancel);

      mbox.exec ();

      if (mbox.clickedButton() == discard_button) {
        restore_session (fn);
      }

    }

  }

  END_PROTECTED
}

void
MainWindow::cm_save_bookmarks ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    std::string fn;
    if (mp_bookmarks_fdia->get_save (fn)) {
      current_view ()->bookmarks ().save (fn);
    }
  } else {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to save the bookmarks from")));
  }

  END_PROTECTED
}

void
MainWindow::cm_load_bookmarks ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    std::string fn;
    if (mp_bookmarks_fdia->get_open (fn)) {
      BookmarkList bookmarks;
      bookmarks.load (fn);
      current_view ()->bookmarks (bookmarks);
    }
  } else {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to load the bookmarks for")));
  }

  END_PROTECTED
}

void
MainWindow::cm_select_current_cell ()
{
  BEGIN_PROTECTED

  lay::LayoutView *view = current_view ();
  if (view && view->active_cellview_index () >= 0) {
    lay::LayoutView::cell_path_type path;
    int cvi = view->active_cellview_index ();
    view->current_cell_path (path);
    view->select_cell_fit (path, cvi);
  }

  END_PROTECTED
}

void
MainWindow::cm_open_current_cell ()
{
  BEGIN_PROTECTED

  if (current_view () && current_view ()->active_cellview_index () >= 0) {
    current_view ()->cm_open_current_cell ();
  }

  END_PROTECTED
}

void
MainWindow::cm_select_cell ()
{
  BEGIN_PROTECTED

  if (current_view () && current_view ()->active_cellview_index () >= 0) {

    CellSelectionForm form (0, current_view (), "cell_selection_form");

    if (form.exec () == QDialog::Accepted && 
        form.selected_cellview_index () >= 0) {
      current_view ()->select_cell (form.selected_cellview ().combined_unspecific_path (), form.selected_cellview_index ()); 
      current_view ()->set_current_cell_path (form.selected_cellview_index (), form.selected_cellview ().combined_unspecific_path ());
      current_view ()->zoom_fit ();
    }

  } else {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to select a cell for")));
  }

  END_PROTECTED
}

void
MainWindow::cm_screenshot ()
{
  BEGIN_PROTECTED

  if (current_view ()) {
    std::string fn;
    if (mp_screenshot_fdia->get_save (fn)) {
      current_view ()->save_screenshot (fn);
    }
  } else {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to create a screenshot from")));
  }

  END_PROTECTED
}

void
MainWindow::cm_save_current_cell_as ()
{
  BEGIN_PROTECTED

  if (current_view ()) {

    int cv_index = current_view ()->active_cellview_index ();
    if (cv_index >= 0 && cv_index < int (current_view ()->cellviews ())) {

      LayoutView::cell_path_type path;
      current_view ()->current_cell_path (path);
      if (! path.empty ()) {

        const lay::CellView &cv = current_view ()->cellview (cv_index);

        QFileInfo file_info (tl::to_qstring (cv->filename ()));
        std::string suffix = tl::to_string (file_info.suffix ());

        std::string fn = std::string (cv->layout ().cell_name (path.back ())) + "." + suffix;
        if (mp_layout_fdia->get_save (fn)) {

          db::SaveLayoutOptions options (cv->save_options ());
          options.set_dbu (cv->layout ().dbu ());
          options.set_format_from_filename (fn);

          tl::OutputStream::OutputStreamMode om = tl::OutputStream::OM_Auto;
          if (mp_layout_save_as_options->get_options (current_view (), cv_index, fn, om, options, this, false)) {

            options.clear_cells ();

            std::vector<lay::LayoutView::cell_path_type> paths;
            current_view ()->selected_cells_paths (cv_index, paths);
            for (std::vector<lay::LayoutView::cell_path_type>::const_iterator p = paths.begin (); p != paths.end (); ++p) {
              if (! p->empty ()) {
                options.add_cell (p->back ());
              }
            }

            cv->save_as (fn, om, options, false /*don't update*/);

            add_mru (fn, cv->tech_name ());

          }

        }

      }

    }

  }

  END_PROTECTED
}

void
MainWindow::cm_save ()
{
  do_save (false);
}

void
MainWindow::cm_save_as ()
{
  do_save (true);
}

void
MainWindow::do_save (bool as)
{
  BEGIN_PROTECTED

  if (current_view ()) {

    std::vector<int> cv_indexes;
    if (current_view ()->cellviews () > 1) {
      SelectCellViewForm form (0, current_view (), tl::to_string (QObject::tr ("Select Layout To Save")), false /*multiple selection*/);
      form.set_selection (current_view ()->active_cellview_index ());
      if (form.exec () == QDialog::Accepted) {
        cv_indexes = form.selected_cellviews ();
      }
    } else if (current_view ()->cellviews () == 1) {
      cv_indexes.push_back (0);
    }

    if (! cv_indexes.empty ()) {

      std::string fn;
      for (std::vector<int>::const_iterator i = cv_indexes.begin (); i != cv_indexes.end (); ++i) {

        int cv_index = *i;
        const lay::CellView &cv = current_view ()->cellview (cv_index);

        fn = cv->filename ();

        if (! (as || fn.empty ()) || mp_layout_fdia->get_save (fn, tl::to_string (tr ("Layout '%1'").arg (tl::to_qstring (cv->name ()))))) {

          db::SaveLayoutOptions options (cv->save_options ());
          options.set_dbu (cv->layout ().dbu ());

          options.set_format_from_filename (fn);

          tl::OutputStream::OutputStreamMode om = tl::OutputStream::OM_Auto;

          if (! as) {

            //  initialize the specific options from the configuration ("writer options")
            for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
              const StreamWriterPluginDeclaration *decl = dynamic_cast <const StreamWriterPluginDeclaration *> (&*cls);
              if (decl && decl->format_name () == options.format ()) {
                options.set_specific_options (decl->create_specific_options (this));
                break;
              }
            }

          } else if (! mp_layout_save_as_options->get_options (current_view (), cv_index, fn, om, options, this, true)) {
            break;
          }

          current_view ()->save_as ((unsigned int) cv_index, fn, om, options, true);
          add_mru (fn, current_view ()->cellview (cv_index)->tech_name ());

        }

      }

    }

  } else {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to save")));
  }

  END_PROTECTED
}

void
MainWindow::cm_save_all ()
{
  BEGIN_PROTECTED

    for (int view_index = 0; view_index < int (views ()); ++view_index) {

      for (unsigned int cv_index = 0; cv_index < view (view_index)->cellviews (); ++cv_index) {

        const lay::CellView &cv = view (view_index)->cellview (cv_index);
        std::string fn = cv->filename ();

        if (! fn.empty () || mp_layout_fdia->get_save (fn, tl::to_string (tr ("Layout '%1'").arg (tl::to_qstring (cv->name ()))))) {

          db::SaveLayoutOptions options (cv->save_options ());
          options.set_dbu (cv->layout ().dbu ());

          options.set_format_from_filename (fn);

          tl::OutputStream::OutputStreamMode om = tl::OutputStream::OM_Auto;

          //  initialize the specific options from the configuration if required
          if (! options.get_specific_options ()) {

            for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
              const StreamWriterPluginDeclaration *decl = dynamic_cast <const StreamWriterPluginDeclaration *> (&*cls);
              if (decl && decl->format_name () == options.format ()) {
                options.set_specific_options (decl->create_specific_options (this));
                break;
              }
            }

          }

          view (view_index)->save_as (cv_index, fn, om, options, true);
          add_mru (fn, current_view ()->cellview (cv_index)->tech_name ());

        }

      }

    }

  END_PROTECTED
}

void
MainWindow::cm_setup ()
{
  mp_setup_form->show ();
  mp_setup_form->setup ();
}

void
MainWindow::view_selected (int index)
{
  if (index >= 0 && index < int (views ())) {

    //  Hint: setting the focus to the tab bar avoids problem with dangling keyboard focus.
    //  Sometimes, the focus was set to the hierarchy level spin buttons which caught Copy&Paste
    //  events in effect.
    mp_tab_bar->setFocus ();

    if (! m_disable_tab_selected) {
      select_view (index);
    }

  }
}

void
MainWindow::select_view (int index)
{
  bool dis = m_disable_tab_selected;
  m_disable_tab_selected = true; // prevent recursion

  try {

    tl_assert (index >= 0 && index < int (views ()));

    int view_index_org = current_view_index ();

    mp_tab_bar->setCurrentIndex (index);

    bool box_set = (m_synchronized_views && current_view () != 0);
    db::DBox box;
    if (box_set) {
      box = current_view ()->viewport ().box ();
    }

    m_current_view = index;

    mp_layer_toolbox->set_view (current_view ());

    if (current_view ()) {

      if (box_set) {
        current_view ()->zoom_box (box);
      }

      mp_view_stack->raiseWidget (m_current_view);
      mp_hp_stack->raiseWidget (m_current_view);
      mp_lp_stack->raiseWidget (m_current_view);
      mp_setup_form->setup ();

    }

    m_current_view_observers.signal_observers ();
    m_current_view_observers.signal_observers (int (view_index_org));

    m_disable_tab_selected = dis;

  } catch (...) {
    m_disable_tab_selected = dis;
    throw;
  }
}

void 
MainWindow::cm_open_too ()
{
  open (2);
}

void 
MainWindow::cm_open_new_view ()
{
  open (1);
}

void 
MainWindow::cm_open ()
{
  open (0);
}

void 
MainWindow::cm_pull_in ()
{
  BEGIN_PROTECTED

  std::vector <std::string> names;
  lay::LayoutHandle::get_names (names);

  QStringList layouts;
  for (std::vector <std::string>::const_iterator n = names.begin (); n != names.end (); ++n) {
    layouts << tl::to_qstring (*n);
  }

  if (layouts.size () == 0) {
    throw tl::Exception (tl::to_string (QObject::tr ("No layouts loaded")));
  }

  bool ok = false;
  QString item = QInputDialog::getItem (this, QObject::tr ("Choose Layout"),
                                        QObject::tr ("Choose an existing layout for being opened in the current view\nadditionally to the layouts already shown"),
                                        layouts, 0, false, &ok);
  if (ok) {

    lay::LayoutHandle *layout_handle = lay::LayoutHandle::find (tl::to_string (item));
    if (layout_handle) {

      if (! current_view ()) {
        create_view ();
      }

      if (current_view ()) {

        //  If there is another view holding that layout already, take the layer properties from there
        int other_cv_index = -1;
        const lay::LayoutView *other_view = 0;
        for (unsigned int i = 0; i < views () && other_cv_index < 0; ++i) {
          for (unsigned int cvi = 0; cvi < view (i)->cellviews () && other_cv_index < 0; ++cvi) {
            if (view (i)->cellview (cvi).handle () == layout_handle) {
              other_view = view (i);
              other_cv_index = int (cvi);
            }
          }
        }

        if (! other_view) {
          current_view ()->add_layout (layout_handle, true);
        } else {

          unsigned int cv_index = current_view ()->add_layout (layout_handle, true, false /*don't initialize layers*/);

          std::vector<lay::LayerPropertiesList> other_props;
          for (unsigned int i = 0; i < other_view->layer_lists (); ++i) {
            other_props.push_back (other_view->get_properties (i));
            other_props.back ().remove_cv_references (other_cv_index, true);
            other_props.back ().translate_cv_references (cv_index);
          }

          current_view ()->merge_layer_props (other_props);

        }

      }

    }

  }

  END_PROTECTED
}

void
MainWindow::cm_reader_options ()
{
  mp_layout_load_options->get_global_options (m_reader_options, m_initial_technology);
}

void
MainWindow::cm_writer_options ()
{
  mp_layout_save_options->exec (this);
}

void 
MainWindow::cm_new_panel ()
{
  create_view ();
}

void 
MainWindow::cm_new_layout ()
{
  BEGIN_PROTECTED

  std::string technology = m_initial_technology;

  lay::NewLayoutPropertiesDialog dialog (this);
  if (dialog.exec (technology, m_new_cell_cell_name, m_default_dbu, m_new_cell_window_size, m_new_layout_current_panel)) {

    const lay::CellView &cellview = create_or_load_layout (0, 0, technology, m_new_layout_current_panel ? 2 : 1 /*= new view*/);

    cellview->layout ().dbu (m_default_dbu);
    db::cell_index_type new_ci = cellview->layout ().add_cell (m_new_cell_cell_name.empty () ? 0 : m_new_cell_cell_name.c_str ());

    current_view ()->select_cell (new_ci, current_view ()->active_cellview_index ());
    current_view ()->zoom_box (db::DBox (-0.5 * m_new_cell_window_size, -0.5 * m_new_cell_window_size, 0.5 * m_new_cell_window_size, 0.5 * m_new_cell_window_size));
    current_view ()->set_hier_levels (std::make_pair (0, 1));

    //  make the current settings default for new calls of the dialog (and maybe for other
    //  components)
    config_set (cfg_default_dbu, m_default_dbu);
    config_finalize ();

  }

  END_PROTECTED
}

void
MainWindow::call_on_current_view (void (lay::LayoutView::*func) (), const std::string &op_desc)
{
  BEGIN_PROTECTED

  lay::LayoutView *curr = current_view ();
  if (! curr || curr->active_cellview_index () < 0) {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open for operation: ")) + op_desc);
  }

  (curr->*func) ();

  END_PROTECTED
}

void 
MainWindow::cm_adjust_origin ()
{
  call_on_current_view (&lay::LayoutView::cm_align_cell_origin, tl::to_string (QObject::tr ("adjust cell origin")));
}

void 
MainWindow::cm_new_cell ()
{
  BEGIN_PROTECTED

  lay::LayoutView *curr = current_view ();
  if (! curr || curr->active_cellview_index () < 0) {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to create a new cell inside")));
  }

  NewCellPropertiesDialog cell_prop_dia (this); 
  if (cell_prop_dia.exec (& curr->cellview (curr->active_cellview_index ())->layout (), m_new_cell_cell_name, m_new_cell_window_size)) {

    db::cell_index_type new_ci = curr->new_cell (curr->active_cellview_index (), m_new_cell_cell_name.c_str ());
    curr->select_cell (new_ci, curr->active_cellview_index ());
    curr->zoom_box (db::DBox (-0.5 * m_new_cell_window_size, -0.5 * m_new_cell_window_size, 0.5 * m_new_cell_window_size, 0.5 * m_new_cell_window_size));

    if (curr->get_max_hier_levels () < 1 || curr->get_min_hier_levels () > 0) {
      curr->set_hier_levels (std::make_pair (0, 1));
    }

  }

  END_PROTECTED
}

void
MainWindow::cm_cell_convert_to_static ()
{
  call_on_current_view (&lay::LayoutView::cm_cell_convert_to_static, tl::to_string (QObject::tr ("convert cell to static")));
}

void
MainWindow::cm_lay_convert_to_static ()
{
  call_on_current_view (&lay::LayoutView::cm_lay_convert_to_static, tl::to_string (QObject::tr ("convert all cells to static")));
}

void 
MainWindow::cm_lay_move ()
{
  call_on_current_view (&lay::LayoutView::cm_lay_move, tl::to_string (QObject::tr ("move layout")));
}

void 
MainWindow::cm_lay_scale ()
{
  call_on_current_view (&lay::LayoutView::cm_lay_scale, tl::to_string (QObject::tr ("scale layout")));
}

void 
MainWindow::cm_lay_free_rot ()
{
  call_on_current_view (&lay::LayoutView::cm_lay_free_rot, tl::to_string (QObject::tr ("free rotation of layout")));
}

void 
MainWindow::cm_lay_rot_ccw ()
{
  call_on_current_view (&lay::LayoutView::cm_lay_rot_ccw, tl::to_string (QObject::tr ("counter clockwise rotation of layout")));
}

void 
MainWindow::cm_lay_rot_cw ()
{
  call_on_current_view (&lay::LayoutView::cm_lay_rot_cw, tl::to_string (QObject::tr ("clockwise rotation of layout")));
}

void 
MainWindow::cm_lay_flip_y ()
{
  call_on_current_view (&lay::LayoutView::cm_lay_flip_y, tl::to_string (QObject::tr ("vertical flip of layout")));
}

void 
MainWindow::cm_lay_flip_x ()
{
  call_on_current_view (&lay::LayoutView::cm_lay_flip_x, tl::to_string (QObject::tr ("horizontal flip of layout")));
}

void 
MainWindow::cm_sel_move ()
{
  call_on_current_view (&lay::LayoutView::cm_sel_move, tl::to_string (QObject::tr ("move selection")));
}

void 
MainWindow::cm_sel_move_to ()
{
  call_on_current_view (&lay::LayoutView::cm_sel_move_to, tl::to_string (QObject::tr ("move selection to position")));
}

void 
MainWindow::cm_sel_scale ()
{
  call_on_current_view (&lay::LayoutView::cm_sel_scale, tl::to_string (QObject::tr ("scale selection")));
}

void 
MainWindow::cm_sel_free_rot ()
{
  call_on_current_view (&lay::LayoutView::cm_sel_free_rot, tl::to_string (QObject::tr ("free rotation of selection")));
}

void 
MainWindow::cm_sel_rot_ccw ()
{
  call_on_current_view (&lay::LayoutView::cm_sel_rot_ccw, tl::to_string (QObject::tr ("counter clockwise rotation of selection")));
}

void 
MainWindow::cm_sel_rot_cw ()
{
  call_on_current_view (&lay::LayoutView::cm_sel_rot_cw, tl::to_string (QObject::tr ("clockwise rotation of selection")));
}

void 
MainWindow::cm_sel_flip_y ()
{
  call_on_current_view (&lay::LayoutView::cm_sel_flip_y, tl::to_string (QObject::tr ("vertical flip of selection")));
}

void 
MainWindow::cm_sel_flip_x ()
{
  call_on_current_view (&lay::LayoutView::cm_sel_flip_x, tl::to_string (QObject::tr ("horizontal flip of selection")));
}

void 
MainWindow::cm_edit_layer ()
{
  call_on_current_view (&lay::LayoutView::cm_edit_layer, tl::to_string (QObject::tr ("edit a layer specification")));
}

void 
MainWindow::cm_delete_layer ()
{
  call_on_current_view (&lay::LayoutView::cm_delete_layer, tl::to_string (QObject::tr ("delete a layer")));
}

void 
MainWindow::cm_clear_layer ()
{
  call_on_current_view (&lay::LayoutView::cm_clear_layer, tl::to_string (QObject::tr ("clear a layer")));
}

void 
MainWindow::cm_copy_layer ()
{
  call_on_current_view (&lay::LayoutView::cm_copy_layer, tl::to_string (QObject::tr ("copy layer")));
}

void 
MainWindow::cm_new_layer ()
{
  call_on_current_view (&lay::LayoutView::cm_new_layer, tl::to_string (QObject::tr ("create a new layer")));
}

void 
MainWindow::cm_layout_props ()
{
  BEGIN_PROTECTED

  lay::LayoutView *curr = current_view ();
  if (! curr) {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to show layout properties for")));
  }

  LayoutPropertiesForm lp_form (this, curr, "layout_props_form");
  lp_form.exec ();

  END_PROTECTED
}

void 
MainWindow::cm_layout_stats ()
{
  BEGIN_PROTECTED

  lay::LayoutView *curr = current_view ();
  if (! curr) {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to show layout statistics for")));
  }

  LayoutStatisticsForm lp_form (this, curr, "layout_props_form");
  lp_form.exec ();

  END_PROTECTED
}

void 
MainWindow::cm_clone ()
{
  BEGIN_PROTECTED
  clone_current_view ();
  END_PROTECTED
}

void
MainWindow::clone_current_view ()
{
  lay::LayoutView *view = 0;
  lay::LayoutView *curr = current_view ();
  if (! curr) {
    throw tl::Exception (tl::to_string (QObject::tr ("No view open to clone")));
  }

  //  create a new view
  view = new lay::LayoutView (current_view (), &m_manager, this, mp_view_stack);
  connect (view, SIGNAL (title_changed ()), this, SLOT (view_title_changed ()));
  mp_views.push_back (view);

  //  we must resize the widget here to set the geometry properly. 
  //  This is required to make zoom_fit work.
  view->setGeometry (0, 0, mp_view_stack->width (), mp_view_stack->height ());
  view->show ();

  //  set initial attributes
  view->set_hier_levels (curr->get_hier_levels ());

  //  select the current mode and select the enabled editables
  view->mode (m_mode);

  lay::DisplayState state;
  current_view ()->save_view (state);
  view->goto_view (state);

  view->update_content ();

  m_current_view = mp_views.size () - 1;

  mp_layer_toolbox->set_view (current_view ());

  mp_view_stack->addWidget (view);
  mp_lp_stack->addWidget (view->layer_control_frame ());
  mp_hp_stack->addWidget (view->hierarchy_control_frame ());

  bool f = m_disable_tab_selected;
  m_disable_tab_selected = true;
  int index = mp_tab_bar->insertTab (-1, tl::to_qstring (view->title ()));
  m_disable_tab_selected = f;

  m_new_view_observers.signal_observers ();
  select_view (index);

  update_dock_widget_state ();
}

void 
MainWindow::cm_close_all ()
{
  interactive_close_view (-1, false);
}
 
void 
MainWindow::cm_close ()
{
  interactive_close_view (m_current_view, false);
}
 
void
MainWindow::tab_close_requested (int index)
{
  interactive_close_view (index, true);
}

void 
MainWindow::interactive_close_view (int index, bool all_cellviews)
{
  if (index < 0) {

    //  close all views
    
    bool can_close = true;

    if (lay::Application::instance ()->is_editable ()) {

      int dirty_layouts = 0;
      std::string dirty_files;
      std::set<std::string> seen_names;

      for (index = 0; index < int (views ()); ++index) {

        for (unsigned int i = 0; i < view (index)->cellviews (); ++i) {

          if (view (index)->cellview (i)->is_dirty ()) {

            std::string name = view (index)->cellview (i)->name ();
            if (seen_names.find (name) != seen_names.end ()) {
              continue;
            }

            seen_names.insert (name);

            ++dirty_layouts;
            if (dirty_layouts == max_dirty_files) {
              dirty_files += "\n...";
            } else if (dirty_layouts < max_dirty_files) {
              if (! dirty_files.empty ()) {
                dirty_files += "\n";
              }
              dirty_files += name;
            }

          }

        }

      }

      if (dirty_layouts != 0) {

        QMessageBox mbox (this);
        mbox.setText (tl::to_qstring (tl::to_string (QObject::tr ("The following layouts need saving:\n\n")) + dirty_files + tl::to_string (QObject::tr ("\n\nPress 'Close Without Saving' to close them anyway and discard changes\n")))),
        mbox.setWindowTitle (QObject::tr ("Save Needed"));
        mbox.setIcon (QMessageBox::Warning);
        QAbstractButton *can_close_button = mbox.addButton (QObject::tr ("Close Without Saving"), QMessageBox::YesRole);
        mbox.addButton (QMessageBox::Cancel);

        mbox.exec ();

        can_close = (mbox.clickedButton() == can_close_button);

      }

    }

    if (can_close) {
      BEGIN_PROTECTED
      while (views () > 0) {
        close_view (0);
      }
      END_PROTECTED
    }

  } else if (view (index)) {

    std::vector <int> selected;

    if (view (index)->cellviews () > 1) {

      if (all_cellviews) {

        for (int i = 0; i < int (view (index)->cellviews ()); ++i) {
          selected.push_back (i);
        }

      } else {

        SelectCellViewForm form (0, view (index), tl::to_string (QObject::tr ("Select Layouts To Close")));
        form.set_selection (view (index)->active_cellview_index ());
      
        if (form.exec () != QDialog::Accepted) {
          return;
        }

        selected = form.selected_cellviews ();
        if (selected.empty ()) {
          return;
        }

      }
        
    } else if (view (index)->cellviews () > 0) {
      selected.push_back (0);
    }

    if (selected.size () > 0) {

      int dirty_layouts = 0;
      std::string dirty_files;

      if (lay::Application::instance ()->is_editable ()) {
        for (std::vector <int>::const_iterator i = selected.begin (); i != selected.end (); ++i) {
          if (view (index)->cellview (*i)->is_dirty ()) {

            std::string name = view (index)->cellview (*i)->name ();

            int count = 0;

            for (std::vector <lay::LayoutView *>::const_iterator v = mp_views.begin (); v != mp_views.end (); ++v) {
              for (unsigned int cvi = 0; cvi < (*v)->cellviews (); ++cvi) {
                if ((*v)->cellview (cvi)->name () == name) {
                  ++count;
                }
              }
            }

            for (std::vector <int>::const_iterator ii = selected.begin (); ii != selected.end (); ++ii) {
              if (view (index)->cellview (*ii)->name () == name) {
                --count;
              }
            }

            //  only report layouts as dirty which will vanish if we would close all layouts 
            if (count <= 0) { 
              ++dirty_layouts;
              if (dirty_layouts == max_dirty_files) {
                dirty_files += "\n...";
              } else if (dirty_layouts < max_dirty_files) {
                if (! dirty_files.empty ()) {
                  dirty_files += "\n";
                }
                dirty_files += name;
              }
            }

          }
        }
      }

      bool can_close = true;
      if (dirty_layouts != 0) {

        QMessageBox mbox (this);
        mbox.setText (tl::to_qstring (tl::to_string (QObject::tr ("The following layouts need saving:\n\n")) + dirty_files + tl::to_string (QObject::tr ("\n\nPress 'Close Without Saving' to close them anyway and discard changes\n")))),
        mbox.setWindowTitle (QObject::tr ("Save Needed"));
        mbox.setIcon (QMessageBox::Warning);
        QAbstractButton *can_close_button = mbox.addButton (QObject::tr ("Close Without Saving"), QMessageBox::YesRole);
        mbox.addButton (QMessageBox::Cancel);

        mbox.exec ();

        can_close = (mbox.clickedButton() == can_close_button);

      }

      if (can_close) {

        BEGIN_PROTECTED

        //  Actually erase the selected cellviews
        if (view (index)->cellviews () == selected.size ()) {
          //  all cellviews selected - simply close
          close_view (index);
        } else {
          std::sort (selected.begin (), selected.end ());
          int offset = 0;
          for (std::vector <int>::const_iterator i = selected.begin (); i != selected.end (); ++i) {
            view (index)->erase_cellview ((unsigned int)(*i - offset));
            ++offset;
          }
        }

        END_PROTECTED

      }

    } else {
      close_view (index);
    }

  }

}

void 
MainWindow::close_current_view ()
{
  close_view (m_current_view);
}

void 
MainWindow::close_view (int index)
{
  if (view (index)) {

    //  this suppresses view_selected events that would otherwise be created
    bool f = m_disable_tab_selected;
    m_disable_tab_selected = true;

    BEGIN_PROTECTED

      bool box_set = false;
      db::DBox box;
      if (m_synchronized_views) {
        box = view (index)->viewport ().box ();
        box_set = true;
      }

      mp_tab_bar->removeTab (index);
      mp_view_stack->removeWidget (index);
      mp_lp_stack->removeWidget (index);
      mp_hp_stack->removeWidget (index);

      m_view_closed_observers.signal_observers (int (index));

      delete view (index);
      mp_views.erase (mp_views.begin () + index, mp_views.begin () + index + 1);

      if (int (m_current_view) >= index) {

        int view_index_org = m_current_view;

        if (m_current_view > 0) {
          if (int (m_current_view) > index) {
            --m_current_view;
          } else if (m_current_view >= mp_views.size ()) {
            --m_current_view;
          }
        }

        mp_layer_toolbox->set_view (current_view ());

        if (current_view ()) {
          if (box_set) {
            current_view ()->zoom_box (box);
          }
          mp_tab_bar->setCurrentIndex (m_current_view);
          mp_view_stack->raiseWidget (m_current_view);
          mp_lp_stack->raiseWidget (m_current_view);
          mp_hp_stack->raiseWidget (m_current_view);
        }

        m_current_view_observers.signal_observers ();
        m_current_view_observers.signal_observers (int (view_index_org));

        update_dock_widget_state ();

      }

    END_PROTECTED

    m_disable_tab_selected = f;

  }
}

void
MainWindow::cm_reload ()
{    
  BEGIN_PROTECTED 

  if (current_view ()) {

    std::vector <int> selected;

    if (current_view ()->cellviews () > 1) {

      SelectCellViewForm form (0, current_view (), tl::to_string (QObject::tr ("Select Layouts To Reload")));
      form.select_all ();
    
      if (form.exec () == QDialog::Accepted) {
        selected = form.selected_cellviews ();
      }
        
    } else if (current_view ()->cellviews () > 0) {
      selected.push_back (0);
    }

    if (selected.size () > 0) {

      int dirty_layouts = 0;
      std::string dirty_files;

      if (lay::Application::instance ()->is_editable ()) {
        for (std::vector <int>::const_iterator i = selected.begin (); i != selected.end (); ++i) {
          if (current_view ()->cellview (*i)->is_dirty ()) {
            ++dirty_layouts;
            if (dirty_layouts == max_dirty_files) {
              dirty_files += "\n...";
            } else if (dirty_layouts < max_dirty_files) {
              if (! dirty_files.empty ()) {
                dirty_files += "\n";
              }
              dirty_files += current_view ()->cellview (*i)->name ();
            }
          }
        }
      }

      bool can_reload = true;
      if (dirty_layouts != 0) {

        QMessageBox mbox (this);
        mbox.setText (tl::to_qstring (tl::to_string (QObject::tr ("The following layouts need saving:\n\n")) + dirty_files + "\n\nPress 'Reload Without Saving' to reload anyhow and discard changes."));
        mbox.setWindowTitle (QObject::tr ("Save Needed"));
        mbox.setIcon (QMessageBox::Warning);
        QAbstractButton *yes_button = mbox.addButton (QObject::tr ("Reload Without Saving"), QMessageBox::YesRole);
        mbox.addButton (QMessageBox::Cancel);

        mbox.exec ();

        can_reload = (mbox.clickedButton() == yes_button);

      }

      if (can_reload) {

        //  Actually reload
        for (std::vector <int>::const_iterator i = selected.begin (); i != selected.end (); ++i) {
          reload_layout (*i);
        }

      }

    }

  }

  END_PROTECTED
}

void
MainWindow::add_mru (const std::string &fn_rel)
{
  add_mru (fn_rel, m_initial_technology);
}

void
MainWindow::add_mru (const std::string &fn_rel, const std::string &tech)
{
  std::vector <std::pair<std::string, std::string> > new_mru (m_mru);
  std::string fn (tl::InputStream::absolute_path (fn_rel));

  for (std::vector<std::pair<std::string, std::string> >::iterator mru = new_mru.begin (); mru != new_mru.end (); ++mru) {
    if (mru->first == fn) {
      new_mru.erase (mru);
      break;
    }
  }

  new_mru.push_back (std::make_pair (fn, tech));

  if (new_mru.size () > 10) {
    new_mru.erase (new_mru.begin ());
  }

  std::string config_str;
  for (std::vector<std::pair<std::string, std::string> >::const_iterator mru = new_mru.begin (); mru != new_mru.end (); ++mru) {
    if (! config_str.empty ()) {
      config_str += " ";
    }
    config_str += tl::to_quoted_string (mru->first);
    if (! mru->second.empty ()) {
      config_str += "@";
      config_str += tl::to_quoted_string (mru->second);
    }
  }

  config_set (cfg_mru, config_str);
}

void 
MainWindow::file_menu_show ()
{
  if (mp_menu->is_valid ("file_menu.open_recent_menu")) {

    Action open_recent_action = mp_menu->action ("file_menu.open_recent_menu");

    if (m_mru.size () > 0 && m_edits_enabled) {

      open_recent_action.set_enabled (true);

      QMenu *open_recent_menu = open_recent_action.qaction ()->menu ();
      if (open_recent_menu) {

        open_recent_menu->clear ();

        for (std::vector<std::pair<std::string, std::string> >::iterator mru = m_mru.end (); mru != m_mru.begin (); ) {
          --mru;
          unsigned int i = std::distance (m_mru.begin (), mru);
          QAction *action = open_recent_menu->addAction (tl::to_qstring (mru->first));
          action->setObjectName (tl::to_qstring (tl::sprintf ("open_recent_%d", i + 1)));
          gtf::action_connect (action, SIGNAL (triggered ()), this, SLOT (open_recent ()));
          action->setData (QVariant (int (i))); 
        }

      }

    } else {
      open_recent_action.set_enabled (false);
    }

  }
}

void
MainWindow::open_recent ()
{
  BEGIN_PROTECTED

  QAction *action = dynamic_cast <QAction *> (sender ());
  tl_assert (action);
  size_t n = size_t (action->data ().toInt ());
  if (n >= m_mru.size ()) {
    return;
  }

  OpenLayoutModeDialog open_mode_dialog (this);

  if (views () != 0 && ! open_mode_dialog.exec (m_open_mode)) {
    return;
  }

  if (mp_layout_load_options->show_always () && !mp_layout_load_options->get_global_options (m_reader_options, m_initial_technology)) {
    return;
  }

  std::string fn (m_mru [n].first);  //  create a copy since we change m_mru later
  std::string tech (m_mru [n].second);

  bool can_open = true;

  if (m_open_mode == 0) {

    std::string df_list;
    int dirty_layouts = dirty_files (df_list);

    if (dirty_layouts != 0) {

      QMessageBox mbox (this);
      mbox.setText (tl::to_qstring (tl::to_string (QObject::tr ("The following layouts need saving:\n\n")) + df_list + "\n\nPress 'Close Without Saving' to open the layout and discard changes."));
      mbox.setWindowTitle (QObject::tr ("Save Needed"));
      mbox.setIcon (QMessageBox::Warning);
      QAbstractButton *yes_button = mbox.addButton (QObject::tr ("Close Without Saving"), QMessageBox::YesRole);
      mbox.addButton (QMessageBox::Cancel);

      mbox.exec ();

      can_open = (mbox.clickedButton() == yes_button);

    }

  }

  if (can_open) {
    load_layout (fn, tech, m_open_mode);
    add_mru (fn, tech);  //  make it the latest
  }

  END_PROTECTED
}

void 
MainWindow::open (int mode)
{
  BEGIN_PROTECTED 

  static std::vector<std::string> files;
  if (! mp_layout_fdia->get_open (files)) {
    return;
  }

  if (mp_layout_load_options->show_always () && !mp_layout_load_options->get_global_options (m_reader_options, m_initial_technology)) {
    return;
  }

  bool can_open = true;

  if (mode == 0) {

    std::string df_list;
    int dirty_layouts = dirty_files (df_list);

    if (dirty_layouts != 0) {

      QMessageBox mbox (this);
      mbox.setText (tl::to_qstring (tl::to_string (QObject::tr ("The following layouts need saving:\n\n")) + df_list + "\n\nPress 'Close Without Saving' to open the layout and discard changes."));
      mbox.setWindowTitle (QObject::tr ("Save Needed"));
      mbox.setIcon (QMessageBox::Warning);
      QAbstractButton *yes_button = mbox.addButton (QObject::tr ("Close Without Saving"), QMessageBox::YesRole);
      mbox.addButton (QMessageBox::Cancel);

      mbox.exec ();

      can_open = (mbox.clickedButton() == yes_button);

    }

  }

  if (can_open) {

    for (std::vector<std::string>::const_iterator fn = files.begin (); fn != files.end (); ++fn) {
      load_layout (*fn, m_reader_options, m_initial_technology, mode);
      //  open next layout in "add view" mode, if the current view was overridden -
      //  otherwise that would happen once again.
      if (mode == 0) {
        mode = 1;
      }
      add_mru (*fn, m_initial_technology);
    }

  }

  END_PROTECTED
}

void
MainWindow::reload_layout (unsigned int cv_index)
{
  lay::LayoutView *view = current_view ();

  if (view && view->cellviews () > cv_index) {
    view->reload_layout (cv_index);
  }
}

const lay::CellView &
MainWindow::load_layout (const std::string &filename, const db::LoadLayoutOptions &options, const std::string &technology, int mode)
{
  return create_or_load_layout (&filename, &options, technology, mode);
}

const lay::CellView &
MainWindow::create_layout (const std::string &technology, int mode)
{
  return create_or_load_layout (0, 0, technology, mode);
}

int 
MainWindow::do_create_view ()
{
  //  create a new view
  lay::LayoutView *view = new lay::LayoutView (&m_manager, this, mp_view_stack);

  connect (view, SIGNAL (title_changed ()), this, SLOT (view_title_changed ()));

  mp_views.push_back (view);

  //  we must resize the widget here to set the geometry properly. 
  //  This is required to make zoom_fit work.
  view->setGeometry (0, 0, mp_view_stack->width (), mp_view_stack->height ());
  view->show ();

  //  set initial attributes
  view->set_synchronous (synchronous ());

  int tl = 0;
  config_get (cfg_initial_hier_depth, tl);
  view->set_hier_levels (std::make_pair (0, tl));

  //  select the current mode and select the enabled editables
  view->mode (m_mode);

  return int (mp_views.size () - 1);
}

int
MainWindow::create_view ()
{
  //  create a new view
  int view_index = do_create_view ();

  //  add a new tab and make the new view the current one
  m_current_view = mp_views.size () - 1;

  mp_layer_toolbox->set_view (current_view ());

  mp_view_stack->addWidget (mp_views.back ());
  mp_lp_stack->addWidget (mp_views.back ()->layer_control_frame ());
  mp_hp_stack->addWidget (mp_views.back ()->hierarchy_control_frame ());

  bool f = m_disable_tab_selected;
  m_disable_tab_selected = true;
  int index = mp_tab_bar->insertTab (-1, tl::to_qstring (current_view ()->title ()));
  m_disable_tab_selected = f;

  m_new_view_observers.signal_observers ();
  select_view (index);

  update_dock_widget_state ();

  return view_index;
}

const lay::CellView & 
MainWindow::create_or_load_layout (const std::string *filename, const db::LoadLayoutOptions *options, const std::string &technology, int mode)
{
  lay::LayoutView *vw = 0;

  int view_index_org = current_view_index ();

  if (! current_view ()) {
    mode = 1;
  }

  if (mode == 1) {
    //  create a new view
    vw = view (do_create_view ());
  } else {
    //  take the current view
    vw = current_view ();
    if (mode == 0) {
      //  reset the hierarchy depth in the "replace" case
      int tl = 0;
      config_get (cfg_initial_hier_depth, tl);
      vw->set_hier_levels (std::make_pair (0, tl));
    }
  }

  unsigned int cv_index = 0; 

  try {

    //  load or create the layout
    if (filename != 0) {
      tl_assert (options != 0);
      cv_index = vw->load_layout (*filename, *options, technology, mode == 2);
    } else {
      cv_index = vw->create_layout (technology, mode == 2);
    }

    //  make the new view the current one
    if (mode == 1) {

      m_current_view = mp_views.size () - 1;

      mp_layer_toolbox->set_view (current_view ());

      mp_view_stack->addWidget (mp_views.back ());
      mp_lp_stack->addWidget (mp_views.back ()->layer_control_frame ());
      mp_hp_stack->addWidget (mp_views.back ()->hierarchy_control_frame ());

      bool f = m_disable_tab_selected;
      m_disable_tab_selected = true;
      int index = mp_tab_bar->insertTab (-1, tl::to_qstring (current_view ()->title ()));
      m_disable_tab_selected = f;
      select_view (index);

    } else if (mode == 0) {
      mp_tab_bar->setTabText (m_current_view, tl::to_qstring (current_view ()->title ()));
    } else if (mode == 2) {
      mp_tab_bar->setTabText (m_current_view, tl::to_qstring (current_view ()->title ()));
    }

    m_new_view_observers.signal_observers ();
    m_current_view_observers.signal_observers ();
    m_current_view_observers.signal_observers (int (view_index_org));

    update_dock_widget_state ();

  } catch (...) {

    //  clean up in case of an error ..
    if (mode == 1) {
      delete mp_views.back ();
      mp_views.pop_back ();
    }

    throw;

  }

  return vw->cellview (cv_index);
}

void 
MainWindow::view_title_changed ()
{
  //  transfer the current view's text into the tab bar
  unsigned int tabs = mp_tab_bar->count ();
  for (unsigned int i = 0; i < tabs && i < views (); ++i) {
    if (tl::to_string (mp_tab_bar->tabText (i)) != view (i)->title ()) {
      mp_tab_bar->setTabText (i, tl::to_qstring (view (i)->title ()));
    }
  }
}

double
MainWindow::grid_micron () const
{
  return m_grid_micron;
}

void 
MainWindow::cm_inc_max_hier ()
{
  BEGIN_PROTECTED 

  int new_to = get_max_hier_levels () + 1;
  set_hier_levels (std::make_pair (get_min_hier_levels (), new_to));

  END_PROTECTED
}

void 
MainWindow::cm_dec_max_hier ()
{
  BEGIN_PROTECTED 

  int new_to = get_max_hier_levels () > 0 ? get_max_hier_levels () - 1 : 0;
  set_hier_levels (std::make_pair (std::min (get_min_hier_levels (), new_to), new_to));

  END_PROTECTED
}

void 
MainWindow::cm_max_hier ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->max_hier ();
  }

  END_PROTECTED
}

void 
MainWindow::cm_max_hier_0 ()
{
  BEGIN_PROTECTED 
  set_hier_levels (std::make_pair (std::min (get_min_hier_levels (), 0), 0));
  END_PROTECTED
}

void 
MainWindow::cm_max_hier_1 ()
{
  BEGIN_PROTECTED 
  set_hier_levels (std::make_pair (std::min (get_min_hier_levels (), 0), 1));
  END_PROTECTED
}

void 
MainWindow::set_hier_levels (std::pair<int, int> l)
{
  if (l != get_hier_levels ()) {
    if (current_view ()) {
      current_view ()->set_hier_levels (l);
    }
  } 
}

std::pair<int, int> 
MainWindow::get_hier_levels () const
{
  if (current_view ()) {
    return current_view ()->get_hier_levels ();
  } else {
    int tl = 0;
    config_get (cfg_initial_hier_depth, tl);
    return std::make_pair (0, tl);
  }
}

void 
MainWindow::cm_last_display_state ()
{
  BEGIN_PROTECTED 

  if (has_last_display_state ()) {
    current_view ()->last_display_state ();
  }

  END_PROTECTED
}

bool 
MainWindow::has_last_display_state ()
{
  if (current_view ()) {
    return current_view ()->has_last_display_state ();
  } else {
    return false;
  }
}

void 
MainWindow::cm_next_display_state ()
{
  BEGIN_PROTECTED 

  if (has_next_display_state ()) {
    current_view ()->next_display_state ();
  }

  END_PROTECTED
}

bool 
MainWindow::has_next_display_state ()
{
  if (current_view ()) {
    return current_view ()->has_next_display_state ();
  } else {
    return false;
  }
}

void 
MainWindow::set_synchronous (bool sync_mode)
{
  m_synchronous = sync_mode;
  for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
    (*vp)->set_synchronous (sync_mode);
  }
}

void
MainWindow::current_pos (double x, double y, bool dbu_units) 
{
  mp_cpx_label->setText (tl::to_qstring (dbu_units ? tl::db_to_string (x) : tl::micron_to_string (x)));
  mp_cpy_label->setText (tl::to_qstring (dbu_units ? tl::db_to_string (y) : tl::micron_to_string (y)));
}

void
MainWindow::clear_current_pos ()
{
  mp_cpx_label->setText (QString ());
  mp_cpy_label->setText (QString ());
}

void 
MainWindow::set_progress_can_cancel (bool f)
{
  if (mp_progress_dialog.get ()) {
    mp_progress_dialog->set_can_cancel (f);
  } else if (isVisible () && mp_progress_widget) {
    mp_progress_widget->set_can_cancel (f);
  } else {
    TextProgress::set_progress_can_cancel (f);
  }
}

void 
MainWindow::set_progress_text (const std::string &text)
{
  if (mp_progress_dialog.get ()) {
    mp_progress_dialog->set_text (text);
  } else if (isVisible () && mp_progress_widget) {
    mp_progress_widget->set_text (text);
  } else {
    TextProgress::set_progress_text (text);
  }
}

void 
MainWindow::set_progress_value (double v, const std::string &value)
{
  if (mp_progress_dialog.get ()) {
    mp_progress_dialog->set_value (v, value);
  } else if (isVisible () && mp_progress_widget) {
    mp_progress_widget->set_value (v, value);
  } else {
    TextProgress::set_progress_value (v, value);
  }
}

void 
MainWindow::show_progress_bar (bool show)
{
  if (!isVisible ()) {

    mp_progress_dialog.reset (0);

    if (show) {
      QWidget *tl = QApplication::activeWindow ();
      if (tl && tl->isVisible ()) {
        mp_progress_dialog.reset (new ProgressDialog (tl, mp_pr));
        mp_progress_dialog->show ();
      }
    } else {
      TextProgress::show_progress_bar (show);
    }

  } else {

    if (m_work_in_progress != show) {

      m_work_in_progress = show;
      if (show) {
        //  to avoid recursions of any kind, disallow any user interaction except
        //  cancelling the operation
        mp_app->installEventFilter (this);
        QApplication::setOverrideCursor (QCursor (Qt::WaitCursor));
      } else {
        mp_app->removeEventFilter (this);
        QApplication::restoreOverrideCursor ();
      }

      //  HINT: enabling the scheduler is accumulative - make sure that this method is only called when necessary
      tl::DeferredMethodScheduler::instance ()->enable (! show);

      mp_main_stack_widget->setCurrentIndex (show ? 1 : 0);

      if (show) {
        clear_current_pos ();
      }

    }

  }
}

bool 
MainWindow::eventFilter (QObject *watched, QEvent *event)
{
  if (event->type () == QEvent::MouseButtonDblClick ||
      event->type () == QEvent::MouseButtonPress ||
      event->type () == QEvent::MouseButtonRelease ||
      event->type () == QEvent::MouseMove ||
      event->type () == QEvent::KeyPress ||
      event->type () == QEvent::KeyRelease) {

    QObject *o = watched;
    while (o) {
      //  if the watched object is a child of the progress widget, pass the event on to this ..
      if (o == mp_progress_widget) {
        return QObject::eventFilter(watched, event);
      }
      o = o->parent ();
      //  stop at the level of a MessageBox
      if (dynamic_cast<QMessageBox *> (o)) {
        return QObject::eventFilter(watched, event);
      }
    }
    return true;

  } else {
    // standard event processing
    return QObject::eventFilter(watched, event);
  }
}

void
MainWindow::cm_technologies ()
{
  lay::TechSetupDialog dialog (this);
  if (dialog.exec ()) {

    std::vector<lay::MacroCollection *> nm = lay::Application::instance ()->sync_tech_macro_locations ();

    bool has_autorun = false;
    for (std::vector<lay::MacroCollection *>::const_iterator m = nm.begin (); m != nm.end () && ! has_autorun; ++m) {
      has_autorun = (*m)->has_autorun ();
    }

    if (has_autorun && QMessageBox::question (this, QObject::tr ("Run Macros"), QObject::tr ("Some macros associated with technologies now are configured to run automatically.\n\nChoose 'Yes' to run these macros now. Choose 'No' to not run them."), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
      for (std::vector<lay::MacroCollection *>::const_iterator m = nm.begin (); m != nm.end (); ++m) {
        (*m)->autorun ();
      }
    }

    //  because the macro-tech association might have changed, do this:
    update_menu_with_macros ();

  }
}

void 
MainWindow::add_temp_macro (lay::Macro *m)
{
  m_temp_macros.add_unspecific (m);
  update_menu_with_macros ();
}

void 
MainWindow::show_macro_editor (const std::string &cat, bool add)
{
  mp_macro_editor->show (cat, add);
}

void
MainWindow::cm_edit_drc_scripts ()
{
  show_macro_editor ("drc", false);
}

void
MainWindow::cm_new_drc_script ()
{
  show_macro_editor ("drc", true);
}

void
MainWindow::cm_macro_editor ()
{
  show_macro_editor ();
}

void
MainWindow::cm_show_assistant ()
{
  if (mp_assistant->isMinimized ()) {
    mp_assistant->showNormal ();
  } else {
    mp_assistant->show ();
  }
  mp_assistant->activateWindow ();
  mp_assistant->raise ();
}

void 
MainWindow::show_help (const QString &url)
{
  QWidget *parent = dynamic_cast<QWidget *> (sender ());
  if (! parent) {
    parent = this;
  }

  lay::HelpDialog dialog (parent, true);
  dialog.load (tl::to_string (url));
  dialog.exec ();
}

void 
MainWindow::show_assistant_url (const std::string &url, bool modal) 
{
  if (modal) {

    lay::HelpDialog dialog (this, true);
    dialog.load (url);
    dialog.exec ();

  } else {

    if (mp_assistant->isMinimized ()) {
      mp_assistant->showNormal ();
    } else {
      mp_assistant->show ();
    }
    mp_assistant->activateWindow ();
    mp_assistant->raise ();
    mp_assistant->load (url);

  }
}

void 
MainWindow::show_assistant_topic (const std::string &s, bool modal) 
{
  if (modal) {

    lay::HelpDialog dialog (this, true);
    dialog.search (s);
    dialog.exec ();

  } else {

    if (mp_assistant->isMinimized ()) {
      mp_assistant->showNormal ();
    } else {
      mp_assistant->show ();
    }
    mp_assistant->activateWindow ();
    mp_assistant->raise ();
    mp_assistant->search (s);

  }
}

void
MainWindow::cm_show_all_tips ()
{
  config_set (cfg_tip_window_hidden, "");
  config_finalize ();
}

void
MainWindow::cm_help_about ()
{
  HelpAboutDialog help_about_dialog (this);
  help_about_dialog.exec ();
}

void
MainWindow::cm_help_about_qt ()
{
  QApplication::aboutQt ();
}

lay::Action &
MainWindow::action_for_slot (const char *slot)
{
  std::map<std::string, lay::Action>::iterator a = m_actions_for_slot.find (std::string (slot));
  if (a != m_actions_for_slot.end ()) {
    return a->second;
  } else {
    Action a (new ActionHandle (this));
    gtf::action_connect (a.qaction (), SIGNAL (triggered ()), this, slot);
    return m_actions_for_slot.insert (std::make_pair (std::string (slot), a)).first->second;
  }
}

lay::Action *
MainWindow::create_config_action (const std::string &title, const std::string &cname, const std::string &cvalue)
{
  lay::ConfigureAction *ca = new lay::ConfigureAction(this, title, cname, cvalue);
  m_ca_collection.insert (ca);
  return ca;
}

lay::Action *
MainWindow::create_config_action (const std::string &cname, const std::string &cvalue)
{
  lay::ConfigureAction *ca = new lay::ConfigureAction(this, std::string (), cname, cvalue);
  m_ca_collection.insert (ca);
  return ca;
}

void 
MainWindow::register_config_action (const std::string &name, lay::ConfigureAction *action)
{
  std::map<std::string, std::vector<lay::ConfigureAction *> >::iterator ca = m_configuration_actions.insert (std::make_pair (name, std::vector<lay::ConfigureAction *> ())).first;
  for (std::vector<lay::ConfigureAction *>::iterator a = ca->second.begin (); a != ca->second.end (); ++a) {
    if (*a == action) {
      return; // already registered
    }
  }

  ca->second.push_back (action);
}
  
void 
MainWindow::unregister_config_action (const std::string &name, lay::ConfigureAction *action)
{
  std::map<std::string, std::vector<lay::ConfigureAction *> >::iterator ca = m_configuration_actions.find (name);
  if (ca != m_configuration_actions.end ()) {
    for (std::vector<lay::ConfigureAction *>::iterator a = ca->second.begin (); a != ca->second.end (); ++a) {
      if (*a == action) {
        ca->second.erase (a);
        return;
      }
    }
  }
}

void 
MainWindow::generic_menu ()
{
  QAction *action = dynamic_cast <QAction *> (sender ());
  tl_assert (action);
  generic_menu (std::string (action->data ().toString ().toAscii ()));
}

void 
MainWindow::generic_menu (const std::string &symbol)
{
  BEGIN_PROTECTED 

  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    if (cls->menu_activated (symbol)) {
      return;
    }
  }

  if (current_view ()) {
    current_view ()->menu_activated (symbol);
  } else {
    throw tl::Exception (tl::to_string (QObject::tr ("No view is active")));
  }

  END_PROTECTED
}

void
MainWindow::menu_changed ()
{
  //  delay actual rebuilding of the menu to collect multiple change events.
  dm_do_update_menu ();
}

void
MainWindow::do_update_menu ()
{
  mp_menu->build (menuBar (), mp_tool_bar);
}

void
MainWindow::cm_cell_user_properties ()
{
  call_on_current_view (&lay::LayoutView::cm_cell_user_properties, tl::to_string (QObject::tr ("edit cell's user properties")));
}

void
MainWindow::cm_cell_delete ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_cell_delete ();
  }

  END_PROTECTED
}

void
MainWindow::cm_cell_replace ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_cell_replace ();
  }

  END_PROTECTED
}

void
MainWindow::cm_cell_rename ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_cell_rename ();
  }

  END_PROTECTED
}

void
MainWindow::cm_cell_flatten ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_cell_flatten ();
  }

  END_PROTECTED
}

void
MainWindow::cm_cell_select ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_cell_select ();
  }

  END_PROTECTED
}

void
MainWindow::cm_cell_hide ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_cell_hide ();
  }

  END_PROTECTED
}

void
MainWindow::cm_cell_show ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_cell_show ();
  }

  END_PROTECTED
}

void
MainWindow::cm_cell_show_all ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_cell_show_all ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_select_all ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_select_all ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_new_tab ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_new_tab ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_rename_tab ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_rename_tab ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_remove_tab ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_remove_tab ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_make_invalid ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_make_invalid ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_make_valid ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_make_valid ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_hide_all ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_hide_all ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_hide ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_hide ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_show_only ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_show_only ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_show_all ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_show_all ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_show ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_show ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_rename ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_rename ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_delete ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_delete ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_insert ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_insert ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_group ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_group ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_ungroup ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_ungroup ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_source ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_source ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_sort_by_name ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_sort_by_name ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_sort_by_ild ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_sort_by_ild ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_sort_by_idl ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_sort_by_idl ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_sort_by_ldi ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_sort_by_ldi ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_sort_by_dli ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_sort_by_dli ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_regroup_by_index ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_regroup_by_index ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_regroup_by_datatype ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_regroup_by_datatype ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_regroup_by_layer ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_regroup_by_layer ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_regroup_flatten ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_regroup_flatten ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_expand_all ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_expand_all ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_add_missing ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_add_missing ();
  }

  END_PROTECTED
}

void
MainWindow::cm_lv_remove_unused ()
{
  BEGIN_PROTECTED 

  if (current_view ()) {
    current_view ()->cm_remove_unused ();
  }

  END_PROTECTED
}

void 
MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData () && event->mimeData ()->hasUrls () && event->mimeData ()->urls ().size () >= 1) {
    event->acceptProposedAction ();
  }
}

void 
MainWindow::dropEvent(QDropEvent *event)
{
  BEGIN_PROTECTED

  if (event->mimeData () && event->mimeData ()->hasUrls ()) {

    QList<QUrl> urls = event->mimeData ()->urls ();
    for (QList<QUrl>::const_iterator url = urls.begin (); url != urls.end (); ++url) {

      QString path;
      if (url->scheme () == QString::fromAscii ("file")) {
        path = url->toLocalFile ();

#if defined(__APPLE__)
        //----------------------------------------------------------------------------------------
        // By Kazunari Sekigawa (November 12, 2015)
        //
        // [Issue]
        //   When drag & dropping an GDS2/OASIS file from Finder, an error like below flags on:
        //     Unable to open file: /.file/id=6571367.1783076 (errno=20)
        //   http://klayout.de/forum/comments.php?DiscussionID=733&page=1#Item_0
        //
        //   Such a URL is called "File Reference URL" in OSX and iOS terminology.
        //   This has to be converted back to an ordinary full path.
        //   But due to a bug in Qt-4.8.x, this conversion fails.
        //
        // [Refs for workaround]
        //   https://bugreports.qt.io/browse/QTBUG-40449
        //   Sub: OS X Yosemite drag and drop file QUrl in this format: "file:///.file/id=......"
        //----------------------------------------------------------------------------------------
        QString keystring = QString::fromAscii("/.file/id=");

        if ( path.startsWith(keystring) ) {
          CFStringRef relCFStringRef = CFStringCreateWithCString(
                                          kCFAllocatorDefault,
                                          path.toUtf8().constData(),
                                          kCFStringEncodingUTF8
                                        );
          CFURLRef relCFURL = CFURLCreateWithFileSystemPath(
                                          kCFAllocatorDefault,
                                          relCFStringRef,
                                          kCFURLPOSIXPathStyle,
                                          false // isDirectory
                                        );
          CFErrorRef error  = 0;
          CFURLRef absCFURL = CFURLCreateFilePathURL(
                                          kCFAllocatorDefault,
                                          relCFURL,
                                          &error
                                        );
          if ( !error ) {
            static const CFIndex maxAbsPathCStrBufLen = 4096;
            char absPathCStr[maxAbsPathCStrBufLen];
            if ( CFURLGetFileSystemRepresentation(
                    absCFURL,
                    true, // resolveAgainstBase
                    reinterpret_cast<UInt8 *>( &absPathCStr[0] ),
                    maxAbsPathCStrBufLen
                  )
                ) {
              path = QString::fromUtf8( absPathCStr );
            }
          }
          CFRelease( absCFURL );
          CFRelease( relCFURL );
          CFRelease( relCFStringRef );
        }
#endif

      } else if (url->scheme () == QString::fromAscii ("http") || url->scheme () == QString::fromAscii ("https")) {
        path = url->toString ();
      } else {
        //  other schemes are not supported currently.
        continue;
      }

#if defined(__APPLE__)
      QFileInfo file_info (path); // Use the one resolved above
      QString suffix = file_info.suffix ().toLower ();
#else
      QFileInfo file_info (url->path ()); // Original
      QString suffix = file_info.suffix ().toLower ();
#endif
      if (suffix == QString::fromAscii ("rb") || 
          suffix == QString::fromAscii ("rbm") || 
          suffix == QString::fromAscii ("lym") || 
          suffix == QString::fromAscii ("lydrc") || 
          suffix == QString::fromAscii ("drc")) {

        //  load and run macro
        std::auto_ptr<lay::Macro> macro (new lay::Macro ());
        macro->load_from (tl::to_string (path));
        macro->set_file_path (tl::to_string (path));

        if (macro->is_autorun () || macro->show_in_menu ()) {

          //  install ruby module permanently
          if (QMessageBox::question (this, 
                                     QObject::tr ("Install Macro"), 
                                     tl::to_qstring (tl::sprintf (tl::to_string (QObject::tr ("Install macro '%s' permanently?\n\nPress 'Yes' to install the macro in the application settings folder permanently.")).c_str (), tl::to_string (file_info.fileName ()).c_str ())),
                                     QMessageBox::Yes | QMessageBox::No, 
                                     QMessageBox::No) == QMessageBox::Yes) {

            //  Use the application data folder
            QDir folder (tl::to_qstring (lay::Application::instance ()->appdata_path ()));

            std::string cat = "macros";
            if (! macro->category ().empty ()) {
              cat = macro->category ();
            }

            if (! folder.cd (tl::to_qstring (cat))) {
              throw tl::Exception (tl::to_string (QObject::tr ("Folder '%s' does not exists in installation path '%s' - cannot install")).c_str (), cat, lay::Application::instance ()->appdata_path ());
            }

            QFileInfo target (folder, file_info.fileName ());

            if (! target.exists () || QMessageBox::question (this,
                                                             QObject::tr ("Overwrite Macro"), 
                                                             QObject::tr ("Overwrite existing macro?"),
                                                             QMessageBox::Yes | QMessageBox::No, 
                                                             QMessageBox::No) == QMessageBox::Yes) {

              QFile target_file (target.filePath ());
              if (target.exists () && ! target_file.remove ()) {
                throw tl::Exception (tl::to_string (QObject::tr ("Unable to remove file '%s'")).c_str (), tl::to_string (target.filePath ()).c_str ());
              }

              macro->set_file_path (tl::to_string (target.filePath ()));

              //  run the macro now - if it fails, it is not installed, but the file path is already set to
              //  the target path.
              if (macro->is_autorun ()) {
                macro->run ();
              }

              macro->save ();

              //  refresh macro editor to show new macro plus to install the menus
              mp_macro_editor->refresh ();

            }

          } else {

            if (macro->is_autorun ()) {
              //  If it is not installed, run it now ..
              macro->run ();
            } else if (macro->show_in_menu ()) {
              //  .. or add as temporary macro so it is shown in the menu.
              add_temp_macro (macro.release ());
            }

          }

        } else {
          macro->run ();
        }

      } else if (suffix == QString::fromAscii ("lyp")) {

        load_layer_properties (tl::to_string (path), false /*current view only*/, false /*don't add a default*/);

      } else if (suffix == QString::fromAscii ("lys")) {

        restore_session (tl::to_string (path));

      } else if (suffix == QString::fromAscii ("lyb")) {

        if (current_view ()) {
          BookmarkList bookmarks;
          bookmarks.load (tl::to_string (path));
          current_view ()->bookmarks (bookmarks);
        }

      } else {

        OpenLayoutModeDialog open_mode_dialog (this);
        if (views () == 0 || open_mode_dialog.exec (m_open_mode)) {

          if (m_open_mode == 0) {

            std::string df_list;
            int dirty_layouts = dirty_files (df_list);

            bool can_open = true;
            if (dirty_layouts != 0) {

              QMessageBox mbox (this);
              mbox.setText (tl::to_qstring (tl::to_string (QObject::tr ("The following layouts need saving:\n\n")) + df_list + "\n\nPress 'Close Without Saving' to open the layout and discard changes."));
              mbox.setWindowTitle (QObject::tr ("Save Needed"));
              mbox.setIcon (QMessageBox::Warning);
              QAbstractButton *yes_button = mbox.addButton (QObject::tr ("Close Without Saving"), QMessageBox::YesRole);
              mbox.addButton (QMessageBox::Cancel);

              mbox.exec ();

              can_open = (mbox.clickedButton() == yes_button);

            }

            if (! can_open) {
              return;
            }

          }

          load_layout (tl::to_string (path), m_reader_options, m_initial_technology, m_open_mode);

          add_mru (tl::to_string (path), m_initial_technology);

        }

      }

    }

  }

  END_PROTECTED
}

void 
MainWindow::plugin_registered (lay::PluginDeclaration *cls)
{
  //  store current state in configuration
  save_state_to_config ();

  cls->init_menu (this);

  //  recreate all plugins
  for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
    (*vp)->create_plugins (this);
  }

  //  re-establish the configuration
  config_setup ();
}

void 
MainWindow::plugin_removed (lay::PluginDeclaration *cls)
{
  //  store current state in configuration
  save_state_to_config ();

  cls->remove_menu_items (this);

  //  recreate all plugins except the one that got removed
  for (std::vector <lay::LayoutView *>::iterator vp = mp_views.begin (); vp != mp_views.end (); ++vp) {
    (*vp)->create_plugins (this, cls);
  }

  //  re-establish the configuration
  config_setup ();
}

// ------------------------------------------------------------
//  Implementation of the "help about" dialog

HelpAboutDialog::HelpAboutDialog (QWidget *parent)
  : QDialog (parent)
{
  mp_ui = new Ui::HelpAboutDialog ();
  mp_ui->setupUi (this);

  std::vector<std::string> build_options;
  if (lay::Application::instance ()->ruby_interpreter ().available ()) {
    build_options.push_back (tl::to_string (tr ("Ruby interpreter ")) + lay::Application::instance ()->ruby_interpreter ().version ());
  }
  if (lay::Application::instance ()->python_interpreter ().available ()) {
    build_options.push_back (tl::to_string (tr ("Python interpreter ")) + lay::Application::instance ()->python_interpreter ().version ());
  }
#if defined(HAVE_QTBINDINGS)
  build_options.push_back (tl::to_string (tr ("Qt bindings for scripts")));
#endif
#if defined(HAVE_64BIT_COORD)
  build_options.push_back (tl::to_string (tr ("Wide coordinates (64 bit)")));
#endif

  std::string s;

  s = "<html><body>";

  s += "<h1>";
  s += escape_xml (std::string (lay::Version::name ()) + " " + lay::Version::version ());
  s += "</h1>";

  std::vector<std::string> about_paras = tl::split (lay::Version::about_text (), "\n\n");
  for (std::vector<std::string>::const_iterator p = about_paras.begin (); p != about_paras.end (); ++p) {
    s += std::string ("<p>") + escape_xml (*p) + "</p>";
  }

  if (! build_options.empty ()) {
    s += "<p>";
    s += "<h4>";
    s += escape_xml (tl::to_string (QObject::tr ("Build options:")));
    s += "</h4><ul>";
    for (std::vector<std::string>::const_iterator bo = build_options.begin (); bo != build_options.end (); ++bo) {
      s += "<li>";
      s += escape_xml (*bo);
      s += "</li>";
    }
    s += "</ul>";
  }
  
  s += "</body></html>";

  std::string t = tl::to_string (QObject::tr ("About ")) + lay::Version::name ();

  setWindowTitle (tl::to_qstring (t));

  mp_ui->main->setWordWrap (true);
  mp_ui->main->setText (tl::to_qstring (s));
}

HelpAboutDialog::~HelpAboutDialog ()
{
  delete mp_ui;
  mp_ui = 0;
}

} // namespace lay

