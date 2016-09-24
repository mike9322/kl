
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


#ifndef HDR_dbPolygonTools
#define HDR_dbPolygonTools

#include "config.h"

#include "dbPolygon.h"

#include <vector>
#include <limits>
#include <algorithm>

namespace db {

/**
 *  @brief An inside test operator
 *
 *  This class allows to efficiently test whether multiple points are inside a given polygon.
 *  Since the test is efficiently implemented when the polygon edges are sorted, the sorting 
 *  and memory allocation step is performed once in the test operator's constructor while 
 *  each individual test is performed efficiently.
 */

template <class P>
class inside_poly_test 
{
public:
  typedef typename P::point_type point_type;
  typedef typename P::coord_type coord_type;
  typedef typename db::edge<coord_type> edge_type;

  /**
   *  @brief Constructor
   */
  inside_poly_test (const P &polygon);

  /**
   *  @brief Actual test
   *
   *  This function returns 1, if the point is inside (not on)
   *  the polygon. It returns 0, if the point is on the polygon and -1
   *  if outside. 
   */
  int operator() (const point_type &pt) const;

private:
  std::vector<edge_type> m_edges;
};

//  Some helper classes and functions for implementing cut_polygon

class KLAYOUT_DLL CutPolygonReceiverBase
{
public:
  virtual ~CutPolygonReceiverBase () { }
  virtual void put (const void *) = 0;
};

template <class OutputIter, class Polygon>
class cut_polygon_receiver
  : public CutPolygonReceiverBase
{
public:
  cut_polygon_receiver (const OutputIter &iter)
    : m_iter (iter)
  { }

  virtual void put (const void *polygon)
  {
    *m_iter++ = *((const Polygon *) polygon);
  }

private:
  OutputIter m_iter;
};

template <class PolygonType, class Edge>
void KLAYOUT_DLL cut_polygon_internal (const PolygonType &input, const Edge &line, CutPolygonReceiverBase *right_of_line);

/**
 *  @brief Polygon cut function
 *
 *  This functions cuts a polygon at the given line (given by an edge)
 *  and produces all parts of the polygon that are "right" of the line given by "line".
 */
template <class PolygonType, class OutputIter>
void cut_polygon (const PolygonType &input, const typename PolygonType::edge_type &line, OutputIter right_of_line)
{
  cut_polygon_receiver<OutputIter, PolygonType> output (right_of_line);
  cut_polygon_internal (input, line, &output);
}

/**
 *  @brief Split a polygon into two or more parts 
 *
 *  This function splits a polygon into parts using some heuristics to determine a "suitable" cut line.
 *  The cut line is choosen through a vertex close to a center (either horizontal or vertical). The splitting
 *  is supposed to create smaller parts with less vertices or a better area ratio of polygon to bounding box area.
 *
 *  @param polygon The input polygon
 *  @param output The parts 
 */
template <class PolygonType>
void KLAYOUT_DLL split_polygon (const PolygonType &polygon, std::vector<PolygonType> &output);

/**
 *  @brief Determines wheter a polygon and a box interact
 *
 *  This function determines wheter the polygon and the box share at least on common point
 *  and returns true in this case.
 */
template<class Polygon, class Box>
bool interact_pb (const Polygon &poly, const Box &box)
{
  if (! poly.box ().touches (box)) {
    return false;
  }

  if (poly.begin_hull () == poly.end_hull ()) {
    return false;
  }

  //  if the box center is inside or at the rim of the polygon, return true
  if (db::inside_poly (poly.begin_edge (), box.center ()) >= 0 ||
      box.contains (*poly.begin_hull ())) {
    return true;
  }

  for (typename Polygon::polygon_edge_iterator e = poly.begin_edge (); ! e.at_end (); ++e) {
    if ((*e).clipped (box).first) {
      return true;
    }
  }

  return false;
}

/**
 *  @brief Determines whether two polygons share at least one common point.
 */
template <class Polygon1, class Polygon2>
bool interact_pp (const Polygon1 &poly1, const Polygon2 &poly2)
{
  typedef typename Polygon1::coord_type coord_type;
  typedef typename Polygon1::polygon_edge_iterator edge_iterator1;
  typedef typename Polygon2::polygon_edge_iterator edge_iterator2;
  typedef db::edge<coord_type> edge_type;

  if (! poly1.box ().touches (poly2.box ())) {
    return false;
  }

  if (poly1.begin_hull () == poly1.end_hull () ||
      poly2.begin_hull () == poly2.end_hull ()) {
    return false;
  }

  //  if at least one point of poly2 is inside or at the rim of poly1, return true
  if (db::inside_poly (poly1.begin_edge (), *poly2.begin_hull ()) >= 0 ||
      db::inside_poly (poly2.begin_edge (), *poly1.begin_hull ()) >= 0) {
    return true;
  }

  //  in all other cases, in intersection happens if at least one of the edges of poly1 or
  //  poly2 intersect. This is checked with a simple scanline algorithm ...

  std::vector <edge_type> edges1;
  edges1.reserve (poly1.vertices ());
  for (edge_iterator1 e = poly1.begin_edge (); ! e.at_end (); ++e) {
    edges1.push_back (*e);
  }

  std::sort (edges1.begin (), edges1.end (), edge_ymin_compare<coord_type> ());

  std::vector <edge_type> edges2;
  edges2.reserve (poly2.vertices ());
  for (edge_iterator2 e = poly2.begin_edge (); ! e.at_end (); ++e) {
    edges2.push_back (*e);
  }

  std::sort (edges2.begin (), edges2.end (), edge_ymin_compare<coord_type> ());

  coord_type y = std::min (std::min (edges1.front ().y1 (), edges1.front ().y2 ()),
                           std::min (edges2.front ().y1 (), edges2.front ().y2 ()));
  
  typename std::vector <edge_type>::iterator ec1 = edges1.begin (); 
  typename std::vector <edge_type>::iterator ef1 = edges1.begin (); 
  typename std::vector <edge_type>::iterator ec2 = edges2.begin (); 
  typename std::vector <edge_type>::iterator ef2 = edges2.begin (); 

  while (ec1 != edges1.end () && ec2 != edges2.end ()) {

    while (ef1 != edges1.end () && edge_ymin (*ef1) <= y) {
      ++ef1;
    }

    while (ef2 != edges2.end () && edge_ymin (*ef2) <= y) {
      ++ef2;
    }

    coord_type yy = std::numeric_limits <coord_type>::max ();

    if (ef1 != edges1.end ()) {
      yy = edge_ymin (*ef1);
    }

    if (ef2 != edges2.end ()) {
      coord_type ynext = edge_ymin (*ef2);
      if (ynext < yy) {
        yy = ynext;
      }
    }

    std::sort (ec1, ef1, edge_xmin_at_yinterval_compare<coord_type> (y, yy));
    std::sort (ec2, ef2, edge_xmin_at_yinterval_compare<coord_type> (y, yy));

    typename std::vector <edge_type>::iterator c1 = ec1;
    typename std::vector <edge_type>::iterator f1 = ec1;
    typename std::vector <edge_type>::iterator c2 = ec2;
    typename std::vector <edge_type>::iterator f2 = ec2;

    coord_type x1 = edge_xmin_at_yinterval (*ec1, y, yy);
    coord_type x2 = edge_xmin_at_yinterval (*ec2, y, yy);
    coord_type x = std::min (x1, x2);

    while (c1 != ef1 && c2 != ef2) {

      while (f1 != ef1 && edge_xmin_at_yinterval (*f1, y, yy) <= x) {
        ++f1;
      }

      while (f2 != ef2 && edge_xmin_at_yinterval (*f2, y, yy) <= x) {
        ++f2;
      }

      coord_type xx = std::numeric_limits <coord_type>::max ();

      if (f1 != ef1) {
        xx = edge_xmin_at_yinterval (*f1, y, yy);
      }

      if (f2 != ef2) {
        coord_type xnext = edge_xmin_at_yinterval (*f2, y, yy);
        if (xnext < xx) {
          xx = xnext;
        }
      }

      for (typename std::vector <edge_type>::iterator a = c1; a != f1; ++a) {
        for (typename std::vector <edge_type>::iterator b = c2; b != f2; ++b) {
          if (a->intersect (*b)) {
            return true;
          }
        }
      }

      x = xx;

      for (typename std::vector <edge_type>::iterator cc = c1; cc != f1; ++cc) {
        if (edge_xmax (*cc) < x || edge_xmax_at_yinterval (*cc, y, yy) < x) {
          if (c1 != cc) {
            std::swap (*cc, *c1);
          }
          ++c1;
        }
      }

      for (typename std::vector <edge_type>::iterator cc = c2; cc != f2; ++cc) {
        if (edge_xmax (*cc) < x || edge_xmax_at_yinterval (*cc, y, yy) < x) {
          if (c2 != cc) {
            std::swap (*cc, *c2);
          }
          ++c2;
        }
      }

    }

    y = yy;

    for (typename std::vector <edge_type>::iterator cc = ec1; cc != ef1; ++cc) {
      if (edge_ymax (*cc) < y) {
        if (ec1 != cc) {
          std::swap (*cc, *ec1);
        }
        ++ec1;
      }
    }

    for (typename std::vector <edge_type>::iterator cc = ec2; cc != ef2; ++cc) {
      if (edge_ymax (*cc) < y) {
        if (ec2 != cc) {
          std::swap (*cc, *ec2);
        }
        ++ec2;
      }
    }

  }

  return false;
}

//  Some specializations that map all combinations to template versions
inline bool interact (const db::Box &box1,              const db::Box &box2)                { return box1.touches (box2); }
inline bool interact (const db::DBox &box1,             const db::DBox &box2)               { return box1.touches (box2); }
inline bool interact (const db::Polygon &poly,          const db::Box &box)                 { return interact_pb (poly, box); }
inline bool interact (const db::SimplePolygon &poly,    const db::Box &box)                 { return interact_pb (poly, box); }
inline bool interact (const db::DPolygon &poly,         const db::DBox &box)                { return interact_pb (poly, box); }
inline bool interact (const db::DSimplePolygon &poly,   const db::DBox &box)                { return interact_pb (poly, box); }
inline bool interact (const db::Polygon &poly1,         const db::Polygon &poly2)           { return interact_pp (poly1, poly2); }
inline bool interact (const db::SimplePolygon &poly1,   const db::Polygon &poly2)           { return interact_pp (poly1, poly2); }
inline bool interact (const db::Polygon &poly1,         const db::SimplePolygon &poly2)     { return interact_pp (poly1, poly2); }
inline bool interact (const db::SimplePolygon &poly1,   const db::SimplePolygon &poly2)     { return interact_pp (poly1, poly2); }
inline bool interact (const db::DPolygon &poly1,        const db::DPolygon &poly2)          { return interact_pp (poly1, poly2); }
inline bool interact (const db::DSimplePolygon &poly1,  const db::DPolygon &poly2)          { return interact_pp (poly1, poly2); }
inline bool interact (const db::DPolygon &poly1,        const db::DSimplePolygon &poly2)    { return interact_pp (poly1, poly2); }
inline bool interact (const db::DSimplePolygon &poly1,  const db::DSimplePolygon &poly2)    { return interact_pp (poly1, poly2); }

/**
 *  @brief Extract a corner radius from a contour
 *
 *  This method will determine the radius of a contour if the contour was formed by rounding another contour.
 *  The corners must be formed by soft bending edges. 
 *  It is possible to retrieve the original contour (or an approximation of the latter) by passing a vector
 *  in "new_pts" which will receive the original contour.
 *
 *  @param from, to The iterators describing the contour
 *  @param rinner The inner corner radius (in dbu units) extracted (if return value is true)
 *  @param router The outer corner radius (in dbu units) extracted (if return value is true)
 *  @param n Receives the number of points per full circle (if return value is true)
 *  @param new_pts If != 0, this vector will receive the contour without the rounded corners (if return value is true)
 *  @param fallback Fallback algorithm (less strict) if true 
 *  @return True, if the extraction was successful
 */
bool KLAYOUT_DLL extract_rad_from_contour (db::Polygon::polygon_contour_iterator from, db::Polygon::polygon_contour_iterator to, double &rinner, double &router, unsigned int &n, std::vector <db::Point> *new_pts = 0, bool fallback = false);

/**
 *  @brief Extract the radius (better: radii) from a polygon and if requested, compute the new polygon without the rounding
 *
 *  See extract_rad_from_contour for details.
 */
bool KLAYOUT_DLL extract_rad (const db::Polygon &polygon, double &rinner, double &router, unsigned int &n, db::Polygon *new_polygon = 0);

/**
 *  @brief Compute the rounded version of a polygon contour
 *
 *  Computes the version of a contour with the corners rounded (inner corners with rinner, outer corners with router, n points per full circle=.
 *  
 *  @param from, to The iterators describing the contour
 *  @param new_pts Receives the new points
 *  @param rinner The inner corner radius (in dbu units)
 *  @param router The outer corner radius (in dbu units)
 *  @param n The number of points per full circle
 */
void KLAYOUT_DLL compute_rounded_contour (db::Polygon::polygon_contour_iterator from, db::Polygon::polygon_contour_iterator to, std::vector <db::Point> &new_pts, double rinner, double router, unsigned int n);

/**
 *  @brief Compute the rounded version of the polygon
 *
 *  See compute_rounded_contour for details.
 */
db::Polygon KLAYOUT_DLL compute_rounded (const db::Polygon &poly, double rinner, double router, unsigned int n);

/**
 *  @brief Smooth a contour 
 *
 *  Removes vertexes from a contour which deviate from the "average" line by more than "d".
 *
 *  @param from The start of the contour
 *  @param to The end of the contour
 *  @param new_pts The points that make up the new contour
 *  @param d The distance that determines the smoothing "roughness"
 */
void KLAYOUT_DLL smooth_contour (db::Polygon::polygon_contour_iterator from, db::Polygon::polygon_contour_iterator to, std::vector <db::Point> &new_pts, db::Coord d);

/**
 *  @brief Smooth a polygon (apply smoothing to the whole polygon)
 */
db::Polygon KLAYOUT_DLL smooth (const db::Polygon &poly, db::Coord d);

/**
 *  @brief A area collector
 *
 *  This class provides a generic 2d map of area values. 
 *  It is used for example by the rasterize function to collect area values 
 *  on a per-pixel basis.
 */
class KLAYOUT_DLL AreaMap
{
public:
  typedef db::coord_traits<db::Coord>::area_type area_type;

