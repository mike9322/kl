
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



#include "dbDXFReader.h"
#include "dbStream.h"
#include "dbObjectWithProperties.h"
#include "dbArray.h"
#include "dbStatic.h"
#include "dbRecursiveShapeIterator.h"
#include "dbEdgeProcessor.h"
#include "dbEdgesToContours.h"

#include "tlException.h"
#include "tlString.h"
#include "tlUtils.h"
#include "tlClassRegistry.h"

#include <cctype>
#include <set>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QPolygon>
#include <QtGui/QPainterPath>

namespace db
{

// ---------------------------------------------------------------
//  DXFReader

static std::string zero_layer_name ("0");

DXFReader::DXFReader (tl::InputStream &s)
  : m_stream (s),
    m_read_texts (true), m_create_layers (true),
    m_progress (tl::to_string (QObject::tr ("Reading DXF file")), 1000),
    m_dbu (0.001), m_unit (1.0), m_text_scaling (1.0), m_polyline_mode (0), m_circle_points (100),
    m_ascii (false), m_initial (true), m_render_texts_as_polygons (false), m_keep_other_cells (false), m_line_number (0),
    m_zero_layer (0), m_next_layer_index (0)
{
  m_progress.set_format (tl::to_string (QObject::tr ("%.0fk lines")));
  m_progress.set_format_unit (1000.0);
  m_progress.set_unit (100000.0);
}

DXFReader::~DXFReader ()
{
  //  .. nothing yet ..
}

void 
DXFReader::check_coord (double x)
{
  //  Note: we stay on the safe side by dropping one bit (*0.5)
  if (x < std::numeric_limits <db::Coord>::min () * 0.5 ||
      x > std::numeric_limits <db::Coord>::max () * 0.5) {
    error (tl::to_string (QObject::tr ("Coordinate value overflow")));
  }
}

void 
DXFReader::check_point (const db::DPoint &p)
{
  check_coord (p.x ());
  check_coord (p.y ());
}

db::Polygon 
DXFReader::safe_from_double (const db::DPolygon &p)
{
  for (db::DPolygon::polygon_contour_iterator q = p.begin_hull (); q != p.end_hull (); ++q) {
    check_point (*q);
  }
  for (unsigned int h = 0; h < p.holes (); ++h) {
    for (db::DPolygon::polygon_contour_iterator q = p.begin_hole (h); q != p.end_hole (h); ++q) {
      check_point (*q);
    }
  }
  return db::Polygon::from_double (p);
}

db::SimplePolygon 
DXFReader::safe_from_double (const db::DSimplePolygon &p)
{
  for (db::DPolygon::polygon_contour_iterator q = p.begin_hull (); q != p.end_hull (); ++q) {
    check_point (*q);
  }
  return db::SimplePolygon::from_double (p);
}

db::Text 
DXFReader::safe_from_double (const db::DText &p)
{
  check_point (p.trans ().disp ());
  check_coord (p.size ());
  return db::Text::from_double (p);
}

db::Path 
DXFReader::safe_from_double (const db::DPath &p)
{
  for (db::DPath::iterator q = p.begin (); q != p.end (); ++q) {
    check_point (*q);
  }
  check_coord (p.width ());
  check_coord (p.bgn_ext ());
  check_coord (p.end_ext ());
  return db::Path::from_double (p);
}

db::Point 
DXFReader::safe_from_double (const db::DPoint &p)
{
  check_point (p);
  return db::Point::from_double (p);
}

db::Edge 
DXFReader::safe_from_double (const db::DEdge &p)
{
  check_point (p.p1 ());
  check_point (p.p2 ());
  return db::Edge::from_double (p);
}

db::Box 
DXFReader::safe_from_double (const db::DBox &p)
{
  check_point (p.p1 ());
  check_point (p.p2 ());
  return db::Box::from_double (p);
}

void
DXFReader::parse_entity (const std::string &entity_code, size_t &nsolids, size_t &closed_polylines)
{
  int g;

  if (entity_code == "HATCH" || entity_code == "SOLID") {
    ++nsolids;
    while ((g = read_group_code ()) != 0) {
      skip_value (g);
    }
  } else if (entity_code == "POLYLINE" || entity_code == "LWPOLYLINE") {
    while ((g = read_group_code ()) != 0) {
      if (g == 70) {
        int flags = read_int16 ();
        if ((flags & 1) != 0) {
          ++closed_polylines;
        }
      } else {
        skip_value (g);
      }
    }
  } else {
    while ((g = read_group_code ()) != 0) {
      skip_value (g);
    }
  }
}

int 
DXFReader::determine_polyline_mode ()
{
  m_initial = true;
  m_line_number = 0;

  size_t nsolids = 0;
  size_t closed_polylines = 0;

  // Read sections
  int g;

  while (true) {

    while ((g = read_group_code()) != 0) {
      skip_value (g);
    }

    const std::string &name = read_string (true);
    if (name == "EOF") {

      break;

    } else if (name == "SECTION") {

      while ((g = read_group_code()) != 2) {
        skip_value (g);
      }

      const std::string &section_name = read_string (true);
      if (section_name == "BLOCKS") {

        while (true) {

          while ((g = read_group_code()) != 0) {
            skip_value (g);
          }

          const std::string &entity = read_string (true);
          if (entity == "BLOCK") {

            while ((g = read_group_code ()) != 0) {
              skip_value (g);
            }

            while (true) {
              const std::string &entity_code = read_string (true);
              if (entity_code == "ENDBLK") {
                break;
              } else {
                parse_entity (entity_code, nsolids, closed_polylines);
              } 
            }

          } else if (entity == "ENDSEC") {
            break;
          }

        }

      } else if (section_name == "ENTITIES") {

        while ((g = read_group_code ()) != 0) {
          skip_value (g);
        }

        while (true) {
          const std::string &entity_code = read_string (true);
          if (entity_code == "ENDSEC") {
            break;
          } else {
            parse_entity (entity_code, nsolids, closed_polylines);
          } 
        }


      }

    }

  }

  //  if at least one "solid style" entity is found, create lines from polylines. Otherwise create polygons from closed polylines.
  if (nsolids > 0) {
    return 1; // solid mode
  } else if (closed_polylines > 0) {
    return 2; // polyline to polygon mode
  } else {
    return 3; // merge lines mode
  }
}

const LayerMap &
DXFReader::read (db::Layout &layout, const db::LoadLayoutOptions &options)
{
  m_dbu = 0.001;
  m_unit = 1.0;
  m_polyline_mode = 0;
  m_circle_points = 100;
  m_text_scaling = 100.0;

  const db::DXFReaderOptions *specific_options = dynamic_cast<const db::DXFReaderOptions *> (options.get_specific_options ("DXF"));
  if (specific_options) {
    m_dbu = specific_options->dbu;
    m_unit = specific_options->unit;
    m_text_scaling = specific_options->text_scaling;
    m_polyline_mode = specific_options->polyline_mode;
    m_circle_points = specific_options->circle_points;
    m_render_texts_as_polygons = specific_options->render_texts_as_polygons;
    m_keep_other_cells = specific_options->keep_other_cells;
  }

  if (m_polyline_mode == 0 /*auto mode*/) {
    m_polyline_mode = determine_polyline_mode ();
    if (m_polyline_mode == 3) {
      tl::log << tl::to_string (QObject::tr ("Automatic polyline mode: merge lines with width = 0 into polygons"));
    } else if (m_polyline_mode == 2) {
      tl::log << tl::to_string (QObject::tr ("Automatic polyline mode: create polygons from closed polylines with width = 0"));
    } else if (m_polyline_mode == 1) {
      tl::log << tl::to_string (QObject::tr ("Automatic polyline mode: keep lines, make polygons from solid and hatch entities"));
    }
  }

  m_stream.reset ();
  m_initial = true;
  m_line_number = 0;
  m_layer_map = options.layer_map ();
  m_layer_map.prepare (layout);
  m_next_layer_index = 0;
  m_read_texts = options.enable_text_objects ();
  m_create_layers = options.create_other_layers ();

  db::cell_index_type top = layout.add_cell("TOP"); // TODO: make variable ..

  layout.dbu (m_dbu);
  do_read (layout, top);
  cleanup (layout, top);

  return m_layer_map;
}

const LayerMap &
DXFReader::read (db::Layout &layout)
{
  return read (layout, db::LoadLayoutOptions ());
}

void 
DXFReader::error (const std::string &msg)
{
  if (m_ascii) {
    throw DXFReaderException (msg, m_line_number, m_cellname);
  } else {
    throw DXFReaderException (msg, m_stream.pos (), m_cellname);
  }
}

void 
DXFReader::warn (const std::string &msg) 
{
  // TODO: compress
  if (m_ascii) {
    tl::warn << msg 
             << tl::to_string (QObject::tr (" (line=")) << m_line_number
             << tl::to_string (QObject::tr (", cell=")) << m_cellname
             << ")";
  } else {
    tl::warn << msg 
             << tl::to_string (QObject::tr (" (position=")) << m_stream.pos ()
             << tl::to_string (QObject::tr (", cell=")) << m_cellname
             << ")";
  }
}

static bool 
extract_plain_layer (const char *s, int &l)
{
  l = 0;
  if (! *s) {
    return false;
  }
  while (*s && isdigit (*s)) {
    l = l * 10 + (unsigned int) (*s - '0');
    ++s;
  }
  return (*s == 0);
}

static bool 
extract_ld (const char *s, int &l, int &d, std::string &n)
{
  l = d = 0;

  if (*s == 'L') {
    ++s;
  }

  if (! *s || ! isdigit (*s)) {
    return false;
  }

  while (*s && isdigit (*s)) {
    l = l * 10 + (unsigned int) (*s - '0');
    ++s;
  }

  if (*s == 'D' || *s == '.') {
    ++s;
    if (! *s || ! isdigit (*s)) {
      return false;
    }
    while (*s && isdigit (*s)) {
      d = d * 10 + (unsigned int) (*s - '0');
      ++s;
    }
  }

  if (*s && (isspace (*s) || *s == '_')) {
    ++s;
    n = s;
    return true;
  } else if (*s == 0) {
    n.clear ();
    return true;
  } else {
    return false;
  }
}

std::pair <bool, unsigned int> 
DXFReader::open_layer (db::Layout &layout, const std::string &n)
{
  std::string name (n);

  int l = -1, d = -1;
  std::string on;

  std::pair<bool, unsigned int> ll (false, 0);

  if (n == zero_layer_name) {
    return std::make_pair (true, m_zero_layer);
  }

  ll = m_layer_map.logical (n);
  if (! ll.first) {

    if (extract_plain_layer (n.c_str (), l)) {

      db::LayerProperties lp;
      lp.layer = l;
      lp.datatype = 0;
      ll = m_layer_map.logical (lp);

    } else if (extract_ld (n.c_str (), l, d, on)) {

      db::LayerProperties lp;
      lp.layer = l;
      lp.datatype = d;
      lp.name = on;
      ll = m_layer_map.logical (lp);

    }

  }

  if (ll.first) {

    //  create the layer if it is not part of the layout yet.
    if (! layout.is_valid_layer (ll.second)) {
      layout.insert_layer (ll.second, m_layer_map.mapping (ll.second));
    }

    return ll;

  } else if (! m_create_layers) {

    return std::pair<bool, unsigned int> (false, 0);

  } else {

    std::map <std::string, unsigned int>::const_iterator nl = m_new_layers.find (n);
    if (nl == m_new_layers.end ()) {

      unsigned int ll = m_next_layer_index++;

      layout.insert_layer (ll, db::LayerProperties ());
      m_new_layers.insert (std::make_pair (n, ll));

      return std::pair<bool, unsigned int> (true, ll);

    } else {
      return std::pair<bool, unsigned int> (true, nl->second);
    }

  }
}

void 
DXFReader::do_read (db::Layout &layout, db::cell_index_type top)
{
  m_new_layers.clear ();

  //  create the zero layer - this is not mapped to GDS but can be specified in the layer mapping as
  //  a layer named "0".
  std::pair<bool, unsigned int> ll = m_layer_map.logical (zero_layer_name);
  if (ll.first) {

    //  create the layer if it is not part of the layout yet.
    if (! layout.is_valid_layer (ll.second)) {
      layout.insert_layer (ll.second, m_layer_map.mapping (ll.second));
    }

    m_zero_layer = ll.second;

  } else {

    //  or explicitly create the layer:
    m_zero_layer = m_layer_map.next_index ();
    layout.insert_layer (m_zero_layer, db::LayerProperties (0, 0, zero_layer_name));
    m_layer_map.map (zero_layer_name, m_zero_layer);

  }

  m_next_layer_index = m_layer_map.next_index ();

  // Read sections
  int g;

  while (true) {

    while ((g = read_group_code()) != 0) {
      skip_value (g);
    }

    const std::string &name = read_string (true);
    if (name == "EOF") {

      break;

    } else if (name == "SECTION") {

      while ((g = read_group_code()) != 2) {
        skip_value (g);
      }

      const std::string &section_name = read_string (true);
      if (section_name == "BLOCKS") {

        while (true) {

          while ((g = read_group_code()) != 0) {
            skip_value (g);
          }

          const std::string &entity = read_string (true);
          if (entity == "BLOCK") {
            read_cell (layout);
          } else if (entity == "ENDSEC") {
            break;
          }

        }

      } else if (section_name == "TABLES") {

        while (true) {

          while ((g = read_group_code ()) != 0) {
            skip_value (g);
          }

          const std::string &entity = read_string (true);
          if (entity == "TABLE") {

            while ((g = read_group_code ()) != 0) {
              if (g == 2) {
                break;
              }
              skip_value (g);
            }

            if (g == 2) {

              std::string table_name = read_string (true);
              if (table_name == "LAYER") {

                while (true) {

                  while ((g = read_group_code ()) != 0) {
                    if (g == 2) {
                      std::string layer_name = read_string (true);
                      open_layer (layout, layer_name);
                    } else {
                      skip_value (g);
                    }
                  }

                  if (read_string (true) == "ENDTAB") {
                    break;
                  }

                }

              }

            }

          } else if (entity == "ENDSEC") {
            break;
          }

        }

      } else if (section_name == "ENTITIES") {

        //  skip groups to first entity (consume the group code for this one)
        int g;
        while ((g = read_group_code ()) != 0) {
          skip_value (g);
        }

        read_entities (layout, layout.cell (top), db::DPoint (0.0, 0.0));

      } else {

        do {
          while ((g = read_group_code ()) != 0) {
            skip_value (g);
          }
        } while (read_string (true) != "ENDSEC");

      }

    }

  }

  //  assign layer numbers to new layers
  if (! m_new_layers.empty ()) {

    std::set<std::pair<int, int> > used_ld;
    for (db::Layout::layer_iterator l = layout.begin_layers (); l != layout.end_layers (); ++l) {
      used_ld.insert (std::make_pair((*l).second->layer, (*l).second->datatype));
    }

    //  assign fixed layer numbers for all layers whose name is a fixed number unless there is already a layer with that number
    for (std::map<std::string, unsigned int>::iterator i = m_new_layers.begin (); i != m_new_layers.end (); ) {

      std::map<std::string, unsigned int>::iterator ii = i;
      ++ii;

      int l = -1;
      if (extract_plain_layer (i->first.c_str (), l) && used_ld.find (std::make_pair (l, 0)) == used_ld.end ()) {

        used_ld.insert (std::make_pair (l, 0));

        db::LayerProperties lp;
        lp.layer = l;
        lp.datatype = 0;
        layout.set_properties (i->second, lp);
        m_layer_map.map (lp, i->second);

        m_new_layers.erase (i);

      }

      i = ii;

    }
    
    //  assign fixed layer numbers for all layers whose name is a LxDy or Lx notation unless there is already a layer with that layer/datatype
    for (std::map<std::string, unsigned int>::iterator i = m_new_layers.begin (); i != m_new_layers.end (); ) {

      std::map<std::string, unsigned int>::iterator ii = i;
      ++ii;

      int l = -1, d = -1;
      std::string n;

      if (extract_ld (i->first.c_str (), l, d, n) && used_ld.find (std::make_pair (l, d)) == used_ld.end ()) {

        used_ld.insert (std::make_pair (l, d));

        db::LayerProperties lp;
        lp.layer = l;
        lp.datatype = d;
        lp.name = n;
        layout.set_properties (i->second, lp);
        m_layer_map.map (lp, i->second);

        m_new_layers.erase (i);

      }

      i = ii;

    }

    //  insert the remaining ones
    for (std::map<std::string, unsigned int>::const_iterator i = m_new_layers.begin (); i != m_new_layers.end (); ++i) {
      db::LayerProperties lp;
      lp.name = i->first;
      layout.set_properties (i->second, lp);
      m_layer_map.map (lp, i->second);
    }

  }
}

void
DXFReader::cleanup (db::Layout &layout, db::cell_index_type top_cell)
{
  std::vector <db::cell_index_type> cells_to_delete;

  do
  {
    cells_to_delete.clear ();

    //  remove all cells which are not used except for the top cell
    for (db::Layout::const_iterator c = layout.begin (); c != layout.end (); ++c) {
      if ((! m_keep_other_cells || m_used_template_cells.find (c->cell_index ()) != m_used_template_cells.end ()) && c->is_top () && c->cell_index () != top_cell) {
        cells_to_delete.push_back (c->cell_index ());
      }
    }

    //  it's more efficient to remove the cells afterwards because is_top requires an updated hierarchy
    for (std::vector <db::cell_index_type>::const_iterator c = cells_to_delete.begin (); c != cells_to_delete.end (); ++c) {
      layout.delete_cell (*c);
    }

    //  deleting cells can make other cells "top", thus we iterate

  } while (!cells_to_delete.empty ());

  //  rename the remaining cells
  for (std::map <std::string, db::cell_index_type>::const_iterator b = m_block_per_name.begin (); b != m_block_per_name.end (); ++b) {
    if (layout.is_valid_cell_index (b->second)) {
      layout.rename_cell (b->second, layout.uniquify_cell_name (b->first.c_str ()).c_str ());
    }
  }

  m_template_cells.clear ();
  m_used_template_cells.clear ();
  m_block_per_name.clear ();
}

void
DXFReader::read_cell (db::Layout &layout)
{
  std::string cell_name;
  double xoff = 0.0, yoff = 0.0;

  int g;
  while ((g = read_group_code ()) != 0) {
    if (g == 2) {
      cell_name = read_string (true);
    } else if (g == 10) {
      xoff = read_double ();
    } else if (g == 20) {
      yoff = read_double ();
    } else {
      skip_value (g);
    }
  }

  std::map <std::string, db::cell_index_type>::const_iterator b = m_block_per_name.find (cell_name);
  if (b == m_block_per_name.end ()) {
          
    //  create a first representative. Later, layer variants are built
    db::cell_index_type cell = layout.add_cell ();
    m_block_per_name.insert (std::make_pair (cell_name, cell));
    m_template_cells.insert (cell);
    read_entities (layout, layout.cell (cell), db::DPoint (-xoff, -yoff));

  } else {

    //  read the entities and create all layer variants required so far.
    read_entities (layout, layout.cell (b->second), db::DPoint (-xoff, -yoff));

    for (std::map <VariantKey, db::cell_index_type>::const_iterator b2l = m_block_to_variant.begin (); b2l != m_block_to_variant.end (); ++b2l) {
      if (b2l->first.cell_index == b->second) {
        fill_layer_variant_cell (layout, cell_name, b->second, b2l->second, b2l->first.layer, b2l->first.sx, b2l->first.sy);
      }
    }

  }
}

void 
DXFReader::fill_layer_variant_cell (db::Layout &layout, const std::string &cellname, db::cell_index_type template_cell, db::cell_index_type var_cell, unsigned int layer, double sx, double sy)
{
  m_used_template_cells.insert (template_cell);

  const db::Cell &src = layout.cell (template_cell);
  db::Cell &target = layout.cell (var_cell);

  //  copy all instances
  for (db::Cell::const_iterator i = src.begin (); ! i.at_end (); ++i) {

    db::CellInstArray cell_inst = i->cell_inst ();

    // replace instances to template cells (those are not layer variants yet). This 
    // achieves a recursive variant building.
    if (m_template_cells.find (cell_inst.object ().cell_index ()) != m_template_cells.end () || fabs (sx - 1.0) > 1e-6 || fabs (sy - 1.0) > 1e-6) {

      db::Trans t = cell_inst.front ();
      t = db::Trans (t.rot (), db::Point::from_double (db::DPoint (t.disp ().x () * sx, t.disp ().y () * sy)));

      bool swap_sxy = ((t.angle () % 2) != 0);
      db::CellInst obj (make_layer_variant (layout, cellname, cell_inst.object ().cell_index (), layer, swap_sxy ? sy : sx, swap_sxy ? sx : sy));

      db::Point a, b;
      unsigned long na = 0, nb = 0;
      if (cell_inst.is_regular_array (a, b, na, nb)) {
        a = db::Point::from_double (db::DPoint (a.x () * sx, a.y () * sy));
        b = db::Point::from_double (db::DPoint (b.x () * sx, b.y () * sy));
        cell_inst = db::CellInstArray (obj, t, a, b, na, nb);
      } else {
        cell_inst = db::CellInstArray (obj, t);
      }

    }

    target.insert (cell_inst);

  }

  if (fabs (sx - 1.0) < 1e-6 && fabs (sy - 1.0) < 1e-6) {

    //  copy the shapes except for the zero layer ... 
    for (db::Layout::layer_iterator l = layout.begin_layers (); l != layout.end_layers (); ++l) {
      if ((*l).first != m_zero_layer || layer == m_zero_layer) {
        target.shapes ((*l).first) = src.shapes ((*l).first);
      }
    }

    //  translate the zero layer shapes to the destination layer
    if (layer != m_zero_layer) {
      db::Shapes &ts = target.shapes (layer);
      for (db::Shapes::shape_iterator s = src.shapes (m_zero_layer).begin (db::Shapes::shape_iterator::All); ! s.at_end (); ++s) {
        ts.insert (*s);
      }
    }

  } else {

    db::Matrix3d m (sx, 0.0, 0.0, sy);

    //  copy the shapes except for the zero layer ... 
    for (db::Layout::layer_iterator l = layout.begin_layers (); l != layout.end_layers (); ++l) {
      if ((*l).first != m_zero_layer || layer == m_zero_layer) {
        for (db::Shapes::shape_iterator s = src.shapes ((*l).first).begin (db::Shapes::shape_iterator::All); ! s.at_end (); ++s) {
          insert_scaled (target.shapes ((*l).first), *s, m);
        }
      }
    }

    //  translate the zero layer shapes to the destination layer
    if (layer != m_zero_layer) {
      db::Shapes &ts = target.shapes (layer);
      for (db::Shapes::shape_iterator s = src.shapes (m_zero_layer).begin (db::Shapes::shape_iterator::All); ! s.at_end (); ++s) {
        insert_scaled (ts, *s, m);
      }
    }

  }
}

void 
DXFReader::insert_scaled (db::Shapes &target, const db::Shape &src, const db::Matrix3d &m)
{
  if (src.is_edge ()) {
    db::Edge e;
    src.edge (e);
    target.insert (safe_from_double (e.transformed (m)));
  } else if (src.is_box ()) {
    db::Box b;
    src.box (b);
    target.insert (safe_from_double (b.transformed (m)));
  } else if (src.is_path () || src.is_polygon ()) {
    db::Polygon p;
    src.polygon (p);
    target.insert (safe_from_double (p.transformed (m)));
  } else if (src.is_text ()) {
    db::Text t;
    src.text (t);
    db::Trans tt = t.trans ();
    t.trans (db::Trans (tt.rot (), safe_from_double (tt.disp ().transformed (m))));
    t.size (db::coord_traits<db::Coord>::rounded (t.size () * m.mag_y ()));
    target.insert (t);
  }
}

db::cell_index_type 
DXFReader::make_layer_variant (db::Layout &layout, const std::string &cellname, db::cell_index_type template_cell, unsigned int layer, double sx, double sy)
{
  db::cell_index_type ci;

  //  for the zero layer the variant is equal to the template cell
  if (layer == m_zero_layer && fabs (sx - 1.0) < 1e-6 && fabs (sy - 1.0) < 1e-6) {
    return template_cell;
  }

  std::map <VariantKey, db::cell_index_type>::const_iterator b2l = m_block_to_variant.find (VariantKey (template_cell, layer, sx, sy));
  if (b2l == m_block_to_variant.end ()) {

    //  create a new base layer variant
    ci = layout.add_cell (cellname.c_str ());
    m_block_to_variant.insert (std::make_pair (VariantKey (template_cell, layer, sx, sy), ci));

    fill_layer_variant_cell (layout, cellname, template_cell, ci, layer, sx, sy);

  } else {
    ci = b2l->second;
  }

  return ci;
}

db::DCplxTrans 
DXFReader::global_trans (const db::DPoint &offset, double ex, double ey, double ez)
{
  if (fabs (ex) > 1e-6 || fabs (ey) > 1e-6 || fabs (fabs (ez) - 1.0) > 1e-6) {
    warn ("Only (0,0,1) and (0,0,-1) extrusion directions are supported");
  }

  double f = m_unit / m_dbu;
  if (ez < 0.0) {
    return db::DCplxTrans (f, 180.0, true, offset * f);
  } else {
    return db::DCplxTrans (f, 0.0, false, offset * f);
  }
}

void 
DXFReader::add_bulge_segment (std::vector<db::DPoint> &points, const db::DPoint &p, double b)
{
  if (!points.empty () && fabs (b) > 1e-10) {

    double a = 2.0 * atan (b);

    db::DPoint p0 = points.back ();
    db::DPoint d = p - p0;
    db::DPoint t = db::DPoint (-d.y (), d.x ());
    db::DPoint m = (p0 + d * 0.5) + t * (0.5 / tan (a));

    db::DPoint r = p0 - m;
    db::DPoint s (-r.y (), r.x ());

    int n = int (ceil (m_circle_points * fabs (a) / M_PI));
    double da = 2 * a / std::max (1, n);

    for (int i = 1; i < n; ++i) {
      points.push_back (m + r * cos (da * i) + s * sin (da * i));
    }

  }

  points.push_back (p);
}

static 
double b_func (double t, size_t j, int n, const std::vector<double> &knots)
{
  if (n == 0) {
    return (knots [j] < t - 1e-6 && knots [j + 1] > t - 1e-6) ? 1.0 : 0.0;
  } else {
    double dt1 = knots [j + n] - knots [j];
    double dt2 = knots [j + n + 1] - knots [j + 1];
    double f1 = 0.0;
    if (dt1 > 1e-6) {
      f1 = (t - knots [j]) / dt1;
    }
    double f2 = 0.0;
    if (dt2 > 1e-6) {
      f2 = (knots [j + n + 1] - t) / dt2;
    }
    return f1 * b_func (t, j, n - 1, knots) + f2 * b_func (t, j + 1, n - 1, knots);
  }
}

void
DXFReader::spline_interpolation (std::vector<db::DPoint> &points, int n, const std::vector<double> &knots, bool save_first)
{
  //  TODO: this is quite inefficient
  if (int (knots.size()) != int (points.size() + n + 1)) {
    warn ("Spline interpolation failed: mismatch between number of knots and points");
    return;
  }

  if (int(knots.size ()) <= n || points.empty () || n <= 1) {
    return;
  }

  double t0 = knots [n];
  double tn = knots [knots.size () - n - 1];
  double dt = 1.0 / ceil (m_circle_points * 0.25 - 1e-6);

  std::vector<db::DPoint> new_points;
  if (save_first) {
    new_points.push_back (points.front ());
  }

  for (double t = t0 + dt; t < tn + 1e-6; t += dt) {
    db::DPoint s;
    for (size_t j = 0; j < points.size (); ++j) {
      s += points [j] * b_func (t, j, n, knots);
    }
    new_points.push_back (s);
  }

  points.swap (new_points);
}

void 
DXFReader::elliptic_interpolation (std::vector<db::DPoint> &points, const std::vector<double> &rmin, const std::vector<db::DPoint> &vmaj, const std::vector<double> &start, const std::vector<double> &end, const std::vector<int> &ccw)
{
  if (rmin.size () != points.size () || vmaj.size () != points.size () || start.size () != points.size () || end.size () != points.size () || (!ccw.empty () && ccw.size () != points.size ())) {
    warn ("Elliptic arc interpolation failed: mismatch between number of parameters and points");
    return;
  }

  std::vector<db::DPoint> new_points;

  for (size_t i = 0; i < points.size (); ++i) {

    double sa = start [i], ea = end [i];
    while (ea < sa - 1e-6) {
      ea += 360;
    }

    int n = int (std::max (1.0, floor (0.5 + (ea - sa) * m_circle_points / 360.0)));
    double da = (ea - sa) / n;

    db::DVector vx = vmaj [i];
    db::DVector vy = db::DVector (vx.y (), -vx.x ()) * rmin [i];

    bool ccw_flag = (ccw.empty () || ccw [i]);
    if (ccw_flag) {
      vy = -vy;
    }

    double a = sa;
    for (int j = 0; j < n + 1; ++j) {
      new_points.push_back (points[i] + vx * cos (a * M_PI / 180.0) + vy * sin (a * M_PI / 180.0));
      a += da;
    }

  }

  points.swap (new_points);
}

void
DXFReader::arc_interpolation (std::vector<db::DPoint> &points, const std::vector<double> &rad, const std::vector<double> &start, const std::vector<double> &end, const std::vector<int> &ccw)
{
  if (rad.size () != points.size () || start.size () != points.size () || end.size () != points.size () || (!ccw.empty () && ccw.size () != points.size ())) {
    warn ("Circular arc interpolation failed: mismatch between number of parameters and points");
    return;
  }

  std::vector<db::DPoint> new_points;

  for (size_t i = 0; i < points.size (); ++i) {

    double sa = start [i], ea = end [i];
    while (ea < sa - 1e-6) {
      ea += 360;
    }

    int n = int (std::max (1.0, floor (0.5 + (ea - sa) * m_circle_points / 360.0)));
    double da = (ea - sa) / n;

    db::DVector vx = db::DVector (rad [i], 0.0);
    db::DVector vy = db::DVector (vx.y (), -vx.x ());

    bool ccw_flag = (ccw.empty () || ccw [i]);
    if (ccw_flag) {
      vy = -vy;
    }

    double a = sa;
    for (int j = 0; j < n + 1; ++j) {
      new_points.push_back (points[i] + vx * cos (a * M_PI / 180.0) + vy * sin (a * M_PI / 180.0));
      a += da;
    }

  }

  points.swap (new_points);
}

void
DXFReader::deliver_points_to_edges (std::vector<db::DPoint> &points, const std::vector<db::DPoint> &points2, const db::DCplxTrans &tt, int edge_type, int value94, const std::vector<double> &value40, const std::vector<double> &value50, const std::vector<double> &value51, const std::vector<int> &value73, std::vector<db::Edge> &iedges)
{
  if (points.empty ()) {
    return;
  }

  if (edge_type == 4) {

    spline_interpolation (points, value94, value40);

  } else if (edge_type == 1) {

    if (points.size () != points2.size ()) {
      warn ("Line interpolation failed: mismatch between number of points");
      return;
    }

    std::vector<db::DPoint> points1;
    points1.swap (points);

    points.reserve (points1.size () + points2.size ());
    for (size_t i = 0; i < points1.size (); ++i) {
      points.push_back (points1 [i]);
      points.push_back (points2 [i]);
    }

  } else if (edge_type == 2) {

    arc_interpolation (points, value40, value50, value51, value73);

  } else if (edge_type == 3) {

    elliptic_interpolation (points, value40, points2, value50, value51, value73);

  }

  //  produce the edges. If cont is true, continue with the previous edge
  if (! points.empty ()) {
    db::Point pl = safe_from_double (tt * points.front ());
    for (std::vector<db::DPoint>::const_iterator p = points.begin () + 1; p != points.end (); ++p) {
      db::Edge ie (pl, safe_from_double (tt * *p));
      if (! ie.is_degenerate ()) {
        iedges.push_back (ie);
      }
      pl = ie.p2 ();
    }
  }
}

/**
 *  @brief Adds closing edges to the loop
 *  For this we look for edges not having a connecting edge and insert edges to the nearest points.
 */
static void 
finish_loop (size_t from, size_t to, std::vector<db::Edge> &edges)
{
  std::multiset<db::Point> p1;
  for (size_t i = from; i < to; ++i) {
    p1.insert (edges [i].p1 ());
  }

  for (size_t i = from; i < to; ++i) {

    db::Point pi2 = edges [i].p2 ();

    std::multiset<db::Point>::iterator ip1 = p1.find (pi2);
    if (ip1 != p1.end ()) {

      p1.erase (ip1);

    } else {

      //  search for the nearest point to connect to

      db::Point p1min = edges [i].p1 ();
      std::multiset<db::Point>::iterator ip1min = p1.end ();

      double d = -1.0;
      for (size_t j = from; j < to; ++j) {
        db::Point pj1 = edges [j].p1 ();
        double dd = pj1.sq_double_distance (pi2);
        if (j != i && (d < 0.0 || dd < d) && (ip1 = p1.find (pj1)) != p1.end ()) {
          ip1min = ip1;
          p1min = pj1;
          d = dd;
        }
      }

      if (ip1min != p1.end ()) {
        p1.erase (ip1min);
      }

      edges.push_back (db::Edge (pi2, p1min));

    }

  }
}

static std::string
normalize_string (const std::string &in, bool for_mtext)
{
  /*
    Note: MTEXT's have some embedded formatting options.
    These are some options taken from http://www.cadforum.cz/forum_en/forum_posts.asp?TID=5178:
    \O...\o        Turns overline on and off
    \L...\l        Turns underline on and off
    \~             Inserts a nonbreaking space
    \\             Inserts a backslash
    \{...\}        Inserts an opening and closing brace
    \File name;    Changes to the specified font file
    \Hvalue;       Changes to the text height specified in drawing units
    \Hvaluex;      Changes the text height to a multiple of the current text height
    \S...^...;     Stacks the subsequent text at the \, #, or ^ symbol
    \Tvalue;       Adjusts the space between characters, from.75 to 4 times
    \Qangle;       Changes obliquing angle
    \Wvalue;       Changes width factor to produce wide text
    \Avalue;       Sets the alignment value; valid values: 0, 1, 2 (bottom, center, top)

    Some other codes that appear to be used:
    %%d            %
    %%p            +/-
  */
  std::string s;

  for (const char *c = in.c_str (); *c; ) {

    if (*c == '%' && c[1] == '%' && c[2] && tolower (c[2]) == 'p') {
      //  replace %%p by +/-
      s += "+/-";
      c += 3;
    } else if (*c == '%' && c[1] == '%' && tolower (c[2]) == 'd') {
      //  replace %%d by %
      s += "%";
      c += 3;
    } else if (for_mtext && *c == '^' && c[1] == 'J') {
      //  replace 
      s += "\n";
      c += 2;
    } else if (for_mtext && (*c == '{' || *c == '}')) {
      //  ignore { .. } brackets
      ++c;
    } else if (*c == '\\' && c[1] && tolower (c[1]) == 'u') {

      c += 2;
      if (*c == '+') {
        ++c;
      }

      int code = 0;
      for (int i = 0; i < 4; ++i) {
        if (!*c) {
          break;
        } else if (isdigit(*c)) {
          code = (code * 16) + int(*c - '0');
          ++c;
        } else if (tolower(*c) <= 'f' && tolower(*c) >= 'a') {
          code = (code * 16) + int(tolower(*c) - 'a' + 10);
          ++c;
        } else {
          break;
        }
      }

      s += QString (QChar(code)).toUtf8 ().constData ();

    } else if (for_mtext && *c == '\\' && c[1] && tolower(c[1]) == 'p') {
      s += "\n";
      c += 2;
    } else if (for_mtext && *c == '\\' && c[1] && (tolower(c[1]) == 'o' || tolower(c[1]) == 'l')) {
      //  ignore underline, overline, 
      c += 2;
    } else if (for_mtext && *c == '\\' && c[1] && tolower(c[1]) == '~') {
      //  ignore non-breaking space
      c += 2;
    } else if (for_mtext && *c == '\\' && c[1] && isalpha (c[1])) {
      //  ignore other formatting commands
      c += 2;
      while (*c && *c != ';') {
        ++c;
      }
      if (*c) {
        ++c;
      }
    } else if (*c == '\\' && c[1]) {
      //  backslash escape
      s += c[1];
      c += 2;
    } else {
      s += *c;
      ++c;
    }
  }

  return s;
}

void 
DXFReader::deliver_text (db::Shapes &shapes, const std::string &s, const db::DCplxTrans &text_trans, double h, double ls, int halign, int valign, double w)
{
  db::HAlign ha = db::NoHAlign;
  if (halign == 0) {
    ha = HAlignLeft;
  //  TODO: what is the interpretation of halign (TEXT code 72) value 3 and 5?
  } else if (halign == 1 || halign == 3 || halign == 4 || halign == 5) {
    ha = HAlignCenter;
  } else if (halign == 2) {
    ha = HAlignRight;
  }
  db::VAlign va = db::NoVAlign;
  if (valign == 0 || valign == 1) {
    va = VAlignBottom;
  } else if (valign == 2) {
    va = VAlignCenter;
  } else if (valign == 3) {
    va = VAlignTop;
  }

  if (m_render_texts_as_polygons) {

    db::EdgeProcessor ep;

    //  we use a pixel size of 200 for reference, so we are less dependent on the accuracy of the 
    //  font rendering engine
    QFont f (QString::fromAscii ("Courier"));
    f.setPixelSize (200);
    QFontMetrics fm (f);

    //  The m_text_scaling divider is the letter width in percent of the height.
    //  92 is the default letter pitch in percent of the text height.
    int pixel_size_ref = int (floor (0.5 + 100.0 * fm.width(QChar::fromAscii('X')) / (0.92 * m_text_scaling)));

    //  split text into lines
    QStringList lines = QString::fromUtf8 (s.c_str ()).split (QString::fromAscii ("\n"));
    double y0 = 0.0; 
    if (va == VAlignBottom || va == NoVAlign) {
      y0 += h * (lines.size () - 1);
    } else if (va == VAlignCenter) {
      y0 += h * (0.5 * lines.size () - 1);
    } else {
      y0 = -h;
    }

    std::vector <db::Point> points;
    std::vector <db::Edge> iedges;

    if (w > 0.0) {

      //  wrap lines if required
      QStringList ll = lines;
      lines.clear ();
      for (QStringList::const_iterator l = ll.begin (); l != ll.end (); ++l) {

        if (fm.width (*l) * h / pixel_size_ref > w) {

          //  wrapping required
          QString line;
          double wl = 0.0;
          for (int i = 0; i < int (l->size ()); ) {

            QString ls;
            bool any_word = false;
            while (i < int (l->size ()) && ((*l)[i].isLetter () || (*l)[i].isDigit ())) {
              ls += (*l)[i];
              ++i;
              any_word = true;
            }
            if (! any_word) {
              ls += (*l)[i];
              ++i;
            }

            double wc = fm.width (ls) * h / pixel_size_ref;
            if (wl + wc > w) {
              lines.push_back (line);
              line.clear ();
              wl = 0;
            }

            line += ls;
            wl += wc;

          }

          if (! line.isEmpty ()) {
            lines.push_back (line);
          }

        } else {
          //  no wrapping required
          lines.push_back (*l);
        }

      }

    }

    for (QStringList::const_iterator l = lines.begin (); l != lines.end (); ++l) {

      double x0 = 0.0;
      if (ha == HAlignLeft || ha == NoHAlign) {
      } else if (ha == HAlignCenter) {
        x0 -= fm.width (*l) * 0.5 * h / pixel_size_ref;
      } else {
        x0 -= fm.width (*l) * h / pixel_size_ref;
      }

      QPainterPath pp;
      pp.addText (QPointF (0.0, 0.0), f, *l);
      QList<QPolygonF> polygons = pp.toFillPolygons ();
      for (QList<QPolygonF>::const_iterator poly = polygons.begin (); poly != polygons.end (); ++poly) {

        points.clear ();
        for (QPolygonF::const_iterator pt = poly->begin (); pt != poly->end (); ++pt) {
          points.push_back (safe_from_double (text_trans * db::DPoint (pt->x () * h / pixel_size_ref + x0, -pt->y () * h / pixel_size_ref + y0)));
        }

        for (size_t i = 0; i < points.size (); ++i) {
          if (i == 0) {
            iedges.push_back (db::Edge (points.back (), points [i]));
          } else {
            iedges.push_back (db::Edge (points [i - 1], points [i]));
          }
        }

      }

      std::vector <db::Polygon> pout;
      ep.simple_merge (iedges, pout, true /*resolve holes*/, true /*min coherence*/, 0);

      for (std::vector <db::Polygon>::const_iterator po = pout.begin (); po != pout.end (); ++po) {
        shapes.insert (*po);
      }

      y0 -= ls;

    }

  } else {
    db::DText text (s, db::DTrans (text_trans), text_trans.ctrans (h * m_text_scaling / 100.0), db::NoFont, ha, va);
    shapes.insert (safe_from_double (text));
  }
}

void
DXFReader::read_entities (db::Layout &layout, db::Cell &cell, const db::DPoint &offset)
{
  std::map <unsigned int, std::vector <db::Edge> > collected_edges;
  db::EdgeProcessor ep (true /* with progress*/);

  int g;

  while (true) {

    const std::string &entity_code = read_string (true);

    if (entity_code == "ENDSEC") {
      break;
    } else if (entity_code == "ENDBLK") {
      break;
    } else if (entity_code == "LWPOLYLINE" || entity_code == "POLYLINE") {

      std::vector<db::DPoint> points;

      std::string layer;
      int flags = 0;
      double width = 0.0;
      bool width_set = false;
      unsigned int got_width = 0;
      double common_width = 0.0;
      unsigned int common_width_set = 0;
      double ex = 0.0, ey = 0.0, ez = 1.0;
      size_t points_with_width = 0;
      size_t points_with_one_width = 0;
      size_t tot_points = 0;
      double b = 0.0;

      if (entity_code == "LWPOLYLINE") {

        unsigned int xy_flags = 0;
        double x = 0.0, y = 0.0;

        while ((g = read_group_code ()) != 0) {

          if (g == 8) {
            layer = read_string (true);
          } else if (g == 70) {
            flags = read_int16 ();
          } else if (g == 10 || g == 20) {

            if (g == 10) {
              x = read_double ();
              xy_flags |= 1;
            } else {
              y = read_double ();
              xy_flags |= 2;
            }

            if (xy_flags == 3) {
              add_bulge_segment (points, db::DPoint (x, y), b);
              ++tot_points;
              b = 0.0;
              xy_flags = 0;
            }

            if (got_width == 3) {
              ++points_with_width;
            } else if (got_width > 0) {
              ++points_with_one_width;
            }

            got_width = 0;
            
          } else if (g == 210) {
            ex = read_double ();
          } else if (g == 220) {
            ey = read_double ();
          } else if (g == 230) {
            ez = read_double ();
          } else if (g == 43) {

            common_width = read_double ();
            common_width_set = 3;

          } else if (g == 42) {
            b = read_double (); // bulge
          } else if (g == 41 || g == 40) {

            if (g == 41) {
              got_width |= 2;
            } else {
              got_width |= 1;
            }

            if (!width_set) {
              width = read_double ();
              width_set = true;
            } else {
              double w = read_double ();
              if (fabs (w - width) > 1e-6) {
                warn ("Non-uniform width encountered on LWPOLYLINE");
              }
            }

          } else {
            skip_value (g);
          }

        }

      } else {

        while ((g = read_group_code ()) != 0) {

          if (g == 8) {
            layer = read_string (true);
          } else if (g == 70) {
            flags = read_int16 ();
          } else if (g == 210) {
            ex = read_double ();
          } else if (g == 220) {
            ey = read_double ();
          } else if (g == 230) {
            ez = read_double ();
          } else if (g == 40 || g == 41) {

            if (common_width_set == 0) {
              common_width = read_double ();
            } else {
              double w = read_double ();
              if (fabs (w - common_width) > 1e-6) {
                warn ("Different start and end width encountered on POLYLINE");
              }
            }

            if (g == 40) {
              common_width_set |= 1;
            } else {
              common_width_set |= 2;
            }

          } else {
            skip_value (g);
          }

        }

        while (true) {

          const std::string &e = read_string (true);
          if (e == "VERTEX") {

            if (got_width == 3) {
              ++points_with_width;
            } else if (got_width > 0) {
              ++points_with_one_width;
            }

            got_width = 0;
            
            double x = 0.0, y = 0.0;
            double bnew = 0.0;

            while ((g = read_group_code ()) != 0) {
              if (g == 10) {
                x = read_double ();
              } else if (g == 20) {
                y = read_double ();
              } else if (g == 42) {
                bnew = read_double (); // bulge
              } else if (g == 40 || g == 41) {

                if (g == 41) {
                  got_width |= 2;
                } else {
                  got_width |= 1;
                }

                if (!width_set) {
                  width = read_double ();
                  width_set = true;
                } else {
                  double w = read_double ();
                  if (fabs (w - width) > 1e-6) {
                    warn ("Non-uniform width encountered on POLYLINE");
                  }
                }

              } else {
                skip_value (g);
              }
            }

            add_bulge_segment (points, db::DPoint (x, y), b);
            ++tot_points;
            b = bnew;

          } else if (e == "SEQEND") {
            while ((g = read_group_code ()) != 0) {
              skip_value (g);
            }
            break;
          } else {
            while ((g = read_group_code ()) != 0) {
              skip_value (g);
            }
          }

        }

      }

      if (got_width == 3) {
        ++points_with_width;
      } else if (got_width > 0) {
        ++points_with_one_width;
      }

      //  Create a closing arc if a bulge was specified on the last point and the polygon is 
      //  marked as a closed one
      if (fabs (b) > 1e-10 && (flags & 1) != 0) {
        //  Hint: needs a copy, since points may be altered by add_bulge_segment
        db::DPoint p0 (points [0]);
        add_bulge_segment (points, p0, b);
      }

      //  Let the per-vertex width override the common width 
      //  TODO: this scheme just covers the case if all or no vertex has width
      //  specifications. 
      if (! width_set || fabs (width) < 1e-6) {
        width = common_width;
      }

      //  issue a warning if there are vertices without a width specification
      if (points_with_width > 0 && points_with_width < tot_points) {
        warn ("Mixed width specification encountered on LWPOLYLINE or POLYLINE - uniform width supported only");
      }
      if (points_with_one_width > 0) {
        warn ("Single width specification encountered on LWPOLYLINE or POLYLINE vertex - full and uniform specification supported only");
      }
      if (common_width_set > 0 && common_width_set < 3) {
        warn ("Either both start and end width must be specified on POLYLINE or none of them");
      }

      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {

        db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

        //  create the polygon or path for width = 0: in mode 2, the polygon is always created, in modes 3 and 4
        //  the polygon is split into edges and joined with other edges later (this will resolve holes formed by
        //  other polygons)
        if (width < 1e-6 && (flags & 1) != 0 && m_polyline_mode == 2) {

          db::DPolygon p;
          p.assign_hull (points.begin (), points.end (), tt);
          cell.shapes(ll.second).insert (safe_from_double (p));

        } else if (! points.empty ()) {

          //  in the merge line modes create a set of edges from an open polyline and merge later
          if (width < 1e-6 && /*(flags & 1) == 0 &&*/ m_polyline_mode >= 3) {

            std::vector <db::Edge> &edges = collected_edges.insert (std::make_pair (ll.second, std::vector <db::Edge> ())).first->second;
            for (std::vector<db::DPoint>::const_iterator p = points.begin () + 1; p != points.end (); ++p) {
              edges.push_back (safe_from_double (db::DEdge (tt.trans (p[-1]), tt.trans (*p))));
            }

            if ((flags & 1) != 0) {
              edges.push_back (safe_from_double (db::DEdge (tt.trans (points.back ()), tt.trans (points.front ()))));
            }

          } else {

            if ((flags & 1) != 0 && fabs (width) > 1e-6 && points.size () > 2) {

              //  closed polylines are created by forming the rim of a polygon
              //  with the specified width
             
              db::DPolygon p;
              p.assign_hull (points.begin (), points.end (), tt, false /*no compression*/);
              std::vector <db::Polygon> pin;
              pin.push_back (safe_from_double (p));

              std::vector <db::Polygon> pouter, pinner;
              db::Coord w = db::coord_traits<db::Coord>::rounded (tt.ctrans (std::max (0.0, width)));
              ep.size (pin, w * 0.5, w * 0.5, pouter, 2, false);
              ep.size (pouter, -w, -w, pinner, 2, false);

              pin.clear ();
              ep.boolean (pouter, pinner, pin, db::BooleanOp::ANotB, true /*resolve holes*/);

              for (std::vector <db::Polygon>::const_iterator po = pin.begin (); po != pin.end (); ++po) {
                cell.shapes(ll.second).insert (*po);
              }

            } else {

              if ((flags & 1) != 0) {
                points.push_back (points.front ());
              }

              db::DPath p;
              p.assign (points.begin (), points.end (), tt);
              p.bgn_ext (0.0);
              p.end_ext (0.0);
              p.width (tt.ctrans (std::max (0.0, width)));
              cell.shapes (ll.second).insert (safe_from_double (p));

            }

          }

        }

      }

    } else if (entity_code == "SPLINE") {

      std::vector<double> knots;
      std::vector<db::DPoint> points;
      db::DPoint pc;
      double ex = 0.0, ey = 0.0, ez = 1.0;

      std::string layer;
      unsigned int xy_flag = 0;
      int degree = 1;

      while ((g = read_group_code ()) != 0) {
        if (g == 8) {
          layer = read_string (true);
        } else if (g == 10 || g == 20) {

          if (xy_flag == 0) {
            points.push_back (db::DPoint ());
          }

          if (g == 10) {
            points.back ().set_x (read_double ());
            xy_flag |= 1;
          } else {
            points.back ().set_y (read_double ());
            xy_flag |= 2;
          }
          if (xy_flag == 3) {
            xy_flag = 0;
          }

        } else if (g == 71) {
          degree = read_int32 ();
        } else if (g == 40) {
          knots.push_back (read_double ());
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first && ! points.empty ()) {

        spline_interpolation (points, degree, knots, true /*save first point*/);

        if (m_polyline_mode == 3 || m_polyline_mode == 4) {

          //  in "join" mode, add an edge for each segment
          std::vector <db::Edge> &edges = collected_edges.insert (std::make_pair (ll.second, std::vector <db::Edge> ())).first->second;
          for (size_t i = 0; i + 1 < points.size (); ++i) {
            edges.push_back (safe_from_double (db::DEdge (tt.trans (points [i]), tt.trans (points [i + 1]))));
          }

        } else {

          //  create a path with width 0 for the spline
          db::DPath p;
          p.assign (points.begin (), points.end (), tt);
          p.bgn_ext (0.0);
          p.end_ext (0.0);
          p.width (0);
          cell.shapes (ll.second).insert (safe_from_double (p));

        }

      }

    } else if (entity_code == "LINE") {

      db::DPoint p1, p2;
      double w = 0.0;
      double ex = 0.0, ey = 0.0, ez = 1.0;

      std::string layer;

      while ((g = read_group_code ()) != 0) {
        if (g == 8) {
          layer = read_string (true);
        } else if (g == 10) {
          p1.set_x (read_double ());
        } else if (g == 20) {
          p1.set_y (read_double ());
        } else if (g == 11) {
          p2.set_x (read_double ());
        } else if (g == 21) {
          p2.set_y (read_double ());
        } else if (g == 39) {
          w = read_double ();
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {

        if (w < 1e-6 && (m_polyline_mode == 3 || m_polyline_mode == 4)) {

          std::vector <db::Edge> &edges = collected_edges.insert (std::make_pair (ll.second, std::vector <db::Edge> ())).first->second;
          edges.push_back (safe_from_double (db::DEdge (tt.trans (p1), tt.trans (p2))));

        } else {

          //  create the path
          db::DPoint points [2] = { p1, p2 };
          db::DPath p;
          p.assign (&points[0], points + 2, tt);
          p.bgn_ext (0.0);
          p.end_ext (0.0);
          p.width (tt.ctrans (std::max (0.0, w)));
          cell.shapes (ll.second).insert (safe_from_double (p));

        }

      }

    } else if (entity_code == "TRACE") {

      db::DPoint p1, p2, p3, p4;
      /* not used currently:
      double w = 0.0;
      */
      double ex = 0.0, ey = 0.0, ez = 1.0;

      std::string layer;

      while ((g = read_group_code ()) != 0) {
        if (g == 8) {
          layer = read_string (true);
        } else if (g == 10) {
          p1.set_x (read_double ());
        } else if (g == 20) {
          p1.set_y (read_double ());
        } else if (g == 11) {
          p2.set_x (read_double ());
        } else if (g == 21) {
          p2.set_y (read_double ());
        } else if (g == 12) {
          p3.set_x (read_double ());
        } else if (g == 22) {
          p3.set_y (read_double ());
        } else if (g == 13) {
          p4.set_x (read_double ());
        } else if (g == 23) {
          p4.set_y (read_double ());
        } else if (g == 39) {
          // not used currently: w = read_double ();
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {

        //  TODO: what to do with the width?

        //  create the path
        db::DPoint points [4] = { p1, p2, p4, p3 };
        db::DPolygon p;
        p.assign_hull (&points[0], points + 4, tt);
        cell.shapes(ll.second).insert (safe_from_double (p));

      }

    } else if (entity_code == "ARC") {

      db::DPoint pc;
      double as = 0.0, ae = 0.0;
      double r = 0.0;
      double w = 0.0;
      double ex = 0.0, ey = 0.0, ez = 1.0;

      std::string layer;

      while ((g = read_group_code ()) != 0) {
        if (g == 8) {
          layer = read_string (true);
        } else if (g == 10) {
          pc.set_x (read_double ());
        } else if (g == 20) {
          pc.set_y (read_double ());
        } else if (g == 50) {
          as = read_double ();
        } else if (g == 51) {
          ae = read_double ();
        } else if (g == 40) {
          r = read_double ();
        } else if (g == 39) {
          w = read_double ();
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      if (ae < as - 1e-6) {
        ae += -floor ((ae - as - 1e-6) / 360.0) * 360.0;
      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {

        int n = int (std::max (1.0, ceil ((ae - as) / 360.0 * m_circle_points)));
        double da = (ae - as) / n;

        std::vector<db::DPoint> points;
        points.reserve (n + 1);

        double a = as;
        for (int i = 0; i < n + 1; ++i) {
          points.push_back (db::DPoint (pc.x () + r * cos ((M_PI / 180.0) * a), pc.y () + r * sin ((M_PI / 180.0) * a)));
          a += da;
        }

        if (w < 1e-6 && (m_polyline_mode == 3 || m_polyline_mode == 4)) {

          std::vector <db::Edge> &edges = collected_edges.insert (std::make_pair (ll.second, std::vector <db::Edge> ())).first->second;
          for (size_t i = 1; i < points.size (); ++i) {
            edges.push_back (safe_from_double (db::DEdge (tt.trans (points [i - 1]), tt.trans (points [i]))));
          }

        } else {

          //  create the path
          db::DPath p;
          p.assign (&points[0], &points[0] + points.size (), tt);
          p.bgn_ext (0.0);
          p.end_ext (0.0);
          p.width (tt.ctrans (std::max (0.0, w)));
          cell.shapes(ll.second).insert (safe_from_double (p));

        }

      }

    } else if (entity_code == "MTEXT") {

      db::DPoint p;
      db::DVector xv;
      double h = 0.0, ls = 1.0;
      double w = -1.0;
      std::string s;
      std::string layer;
      double ex = 0.0, ey = 0.0, ez = 1.0;
      int m = 0;
      bool in_columns = false;

      while ((g = read_group_code ()) != 0) {
        if (g == 8) {
          layer = read_string (true);
        } else if (g == 10) {
          p.set_x (read_double ());
        } else if (g == 20) {
          p.set_y (read_double ());
        } else if (g == 11) {
          xv.set_x (read_double ());
        } else if (g == 21) {
          xv.set_y (read_double ());
        } else if (g == 40) {
          h = read_double ();
        } else if (g == 41) {
          w = read_double ();
        } else if (g == 46) {
          //  undocumented feature?
          double w46 = read_double ();
          if (w < 0.0) {
            w = w46;
          }
        } else if (g == 44) {
          ls = read_double ();
        } else if (g == 50) {
          double v = read_double ();
          if (! in_columns) {
            xv = db::DVector (cos (v / 180.0 * M_PI), sin (v / 180.0 * M_PI));
          } 
        } else if (g == 71) {
          m = read_int32 ();
        } else if (g == 75) {
          read_int32 ();
          in_columns = true;
        } else if (g == 1 || g == 3) {
          s += read_string (false);
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

      //  create the text
      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {

        double a = 0.0;
        if (xv.x () != 0.0 || xv.y () != 0.0) {
          a = atan2 (xv.y (), xv.x ()) / M_PI * 180.0;
        } 

        db::DCplxTrans text_trans (1.0, a, false, db::DPoint ());

        int halign = 0;
        int valign = 0;
        if (m > 0) {
          int va = (m - 1) / 3; // 0: top, 1: middle, 2: bottom
          if (va == 0) {
            valign = 3; // top for TEXT objects
          } else if (va == 1) {
            valign = 2; // center for TEXT objects
          } else if (va == 2) {
            valign = 0; // bottom for TEXT objects
          }
          halign = (m - 1) % 3; // 0: left, 1: middle, 2: right
        }

        deliver_text (cell.shapes(ll.second), normalize_string (s, true), tt * db::DCplxTrans (p) * text_trans, h, h * ls, halign, valign, w);

      }

    } else if (entity_code == "TEXT" || entity_code == "ATTRIB" || entity_code == "ATTDEF") {

      bool is_text = (entity_code == "TEXT");

      db::DPoint p, p2;
      bool has_p2 = false;
      double h = 0.0;
      std::string s;
      std::string layer;
      double a = 0.0;
      double ex = 0.0, ey = 0.0, ez = 1.0;
      int m = 0, halign = 0, valign = 0;

      while ((g = read_group_code ()) != 0) {
        if (g == 8) {
          layer = read_string (true);
        } else if (g == 10) {
          p.set_x (read_double ());
        } else if (g == 20) {
          p.set_y (read_double ());
        } else if (g == 11) {
          has_p2 = true;
          p2.set_x (read_double ());
        } else if (g == 21) {
          has_p2 = true;
          p2.set_y (read_double ());
        } else if (g == 40) {
          h = read_double ();
        } else if (g == 50) {
          a = read_double ();
        } else if (g == 71) {
          m = read_int32 ();
        } else if (g == 72) {
          halign = read_int32 ();
        } else if ((is_text && g == 73 /*for TEXT*/) || (!is_text && g == 74 /*for ATTRIB and ATTDEF*/)) {
          valign = read_int32 ();
        } else if (g == 1) {
          s = read_string (false);
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

      //  create the text
      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {

        //  TODO: check implementation, in particular alignment and mirror flags
        db::DCplxTrans text_trans (1.0, a, false, db::DPoint ());
        if ((m & 2) != 0) {
          text_trans = db::DCplxTrans (db::FTrans (db::FTrans::m90));
        }
        if ((m & 4) != 0) {
          text_trans = db::DCplxTrans (db::FTrans (db::FTrans::m0));
        }

        s = normalize_string (s, false);

        if (has_p2) {
          if (valign == 0 && halign >= 5) {
            if (halign == 5) {
              //  fit the text for the "fit" type
              double lt = s.size () * h;
              if (lt > 0.0 && lt > p.distance (p2)) {
                h *= p.distance (p2) / lt;
              }
            }
            p = (p + p2) * 0.5;
          } else if (halign != 0 || valign != 0) {
            std::swap (p, p2);
          }
        }

        deliver_text (cell.shapes (ll.second), s, tt * db::DCplxTrans (p) * text_trans, h, h, halign, valign);

      }

    } else if (entity_code == "HATCH") {

      std::string layer;
      double ex = 0.0, ey = 0.0, ez = 1.0;

      while ((g = read_group_code ()) != 0) {

        if (g == 8) {
          layer = read_string (true);
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else if (g == 91) {
          read_int32 ();
          break;
        } else {
          skip_value (g);
        }

      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);
      std::vector <db::Edge> iedges;

      db::DPoint pc, pc2;
      std::vector<db::DPoint> points;
      std::vector<double> value40;
      std::vector<double> value50;
      std::vector<double> value51;
      std::vector<int> value73;
      std::vector<db::DPoint> points2;
      unsigned int xy_flag = 0;
      unsigned int xy_flag2 = 0;
      double b = 0.0;
      int edge_type = 0;
      int value94 = 0;
      size_t loop_start = iedges.size ();

      bool is_polyline = false;

      while (g != 0 && (g = read_group_code ()) != 0) {

        if (g == 98) {

          //  stop at the seed point definition (98) since that would be
          //  interpreted as a point
          read_int32 ();
          break;

        } else if (g == 72 || g == 92 || g == 93) {

          //  generate the next segment, create a closing arc if a bulge was specified on the last point
          if (! points.empty ()) {
            if (fabs (b) > 1e-10) {
              //  Hint: needs a copy, since points may be altered by add_bulge_segment
              db::DPoint p0 (points [0]);
              add_bulge_segment (points, p0, b);
            }
            deliver_points_to_edges (points, points2, tt, edge_type, value94, value40, value50, value51, value73, iedges);
          } 

          //  close previous loop if necessary
          if (g != 72) {
            finish_loop (loop_start, iedges.size (), iedges);
            loop_start = iedges.size ();
          }

          value40.clear ();
          value50.clear ();
          value51.clear ();
          value73.clear ();
          points.clear ();
          points2.clear ();
          b = 0.0;
          xy_flag = 0;
          xy_flag2 = 0;
          edge_type = 0;
          value94 = 0;

          int v = read_int32 ();
          if (g == 92) {
            is_polyline = ((v & 2) != 0);
          } else if (g == 72) {
            if (! is_polyline) {
              edge_type = v;
            }
          }

        } else if (g == 73) {

          value73.push_back (read_int32 ());

        } else if (g == 94) {

          value94 = read_int32 ();

        } else if (g == 40) {

          value40.push_back (read_double ());

        } else if (g == 50) {

          value50.push_back (read_double ());

        } else if (g == 51) {

          value51.push_back (read_double ());

        } else if (g == 42) {

          double v = read_double (); 
          if (is_polyline) {
            b = v; // bulge for polyline
          }

        } else if (g == 11 || g == 21) {

          if (g == 11) {
            pc2.set_x (read_double ());
            xy_flag2 |= 1;
          } else {
            pc2.set_y (read_double ());
            xy_flag2 |= 2;
          }

          if (xy_flag2 == 3) {
            points2.push_back (pc2);
            xy_flag2 = 0;
          }

        } else if (g == 10 || g == 20) {

          if (g == 10) {
            pc.set_x (read_double ());
            xy_flag |= 1;
          } else {
            pc.set_y (read_double ());
            xy_flag |= 2;
          }

          if (xy_flag == 3) {
            add_bulge_segment (points, pc, b);
            b = 0.0;
            xy_flag = 0;
          }

        } else {
          skip_value (g);
        }

      }

      while (g != 0 && (g = read_group_code ()) != 0) {
        skip_value (g);
      }

      //  generate the final segment, create a closing arc if a bulge was specified on the last point
      if (! points.empty ()) {
        if (fabs (b) > 1e-10) {
          //  Hint: needs a copy, since points may be altered by add_bulge_segment
          db::DPoint p0 (points [0]);
          add_bulge_segment (points, p0, b);
        }
        deliver_points_to_edges (points, points2, tt, edge_type, value94, value40, value50, value51, value73, iedges);
      } 

      //  close previous loop if necessary
      finish_loop (loop_start, iedges.size (), iedges);
      loop_start = iedges.size ();

      //  create the polygons
      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {

        std::vector <db::Polygon> pout;
        ep.simple_merge (iedges, pout, true /*resolve holes*/, true /*min coherence*/, 0);

        for (std::vector <db::Polygon>::const_iterator po = pout.begin (); po != pout.end (); ++po) {
          cell.shapes(ll.second).insert (*po);
        }

      }

    } else if (entity_code == "SOLID") {

      std::vector <db::DPoint> p;
      p.push_back (db::DPoint ());
      std::string layer;
      double ex = 0.0, ey = 0.0, ez = 1.0;

      while ((g = read_group_code ()) != 0) {

        if (g == 8) {

          layer = read_string (true);

        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else if (g >= 10 && g <= 13) {

          while (p.size () < size_t (g - 10 + 1)) {
            p.push_back (db::DPoint ());
          }

          p[g - 10].set_x (read_double ());

        } else if (g >= 20 && g <= 23) {

          while (p.size () < size_t (g - 20 + 1)) {
            p.push_back (db::DPoint ());
          }

          p[g - 20].set_y (read_double ());

        } else {
          skip_value (g);
        }
      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

      //  create the polygon
      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {
        db::DSimplePolygon poly;
        if (p.size () == 4) {
          std::swap (p [2], p [3]);
        }
        poly.assign_hull (p.begin (), p.end (), tt);
        cell.shapes(ll.second).insert (safe_from_double (poly));
      }

    } else if (entity_code == "ELLIPSE") {

      db::DPoint pc, pm;
      double r = 1.0;
      std::string layer;
      double ex = 0.0, ey = 0.0, ez = 1.0;
      double sa = 0.0, ea = M_PI * 2.0;

      while ((g = read_group_code ()) != 0) {
        if (g == 8) {
          layer = read_string (true);
        } else if (g == 10) {
          pc.set_x (read_double ());
        } else if (g == 20) {
          pc.set_y (read_double ());
        } else if (g == 11) {
          pm.set_x (read_double ());
        } else if (g == 21) {
          pm.set_y (read_double ());
        } else if (g == 40) {
          r = read_double ();
        } else if (g == 41) {
          sa = read_double ();
        } else if (g == 42) {
          ea = read_double ();
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

      //  create the polygon
      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {

        if (m_polyline_mode == 3 || m_polyline_mode == 4) {

          std::vector <db::Edge> &edges = collected_edges.insert (std::make_pair (ll.second, std::vector <db::Edge> ())).first->second;

          int n = int (std::max (1.0, floor (0.5 + (ea - sa) * m_circle_points / (M_PI * 2.0))));
          double da = (ea - sa) / n;

          db::DPoint pl;
          db::DVector vmaj = pm; // documentation says that pm is the "endpoint", 
          db::DVector vmin (-vmaj.y () * r, vmaj.x () * r);

          double a = sa;
          for (int i = 0; i < n + 1; ++i) {

            db::DPoint pp = tt * (pc + vmaj * cos (a) + vmin * sin (a));

            if (a > sa + 1e-6) {
              edges.push_back (db::Edge (safe_from_double (pl), safe_from_double (pp)));
            }

            pl = pp;

            a += da;

          }

        } else {

          int n = int (std::max (1.0, floor (0.5 + (ea - sa) * m_circle_points / (M_PI * 2.0))));
          double da = (ea - sa) / n;

          db::DPoint pl;
          db::DVector vmaj = pm; // documentation says that pm is the "endpoint", 
          db::DVector vmin (-vmaj.y () * r, vmaj.x () * r);

          double a = sa;
          for (int i = 0; i < n + 1; ++i) {

            db::DPoint pp = tt * (pc + vmaj * cos (a) + vmin * sin (a));

            if (a > sa + 1e-6) {

              //  create the line segment
              db::DPoint points [2] = { pl, pp };
              db::DPath p;
              p.assign (&points[0], points + 2);
              p.bgn_ext (0.0);
              p.end_ext (0.0);
              p.width (0.0);
              cell.shapes(ll.second).insert (safe_from_double (p));

            }

            pl = pp;

            a += da;

          }

        }

      }

    } else if (entity_code == "CIRCLE") {

      db::DPoint p;
      double r = 0.0;
      std::string layer;
      double ex = 0.0, ey = 0.0, ez = 1.0;

      while ((g = read_group_code ()) != 0) {
        if (g == 8) {
          layer = read_string (true);
        } else if (g == 10) {
          p.set_x (read_double ());
        } else if (g == 20) {
          p.set_y (read_double ());
        } else if (g == 40) {
          r = read_double ();
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      db::DCplxTrans tt = global_trans (offset, ex, ey, ez);

      //  create the polygon
      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      if (ll.first) {

        if (m_polyline_mode == 3 || m_polyline_mode == 4) {

          std::vector <db::Edge> &edges = collected_edges.insert (std::make_pair (ll.second, std::vector <db::Edge> ())).first->second;

          int n = m_circle_points;
          double da = (M_PI * 2.0) / n;

          db::DPoint pl, pp;

          double a = 0.0;
          for (int i = 0; i < n + 1; ++i) {

            db::DPoint pp = tt * (p + db::DPoint (0, r) * cos (a) + db::DPoint (r, 0) * sin (a));
            if (i > 0) {
              edges.push_back (db::Edge (safe_from_double (pl), safe_from_double (pp)));
            }

            pl = pp;
            a += da;

          }

        } else {

          db::DPoint pv[1] = { tt * p };
          db::DPath path (pv, pv + 1, tt.ctrans (r * 2), tt.ctrans (r), tt.ctrans (r), true);
          cell.shapes(ll.second).insert (safe_from_double (path));

        }

      }

    } else if (entity_code == "DIMENSION") {

      db::DPoint p1, p2;
      std::string cellname, layer (zero_layer_name);
      //  not used currently: double ex = 0.0, ey = 0.0, ez = 1.0;

      while ((g = read_group_code ()) != 0) {
        if (g == 2) {
          cellname = read_string (true);
        } else if (g == 8) {
          layer = read_string (true);
        } else if (g == 10) {
          p1.set_x (read_double ());
        } else if (g == 20) {
          p1.set_y (read_double ());
        } else if (g == 11) {
          p2.set_x (read_double ());
        } else if (g == 21) {
          p2.set_y (read_double ());
        } else if (g == 210) {
          //  not used currently: ex = read_double ();
        } else if (g == 220) {
          //  not used currently: ey = read_double ();
        } else if (g == 230) {
          //  not used currently: ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      //  TODO: beside the placement of the representative BLOCK (group 2 record), this
      //  implementation does nothing.
 
      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      //  fallback: if the target layer does not exist (i.e. is not mapped, use the zero layer
      if (! ll.first) {
        ll = open_layer (layout, zero_layer_name);
      }
      if (ll.first) {

        //  Place the BLOCK for that DIMENSION object - no text is generated yet
        if (! cellname.empty ()) {

          std::map <std::string, db::cell_index_type>::const_iterator b = m_block_per_name.find (cellname);
          if (b == m_block_per_name.end ()) {
            
            //  create a first representative. Build variants and fill later when the cell is defined in a BLOCK statement.
            db::cell_index_type cell = layout.add_cell ();
            b = m_block_per_name.insert (std::make_pair (cellname, cell)).first;
            m_template_cells.insert (cell);

          } 

          db::cell_index_type ci = make_layer_variant (layout, cellname, b->second, ll.second, 1.0, 1.0);

          db::CplxTrans gt = db::CplxTrans (global_trans (offset, 0.0, 0.0, 1.0));
          double f = gt.mag ();

          db::CplxTrans t = gt * db::CplxTrans(1.0 / f);

          if (t.is_ortho () && fabs (t.mag () - 1.0) < 1e-6) {
            cell.insert (db::CellInstArray (db::CellInst (ci), db::Trans (t)));
          } else {
            cell.insert (db::CellInstArray (db::CellInst (ci), t));
          }

        }

      }

    } else if (entity_code == "INSERT") {

      db::DPoint p;
      double sx = 1.0, sy = 1.0;
      int nx = 1, ny = 1;
      double dx = 0.0, dy = 0.0;
      std::string s;
      std::string cellname, layer (zero_layer_name);
      double a = 0.0;
      double ex = 0.0, ey = 0.0, ez = 1.0;

      while ((g = read_group_code ()) != 0) {
        if (g == 2) {
          cellname = read_string (true);
        } else if (g == 8) {
          layer = read_string (true);
        } else if (g == 10) {
          p.set_x (read_double ());
        } else if (g == 20) {
          p.set_y (read_double ());
        } else if (g == 41) {
          sx = read_double ();
        } else if (g == 42) {
          sy = read_double ();
        } else if (g == 50) {
          a = read_double ();
        } else if (g == 70) {
          nx = read_int16 ();
        } else if (g == 71) {
          ny = read_int16 ();
        } else if (g == 44) {
          dx = read_double ();
        } else if (g == 45) {
          dy = read_double ();
        } else if (g == 210) {
          ex = read_double ();
        } else if (g == 220) {
          ey = read_double ();
        } else if (g == 230) {
          ez = read_double ();
        } else {
          skip_value (g);
        }
      }

      std::pair <bool, unsigned int> ll = open_layer (layout, layer);
      //  fallback: if the target layer does not exist (i.e. is not mapped, use the zero layer
      if (! ll.first) {
        ll = open_layer (layout, zero_layer_name);
      }
      if (ll.first) {

        std::map <std::string, db::cell_index_type>::const_iterator b = m_block_per_name.find (cellname);
        if (b == m_block_per_name.end ()) {
          
          //  create a first representative. Build variants and fill later when the cell is defined in a BLOCK statement.
          db::cell_index_type cell = layout.add_cell ();
          b = m_block_per_name.insert (std::make_pair (cellname, cell)).first;
          m_template_cells.insert (cell);

        } 

        if (fabs (sx) < 1e-6 || fabs (sy) < 1e-6) {
          warn ("Invalid scaling value " + tl::to_string (sx) + "," + tl::to_string (sy) + " ignored");
          sx = sy = 1.0;
        }

        double s = std::min (fabs (sx), fabs (sy));
        db::cell_index_type ci = make_layer_variant (layout, cellname, b->second, ll.second, fabs (sx) / s, fabs (sy) / s);
        sx *= s / fabs (sx);
        sy *= s / fabs (sy);

        db::DCplxTrans tb;

        db::CplxTrans t (fabs (fabs (sx) - 1.0) > 1e-6 ? fabs (sx) : 1.0, 0.0, false, db::DPoint ());
        if (sx < 0) {
          t = db::CplxTrans (DFTrans::m90) * t;
        }
        if (sy < 0) {
          t = db::CplxTrans (DFTrans::m0) * t;
        }
        if (fabs (a) > 1e-6) {
          t = db::CplxTrans (1.0, a, false, db::DPoint ()) * t;
          tb = db::CplxTrans (1.0, a, false, db::DPoint ());
        }

        t = db::CplxTrans (p) * t;

        db::CplxTrans gt = db::CplxTrans (global_trans (offset, ex, ey, ez));
        double f = gt.mag ();

        t = gt * t * db::CplxTrans(1.0 / f);

        if (nx == 1 && ny == 1) {
          if (t.is_ortho () && fabs (t.mag () - 1.0) < 1e-6) {
            cell.insert (db::CellInstArray (db::CellInst (ci), db::Trans (t)));
          } else {
            cell.insert (db::CellInstArray (db::CellInst (ci), t));
          }
        } else {
          db::Point vx = safe_from_double (tb * db::DPoint (f * dx, 0));
          db::Point vy = safe_from_double (tb * db::DPoint (0, f * dy));
          if (t.is_ortho () && fabs (t.mag () - 1.0) < 1e-6) {
            cell.insert (db::CellInstArray (db::CellInst (ci), db::Trans (t), vx, vy, nx, ny));
          } else {
            cell.insert (db::CellInstArray (db::CellInst (ci), t, vx, vy, nx, ny));
          }
        }

      }

    } else {
      warn ("Entity " + entity_code + " not supported - ignored.");
      while ((g = read_group_code()) != 0) {
        skip_value (g);
      }
    }

  }

  //  merge the edges 
  
  if (! collected_edges.empty ()) {

    tl::RelativeProgress progress (tl::to_string (QObject::tr ("Merging edges")), 1000000, 10000);

    db::EdgesToContours e2c;

    for (std::map <unsigned int, std::vector <db::Edge> >::iterator ce = collected_edges.begin (); ce != collected_edges.end (); ++ce) {

      std::vector <db::Edge> &edges = ce->second;
      if (! edges.empty ()) {

        std::vector<db::Edge> cc_edges;

        e2c.fill (edges.begin (), edges.end (), true /*unordered*/, &progress);

        for (size_t c = 0; c < e2c.contours (); ++c) {

          if (e2c.contour (c).back () == e2c.contour (c).front () || m_polyline_mode == 4 /*auto-close*/) {

            //  closed contour: store for later merging
            for (std::vector<db::Point>::const_iterator cc = e2c.contour (c).begin (); cc + 1 != e2c.contour (c).end (); ++cc) {
              cc_edges.push_back (db::Edge (cc[0], cc[1]));
            }

            if (e2c.contour (c).back () != e2c.contour (c).front ()) {
              cc_edges.push_back (db::Edge (e2c.contour (c).back (), e2c.contour (c).front ()));
            }

          } else {

            //  open contour: create a path with width = 0 
            db::Path p;
            p.assign (e2c.contour (c).begin (), e2c.contour (c).end ());
            p.width (0);
            cell.shapes (ce->first).insert (p);

          }

        }

        //  merge the closed contours to resolve holes
        if (! cc_edges.empty ()) {

          std::vector <db::Polygon> pout;
          ep.simple_merge (cc_edges, pout, true /*resolve holes*/, true /*min coherence*/, 0);

          for (std::vector <db::Polygon>::const_iterator po = pout.begin (); po != pout.end (); ++po) {
            cell.shapes (ce->first).insert (*po);
          }

        }

      }

    }

  }
}

bool
DXFReader::prepare_read (bool ignore_empty_lines)
{
  if (m_initial) {

    //  Detect binary format
    const char *h = m_stream.get (22);
    if (h && h[21] == 0 && std::string (h) == "AutoCAD Binary DXF\015\012\032") {
      m_ascii = false;
    } else {
      m_stream.unget (22);
      m_ascii = true;
    }

    m_initial = false;

  }

  if (m_ascii) {

    const char *c;

    do {

      ++m_line_number;
      m_progress.set (m_line_number);

      //  does not release the buffer ..
      m_line.clear ();

      //  read one line 
      while ((c = m_stream.get (1)) != 0) {
        if (*c == '\015' /*CR*/ || *c == '\012') {
          break;
        }
        m_line += *c;
      }

      //  consume CR + LF for windows compatibility
      if (c && *c == '\015' /*CR*/) {
        c = m_stream.get (1);
        if (c && *c != '\012' /*LF*/) {
          m_stream.unget (1);
        }
      }

      tl::Extractor ex (m_line.c_str ());
      if (ignore_empty_lines && ex.at_end ()) {
        warn ("Empty line ignored");
      } else {
        return true;
      }

    } while (c != 0);

    return false;

  } else {
    return true;
  }
}

void
DXFReader::skip_value (int g) 
{
  //  TODO: this table is very likely to be incomplete ..
  if (g < 10) {
    read_string (false);
  } else if (g < 60) {
    read_double ();
  } else if (g < 90) {
    read_int16 ();
  } else if (g < 100) {
    read_int32 (); 
  } else if (g < 110) {
    read_string (false); 
  } else if (g < 160) {
    read_double (); 
  } else if (g < 210) {
    read_int16 (); 
  } else if (g < 270) {
    read_double (); 
  } else if (g < 290) {
    read_int16 (); 
  } else if (g < 300) {
    // Documentation says "bool": read_bool (), but how?
    read_int16 ();
  } else if (g < 370) {
    read_string (false); 
  } else if (g < 390) {
    read_int16 (); 
  } else if (g < 400) {
    read_string (false); 
  } else if (g < 410) {
    read_int16 (); 
  } else if (g < 420) {
    read_string (false); 
  } else if (g < 430) {
    read_int32 (); 
  } else if (g < 440) {
    read_string (false); 
  } else if (g < 460) {
    read_int32 (); 
  } else if (g < 470) {
    read_double (); 
  } else if (g < 1010) {
    read_string (false);
  } else if (g < 1060) {
    read_double ();
  } else if (g < 1071) {
    read_int16 ();
  } else if (g < 1072) {
    read_int32 ();
  } else {
    if (m_ascii) {
      warn ("Unexpected group code: " + tl::to_string (g));
    } else {
      error ("Unexpected group code: " + tl::to_string (g));
    }
  }
}

int
DXFReader::read_group_code ()
{
  prepare_read (true);

  if (m_ascii) {

    do {
    
      //  ignore uninterpretable lines to work around buggy DXF files with empty lines ..
      tl::Extractor ex (m_line.c_str ()); 
      int x = 0;
      if (! ex.try_read (x) || ! ex.at_end ()) {
        warn ("Expected an ASCII integer value - line ignored");
      } else {
        return x;
      }

    } while (prepare_read (true));

    error ("Unexpected end of file - group code expected");
    return 0;

  } else {

    const unsigned char *x = reinterpret_cast<const unsigned char *> (m_stream.get (1));
    if (! x) {
      error ("Unexpected end of file");
      return 0;
    }

    if (*x == 255) {
      x = reinterpret_cast<const unsigned char *> (m_stream.get (2));
      if (! x) {
        error ("Unexpected end of file");
        return 0;
      }
      return int(x[0]) + (int (x[1]) << 8);
    } else {
      return x[0];
    }

  }
}

int 
DXFReader::read_int16 ()
{
  if (m_ascii) {
    return read_int32 ();
  } else {

    prepare_read (true);

    const unsigned char *x = reinterpret_cast<const unsigned char *> (m_stream.get (2));
    if (! x) {
      error ("Unexpected end of file");
      return 0;
    }

    return int(x[0]) + (int (x[1]) << 8);

  }
}

long long 
DXFReader::read_int64 ()
{
  prepare_read (true);

  if (m_ascii) {
    tl::Extractor ex (m_line.c_str ()); 
    double x = 0;
    if (! ex.try_read (x) || ! ex.at_end ()) {
      error ("Expected an ASCII numerical value");
    }
    if (x < std::numeric_limits<long long>::min() || x > std::numeric_limits<long long>::max()) {
      error ("Value is out of limits for a 64 bit signed integer");
    }
    return (long long) x;
  } else {

    const unsigned char *x = reinterpret_cast<const unsigned char *> (m_stream.get (8));
    if (! x) {
      error ("Unexpected end of file");
      return 0;
    }

    //  TODO: can be done faster probably ..
    long long ll = (long long)x[0] + ((long long)x[1] << 8) +
                   (((long long)x[2] + ((long long)x[3] << 8)) << 16) + 
                   (((long long)x[4] + ((long long)x[5] << 8) + 
                   (((long long)x[6] + ((long long)x[7] << 8)) << 16)) << 32);
    return ll;

  }

}

double 
DXFReader::read_double ()
{
  prepare_read (true);

  if (m_ascii) {
    tl::Extractor ex (m_line.c_str ()); 
    double x = 0;
    if (! ex.try_read (x) || ! ex.at_end ()) {
      error ("Expected an ASCII floating-point value");
    }
    return x;
  } else {

    const unsigned char *x = reinterpret_cast<const unsigned char *> (m_stream.get (8));
    if (! x) {
      error ("Unexpected end of file");
      return 0.0;
    }

    //  TODO: can be done faster probably ..
    long long ll = (long long)x[0] + ((long long)x[1] << 8) +
                   (((long long)x[2] + ((long long)x[3] << 8)) << 16) + 
                   (((long long)x[4] + ((long long)x[5] << 8) + 
                   (((long long)x[6] + ((long long)x[7] << 8)) << 16)) << 32);

    union {
      long long ll;
      double d;
    } converter;

    converter.ll = ll;
    return converter.d;

  }

}

int 
DXFReader::read_int32 ()
{
  prepare_read (true);

  if (m_ascii) {
    tl::Extractor ex (m_line.c_str ()); 
    double x = 0;
    if (! ex.try_read (x) || ! ex.at_end ()) {
      error ("Expected an ASCII numerical value");
    }
    if (x < std::numeric_limits<int>::min() || x > std::numeric_limits<int>::max()) {
      error ("Value is out of limits for a 32 bit signed integer");
    }
    return int (x);
  } else {

    const unsigned char *x = reinterpret_cast<const unsigned char *> (m_stream.get (4));
    if (! x) {
      error ("Unexpected end of file");
      return 0;
    }

    return (int)x[0] + ((int)x[1] << 8) + (((int)x[2] + ((int)x[3] << 8)) << 16);

  }

}

const std::string &
DXFReader::read_string (bool ignore_empty_lines)
{
  prepare_read (ignore_empty_lines);

  if (! m_ascii) {

    //  reuse "m_line" for collecting strings ..
    m_line.clear ();

    //  read one string 
    const char *c;
    while ((c = m_stream.get (1)) != 0 && *c) {
      m_line += *c;
    }

    if (! c) {
      error ("Unexpected end of file");
    }

  }

  return m_line;
}

}

