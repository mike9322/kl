
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


#include "dbLayoutDiff.h"
#include "dbLayout.h"
#include "dbCellMapping.h"
#include "dbFuzzyCellMapping.h"
#include "dbLayoutUtils.h"
#include "tlLog.h"

namespace db
{

static void 
collect_layers (const db::Layout &l, std::map<db::LayerProperties, unsigned int, db::LPLogicalLessFunc> &layers, unsigned int flags /* not used currently */)
{
  for (unsigned int i = 0; i < l.layers (); ++i) {
    if (l.is_valid_layer (i)) {
      const LayerProperties &lp = l.get_properties (i);
      if (lp != LayerProperties ()) {
        layers.insert (std::make_pair (lp, i));
      }
    }
  }
}

static void
collect_cells (const db::Layout &l, const db::Cell *top, std::map <std::string, db::cell_index_type> &cells)
{
  if (!top) {

    for (db::Layout::const_iterator c = l.begin (); c != l.end (); ++c) {
      cells.insert (std::make_pair (l.cell_name (c->cell_index ()), c->cell_index ()));
    }

  } else {

    std::set<db::cell_index_type> called_cells;
    top->collect_called_cells (called_cells);

    called_cells.insert (top->cell_index ());

    for (std::set<db::cell_index_type>::const_iterator c = called_cells.begin (); c != called_cells.end (); ++c) {
      cells.insert (std::make_pair (l.cell_name (*c), *c));
    }

  }
}

static void
collect_insts_of_unmapped_cells (const db::Layout &l, const db::Cell *cell, unsigned int flags, const std::map <db::cell_index_type, db::cell_index_type> &cci, std::vector <db::CellInstArrayWithProperties> &insts)
{
  for (db::Cell::const_iterator i = cell->begin (); !i.at_end (); ++i) {

    std::map <db::cell_index_type, db::cell_index_type>::const_iterator ccii = cci.find (i->cell_index ());
    if (ccii == cci.end ()) {

      db::CellInstArrayWithProperties new_inst (i->cell_inst (), i->prop_id ());
      insts.push_back (new_inst);

    }
  }
}

static void 
rewrite_instances_to (std::vector <db::CellInstArrayWithProperties> &insts, unsigned int flags, const std::vector <db::cell_index_type> &common_cells, db::PropertyMapper &pn)
{
  for (std::vector <db::CellInstArrayWithProperties>::iterator i = insts.begin (); i != insts.end (); ++i) {

    tl_assert (size_t (i->object ().cell_index ()) < common_cells.size ());

    db::properties_id_type prop_id = 0;
    if (! (flags & layout_diff::f_no_properties)) {
      prop_id = pn (i->properties_id ());
    }

    i->object () = db::CellInst (common_cells [i->object ().cell_index ()]);
    i->properties_id (prop_id);

  }
}

static void
collect_insts (const db::Layout &l, const db::Cell *cell, unsigned int flags, const std::map <db::cell_index_type, db::cell_index_type> &cci, std::vector <db::CellInstArrayWithProperties> &insts, PropertyMapper &pn)
{
  insts.clear ();

  for (db::Cell::const_iterator i = cell->begin (); !i.at_end (); ++i) {

    std::map <db::cell_index_type, db::cell_index_type>::const_iterator ccii = cci.find (i->cell_index ());

    if (ccii != cci.end ()) {
    
      db::CellInst new_obj (ccii->second);

      db::properties_id_type prop_id = 0;
      if (! (flags & layout_diff::f_no_properties)) {
        prop_id = pn (i->prop_id ());
      }

      db::Point a, b;
      unsigned long amax, bmax;
      if ((flags & layout_diff::f_flatten_array_insts) == 0 && i->is_regular_array (a, b, amax, bmax) && (amax > 1 || bmax > 1)) {

        //  normalize arrays (this is a weak normalization!)
        if (amax == 1) {
          a = db::Point ();
        }
        if (bmax == 1) {
          b = db::Point ();
        }
        if (b < a) {
          std::swap (a, b);
          std::swap (amax, bmax);
        }

        insts.push_back (db::CellInstArrayWithProperties (db::CellInstArray (new_obj, i->complex_trans (), a, b, amax, bmax), prop_id));

      } else {
        for (db::CellInstArray::iterator a = i->begin (); ! a.at_end (); ++a) {
          insts.push_back (db::CellInstArrayWithProperties (db::CellInstArray (new_obj, i->complex_trans (*a)), prop_id));
        }
      }

    }

  }

  std::sort (insts.begin (), insts.end ());
}

static void
collect_polygons (const db::Layout &l, const db::Cell *c, unsigned int layer, unsigned int flags, std::vector< std::pair<db::Polygon, db::properties_id_type> > &shapes, PropertyMapper &pn)
{
  shapes.clear ();

  for (db::ShapeIterator s = c->shapes (layer).begin (db::ShapeIterator::Polygons | ((flags & db::layout_diff::f_paths_as_polygons) ? db::ShapeIterator::Paths : 0) | ((flags & db::layout_diff::f_boxes_as_polygons) ? db::ShapeIterator::Boxes : 0)); !s.at_end (); ++s) {
    db::properties_id_type prop_id = 0;
    if (! (flags & layout_diff::f_no_properties)) {
      prop_id = pn (s->prop_id ());
    }
    shapes.push_back (std::make_pair (db::Polygon (), prop_id));
    s->polygon (shapes.back ().first);
  }

  std::sort (shapes.begin (), shapes.end ());
}

static void
collect_edges (const db::Layout &l, const db::Cell *c, unsigned int layer, unsigned int flags, std::vector< std::pair<db::Edge, db::properties_id_type> > &shapes, PropertyMapper &pn)
{
  shapes.clear ();

  for (db::ShapeIterator s = c->shapes (layer).begin (db::ShapeIterator::Edges); !s.at_end (); ++s) {
    db::properties_id_type prop_id = 0;
    if (! (flags & layout_diff::f_no_properties)) {
      prop_id = pn (s->prop_id ());
    }
    shapes.push_back (std::make_pair (db::Edge (), prop_id));
    s->edge (shapes.back ().first);
  }

  std::sort (shapes.begin (), shapes.end ());
}

static void
collect_boxes (const db::Layout &l, const db::Cell *c, unsigned int layer, unsigned int flags, std::vector< std::pair<db::Box, db::properties_id_type> > &shapes, PropertyMapper &pn)
{
  shapes.clear ();

  for (db::ShapeIterator s = c->shapes (layer).begin (db::ShapeIterator::Boxes); !s.at_end (); ++s) {
    db::properties_id_type prop_id = 0;
    if (! (flags & layout_diff::f_no_properties)) {
      prop_id = pn (s->prop_id ());
    }
    shapes.push_back (std::make_pair (db::Box (), prop_id));
    s->box (shapes.back ().first);
  }

  std::sort (shapes.begin (), shapes.end ());
}

static void
collect_texts (const db::Layout &l, const db::Cell *c, unsigned int layer, unsigned int flags, std::vector< std::pair<db::Text, db::properties_id_type> > &shapes, PropertyMapper &pn)
{
  shapes.clear ();

  for (db::ShapeIterator s = c->shapes (layer).begin (db::ShapeIterator::Texts); !s.at_end (); ++s) {

    db::properties_id_type prop_id = 0;
    if (! (flags & layout_diff::f_no_properties)) {
      prop_id = pn (s->prop_id ());
    }
    shapes.push_back (std::make_pair (db::Text (), prop_id));
    s->text (shapes.back ().first);
    //  force the text string to be a real string rather than a potential reference
    //  to a string repository entry - only this way we can compare strings from different
    //  layouts.
    shapes.back ().first.string (shapes.back ().first.string ());

    if (flags & layout_diff::f_no_text_details) {
      shapes.back ().first.font (db::NoFont);
      shapes.back ().first.halign (db::NoHAlign);
      shapes.back ().first.valign (db::NoVAlign);
    }

    if (flags & layout_diff::f_no_text_orientation) {
      db::Text::trans_type tt (shapes.back ().first.trans ());
      tt = db::Text::trans_type (tt.disp ());
      shapes.back ().first.trans (tt);
      shapes.back ().first.size (0);
    }

  }

  std::sort (shapes.begin (), shapes.end ());
}

static void
collect_paths (const db::Layout &l, const db::Cell *c, unsigned int layer, unsigned int flags, std::vector< std::pair<db::Path, db::properties_id_type> > &shapes, db::PropertyMapper &pn)
{
  shapes.clear ();

  for (db::ShapeIterator s = c->shapes (layer).begin (db::ShapeIterator::Paths); !s.at_end (); ++s) {
    db::properties_id_type prop_id = 0;
    if (! (flags & layout_diff::f_no_properties)) {
      prop_id = pn (s->prop_id ());
    }
    shapes.push_back (std::make_pair (db::Path (), prop_id));
    s->path (shapes.back ().first);
  }

  std::sort (shapes.begin (), shapes.end ());
}

static bool
do_compare_layouts (const db::Layout &a, const db::Cell *top_a, const db::Layout &b, const db::Cell *top_b, unsigned int flags, DifferenceReceiver &r)
{
  bool differs = false;

  if (fabs (a.dbu () - b.dbu ()) > 1e-9) {
    differs = true;
    if (flags & layout_diff::f_silent) {
      return false;
    }
    r.dbu_differs (a.dbu (), b.dbu ());
  }

  bool verbose = (flags & layout_diff::f_verbose);

  db::Layout n, na, nb;
  na.properties_repository () = a.properties_repository ();
  nb.properties_repository () = b.properties_repository ();

  db::PropertyMapper prop_normalize_a (n, a);
  db::PropertyMapper prop_normalize_b (n, b);

  db::PropertyMapper prop_remap_to_a (na, n);
  db::PropertyMapper prop_remap_to_b (nb, n);

  //  compare layers

  std::map<db::LayerProperties, unsigned int, db::LPLogicalLessFunc> layers_a;
  std::map<db::LayerProperties, unsigned int, db::LPLogicalLessFunc> layers_b;

  collect_layers (a, layers_a, flags);
  collect_layers (b, layers_b, flags);

  std::vector<db::LayerProperties> common_layers;
  std::vector<db::LayerProperties> layers_in_a_only;
  std::vector<db::LayerProperties> layers_in_b_only;

  for (std::map<db::LayerProperties, unsigned int, db::LPLogicalLessFunc>::const_iterator la = layers_a.begin (); la != layers_a.end (); ++la) {
    std::map<db::LayerProperties, unsigned int, db::LPLogicalLessFunc>::const_iterator lb = layers_b.find (la->first);
    if (lb == layers_b.end ()) {
      differs = true;
      if (flags & layout_diff::f_silent) {
        return false;
      }
      if (flags & layout_diff::f_dont_summarize_missing_layers) {
        layers_in_a_only.push_back (la->first);
        common_layers.push_back (la->first);
      } else {
        r.layer_in_a_only (la->first);
      }
    } else {
      common_layers.push_back (la->first);
      if (! (flags & layout_diff::f_no_layer_names) && la->first.name != lb->first.name) {
        differs = true;
        if (flags & layout_diff::f_silent) {
          return false;
        }
        r.layer_name_differs (la->first, lb->first);
      }
    }
  }

  for (std::map<db::LayerProperties, unsigned int, db::LPLogicalLessFunc>::const_iterator lb = layers_b.begin (); lb != layers_b.end (); ++lb) {
    std::map<db::LayerProperties, unsigned int, db::LPLogicalLessFunc>::const_iterator la = layers_a.find (lb->first);
    if (la == layers_a.end ()) {
      differs = true;
      if (flags & layout_diff::f_silent) {
        return false;
      }
      if (flags & layout_diff::f_dont_summarize_missing_layers) {
        layers_in_b_only.push_back (lb->first);
        common_layers.push_back (lb->first);
      } else {
        r.layer_in_b_only (lb->first);
      }
    } 
  }

  //  compare cells

  std::map <std::string, db::cell_index_type> cells_a; 
  std::map <std::string, db::cell_index_type> cells_b; 

  collect_cells (a, top_a, cells_a);
  collect_cells (b, top_b, cells_b);

  std::vector <std::string> common_cells;
  std::map <db::cell_index_type, db::cell_index_type> common_cell_indices_a;
  std::vector <db::cell_index_type> common_cells_a;
  std::map <db::cell_index_type, db::cell_index_type> common_cell_indices_b;
  std::vector <db::cell_index_type> common_cells_b;

  if (top_a && top_b && (flags & layout_diff::f_smart_cell_mapping)) {

    //  employ the cell mapping to derive equivalent cells
    if (tl::verbosity () >= 20) {
      tl::info << "Layout diff - cell name mapping";
    }

    db::FuzzyCellMapping mapping;
    mapping.create (a, top_a->cell_index (), b, top_b->cell_index ());

    // collect all A cells which have corresponding B cells.
    std::set<db::cell_index_type> mapped;
    for (std::map <std::string, db::cell_index_type>::const_iterator cb = cells_b.begin (); cb != cells_b.end (); ++cb) {
      std::pair<bool, db::cell_index_type> cm = mapping.cell_mapping_pair (cb->second);
      if (cm.first) {
        mapped.insert (cm.second);
      }
    }

    db::cell_index_type cci = 0;
    for (std::map <std::string, db::cell_index_type>::const_iterator cb = cells_b.begin (); cb != cells_b.end (); ++cb) {

      std::pair<bool, db::cell_index_type> cm = mapping.cell_mapping_pair (cb->second);
      if (!cm.first) {

        //  Employ exact name matching to unused cells as last resort.
        std::map <std::string, db::cell_index_type>::const_iterator ca = cells_a.find (cb->first);
        if (ca == cells_a.end () || mapped.find (ca->second) != mapped.end ()) {

          differs = true;
          if (flags & layout_diff::f_silent) {
            return false;
          }

          r.cell_in_b_only (cb->first, cb->second);

        } else {

          mapped.insert (ca->second);
          common_cells.push_back (ca->first);
          common_cell_indices_a.insert (std::make_pair (ca->second, cci));
          common_cells_a.push_back (ca->second);
          common_cell_indices_b.insert (std::make_pair (cb->second, cci));
          common_cells_b.push_back (cb->second);
          ++cci;

        }

      } else {

        if (cb->first == a.cell_name (cm.second)) {
          common_cells.push_back (cb->first);
        } else {
          r.cell_name_differs (std::string (a.cell_name (cm.second)), cm.second, cb->first, cb->second);
          differs = true;
          if (flags & layout_diff::f_silent) {
            return false;
          }
          common_cells.push_back (a.cell_name (cm.second)); // use layout A cell name as reference
        }

        common_cell_indices_a.insert (std::make_pair (cm.second, cci));
        common_cells_a.push_back (cm.second);
        common_cell_indices_b.insert (std::make_pair (cb->second, cci));
        common_cells_b.push_back (cb->second);
        ++cci;

      }

    }

    for (std::map <std::string, db::cell_index_type>::const_iterator ca = cells_a.begin (); ca != cells_a.end (); ++ca) {
      if (mapped.find (ca->second) == mapped.end ()) {
        differs = true;
        if (flags & layout_diff::f_silent) {
          return false;
        }
        r.cell_in_a_only (ca->first, ca->second);
      }
    }

  } else {

    db::cell_index_type cci = 0;
    for (std::map <std::string, db::cell_index_type>::const_iterator ca = cells_a.begin (); ca != cells_a.end (); ++ca) {
      std::map <std::string, db::cell_index_type>::const_iterator cb = cells_b.find (ca->first);
      if (cb == cells_b.end ()) {
        differs = true;
        if (flags & layout_diff::f_silent) {
          return false;
        }
        r.cell_in_a_only (ca->first, ca->second);
      } else {
        common_cells.push_back (ca->first);
        common_cell_indices_a.insert (std::make_pair (ca->second, cci));
        common_cells_a.push_back (ca->second);
        common_cell_indices_b.insert (std::make_pair (cb->second, cci));
        common_cells_b.push_back (cb->second);
        ++cci;
      }
    }

    for (std::map <std::string, db::cell_index_type>::const_iterator cb = cells_b.begin (); cb != cells_b.end (); ++cb) {
      std::map <std::string, db::cell_index_type>::const_iterator ca = cells_a.find (cb->first);
      if (ca == cells_a.end ()) {
        differs = true;
        if (flags & layout_diff::f_silent) {
          return false;
        }
        r.cell_in_b_only (cb->first, cb->second);
      }
    }

  }


  tl::RelativeProgress progress (tl::to_string (QObject::tr ("Layout diff")), common_cells.size (), 1);

  //  compare cell by cell
  
  if (tl::verbosity () >= 20) {
    tl::info << "Layout diff - cell by cell compare";
  }

  std::vector <db::CellInstArrayWithProperties> insts_a;
  std::vector <db::CellInstArrayWithProperties> insts_b;
  std::vector <std::pair <db::Polygon, db::properties_id_type> > polygons_a;
  std::vector <std::pair <db::Polygon, db::properties_id_type> > polygons_b;
  std::vector <std::pair <db::Path, db::properties_id_type> > paths_a;
  std::vector <std::pair <db::Path, db::properties_id_type> > paths_b;
  std::vector <std::pair <db::Text, db::properties_id_type> > texts_a;
  std::vector <std::pair <db::Text, db::properties_id_type> > texts_b;
  std::vector <std::pair <db::Box, db::properties_id_type> > boxes_a;
  std::vector <std::pair <db::Box, db::properties_id_type> > boxes_b;
  std::vector <std::pair <db::Edge, db::properties_id_type> > edges_a;
  std::vector <std::pair <db::Edge, db::properties_id_type> > edges_b;

  for (unsigned int cci = 0; cci < common_cells.size (); ++cci) {

    const db::Cell *cell_a = &a.cell (common_cells_a [cci]);
    const db::Cell *cell_b = &b.cell (common_cells_b [cci]);

    if (tl::verbosity () >= 30) {
      tl::info << "Layout diff - compare cell " << a.cell_name (cell_a->cell_index ()) << " and " << b.cell_name (cell_b->cell_index ());
    }

    r.begin_cell (common_cells [cci], common_cells_a [cci], common_cells_b [cci]); 

    if (!verbose && cell_a->bbox () != cell_b->bbox ()) {
      differs = true;
      if (flags & layout_diff::f_silent) {
        return false;
      }
      r.bbox_differs (cell_a->bbox (), cell_b->bbox ());
    }

    collect_insts (a, cell_a, flags, common_cell_indices_a, insts_a, prop_normalize_a);
    collect_insts (b, cell_b, flags, common_cell_indices_b, insts_b, prop_normalize_b);

    std::vector <db::CellInstArrayWithProperties> anotb;
    std::set_difference (insts_a.begin (), insts_a.end (), insts_b.begin (), insts_b.end (), std::back_inserter (anotb));

    rewrite_instances_to (anotb, flags, common_cells_a, prop_remap_to_a);
    collect_insts_of_unmapped_cells (a, cell_a, flags, common_cell_indices_a, anotb);

    std::vector <db::CellInstArrayWithProperties> bnota;
    std::set_difference (insts_b.begin (), insts_b.end (), insts_a.begin (), insts_a.end (), std::back_inserter (bnota));

    rewrite_instances_to (bnota, flags, common_cells_b, prop_remap_to_b);
    collect_insts_of_unmapped_cells (b, cell_b, flags, common_cell_indices_b, bnota);

    if (! anotb.empty () || ! bnota.empty ()) {

      differs = true;

      if (flags & layout_diff::f_silent) {
        return false;
      }

      r.begin_inst_differences ();

      if (verbose) {

        r.instances_in_a (insts_a, common_cells, n.properties_repository ());
        r.instances_in_b (insts_b, common_cells, n.properties_repository ());

        r.instances_in_a_only (anotb, a);
        r.instances_in_b_only (bnota, b);

      }

      r.end_inst_differences ();

    }


    //  compare layer by layer
    
    for (std::vector<db::LayerProperties>::const_iterator cl = common_layers.begin (); cl != common_layers.end (); ++cl) {

      if (tl::verbosity () >= 40) {
        tl::info << "Layout diff - compare layer " << cl->to_string ();
      }

      bool is_valid_a = false, is_valid_b = false;
      unsigned int layer_a = 0, layer_b = 0;

      if (layers_a.find (*cl) != layers_a.end ()) { 
        layer_a = layers_a.find (*cl)->second;
        is_valid_a = true;
      }
      
      if (layers_b.find (*cl) != layers_b.end ()) {
        layer_b = layers_b.find (*cl)->second;
        is_valid_b = true;
      }

      r.begin_layer (*cl, layer_a, is_valid_a, layer_b, is_valid_b);

      if (!verbose && is_valid_a && is_valid_b && cell_a->bbox (layer_a) != cell_b->bbox (layer_b)) {
        differs = true;
        if (flags & layout_diff::f_silent) {
          return false;
        }
        r.per_layer_bbox_differs (cell_a->bbox (layer_a), cell_b->bbox (layer_b));
      }

      //  compare polygons

      polygons_a.clear();
      polygons_b.clear();
      if (is_valid_a) {
        collect_polygons (a, cell_a, layer_a, flags, polygons_a, prop_normalize_a);
      } 
      if (is_valid_b) {
        collect_polygons (b, cell_b, layer_b, flags, polygons_b, prop_normalize_b);
      }

      if (polygons_a != polygons_b) {
        differs = true;
        if (flags & layout_diff::f_silent) {
          return false;
        }
        r.begin_polygon_differences ();
        if (verbose) {
          r.detailed_diff (n.properties_repository (), polygons_a, polygons_b);
        }
        r.end_polygon_differences ();
      }


      //  compare paths

      if (! (flags & db::layout_diff::f_paths_as_polygons)) {

        paths_a.clear();
        paths_b.clear();
        if (is_valid_a) {
          collect_paths (a, cell_a, layer_a, flags, paths_a, prop_normalize_a);
        }
        if (is_valid_b) {
          collect_paths (b, cell_b, layer_b, flags, paths_b, prop_normalize_b);
        }

        if (paths_a != paths_b) {
          differs = true;
          if (flags & layout_diff::f_silent) {
            return false;
          }
          r.begin_path_differences ();
          if (verbose) {
            r.detailed_diff (n.properties_repository (), paths_a, paths_b);
          }
          r.end_path_differences ();
        }

      }

      //  compare texts

      texts_a.clear();
      texts_b.clear();
      if (is_valid_a) {
        collect_texts (a, cell_a, layer_a, flags, texts_a, prop_normalize_a);
      }
      if (is_valid_b) {
        collect_texts (b, cell_b, layer_b, flags, texts_b, prop_normalize_b);
      }

      if (texts_a != texts_b) {
        differs = true;
        if (flags & layout_diff::f_silent) {
          return false;
        }
        r.begin_text_differences ();
        if (verbose) {
          r.detailed_diff (n.properties_repository (), texts_a, texts_b);
        }
        r.end_text_differences ();
      }

      //  compare boxes (unless this is done by the polygon compare code)
      if (! (flags & db::layout_diff::f_boxes_as_polygons)) {

        boxes_a.clear();
        boxes_b.clear();
        if (is_valid_a) {
          collect_boxes (a, cell_a, layer_a, flags, boxes_a, prop_normalize_a);
        }
        if (is_valid_b) {
          collect_boxes (b, cell_b, layer_b, flags, boxes_b, prop_normalize_b);
        }

        if (boxes_a != boxes_b) {
          differs = true;
          if (flags & layout_diff::f_silent) {
            return false;
          }
          r.begin_box_differences ();
          if (verbose) {
            r.detailed_diff (n.properties_repository (), boxes_a, boxes_b);
          }
          r.end_box_differences ();
        }

      }

      //  compare edges

      edges_a.clear();
      edges_b.clear();
      if (is_valid_a) {
        collect_edges (a, cell_a, layer_a, flags, edges_a, prop_normalize_a);
      }
      if (is_valid_b) {
        collect_edges (b, cell_b, layer_b, flags, edges_b, prop_normalize_b);
      }

      if (edges_a != edges_b) {
        differs = true;
        if (flags & layout_diff::f_silent) {
          return false;
        }
        r.begin_edge_differences ();
        if (verbose) {
          r.detailed_diff (n.properties_repository (), edges_a, edges_b);
        }
        r.end_edge_differences ();
      }

      r.end_layer ();

    }

    r.end_cell ();

    ++progress;

  }

  return ! differs;

}

bool
compare_layouts (const db::Layout &a, const db::Layout &b, unsigned int flags, DifferenceReceiver &r)
{
  return do_compare_layouts (a, 0, b, 0, flags, r);
}

bool
compare_layouts (const db::Layout &a, db::cell_index_type top_a, const db::Layout &b, db::cell_index_type top_b, unsigned int flags, DifferenceReceiver &r)
{
  return do_compare_layouts (a, &a.cell (top_a), b, &b.cell (top_b), flags, r);
}

// -------------------------------------------------------------------------------
//  Declaration and implementation of a printing diff receiver

class PrintingDifferenceReceiver
  : public DifferenceReceiver
{
public:
  PrintingDifferenceReceiver ();
  virtual ~PrintingDifferenceReceiver () { }

  void dbu_differs (double dbu_a, double dbu_b);
  void layer_in_a_only (const db::LayerProperties &la);
  void layer_in_b_only (const db::LayerProperties &lb);
  void layer_name_differs (const db::LayerProperties &la, const db::LayerProperties &lb);
  void cell_in_a_only (const std::string &cellname, db::cell_index_type ci);
  void cell_in_b_only (const std::string &cellname, db::cell_index_type ci);
  void cell_name_differs (const std::string &cellname_a, db::cell_index_type cia, const std::string &cellname_b, db::cell_index_type cib);
  void begin_cell (const std::string &cellname, db::cell_index_type cia, db::cell_index_type cib);
  void bbox_differs (const db::Box &ba, const db::Box &bb);
  void begin_inst_differences ();
  void instances_in_a (const std::vector <db::CellInstArrayWithProperties> &insts_a, const std::vector <std::string> &cell_names, const db::PropertiesRepository &props);
  void instances_in_b (const std::vector <db::CellInstArrayWithProperties> &insts_b, const std::vector <std::string> &cell_names, const db::PropertiesRepository &props);
  void instances_in_a_only (const std::vector <db::CellInstArrayWithProperties> &anotb, const db::Layout &a);
  void instances_in_b_only (const std::vector <db::CellInstArrayWithProperties> &bnota, const db::Layout &b);
  void end_inst_differences ();
  void begin_layer (const db::LayerProperties &layer, unsigned int layer_index_a, bool is_valid_a, unsigned int layer_index_b, bool is_valid_b);
  void per_layer_bbox_differs (const db::Box &ba, const db::Box &bb);
  void begin_polygon_differences ();
  void detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Polygon, db::properties_id_type> > &a, const std::vector <std::pair <db::Polygon, db::properties_id_type> > &b);
  void end_polygon_differences ();
  void begin_path_differences ();
  void detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Path, db::properties_id_type> > &a, const std::vector <std::pair <db::Path, db::properties_id_type> > &b);
  void end_path_differences ();
  void begin_box_differences ();
  void detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Box, db::properties_id_type> > &a, const std::vector <std::pair <db::Box, db::properties_id_type> > &b);
  void end_box_differences ();
  void begin_edge_differences ();
  void detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Edge, db::properties_id_type> > &a, const std::vector <std::pair <db::Edge, db::properties_id_type> > &b);
  void end_edge_differences ();
  void begin_text_differences ();
  void detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Text, db::properties_id_type> > &a, const std::vector <std::pair <db::Text, db::properties_id_type> > &b);
  void end_text_differences ();
  void end_layer ();
  void end_cell ();

