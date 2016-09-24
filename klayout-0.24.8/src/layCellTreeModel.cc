
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


#include "layCellTreeModel.h"
#include "layLayoutView.h"
#include "tlGlobPattern.h"
#include "dbPCellHeader.h"

#include <QtGui/QTreeView>
#include <QtCore/QMimeData>

#include <string.h>

#include <algorithm>

namespace lay {

// --------------------------------------------------------------------
//  A compare functor for the cell tree items by area

struct cmp_cell_tree_items_f 
{
  cmp_cell_tree_items_f (CellTreeModel::Sorting s)
    : m_sorting (s)
  { }

  bool operator() (const CellTreeItem *a, const CellTreeItem *b)
  {
    if (m_sorting == CellTreeModel::ByArea) {
      if (a->by_area_equal_than (b)) {
        return a->by_name_less_than (b);
      } else {
        return a->by_area_less_than (b);
      }
    } else if (m_sorting == CellTreeModel::ByAreaReverse) {
      if (a->by_area_equal_than (b)) {
        return a->by_name_less_than (b);
      } else {
        return b->by_area_less_than (a);
      }
    } else {
      return a->by_name_less_than (b);
    }
  }

private:
  CellTreeModel::Sorting m_sorting;
};

// --------------------------------------------------------------------
//  A compare functor for the cell tree items vs. name

struct cmp_cell_tree_item_vs_name_f 
{
  bool operator() (const CellTreeItem *a, const char *name)
  {
    return a->name_less_than (name);
  }
};

// --------------------------------------------------------------------
//  CellTreeItem implementation

CellTreeItem::CellTreeItem (const db::Layout *layout, CellTreeItem *parent, bool is_pcell, size_t cell_index, bool flat, CellTreeModel::Sorting s)
  : mp_layout (layout), mp_parent (parent), m_sorting (s), m_is_pcell (is_pcell), m_index (0), m_children (), m_cell_index (cell_index)
{
  if (! flat && ! is_pcell) {
    m_child_count = mp_layout->cell (m_cell_index).child_cells ();
  } else {
    m_child_count = 0;
  }
}

CellTreeItem::~CellTreeItem ()
{
  for (std::vector<CellTreeItem *>::iterator c = m_children.begin (); c != m_children.end (); ++c) {
    delete *c;
  }
  m_children.clear ();
}

std::string 
CellTreeItem::display_text () const
{
  if (m_is_pcell) {
    return name ();
  } else if (mp_layout->is_valid_cell_index (m_cell_index)) {
    return mp_layout->cell (m_cell_index).get_display_name ();
  } else {
    return std::string ();
  }
}

int 
CellTreeItem::children () const
{
  return m_child_count;
}

CellTreeItem *
CellTreeItem::child (int index) 
{
  if (! m_is_pcell && int (m_children.size ()) <= index) {

    //  create a list of child sub-item

    const db::Cell *cell = & mp_layout->cell (m_cell_index);

    m_children.reserve (m_child_count);

    for (db::Cell::child_cell_iterator child = cell->begin_child_cells (); ! child.at_end (); ++child) {
      CellTreeItem *child_item = new CellTreeItem (mp_layout, this, false, *child, false, m_sorting);
      m_children.push_back (child_item);
    }

    std::sort (m_children.begin (), m_children.end (), cmp_cell_tree_items_f (m_sorting));

    for (size_t i = 0; i < m_children.size (); ++i) {
      m_children [i]->set_index (i);
    }

  }

  return m_children [index];
}

db::cell_index_type
CellTreeItem::cell_index () const
{
  return m_cell_index;
}

CellTreeItem *
CellTreeItem::parent () const
{
  return mp_parent;
}

const char *
CellTreeItem::name () const
{
  if (! m_is_pcell) {
    return mp_layout->cell_name (m_cell_index);
  } else {
    return mp_layout->pcell_header (m_cell_index)->get_name ().c_str ();
  }
}

bool 
CellTreeItem::by_name_less_than (const CellTreeItem *b) const
{
#if 0 // with name:
  return strcmp (name (), b->name ()) < 0;
#else // with display text:
  return display_text () < b->display_text ();
#endif
}

bool 
CellTreeItem::name_less_than (const char *n) const
{
#if 0 // with name:
  return strcmp (name (), n) < 0;
#else // with display text:
  return display_text () < n;
#endif
}

bool 
CellTreeItem::name_equals (const char *n) const
{
#if 0 // with name:
  return strcmp (name (), n) == 0;
#else // with display text:
  return display_text () == n;
#endif
}

bool 
CellTreeItem::name_matches (const tl::GlobPattern &p) const
{
#if 0 // with name:
  return p.match (name ());
#else // with display text:
  return p.match (display_text ());
#endif
}

bool 
CellTreeItem::by_area_less_than (const CellTreeItem *b) const
{
  if (m_is_pcell || b->is_pcell ()) {
    return m_is_pcell > b->is_pcell ();
  }
  // Hint: since mp_layout == b.mp_layout, not conversion to um^2 is required because of different DBU
  return mp_layout->cell (m_cell_index).bbox ().area () < b->mp_layout->cell (b->m_cell_index).bbox ().area ();
}

bool
CellTreeItem::by_area_equal_than (const CellTreeItem *b) const
{
  if (m_is_pcell != b->is_pcell ()) {
    return false;
  }
  // Hint: since mp_layout == b.mp_layout, not conversion to um^2 is required because of different DBU
  return mp_layout->cell (m_cell_index).bbox ().area () == b->mp_layout->cell (b->m_cell_index).bbox ().area ();
}

// --------------------------------------------------------------------
//  CellTreeModel implementation
//  Hint: it may happen that the cell tree model gets engaged while the layout is not
//  valid ("under construction"). In this case, the model will return defaults or void
//  objects.

CellTreeModel::CellTreeModel (QWidget *parent, lay::LayoutView *view, int cv_index, unsigned int flags, const db::Cell *base, Sorting sorting)
  : QAbstractItemModel (parent), 
    m_flags (flags),
    m_sorting (sorting),
    mp_parent (parent), 
    mp_view (view), 
    m_cv_index (cv_index),
    mp_base (base)
{
  mp_view->add_cell_visibility_observer (*this);
  mp_view->add_cellview_observer (*this);

  m_flat = ((flags & Flat) != 0) && ((flags & TopCells) == 0);
  m_pad = ((flags & NoPadding) == 0);

  mp_layout = & view->cellview (cv_index)->layout ();
  tl_assert (! mp_layout->under_construction () && ! (mp_layout->manager () && mp_layout->manager ()->transacting ()));

  build_top_level ();

  m_current_index = m_selected_indexes.begin ();
}

CellTreeModel::CellTreeModel (QWidget *parent, db::Layout *layout, unsigned int flags, const db::Cell *base, Sorting sorting)
  : QAbstractItemModel (parent), 
    m_flags (flags),
    m_sorting (sorting),
    mp_parent (parent), 
    mp_view (0), 
    m_cv_index (-1),
    mp_base (base)
{
  m_flat = ((flags & Flat) != 0) && ((flags & TopCells) == 0);
  m_pad = ((flags & NoPadding) == 0);

  mp_layout = layout;
  tl_assert (! mp_layout->under_construction () && ! (mp_layout->manager () && mp_layout->manager ()->transacting ()));

  build_top_level ();

  m_current_index = m_selected_indexes.begin ();
}

CellTreeModel::~CellTreeModel ()
{
  clear_top_level ();
  if (mp_view) {
    mp_view->remove_cell_visibility_observer (*this);
  }
}

void 
CellTreeModel::set_sorting (Sorting s)
{
  if (s != m_sorting) {
    m_sorting = s;
    clear_top_level ();
    build_top_level ();
    //  Important: reset here, since otherwise QModelIndex objects with the wrong internalPointer will exist inside the view.
    reset ();
    signal_data_changed ();
  }
}

void 
CellTreeModel::clear_top_level ()
{
  for (std::vector<CellTreeItem *>::iterator c = m_toplevel.begin (); c != m_toplevel.end (); ++c) {
    delete *c;
  }
  m_toplevel.clear ();
}

void 
CellTreeModel::build_top_level ()
{
  if ((m_flags & Children) != 0) {

    m_flat = true; //  no "hierarchical children" yet.

    m_toplevel.reserve (mp_base->child_cells ());

    for (db::Cell::child_cell_iterator child = mp_base->begin_child_cells (); ! child.at_end (); ++child) {
      CellTreeItem *item = new CellTreeItem (mp_layout, 0, false, *child, true, m_sorting);
      m_toplevel.push_back (item);
    }

  } else if ((m_flags & Parents) != 0) {

    m_flat = true; //  no "hierarchical parents" yet.

    m_toplevel.reserve (mp_base->parent_cells ());

    for (db::Cell::parent_cell_iterator parent = mp_base->begin_parent_cells (); parent != mp_base->end_parent_cells (); ++parent) {
      CellTreeItem *item = new CellTreeItem (mp_layout, 0, false, *parent, true, m_sorting);
      m_toplevel.push_back (item);
    }

  } else {

    if (m_flat) {
      m_toplevel.reserve (mp_layout->cells ());
    }

    db::Layout::top_down_const_iterator top = mp_layout->begin_top_down ();
    while (top != mp_layout->end_top_down ()) {

      if (m_flat) {
        CellTreeItem *item = new CellTreeItem (mp_layout, 0, false, *top, true, m_sorting);
        m_toplevel.push_back (item);
      } else if (mp_layout->cell (*top).is_top ()) {
        if ((m_flags & BasicCells) == 0 || ! mp_layout->cell (*top).is_proxy ()) {
          CellTreeItem *item = new CellTreeItem (mp_layout, 0, false, *top, (m_flags & TopCells) != 0, m_sorting);
          m_toplevel.push_back (item);
        }
      } else {
        break;
      }

      ++top;

    }

    if ((m_flags & BasicCells) != 0) {
      for (db::Layout::pcell_iterator pc = mp_layout->begin_pcells (); pc != mp_layout->end_pcells (); ++pc) {
        CellTreeItem *item = new CellTreeItem (mp_layout, 0, true, pc->second, true, m_sorting);
        m_toplevel.push_back (item);
      }
    }

  }

  std::sort (m_toplevel.begin (), m_toplevel.end (), cmp_cell_tree_items_f (m_sorting));

  for (size_t i = 0; i < m_toplevel.size (); ++i) {
    m_toplevel [i]->set_index (i);
  }
}

Qt::ItemFlags 
CellTreeModel::flags (const QModelIndex &index) const
{
  return Qt::ItemIsDragEnabled | QAbstractItemModel::flags (index);
}

QStringList 
CellTreeModel::mimeTypes () const
{
  QStringList types;
  types << QString::fromAscii (lay::drag_drop_mime_type);
  return types;
}

QMimeData *
CellTreeModel::mimeData(const QModelIndexList &indexes) const
{
  const db::Cell *c = 0;
  for (QModelIndexList::const_iterator i = indexes.begin (); i != indexes.end () && !c; ++i) {
    if (i->isValid()) {
      c = cell (*i);
    }
  }

  if (c) {
    lay::CellDragDropData data (mp_layout, c->cell_index ());
    return data.to_mime_data ();
  } else {
    return 0;
  }
}

int 
CellTreeModel::columnCount (const QModelIndex &) const 
{
  return 1;
}

QVariant 
CellTreeModel::data (const QModelIndex &index, int role) const 
{
  CellTreeItem *item = (CellTreeItem *) index.internalPointer ();
  if (! item || mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return QVariant ();
  }

  if (role == Qt::DisplayRole || role == Qt::EditRole) {

    if (m_pad) {
      return QVariant (tl::to_qstring (" " + item->display_text () + " "));
    } else {
      return QVariant (tl::to_qstring (item->display_text ()));
    }

  } else if (role == Qt::FontRole) {

    if (! mp_view) {

      return QVariant ();

    } else {

      QFont f (mp_parent->font ());

      const lay::CellView::unspecific_cell_path_type &path = mp_view->cellview (m_cv_index).unspecific_path ();
      const lay::CellView::specific_cell_path_type &ctx_path = mp_view->cellview (m_cv_index).specific_path ();

      if (! path.empty ()) {
        if (item->cell_index () == path.back ()) {
          if (m_flat) {
            f.setBold (true);
          } else {
            CellTreeItem *it = item;
            lay::CellView::unspecific_cell_path_type::const_iterator p = path.end ();
            while (it && p != path.begin ()) {
              --p;
              if (it->cell_index () != *p) {
                break;
              }
              it = it->parent ();
            }
            if (! it && p == path.begin ()) {
              f.setBold (true);
            }
          }
        } else if (! ctx_path.empty () && item->cell_index () == ctx_path.back ().inst_ptr.cell_index ()) {
          if (m_flat) {
            f.setUnderline (true);
          } else {
            CellTreeItem *it = item;
            lay::CellView::specific_cell_path_type::const_iterator cp = ctx_path.end ();
            while (it && cp != ctx_path.begin ()) {
              --cp;
              if (it->cell_index () != cp->inst_ptr.cell_index ()) {
                break;
              }
              it = it->parent ();
            }
            if (cp == ctx_path.begin ()) {
              lay::CellView::unspecific_cell_path_type::const_iterator p = path.end ();
              while (it && p != path.begin ()) {
                --p;
                if (it->cell_index () != *p) {
                  break;
                }
                it = it->parent ();
              }
              if (! it && p == path.begin ()) {
                f.setUnderline (true);
              }
            }
          }
        }
      }

      if (mp_view->is_cell_hidden (item->cell_index (), m_cv_index)) {
        f.setStrikeOut (true);
      }

      return QVariant (f);

    }

  } else if (role == Qt::BackgroundRole) {

    if (m_selected_indexes.find (index) != m_selected_indexes.end ()) {
      return QVariant (QColor (Qt::blue).lighter (180));
    } else {
      return QVariant ();
    }

  } else if (role == Qt::TextColorRole) {

#if 0 // do strikeout rather than making the color darker
    if (! mp_view) {
      return QVariant ();
    } else {
      QPalette pl (mp_parent->palette ());
      if (mp_view->is_cell_hidden (item->cell_index (), m_cv_index)) {
        QColor c1 = pl.color (QColorGroup::Text);
        QColor cb = pl.color (QColorGroup::Base);
        return QVariant (QColor ((c1.red () + cb.red ()) / 2, (c1.green () + cb.green ()) / 2, (c1.blue () + cb.blue ()) / 2));
      } else {
        return QVariant (pl.color (QColorGroup::Text));
      }
    }
#else
    return QVariant ();
#endif

  } else {

    return QVariant ();

  }
}

QVariant 
CellTreeModel::headerData (int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
  return QVariant ();
}

int 
CellTreeModel::rowCount (const QModelIndex &parent) const 
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return 0;
  } else if (parent.isValid ()) {
    CellTreeItem *item = (CellTreeItem *) parent.internalPointer ();
    if (! item) {
      return 0;
    } else if (! mp_layout->is_valid_cell_index (item->cell_index ())) {
      //  for safety we return 0 children for invalid cells
      return 0;
    } else {
      return int (item->children ());
    }
  } else {
    return int (m_toplevel.size ());
  }
}

