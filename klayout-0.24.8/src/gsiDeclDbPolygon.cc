
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


#include "gsiDecl.h"
#include "dbPoint.h"
#include "dbPolygon.h"
#include "dbPolygonTools.h"

namespace gsi
{

// ---------------------------------------------------------------
//  simple polygon binding

template <class C>
struct simple_polygon_defs
{
  typedef typename C::coord_type coord_type;
  typedef typename C::box_type box_type;
  typedef typename C::point_type point_type;
  typedef typename C::distance_type distance_type;
  typedef typename C::area_type area_type;
  typedef db::simple_trans<coord_type> simple_trans_type;
  typedef db::complex_trans<coord_type, double> complex_trans_type;
  typedef db::complex_trans<coord_type, coord_type> icomplex_trans_type;

  static void set_points1 (C *c, const std::vector<point_type> &pts)
  {
    c->assign_hull (pts.begin (), pts.end (), false);
  }

  static void set_points (C *c, const std::vector<point_type> &pts, bool raw)
  {
    if (raw) {
      c->assign_hull (pts.begin (), pts.end (), false);
    } else {
      c->assign_hull (pts.begin (), pts.end ());
    }
  }

  static point_type point (C *c, size_t p)
  {
    if (c->hull ().size () > p) {
      return c->hull ()[p];
    } else {
      return point_type ();
    }
  }

  static size_t num_points (C *c)
  {
    return c->hull ().size ();
  }

  static C *from_string (const char *s)
  {
    tl::Extractor ex (s);
    std::auto_ptr<C> c (new C ());
    ex.read (*c.get ());
    return c.release ();
  }

  static C *new_v ()
  {
    return new C;
  }

  static C *new_p (const std::vector<point_type> &pts, bool raw)
  {
    C *c = new C;
    if (! raw) {
      c->assign_hull (pts.begin (), pts.end ());
    } else {
      c->assign_hull (pts.begin (), pts.end (), false);
    }
    return c;
  }

  static C *new_b (const box_type &box)
  {
    return new C (box);
  }

  static C *ellipse (const box_type &box, int npoints)
  {
    npoints = std::max (3, std::min (10000000, npoints));

    std::vector<point_type> pts;
    pts.reserve (npoints);

    double da = M_PI * 2.0 / npoints;
    for (int i = 0; i < npoints; ++i) {
      double x = box.center ().x () - box.width () * 0.5 * cos (da * i);
      double y = box.center ().y () + box.height () * 0.5 * sin (da * i);
      pts.push_back (point_type::from_double (db::DPoint (x, y)));
    }

    C *c = new C;
    c->assign_hull (pts.begin (), pts.end (), false);
    return c;
  }

  static bool inside (const C *poly, point_type pt)
  {
    return db::inside_poly (poly->begin_edge (), pt) >= 0;
  }

  static void compress (C *poly, bool remove_reflected)
  {
    poly->compress (remove_reflected);
  }

  static C &move_xy (C *poly, coord_type dx, coord_type dy)
  {
    return poly->move (point_type (dx, dy));
  }

  static C moved_xy (const C *poly, coord_type dx, coord_type dy)
  {
    return poly->moved (point_type (dx, dy));
  }

  static C scale (const C *p, double s)
  {
    return C (p->transformed (icomplex_trans_type (s), false /*don't compress*/));
  }

  static C *transform (C *poly, const simple_trans_type &t)
  {
    poly->transform (t, false /*don't compress*/);
    return poly;
  }

  static C transformed (const C *poly, const simple_trans_type &t)
  {
    return poly->transformed (t, false /*don't compress*/);
  }

  static db::simple_polygon<double> transformed_cplx (const C *poly, const complex_trans_type &t)
  {
    return poly->transformed (t, false /*don't compress*/);
  }

#if defined(HAVE_64BIT_COORD)
  //  workaround for missing 128bit binding of GSI
  static double area (const C *poly)
#else
  static area_type area (const C *poly)
#endif
  { 
    return poly->area ();
  }