private:
  std::string m_cellname;
  db::LayerProperties m_layer;

  void print_cell_inst (const db::CellInstArrayWithProperties &ci, const std::vector <std::string> &cell_names);
  void print_cell_inst (const db::CellInstArrayWithProperties &ci, const db::Layout &l);
  template <class SH> void print_diffs (const db::PropertiesRepository &pr, const std::vector <std::pair <SH, db::properties_id_type> > &a, const std::vector <std::pair <SH, db::properties_id_type> > &b);
};

PrintingDifferenceReceiver::PrintingDifferenceReceiver ()
  : m_cellname (), m_layer ()
{
  // .. nothing yet ..
}

void 
PrintingDifferenceReceiver::print_cell_inst (const db::CellInstArrayWithProperties &ci, const db::Layout &l)
{
  tl::info << "  " << l.cell_name (ci.object ().cell_index ()) << " " << ci.complex_trans ().to_string () << tl::noendl;

  db::Point a, b;
  unsigned long amax, bmax;
  if (ci.is_regular_array (a, b, amax, bmax)) {
    tl::info << "[a=" << a.to_string () << ", b=" << b.to_string () << ", na=" << amax << ", nb=" << bmax << "]" << tl::noendl;
  } else {
    tl::info << "" << tl::noendl;
  }
  if (ci.properties_id () != 0) {
    tl::info << " [" << ci.properties_id () << "]";
    /*  to print the properties themselves:
    const db::PropertiesRepository::properties_set &props = pr.properties (ci.properties_id ());
    for (db::PropertiesRepository::properties_set::const_iterator p = props.begin (); p != props.end (); ++p) {
      const tl::Variant &name = pr.prop_name (p->first);
      if (name.is_long ()) {
        tl::info << "  {" << int (name.to_long ()) << " {" << p->second.to_string () << "}}";
      } else if (name.is_string ()) {
        tl::info << "  {{" << name.to_string () << "} {" << p->second.to_string () << "}}";
      }
    }
    tl::info << "}";
    */
  } else {
    tl::info << "";
  }
}

