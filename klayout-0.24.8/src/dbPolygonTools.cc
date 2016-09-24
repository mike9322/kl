
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


#include "dbPolygonTools.h"
#include "dbEdgeProcessor.h"

#include <algorithm>

namespace db
{

// -------------------------------------------------------------------------
//  Implementation of inside_poly_test

//  internal: compare edges by higher y coordinate
template <class E>
struct inside_poly_test_edge_max_compare_f
{
  bool operator() (const E &e1, const E &e2)
  {
    return std::max (e1.p1 ().y (), e1.p2 ().y ()) < std::max (e2.p1 ().y (), e2.p2 ().y ());
  }
};

template<class P> 
inside_poly_test<P>::inside_poly_test (const P &polygon)
{
  m_edges.reserve (polygon.vertices ());
  for (typename P::polygon_edge_iterator e = polygon.begin_edge (); ! e.at_end (); ++e) {
    m_edges.push_back (*e);
  }
  std::sort (m_edges.begin (), m_edges.end (), inside_poly_test_edge_max_compare_f<edge_type> ());
}

template<class P> 
int inside_poly_test<P>::operator() (const typename inside_poly_test<P>::point_type &pt) const
{
  int wrapcount_left = 0;

  typename std::vector<edge_type>::const_iterator e = std::lower_bound (m_edges.begin (), m_edges.end (), edge_type (pt, pt), inside_poly_test_edge_max_compare_f<edge_type> ());
  while (e != m_edges.end () && pt.y () <= std::max (e->p1 ().y (), e->p2 ().y ())) {

    if ((*e).p1 ().y () <= pt.y () && (*e).p2 ().y () > pt.y ()) {
      int side = (*e).side_of (pt);
      if (side < 0) { 
        ++wrapcount_left;
      } else if (side == 0) {
        //  "on" the line is excluded in the predicate
        return 0;
      }
    } else if ((*e).p2 ().y () <= pt.y () && (*e).p1 ().y () > pt.y ()) {
      int side = (*e).side_of (pt);
      if (side > 0) { 
        --wrapcount_left;
      } else if (side == 0) {
        //  "on" the line is excluded in the predicate
        return 0;
      }
    } else if ((*e).p1 ().y () == pt.y () && (*e).p2 ().y () == pt.y () &&
               (((*e).p1 ().x () <= pt.x () && (*e).p2 ().x () >= pt.x ()) ||
                ((*e).p2 ().x () <= pt.x () && (*e).p1 ().x () >= pt.x ()))) {
      //  "on" the horizontal line is excluded in the predicate
      return 0;
    }

    ++e;

  }

  return (wrapcount_left != 0) ? 1 : -1;
}

template class KLAYOUT_DLL inside_poly_test<db::SimplePolygon>;
template class KLAYOUT_DLL inside_poly_test<db::Polygon>;
template class KLAYOUT_DLL inside_poly_test<db::DSimplePolygon>;
template class KLAYOUT_DLL inside_poly_test<db::DPolygon>;

// -------------------------------------------------------------------------
//  Implementation of cut_polygon

/**
 *  @brief A helper structure describing an edge cutting the cut line.
 */
template <class PointType>
struct cut_polygon_edge
{
  typedef typename PointType::coord_type coord_type;
  typedef typename db::edge<coord_type> edge_type;
  typedef typename db::coord_traits<coord_type>::area_type projection_type;

  cut_polygon_edge ()
    : contour (-1), index (0), projected (0), point (), last_point ()
  { }

  cut_polygon_edge (int c, unsigned int n, projection_type p, const PointType &pt, const PointType &lpt) 
    : contour (c), index (n), projected (p), point (pt), last_point (lpt)
  { }

  int contour;
  unsigned int index;
  projection_type projected;
  PointType point;
  PointType last_point;
};

template <class CuttingEdgeType>
struct cut_polygon_segment
{
  typedef typename CuttingEdgeType::edge_type edge_type;
  typedef typename CuttingEdgeType::projection_type projection_type;

  CuttingEdgeType leave;
  CuttingEdgeType enter;
  int segment;
  bool hole;

  cut_polygon_segment ()
    : leave (), enter (), segment (-1), hole (false)
  {
    // .. nothing yet ..
  }

  bool operator< (const cut_polygon_segment &b) const
  {
    projection_type amin = std::min (leave.projected, enter.projected);
    projection_type bmin = std::min (b.leave.projected, b.enter.projected);

    projection_type amax = std::max (leave.projected, enter.projected);
    projection_type bmax = std::max (b.leave.projected, b.enter.projected);

    if (amin != bmin) {
      return amin < bmin;
    } else {
      int vs = db::vprod_sign (min_edge (), b.min_edge ());
      if (vs != 0) {
        return vs > 0;
      } else if (amax == amin) {
        return bmax != bmin;
      } else if (bmax == bmin) {
        return false;
      } else {
        return amax > bmax;
      }
    }
  }

  bool after (const cut_polygon_segment &b) const
  {
    projection_type pb_max = std::max (b.leave.projected, b.enter.projected);
    projection_type pa_min = std::min (leave.projected, enter.projected);

    if (pb_max < pa_min) {
      return true;
    } else if (pb_max > pa_min) {
      return false;
    } else {
      return db::vprod_sign (min_edge (), b.max_edge ()) <= 0;
    }
  }

  edge_type max_edge () const
  {
    if (leave.projected > enter.projected) {
      return edge_type (leave.last_point, leave.point);
    } else if (leave.projected < enter.projected) {
      return edge_type (enter.last_point, enter.point);
    } else {
      int vs = db::vprod_sign (leave.point - leave.last_point, enter.point - enter.last_point);
      if (vs < 0) {
        return edge_type (leave.last_point, leave.point);
      } else {
        return edge_type (enter.last_point, enter.point);
      }
    }
  }