  /**
   *  @brief Constructor
   */
  AreaMap ();

  /**
   *  @brief Constructor
   */
  AreaMap (const db::Point &p0, const db::Vector &d, size_t nx, size_t ny);

  /**
   *  @brief Destructor
   */
  ~AreaMap ();

  /**
   *  @brief Reinitialize
   */
  void reinitialize (const db::Point &p0, const db::Vector &d, size_t nx, size_t ny);

  /**
   *  @brief Swap of two maps
   */
  void swap (AreaMap &other);

  /**
   *  @brief Get the area of one pixel
   */
  area_type &get (size_t x, size_t y)
  {
    return mp_av [y * m_nx + x];
  }

  /**
   *  @brief Get the area of one pixel (const version)
   */
  const area_type &get (size_t x, size_t y) const
  {
    return mp_av [y * m_nx + x];
  }

  /**
   *  @brief The number of pixels in x-dimension
   */
  size_t nx () const 
  {
    return m_nx;
  }

  /**
   *  @brief The number of pixels in y-dimension
   */
  size_t ny () const
  {
    return m_ny;
  }

  /**
   *  @brief The origin
   */
  const db::Point &p0 () const
  {
    return m_p0;
  }

  /**
   *  @brief Move the origin
   */
  void move (const db::Vector &d)
  {
    m_p0 += d;
  }