void 
PrintingDifferenceReceiver::print_cell_inst (const db::CellInstArrayWithProperties &ci, const std::vector <std::string> &cell_names)
{
  tl::info << "  " << cell_names [ci.object ().cell_index ()] << " " << ci.complex_trans ().to_string () << tl::noendl;

  db::Point a, b;
  unsigned long amax, bmax;
  if (ci.is_regular_array (a, b, amax, bmax)) {
    tl::info << "[a=" << a.to_string () << ", b=" << b.to_string () << ", na=" << amax << ", nb=" << bmax << "]" << tl::noendl;
  } else {
    tl::info << "" << tl::noendl;
  }
  if (ci.properties_id () != 0) {
    tl::info << " [" << ci.properties_id () << "]";
    /*  to print the properties themselves:
    const db::PropertiesRepository::properties_set &props = pr.properties (ci.properties_id ());
    for (db::PropertiesRepository::properties_set::const_iterator p = props.begin (); p != props.end (); ++p) {
      const tl::Variant &name = pr.prop_name (p->first);
      if (name.is_long ()) {
        tl::info << "  {" << int (name.to_long ()) << " {" << p->second.to_string () << "}}";
      } else if (name.is_string ()) {
        tl::info << "  {{" << name.to_string () << "} {" << p->second.to_string () << "}}";
      }
    }
    tl::info << "}";
    */
  } else {
    tl::info << "";
  }
}

