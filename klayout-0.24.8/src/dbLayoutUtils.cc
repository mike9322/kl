
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


#include "dbLayoutUtils.h"
#include "tlProgress.h"

namespace db
{

// ------------------------------------------------------------------------------------
//  DirectLayerMapping implementation

DirectLayerMapping::DirectLayerMapping (db::Layout *target_layout)
  : ImportLayerMapping (), mp_layout (target_layout), m_initialized (false)
{
  // .. nothing yet ..
}

std::pair <bool, unsigned int> 
DirectLayerMapping::map_layer (const LayerProperties &lprops)
{
  if (! m_initialized) {
    for (db::Layout::layer_iterator l = mp_layout->begin_layers (); l != mp_layout->end_layers (); ++l) {
      m_lmap.insert (std::make_pair (*(*l).second, (*l).first));
    }
    m_initialized = true;
  }

  std::map <db::LayerProperties, unsigned int, db::LPLogicalLessFunc>::const_iterator lm = m_lmap.find (lprops);
  if (lm != m_lmap.end ()) {
    return std::make_pair (true, lm->second);
  } else {
    return std::make_pair (true, m_lmap.insert (std::make_pair (lprops, mp_layout->insert_layer (lprops))).first->second);
  }
}

// ------------------------------------------------------------------------------------
//  PropertyMapper implementation

PropertyMapper::PropertyMapper (db::Layout &target, const db::Layout &source)
  : mp_target (&target), mp_source (&source)
{
  //  .. nothing yet ..
}

/**
 *  @brief Instantiate a property mapper for mapping of property ids from the source to the target layout
 *
 *  This version does not specify a certain source or target layout. These must be set with the
 *  set_source or set_target methods.
 */
PropertyMapper::PropertyMapper ()
  : mp_target (0), mp_source (0)
{
  //  .. nothing yet ..
}

/**
 *  @brief Specify the source layout
 */
void 
PropertyMapper::set_source (const db::Layout &source)
{
  if (&source != mp_source) {
    m_prop_id_map.clear ();
    mp_source = &source;
  }
}

/**
 *  @brief Specify the target layout
 */
void 
PropertyMapper::set_target (db::Layout &target)
{
  if (&target != mp_target) {
    m_prop_id_map.clear ();
    mp_target = &target;
  }
}

/**
 *  @brief The actual mapping function
 */
db::Layout::properties_id_type 
PropertyMapper::operator() (db::Layout::properties_id_type source_id)
{
  if (source_id == 0 || mp_source == mp_target) {
    return source_id;
  }

  tl_assert (mp_source != 0);
  tl_assert (mp_target != 0);

  std::map <db::Layout::properties_id_type, db::Layout::properties_id_type>::const_iterator p = m_prop_id_map.find (source_id);

  if (p == m_prop_id_map.end ()) {
    db::Layout::properties_id_type new_id = mp_target->properties_repository ().translate (mp_source->properties_repository (), source_id);
    m_prop_id_map.insert (std::make_pair (source_id, new_id));
    return new_id;
  } else {
    return p->second;
  }
}

// ------------------------------------------------------------------------------------
//  merge_layouts implementation

void 
merge_layouts (db::Layout &target, 
               const db::Layout &source, 
               const db::ICplxTrans &trans,
               const std::vector<db::cell_index_type> &source_cells, 
               const std::map<db::cell_index_type, db::cell_index_type> &cell_mapping,
               const std::map<unsigned int, unsigned int> &layer_mapping,
               std::map<db::cell_index_type, db::cell_index_type> *final_cell_mapping)
{
  if (final_cell_mapping) {
    final_cell_mapping->insert (cell_mapping.begin (), cell_mapping.end ());
  }

  //  collect all called cells and all top level cells
  std::set<db::cell_index_type> all_top_level_cells;
  std::set<db::cell_index_type> all_cells_to_copy;

  for (std::vector<db::cell_index_type>::const_iterator src = source_cells.begin (); src != source_cells.end (); ++src) {
    all_cells_to_copy.insert (*src);
    all_top_level_cells.insert (*src);
    source.cell (*src).collect_called_cells (all_cells_to_copy);
  }

  //  identify all new cells and create new ones
  std::map<db::cell_index_type, db::cell_index_type> new_cell_mapping;
  for (std::set<db::cell_index_type>::const_iterator c = all_cells_to_copy.begin (); c != all_cells_to_copy.end (); ++c) {
    if (cell_mapping.find (*c) == cell_mapping.end ()) {
      new_cell_mapping.insert (std::make_pair (*c, target.add_cell (source.cell_name (*c))));
    }
  }

  if (final_cell_mapping) {
    final_cell_mapping->insert (new_cell_mapping.begin (), new_cell_mapping.end ());
  }

  //  provide the property mapper
  db::PropertyMapper pm (target, source);

  tl::RelativeProgress progress (tl::to_string (QObject::tr ("Merge cells")), all_cells_to_copy.size (), 1);

  //  actually to the mapping
  for (std::set<db::cell_index_type>::const_iterator c = all_cells_to_copy.begin (); c != all_cells_to_copy.end (); ++c) {

    ++progress;

    db::cell_index_type target_cell_index = 0;
    std::map<db::cell_index_type, db::cell_index_type>::const_iterator cm = cell_mapping.find (*c);
    if (cm == cell_mapping.end ()) {
      target_cell_index = new_cell_mapping[*c];
    } else {
      target_cell_index = cm->second;
    }

    const db::Cell &source_cell = source.cell (*c);
    db::Cell &target_cell = target.cell (target_cell_index);

    //  copy the shapes
    db::ICplxTrans shape_trans;
    if (all_top_level_cells.find (*c) == all_top_level_cells.end ()) {
      shape_trans = db::ICplxTrans (trans.mag ());
    } else {
      shape_trans = trans;
    }

    for (std::map<unsigned int, unsigned int>::const_iterator lm = layer_mapping.begin (); lm != layer_mapping.end (); ++lm) {
      target_cell.shapes (lm->second).insert_transformed (source_cell.shapes (lm->first), shape_trans, pm);
    }

    //  copy the instances
    for (db::Cell::const_iterator inst = source_cell.begin (); !inst.at_end (); ++inst) {

      //  only copy instances for new cells ..
      std::map<db::cell_index_type, db::cell_index_type>::const_iterator nc = new_cell_mapping.find (inst->cell_index ());
      if (nc != new_cell_mapping.end ()) {

        db::CellInstArray new_inst_array (inst->cell_inst ());
        new_inst_array.transform_into (shape_trans, 0 /*no array repository*/);

        new_inst_array.object ().cell_index (nc->second);

        if (inst->has_prop_id ()) {
          target_cell.insert (db::object_with_properties<db::CellInstArray> (new_inst_array, pm (inst->prop_id ())));
        } else {
          target_cell.insert (new_inst_array);
        }

      }

    }

  }

}

static void 
copy_or_propagate_shapes (db::Layout &target, 
                          const db::Layout &source, 
                          const db::ICplxTrans &trans,
                          const db::ICplxTrans &propagate_trans,
                          db::PropertyMapper &pm,
                          db::cell_index_type source_cell_index,
                          db::cell_index_type source_parent_cell_index,
                          unsigned int target_layer, unsigned int source_layer,
                          const std::set<db::cell_index_type> &all_cells_to_copy,
                          const std::map<db::cell_index_type, db::cell_index_type> &cell_mapping)
{
  const db::Cell &source_cell = source.cell (source_cell_index);
  const db::Cell &source_parent_cell = source.cell (source_parent_cell_index);

  std::map<db::cell_index_type, db::cell_index_type>::const_iterator cm = cell_mapping.find (source_parent_cell_index);
  if (cm == cell_mapping.end ()) {

    for (db::Cell::parent_inst_iterator p = source_parent_cell.begin_parent_insts (); ! p.at_end (); ++p) {

      if (all_cells_to_copy.find (p->parent_cell_index ()) != all_cells_to_copy.end ()) {
        const db::CellInstArray &cell_inst = p->child_inst ().cell_inst ();
        for (db::CellInstArray::iterator a = cell_inst.begin (); ! a.at_end (); ++a) {
          db::ICplxTrans t = db::ICplxTrans (cell_inst.complex_trans (*a)) * propagate_trans;
          copy_or_propagate_shapes (target, source, trans, t, pm, source_cell_index, p->parent_cell_index (), target_layer, source_layer, all_cells_to_copy, cell_mapping);
        }
      }

    }

  } else {

    db::Cell &target_cell = target.cell (cm->second);
    target_cell.shapes (target_layer).insert_transformed (source_cell.shapes (source_layer), trans * propagate_trans, pm);

  }
}

void 
copy_shapes (db::Layout &target, 
             const db::Layout &source, 
             const db::ICplxTrans &trans,
             const std::vector<db::cell_index_type> &source_cells, 
             const std::map<db::cell_index_type, db::cell_index_type> &cell_mapping,
             const std::map<unsigned int, unsigned int> &layer_mapping)
{
  //  collect all called cells and all top level cells
  std::set<db::cell_index_type> all_top_level_cells;
  std::set<db::cell_index_type> all_cells_to_copy;

  for (std::vector<db::cell_index_type>::const_iterator src = source_cells.begin (); src != source_cells.end (); ++src) {
    all_cells_to_copy.insert (*src);
    all_top_level_cells.insert (*src);
    source.cell (*src).collect_called_cells (all_cells_to_copy);
  }

  //  provide the property mapper
  db::PropertyMapper pm (target, source);

  tl::RelativeProgress progress (tl::to_string (QObject::tr ("Merge cells")), all_cells_to_copy.size () * layer_mapping.size (), 1);

  //  and copy
  for (std::set<db::cell_index_type>::const_iterator c = all_cells_to_copy.begin (); c != all_cells_to_copy.end (); ++c) {
    for (std::map<unsigned int, unsigned int>::const_iterator lm = layer_mapping.begin (); lm != layer_mapping.end (); ++lm) {
      ++progress;
      copy_or_propagate_shapes (target, source, trans, db::ICplxTrans (), pm, *c, *c, lm->second, lm->first, all_cells_to_copy, cell_mapping);
    }
  }
}

void 
move_shapes (db::Layout &target, 
             db::Layout &source, 
             const db::ICplxTrans &trans,
             const std::vector<db::cell_index_type> &source_cells, 
             const std::map<db::cell_index_type, db::cell_index_type> &cell_mapping,
             const std::map<unsigned int, unsigned int> &layer_mapping)
{
  //  collect all called cells and all top level cells
  std::set<db::cell_index_type> all_top_level_cells;
  std::set<db::cell_index_type> all_cells_to_copy;

  for (std::vector<db::cell_index_type>::const_iterator src = source_cells.begin (); src != source_cells.end (); ++src) {
    all_cells_to_copy.insert (*src);
    all_top_level_cells.insert (*src);
    source.cell (*src).collect_called_cells (all_cells_to_copy);
  }

  //  provide the property mapper
  db::PropertyMapper pm (target, source);

  tl::RelativeProgress progress (tl::to_string (QObject::tr ("Merge cells")), all_cells_to_copy.size () * layer_mapping.size (), 1);

  //  and copy
  for (std::set<db::cell_index_type>::const_iterator c = all_cells_to_copy.begin (); c != all_cells_to_copy.end (); ++c) {
    for (std::map<unsigned int, unsigned int>::const_iterator lm = layer_mapping.begin (); lm != layer_mapping.end (); ++lm) {
      ++progress;
      copy_or_propagate_shapes (target, source, trans, db::ICplxTrans (), pm, *c, *c, lm->second, lm->first, all_cells_to_copy, cell_mapping);
      source.cell (*c).shapes (lm->first).clear ();
    }
  }
}

// ------------------------------------------------------------
//  Implementation of "find_layout_context"

static std::pair<bool, db::ICplxTrans> 
find_layout_context (const db::Layout &layout, db::cell_index_type from, db::cell_index_type to, std::set <db::cell_index_type> &visited, const db::ICplxTrans &trans) 
{
  const db::Cell &cell = layout.cell (from);
  for (db::Cell::parent_inst_iterator p = cell.begin_parent_insts (); ! p.at_end (); ++p) {

    if (p->parent_cell_index () == to) {

      return std::make_pair (true, db::ICplxTrans (p->child_inst ().complex_trans ()) * trans);

    } else if (visited.find (p->parent_cell_index ()) == visited.end ()) {

      visited.insert (p->parent_cell_index ());

      std::pair<bool, db::ICplxTrans> context = find_layout_context (layout, p->parent_cell_index (), to, visited, db::ICplxTrans (p->child_inst ().complex_trans ()) * trans);
      if (context.first) {
        return context;
      }

    }

  }

  return std::pair<bool, db::ICplxTrans> (false, db::ICplxTrans ());
}

std::pair<bool, db::ICplxTrans> 
find_layout_context (const db::Layout &layout, db::cell_index_type from, db::cell_index_type to)
{
  if (from == to) {
    return std::make_pair (true, db::ICplxTrans ());
  } else {
    std::set <db::cell_index_type> v;
    return find_layout_context (layout, from, to, v, db::ICplxTrans ());
  }
}

// ------------------------------------------------------------
//  Implementation of ContextCache

ContextCache::ContextCache (const db::Layout &layout)
  : mp_layout (&layout)
{
  //  .. nothing yet ..
}

const std::pair<bool, db::ICplxTrans> &
ContextCache::find_layout_context (db::cell_index_type from, db::cell_index_type to)
{
  std::map<std::pair<db::cell_index_type, db::cell_index_type>, std::pair<bool, db::ICplxTrans> >::iterator c = m_cache.find (std::make_pair (from, to));
  if (c == m_cache.end ()) {
    c = m_cache.insert (std::make_pair (std::make_pair (from, to), std::make_pair (false, db::ICplxTrans ()))).first;
    c->second = db::find_layout_context (*mp_layout, from, to);
  }
  return c->second;
}

}

