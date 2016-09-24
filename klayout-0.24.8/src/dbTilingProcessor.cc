
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


#include "dbTilingProcessor.h"
#include "dbPolygonTools.h"
#include "dbClip.h"

#include "tlExpression.h"
#include "tlProgress.h"
#include "tlThreadedWorkers.h"

#include <cmath>

namespace db
{

/**
 *  @brief A helper class for the generic implementation of the insert functionality
 */
class RdbInserter
{
public:
  RdbInserter (rdb::Database *rdb, rdb::id_type cell_id, rdb::id_type category_id, const db::CplxTrans &trans)
    : mp_rdb (rdb), m_cell_id (cell_id), m_category_id (category_id), m_trans (trans)
  {
    //  .. nothing yet ..
  }

  template <class T>
  void operator() (const T &t)
  {
    rdb::Item *item = mp_rdb->create_item (m_cell_id, m_category_id);
    item->add_value (t.transformed (m_trans));
  }

  void operator() (const db::SimplePolygon &t)
  {
    rdb::Item *item = mp_rdb->create_item (m_cell_id, m_category_id);
    item->add_value (db::simple_polygon_to_polygon (t).transformed (m_trans));
  }

private:
  rdb::Database *mp_rdb;
  rdb::id_type m_cell_id, m_category_id;
  const db::CplxTrans m_trans;
};

/**
 *  @brief A helper class for the generic implementation of the layout insert functionality
 */
class ShapesInserter
{
public:
  ShapesInserter (db::Shapes *shapes, const db::ICplxTrans &trans, db::Coord ep_sizing)
    : mp_shapes (shapes), m_trans (trans), m_ep_sizing (ep_sizing)
  {
    //  .. nothing yet ..
  }

  template <class T>
  void operator() (const T &t)
  {
    mp_shapes->insert (t.transformed (m_trans));
  }

  void operator() (const db::EdgePair &ep)
  {
    mp_shapes->insert (ep.normalized ().to_polygon (m_ep_sizing).transformed (m_trans));
  }

private:
  db::Shapes *mp_shapes;
  const db::ICplxTrans m_trans;
  db::Coord m_ep_sizing;
};

/**
 *  @brief A helper class for the generic implementation of the region insert functionality
 */
class RegionInserter
{
public:
  RegionInserter (db::Region *region, const db::ICplxTrans &trans, db::Coord ep_sizing)
    : mp_region (region), m_trans (trans), m_ep_sizing (ep_sizing)
  {
    //  .. nothing yet ..
  }

  template <class T>
  void operator() (const T &t)
  {
    mp_region->insert (t.transformed (m_trans));
  }

  void operator() (const db::Text &t)
  {
    //  .. texts are discarded ..
  }

  void operator() (const db::Edge &t)
  {
    //  .. edges are discarded ..
  }

  void operator() (const db::EdgePair &ep)
  {
    mp_region->insert (ep.normalized ().to_polygon (m_ep_sizing).transformed (m_trans));
  }

private:
  db::Region *mp_region;
  const db::ICplxTrans m_trans;
  db::Coord m_ep_sizing;
};

/**
 *  @brief A helper class for the generic implementation of the edge collection insert functionality
 */
class EdgesInserter
{
public:
  EdgesInserter (db::Edges *edges, const db::ICplxTrans &trans)
    : mp_edges (edges), m_trans (trans)
  {
    //  .. nothing yet ..
  }

  void operator() (const db::Text &t)
  {
    //  .. texts are discarded ..
  }

  void operator() (const db::EdgePair &ep)
  {
    mp_edges->insert (ep.first ().transformed (m_trans));
    mp_edges->insert (ep.second ().transformed (m_trans));
  }

  template <class T>
  void operator() (const T &t)
  {
    mp_edges->insert (t.transformed (m_trans));
  }

private:
  db::Edges *mp_edges;
  const db::ICplxTrans m_trans;
};

/**
 *  @brief A helper class for the generic implementation of the edge pair collection insert functionality
 */
class EdgePairsInserter
{
public:
  EdgePairsInserter (db::EdgePairs *edge_pairs, const db::ICplxTrans &trans)
    : mp_edge_pairs (edge_pairs), m_trans (trans)
  {
    //  .. nothing yet ..
  }

  template <class T>
  void operator() (const T &t)
  {
    //  .. discard anything except EdgePairs ..
  }