template <class SH>
void
PrintingDifferenceReceiver::print_diffs (const db::PropertiesRepository &pr, const std::vector <std::pair <SH, db::properties_id_type> > &a, const std::vector <std::pair <SH, db::properties_id_type> > &b)
{
  std::vector <std::pair <SH, db::properties_id_type> > anotb;
  std::set_difference (a.begin (), a.end (), b.begin (), b.end (), std::back_inserter (anotb));
  for (typename std::vector <std::pair <SH, db::properties_id_type> >::const_iterator s = anotb.begin (); s != anotb.end (); ++s) {
    tl::info << "  " << s->first.to_string () << tl::noendl;
    if (s->second != 0) {
      tl::info << " [" << s->second << "]";
      /*  to print the properties themselves:
      const db::PropertiesRepository::properties_set &props = pr.properties (s->second);
      for (db::PropertiesRepository::properties_set::const_iterator p = props.begin (); p != props.end (); ++p) {
        const tl::Variant &name = pr.prop_name (p->first);
        if (name.is_long ()) {
          tl::info << "  {" << int (name.to_long ()) << " {" << p->second.to_string () << "}}";
        } else if (name.is_string ()) {
          tl::info << "  {{" << name.to_string () << "} {" << p->second.to_string () << "}}";
        }
      }
      tl::info << "}";
      */
    } else {
      tl::info << "";
    }
  }
}