  /**
   *  @brief The per-pixel displacement vector (pixel size)
   */
  const db::Vector &d () const
  {
    return m_d;
  }

  /**
   *  @brief Compute the bounding box of the area map
   */
  db::Box bbox () const
  {
    return db::Box (m_p0, m_p0 + db::Vector (db::Coord (m_nx) * m_d.x (), db::Coord (m_ny) * m_d.y ()));
  }

  /**
   *  @brief Compute the total area
   */
  area_type total_area () const;

  /**
   *  @brief Compute the maximum (single-covered) area per pixel
   */
  area_type pixel_area () const
  {
    return area_type (m_d.x ()) * area_type (m_d.y ());
  }

  /**
   *  @brief Clear the values
   */
  void clear ();

private:
  area_type *mp_av;
  db::Point m_p0;
  db::Vector m_d;
  size_t m_nx, m_ny;

  //  no copying
  AreaMap (const AreaMap &);
  AreaMap &operator= (const AreaMap &);
};

/**
 *  @brief Rasterize the polygon into the given area map
 *
 *  This will decompose the polygon and produce per-pixel area values for the given 
 *  polygon. The area contributions will be added to the given area map.
 */
void KLAYOUT_DLL rasterize (const db::Polygon &polygon, db::AreaMap &am);

/**
 *  @brief Minkowsky sum of an edge and a polygon
 */
db::Polygon KLAYOUT_DLL minkowsky_sum (const db::Polygon &a, const db::Edge &b, bool resolve_holes = false);

/**
 *  @brief Minkowsky sum of a polygon and a polygon
 */
db::Polygon KLAYOUT_DLL minkowsky_sum (const db::Polygon &a, const db::Polygon &b, bool resolve_holes = false);

/**
 *  @brief Minkowsky sum of a polygon and a box
 */
db::Polygon KLAYOUT_DLL minkowsky_sum (const db::Polygon &a, const db::Box &b, bool resolve_holes = false);

/**
 *  @brief Minkowsky sum of a polygon and a contour
 */
db::Polygon KLAYOUT_DLL minkowsky_sum (const db::Polygon &a, const std::vector<db::Point> &c, bool resolve_holes = false);

/**
 *  @brief Resolve holes 
 */
db::Polygon KLAYOUT_DLL resolve_holes (const db::Polygon &p);

/**
 *  @brief SimplePolygon to Polygon conversion
 */
db::Polygon KLAYOUT_DLL simple_polygon_to_polygon (const db::SimplePolygon &a);

/**
 *  @brief Polygon to SimplePolygon conversion (resolves holes)
 */
db::SimplePolygon KLAYOUT_DLL polygon_to_simple_polygon (const db::Polygon &a);

}

#endif