  void operator() (const db::EdgePair &ep)
  {
    mp_edge_pairs->insert (ep.transformed (m_trans));
  }

private:
  db::EdgePairs *mp_edge_pairs;
  const db::ICplxTrans m_trans;
};

template <class X>
void insert (X &inserter, const db::Polygon &o, const db::Box &tile, bool clip)
{
  if (clip && ! o.box ().inside (tile)) {
    //  apply clipping
    if (o.box ().touches (tile)) {
      std::vector <db::Polygon> clipped_poly;
      db::clip_poly (o, tile, clipped_poly);
      for (std::vector <db::Polygon>::const_iterator cp = clipped_poly.begin (); cp != clipped_poly.end (); ++cp) {
        inserter (*cp);
      }
    }
  } else {
    //  no clipping
    inserter (o);
  }
}

template <class X>
void insert (X &inserter, const db::SimplePolygon &o, const db::Box &tile, bool clip)
{
  if (clip && ! o.box ().inside (tile)) {
    //  apply clipping
    if (o.box ().touches (tile)) {
      std::vector <db::SimplePolygon> clipped_poly;
      db::clip_poly (o, tile, clipped_poly);
      for (std::vector <db::SimplePolygon>::const_iterator cp = clipped_poly.begin (); cp != clipped_poly.end (); ++cp) {
        inserter (*cp);
      }
    }
  } else {
    //  no clipping
    inserter (o);
  }
}

template <class X>
void insert (X &inserter, const db::Path &o, const db::Box &tile, bool clip)
{
  if (clip && ! o.box ().inside (tile)) {
    //  apply clipping
    if (o.box ().touches (tile)) {
      insert (inserter, o.polygon (), tile, clip);
    }
  } else {
    //  no clipping
    inserter (o);
  }
}

template <class X>
void insert (X &inserter, const db::EdgePair &o, const db::Box &tile, bool clip)
{
  if (clip) {
    //  no real clipping for edge pairs - just select the ones that touch the clip rectangle
    if (o.first ().clipped (tile).first || o.second ().clipped (tile).first) {
      inserter (o);
    }
  } else {
    inserter (o);
  }
}

template <class X>
void insert (X &inserter, const db::Text &o, const db::Box &tile, bool clip)
{
  if (clip) {
    //  clipping
    if (o.box ().inside (tile)) {
      inserter (o);
    }
  } else {
    //  no clipping
    inserter (o);
  }
}

template <class X>
void insert (X &inserter, const db::Box &o, const db::Box &tile, bool clip)
{
  if (clip) {
    //  clipping
    db::Box oc = o & tile;
    if (! oc.empty ()) {
      inserter (oc);
    }
  } else {
    //  no clipping
    inserter (o);
  }
}

template <class X>
void insert (X &inserter, const db::Edge &o, const db::Box &tile, bool clip)
{
  if (clip) {
    //  apply clipping. To ensure an edge is just added once, clipping is applied in a
    //  somewhat special way: edges coincident with the clip box are only taken if their
    //  inside side is towards the clip box (see Region::perimeter implementation).
    if (o.bbox ().touches (tile)) {

      std::pair<bool, db::Edge> ce = o.clipped (tile);
      if (ce.first) {

        db::Coord dx = ce.second.dx ();
        db::Coord dy = ce.second.dy ();
        db::Coord x = ce.second.p1 ().x ();
        db::Coord y = ce.second.p1 ().y ();
        if ((dx == 0 && x == tile.left ()   && dy < 0) ||
            (dx == 0 && x == tile.right ()  && dy > 0) ||
            (dy == 0 && y == tile.top ()    && dx < 0) ||
            (dy == 0 && y == tile.bottom () && dx > 0)) {
          //  not counted -> box is at outside side of the edge
        } else {
          inserter (ce.second);
        }

      }

    }

  } else {
    //  no clipping
    inserter (o);
  }
}

template <class X>
void insert (X &inserter, const db::Region &data, const db::Box &tile, bool clip)
{
  for (db::Region::const_iterator o = data.begin (); ! o.at_end (); ++o) {
    insert (inserter, *o, tile, clip);
  }
}

template <class X>
void insert (X &inserter, const db::Edges &data, const db::Box &tile, bool clip)
{
  for (db::Edges::const_iterator o = data.begin (); ! o.at_end (); ++o) {
    insert (inserter, *o, tile, clip);
  }
}

template <class X>
void insert (X &inserter, const db::EdgePairs &data, const db::Box &tile, bool clip)
{
  for (db::EdgePairs::const_iterator o = data.begin (); o != data.end (); ++o) {
    insert (inserter, *o, tile, clip);
  }
}

template <class X>
bool insert_var (X &inserter, const tl::Variant &obj, const db::Box &tile, bool clip)
{
  if (obj.is_user<db::Region> ()) {
    insert (inserter, obj.to_user<db::Region> (), tile, clip);
    return true;
  } else if (obj.is_user<db::EdgePairs> ()) {
    insert (inserter, obj.to_user<db::EdgePairs> (), tile, clip);
    return true;
  } else if (obj.is_user<db::Edges> ()) {
    insert (inserter, obj.to_user<db::Edges> (), tile, clip);
    return true;
  } else if (obj.is_user<db::Box> ()) {
    insert (inserter, obj.to_user<db::Box> (), tile, clip);
    return true;
  } else if (obj.is_user<db::Path> ()) {
    insert (inserter, obj.to_user<db::Path> (), tile, clip);
    return true;
  } else if (obj.is_user<db::Text> ()) {
    insert (inserter, obj.to_user<db::Text> (), tile, clip);
    return true;
  } else if (obj.is_user<db::Polygon> ()) {
    insert (inserter, obj.to_user<db::Polygon> (), tile, clip);
    return true;
  } else if (obj.is_user<db::SimplePolygon> ()) {
    insert (inserter, obj.to_user<db::SimplePolygon> (), tile, clip);
    return true;
  } else if (obj.is_user<db::EdgePair> ()) {
    insert (inserter, obj.to_user<db::EdgePair> (), tile, clip);
    return true;
  } else if (obj.is_user<db::Edge> ()) {
    insert (inserter, obj.to_user<db::Edge> (), tile, clip);
    return true;
  } else if (obj.is_nil ()) {
    //  .. ignore nil
    return true;
  } else {
    return false;
  }
}

class TileRdbOutputReceiver
  : public db::TileOutputReceiver
{
public:
  TileRdbOutputReceiver (rdb::Database *rdb, size_t cell_id, size_t category_id)
    : mp_rdb (rdb), m_cell_id (cell_id), m_category_id (category_id)
  {
    //  .. nothing yet ..
  }

  void put (size_t ix, size_t iy, const db::Box &tile, size_t id, const tl::Variant &obj, double dbu, const db::ICplxTrans &trans, bool clip)
  {
    db::CplxTrans t (db::CplxTrans (dbu) * db::CplxTrans (trans));
    RdbInserter inserter (mp_rdb, m_cell_id, m_category_id, t);

    if (! insert_var (inserter, obj, tile, clip)) {
      //  try to_string as the last resort
      rdb::Item *item = mp_rdb->create_item (m_cell_id, m_category_id);
      item->add_value (std::string (obj.to_string ()));
    }
  }

private:
  rdb::Database *mp_rdb;
  size_t m_cell_id, m_category_id;
};

class TileLayoutOutputReceiver
  : public db::TileOutputReceiver
{
public:
  TileLayoutOutputReceiver (db::Layout *layout, db::Cell *cell, unsigned int layer, db::Coord e)
    : mp_layout (layout), mp_cell (cell), m_layer (layer), m_ep_sizing (e)
  {
    //  .. nothing yet ..
  }

  void put (size_t ix, size_t iy, const db::Box &tile, size_t id, const tl::Variant &obj, double dbu, const db::ICplxTrans &trans, bool clip)
  {
    db::ICplxTrans t (db::ICplxTrans (dbu / mp_layout->dbu ()) * trans);
    db::Shapes &shapes = mp_cell->shapes (m_layer);
    ShapesInserter inserter (&shapes, t, m_ep_sizing);

    insert_var (inserter, obj, tile, clip);
  }

  void begin (size_t nx, size_t ny, const db::DPoint &p0, double dx, double dy) 
  { 
    mp_layout->start_changes ();
  }

  void finish () 
  { 
    mp_layout->end_changes ();
  }

private:
  db::Layout *mp_layout;
  db::Cell *mp_cell;
  unsigned int m_layer;
  db::Coord m_ep_sizing;
};

class TileRegionOutputReceiver
  : public db::TileOutputReceiver
{
public:
  TileRegionOutputReceiver (db::Region *region, db::Coord e)
    : mp_region (region), m_ep_sizing (e)
  {
    //  .. nothing yet ..
  }

  void put (size_t ix, size_t iy, const db::Box &tile, size_t id, const tl::Variant &obj, double dbu, const db::ICplxTrans &trans, bool clip)
  {
    //  optimisation
    if (obj.is_user<db::Region> () && ! clip) {
      *mp_region += obj.to_user<db::Region> ();
    } else {
      RegionInserter inserter (mp_region, trans, m_ep_sizing);
      insert_var (inserter, obj, tile, clip);
    }
  }

private:
  db::Region *mp_region;
  db::Coord m_ep_sizing;
};

class TileEdgesOutputReceiver
  : public db::TileOutputReceiver
{
public:
  TileEdgesOutputReceiver (db::Edges *edges)
    : mp_edges (edges)
  {
    //  .. nothing yet ..
  }

  void put (size_t ix, size_t iy, const db::Box &tile, size_t id, const tl::Variant &obj, double dbu, const db::ICplxTrans &trans, bool clip)
  {
    //  optimisation
    if (obj.is_user<db::Edges> () && ! clip) {
      *mp_edges += obj.to_user<db::Edges> ();
    } else {
      EdgesInserter inserter (mp_edges, trans);
      insert_var (inserter, obj, tile, clip);
    }
  }

private:
  db::Edges *mp_edges;
};

class TileEdgePairsOutputReceiver
  : public db::TileOutputReceiver
{
public:
  TileEdgePairsOutputReceiver (db::EdgePairs *edge_pairs)
    : mp_edge_pairs (edge_pairs)
  {
    //  .. nothing yet ..
  }

  void put (size_t ix, size_t iy, const db::Box &tile, size_t id, const tl::Variant &obj, double dbu, const db::ICplxTrans &trans, bool clip)
  {
    EdgePairsInserter inserter (mp_edge_pairs, trans);
    insert_var (inserter, obj, tile, clip);
  }

private:
  db::EdgePairs *mp_edge_pairs;
};

class TilingProcessorJob
  : public tl::JobBase
{
public:
  TilingProcessorJob (TilingProcessor *proc, int nworkers, bool has_tiles)
    : tl::JobBase (nworkers),
      mp_proc (proc),
      m_has_tiles (has_tiles),
      m_progress (0)
  {
    //  .. nothing yet ..
  }

  bool has_tiles () const
  {
    return m_has_tiles;
  }

  void next_progress () 
  {
    QMutexLocker locker (&m_mutex);
    ++m_progress;
  }

  void update_progress (tl::RelativeProgress &progress) 
  {
    unsigned int p;
    {
      QMutexLocker locker (&m_mutex);
      p = m_progress;
    }

    progress.set (p, true /*force yield*/);
  }

  TilingProcessor *processor () const
  {
    return mp_proc;
  }

  virtual tl::Worker *create_worker ();

private:
  TilingProcessor *mp_proc;
  bool m_has_tiles;
  unsigned int m_progress;
  QMutex m_mutex;
};

class TilingProcessorTask
  : public tl::Task
{
public:
  TilingProcessorTask (const std::string &tile_desc, size_t ix, size_t iy, const db::DBox &clip_box, const db::DBox &region, const std::string &script, size_t script_index)
    : m_tile_desc (tile_desc), m_ix (ix), m_iy (iy), m_clip_box (clip_box), m_region (region), m_script (script), m_script_index (script_index)
  {
    //  .. nothing yet ..
  }

  const std::string &tile_desc () const
  {
    return m_tile_desc;
  }
  
  const db::DBox &clip_box () const
  {
    return m_clip_box;
  }

  size_t ix () const
  {
    return m_ix;
  }
  
  size_t iy () const
  {
    return m_iy;
  }
  
  const db::DBox &region () const
  {
    return m_region;
  }
  
  const std::string &script () const
  {
    return m_script;
  }

  size_t script_index () const
  {
    return m_script_index;
  }

private:
  std::string m_tile_desc;
  size_t m_ix, m_iy;
  db::DBox m_clip_box, m_region;
  std::string m_script;
  size_t m_script_index;
};

class TilingProcessorWorker
  : public tl::Worker
{
public:
  TilingProcessorWorker (TilingProcessorJob *job)
    : tl::Worker (), mp_job (job)
  {
    //  .. nothing yet ..
  }

  void perform_task (tl::Task *task) 
  {
    TilingProcessorTask *tile_task = dynamic_cast <TilingProcessorTask *> (task);
    if (tile_task) {
      do_perform (tile_task);
    }
  }

private:
  TilingProcessorJob *mp_job;

  void do_perform (const TilingProcessorTask *task);
};

class TilingProcessorOutputFunction
  : public tl::EvalFunction
{
public:
  TilingProcessorOutputFunction (TilingProcessor *proc, size_t ix, size_t iy, const db::Box &tile_box)
    : mp_proc (proc), m_ix (ix), m_iy (iy), m_tile_box (tile_box)
  {
    //  .. nothing yet ..
  }

  void execute (const tl::ExpressionParserContext &context, tl::Variant &out, const std::vector<tl::Variant> &args) const 
  {
    mp_proc->put (m_ix, m_iy, m_tile_box, args);
  }

private:
  TilingProcessor *mp_proc;
  size_t m_ix, m_iy;
  db::Box m_tile_box; 
};

class TilingProcessorCountFunction
  : public tl::EvalFunction
{
public:
  TilingProcessorCountFunction (TilingProcessor *proc)
    : mp_proc (proc)
  {
    //  .. nothing yet ..
  }

  void execute (const tl::ExpressionParserContext &context, tl::Variant &out, const std::vector<tl::Variant> &args) const 
  {
    // TODO: ... implement ..
  }

private:
  TilingProcessor *mp_proc;
};

void
TilingProcessorWorker::do_perform (const TilingProcessorTask *tile_task)
{
  tl::Eval eval (&mp_job->processor ()->top_eval ());

  db::Box clip_box_dbu = db::Box::world ();

  eval.set_var ("_dbu", tl::Variant (mp_job->processor ()->dbu ()));

  if (! mp_job->has_tiles ()) { 
    eval.set_var ("_tile", tl::Variant ());
  } else {

    clip_box_dbu = db::Box::from_double (tile_task->clip_box ().transformed (db::DCplxTrans (mp_job->processor ()->dbu ()).inverted ()));

    db::Region r;
    r.insert (clip_box_dbu);
    eval.set_var ("_tile", tl::Variant (r));

  }

  for (std::vector<TilingProcessor::InputSpec>::const_iterator i = mp_job->processor ()->begin_inputs (); i != mp_job->processor ()->end_inputs (); ++i) {

    double dbu = mp_job->processor ()->dbu ();
    if (mp_job->processor ()->scale_to_dbu () && i->iter.layout ()) {
      dbu = i->iter.layout ()->dbu ();
    }

    double sf = dbu / mp_job->processor ()->dbu ();

    if (! mp_job->has_tiles ()) { 

      if (i->region) {
        eval.set_var (i->name, tl::Variant (db::Region (i->iter, db::ICplxTrans (sf) * i->trans, i->merged_semantics)));
      } else {
        eval.set_var (i->name, tl::Variant (db::Edges (i->iter, db::ICplxTrans (sf) * i->trans, i->merged_semantics)));
      }

    } else {

      db::Box region_dbu = db::Box::from_double (tile_task->region ().transformed ((db::DCplxTrans (dbu) * db::DCplxTrans (i->trans)).inverted ()));
      region_dbu &= i->iter.region ();

      db::RecursiveShapeIterator iter;
      if (! region_dbu.empty ()) {
        iter = i->iter;
        iter.set_region (region_dbu);
      }

      if (i->region) {
        eval.set_var (i->name, tl::Variant (db::Region (iter, db::ICplxTrans (sf) * i->trans, i->merged_semantics)));
      } else {
        eval.set_var (i->name, tl::Variant (db::Edges (iter, db::ICplxTrans (sf) * i->trans, i->merged_semantics)));
      }

    }

  }

  eval.define_function ("_output", new TilingProcessorOutputFunction (mp_job->processor (), tile_task->ix (), tile_task->iy (), clip_box_dbu));
  eval.define_function ("_count", new TilingProcessorCountFunction (mp_job->processor ()));

  if (tl::verbosity () >= (mp_job->has_tiles () ? 20 : 10)) {
    tl::info << "TilingProcessor: script #" << (tile_task->script_index () + 1) << ", tile " << tile_task->tile_desc ();
  }

  tl::SelfTimer timer (tl::verbosity () >= (mp_job->has_tiles () ? 21 : 11), "Elapsed time");

  tl::Expression ex;
  eval.parse (ex, tile_task->script ());
  ex.execute ();

  mp_job->next_progress ();
}

tl::Worker *
TilingProcessorJob::create_worker ()
{
  return new TilingProcessorWorker (this);
}

// ----------------------------------------------------------------------------------
//  The tiling processor implementation

TilingProcessor::TilingProcessor ()
  : m_tile_width (0.0), m_tile_height (0.0),
    m_ntiles_w (0), m_ntiles_h (0), 
    m_tile_size_given (false), m_tile_count_given (false),
    m_tile_origin_x (0.0), m_tile_origin_y (0.0),
    m_tile_origin_given (false),
    m_tile_bx (0.0), m_tile_by (0.0),
    m_threads (0), m_dbu (0.001), m_dbu_specific (0.001), m_dbu_specific_set (false),
    m_scale_to_dbu (true)
{
  //  .. nothing yet ..
}

void 
TilingProcessor::input (const std::string &name, const db::RecursiveShapeIterator &iter, const db::ICplxTrans &trans, bool as_region, bool merged_semantics)
{
  if (m_inputs.empty () && iter.layout ()) {
    m_dbu = iter.layout ()->dbu ();
  }
  m_inputs.push_back (InputSpec ());
  m_inputs.back ().name = name;
  m_inputs.back ().iter = iter;
  m_inputs.back ().trans = trans;
  m_inputs.back ().region = as_region;
  m_inputs.back ().merged_semantics = merged_semantics;
}

TilingProcessor::~TilingProcessor ()
{
  for (std::vector<OutputSpec>::const_iterator o = m_outputs.begin (); o != m_outputs.end (); ++o) {
    delete o->receiver;
  }
  m_outputs.clear ();
}

void  
TilingProcessor::tile_size (double w, double h)
{
  m_tile_width = std::max (0.0, w);
  m_tile_height = std::max (0.0, h);
  m_tile_size_given = true;
}

void  
TilingProcessor::tiles (size_t nx, size_t ny)
{
  m_ntiles_w = nx;
  m_ntiles_h = ny;
  m_tile_count_given = true;
}

void  
TilingProcessor::tile_origin (double xo, double yo)
{
  m_tile_origin_x = xo;
  m_tile_origin_y = yo;
  m_tile_origin_given = true;
}

void  
TilingProcessor::tile_border (double bx, double by)
{
  m_tile_bx = std::max (0.0, bx);
  m_tile_by = std::max (0.0, by);
}

void  
TilingProcessor::set_threads (size_t n)
{
  m_threads = n;
}

void  
TilingProcessor::queue (const std::string &script)
{
  m_scripts.push_back (script);
}

void  
TilingProcessor::var (const std::string &name, const tl::Variant &value)
{
  m_top_eval.set_var (name, value);
}

void  
TilingProcessor::output (const std::string &name, size_t id, TileOutputReceiver *rec, const db::ICplxTrans &trans)
{
  m_top_eval.set_var (name, m_outputs.size ());
  m_outputs.push_back (OutputSpec ());
  m_outputs.back ().name = name;
  m_outputs.back ().id = id;
  m_outputs.back ().receiver = rec;
  m_outputs.back ().trans = trans;
}

void  
TilingProcessor::output (const std::string &name, rdb::Database &rdb, rdb::id_type cell_id, rdb::id_type category_id)
{
  m_top_eval.set_var (name, m_outputs.size ());
  m_outputs.push_back (OutputSpec ());
  m_outputs.back ().name = name;
  m_outputs.back ().id = 0;
  m_outputs.back ().receiver = new TileRdbOutputReceiver (&rdb, cell_id, category_id);
}

void   
TilingProcessor::output (const std::string &name, db::Layout &layout, db::cell_index_type cell_index, const db::LayerProperties &lp, db::Coord ep_ext)
{
  //  if we have a layer with the requested properties already, return this.
  db::Layout::layer_iterator li = layout.begin_layers ();
  for ( ; li != layout.end_layers (); ++li) {
    if ((*li).second->log_equal (lp)) {
      break;
    }
  }

  unsigned int layer;
  if (li != layout.end_layers ()) {
    layer = (*li).first;
  } else {
    layer = layout.insert_layer (lp);
  }

  output (name, layout, cell_index, layer, ep_ext);
}

void   
TilingProcessor::output (const std::string &name, db::Layout &layout, db::cell_index_type cell_index, unsigned int layer, db::Coord ep_ext)
{
  m_top_eval.set_var (name, m_outputs.size ());
  m_outputs.push_back (OutputSpec ());
  m_outputs.back ().name = name;
  m_outputs.back ().id = 0;
  m_outputs.back ().receiver = new TileLayoutOutputReceiver (&layout, &layout.cell (cell_index), layer, ep_ext);
}

void 
TilingProcessor::output (const std::string &name, db::Region &region, db::Coord ep_ext)
{
  m_top_eval.set_var (name, m_outputs.size ());
  m_outputs.push_back (OutputSpec ());
  m_outputs.back ().name = name;
  m_outputs.back ().id = 0;
  m_outputs.back ().receiver = new TileRegionOutputReceiver (&region, ep_ext);
}

void 
TilingProcessor::output (const std::string &name, db::EdgePairs &edge_pairs)
{
  m_top_eval.set_var (name, m_outputs.size ());
  m_outputs.push_back (OutputSpec ());
  m_outputs.back ().name = name;
  m_outputs.back ().id = 0;
  m_outputs.back ().receiver = new TileEdgePairsOutputReceiver (&edge_pairs);
}

void 
TilingProcessor::output (const std::string &name, db::Edges &edges)
{
  m_top_eval.set_var (name, m_outputs.size ());
  m_outputs.push_back (OutputSpec ());
  m_outputs.back ().name = name;
  m_outputs.back ().id = 0;
  m_outputs.back ().receiver = new TileEdgesOutputReceiver (&edges);
}

void 
TilingProcessor::put (size_t ix, size_t iy, const db::Box &tile, const std::vector<tl::Variant> &args)
{
  QMutexLocker locker (&m_output_mutex);

  if (args.size () < 2 || args.size () > 3) {
    throw tl::Exception (tl::to_string (QObject::tr ("_output function requires two or three arguments: handle and object and a clip flag (optional)")));
  }

  bool clip = ((args.size () <= 2 || args [2].to_bool ()) && ! tile.empty ());

  size_t index = args[0].to<size_t> ();
  if (index >= m_outputs.size ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("Invalid handle (first argument) of _output function")));
  }

  m_outputs[index].receiver->put (ix, iy, tile, m_outputs[index].id, args[1], dbu (), m_outputs[index].trans, clip);
}