void
PrintingDifferenceReceiver::dbu_differs (double dbu_a, double dbu_b) 
{
  tl::error << "layout_diff: database units differ " << dbu_a << " vs. " << dbu_b;
}

void 
PrintingDifferenceReceiver::layer_in_a_only (const db::LayerProperties &la)
{
  tl::error << "layout_diff: layer " << la.to_string () << " is not present in layout b, but in a";
}

void 
PrintingDifferenceReceiver::layer_in_b_only (const db::LayerProperties &lb)
{
  tl::error << "layout_diff: layer " << lb.to_string () << " is not present in layout a, but in b";
}

void
PrintingDifferenceReceiver::layer_name_differs (const db::LayerProperties &la, const db::LayerProperties &lb)
{
  tl::error << "layout_diff: layer names differ between layout a and b for layer " << la.layer << "/" << la.datatype << ": " 
            << la.name << " vs. " << lb.name;
}

void 
PrintingDifferenceReceiver::cell_in_a_only (const std::string &cellname, db::cell_index_type ci)
{
  tl::error << "layout_diff: cell " << cellname << " is not present in layout b, but in a";
}

void 
PrintingDifferenceReceiver::cell_in_b_only (const std::string &cellname, db::cell_index_type ci)
{
  tl::error << "layout_diff: cell " << cellname << " is not present in layout a, but in b";
}