  edge_type min_edge () const
  {
    if (leave.projected < enter.projected) {
      return edge_type (leave.last_point, leave.point);
    } else if (leave.projected > enter.projected) {
      return edge_type (enter.last_point, enter.point);
    } else {
      int vs = db::vprod_sign (leave.point - leave.last_point, enter.point - enter.last_point);
      if (vs > 0) {
        return edge_type (leave.last_point, leave.point);
      } else {
        return edge_type (enter.last_point, enter.point);
      }
    }
  }
};

template <class CuttingEdge, class CuttingEdgeSegment>
static void cut_polygon_produce_cut_points (typename std::vector<CuttingEdgeSegment>::const_iterator from, typename std::vector<CuttingEdgeSegment>::const_iterator to, std::vector<CuttingEdge> &output, bool holes)
{
  typename std::vector<CuttingEdgeSegment>::const_iterator e = from;
  while (e != to) {

    //  collect "illegal" segments (i.e. holes not being bracketed by a contour
    typename std::vector<CuttingEdgeSegment>::const_iterator e1 = e;
    for ( ; e != to && e->hole != holes; ++e) {
      ;
    }

    if (e == to) {
      //  In this case we have only wrong typed segments within the wrong bracketing segment (i.e. holes inside a hole bracket) or on the outside. 
      //  Sort the leaving and entering edges correctly.
      for (typename std::vector<CuttingEdgeSegment>::const_iterator o = e1; o != e; ++o) {
        if (! holes) {
          output.push_back (o->leave);
          output.push_back (o->enter);
        } else {
          output.push_back (o->enter);
          output.push_back (o->leave);
        }
      }
      return;
    }

    typename std::vector<CuttingEdgeSegment>::const_iterator ee = e + 1;
    for ( ; ee != to; ++ee) {
      if (e->hole == holes && ee->after (*e)) {
        break;
      }
    }

    if (e->hole) {
      output.push_back (e->enter);
    } else {
      output.push_back (e->leave);
    }

    //  include all illegal segments into the first "good" segment, so we have a correct hierarchy at least.
    if (e1 != e) {
      cut_polygon_produce_cut_points<CuttingEdge, CuttingEdgeSegment> (e1, e, output, !holes);
    } 

    if (e + 1 != ee) {
      cut_polygon_produce_cut_points<CuttingEdge, CuttingEdgeSegment> (e + 1, ee, output, !holes);
    }

    if (e->hole) {
      output.push_back (e->leave);
    } else {
      output.push_back (e->enter);
    }

    e = ee;

  }
}

template <class PolygonType, class Edge>
void cut_polygon_internal (const PolygonType &input, const Edge &line, CutPolygonReceiverBase *right_of_line)
{
  typedef typename PolygonType::point_type point_type;
  typedef typename PolygonType::coord_type coord_type;
  typedef typename PolygonType::area_type area_type;
  typedef typename PolygonType::contour_type contour_type;
  typedef db::edge<coord_type> edge_type;
  typedef cut_polygon_edge<point_type> cut_polygon_edge_type;
  typedef cut_polygon_segment<cut_polygon_edge_type> cutting_segment_type;
  typedef typename db::coord_traits<coord_type>::area_type projection_type;

  bool do_hole_assignment = (input.holes () > 0);
  std::vector <PolygonType> hull_polygons;
  std::vector <PolygonType> hole_polygons;

  std::vector<cutting_segment_type> cutting_segments;

  for (unsigned int nc = 0; nc < input.holes () + 1; ++nc) {

    const contour_type &contour = input.contour (nc);
    if (contour.size () == 0) {
      continue;
    }

    bool any = false;

    unsigned int nn = (unsigned int) contour.size () - 1;
    int sc = -1;
    size_t nfirst = cutting_segments.size ();

    point_type last_pt = contour[nn];
    for (unsigned int n = 0; n < contour.size (); ++n) {

      edge_type e (last_pt, contour[n]);
      last_pt = e.p2 ();

      std::pair <bool, point_type> ip = line.crossed_by_point (e);
      if (ip.first) {

        int s1 = line.side_of (e.p1 ());
        int s2 = line.side_of (e.p2 ());

        projection_type p = db::sprod (ip.second, line.p2 (), line.p1 ());

        if (s1 < 0 && s2 >= 0) {
          // right -> left or on edge
          if (cutting_segments.size () == nfirst) {
            cutting_segments.push_back (cutting_segment_type ());
          }
          cutting_segments.back ().leave = cut_polygon_edge_type (int (nc), nn, p, ip.second, e.p1 ());
          any = true;
        }

        if (s1 >= 0 && s2 < 0) {
          // left or on edge -> right 
          ++sc;
          cutting_segments.push_back (cutting_segment_type ());
          cutting_segments.back ().enter = cut_polygon_edge_type (int (nc), nn, p, ip.second, e.p2 ());
          cutting_segments.back ().segment = sc;
        }

      }

      nn = n;

    }

    if (any) {

      //  tie together last and first partial segments.
      if (cutting_segments[nfirst].segment < 0) {
        cutting_segments[nfirst].enter = cutting_segments.back ().enter;
        cutting_segments.pop_back ();
      }

      //  assign hull/hole identities ..
      for (typename std::vector<cutting_segment_type>::iterator c = cutting_segments.begin () + nfirst; c != cutting_segments.end (); ++c) {

        unsigned int n = (unsigned int) contour.size ();
        unsigned int n1 = c->enter.index;
        unsigned int n2 = c->leave.index;

        //  compute area of the segment and derive the hull part/hole part nature of the segment from the sign
        area_type a = 0;
        point_type pl = c->enter.point;
        for (unsigned int i = n1; ; ) {
          a += db::vprod (pl, contour[i]);
          pl = contour[i];
          if (i == n2) {
            break;
          }
          ++i;
          if (i == n) {
            i = 0;
          }
        }
        a += db::vprod (pl, c->leave.point);
        a += db::vprod (c->leave.point, c->enter.point);

        c->hole = (a > 0);

      }

    } else if (line.side_of (contour[0]) < 0) {

      if (do_hole_assignment) {

        if (nc == 0) {
          //  the hull is fully on the right side -> just output the input polygon and that's it.
          right_of_line->put (&input);
          return;
        } else {
          //  remember hole contours for later assignment
          hole_polygons.push_back (PolygonType ());
          hole_polygons.back ().assign_hull (contour.begin (), contour.end ());
        }

      } else {
        PolygonType poly;
        poly.assign_hull (contour.begin (), contour.end ());
        right_of_line->put (&poly);
      }
    }

  }

  std::sort (cutting_segments.begin (), cutting_segments.end ());

  std::vector<cut_polygon_edge_type> cutting_edges;
  cutting_edges.reserve (cutting_segments.size () * 2);

  cut_polygon_produce_cut_points<cut_polygon_edge_type, cutting_segment_type> (typename std::vector<cutting_segment_type>::const_iterator (cutting_segments.begin ()), typename std::vector<cutting_segment_type>::const_iterator (cutting_segments.end ()), cutting_edges, false);

  std::vector<point_type> contour_points;
  typedef std::map <std::pair<int, int>, std::pair<typename std::vector<cut_polygon_edge_type>::iterator, typename std::vector<cut_polygon_edge_type>::iterator> > cut_point_map_type;
  cut_point_map_type cut_points;

  for (typename std::vector<cut_polygon_edge_type>::iterator c = cutting_edges.begin (); c != cutting_edges.end (); c += 2) {
    cut_points.insert (std::make_pair (std::make_pair (c[0].contour, c[0].index), std::make_pair (c, c + 1)));
    cut_points.insert (std::make_pair (std::make_pair (c[1].contour, c[1].index), std::make_pair (c + 1, c)));
  }

  for (typename std::vector<cut_polygon_edge_type>::iterator c = cutting_edges.begin (); c != cutting_edges.end (); c += 2) {

    if (c->contour >= 0) {

      typename std::vector<cut_polygon_edge_type>::iterator c1 = c;
      typename std::vector<cut_polygon_edge_type>::iterator c2 = c + 1;

      contour_points.clear ();
      bool is_hull = false;

      do {

        tl_assert (c1->contour >= 0 && c2->contour >= 0);

        contour_points.push_back (c1->point);
        contour_points.push_back (c2->point);

        int n = c2->index;
        int n0 = n;
        int nc = c2->contour;
        const contour_type &contour = input.contour (nc);

        if (nc == 0) {
          is_hull = true;
        }

        c1->contour = -1;
        c2->contour = -1;

        ++n;
        if (n == int (contour.size ())) {
          n = 0;
        }

        while (n != n0) {

          contour_points.push_back (contour[n]);

          typename cut_point_map_type::iterator cp = cut_points.find (std::make_pair (nc, n));
          if (cp != cut_points.end ()) {
            c1 = cp->second.first;
            c2 = cp->second.second;
            break;
          }

          ++n;
          if (n == int (contour.size ())) {
            n = 0;
          }

        }

        tl_assert (n != n0);

      } while (c1 != c && c2 != c);

      //  Hint: the algorithm tends to create spikes for hole insertion edges.
      //  Therefore we used "remove reflected" on the assignment.
      if (do_hole_assignment) {

        if (is_hull) {
          hull_polygons.push_back (PolygonType ());
          hull_polygons.back ().assign_hull (contour_points.begin (), contour_points.end (), true, true /*remove reflected*/);
        } else {
          hole_polygons.push_back (PolygonType ());
          hole_polygons.back ().assign_hull (contour_points.begin (), contour_points.end (), true, true /*remove reflected*/);
        }

      } else {
        PolygonType poly;
        poly.assign_hull (contour_points.begin (), contour_points.end (), true, true /*remove reflected*/);
        //  it might happen in some cases, that cut pieces may vanish (i.e. all points on a line). Thus we check, if that
        //  is the case and do not produce a polygon then.
        if (poly.vertices () > 0) {
          right_of_line->put (&poly);
        }
      }

    }

  }

  //  do hole assignment
  for (typename std::vector<PolygonType>::iterator hull = hull_polygons.begin (); hull != hull_polygons.end (); ++hull) {

    //  it might happen in some cases, that cut pieces may vanish (i.e. all points on a line). Thus we check, if that
    //  is the case and do not produce a polygon then.
    if (hull->vertices () > 0) {

      db::inside_poly_test<PolygonType> inside_hull (*hull);
      for (typename std::vector<PolygonType>::iterator hole = hole_polygons.begin (); hole != hole_polygons.end (); ++hole) {
        size_t n = hole->hull ().size ();
        if (n > 0) {
          //  look for one point "really" inside ...
          int inside = 0;
          for (size_t i = 0; i < n && inside == 0; ++i) {
            inside = inside_hull (hole->hull ()[i]);
          }
          if (inside >= 0) {
            hull->insert_hole (hole->hull ().begin (), hole->hull ().end ());
            *hole = PolygonType ();
          }
        }
      }

      right_of_line->put (&*hull);

    }

  }

  // use non-assigned hole (parts) as hulls
  // TODO: precisely, this is possible only if the orientation is clockwise. Since we loose the orientation because
  // we assign to a PolygonType, this check is not possible.
  for (typename std::vector<PolygonType>::iterator hole = hole_polygons.begin (); hole != hole_polygons.end (); ++hole) {
    if (hole->vertices () > 0) {
      right_of_line->put (&*hole);
    }
  }
}

template KLAYOUT_DLL void cut_polygon_internal<> (const db::Polygon &polygon, const db::Polygon::edge_type &line, CutPolygonReceiverBase *right_of_line);
template KLAYOUT_DLL void cut_polygon_internal<> (const db::SimplePolygon &polygon, const db::SimplePolygon::edge_type &line, CutPolygonReceiverBase *right_of_line);
template KLAYOUT_DLL void cut_polygon_internal<> (const db::DPolygon &polygon, const db::DPolygon::edge_type &line, CutPolygonReceiverBase *right_of_line);
template KLAYOUT_DLL void cut_polygon_internal<> (const db::DSimplePolygon &polygon, const db::DSimplePolygon::edge_type &line, CutPolygonReceiverBase *right_of_line);

// -------------------------------------------------------------------------
//  Implementation of split_polygon

template <class PolygonType>
void
split_polygon (const PolygonType &polygon, std::vector<PolygonType> &output)
{
  typedef typename PolygonType::coord_type coord_type;
  typedef typename PolygonType::point_type point_type;
  typedef typename PolygonType::box_type box_type;
  typedef db::edge<coord_type> edge_type;

  box_type bbox = polygon.box ();
  box_type b1, b2;

  coord_type x = bbox.center ().x ();
  coord_type xx = x;
  bool xx_set = false;

  coord_type y = bbox.center ().y ();
  coord_type yy = y;
  bool yy_set = false;

  for (typename PolygonType::polygon_contour_iterator e = polygon.begin_hull (); e != polygon.end_hull (); ++e) {
    if ((*e).x () != bbox.left () && (*e).x () != bbox.right () && (std::abs ((*e).x () - x) < std::abs (xx - x) || ! xx_set)) {
      xx = (*e).x ();
      xx_set = true;
    }
    if ((*e).y () != bbox.top () && (*e).y () != bbox.bottom () && (std::abs ((*e).y () - y) < std::abs (yy - y) || ! yy_set)) {
      yy = (*e).y ();
      yy_set = true;
    }
  }

  if (! xx_set && ! yy_set) {
    if (bbox.width () > bbox.height ()) { 
      xx_set = true;
    } else {
      yy_set = true;
    }
  } else if (xx_set && yy_set) {
    //  an empiric threshold for splitting polygons in one direction: don't split along the long
    //  axis for polygons with a aspect ratio (of the bounding box) of larger than 3
    if (bbox.width () > 3 * bbox.height ()) {
      yy_set = false;
    } else if (bbox.height () > 3 * bbox.width ()) {
      xx_set = false;
    }
  }

  std::vector <PolygonType> xx_polygons;
  size_t xx_n = std::numeric_limits<size_t>::max ();
  if (xx_set) {

    db::cut_polygon (polygon, edge_type (point_type (xx, 0), point_type (xx, 1)), std::back_inserter (xx_polygons));
    db::cut_polygon (polygon, edge_type (point_type (xx, 1), point_type (xx, 0)), std::back_inserter (xx_polygons));
    
    xx_n = 0;
    for (typename std::vector <PolygonType>::const_iterator p = xx_polygons.begin (); p != xx_polygons.end (); ++p) {
      xx_n += p->vertices ();
    }

  }

  std::vector <PolygonType> yy_polygons;
  size_t yy_n = std::numeric_limits<size_t>::max ();
  if (yy_set) {

    db::cut_polygon (polygon, edge_type (point_type (0, yy), point_type (1, yy)), std::back_inserter (yy_polygons));
    db::cut_polygon (polygon, edge_type (point_type (1, yy), point_type (0, yy)), std::back_inserter (yy_polygons));
    
    yy_n = 0;
    for (typename std::vector <PolygonType>::const_iterator p = yy_polygons.begin (); p != yy_polygons.end (); ++p) {
      yy_n += p->vertices ();
    }

  }

  if (xx_n < yy_n) {
    output.swap (xx_polygons);
  } else {
    output.swap (yy_polygons);
  }
}

template void split_polygon<> (const db::Polygon &polygon, std::vector<db::Polygon> &output);
template void split_polygon<> (const db::SimplePolygon &polygon, std::vector<db::SimplePolygon> &output);
template void split_polygon<> (const db::DPolygon &polygon, std::vector<db::DPolygon> &output);
template void split_polygon<> (const db::DSimplePolygon &polygon, std::vector<db::DSimplePolygon> &output);

// -------------------------------------------------------------------------
//  Smoothing tools

void 
smooth_contour (db::Polygon::polygon_contour_iterator from, db::Polygon::polygon_contour_iterator to, std::vector <db::Point> &points, db::Coord d)
{
  points.clear ();
  points.reserve (std::distance (from, to));

  std::vector<db::Point> org_points;
  std::vector<size_t> point_indexes;
  point_indexes.reserve (std::distance (from, to));

  //  collect the points into a vector

  size_t pi = 0;
  for (db::Polygon::polygon_contour_iterator p = from; p != to; ++p, ++pi) {
    points.push_back (*p);
    point_indexes.push_back (pi);
  }

  org_points = points;

  //  proceed until there is nothing to do
  
  bool even = false;
  int cont = 2;
  while (points.size () > 3 && cont > 0) {

    std::vector<db::Point> new_points;
    new_points.reserve (points.size ());
    std::vector<size_t> new_point_indexes;
    new_point_indexes.reserve (points.size ());

    bool any = false;

    size_t i;
    bool first_point_deleted = false;
    for (i = (even ? 0 : 1); i < points.size (); i += 2) {

      if (i == points.size () - 1 && first_point_deleted) {
        break;
      }

      db::Point p0 = points [(i + points.size () - 1) % points.size ()];
      db::Point p1 = points [i];
      db::Point p2 = points [(i + 1) % points.size ()];

      size_t pi0 = point_indexes [(i + points.size () - 1) % points.size ()];
      size_t pi1 = point_indexes [i];
      size_t pi2 = point_indexes [(i + 1) % points.size ()];

      if (i > 0) {
        new_points.push_back (p0);
        new_point_indexes.push_back (pi0);
      }

      bool can_drop = (db::sprod_sign (p2 - p1, p1 - p0) > 0);

      //  Limit smoothing to edges enclosing a little more than 45 degree
      if (can_drop && abs (db::vprod (p2 - p1, p1 - p0)) > 0.8 * p2.distance (p1) * p1.distance (p0)) {
        can_drop = false;
      }

      for (size_t j = pi0; can_drop; ) {
        if (abs (db::Edge (p0, p2).distance (org_points [j])) > d) {
          can_drop = false;
        }
        if (j == pi2) {
          break;
        }
        ++j;
        if (j == org_points.size ()) {
          j = 0;
        }
      }

      if (can_drop) {
        //  drop this point
        any = true;
        if (i == 0) {
          first_point_deleted = true;
        }
      } else {
        new_points.push_back (p1);
        new_point_indexes.push_back (pi1);
      }

    }

    if (any) {
      cont = 2;
    } else {
      cont -= 1;
    }

    while (i <= points.size ()) {
      new_points.push_back (points [i - 1]);
      new_point_indexes.push_back (point_indexes [i - 1]);
      ++i;
    }

    points.swap (new_points);
    point_indexes.swap (new_point_indexes);

    even = !even;

  }
}

db::Polygon 
smooth (const db::Polygon &polygon, db::Coord d)
{
  db::Polygon new_poly;
  std::vector <db::Point> new_pts;

  smooth_contour (polygon.begin_hull (), polygon.end_hull (), new_pts, d);
  new_poly.assign_hull (new_pts.begin (), new_pts.end (), false /*don't compress*/);

  for (unsigned int h = 0; h < polygon.holes (); ++h) {
    new_pts.clear ();
    smooth_contour (polygon.begin_hole (h), polygon.end_hole (h), new_pts, d);
    new_poly.insert_hole (new_pts.begin (), new_pts.end (), false /*don't compress*/);
  }

  return new_poly;
}

// -------------------------------------------------------------------------
//  Rounding tools

bool 
extract_rad_from_contour (db::Polygon::polygon_contour_iterator from, db::Polygon::polygon_contour_iterator to, double &rinner, double &router, unsigned int &n, std::vector <db::Point> *new_pts, bool fallback)
{
  if (from == to) {
    return false;
  }

  db::Polygon::polygon_contour_iterator p0 = from;

  db::Polygon::polygon_contour_iterator p1 = p0;
  ++p1;
  if (p1 == to) {
    p1 = from;
  }
  db::Polygon::polygon_contour_iterator p2 = p1;

  const double cos_thr = 0.8;
  const double circle_segment_thr = 2.5;

  //  search for the first circle segment (where cos(a) > cos_thr) 
  double ls_inner = 0.0, ls_outer = 0.0;
  unsigned long n_ls_inner = 0, n_ls_outer = 0;

  if (! fallback) {

    do {

      ++p2;
      if (p2 == to) {
        p2 = from;
      }

      db::Edge ep (*p0, *p1);
      db::Edge e (*p1, *p2);

      bool inner = (db::vprod_sign (ep, e) > 0);
      double &ls = inner ? ls_inner : ls_outer;
      unsigned long &n_ls = inner ? n_ls_inner : n_ls_outer;

      if (db::sprod (ep, e) > cos_thr * e.double_length () * ep.double_length ()) {
        ls += std::min (e.double_length (), ep.double_length ());
        ++n_ls;
      }

      p0 = p1;
      p1 = p2;

    } while (p0 != from);

    if (n_ls_inner > 0) {
      ls_inner /= n_ls_inner;
    }
    if (n_ls_outer > 0) {
      ls_outer /= n_ls_outer;
    }

  }

  bool found = false;

  //  search for the first circle segment (where cos(a) > cos_thr) 
  //  or a long segment is followed by a short one or the curvature changes.

  db::Polygon::polygon_contour_iterator pm1 = from;

  p0 = pm1;
  ++p0;
  if (p0 == to) {
    p0 = from;
  }

  p1 = p0;
  ++p1;
  if (p1 == to) {
    p1 = from;
  }

  p2 = p1;
  ++p2;
  if (p2 == to) {
    p2 = from;
  }

  db::Polygon::polygon_contour_iterator p3 = p2;

  do {

    ++p3;
    if (p3 == to) {
      p3 = from;
    }

    db::Edge em (*pm1, *p0);
    db::Edge ep (*p0, *p1);
    db::Edge e (*p1, *p2);
    db::Edge en (*p2, *p3);

    bool first_or_last = fallback || (e.double_length () > circle_segment_thr * ep.double_length () || ep.double_length () > circle_segment_thr * e.double_length ()) 
                                  || (db::vprod_sign (em, ep) * db::vprod_sign (ep, e) < 0 || db::vprod_sign (ep, e) * db::vprod_sign (e, en) < 0);

    if (first_or_last && db::sprod (ep, e) > cos_thr * e.double_length () * ep.double_length ()) {
      double ls = (db::vprod_sign (ep, e) > 0 ? ls_inner : ls_outer);
      if (! fallback && ((e.double_length () < circle_segment_thr * ls && ep.double_length () > circle_segment_thr * ls) 
                         || db::vprod_sign (em, ep) * db::vprod_sign (ep, e) < 0)) {
        found = true;
        break;
      } else if (fallback && (ep.dx () == 0 || ep.dy () == 0)) {
        found = true;
        break;
      }
    }

    pm1 = p0;
    p0 = p1;
    p1 = p2;
    p2 = p3;

  } while (pm1 != from);

  if (! found) {
    return false;
  }

  //  create a list of new points without the rounded corners and compute rounding radii

  if (new_pts) {
    new_pts->clear ();
  }

  db::Polygon::polygon_contour_iterator pfirst = p0;
  bool in_corner = false;
  double ls_corner = 0.0;
  db::Edge elast;
  db::Polygon::polygon_contour_iterator plast;
  double asum = 0.0;
  unsigned int nseg = 0;

  double rxi_sum = 0.0;
  double rxo_sum = 0.0;
  double da_sum = 0.0;
  int n_corners = 0;
  int ni_corners = 0;
  int no_corners = 0;

  p3 = p2;

  do {

    ++p3;
    if (p3 == to) {
      p3 = from;
    }

    db::Edge em (*pm1, *p0);
    db::Edge ep (*p0, *p1);
    db::Edge e (*p1, *p2);
    db::Edge en (*p2, *p3);

    //  Heuristic detection of a new circle segment: 
    //  In fallback mode vertical or horizontal edges separate circle segments.
    //  In non-fallback mode either a long edge followed by a short one indicates the beginning of a new
    //  circle segment or a circle segment is detected when the curvature changes.
    //  The latter case detects situations where two circle segments directly attach to each other
    //  with different bending direction.

    bool first_or_last = fallback || (e.double_length () > circle_segment_thr * ep.double_length () || ep.double_length () > circle_segment_thr * e.double_length ())
                                  || (db::vprod_sign (em, ep) * db::vprod_sign (ep, e) < 0 || db::vprod_sign (ep, e) * db::vprod_sign (e, en) < 0);

    if (db::sprod (ep, e) > cos_thr * e.double_length () * ep.double_length ()) { 

      double ls = db::vprod_sign (ep, e) > 0 ? ls_inner : ls_outer;

      if ((! fallback && first_or_last && ((e.double_length () < circle_segment_thr * ls && ep.double_length () > circle_segment_thr * ls) || db::vprod_sign (em, ep) * db::vprod_sign (ep, e) < 0)) ||
          (fallback && (ep.dx () == 0 || ep.dy () == 0))) {

        if (! in_corner) {
          elast = ep;
          plast = p1;
          asum = db::vprod (*p1, *p2);
          nseg = 1;
          ls_corner = ls;
        } 
        in_corner = true;

      } else if ((!fallback && first_or_last && ((e.double_length () > circle_segment_thr * ls_corner && ep.double_length () < circle_segment_thr * ls_corner) || db::vprod_sign (ep, e) * db::vprod_sign (e, en) < 0)) ||
                 (fallback && (e.dx () == 0 || e.dy () == 0))) {

        if (in_corner) {

          std::pair<bool, db::Point> cp = elast.cut_point (e);
          if (! cp.first) {

            //  We have a full 180 degree bend without a stop (actually two corners).
            //  Use the segment in between that is perpendicular to the start and end segment as stop edge.
            db::Polygon::polygon_contour_iterator pp1 = plast;
            db::Polygon::polygon_contour_iterator pp2 = pp1;
            double asum_part = 0.0;
            unsigned int nseg_part = 0;

            while (pp1 != p1) {

              ++pp2;
              if (pp2 == to) {
                pp2 = from;
              }

              e = db::Edge (*pp1, *pp2);
              if (db::sprod_sign (elast, e) == 0) {
                break;
              }

              asum_part += db::vprod (*pp1, *pp2);
              ++nseg_part;

              pp1 = pp2;

            }

            cp = elast.cut_point (e);
            if (! cp.first) {
              return false;
            }

            if (new_pts) {
              new_pts->push_back (cp.second);
            }

            ++nseg_part;

            asum -= asum_part;
            asum -= db::vprod (e.p1 (), e.p2 ());
            nseg -= nseg_part;

            asum_part += db::vprod (cp.second, elast.p2 ());
            asum_part += db::vprod (*pp1, cp.second);

            double sin_atot = db::vprod (elast, e);
            double cos_atot = db::sprod (elast, e);
            double atot = fabs (atan2 (sin_atot, cos_atot));

            double rx = sqrt (fabs (asum_part) * 0.5 / (tan (atot * 0.5) - tan (atot * 0.5 / nseg_part) * nseg_part));
            double da = atot / nseg_part;

            if (sin_atot > 0.0) {
              rxi_sum += rx;
              ++ni_corners;
            } else {
              rxo_sum += rx;
              ++no_corners;
            }

            da_sum += da;
            ++n_corners;

            elast = e;

            e = db::Edge (*p1, *p2);
            cp = elast.cut_point (e);
            if (! cp.first) {
              return false;
            }

          }

          if (new_pts) {
            new_pts->push_back (cp.second);
          }

          asum += db::vprod (cp.second, elast.p2 ());
          asum += db::vprod (*p1, cp.second);

          ++nseg;

          double sin_atot = db::vprod (elast, e);
          double cos_atot = db::sprod (elast, e);
          double atot = fabs (atan2 (sin_atot, cos_atot));

          double rx = sqrt (fabs (asum) * 0.5 / (tan (atot * 0.5) - tan (atot * 0.5 / nseg) * nseg));
          double da = atot / nseg;

          if (sin_atot > 0.0) {
            rxi_sum += rx;
            ++ni_corners;
          } else {
            rxo_sum += rx;
            ++no_corners;
          }

          da_sum += da;
          ++n_corners;

        }
        in_corner = false;

      } else if (in_corner) {

        asum += db::vprod (*p1, *p2);
        ++nseg;

      } else {
        if (new_pts) {
          new_pts->push_back (*p1);
        }
      }

    } else {
      if (new_pts) {
        new_pts->push_back (*p1);
      }
    }

    pm1 = p0;
    p0 = p1;
    p1 = p2;
    p2 = p3;

  } while (p0 != pfirst);

  if (n_corners < 2) {

    return false;

  } else {
    n = (unsigned int) floor (2.0 * M_PI / (da_sum / n_corners) + 0.5);
    if (ni_corners > 0) {
      rinner = floor ((rxi_sum / ni_corners * 0.5) + 0.5) * 2;
    } 
    if (no_corners > 0) {
      router = floor ((rxo_sum / no_corners * 0.5) + 0.5) * 2;
    }
    return true;
  }
}

bool 
extract_rad (const db::Polygon &polygon, double &rinner, double &router, unsigned int &n, db::Polygon *new_polygon)
{
  if (new_polygon) {

    std::vector <db::Point> new_pts;

    if (! extract_rad_from_contour (polygon.begin_hull (), polygon.end_hull (), rinner, router, n, &new_pts) && 
        ! extract_rad_from_contour (polygon.begin_hull (), polygon.end_hull (), rinner, router, n, &new_pts, true)) {
      //  no radius found
      return false;
    } else {
      new_polygon->assign_hull (new_pts.begin (), new_pts.end (), true /*compress*/);
    }

    for (unsigned int h = 0; h < polygon.holes (); ++h) {

      new_pts.clear ();
      if (! extract_rad_from_contour (polygon.begin_hole (h), polygon.end_hole (h), rinner, router, n, &new_pts) && 
          ! extract_rad_from_contour (polygon.begin_hole (h), polygon.end_hole (h), rinner, router, n, &new_pts, true)) {
        //  no radius found
        return false;
      } else {
        new_polygon->insert_hole (new_pts.begin (), new_pts.end (), true /*compress*/);
      }

    }

  } else {

    if (! extract_rad_from_contour (polygon.begin_hull (), polygon.end_hull (), rinner, router, n, 0)) {
      if (! extract_rad_from_contour (polygon.begin_hull (), polygon.end_hull (), rinner, router, n, 0, true)) {
        return false;
      }
    }

    for (unsigned int h = 0; h < polygon.holes (); ++h) {
      if (! extract_rad_from_contour (polygon.begin_hole (h), polygon.end_hole (h), rinner, router, n, 0)) {
        if (! extract_rad_from_contour (polygon.begin_hole (h), polygon.end_hole (h), rinner, router, n, 0, true)) {
          return false;
        }
      }
    }

  }

  return true;

}

void 
compute_rounded_contour (db::Polygon::polygon_contour_iterator from, db::Polygon::polygon_contour_iterator to, std::vector <db::Point> &new_pts, double rinner, double router, unsigned int n)
{
  std::vector<db::Point> points;

  //  collect the points into a vector

  if (from != to) {

    db::Polygon::polygon_contour_iterator p0 = from;
    db::Polygon::polygon_contour_iterator p1 = p0;
    ++p1;
    if (p1 == to) {
      p1 = from;
    }
    db::Polygon::polygon_contour_iterator p2 = p1;

    do {

      ++p2;
      if (p2 == to) {
        p2 = from;
      }

      if (! db::Edge (*p0, *p1).parallel (db::Edge (*p1, *p2))) {
        points.push_back (*p1);
      }

      p0 = p1;
      p1 = p2;

    } while (p0 != from);

  }

  //  compute the radii and segment length 

  std::vector<double> rad (points.size (), 0.0);
  std::vector<double> seg (points.size (), 0.0);

  for (size_t i = 0; i < points.size (); ++i) {

    db::Point p0 = points [(i + points.size () - 1) % points.size ()];
    db::Point p1 = points [i];
    db::Point p2 = points [(i + points.size () + 1) % points.size ()];

    db::DPoint e1 = (db::DPoint (p1) - db::DPoint (p0)) * (1.0 / p0.double_distance (p1));
    db::DPoint e2 = (db::DPoint (p2) - db::DPoint (p1)) * (1.0 / p1.double_distance (p2));

    double sin_a = db::vprod (e1, e2);
    double cos_a = db::sprod (e1, e2);
    double a = fabs (atan2 (sin_a, cos_a));

    double r = sin_a > 0.0 ? rinner : router;
    double s = r * fabs (sin (a * 0.5) / cos (a * 0.5));

    rad [i] = r;
    seg [i] = s;

  }

  //  compute the rounded points

  for (size_t i = 0; i < points.size (); ++i) {

    db::Point p0 = points [(i + points.size () - 1) % points.size ()];
    db::Point p1 = points [i];
    db::Point p2 = points [(i + points.size () + 1) % points.size ()];

    db::DPoint e1 = (db::DPoint (p1) - db::DPoint (p0)) * (1.0 / p0.double_distance (p1));
    db::DPoint e2 = (db::DPoint (p2) - db::DPoint (p1)) * (1.0 / p1.double_distance (p2));

    double sin_a = db::vprod (e1, e2);
    double cos_a = db::sprod (e1, e2);
    double a = fabs (atan2 (sin_a, cos_a));

    double s0 = seg [(i + points.size () - 1) % points.size ()];
    double s1 = seg [i];
    double s2 = seg [(i + points.size () + 1) % points.size ()];

    double f0 = std::min (1.0, p0.double_distance (p1) / (s0 + s1));
    double f1 = std::min (1.0, p1.double_distance (p2) / (s1 + s2));
    double r = std::min (f0, f1) * rad [i];

    if (r > 0.0) {

      db::DPoint q0 = db::DPoint (p1) - e1 * (tan (a * 0.5) * r);
      db::DPoint n1;
      if (sin_a > 0) {
        n1 = db::DPoint (e1.y (), -e1.x ());
      } else {
        n1 = db::DPoint (-e1.y (), e1.x ());
      }
      db::DPoint pr = q0 - n1 * r;

      double ares = (2.0 * M_PI) / double (n);
      unsigned int nseg = (unsigned int) floor (a / ares + 0.5);
      if (nseg == 0) {
        new_pts.push_back (p1);
      } else {

        double da = a / floor (a / ares + 0.5);
        for (double aa = 0.0; aa < a - 1e-6; aa += da) {

          db::DPoint q1 = pr + n1 * (r * cos (aa + da)) + e1 * (r * sin (aa + da));

          //  do a interpolation by computing the crossing point of the tangents of the
          //  circle at a and a+da. This scheme guarantees a low distortion of the original
          //  polygon and enables reverting back to the original polygon to some degree.
          db::DPoint qm = (q0 + q1) * 0.5;
          db::DPoint q = qm + (qm - pr) * (q0.sq_distance (qm) / pr.sq_distance (qm));

          new_pts.push_back (db::Point::from_double (q));

          q0 = q1;

        }

      }

    } else {
      new_pts.push_back (p1);
    }

  } 
}

db::Polygon 
compute_rounded (const db::Polygon &polygon, double rinner, double router, unsigned int n)
{
  db::Polygon new_poly;
  std::vector <db::Point> new_pts;

  compute_rounded_contour (polygon.begin_hull (), polygon.end_hull (), new_pts, rinner, router, n);
  new_poly.assign_hull (new_pts.begin (), new_pts.end (), false /*don't compress*/);

  for (unsigned int h = 0; h < polygon.holes (); ++h) {
    new_pts.clear ();
    compute_rounded_contour (polygon.begin_hole (h), polygon.end_hole (h), new_pts, rinner, router, n);
    new_poly.insert_hole (new_pts.begin (), new_pts.end (), false /*don't compress*/);
  }

  return new_poly;
}

// -------------------------------------------------------------------------
//  Implementation of AreaMap

AreaMap::AreaMap ()
  : m_nx (0), m_ny (0)
{
  mp_av = 0;
}

AreaMap::AreaMap (const db::Point &p0, const db::Vector &d, size_t nx, size_t ny)
  : m_p0 (p0), m_d (d), m_nx (nx), m_ny (ny)
{
  mp_av = new area_type [nx * ny];
  clear ();
}

AreaMap::~AreaMap ()
{
  if (mp_av) {
    delete[] mp_av;
  }
  mp_av = 0;
}

void
AreaMap::reinitialize (const db::Point &p0, const db::Vector &d, size_t nx, size_t ny)
{
  m_p0 = p0;
  m_d = d;
  m_nx = nx;
  m_ny = ny;

  if (mp_av) {
    delete mp_av;
  }

  mp_av = new area_type [nx * ny];

  clear ();
}

void
AreaMap::clear ()
{
  if (mp_av) {
    area_type *a = mp_av;
    for (size_t n = m_nx * m_ny; n > 0; --n) {
      *a++ = 0;
    }
  }
}

void
AreaMap::swap (AreaMap &other)
{
  std::swap (m_p0, other.m_p0);
  std::swap (m_d, other.m_d);
  std::swap (m_nx, other.m_nx);
  std::swap (m_ny, other.m_ny);
  std::swap (mp_av, other.mp_av);
}

AreaMap::area_type 
AreaMap::total_area () const
{
  area_type asum = 0;
  if (mp_av) {
    const area_type *a = mp_av;
    for (size_t n = m_nx * m_ny; n > 0; --n) {
      asum += *a++;
    }
  }
  return asum;
}

// -------------------------------------------------------------------------
//  Implementation of rasterize

void
rasterize (const db::Polygon &polygon, db::AreaMap &am)
{
  typedef db::AreaMap::area_type area_type;
  db::Box box = am.bbox ();
  db::Box pbox = polygon.box ();

  //  check if the polygon overlaps the rasterization area. Otherwise, we simply do nothing.
  if (! pbox.overlaps (box)) {
    return;
  }

  db::Coord ymin = box.bottom (), ymax = box.top ();
  db::Coord dy = am.d ().y (), dx = am.d ().x ();
  db::Coord y0 = am.p0 ().y (), x0 = am.p0 ().x ();
  size_t ny = am.ny (), nx = am.nx ();

  size_t iy0 = std::min (ny, size_t (std::max (db::Coord (0), (pbox.bottom () - am.p0 ().y ()) / am.d ().y ())));
  size_t iy1 = std::min (ny, size_t (std::max (db::Coord (0), (pbox.top () - am.p0 ().y () + am.d ().y () - 1) / am.d ().y ())));

  size_t ix0 = std::min (nx, size_t (std::max (db::Coord (0), (pbox.left () - am.p0 ().x ()) / am.d ().x ())));
  size_t ix1 = std::min (nx, size_t (std::max (db::Coord (0), (pbox.right () - am.p0 ().x () + am.d ().x () - 1) / am.d ().x ())));

  //  no scanning required (i.e. degenerated polygon) -> do nothing 
  if (iy0 == iy1 || ix0 == ix1) {
    return;
  }

  //  collect edges 
  size_t n = 0;
  for (db::Polygon::polygon_edge_iterator e = polygon.begin_edge (); ! e.at_end (); ++e) {
    if ((*e).dy () != 0 && db::edge_ymax (*e) > ymin && db::edge_ymin (*e) < ymax) {
      ++n;
    }
  }

  std::vector <db::Edge> edges;
  edges.reserve (n);
  for (db::Polygon::polygon_edge_iterator e = polygon.begin_edge (); ! e.at_end (); ++e) {
    if ((*e).dy () != 0 && db::edge_ymax (*e) > ymin && db::edge_ymin (*e) < ymax) {
      edges.push_back (*e);
    }
  }

  //  sort edges
  std::sort (edges.begin (), edges.end (), db::edge_ymin_compare<db::Coord> ());

  std::vector <db::Edge>::iterator c = edges.begin ();

  db::Coord y = y0 + dy * db::Coord (iy0);

  while (c != edges.end () && db::edge_ymax (*c) <= y) {
    ++c;
  }

  std::vector <db::Edge>::iterator f = c;

  for (size_t iy = iy0; iy < iy1; ++iy) {

    db::Coord yy = y + dy;
    while (f != edges.end () && db::edge_ymin (*f) < yy) {
      ++f;
    }

    std::sort (c, f, db::edge_xmin_compare <db::Coord> ());

    db::Coord x = x0 + dx * db::Coord (ix0);
    db::Coord xl = pbox.left ();
    area_type a = 0;

    std::vector <db::Edge>::iterator cc = c;

    while (cc != edges.end () && db::edge_xmax (*cc) <= x) {
      db::Coord y1 = std::max (y, std::min (yy, cc->p1 ().y ()));
      db::Coord y2 = std::max (y, std::min (yy, cc->p2 ().y ()));
      a += area_type (dx) * area_type (y2 - y1);
      ++cc;
    }

    std::vector <db::Edge>::iterator ff = cc;

    for (size_t ix = ix0; ix < ix1; ++ix) {

      db::Coord xx = x + dx;

      // TODO: edge_xmin_at_interval(y, yy) and edge_xmax.. would be more efficient in the
      // all-angle case. However, it is crucial that the edge clipping produces 
      // connected edge segments and it is questionable whether the at_interval 
      // functions produce a sorting/filter criterion compatible with the clip.

      while (ff != f && db::edge_xmin (*ff) < xx) {
        ++ff;
      }

      if (xl < x) {

        //  consider all edges or parts of those left of the first cell
        db::Box left (xl, y, x, yy);

        for (std::vector <db::Edge>::iterator e = cc; e != ff; ++e) {

          std::pair<bool, db::Edge> ec = e->clipped (left);
          if (ec.first && db::edge_xmin (ec.second) < x) {
            a += area_type (ec.second.dy ()) * area_type (dx);
          }

        }

      }

      db::Box cell (x, y, xx, yy);

      area_type aa = a;

      for (std::vector <db::Edge>::iterator e = cc; e != ff; ++e) {

        std::pair<bool, db::Edge> ec = e->clipped (cell);
        if (ec.first && db::edge_xmin (ec.second) < xx) {

          aa += area_type (ec.second.dy ()) * area_type (2 * xx - (ec.second.p2 ().x () + ec.second.p1 ().x ())) / 2;
          a += area_type (ec.second.dy ()) * area_type (dx);

        }

      }

      am.get (ix, iy) += aa;

      x = xx;
      xl = xx;

      for (std::vector <db::Edge>::iterator ccx = cc; ccx != ff; ++ccx) {
        if (db::edge_xmax (*ccx) <= x) {
          std::swap (*ccx, *cc);
          ++cc;
        }
      }

    }

    y = yy;

    for (std::vector <db::Edge>::iterator cx = c; cx != f; ++cx) {
      if (db::edge_ymax (*cx) <= y) {
        std::swap (*cx, *c);
        ++c;
      }
    }

  }

}

// -------------------------------------------------------------------------
//  Implementation of minkowsky_sum

/**
 *  @brief A helper class that produces edges into an EdgeProcessor from a sequence of points
 */
class EdgeInputIterator
{
public:
  EdgeInputIterator (db::EdgeProcessor &ep, bool inverse = false)
    : m_last_set (false), m_last (), mp_ep (&ep), m_inverse (inverse)
  { }