QModelIndex 
CellTreeModel::index (int row, int column, const QModelIndex &parent) const 
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return QModelIndex ();
  } else if (parent.isValid ()) {
    CellTreeItem *item = (CellTreeItem *) parent.internalPointer ();
    if (! item) {
      return QModelIndex ();
    } else if (! mp_layout->is_valid_cell_index (item->cell_index ())) {
      //  for safety we don't return valid child indexes for invalid cells
      return QModelIndex ();
    } else {
      return createIndex (row, column, item->child (row));
    }
  } else if (row >= 0 && row < int (m_toplevel.size ())) {
    return createIndex (row, column, m_toplevel [row]);
  } else {
    return QModelIndex ();
  }
}

QModelIndex 
CellTreeModel::parent (const QModelIndex &index) const 
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return QModelIndex ();
  } 
  if (! index.isValid ()) {
    return index;
  }
  CellTreeItem *item = (CellTreeItem *) index.internalPointer ();
  if (! item) {
    return QModelIndex ();
  }
  CellTreeItem *pitem = item->parent ();
  if (pitem) {
    return createIndex (int (pitem->index ()), index.column (), pitem);
  } else {
    return QModelIndex ();
  }
}

int 
CellTreeModel::toplevel_items () const
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return 0;
  } else {
    return int (m_toplevel.size ());
  }
}