void 
PrintingDifferenceReceiver::cell_name_differs (const std::string &cellname_a, db::cell_index_type cia, const std::string &cellname_b, db::cell_index_type cib)
{
  tl::error << "layout_diff: cell " << cellname_a << " in a is renamed to " << cellname_b << " in b";
}

void 
PrintingDifferenceReceiver::bbox_differs (const db::Box &ba, const db::Box &bb)
{
  tl::error << "layout_diff: bounding boxes differ for cell " << m_cellname << ", " << ba.to_string () << " vs. " << bb.to_string ();
}

void 
PrintingDifferenceReceiver::begin_cell (const std::string &cellname, db::cell_index_type cia, db::cell_index_type cib)
{
  m_cellname = cellname;
}

void
PrintingDifferenceReceiver::begin_inst_differences ()
{
  tl::error << "layout_diff: instances differ in cell " << m_cellname;
}

void
PrintingDifferenceReceiver::instances_in_a (const std::vector <db::CellInstArrayWithProperties> &insts_a, const std::vector <std::string> &cell_names, const db::PropertiesRepository &props)
{
  tl::info << "list for a:";
  for (std::vector <db::CellInstArrayWithProperties>::const_iterator s = insts_a.begin (); s != insts_a.end (); ++s) {
    print_cell_inst (*s, cell_names);
  }
}