  ~EdgeInputIterator ()
  {
    //  close the polygon
    if (m_last_set && m_last != m_first) {
      if (!m_inverse) {
        mp_ep->insert (db::Edge (m_last, m_first));
      } else {
        mp_ep->insert (db::Edge (m_first, m_last));
      }
      m_last_set = false;
    }

    mp_ep = 0;
  }

  void operator+= (const db::Point &p)
  {
    if (m_last_set) {
      if (!m_inverse) {
        mp_ep->insert (db::Edge (m_last, p));
      } else {
        mp_ep->insert (db::Edge (p, m_last));
      }
    } else {
      m_first = p;
    }

    m_last = p;
    m_last_set = true;
  }

private:
  bool m_last_set;
  db::Point m_last, m_first;
  db::EdgeProcessor *mp_ep;
  bool m_inverse;
};

/**
 *  @brief Produce edges for the partial Minkowsky sum of an edge with an input polygon
 */
static void
ms_production (const db::Polygon &a, const db::Point &p1, const db::Point &p2, db::EdgeProcessor &ep)
{
  double d12 = p2.double_distance (p1); 
  db::DPoint d (-double (p2.y () - p1.y ()) / d12, double (p2.x () - p1.x ()) / d12);

  db::EdgeInputIterator e (ep);

  db::Polygon::polygon_contour_iterator ci = a.begin_hull ();
  db::Polygon::polygon_contour_iterator cf = a.end_hull ();

  db::Polygon::polygon_contour_iterator cmin = cf, cmax = cf;
  double pmin = 0.0, pmax = 0.0;

  //  Look for the points in the contour bounding the partial sum perpendicular to the edge
  for (db::Polygon::polygon_contour_iterator c = ci; c != cf; ++c) {

    double p = (*c).x() * d.x () + (*c).y () * d.y ();

    if (cmin == cf || pmin > p) {
      pmin = p;
      cmin = c;
    }

    if (cmax == cf || pmax < p) {
      pmax = p;
      cmax = c;
    }

  }

  tl_assert (cmin != cf && cmax != cf);

  db::Polygon::polygon_contour_iterator c = cmin;
  db::Polygon::polygon_contour_iterator cc = cf;
  db::Polygon::polygon_contour_iterator cl = cf;

  bool pcc_set = false;
  double pcc = 0.0;

  while (true) {

    double pc = (*c).x() * d.x () + (*c).y () * d.y ();

    // detect inversion due to a convex pattern and create a cover polygon for that case
    if (pcc_set) {

      cc = c;
      if (cc == ci) {
        cc = cf;
      }
      --cc;

      if (pcc > pc + 1e-6) {

        if (cl == cf) {
          cl = cc;
        }

      } else if (cl != cf) {

        EdgeInputIterator ee (ep, true);

        // create the cover polygon
        db::Polygon::polygon_contour_iterator k = cl;

        while (k != cc) {
          ee += (p1 + *k);
          if (++k == cf) {
            k = ci;
          }
        }

        ee += (p1 + *k);

        while (k != cl) {
          ee += (p2 + *k);
          if (k == ci) {
            k = cf;
          }
          --k;
        }

        ee += (p2 + *cl);

        cl = cf;

      }

    }

    // produce a new edge
    e += (p1 + *c); 

    if (c == cmax) {
      break;
    }

    if (++c == cf) {
      c = ci;
    }

    pcc = pc;
    pcc_set = true;

  }

  cl = cf;
  pcc_set = false;

  while (true) {

    double pc = (*c).x() * d.x () + (*c).y () * d.y ();

    // detect inversion due to a convex pattern and create a cover polygon for that case
    if (pcc_set) {

      cc = c;
      if (cc == ci) {
        cc = cf;
      }
      --cc;

      pcc = (*cc).x() * d.x () + (*cc).y () * d.y ();

      if (pcc < pc - 1e-6) {

        if (cl == cf) {
          cl = cc;
        }

      } else if (cl != cf) {

        EdgeInputIterator ee (ep, true);

        // create the cover polygon
        db::Polygon::polygon_contour_iterator k = cl;

        // create the cover polygon
        while (k != cc) {
          ee += (p2 + *k);
          if (++k == cf) {
            k = ci;
          }
        }

        ee += (p2 + *cc);

        while (k != cl) {
          ee += (p1 + *k);
          if (k == ci) {
            k = cf;
          }
          --k;
        }

        ee += (p1 + *cl);

        cl = cf;

      }

    }

    e += (p2 + *c);

    if (c == cmin) {
      break;
    }

    if (++c == cf) {
      c = ci;
    }

    pcc = pc;
    pcc_set = true;

  }

}

static db::Polygon 
ms_extraction (db::EdgeProcessor &ep, bool resolve_holes)
{
  db::SimpleMerge op (-1);
  std::vector <db::Polygon> polygons;
  db::PolygonContainer pc (polygons);
  db::PolygonGenerator out (pc, resolve_holes, false);
  ep.process (out, op);

  if (polygons.empty ()) {
    return db::Polygon ();
  } else {
    tl_assert (polygons.size () == 1);
    return polygons [0];
  }
}

static db::Polygon 
do_minkowsky_sum (const db::Polygon &a, const db::Edge &b, bool resolve_holes)
{
  db::EdgeProcessor ep;
  db::ms_production (a, b.p1 (), b.p2 (), ep);
  return db::ms_extraction (ep, resolve_holes);
}

db::Polygon 
minkowsky_sum (const db::Polygon &a, const db::Edge &b, bool rh)
{
  if (a.holes () > 0) {
    return do_minkowsky_sum (db::resolve_holes (a), b, rh);
  } else {
    return do_minkowsky_sum (a, b, rh);
  }
}

static db::Polygon 
do_minkowsky_sum (const db::Polygon &a, const db::Polygon &b, bool resolve_holes)
{
  tl_assert (a.begin_hull () != a.end_hull ());

  db::Point p0 = *a.begin_hull ();

  db::EdgeProcessor ep;
  for (db::Polygon::polygon_edge_iterator e = b.begin_edge (); ! e.at_end (); ++e) {
    ep.insert (db::Edge ((*e).p1 () + p0, (*e).p2 () + p0));
    db::ms_production (a, (*e).p1 (), (*e).p2 (), ep);
  }

  return db::ms_extraction (ep, resolve_holes);
}

db::Polygon 
minkowsky_sum (const db::Polygon &a, const db::Polygon &b, bool rh)
{
  if (a.holes () > 0) {
    return do_minkowsky_sum (db::resolve_holes (a), b, rh);
  } else {
    return do_minkowsky_sum (a, b, rh);
  }
}

static db::Polygon 
do_minkowsky_sum (const db::Polygon &a, const db::Box &b, bool resolve_holes)
{
  return minkowsky_sum (a, db::Polygon (b), resolve_holes);
}

db::Polygon 
minkowsky_sum (const db::Polygon &a, const db::Box &b, bool rh)
{
  if (a.holes () > 0) {
    return do_minkowsky_sum (db::resolve_holes (a), b, rh);
  } else {
    return do_minkowsky_sum (a, b, rh);
  }
}

static db::Polygon 
do_minkowsky_sum (const db::Polygon &a, const std::vector<db::Point> &c, bool resolve_holes)
{
  db::EdgeProcessor ep;
  for (size_t i = 1; i < c.size (); ++i) {
    db::ms_production (a, c[i - 1], c[i], ep);
  }

  return db::ms_extraction (ep, resolve_holes);
}

db::Polygon 
minkowsky_sum (const db::Polygon &a, const std::vector<db::Point> &c, bool rh)
{
  if (a.holes () > 0) {
    return do_minkowsky_sum (db::resolve_holes (a), c, rh);
  } else {
    return do_minkowsky_sum (a, c, rh);
  }
}

// -------------------------------------------------------------------------
//  Implementation of hole resolution and polygon to simple polygon conversion

db::Polygon 
resolve_holes (const db::Polygon &p)
{
  db::EdgeProcessor ep;
  ep.insert_sequence (p.begin_edge ());

  std::vector<db::Polygon> polygons;
  db::PolygonContainer pc (polygons);
  db::PolygonGenerator out (pc, true /*resolve holes*/, false /*max coherence to get one polygon*/);

  db::SimpleMerge op;
  ep.process (out, op);

  if (polygons.empty ()) {
    return db::Polygon ();
  } else {
    tl_assert (polygons.size () == 1);
    return polygons [0];
  }
}

db::Polygon 
simple_polygon_to_polygon (const db::SimplePolygon &sp)
{
  db::Polygon p;
  p.assign_hull (sp.begin_hull (), sp.end_hull ());
  return p;
}

db::SimplePolygon 
polygon_to_simple_polygon (const db::Polygon &p)
{
  if (p.holes () > 0) {
    db::Polygon pp = resolve_holes (p);
    db::SimplePolygon sp;
    sp.assign_hull (pp.begin_hull (), pp.end_hull ());
    return sp;
  } else {
    db::SimplePolygon sp;
    sp.assign_hull (p.begin_hull (), p.end_hull ());
    return sp;
  }
}

}