CellTreeItem *
CellTreeModel::toplevel_item (int index) 
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return 0;
  } else {
    return m_toplevel [index];
  }
}

QModelIndex 
CellTreeModel::model_index (CellTreeItem *item) const
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return QModelIndex ();
  } else {
    return createIndex (int (item->index ()), 0, item);
  }
}

bool
CellTreeModel::is_pcell (const QModelIndex &index) const
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return false;
  } else {
    CellTreeItem *item = (CellTreeItem *) index.internalPointer ();
    return item->is_pcell ();
  }
}

db::pcell_id_type
CellTreeModel::pcell_id (const QModelIndex &index) const
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return 0;
  } else {
    CellTreeItem *item = (CellTreeItem *) index.internalPointer ();
    return item->cell_index ();
  }
}

db::cell_index_type 
CellTreeModel::cell_index (const QModelIndex &index) const
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return 0;
  } else {
    CellTreeItem *item = (CellTreeItem *) index.internalPointer ();
    return item->cell_index ();
  }
}

const db::Cell *
CellTreeModel::cell (const QModelIndex &index) const
{
  if (index.isValid () && ! mp_layout->under_construction () && ! (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    CellTreeItem *item = (CellTreeItem *) index.internalPointer ();
    return & mp_layout->cell (item->cell_index ());
  } else {
    return 0;
  }
}

const char *
CellTreeModel::cell_name (const QModelIndex &index) const
{
  if (index.isValid () && ! mp_layout->under_construction () && ! (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    CellTreeItem *item = (CellTreeItem *) index.internalPointer ();
    if (item->is_pcell ()) {
      return mp_layout->pcell_header (item->cell_index ())->get_name ().c_str ();
    } else {
      return mp_layout->cell_name (item->cell_index ());
    }
  } else {
    return 0;
  }
}

void
CellTreeModel::clear_locate ()
{
  m_selected_indexes.clear ();
  m_current_index = m_selected_indexes.begin ();

  signal_data_changed ();
}

QModelIndex 
CellTreeModel::locate_next ()
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return QModelIndex ();
  }

  if (m_current_index == m_selected_indexes.end ()) {
    return QModelIndex ();
  } else {
    ++m_current_index;
    if (m_current_index == m_selected_indexes.end ()) {
      m_current_index = m_selected_indexes.begin ();
    }
    return *m_current_index;
  }
}