void
PrintingDifferenceReceiver::instances_in_b (const std::vector <db::CellInstArrayWithProperties> &insts_b, const std::vector <std::string> &cell_names, const db::PropertiesRepository &props)
{
  tl::info << "list for b:";
  for (std::vector <db::CellInstArrayWithProperties>::const_iterator s = insts_b.begin (); s != insts_b.end (); ++s) {
    print_cell_inst (*s, cell_names);
  }
}

void
PrintingDifferenceReceiver::instances_in_a_only (const std::vector <db::CellInstArrayWithProperties> &anotb, const db::Layout &a)
{
  tl::info << "Not in b but in a:";
  for (std::vector <db::CellInstArrayWithProperties>::const_iterator s = anotb.begin (); s != anotb.end (); ++s) {
    print_cell_inst (*s, a);
  }
}

void
PrintingDifferenceReceiver::instances_in_b_only (const std::vector <db::CellInstArrayWithProperties> &bnota, const db::Layout &b)
{
  tl::info << "Not in a but in b:";
  for (std::vector <db::CellInstArrayWithProperties>::const_iterator s = bnota.begin (); s != bnota.end (); ++s) {
    print_cell_inst (*s, b);
  }
}

void
PrintingDifferenceReceiver::end_inst_differences ()
{
}

