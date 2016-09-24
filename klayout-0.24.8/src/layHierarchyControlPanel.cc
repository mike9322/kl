
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


#include <string>

#include <QtGui/QTreeView>
#include <QtGui/QHeaderView>
#include <QtGui/QComboBox>
#include <QtGui/QResizeEvent>
#include <QtGui/QMenu>
#include <QtGui/QApplication>
#include <QtGui/QDrag>
#include <QtGui/QSplitter>
#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QToolButton>

#include "dbClipboard.h"
#include "dbClipboardData.h"
#include "layHierarchyControlPanel.h"
#include "layCellTreeModel.h"
#include "layLayoutView.h"
#include "layMainWindow.h"
#include "layAbstractMenu.h"
#include "layDialogs.h"
#include "layExceptions.h"
#include "layConfig.h"
#include "tlInternational.h"
#include "tlString.h"
#include "gtf.h"

namespace lay
{

// --------------------------------------------------------------------
//  A helper class the identifies clipboard data 

class CellClipboardData
  : public db::ClipboardData
{
public:
  CellClipboardData () { }
};

// --------------------------------------------------------------------
//  HCPCellTreeWidget implementation

HCPCellTreeWidget::HCPCellTreeWidget (QWidget *parent, const char *name)
  : QTreeView (parent)
{
  //  Don't request focus: this leaves focus on the canvas and the arrow keys functional there
  setFocusPolicy (Qt::NoFocus);
  //  Allow dragging from here to 
  setDragDropMode (QAbstractItemView::DragOnly);

  setObjectName (QString::fromAscii (name));
}

void
HCPCellTreeWidget::startDrag (Qt::DropActions supportedActions)
{
  QModelIndex index = selectionModel ()->currentIndex ();
  if (index.isValid ()) {

    QModelIndexList indexes;
    indexes << index;
    QMimeData *data = model ()->mimeData (indexes);
    if (!data) {
      return;
    }

    QDrag *drag = new QDrag (this);
    drag->setMimeData(data);
    QPixmap px (1, 1);
    px.fill (QColor (0, 0, 0));
    px.createMaskFromColor (QColor (0, 0, 0), Qt::MaskOutColor);
    drag->setPixmap (px);

    Qt::DropAction defaultDropAction = Qt::IgnoreAction;
    if (supportedActions & Qt::CopyAction) {
      defaultDropAction = Qt::CopyAction;
    } 

    drag->exec(supportedActions, defaultDropAction);

  }
}

void 
HCPCellTreeWidget::mouseDoubleClickEvent (QMouseEvent *event)
{
  QModelIndex index (indexAt (event->pos ()));
  if (index.isValid ()) {
    emit cell_double_clicked (index);
  }
}

void 
HCPCellTreeWidget::mousePressEvent (QMouseEvent *event)
{
  if (event->button () == Qt::MidButton) {
    //  eat this event.
  } else {
    QModelIndex index (indexAt (event->pos ()));
    if (index.isValid ()) {
      emit cell_clicked (index);
    }
    QTreeView::mousePressEvent (event);
  }
}

void 
HCPCellTreeWidget::mouseReleaseEvent (QMouseEvent *event)
{
  if (event->button () == Qt::MidButton) {
    QModelIndex index (indexAt (event->pos ()));
    if (index.isValid ()) {
      emit cell_middle_clicked (index);
    }
  } else {
    QTreeView::mouseReleaseEvent (event);
  }
}


// --------------------------------------------------------------------
//  HierarchyControlPanel implementation

const int max_cellviews_in_split_mode = 5;

void 
HierarchyControlPanel::init_menu (lay::AbstractMenu &menu)
{
  MenuLayoutEntry sorting_menu [] = {
    MenuLayoutEntry ("by_name",                     tl::to_string (QObject::tr ("By Name")),                std::make_pair (cfg_cell_list_sorting, "?by-name")),
    MenuLayoutEntry ("by_area",                     tl::to_string (QObject::tr ("By Area - Small To Large")),  std::make_pair (cfg_cell_list_sorting, "?by-area")),
    MenuLayoutEntry ("by_area",                     tl::to_string (QObject::tr ("By Area - Large To Small")),  std::make_pair (cfg_cell_list_sorting, "?by-area-reverse")),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry context_menu [] = {
    MenuLayoutEntry ("flat_mode",                   tl::to_string (QObject::tr ("Flat Cell List")),         std::make_pair (cfg_flat_cell_list, "?")),
    MenuLayoutEntry ("split_mode",                  tl::to_string (QObject::tr ("Split Mode")),             std::make_pair (cfg_split_cell_list, "?")),
    MenuLayoutEntry ("sorting",                     tl::to_string (QObject::tr ("Sorting")),                sorting_menu),
    MenuLayoutEntry::separator ("operations_group"),
    MenuLayoutEntry ("new_cell:edit:edit_mode",     tl::to_string (QObject::tr ("New Cell")),               SLOT (cm_new_cell ())),
    MenuLayoutEntry ("delete_cell:edit:edit_mode",  tl::to_string (QObject::tr ("Delete Cell")),            SLOT (cm_cell_delete ())),
    MenuLayoutEntry ("rename_cell:edit:edit_mode",  tl::to_string (QObject::tr ("Rename Cell")),            SLOT (cm_cell_rename ())),
    MenuLayoutEntry ("replace_cell:edit:edit_mode", tl::to_string (QObject::tr ("Replace Cell")),           SLOT (cm_cell_replace ())),
    MenuLayoutEntry ("flatten_cell:edit:edit_mode", tl::to_string (QObject::tr ("Flatten Cell")),           SLOT (cm_cell_flatten ())),
    MenuLayoutEntry ("cell_user_properties",        tl::to_string (QObject::tr ("User Properties")),        SLOT (cm_cell_user_properties ())),
    MenuLayoutEntry::separator ("clipboard_group:edit_mode"),
    MenuLayoutEntry ("copy:edit_mode",              tl::to_string (QObject::tr ("Copy")),                   SLOT (cm_cell_copy ())),
    MenuLayoutEntry ("cut:edit_mode",               tl::to_string (QObject::tr ("Cut")),                    SLOT (cm_cell_cut ())),
    MenuLayoutEntry ("paste:edit_mode",             tl::to_string (QObject::tr ("Paste")),                  SLOT (cm_cell_paste ())),
    MenuLayoutEntry::separator ("select_group"),
    MenuLayoutEntry ("show_as_top",                 tl::to_string (QObject::tr ("Show As New Top")),        SLOT (cm_cell_select ())),
    MenuLayoutEntry::separator ("visibility_group"),
    MenuLayoutEntry ("hide_cell",                   tl::to_string (QObject::tr ("Hide")),                   SLOT (cm_cell_hide ())),
    MenuLayoutEntry ("show_cell",                   tl::to_string (QObject::tr ("Show")),                   SLOT (cm_cell_show ())),
    MenuLayoutEntry ("show_all",                    tl::to_string (QObject::tr ("Show All")),               SLOT (cm_cell_show_all ())),
    MenuLayoutEntry::separator ("utils_group"),
    MenuLayoutEntry ("open_current",                tl::to_string (QObject::tr ("Where Am I?")),            SLOT (cm_open_current_cell ())),
    MenuLayoutEntry::separator ("file_group"),
    MenuLayoutEntry ("save_cell_as:hide_vo",        tl::to_string (QObject::tr ("Save Selected Cells As")), SLOT (cm_save_current_cell_as ())),
    MenuLayoutEntry::last ()
  };

  MenuLayoutEntry main_menu [] = {
    MenuLayoutEntry ("@hcp_context_menu", "", context_menu),
    MenuLayoutEntry::last ()
  };

  menu.init (main_menu);
}

HierarchyControlPanel::HierarchyControlPanel (lay::LayoutView *view, QWidget *parent, const char *name)
  : QFrame (parent), 
    m_enable_cb (true), 
    mp_view (view),
    m_visibility_needs_update (true),
    m_active_index (0),
    m_flat (false),
    m_split_mode (false),
    m_sorting (CellTreeModel::ByName),
    m_do_update_content_dm (this, &HierarchyControlPanel::do_update_content),
    m_do_full_update_content_dm (this, &HierarchyControlPanel::do_full_update_content)
{
  setObjectName (QString::fromAscii (name));

  QVBoxLayout *ly = new QVBoxLayout (this);
  ly->setSpacing (0);
  ly->setContentsMargins (0, 0, 0, 0);

  mp_selector = new QComboBox (this);
  mp_selector->setObjectName (QString::fromAscii ("cellview_selection"));
  ly->addWidget (mp_selector);

  mp_splitter = new QSplitter (Qt::Vertical, this);
  ly->addWidget (mp_splitter);

  connect (mp_selector, SIGNAL (activated (int)), this, SLOT (selection_changed (int)));

  QSizePolicy sp (QSizePolicy::Minimum, QSizePolicy::Preferred);
  sp.setHorizontalStretch (0);
  sp.setVerticalStretch (0);
  setSizePolicy (sp);

  mp_view->add_cellview_list_observer (*this);
  mp_view->add_hier_changed_observer (*this);

  do_update_content ();
}

HierarchyControlPanel::~HierarchyControlPanel ()
{
  //  .. nothing yet ..
}

QSize
HierarchyControlPanel::sizeHint () const
{
  int w = 120; // TODO: better(?): mp_cell_list->sizeHint ().width ();
  return QSize (w, 0);
}

bool 
HierarchyControlPanel::event (QEvent *e)
{
  if (e->type () == QEvent::MaxUser) {
    //  GTF probe event
    e->accept ();
    return true;
  } else {
    return QFrame::event (e);
  }
}

void 
HierarchyControlPanel::context_menu (const QPoint &p)
{
  QTreeView *cell_list = dynamic_cast<QTreeView *> (sender ());
  if (cell_list) {
    set_active_celltree_from_sender ();
    QMenu *ctx_menu = lay::MainWindow::instance ()->menu ().detached_menu ("hcp_context_menu");
    ctx_menu->exec (cell_list->mapToGlobal (p));
  }
}

void
HierarchyControlPanel::set_sorting (CellTreeModel::Sorting sorting)
{
  if (sorting != m_sorting) {

    m_sorting = sorting;

    for (size_t i = 0; i < mp_cell_lists.size (); ++i) {
      CellTreeModel *model = dynamic_cast <CellTreeModel *> (mp_cell_lists [i]->model ());
      if (model) {
        model->set_sorting (m_sorting);
      }
    }

    m_needs_update.clear ();
    m_do_update_content_dm ();

  }
}

void
HierarchyControlPanel::set_split_mode (bool f)
{
  if (f != m_split_mode) {
    m_split_mode = f;
    m_do_update_content_dm ();
  }
}

void
HierarchyControlPanel::clear_all ()
{
  m_cellviews.clear ();
  m_needs_update.clear ();
  m_force_close.clear ();

  for (size_t i = 0; i < mp_cell_list_frames.size (); ++i) {
    delete mp_cell_list_frames [i];
  }
  mp_cell_list_frames.clear ();
  mp_cell_list_headers.clear ();
  mp_cell_lists.clear ();
}

void
HierarchyControlPanel::set_flat (bool f)
{
  if (f != m_flat) {

    m_flat = f;

    //  do a complete rebuild
    clear_all ();
    m_do_update_content_dm ();

  }
}

void
HierarchyControlPanel::cm_cell_select ()
{
  cell_path_type path;
  current_cell (active (), path);
  emit cell_selected (path, active ());
}

void 
HierarchyControlPanel::middle_clicked (const QModelIndex &index)
{
  BEGIN_PROTECTED
  if (index.isValid ()) {
    set_active_celltree_from_sender ();
    cell_path_type path;
    path_from_index (index, m_active_index, path);
    emit cell_selected (path, active ());
  }
  END_PROTECTED
}

void
HierarchyControlPanel::path_from_index (const QModelIndex &index, int cv_index, cell_path_type &path) const
{
  //  build the path to the cell given by the index
  path.clear ();

  if (index.isValid ()) {

    CellTreeItem *item = (CellTreeItem *) index.internalPointer ();

    if (m_flat && cv_index >= 0 && cv_index < int (m_cellviews.size ()) && item) {

      //  construct a path in the flat case
      lay::CellView cv (m_cellviews [cv_index]);
      cv.set_cell (item->cell_index ());
      path = cv.unspecific_path ();

    } else {

      while (item) {
        path.push_back (item->cell_index ());
        item = item->parent ();
      }

      if (! path.empty ()) {
        std::reverse (path.begin (), path.end ());
      }

    }

  }
}

void
HierarchyControlPanel::set_active_celltree_from_sender ()
{
  for (int i = 0; i < int (mp_cell_lists.size ()); ++i) {
    if (mp_cell_lists [i] == sender ()) {
      select_active (i);
      return;
    }
    if (mp_cell_list_headers [i] == sender ()) {
      select_active (i);
      return;
    }
  }
}

void 
HierarchyControlPanel::header_clicked ()
{
  QToolButton *cb = dynamic_cast<QToolButton *> (sender ());
  if (cb) {
    cb->setChecked (true);
    set_active_celltree_from_sender ();
  }
}

void 
HierarchyControlPanel::clicked (const QModelIndex &index)
{
  set_active_celltree_from_sender ();
}

void 
HierarchyControlPanel::double_clicked (const QModelIndex &index)
{
  BEGIN_PROTECTED
  if (index.isValid ()) {
    set_active_celltree_from_sender ();
    mp_view->manager ()->transaction (tl::to_string (QObject::tr ("Show or hide cell"))); 
    CellTreeItem *item = (CellTreeItem *) index.internalPointer ();
    if (mp_view->is_cell_hidden (item->cell_index (), m_active_index)) {
      mp_view->show_cell (item->cell_index (), m_active_index);
    } else {
      mp_view->hide_cell (item->cell_index (), m_active_index);
    }
    mp_view->manager ()->commit ();
  }
  END_PROTECTED
}

void 
HierarchyControlPanel::set_current_cell (int cv_index, const cell_path_type &path)
{
  if (cv_index < 0 || cv_index >= int (mp_cell_lists.size ())) {
    return;
  }

  QModelIndex index = index_from_path (path, cv_index);
  if (index.isValid ()) {
    mp_cell_lists [cv_index]->scrollTo (index);
    mp_cell_lists [cv_index]->clearSelection ();
    mp_cell_lists [cv_index]->setCurrentIndex (index);
  }
}

void
HierarchyControlPanel::selected_cells (int cv_index, std::vector<HierarchyControlPanel::cell_path_type> &paths) const
{
  if (cv_index >= 0 && cv_index < int (mp_cell_lists.size ())) {
    QModelIndexList sel = mp_cell_lists [cv_index]->selectionModel ()->selectedIndexes ();
    for (QModelIndexList::const_iterator s = sel.begin (); s != sel.end (); ++s) {
      paths.push_back (HierarchyControlPanel::cell_path_type ());
      path_from_index (*s, cv_index, paths.back ());
    }
  }
}

void
HierarchyControlPanel::current_cell (int cv_index, HierarchyControlPanel::cell_path_type &path) const
{
  if (cv_index >= 0 && cv_index < int (mp_cell_lists.size ())) {
    path_from_index (mp_cell_lists [cv_index]->currentIndex (), cv_index, path);
  }
}

void
HierarchyControlPanel::set_background_color (QColor c)
{
  m_background_color = c;
  for (std::vector <QTreeView *>::const_iterator f = mp_cell_lists.begin (); f != mp_cell_lists.end (); ++f) {
    QPalette pl ((*f)->palette ());
    pl.setColor (QPalette::Base, c);
    (*f)->setPalette (pl);
  }
}

void
HierarchyControlPanel::set_text_color (QColor c)
{
  m_text_color = c;
  for (std::vector <QTreeView *>::const_iterator f = mp_cell_lists.begin (); f != mp_cell_lists.end (); ++f) {
    QPalette pl ((*f)->palette ());
    pl.setColor (QPalette::Text, c);
    (*f)->setPalette (pl);
  }
}

void
HierarchyControlPanel::do_full_update_content ()
{
  size_t i = 0; 
  for (std::vector <lay::CellView>::const_iterator cv = m_cellviews.begin (); cv != m_cellviews.end (); ++cv, ++i) {
    if (m_needs_update.size () > i) {
      m_needs_update [i] = true; 
    }
    if (m_force_close.size () > i) {
      m_force_close [i] = true; 
    }
  }

  do_update_content ();
}

void
HierarchyControlPanel::signal_observed ()
{
  m_do_full_update_content_dm ();
}

void 
HierarchyControlPanel::select_active (int cellview_index)
{
  if (cellview_index != m_active_index) {
    mp_selector->setCurrentIndex (cellview_index);
    selection_changed (cellview_index);
  }
}

void
HierarchyControlPanel::selection_changed (int index)
{
  if (index != m_active_index) {

    m_active_index = index;

    bool split_mode = m_split_mode;
    //  for more than max_cellviews_in_split_mode cellviews, switch to overlay mode
    if (int (m_cellviews.size ()) > max_cellviews_in_split_mode) {
      split_mode = false;
    }

    int i = 0;
    for (std::vector <QFrame *>::const_iterator f = mp_cell_list_frames.begin (); f != mp_cell_list_frames.end (); ++f, ++i) {
      (*f)->setVisible (i == index || split_mode);
    }

    i = 0;
    for (std::vector <QToolButton *>::const_iterator f = mp_cell_list_headers.begin (); f != mp_cell_list_headers.end (); ++f, ++i) {
      (*f)->setChecked (i == index);
    }

    emit active_cellview_changed (index);

  }
}

QModelIndex 
HierarchyControlPanel::index_from_path (const cell_path_type &path, int cv_index)
{
  if (cv_index >= 0 && cv_index < int (mp_cell_lists.size ()) && ! path.empty ()) {

    CellTreeModel *model = dynamic_cast <CellTreeModel *> (mp_cell_lists [cv_index]->model ());
    if (! model) {
      return QModelIndex ();
    }

    if (m_flat) {

      //  TODO: linear search might not be effective enough ..
      for (int c = 0; c < model->toplevel_items (); ++c) {
        CellTreeItem *item = model->toplevel_item (c);
        if (item->cell_index () == path.back ()) {
          return model->model_index (item);
        }
      }

    } else {

      for (int c = 0; c < model->toplevel_items (); ++c) {
        CellTreeItem *item = model->toplevel_item (c);
        if (item->cell_index () == path.front ()) {
          item = find_child_item (path.begin () + 1, path.end (), item);
          if (item) {
            return model->model_index (item);
          }
        }
      } 

    }

  }

  return QModelIndex ();
}

CellTreeItem *
HierarchyControlPanel::find_child_item (cell_path_type::const_iterator start, cell_path_type::const_iterator end, CellTreeItem *p)
{
  if (start == end) {
    return p;
  } else {

    for (int n = 0; n < p->children (); ++n) {
      CellTreeItem *item = p->child (n);
      if (item && item->cell_index () == *start) {
        return find_child_item (start + 1, end, item);
      }
    }

    //  not found
    return 0;

  }
}

std::string 
HierarchyControlPanel::display_string (int n) const
{
  return m_cellviews [n]->name () + " (@" + tl::to_string (n + 1) + ")";
}

void
HierarchyControlPanel::do_update_content (int cv_index)
{
  unsigned int imin = (cv_index < 0 ? 0 : (unsigned int) cv_index);
  unsigned int imax = (cv_index < 0 ? std::numeric_limits <unsigned int>::max () : (unsigned int) cv_index);

  for (unsigned int i = imin; i < mp_view->cellviews () && i <= imax; ++i) {
    if (i >= m_force_close.size ()) {
      m_force_close.push_back (true);
    }
    if (i >= m_needs_update.size ()) {
      m_needs_update.push_back (true);
    }
    if (i >= m_cellviews.size ()) {
      m_force_close [i] = true;
      m_needs_update [i] = true;
    }
  }

  unsigned int n = std::min ((unsigned int) m_cellviews.size (), mp_view->cellviews ());
  for (unsigned int i = imin; i < n && i <= imax; ++i) {

    if (&m_cellviews [i]->layout () != &mp_view->cellview (i)->layout ()) {
      m_needs_update [i] = true;
      m_force_close [i] = true;
    } else if (m_cellviews [i].combined_unspecific_path () != mp_view->cellview (i).combined_unspecific_path ()) {
      m_needs_update [i] = true;
    }

    if (m_needs_update [i]) {
      mp_cell_lists [i]->doItemsLayout (); //  this schedules a redraw 
    }

    m_cellviews [i] = mp_view->cellview (i);

  }

  if (m_cellviews.size () < mp_view->cellviews ()) {
    for (unsigned int i = n; i < mp_view->cellviews (); ++i) {
      m_cellviews.push_back (mp_view->cellview (i));
    }
  } else if (m_cellviews.size () > mp_view->cellviews ()) {
    m_cellviews.erase (m_cellviews.begin () + mp_view->cellviews (), m_cellviews.end ()); 
  }

  bool split_mode = m_split_mode;
  //  for more than max_cellviews_in_split_mode cellviews, switch to overlay mode
  if (int (m_cellviews.size ()) > max_cellviews_in_split_mode) {
    split_mode = false;
  }

  while (mp_cell_lists.size () < m_cellviews.size ()) {

    QPalette pl;

    int cv_index = int (mp_cell_lists.size ());

    QFrame *cl_frame = new QFrame (this);
    cl_frame->setFrameShape (QFrame::NoFrame);
    QVBoxLayout *cl_ly = new QVBoxLayout (cl_frame);
    cl_ly->setSpacing (0);
    cl_ly->setContentsMargins (0, 0, 0, 0);

    QToolButton *header = new QToolButton (cl_frame);
    connect (header, SIGNAL (clicked ()), this, SLOT (header_clicked ()));
    header->setText (tl::to_qstring (display_string (cv_index)));
    header->setFocusPolicy (Qt::NoFocus);
    header->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Preferred);
    header->setCheckable (true);
    header->setAutoRaise (true);
    header->setAutoFillBackground (true);
    header->setVisible (split_mode);
    cl_ly->addWidget (header);

    HCPCellTreeWidget *cell_list = new HCPCellTreeWidget (cl_frame, "tree");
    cl_ly->addWidget (cell_list);
    cell_list->setModel (new CellTreeModel (cell_list, mp_view, cv_index, m_flat ? CellTreeModel::Flat : 0, 0, m_sorting));
    cell_list->setUniformRowHeights (true);

    pl = cell_list->palette ();
    if (m_text_color.isValid ()) {
      pl.setColor (QPalette::Text, m_text_color);
    }
    if (m_background_color.isValid ()) {
      pl.setColor (QPalette::Base, m_background_color);
    }
    cell_list->setPalette (pl);

    cell_list->header ()->hide ();
    cell_list->setSelectionMode (QTreeView::ExtendedSelection);
    cell_list->setRootIsDecorated (true);
    cell_list->setIndentation (14);
    cell_list->setContextMenuPolicy (Qt::CustomContextMenu);

    connect (cell_list, SIGNAL (customContextMenuRequested (const QPoint &)), this, SLOT (context_menu (const QPoint &)));
    connect (cell_list, SIGNAL (cell_clicked (const QModelIndex &)), this, SLOT (clicked (const QModelIndex &)));
    connect (cell_list, SIGNAL (cell_double_clicked (const QModelIndex &)), this, SLOT (double_clicked (const QModelIndex &)));
    connect (cell_list, SIGNAL (cell_middle_clicked (const QModelIndex &)), this, SLOT (middle_clicked (const QModelIndex &)));

    mp_cell_lists.push_back (cell_list);
    mp_cell_list_frames.push_back (cl_frame);
    mp_cell_list_headers.push_back (header);
    
    mp_splitter->addWidget (cl_frame);

  }

  while (mp_cell_lists.size () > m_cellviews.size ()) {
    delete mp_cell_list_frames.back ();
    mp_cell_list_frames.pop_back ();
    mp_cell_list_headers.pop_back ();
    mp_cell_lists.pop_back ();
  } 

  for (unsigned int i = imin; i < m_cellviews.size () && i < (unsigned int) mp_selector->count () && i <= imax; ++i) {
    mp_selector->setItemText (i, tl::to_qstring (display_string (i))); 
  }
  while (mp_selector->count () < int (m_cellviews.size ())) {
    mp_selector->addItem (tl::to_qstring (display_string (mp_selector->count ())));
  }
  while (mp_selector->count () > int (m_cellviews.size ())) {
    mp_selector->removeItem (mp_selector->count () - 1);
  } 

  if (m_active_index >= int (m_cellviews.size ())) {
    m_active_index = int (m_cellviews.size ()) - 1;
  } else if (m_active_index < 0 && ! m_cellviews.empty ()) {
    m_active_index = 0;
  }
  mp_selector->setCurrentIndex (m_active_index);
  mp_selector->setVisible (mp_cell_lists.size () > 1 && ! split_mode);

  for (unsigned int i = imin; i < m_cellviews.size () && i <= imax; ++i) {
    
    if (m_needs_update [i]) {

      mp_cell_list_headers [i]->setText (tl::to_qstring (display_string (i)));

      //  draw the cells in the level of the current cell,
      //  add an "above" entry if there is a level above.
      //  highlight the current entry. If the index is 
      //  invalid, just clear the list.

      if (m_force_close [i]) {

        m_force_close [i] = false;

        mp_cell_lists [i]->collapse (mp_cell_lists [i]->rootIndex ());
        
        CellTreeModel *old_model = dynamic_cast <CellTreeModel *> (mp_cell_lists [i]->model ());
        mp_cell_lists [i]->setModel (new CellTreeModel (mp_cell_lists [i], mp_view, i, m_flat ? CellTreeModel::Flat : 0, 0, m_sorting));
        if (old_model) {
          delete old_model;
        }

      }

      //  enable root decoration
      mp_cell_lists [i]->setRootIsDecorated (! m_flat);

      //  locate the item and make selected
      mp_cell_lists [i]->clearSelection ();

      QModelIndex index = index_from_path (m_cellviews [i].combined_unspecific_path (), i);
      if (index.isValid ()) {
        mp_cell_lists [i]->scrollTo (index);
        mp_cell_lists [i]->setCurrentIndex (index);
      }

      m_needs_update [i] = false;

    }

    mp_cell_list_headers [i]->setVisible (split_mode && m_cellviews.size () > 1);
    mp_cell_list_headers [i]->setChecked (int (i) == m_active_index);

    mp_cell_list_frames [i]->setVisible (int (i) == m_active_index || split_mode);

  }
}

CellTreeItem *
HierarchyControlPanel::current_item () const
{
  if (m_active_index < 0 || m_active_index >= int (mp_cell_lists.size ())) {
    return 0;
  }
  if (mp_cell_lists [m_active_index]->currentIndex ().isValid ()) {
    return (CellTreeItem *) mp_cell_lists [m_active_index]->currentIndex ().internalPointer ();
  } else {
    return 0;
  }
}

bool 
HierarchyControlPanel::has_focus () const
{
  return m_active_index >= 0 && m_active_index < int (mp_cell_lists.size ()) && mp_cell_lists [m_active_index]->hasFocus ();
}

void
HierarchyControlPanel::cut () 
{
  if (m_active_index < 0 || m_active_index >= int (mp_cell_lists.size ())) {
    return;
  }

  std::vector<cell_path_type> paths;
  selected_cells (m_active_index, paths);

  if (paths.empty ()) {
    return;
  }

  //  first copy
  bool needs_to_ask = false;

  db::Layout &layout = m_cellviews [m_active_index]->layout ();

  //  collect the called cells of the cells to copy, so we don't copy a cell twice

  db::Clipboard::instance ().clear ();

  //  don't copy the cells which would be copied anyway
  std::set<db::cell_index_type> called_cells;
  for (std::vector<cell_path_type>::const_iterator p = paths.begin (); p != paths.end (); ++p) {
    if (! p->empty ()) {
      const db::Cell &cell = layout.cell (p->back ());
      cell.collect_called_cells (called_cells);
      if (cell.cell_instances () > 0) {
        needs_to_ask = true;
      }
    }
  }

  int cut_mode = 1; // 0: shallow, 1: deep
  if (needs_to_ask) {
    lay::CopyCellModeDialog mode_dialog (this);
    if (! mode_dialog.exec (cut_mode)) {
      return;
    }
  }

  for (std::vector<cell_path_type>::const_iterator p = paths.begin (); p != paths.end (); ++p) {
    if (! p->empty () && called_cells.find (p->back ()) == called_cells.end ()) {
      db::ClipboardValue<lay::CellClipboardData> *cd = new db::ClipboardValue<lay::CellClipboardData> ();
      cd->get ().add (layout, layout.cell (p->back ()), cut_mode == 1 ? 1 /*with subcells*/ : 2 /*first level, then without subcells*/);
      db::Clipboard::instance () += cd;
    }
  }

  //  then do a (shallow or deep) delete

  //  remember the current path
  cell_path_type cell_path (mp_view->cellview (m_active_index).combined_unspecific_path ());

  mp_view->clear_selection ();

  std::set<db::cell_index_type> cells_to_delete;
  for (std::vector<cell_path_type>::const_iterator p = paths.begin (); p != paths.end (); ++p) {
    if (! p->empty () && layout.is_valid_cell_index (p->back ())) {
      cells_to_delete.insert (p->back ());
    }
  }

  mp_view->manager ()->transaction (tl::to_string (QObject::tr ("Cut Cells")));
  if (cut_mode == 1) {
    layout.prune_cells (cells_to_delete);
  } else {
    layout.delete_cells (cells_to_delete);
  }
  layout.cleanup ();
  mp_view->manager ()->commit ();

  //  If one of the cells in the path was deleted, establish a valid path

  bool needs_update = false;
  for (size_t i = cell_path.size (); i > 0; ) {
    --i;
    if (! layout.is_valid_cell_index (cell_path [i])) {
      cell_path.erase (cell_path.begin () + i, cell_path.end ());
      needs_update = true;
    }
  }

  if (needs_update) {
    mp_view->select_cell (cell_path, m_active_index);
  }
}

bool
HierarchyControlPanel::has_selection ()
{
  return (current_item () != 0);
}

void
HierarchyControlPanel::copy () 
{
  if (m_active_index < 0 || m_active_index >= int (mp_cell_lists.size ())) {
    return;
  }

  std::vector<cell_path_type> paths;
  selected_cells (m_active_index, paths);

  if (paths.empty ()) {
    return;
  }

  bool needs_to_ask = false;

  db::Layout &layout = m_cellviews [m_active_index]->layout ();

  //  collect the called cells of the cells to copy, so we don't copy a cell twice

  db::Clipboard::instance ().clear ();

  //  don't copy the cells which would be copied anyway
  std::set<db::cell_index_type> called_cells;
  for (std::vector<cell_path_type>::const_iterator p = paths.begin (); p != paths.end (); ++p) {
    if (! p->empty ()) {
      const db::Cell &cell = layout.cell (p->back ());
      cell.collect_called_cells (called_cells);
      if (cell.cell_instances () > 0) {
        needs_to_ask = true;
      }
    }
  }

  int copy_mode = 1; // 0: shallow, 1: deep
  if (needs_to_ask) {
    lay::CopyCellModeDialog mode_dialog (this);
    if (! mode_dialog.exec (copy_mode)) {
      return;
    }
  }

  for (std::vector<cell_path_type>::const_iterator p = paths.begin (); p != paths.end (); ++p) {
    if (! p->empty () && called_cells.find (p->back ()) == called_cells.end ()) {
      db::ClipboardValue<lay::CellClipboardData> *cd = new db::ClipboardValue<lay::CellClipboardData> ();
      cd->get ().add (layout, layout.cell (p->back ()), copy_mode == 1 ? 1 /*with subcells*/ : 2 /*first level, then without subcells*/);
      db::Clipboard::instance () += cd;
    }
  }
}

void
HierarchyControlPanel::paste () 
{
  if (m_active_index < 0 || m_active_index >= int (mp_cell_lists.size ())) {
    return;
  }

  db::Layout &layout = m_cellviews [m_active_index]->layout ();

  std::vector<unsigned int> new_layers;

  //  paste the content into the active cellview.
  std::vector <db::cell_index_type> new_tops;
  for (db::Clipboard::iterator c = db::Clipboard::instance ().begin (); c != db::Clipboard::instance ().end (); ++c) {
    const db::ClipboardValue<lay::CellClipboardData> *value = dynamic_cast<const db::ClipboardValue<lay::CellClipboardData> *> (*c);
    if (value) {
      std::vector<unsigned int> nl = value->get ().insert (layout, 0, &new_tops);
      new_layers.insert (new_layers.end (), nl.begin (), nl.end ());
    }
  }

  //  Add new layers to the view if required.
  if (! new_layers.empty ()) {
    mp_view->add_new_layers (new_layers, m_active_index);
    mp_view->update_content ();
  }

  //  select the first new top cell
  if (! new_tops.empty ()) {
    //  TODO: this does not work properly: since we are inside a transaction, bboxes are not updated
    //  correctly. Thus, the cell_fit does not work properly.
    mp_view->select_cell_fit (new_tops [0], m_active_index);
  }
}

} // namespace lay 