QModelIndex 
CellTreeModel::locate (const char *name, bool glob_pattern) 
{
  if (mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return QModelIndex ();
  }

  m_selected_indexes.clear ();

  std::vector <CellTreeItem *>::const_iterator lc;
  if (m_sorting == ByName && ! glob_pattern) {
    // employ sorting to look for the cell with that name
    lc = std::lower_bound (m_toplevel.begin (), m_toplevel.end (), name, cmp_cell_tree_item_vs_name_f ());
  } else if (glob_pattern) {
    tl::GlobPattern p (std::string (name) + "*");
    for (lc = m_toplevel.begin (); lc != m_toplevel.end (); ++lc) {
      if ((*lc)->name_matches (p)) {
        m_selected_indexes.insert (model_index (*lc));
      }
    }
  } else {
    // sorting does not help: linear search
    for (lc = m_toplevel.begin (); lc != m_toplevel.end (); ++lc) {
      if ((*lc)->name_equals (name)) {
        m_selected_indexes.insert (model_index (*lc));
      }
    }
  }
  
  signal_data_changed ();

  m_current_index = m_selected_indexes.begin ();
  if (m_current_index == m_selected_indexes.end ()) {
    return QModelIndex (); 
  } else {
    return *m_current_index;
  }
}

QModelIndex 
CellTreeModel::topLeft () const
{
  if (m_toplevel.empty () || mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return QModelIndex ();
  } else {
    return model_index (m_toplevel.front ());
  }
}

QModelIndex 
CellTreeModel::bottomRight () const
{
  if (m_toplevel.empty () || mp_layout->under_construction () || (mp_layout->manager () && mp_layout->manager ()->transacting ())) {
    return QModelIndex ();
  } else {
    QModelIndex p = model_index (m_toplevel.back ());
    int nr = 0;
    while (p.isValid () && (nr = rowCount (p)) > 0) {
      p = index (nr - 1, 0, p);
    }
    return p;
  }
}

void
CellTreeModel::signal_observed ()
{
  signal_data_changed ();
}

} // namespace lay