  static gsi::Methods methods ()
  {
    return
    constructor ("new", &new_v, 
      "@brief Default constructor: creates an empty (invalid) polygon"
    ) +
    constructor ("new|#new_p", &new_p, gsi::arg ("pts"), gsi::arg ("raw", false),
      "@brief Constructor given the points of the simple polygon\n"
      "\n"
      "@param pts The points forming the simple polygon\n"
      "@param raw If true, the points are taken as they are (see below)\n"
      "\n"
      "If the 'raw' argument is set to true, the points are taken as they are. "
      "Specifically no removal of redundant points or joining of coincident edges will take place. "
      "In effect, polygons consisting of a single point or two points can be constructed as "
      "well as polygons with duplicate points. "
      "Note that such polygons may cause problems in some applications.\n"
      "\n"
      "Regardless of raw mode, the point list will be adjusted such that the first point "
      "is the lowest-leftmost one and the orientation is clockwise always.\n"
      "\n"
      "The 'raw' argument has been added in version 0.24.\n"
    ) +
    constructor ("new|#new_b", &new_b, 
      "@brief Constructor converting a box to a polygon\n"
      "\n"
      "@args box\n"
      "\n"
      "@param box The box to convert to a polygon\n"
    ) +
    constructor ("ellipse", &ellipse, 
      "@brief Creates a simple polygon appoximating an ellipse\n"
      "\n"
      "@args box, n\n"
      "\n"
      "@param box The bounding box of the ellipse\n"
      "@param n The number of points that will be used to approximate the ellipse\n"
      "\n"
      "This method has been introduced in version 0.23.\n"
    ) +
    method ("==", &C::operator==,
      "@brief Equality test\n"
      "@args p\n"
      "@param p The object to compare against\n"
    ) +
    method ("!=", &C::operator!=,
      "@brief Inequality test\n"
      "@args p\n"
      "@param p The object to compare against\n"
    ) +
    method_ext ("points=", &set_points1, 
      "@brief Set the points of the simple polygon\n"
      "\n"
      "@args pts\n"
      "@param pts An array of points to assign to the simple polygon\n"
      "\n"
      "See the constructor description for details about raw mode.\n"
    ) +
    method_ext ("set_points", &set_points, gsi::arg ("pts"), gsi::arg ("raw", false),
      "@brief Set the points of the simple polygon\n"
      "\n"
      "@param pts An array of points to assign to the simple polygon\n"
      "@param raw If true, the points are taken as they are\n"
      "\n"
      "See the constructor description for details about raw mode.\n"
      "\n"
      "This method has been added in version 0.24.\n"
    ) +
    method_ext ("point", &point,
      "@brief Get a specific point of the contour"
      "@args p\n"
      "@param p The index of the point to get\n"
      "If the index of the point is not a valid index, a default value is returned.\n"
      "This method was introduced in version 0.18.\n"
    ) +
    method_ext ("num_points|#points", &num_points,
      "@brief Get the number of points"
    ) +
    iterator ("each_point", &C::begin_hull, &C::end_hull, 
      "@brief Iterate over the points that make up the simple polygon"
    ) +
    iterator ("each_edge", &C::begin_edge, 
      "@brief Iterate over the edges that make up the simple polygon"
    ) +
    method_ext ("inside?", &inside,
      "@brief Test, if the given point is inside the polygon\n"
      "@args p\n"
      "If the given point is inside or on the edge the polygon, true is returned. "
      "This tests works well only if the polygon is not self-overlapping and oriented clockwise. "
    ) +
    method_ext ("compress", &compress,
      "@brief Compress the simple polygon.\n"
      "@args remove_reflected\n"
      "\n"
      "This method removes redundant points from the polygon, such as points being on a line formed by two other points.\n"
      "If remove_reflected is true, points are also removed if the two adjacent edges form a spike.\n"
      "\n"
      "@param remove_reflected See description of the functionality.\n"
      "\n"
      "This method was introduced in version 0.18.\n"
    ) +
    method ("is_box?", &C::is_box,
      "@brief Returns true, if the polygon is a simple box.\n"
      "\n"
      "A polygon is a box if it is identical to it's bounding box.\n"
      "\n"
      "@return True if the polygon is a box.\n"
      "\n"
      "This method was introduced in version 0.23.\n"
    ) +
    method_ext ("*", &scale,
      "@brief Scaling by some factor\n"
      "\n"
      "@args f\n"
      "\n"
      "Returns the scaled object. All coordinates are multiplied with the given factor and if "
      "necessary rounded."
    ) +
    method ("move", &C::move,
      "@brief Moves the simple polygon.\n"
      "@args p\n"
      "\n"
      "Moves the simple polygon by the given offset and returns the \n"
      "moved simple polygon. The polygon is overwritten.\n"
      "\n"
      "@param p The distance to move the simple polygon.\n"
      "\n"
      "@return The moved simple polygon.\n"
    ) +
    method_ext ("move", &move_xy,
      "@brief Moves the polygon.\n"
      "@args x,y\n"
      "\n"
      "Moves the polygon by the given offset and returns the \n"
      "moved polygon. The polygon is overwritten.\n"
      "\n"
      "@param x The x distance to move the polygon.\n"
      "@param y The y distance to move the polygon.\n"
      "\n"
      "@return The moved polygon (self).\n"
    ) +
    method ("moved", &C::moved,
      "@brief Returns the moved simple polygon\n"
      "@args p\n"
      "\n"
      "Moves the simple polygon by the given offset and returns the \n"
      "moved simple polygon. The polygon is not modified.\n"
      "\n"
      "@param p The distance to move the simple polygon.\n"
      "\n"
      "@return The moved simple polygon.\n"
    ) +
    method_ext ("moved", &moved_xy,
      "@brief Returns the moved polygon (does not modify self)\n"
      "@args x,y\n"
      "\n"
      "Moves the polygon by the given offset and returns the \n"
      "moved polygon. The polygon is not modified.\n"
      "\n"
      "@param x The x distance to move the polygon.\n"
      "@param y The y distance to move the polygon.\n"
      "\n"
      "@return The moved polygon.\n"
      "\n"
      "This method has been introduced in version 0.23.\n"
    ) +
    method_ext ("transform", &transform,
      "@brief Transforms the simple polygon (in-place)\n"
      "@args t\n"
      "\n"
      "Transforms the simple polygon with the given transformation.\n"
      "Modifies self and returns self. An out-of-place version which does not modify self is \\transformed.\n"
      "\n"
      "@param t The transformation to apply.\n"
      "\n"
      "This method has been introduced in version 0.24.\n"
    ) +
    method_ext ("transformed", &transformed,
      "@brief Transforms the simple polygon.\n"
      "@args t\n"
      "\n"
      "Transforms the simple polygon with the given transformation.\n"
      "Does not modify the simple polygon but returns the transformed polygon.\n"
      "\n"
      "@param t The transformation to apply.\n"
      "\n"
      "@return The transformed simple polygon.\n"
    ) +
    method_ext ("transformed|#transformed_cplx", &transformed_cplx,
      "@brief Transforms the simple polygon.\n"
      "@args t\n"
      "\n"
      "Transforms the simple polygon with the given complex transformation.\n"
      "Does not modify the simple polygon but returns the transformed polygon.\n"
      "\n"
      "@param t The transformation to apply.\n"
      "\n"
      "@return The transformed simple polygon.\n"
    ) +
    constructor ("from_s", &from_string,
      "@brief Creates an object from a string\n"
      "@args s\n"
      "Creates the object from a string representation (as returned by \\to_s)\n"
      "\n"
      "This method has been added in version 0.23.\n"
    ) +
    method ("to_s", (std::string (C::*) () const) &C::to_string,
      "@brief Convert to a string\n"
    ) +
    method_ext ("area", &area,
      "@brief The area of the polygon\n"
      "The area is correct only if the polygon is not self-overlapping and the polygon is oriented clockwise."
    ) +
    method ("perimeter", &C::perimeter,
      "@brief The perimeter of the polygon\n"
      "The perimeter is sum of the lengths of all edges making up the polygon."
    ) +
    method ("bbox", &C::box,
      "@brief Return the bounding box of the simple polygon"
    );
  }
};

static db::Polygon sp_round_corners (const db::SimplePolygon *sp, double rinner, double router, unsigned int n)
{
  db::Polygon p;
  p.assign_hull (sp->begin_hull (), sp->end_hull (), false);
  return db::compute_rounded (p, rinner, router, n);
}

static db::Polygon sp_minkowsky_sum_pe (const db::SimplePolygon *sp, const db::Edge &e, bool rh)
{
  db::Polygon p;
  p.assign_hull (sp->begin_hull (), sp->end_hull (), false);
  return db::minkowsky_sum (p, e, rh);
}

static db::Polygon sp_minkowsky_sum_pp (const db::SimplePolygon *sp, const db::SimplePolygon &spp, bool rh)
{
  db::Polygon p;
  p.assign_hull (sp->begin_hull (), sp->end_hull (), false);
  db::Polygon pp;
  pp.assign_hull (spp.begin_hull (), spp.end_hull (), false);
  return db::minkowsky_sum (p, pp, rh);
}

static db::Polygon sp_minkowsky_sum_pb (const db::SimplePolygon *sp, const db::Box &b, bool rh)
{
  db::Polygon p;
  p.assign_hull (sp->begin_hull (), sp->end_hull (), false);
  return db::minkowsky_sum (p, b, rh);
}

static db::Polygon sp_minkowsky_sum_pc (const db::SimplePolygon *sp, const std::vector<db::Point> &c, bool rh)
{
  db::Polygon p;
  p.assign_hull (sp->begin_hull (), sp->end_hull (), false);
  return db::minkowsky_sum (p, c, rh);
}

static db::SimplePolygon sp_from_dsp (const db::DSimplePolygon &d)
{
  return db::SimplePolygon (db::SimplePolygon::from_double (d, false));
}

static db::DSimplePolygon dsp_from_sp (const db::SimplePolygon &d)
{
  return db::DSimplePolygon (d, db::CplxTrans ());
}

static db::DSimplePolygon *transform_cplx_sp (db::DSimplePolygon *p, const db::DCplxTrans &t)
{
  p->transform (t, false /*no compression*/);
  return p;
}

static db::SimplePolygon *transform_icplx_sp (db::SimplePolygon *p, const db::ICplxTrans &t)
{
  p->transform (t, false /*no compression*/);
  return p;
}

static db::SimplePolygon transformed_icplx_sp (const db::SimplePolygon *p, const db::ICplxTrans &t)
{
  return p->transformed (t, false /*no compression*/);
}

Class<db::SimplePolygon> decl_SimplePolygon ("SimplePolygon", 
  simple_polygon_defs<db::SimplePolygon>::methods () +
  method ("from_dpoly", &sp_from_dsp, 
    "@brief Construct an integer-coordinate polygon from a floating-point coordinate one"
    "\n"
    "@args double_poly\n"
    "\n"
    "This method has been added in version 0.15."
  ) +
  method_ext ("round_corners", &sp_round_corners,
    "@brief Round the corners of the polygon\n"
    "@args rinner, router, n\n"
    "\n"
    "Replaces the corners of the polygon with circle segments.\n"
    "\n"
    "@param rinner The circle radius of inner corners (in database units).\n"
    "@param router The circle radius of outer corners (in database units).\n"
    "@param n The number of points per full circle.\n"
    "\n"
    "@return The new polygon.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("minkowsky_sum", &sp_minkowsky_sum_pe,
    "@brief Compute the Minkowsky sum of a polygon and an edge\n"
    "@args a, b, resolve_holes\n"
    "\n"
    "@param a The first argument.\n"
    "@param b The second argument.\n"
    "@param resolve_holes If true, the output polygon will not contain holes, but holes are resolved by joining the holes with the hull.\n"
    "\n"
    "@return The new polygon representing the Minkowsky sum of a and b.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("minkowsky_sum", &sp_minkowsky_sum_pp,
    "@brief Compute the Minkowsky sum of a polygon and a polygon\n"
    "@args a, b, resolve_holes\n"
    "\n"
    "@param a The first argument.\n"
    "@param b The second argument.\n"
    "@param resolve_holes If true, the output polygon will not contain holes, but holes are resolved by joining the holes with the hull.\n"
    "\n"
    "@return The new polygon representing the Minkowsky sum of a and b.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("minkowsky_sum", &sp_minkowsky_sum_pb,
    "@brief Compute the Minkowsky sum of a polygon and a box\n"
    "@args a, b, resolve_holes\n"
    "\n"
    "@param a The first argument.\n"
    "@param b The second argument.\n"
    "@param resolve_holes If true, the output polygon will not contain holes, but holes are resolved by joining the holes with the hull.\n"
    "\n"
    "@return The new polygon representing the Minkowsky sum of a and b.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("minkowsky_sum", &sp_minkowsky_sum_pc,
    "@brief Compute the Minkowsky sum of a polygon and a contour of points (a trace)\n"
    "@args a, b, resolve_holes\n"
    "\n"
    "@param a The first argument.\n"
    "@param b The second argument (a series of points forming the trace).\n"
    "@param resolve_holes If true, the output polygon will not contain holes, but holes are resolved by joining the holes with the hull.\n"
    "\n"
    "@return The new polygon representing the Minkowsky sum of a and b.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("transform|#transform_cplx", &transform_icplx_sp,
    "@brief Transforms the simple polygon with a complex transformation (in-place)\n"
    "@args t\n"
    "\n"
    "Transforms the simple polygon with the given complex transformation.\n"
    "Modifies self and returns self. An out-of-place version which does not modify self is \\transformed.\n"
    "\n"
    "@param t The transformation to apply.\n"
    "\n"
    "This method has been introduced in version 0.24.\n"
  ) +
  method_ext ("transformed|#transformed_cplx", &transformed_icplx_sp,
    "@brief Transform the simple polygon.\n"
    "@args t\n"
    "\n"
    "Transforms the simple polygon with the given complex transformation.\n"
    "Does not modify the simple polygon but returns the transformed polygon.\n"
    "\n"
    "@param t The transformation to apply.\n"
    "\n"
    "@return The transformed simple polygon (in this case an integer coordinate object).\n"
    "\n"
    "This method has been introduced in version 0.18.\n"
  ),
  "@brief A simple polygon class\n"
  "\n"
  "A simple polygon consists of an outer hull only. To support polygons with holes, use \\Polygon.\n"
  "The hull contour consists of several points. The point\n"
  "list is normalized such that the leftmost, lowest point is \n"
  "the first one. The orientation is normalized such that\n"
  "the orientation of the hull contour is clockwise.\n"
  "\n"
  "It is in no way checked that the contours are not overlapping\n"
  "This must be ensured by the user of the object\n"
  "when filling the contours.\n"
  "\n"
  "The \\SimplePolygon class stores coordinates in integer format. "
  "A class that stores floating-point coordinates is \\DSimplePolygon.\n"
  "\n"
  "See @<a href=\"/programming/database_api.xml\">The Database API@</a> for more details about the "
  "database objects."
);

Class<db::DSimplePolygon> decl_DSimplePolygon ("DSimplePolygon", 
  simple_polygon_defs<db::DSimplePolygon>::methods () +
  method ("from_ipoly", &dsp_from_sp, 
    "@brief Construct a floating-point coordinate polygon from an integer coordinate one"
    "\n"
    "@args int_poly\n"
    "\n"
    "This method has been added in version 0.15."
  ) +
  method_ext ("transform|#transform_cplx", &transform_cplx_sp,
    "@brief Transforms the simple polygon with a complex transformation (in-place)\n"
    "@args t\n"
    "\n"
    "Transforms the simple polygon with the given complex transformation.\n"
    "Modifies self and returns self. An out-of-place version which does not modify self is \\transformed.\n"
    "\n"
    "@param t The transformation to apply.\n"
    "\n"
    "This method has been introduced in version 0.24.\n"
  ),
  "@brief A simple polygon class\n"
  "\n"
  "A simple polygon consists of an outer hull only. To support polygons with holes, use \\DPolygon.\n"
  "The contour consists of several points. The point\n"
  "list is normalized such that the leftmost, lowest point is \n"
  "the first one. The orientation is normalized such that\n"
  "the orientation of the hull contour is clockwise.\n"
  "\n"
  "It is in no way checked that the contours are not over-\n"
  "lapping. This must be ensured by the user of the object\n"
  "when filling the contours.\n"
  "\n"
  "The \\DSimplePolygon class stores coordinates in floating-point format which gives a higher precision "
  "for some operations. A class that stores integer coordinates is \\SimplePolygon.\n"
  "\n"
  "See @<a href=\"/programming/database_api.xml\">The Database API@</a> for more details about the "
  "database objects."
);

// ---------------------------------------------------------------
//  polygon binding

template <class C>
struct polygon_defs
{
  typedef typename C::coord_type coord_type;
  typedef typename C::box_type box_type;
  typedef typename C::point_type point_type;
  typedef typename C::distance_type distance_type;
  typedef typename C::area_type area_type;
  typedef db::simple_trans<coord_type> simple_trans_type;
  typedef db::complex_trans<coord_type, double> complex_trans_type;
  typedef db::complex_trans<coord_type, coord_type> icomplex_trans_type;