void
PrintingDifferenceReceiver::begin_layer (const db::LayerProperties &layer, unsigned int layer_index_a, bool is_valid_a, unsigned int layer_index_b, bool is_valid_b)
{
  m_layer = layer;
}

void 
PrintingDifferenceReceiver::per_layer_bbox_differs (const db::Box &ba, const db::Box &bb)
{
  tl::error << "layout_diff: per-layer bounding boxes differ for cell " << m_cellname << ", layer (" << m_layer.to_string () << "), " 
            << ba.to_string () << " vs. " << bb.to_string ();
}

void
PrintingDifferenceReceiver::begin_polygon_differences ()
{
  tl::error << "layout_diff: polygons differ for layer " << m_layer.to_string () << " in cell " << m_cellname;
}

void
PrintingDifferenceReceiver::detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Polygon, db::properties_id_type> > &a, const std::vector <std::pair <db::Polygon, db::properties_id_type> > &b)
{
  tl::info << "Not in b but in a:";
  print_diffs (pr, a, b);
  tl::info << "Not in a but in b:";
  print_diffs (pr, b, a);
}

void
PrintingDifferenceReceiver::end_polygon_differences ()
{
}

void
PrintingDifferenceReceiver::begin_path_differences ()
{
  tl::error << "layout_diff: paths differ for layer " << m_layer.to_string () << " in cell " << m_cellname;
}

void
PrintingDifferenceReceiver::detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Path, db::properties_id_type> > &a, const std::vector <std::pair <db::Path, db::properties_id_type> > &b)
{
  tl::info << "Not in b but in a:";
  print_diffs (pr, a, b);
  tl::info << "Not in a but in b:";
  print_diffs (pr, b, a);
}

void
PrintingDifferenceReceiver::end_path_differences ()
{
}

void
PrintingDifferenceReceiver::begin_box_differences ()
{
  tl::error << "layout_diff: boxes differ for layer " << m_layer.to_string () << " in cell " << m_cellname;
}

void
PrintingDifferenceReceiver::detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Box, db::properties_id_type> > &a, const std::vector <std::pair <db::Box, db::properties_id_type> > &b)
{
  tl::info << "Not in b but in a:";
  print_diffs (pr, a, b);
  tl::info << "Not in a but in b:";
  print_diffs (pr, b, a);
}

void
PrintingDifferenceReceiver::end_box_differences ()
{
}

void
PrintingDifferenceReceiver::begin_edge_differences ()
{
  tl::error << "layout_diff: edges differ for layer " << m_layer.to_string () << " in cell " << m_cellname;
}

void
PrintingDifferenceReceiver::detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Edge, db::properties_id_type> > &a, const std::vector <std::pair <db::Edge, db::properties_id_type> > &b)
{
  tl::info << "Not in b but in a:";
  print_diffs (pr, a, b);
  tl::info << "Not in a but in b:";
  print_diffs (pr, b, a);
}

void
PrintingDifferenceReceiver::end_edge_differences ()
{
}

void
PrintingDifferenceReceiver::begin_text_differences ()
{
  tl::error << "layout_diff: texts differ for layer " << m_layer.to_string () << " in cell " << m_cellname;
}

void
PrintingDifferenceReceiver::detailed_diff (const db::PropertiesRepository &pr, const std::vector <std::pair <db::Text, db::properties_id_type> > &a, const std::vector <std::pair <db::Text, db::properties_id_type> > &b)
{
  tl::info << "Not in b but in a:";
  print_diffs (pr, a, b);
  tl::info << "Not in a but in b:";
  print_diffs (pr, b, a);
}

void
PrintingDifferenceReceiver::end_text_differences ()
{
}

void
PrintingDifferenceReceiver::end_layer ()
{
}

void 
PrintingDifferenceReceiver::end_cell ()
{
}

// -------------------------------------------------------------------------------
//  Implementation of a printing diff 

bool
compare_layouts (const db::Layout &a, const db::Layout &b, unsigned int flags)
{
  PrintingDifferenceReceiver r;
  return compare_layouts (a, b, flags, r);
}

}