void  
TilingProcessor::execute (const std::string &desc)
{
  db::DBox tot_box;

  for (std::vector<InputSpec>::const_iterator i = m_inputs.begin (); i != m_inputs.end (); ++i) {
    if (! i->iter.at_end ()) {
      if (scale_to_dbu ()) {
        double dbu_value = i->iter.layout () ? i->iter.layout ()->dbu () : dbu ();
        tot_box += i->iter.bbox ().transformed (db::CplxTrans (dbu_value) * db::CplxTrans (i->trans));
      } else {
        tot_box += i->iter.bbox ().transformed (db::CplxTrans (dbu ()) * db::CplxTrans (i->trans));
      }
    }
  }

  //  can't create tiles for empty input
  if (tot_box.empty () && ! (m_tile_count_given && m_tile_origin_given && m_tile_size_given)) {
    return;
  }

  //  add the border to the total box. The reasoning for this is that for example an oversize might grow into
  //  the outer region and therefore be clipped.
  tot_box.enlarge (db::DPoint (m_tile_bx, m_tile_by));

  //  create a tiling plan

  tl::SelfTimer timer_tot (tl::verbosity () >= 11, "Total tiling processor time");

  size_t ntiles_w = 0, ntiles_h = 0;
  double tile_width = 0.0, tile_height = 0.0;

  if (m_tile_size_given && ! m_tile_count_given) {

    tile_width = dbu () * floor (0.5 + m_tile_width / dbu ());
    tile_height = dbu () * floor (0.5 + m_tile_height / dbu ());
    ntiles_w = (m_tile_width > 1e-6 ? size_t (ceil (tot_box.width () / m_tile_width - 1e-10)) : 1);
    ntiles_h = (m_tile_height > 1e-6 ? size_t (ceil (tot_box.height () / m_tile_height - 1e-10)) : 1);

  } else if (! m_tile_size_given && m_tile_count_given) {

    ntiles_w = m_ntiles_w;
    ntiles_h = m_ntiles_h;
    tile_width = (m_ntiles_w > 0 ? dbu () * ceil (tot_box.width () / (dbu () * m_ntiles_w) - 1e-10) : 0.0);
    tile_height = (m_ntiles_h > 0 ? dbu () * ceil (tot_box.height () / (dbu () * m_ntiles_h) - 1e-10) : 0.0);

  } else if (m_tile_size_given && m_tile_count_given) {

    ntiles_w = m_ntiles_w;
    ntiles_h = m_ntiles_h;
    tile_width = dbu () * floor (0.5 + m_tile_width / dbu ());
    tile_height = dbu () * floor (0.5 + m_tile_height / dbu ());

  }

  bool has_tiles = (ntiles_w > 1 || ntiles_h > 1);

  TilingProcessorJob job (this, m_threads, has_tiles);

  double l = 0.0, b = 0.0;

  if (has_tiles) {

    ntiles_w = std::max (size_t (1), ntiles_w);
    ntiles_h = std::max (size_t (1), ntiles_h);

    if (m_tile_origin_given) {
      l = dbu () * floor (0.5 + m_tile_origin_x / dbu ());
      b = dbu () * floor (0.5 + m_tile_origin_y / dbu ());
    } else {
      l = dbu () * floor (0.5 + (tot_box.center ().x () - ntiles_w * 0.5 * tile_width) / dbu ());
      b = dbu () * floor (0.5 + (tot_box.center ().y () - ntiles_h * 0.5 * tile_height) / dbu ());
    }

    //  create the TilingProcessor tasks
    for (size_t ix = 0; ix < ntiles_w; ++ix) {

      for (size_t iy = 0; iy < ntiles_h; ++iy) {

        db::DBox clip_box (l + ix * tile_width, b + iy * tile_height, l + (ix + 1) * tile_width, b + (iy + 1) * tile_height);
        db::DBox region = clip_box.enlarged (db::DPoint (m_tile_bx, m_tile_by));

        std::string tile_desc = tl::sprintf ("%d/%d,%d/%d", ix + 1, ntiles_w, iy + 1, ntiles_h);

        size_t si = 0;
        for (std::vector <std::string>::const_iterator s = m_scripts.begin (); s != m_scripts.end (); ++s, ++si) {
          job.schedule (new TilingProcessorTask (tile_desc, ix, iy, clip_box, region, *s, si));
        }

      }

    }

  } else {

    ntiles_w = ntiles_h = 0;

    size_t si = 0;
    for (std::vector <std::string>::const_iterator s = m_scripts.begin (); s != m_scripts.end (); ++s, ++si) {
      job.schedule (new TilingProcessorTask ("all", 0, 0, db::DBox (), db::DBox (), *s, si));
    }

  }

  //  TODO: there should be a general scheme of how thread-specific progress is merged
  //  into a global one ..
  size_t todo_count = ntiles_w * ntiles_h * m_scripts.size ();
  tl::RelativeProgress progress (desc, todo_count, 1);

  try {

    try {

      for (std::vector<OutputSpec>::const_iterator o = m_outputs.begin (); o != m_outputs.end (); ++o) {
        o->receiver->begin (ntiles_w, ntiles_h, db::DPoint (l, b), tile_width, tile_height);
      }

      job.start ();
      while (job.is_running ()) {
        //  This may throw an exception, if the cancel button has been pressed.
        job.update_progress (progress);
        job.wait (100);
      }

      for (std::vector<OutputSpec>::const_iterator o = m_outputs.begin (); o != m_outputs.end (); ++o) {
        o->receiver->finish ();
      }

    } catch (...) {
      for (std::vector<OutputSpec>::const_iterator o = m_outputs.begin (); o != m_outputs.end (); ++o) {
        o->receiver->finish ();
      }
      throw;
    }

  } catch (tl::BreakException &ex) {
    job.terminate ();
    throw ex;
  } catch (tl::Exception &ex) {
    job.terminate ();
    throw ex;
  }

  if (job.has_error ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("Errors occured during processing. First error message says:\n")) + job.error_messages ().front ());
  }
}

}