  static C *p_from_sp (const db::simple_polygon<coord_type> &sp)
  {
    C *p = new C ();
    p->assign_hull (sp.begin_hull (), sp.end_hull (), false);
    return p;
  }

  static C *ellipse (const box_type &box, int npoints)
  {
    npoints = std::max (3, std::min (10000000, npoints));

    std::vector<point_type> pts;
    pts.reserve (npoints);

    double da = M_PI * 2.0 / npoints;
    for (int i = 0; i < npoints; ++i) {
      double x = box.center ().x () - box.width () * 0.5 * cos (da * i);
      double y = box.center ().y () + box.height () * 0.5 * sin (da * i);
      pts.push_back (point_type::from_double (db::DPoint (x, y)));
    }

    C *c = new C;
    c->assign_hull (pts.begin (), pts.end (), false);
    return c;
  }

  static void set_hull1 (C *c, const std::vector<point_type> &pts)
  {
    c->assign_hull (pts.begin (), pts.end (), false);
  }

  static void set_hull (C *c, const std::vector<point_type> &pts, bool raw)
  {
    if (raw) {
      c->assign_hull (pts.begin (), pts.end (), false);
    } else {
      c->assign_hull (pts.begin (), pts.end ());
    }
  }

  static void set_hole_box (C *c, unsigned int n, const box_type &box)
  {
    if (c->holes () > n) {
      point_type pts[4] = {
        point_type (box.left (), box.bottom ()),
        point_type (box.left (), box.top ()),
        point_type (box.right (), box.top ()),
        point_type (box.right (), box.bottom ())
      };
      c->assign_hole (n, &pts[0], &pts[0] + sizeof (pts) / sizeof (pts[0]));
    }
  }

  static void set_hole (C *c, unsigned int n, const std::vector<point_type> &pts, bool raw)
  {
    if (c->holes () > n) {
      if (raw) {
        c->assign_hole (n, pts.begin (), pts.end (), false);
      } else {
        c->assign_hole (n, pts.begin (), pts.end ());
      }
    }
  }

  static size_t num_points (C *c)
  {
    return c->vertices ();
  }

  static point_type point_hull (C *c, size_t p)
  {
    if (c->hull ().size () > p) {
      return c->hull ()[p];
    } else {
      return point_type ();
    }
  }

  static point_type point_hole (C *c, unsigned int n, size_t p)
  {
    if (c->holes () > n && c->contour (n + 1).size () > p) {
      return c->contour (n + 1)[p];
    } else {
      return point_type ();
    }
  }

  static size_t num_points_hull (C *c)
  {
    return c->hull ().size ();
  }

  static size_t num_points_hole (C *c, unsigned int n)
  {
    return c->contour (n + 1).size ();
  }

  static void insert_hole (C *c, const std::vector<point_type> &pts, bool raw)
  {
    if (raw) {
      return c->insert_hole (pts.begin (), pts.end (), false);
    } else {
      return c->insert_hole (pts.begin (), pts.end ());
    }
  }

  static void insert_hole_box (C *c, const box_type &box)
  {
    point_type pts[4] = {
      point_type (box.left (), box.bottom ()),
      point_type (box.left (), box.top ()),
      point_type (box.right (), box.top ()),
      point_type (box.right (), box.bottom ())
    };
    return c->insert_hole (&pts[0], &pts[0] + sizeof (pts) / sizeof (pts[0]));
  }

  static C *from_string (const char *s)
  {
    tl::Extractor ex (s);
    std::auto_ptr<C> c (new C ());
    ex.read (*c.get ());
    return c.release ();
  }

  static C *new_v ()
  {
    return new C;
  }

  static C *new_p (const std::vector<point_type> &pts, bool raw)
  {
    C *c = new C;
    if (raw) {
      c->assign_hull (pts.begin (), pts.end (), false);
    } else {
      c->assign_hull (pts.begin (), pts.end ());
    }
    return c;
  }

  static C *new_b (const box_type &box)
  {
    return new C (box);
  }

  static void size_xy (C *poly, coord_type dx, coord_type dy, unsigned int mode)
  {
    poly->size (dx, dy, mode);
  }

  static void size_dm (C *poly, coord_type d, unsigned int mode)
  {
    poly->size (d, d, mode);
  }

  static void size_d (C *poly, coord_type d)
  {
    poly->size (d, d, 2);
  }

  static C sized_xy (const C *poly, coord_type dx, coord_type dy, unsigned int mode)
  {
    return poly->sized (dx, dy, mode);
  }

  static C sized_dm (const C *poly, coord_type d, unsigned int mode)
  {
    return poly->sized (d, d, mode);
  }

  static C sized_d (const C *poly, coord_type d)
  {
    return poly->sized (d, d, 2);
  }

  static bool inside (const C *poly, point_type pt)
  {
    return db::inside_poly (poly->begin_edge (), pt) >= 0;
  }

  static C &move_xy (C *poly, coord_type dx, coord_type dy)
  {
    return poly->move (point_type (dx, dy));
  }

  static C moved_xy (const C *poly, coord_type dx, coord_type dy)
  {
    return poly->moved (point_type (dx, dy));
  }

  static C scale (const C *p, double s)
  {
    return C (p->transformed (icomplex_trans_type (s), false /*no compression*/));
  }

  static void compress (C *poly, bool remove_reflected)
  {
    poly->compress (remove_reflected);
  }

  static C *transform (C *poly, const simple_trans_type &t)
  {
    poly->transform (t, false /*no compression*/);
    return poly;
  }

  static C transformed (const C *poly, const simple_trans_type &t)
  {
    return poly->transformed (t, false /*no compression*/);
  }

  static db::polygon<double> transformed_cplx (const C *poly, const complex_trans_type &t)
  {
    return poly->transformed (t, false /*no compression*/);
  }

#if defined(HAVE_64BIT_COORD)
  //  workaround for missing 128bit binding of GSI
  static double area (const C *poly)
#else
  static area_type area (const C *poly)
#endif
  { 
    return poly->area ();
  }

  static gsi::Methods methods ()
  {
    return
    constructor ("new", &new_v, 
      "@brief Default constructor: creates an empty (invalid) polygon"
    ) +
    constructor ("new", &p_from_sp, 
      "@brief Constructor from a simple polygon\n"
      "@args sp\n"
      "@param sp The simple polygon that is converted into the polygon\n"
      "This method was introduced in version 0.22.\n"
    ) +
    constructor ("new|#new_p", &new_p, gsi::arg ("pts"), gsi::arg ("raw", false),
      "@brief Constructor given the points of the polygon hull\n"
      "\n"
      "@param pts The points forming the polygon hull\n"
      "@param raw If true, the point list won't be modified (see \\assign_hull)\n"
      "\n"
      "The 'raw' argument was added in version 0.24.\n"
    ) +
    constructor ("new|#new_b", &new_b, 
      "@brief Constructor converting a box to a polygon\n"
      "\n"
      "@args box\n"
      "\n"
      "@param box The box to convert to a polygon\n"
    ) +
    constructor ("ellipse", &ellipse, 
      "@brief Creates a simple polygon appoximating an ellipse\n"
      "\n"
      "@args box, n\n"
      "\n"
      "@param box The bounding box of the ellipse\n"
      "@param n The number of points that will be used to approximate the ellipse\n"
      "\n"
      "This method has been introduced in version 0.23.\n"
    ) +
    method ("<", &C::operator<,
      "@brief Less operator\n"
      "@args p\n"
      "@param p The object to compare against\n"
      "This operator is provided to establish some, not necessarily a certain sorting order\n"
    ) +
    method ("==", &C::operator==,
      "@brief Equality test\n"
      "@args p\n"
      "@param p The object to compare against\n"
    ) +
    method ("!=", &C::operator!=,
      "@brief Inequality test\n"
      "@args p\n"
      "@param p The object to compare against\n"
    ) +
    method_ext ("hull=", &set_hull1,
      "@brief Set the points of the hull of polygon\n"
      "@args p\n"
      "@param p An array of points to assign to the polygon's hull"
      "\n"
      "The 'assign_hull' variant is provided in analogy to 'assign_hole'.\n"
    ) +
    method_ext ("assign_hull", &set_hull, gsi::arg ("p"), gsi::arg ("raw", false),
      "@brief Set the points of the hull of polygon\n"
      "@args p\n"
      "@param p An array of points to assign to the polygon's hull\n"
      "@param raw If true, the points won't be compressed\n"
      "\n"
      "If the 'raw' argument is set to true, the points are taken as they are. "
      "Specifically no removal of redundant points or joining of coincident edges will take place. "
      "In effect, polygons consisting of a single point or two points can be constructed as "
      "well as polygons with duplicate points. "
      "Note that such polygons may cause problems in some applications.\n"
      "\n"
      "Regardless of raw mode, the point list will be adjusted such that the first point "
      "is the lowest-leftmost one and the orientation is clockwise always.\n"
      "\n"
      "The 'assign_hull' variant is provided in analogy to 'assign_hole'.\n"
      "\n"
      "The 'raw' argument was added in version 0.24.\n"
    ) +
    method_ext ("assign_hole", &set_hole, gsi::arg ("n"), gsi::arg ("p"), gsi::arg ("raw", false),
      "@brief Set the points of the given hole of the polygon\n"
      "@param n The index of the hole to which the points should be assigned\n"
      "@param p An array of points to assign to the polygon's hole\n"
      "@param raw If true, the points won't be compressed (see \\assign_hull)\n"
      "If the hole index is not valid, this method does nothing.\n"
      "\n"
      "This method was introduced in version 0.18.\n"
      "The 'raw' argument was added in version 0.24.\n"
    ) +
    method_ext ("assign_hole", &set_hole_box,
      "@brief Set the box as the given hole of the polygon\n"
      "@args n,b\n"
      "@param n The index of the hole to which the points should be assigned\n"
      "@param b The box to assign to the polygon's hole\n"
      "If the hole index is not valid, this method does nothing.\n"
      "This method was introduced in version 0.23.\n"
    ) +
    method_ext ("num_points|#points", &num_points,
      "@brief Get the total number of points (hull plus holes)\n"
      "This method was introduced in version 0.18.\n"
    ) +
    method_ext ("point_hull", &point_hull,
      "@brief Get a specific point of the hull\n"
      "@args p\n"
      "@param p The index of the point to get\n"
      "If the index of the point is not a valid index, a default value is returned.\n"
      "This method was introduced in version 0.18.\n"
    ) +
    method_ext ("point_hole", &point_hole,
      "@brief Get a specific point of a hole\n"
      "@args n,p\n"
      "@param n The index of the hole to which the points should be assigned\n"
      "@param p The index of the point to get\n"
      "If the index of the point or of the hole is not valid, a default value is returned.\n"
      "This method was introduced in version 0.18.\n"
    ) +
    method_ext ("num_points_hull|#points_hull", &num_points_hull,
      "@brief Get the number of points of the hull\n"
    ) +
    method_ext ("num_points_hole|#points_hole", &num_points_hole,
      "@brief Get the number of points of the given hole\n"
      "@args n\n"
      "The argument gives the index of the hole of which the number of points "
      "are requested. The index must be less than the number of holes (see \\holes). "
    ) +
    method_ext ("insert_hole", &insert_hole, gsi::arg ("p"), gsi::arg ("raw", false),
      "@brief Insert a hole with the given points\n"
      "@param p An array of points to insert as a new hole\n"
      "@param raw If true, the points won't be compressed (see \\assign_hull)\n"
      "\n"
      "The 'raw' argument was added in version 0.24.\n"
    ) +
    method_ext ("insert_hole", &insert_hole_box,
      "@brief Insert a hole from the given box\n"
      "@args b\n"
      "@param b The box to insert as a new hole\n"
      "This method was introduced in version 0.23.\n"
    ) +
    iterator ("each_point_hull", &C::begin_hull, &C::end_hull, 
      "@brief Iterate over the points that make up the hull"
    ) +
    iterator ("each_point_hole", &C::begin_hole, &C::end_hole, 
      "@brief Iterate over the points that make up the nth hole\n"
      "@args n\n"
      "The hole number must be less than the number of holes (see \\holes)"
    ) +
    method_ext ("size", &size_xy,
      "@brief Sizing (biasing)\n"
      "@args dx, dy, mode\n"
      "\n"
      "Shifts the contour outwards (dx,dy>0) or inwards (dx,dy<0).\n"
      "dx is the sizing in x-direction and dy is the sizing in y-direction. The sign of dx and dy should be identical.\n"
      "The sizing operation create invalid (self-overlapping, reverse oriented) contours. \n"
      "\n"
      "The mode defines at which bending angle cutoff occurs \n"
      "(0:>0, 1:>45, 2:>90, 3:>135, 4:>approx. 168, other:>approx. 179)\n"
      "\n"
      "In order to obtain a proper polygon in the general case, the\n"
      "sized polygon must be merged in 'greater than zero' wrap count mode. This is necessary since in the general case,\n"
      "sizing can be complicated operation which lets a single polygon fall apart into disjoint pieces for example.\n"
      "This can be achieved using the \\EdgeProcessor class for example:\n"
      "\n"
      "@code\n"
      "poly = ... # a RBA::Polygon\n"
      "poly.size(-50, 2)\n"
      "ep = RBA::EdgeProcessor::new\n"
      "# result is an array of RBA::Polygon objects\n"
      "result = ep.simple_merge_p2p([ poly ], false, false, 1)\n"
      "@/code\n"
    ) +
    method_ext ("size", &size_dm,
      "@brief Sizing (biasing)\n"
      "@args d, mode\n"
      "\n"
      "Shifts the contour outwards (d>0) or inwards (d<0).\n"
      "This method is equivalent to\n"
      "@code\n"
      "size(d, d, mode)\n"
      "@/code\n"
      "\n"
      "See \\size for a detailed description.\n"
      "\n"
      "This method has been introduced in version 0.23.\n"
    ) +
    method_ext ("sized", &sized_xy,
      "@brief Sizing (biasing) without modifying self\n"
      "@args dx, dy, mode\n"
      "\n"
      "This method applies sizing to the polygon but does not modify self. Instead a sized copy "
      "is returned.\n"
      "See \\size for a description of the operation.\n"
      "\n"
      "This method has been introduced in version 0.23.\n"
    ) +
    method_ext ("sized", &sized_dm,
      "@brief Sizing (biasing) without modifying self\n"
      "@args d, mode\n"
      "\n"
      "Shifts the contour outwards (d>0) or inwards (d<0).\n"
      "This method is equivalent to\n"
      "@code\n"
      "sized(d, d, mode)\n"
      "@/code\n"
      "\n"
      "See \\size and \\sized for a detailed description.\n"
    ) +
    method_ext ("sized", &sized_d,
      "@brief Sizing (biasing)\n"
      "@args d\n"
      "\n"
      "@brief Sizing (biasing) without modifying self\n"
      "This method is equivalent to\n"
      "@code\n"
      "sized(d, d, 2)\n"
      "@/code\n"
      "\n"
      "See \\size and \\sized for a detailed description.\n"
    ) +
    method_ext ("size", &size_d,
      "@brief Sizing (biasing)\n"
      "@args d\n"
      "\n"
      "Shifts the contour outwards (d>0) or inwards (d<0).\n"
      "This method is equivalent to\n"
      "@code\n"
      "size(d, d, 2)\n"
      "@/code\n"
      "\n"
      "See \\size for a detailed description.\n"
    ) +
    method ("holes", &C::holes,
      "@brief Returns the number of holes"
    ) +
    iterator ("each_edge", (typename C::polygon_edge_iterator (C::*)() const) (&C::begin_edge), 
      "@brief Iterate over the edges that make up the polygon\n"
      "\n"
      "This iterator will deliver all edges, including those of the holes. "
      "Hole edges are oriented counterclockwise while hull egdes are oriented clockwise.\n"
    ) +
    iterator ("each_edge", (typename C::polygon_edge_iterator (C::*)(unsigned int) const) (&C::begin_edge), 
      "@brief Iterate over the edges of one contour of the polygon\n"
      "\n"
      "@args contour\n"
      "@param contour The contour number (0 for hull, 1 for first hole ...)\n"
      "\n"
      "This iterator will deliver all edges of the contour specified by the contour parameter. "
      "The hull has contour number 0, the first hole has contour 1 etc.\n"
      "Hole edges are oriented counterclockwise while hull egdes are oriented clockwise.\n"
      "\n"
      "This method was introduced in version 0.24."
    ) +
    method_ext ("inside?", &inside,
      "@brief Test, if the given point is inside the polygon\n"
      "@args p\n"
      "If the given point is inside or on the edge of the polygon, true is returned. "
      "This tests works well only if the polygon is not self-overlapping and oriented clockwise. "
    ) +
    method_ext ("compress", &compress,
      "@brief Compress the polygon.\n"
      "@args remove_reflected\n"
      "\n"
      "This method removes redundant points from the polygon, such as points being on a line formed by two other points.\n"
      "If remove_reflected is true, points are also removed if the two adjacent edges form a spike.\n"
      "\n"
      "@param remove_reflected See description of the functionality.\n"
      "\n"
      "This method was introduced in version 0.18.\n"
    ) +
    method ("is_box?", &C::is_box,
      "@brief Returns true, if the polygon is a simple box.\n"
      "\n"
      "A polygon is a box if it is identical to it's bounding box.\n"
      "\n"
      "@return True if the polygon is a box.\n"
      "\n"
      "This method was introduced in version 0.23.\n"
    ) +
    method_ext ("*", &scale,
      "@brief Scaling by some factor\n"
      "\n"
      "@args f\n"
      "\n"
      "Returns the scaled object. All coordinates are multiplied with the given factor and if "
      "necessary rounded."
    ) +
    method ("move", &C::move,
      "@brief Moves the polygon.\n"
      "@args p\n"
      "\n"
      "Moves the polygon by the given offset and returns the \n"
      "moved polygon. The polygon is overwritten.\n"
      "\n"
      "@param p The distance to move the polygon.\n"
      "\n"
      "@return The moved polygon (self).\n"
      "\n"
      "This method has been introduced in version 0.23.\n"
    ) +
    method_ext ("move", &move_xy,
      "@brief Moves the polygon.\n"
      "@args x,y\n"
      "\n"
      "Moves the polygon by the given offset and returns the \n"
      "moved polygon. The polygon is overwritten.\n"
      "\n"
      "@param x The x distance to move the polygon.\n"
      "@param y The y distance to move the polygon.\n"
      "\n"
      "@return The moved polygon (self).\n"
    ) +
    method ("moved", &C::moved,
      "@brief Returns the moved polygon (does not modify self)\n"
      "@args p\n"
      "\n"
      "Moves the polygon by the given offset and returns the \n"
      "moved polygon. The polygon is not modified.\n"
      "\n"
      "@param p The distance to move the polygon.\n"
      "\n"
      "@return The moved polygon.\n"
      "\n"
      "This method has been introduced in version 0.23.\n"
    ) +
    method_ext ("moved", &moved_xy,
      "@brief Returns the moved polygon (does not modify self)\n"
      "@args x,y\n"
      "\n"
      "Moves the polygon by the given offset and returns the \n"
      "moved polygon. The polygon is not modified.\n"
      "\n"
      "@param x The x distance to move the polygon.\n"
      "@param y The y distance to move the polygon.\n"
      "\n"
      "@return The moved polygon.\n"
      "\n"
      "This method has been introduced in version 0.23.\n"
    ) +
    method_ext ("transform", &transform,
      "@brief Transforms the polygon (in-place)\n"
      "@args t\n"
      "\n"
      "Transforms the polygon with the given transformation.\n"
      "Modifies self and returns self. An out-of-place version which does not modify self is \\transformed.\n"
      "\n"
      "@param t The transformation to apply.\n"
      "\n"
      "This method has been introduced in version 0.24.\n"
    ) +
    method_ext ("transformed", &transformed,
      "@brief Transforms the polygon\n"
      "@args t\n"
      "\n"
      "Transforms the polygon with the given transformation.\n"
      "Does not modify the polygon but returns the transformed polygon.\n"
      "\n"
      "@param t The transformation to apply.\n"
      "\n"
      "@return The transformed polygon.\n"
    ) +
    method_ext ("transformed|#transformed_cplx", &transformed_cplx,
      "@brief Transforms the polygon with a complex transformation\n"
      "@args t\n"
      "\n"
      "Transforms the polygon with the given complex transformation.\n"
      "Does not modify the polygon but returns the transformed polygon.\n"
      "\n"
      "@param t The transformation to apply.\n"
      "\n"
      "@return The transformed polygon.\n"
    ) +
    constructor ("from_s", &from_string,
      "@brief Creates an object from a string\n"
      "@args s\n"
      "Creates the object from a string representation (as returned by \\to_s)\n"
      "\n"
      "This method has been added in version 0.23.\n"
    ) +
    method ("to_s", (std::string (C::*) () const) &C::to_string,
      "@brief Convert to a string\n"
    ) +
    method_ext ("area", &area,
      "@brief The area of the polygon\n"
      "The area is correct only if the polygon is not self-overlapping and the polygon is oriented clockwise."
      "Orientation is ensured automatically in most cases.\n"
    ) +
    method ("perimeter", &C::perimeter,
      "@brief The perimeter of the polygon\n"
      "The perimeter is sum of the lengths of all edges making up the polygon.\n"
      "\n"
      "This method has been introduce in version 0.23.\n"
    ) +
    method ("bbox", &C::box,
      "@brief Return the bounding box of the polygon\n"
      "The bounding box is the box enclosing all points of the polygon.\n"
    );
  }
};

static db::Polygon p_from_dp (const db::DPolygon &d)
{
  return db::Polygon (db::Polygon::from_double (d, false));
}

static db::DPolygon dp_from_p (const db::Polygon &d)
{
  return db::DPolygon (d, db::cast_op<db::DPoint, db::Point> ());
}

static db::Polygon resolved_holes (const db::Polygon *p)
{
  return db::resolve_holes (*p);
}

static void resolve_holes (db::Polygon *p)
{
  if (p->holes () > 0) {
    *p = db::resolve_holes (*p);
  }
}

static db::SimplePolygon to_simple_polygon (const db::Polygon *p)
{
  return db::polygon_to_simple_polygon (*p);
}

static db::DPolygon *transform_cplx_dp (db::DPolygon *p, const db::DCplxTrans &t)
{
  p->transform (t, false /*don't compress*/);
  return p;
}

static db::Polygon *transform_icplx_dp (db::Polygon *p, const db::ICplxTrans &t)
{
  p->transform (t, false /*don't compress*/);
  return p;
}

static db::Polygon transformed_icplx_dp (const db::Polygon *p, const db::ICplxTrans &t)
{
  return p->transformed (t, false /*don't compress*/);
}

static db::Polygon smooth (const db::Polygon *p, db::Coord d)
{
  return db::smooth (*p, d);
}

static db::Polygon round_corners (const db::Polygon *p, double rinner, double router, unsigned int n)
{
  return db::compute_rounded (*p, rinner, router, n);
}

static db::Polygon minkowsky_sum_pe (const db::Polygon *p, const db::Edge &e, bool rh)
{
  return db::minkowsky_sum (*p, e, rh);
}

static db::Polygon minkowsky_sum_pp (const db::Polygon *p, const db::Polygon &pp, bool rh)
{
  return db::minkowsky_sum (*p, pp, rh);
}

static db::Polygon minkowsky_sum_pb (const db::Polygon *p, const db::Box &b, bool rh)
{
  return db::minkowsky_sum (*p, b, rh);
}

static db::Polygon minkowsky_sum_pc (const db::Polygon *p, const std::vector<db::Point> &c, bool rh)
{
  return db::minkowsky_sum (*p, c, rh);
}

Class<db::Polygon> decl_Polygon ("Polygon", 
  polygon_defs<db::Polygon>::methods () +
  method ("from_dpoly", &p_from_dp, 
    "@brief Construct an integer-coordinate polygon from a floating-point coordinate one"
    "\n"
    "@args double_poly\n"
    "\n"
    "This method has been added in version 0.15."
  ) +
  method_ext ("resolve_holes", &resolve_holes,
    "@brief Resolve holes by inserting cut lines and joining the holes with the hull\n"
    "\n"
    "This method modifies the polygon. The out-of-place version is \\resolved_holes.\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("resolved_holes", &resolved_holes,
    "@brief Returns a polygon without holes\n"
    "\n"
    "@return The new polygon without holes.\n"
    "\n"
    "This method does not modify the polygon but return a new polygon.\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("to_simple_polygon", &to_simple_polygon,
    "@brief Converts a polygon to a simple polygon\n"
    "\n"
    "@return The simple polygon.\n"
    "\n"
    "If the polygon contains holes, these will be resolved.\n"
    "This operation requires a well-formed polygon. Reflecting edges, self-intersections and "
    "coincident points will be removed.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("smooth", &smooth,
    "@brief Smoothes a polygon\n"
    "@args d\n"
    "\n"
    "Remove vertices that deviate by more than the distance d from the average contour.\n"
    "The value d is basically the roughness which is removed.\n"
    "\n"
    "@param d The smoothing \"roughness\".\n"
    "\n"
    "@return The smoothed polygon.\n"
    "\n"
    "This method was introduced in version 0.23.\n"
  ) +
  method_ext ("round_corners", &round_corners,
    "@brief Rounds the corners of the polygon\n"
    "@args rinner, router, n\n"
    "\n"
    "Replaces the corners of the polygon with circle segments.\n"
    "\n"
    "@param rinner The circle radius of inner corners (in database units).\n"
    "@param router The circle radius of outer corners (in database units).\n"
    "@param n The number of points per full circle.\n"
    "\n"
    "@return The new polygon.\n"
    "\n"
    "This method was introduced in version 0.20.\n"
  ) +
  method_ext ("minkowsky_sum", &minkowsky_sum_pe,
    "@brief Computes the Minkowsky sum of the polygon and an edge\n"
    "@args e, resolve_holes\n"
    "\n"
    "@param e The edge.\n"
    "@param resolve_holes If true, the output polygon will not contain holes, but holes are resolved by joining the holes with the hull.\n"
    "\n"
    "@return The new polygon representing the Minkowsky sum with the edge e.\n"
    "\n"
    "The Minkowsky sum of a polygon and an edge basically results in the area covered when "
    "\"dragging\" the polygon along the line given by the edge. The effect is similar to drawing the line "
    "with a pencil that has the shape of the given polygon.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("minkowsky_sum", &minkowsky_sum_pp,
    "@brief Computes the Minkowsky sum of the polygon and a polygon\n"
    "@args p, resolve_holes\n"
    "\n"
    "@param p The first argument.\n"
    "@param resolve_holes If true, the output polygon will not contain holes, but holes are resolved by joining the holes with the hull.\n"
    "\n"
    "@return The new polygon representing the Minkowsky sum of self and p.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("minkowsky_sum", &minkowsky_sum_pb,
    "@brief Computes the Minkowsky sum of the polygon and a box\n"
    "@args b, resolve_holes\n"
    "\n"
    "@param b The box.\n"
    "@param resolve_holes If true, the output polygon will not contain holes, but holes are resolved by joining the holes with the hull.\n"
    "\n"
    "@return The new polygon representing the Minkowsky sum of self and the box.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("minkowsky_sum", &minkowsky_sum_pc,
    "@brief Computes the Minkowsky sum of the polygon and a contour of points (a trace)\n"
    "@args b, resolve_holes\n"
    "\n"
    "@param b The contour (a series of points forming the trace).\n"
    "@param resolve_holes If true, the output polygon will not contain holes, but holes are resolved by joining the holes with the hull.\n"
    "\n"
    "@return The new polygon representing the Minkowsky sum of self and the contour.\n"
    "\n"
    "This method was introduced in version 0.22.\n"
  ) +
  method_ext ("transform|#transform_cplx", &transform_icplx_dp,
    "@brief Transforms the polygon with a complex transformation (in-place)\n"
    "@args t\n"
    "\n"
    "Transforms the polygon with the given complex transformation.\n"
    "This version modifies self and will return self as the modified polygon. An out-of-place version "
    "which does not modify self is \\transformed.\n"
    "\n"
    "@param t The transformation to apply.\n"
    "\n"
    "This method was introduced in version 0.24.\n"
  ) +
  method_ext ("transformed|#transformed_cplx", &transformed_icplx_dp,
    "@brief Transforms the polygon with a complex transformation\n"
    "@args t\n"
    "\n"
    "Transforms the polygon with the given complex transformation.\n"
    "Does not modify the polygon but returns the transformed polygon.\n"
    "\n"
    "@param t The transformation to apply.\n"
    "\n"
    "@return The transformed polygon (in this case an integer coordinate polygon).\n"
    "\n"
    "This method was introduced in version 0.18.\n"
  ),
  "@brief A polygon class\n"
  "\n"
  "A polygon consists of an outer hull and zero to many\n"
  "holes. Each contour consists of several points. The point\n"
  "list is normalized such that the leftmost, lowest point is \n"
  "the first one. The orientation is normalized such that\n"
  "the orientation of the hull contour is clockwise, while\n"
  "the orientation of the holes is counterclockwise.\n"
  "\n"
  "It is in no way checked that the contours are not overlapping.\n"
  "This must be ensured by the user of the object\n"
  "when filling the contours.\n"
  "\n"
  "A polygon can be asked for the number of holes using the \\holes method. "
  "\\each_point_hull delivers the points of the hull contour. \\each_point_hole delivers the points "
  "of a specific hole. \\each_edge delivers the edges (point-to-point connections) of both hull and holes. "
  "\\bbox delivers the bounding box, \\area the area and \\perimeter the perimeter of the polygon.\n"
  "\n"
  "Here's an example of how to create a polygon:\n"
  "\n"
  "@code\n"
  "hull =  [ RBA::Point::new(0, 0),       RBA::Point::new(6000, 0), \n"
  "          RBA::Point::new(6000, 3000), RBA::Point::new(0, 3000) ]\n"
  "hole1 = [ RBA::Point::new(1000, 1000), RBA::Point::new(2000, 1000), \n"
  "          RBA::Point::new(2000, 2000), RBA::Point::new(1000, 2000) ]\n"
  "hole2 = [ RBA::Point::new(3000, 1000), RBA::Point::new(4000, 1000), \n"
  "          RBA::Point::new(4000, 2000), RBA::Point::new(3000, 2000) ]\n"
  "poly = RBA::Polygon::new(hull)\n"
  "poly.insert_hole(hole1)\n"
  "poly.insert_hole(hole2)\n"
  "\n"
  "# ask the polygon for some properties\n"
  "poly.holes      # -> 2\n"
  "poly.area       # -> 16000000\n"
  "poly.perimeter  # -> 26000\n"
  "poly.bbox       # -> (0,0;6000,3000)\n"
  "@/code\n"
  "\n"
  "The \\Polygon class stores coordinates in integer format. "
  "A class that stores floating-point coordinates is \\DPolygon.\n"
  "\n"
  "See @<a href=\"/programming/database_api.xml\">The Database API@</a> for more details about the "
  "database objects."
);

Class<db::DPolygon> decl_DPolygon ("DPolygon", 
  polygon_defs<db::DPolygon>::methods () +
  method ("from_ipoly", &dp_from_p, 
    "@brief Construct a floating-point coordinate polygon from an integer coordinate one"
    "\n"
    "@args int_poly\n"
    "\n"
    "This method has been added in version 0.15."
  ) +
  method_ext ("transform|#transform_cplx", &transform_cplx_dp,
    "@brief Transforms the polygon with a complex transformation (in-place)\n"
    "@args t\n"
    "\n"
    "Transforms the polygon with the given complex transformation.\n"
    "Modifies self and returns self. An out-of-place version which does not modify self is \\transformed.\n"
    "\n"
    "@param t The transformation to apply.\n"
    "\n"
    "This method has been introduced in version 0.24.\n"
  ), 
  "@brief A polygon class\n"
  "\n"
  "A polygon consists of an outer hull and zero to many\n"
  "holes. Each contour consists of several points. The point\n"
  "list is normalized such that the leftmost, lowest point is \n"
  "the first one. The orientation is normalized such that\n"
  "the orientation of the hull contour is clockwise, while\n"
  "the orientation of the holes is counterclockwise.\n"
  "\n"
  "It is in no way checked that the contours are not overlapping.\n"
  "This must be ensured by the user of the object\n"
  "when filling the contours.\n"
  "\n"
  "A polygon can be asked for the number of holes using the \\holes method. "
  "\\each_point_hull delivers the points of the hull contour. \\each_point_hole delivers the points "
  "of a specific hole. \\each_edge delivers the edges (point-to-point connections) of both hull and holes. "
  "\\bbox delivers the bounding box, \\area the area and \\perimeter the perimeter of the polygon.\n"
  "\n"
  "Here's an example of how to create a polygon:\n"
  "\n"
  "@code\n"
  "hull =  [ RBA::DPoint::new(0, 0),       RBA::DPoint::new(6000, 0), \n"
  "          RBA::DPoint::new(6000, 3000), RBA::DPoint::new(0, 3000) ]\n"
  "hole1 = [ RBA::DPoint::new(1000, 1000), RBA::DPoint::new(2000, 1000), \n"
  "          RBA::DPoint::new(2000, 2000), RBA::DPoint::new(1000, 2000) ]\n"
  "hole2 = [ RBA::DPoint::new(3000, 1000), RBA::DPoint::new(4000, 1000), \n"
  "          RBA::DPoint::new(4000, 2000), RBA::DPoint::new(3000, 2000) ]\n"
  "poly = RBA::DPolygon::new(hull)\n"
  "poly.insert_hole(hole1)\n"
  "poly.insert_hole(hole2)\n"
  "\n"
  "# ask the polygon for some properties\n"
  "poly.holes      # -> 2\n"
  "poly.area       # -> 16000000.0\n"
  "poly.perimeter  # -> 26000.0\n"
  "poly.bbox       # -> (0,0;6000,3000)\n"
  "@/code\n"
  "\n"
  "The \\DPolygon class stores coordinates in floating-point format which gives a higher precision "
  "for some operations. A class that stores integer coordinates is \\Polygon.\n"
  "\n"
  "See @<a href=\"/programming/database_api.xml\">The Database API@</a> for more details about the "
  "database objects."
);

}

