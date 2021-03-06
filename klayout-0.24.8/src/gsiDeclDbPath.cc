
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
#include "dbPath.h"

namespace gsi
{

// ---------------------------------------------------------------
//  path binding

template <class C>
struct path_defs
{
  typedef typename C::coord_type coord_type;
  typedef typename C::box_type box_type;
  typedef typename C::point_type point_type;
  typedef typename C::distance_type distance_type;
  typedef typename C::area_type area_type;
  typedef db::simple_trans<coord_type> simple_trans_type;
  typedef db::complex_trans<coord_type, double> complex_trans_type;
  typedef db::complex_trans<coord_type, coord_type> icomplex_trans_type;

  static void set_points (C *c, const std::vector<point_type> &pts)
  {
    return c->assign (pts.begin (), pts.end ());
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
    return new C ();
  }

  static C *new_pw (const std::vector<point_type> &pts, coord_type width)
  {
    return new C (pts.begin (), pts.end (), width);
  }

  static C *new_pwx (const std::vector<point_type> &pts, coord_type width, coord_type bgn_ext, coord_type end_ext)
  {
    return new C (pts.begin (), pts.end (), width, bgn_ext, end_ext);
  }

  static C *new_pwxr (const std::vector<point_type> &pts, coord_type width, coord_type bgn_ext, coord_type end_ext, bool round)
  {
    return new C (pts.begin (), pts.end (), width, bgn_ext, end_ext, round);
  }

#if defined(HAVE_64BIT_COORD)
  //  workaround for missing 128bit binding of GSI
  static double area (const C *path)
#else
  static area_type area (const C *path)
#endif
  { 
    return path->area ();
  }

  static distance_type length (const C *path)
  { 
    return path->length ();
  }

  static C &move_xy (C *p, coord_type dx, coord_type dy)
  {
    return p->move (point_type (dx, dy));
  }

  static C moved_xy (const C *p, coord_type dx, coord_type dy)
  {
    return p->moved (point_type (dx, dy));
  }

  static C scale (const C *p, double s)
  {
    return C (p->transformed (icomplex_trans_type (s)));
  }

  static gsi::Methods methods ()
  {
    return
    constructor ("new", &new_v, 
      "@brief Default constructor: creates an empty (invalid) path with width 0"
    ) +
    constructor ("new|#new_pw", &new_pw, 
      "@brief Constructor given the points of the path's spine and the width\n"
      "\n"
      "@args pts, width\n"
      "\n"
      "@param pts The points forming the spine of the path\n"
      "@param width The width of the path\n"
    ) +
    constructor ("new|#new_pwx", &new_pwx, 
      "@brief Constructor given the points of the path's spine, the width and the extensions\n"
      "\n"
      "@args pts, width, bgn_ext, end_ext\n"
      "\n"
      "@param pts The points forming the spine of the path\n"
      "@param width The width of the path\n"
      "@param bgn_ext The begin extension of the path\n"
      "@param end_ext The end extension of the path\n"
    ) +
    constructor ("new|#new_pwxr", &new_pwxr, 
      "@brief Constructor given the points of the path's spine, the width, the extensions and the round end flag\n"
      "\n"
      "@args pts, width, bgn_ext, end_ext, round\n"
      "\n"
      "@param pts The points forming the spine of the path\n"
      "@param width The width of the path\n"
      "@param bgn_ext The begin extension of the path\n"
      "@param end_ext The end extension of the path\n"
      "@param round If this flag is true, the path will get rounded ends\n"
    ) +
    method ("<", &C::operator<,
      "@brief Less operator\n"
      "@args p\n"
      "@param p The object to compare against\n"
      "This operator is provided to establish some, not necessarily a certain sorting order"
    ) +
    method ("==", &C::operator==,
      "@brief Equality test\n"
      "@args p\n"
      "@param p The object to compare against"
    ) +
    method ("!=", &C::operator!=,
      "@brief Inequality test\n"
      "@args p\n"
      "@param p The object to compare against\n"
    ) +
    method_ext ("points=", &set_points,
      "@brief Set the points of the path\n"
      "@args p\n"
      "@param p An array of points to assign to the path's spine"
    ) +
    iterator ("each_point", &C::begin, &C::end, 
      "@brief Get the points that make up the path's spine"
    ) +
    method ("num_points|#points", &C::points,
      "@brief Get the number of points"
    ) +
    method ("width=", (void (C::*)(coord_type)) &C::width,
      "@brief Set the width\n"
      "@args w\n"
    ) +
    method ("width", (coord_type (C::*)() const) &C::width,
      "@brief Get the width\n"
    ) +
    method ("bgn_ext=", (void (C::*)(coord_type)) &C::bgn_ext,
      "@brief Set the begin extension\n"
      "@args ext\n"
    ) +
    method ("bgn_ext", (coord_type (C::*)() const) &C::bgn_ext,
      "@brief Get the begin extension\n"
    ) +
    method ("end_ext=", (void (C::*)(coord_type)) &C::end_ext,
      "@brief Set the end extension\n"
      "@args ext\n"
    ) +
    method ("end_ext", (coord_type (C::*)() const) &C::end_ext,
      "@brief Get the end extension\n"
    ) +
    method ("round=", (void (C::*)(bool)) &C::round,
      "@brief Set the 'round ends' flag\n"
      "@args round_ends_flag\n"
      "A path with round ends show half circles at the ends, instead of square or rectangular ends. "
      "Paths with this flag set should use a begin and end extension of half the width (see \\bgn_ext and \\end_ext). "
      "The interpretation of such paths in other tools may differ otherwise."
    ) +
    method ("is_round?", (bool (C::*)() const) &C::round,
      "@brief Returns true, if the path has round ends\n"
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
      "@brief Moves the path.\n"
      "@args p\n"
      "\n"
      "Moves the path by the given offset and returns the \n"
      "moved path. The path is overwritten.\n"
      "\n"
      "@param p The distance to move the path.\n"
      "\n"
      "@return The moved path.\n"
    ) +
    method_ext ("move", &move_xy,
      "@brief Moves the path.\n"
      "@args dx, dy\n"
      "\n"
      "Moves the path by the given offset and returns the \n"
      "moved path. The path is overwritten.\n"
      "\n"
      "@param dx The x distance to move the path.\n"
      "@param dy The y distance to move the path.\n"
      "\n"
      "@return The moved path.\n"
      "\n"
      "This version has been added in version 0.23.\n"
    ) +
    method ("moved", &C::moved,
      "@brief Returns the moved path (does not change self)\n"
      "@args p\n"
      "\n"
      "Moves the path by the given offset and returns the \n"
      "moved path. The path is not modified.\n"
      "\n"
      "@param p The distance to move the path.\n"
      "\n"
      "@return The moved path.\n"
    ) +
    method_ext ("moved", &moved_xy,
      "@brief Returns the moved path (does not change self)\n"
      "@args dx, dy\n"
      "\n"
      "Moves the path by the given offset and returns the \n"
      "moved path. The path is not modified.\n"
      "\n"
      "@param dx The x distance to move the path.\n"
      "@param dy The y distance to move the path.\n"
      "\n"
      "@return The moved path.\n"
      "\n"
      "This version has been added in version 0.23.\n"
    ) +
    method ("transformed", &C::template transformed<simple_trans_type>,
      "@brief Transform the path.\n"
      "@args t\n"
      "\n"
      "Transforms the path with the given transformation.\n"
      "Does not modify the path but returns the transformed path.\n"
      "\n"
      "@param t The transformation to apply.\n"
      "\n"
      "@return The transformed path.\n"
    ) +
    method ("transformed|#transformed_cplx", &C::template transformed<complex_trans_type>,
      "@brief Transform the path.\n"
      "@args t\n"
      "\n"
      "Transforms the path with the given complex transformation.\n"
      "Does not modify the path but returns the transformed path.\n"
      "\n"
      "@param t The transformation to apply.\n"
      "\n"
      "@return The transformed path.\n"
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
    method ("simple_polygon", &C::simple_polygon,
      "@brief Convert the path to a simple polygon\n"
      "The returned polygon is not guaranteed to be non-selfoverlapping. This may happen if the path overlaps "
      "itself or contains very short segments."
    ) +
    method ("polygon", &C::polygon,
      "@brief Convert the path to a polygon\n"
      "The returned polygon is not guaranteed to be non-self overlapping. This may happen if the path overlaps "
      "itself or contains very short segments."
    ) +
    method ("perimeter", &C::perimeter,
      "@brief Returns the approximate perimeter of the path\n"
      "This method returns the approximate value of the perimeter. It is computed from the length and the width. "
      "end extensions are taken into account correctly, but not effects of the corner interpolation.\n"
      "This method was added in version 0.24.4.\n"
    ) +
    method_ext ("area", &area,
      "@brief Returns the approximate area of the path\n"
      "This method returns the approximate value of the area. It is computed from the length times the width. "
      "end extensions are taken into account correctly, but not effects of the corner interpolation.\n"
      "This method was added in version 0.22.\n"
    ) +
    method_ext ("length", &length,
      "@brief Returns the length of the path\n"
      "the length of the path is determined by summing the lengths of the segments and "
      "adding begin and end extensions. For round-ended paths the length of the paths between the tips "
      "of the ends.\n"
      "\n"
      "This method was added in version 0.23.\n"
    ) +
    method ("bbox", &C::box,
      "@brief Returns the bounding box of the path"
    );
  }
};

db::Path from_dp (const db::DPath &d)
{
  return db::Path (db::Path::from_double (d));
}

db::DPath from_p (const db::Path &d)
{
  return db::DPath (d, db::cast_op<db::DPoint, db::Point> (), db::cast_op<double, db::Coord> ());
}

Class<db::Path> decl_Path ("Path", 
  path_defs<db::Path>::methods () +
  method ("from_dpath", &from_dp, 
    "@brief Construct an integer-coordinate path from a floating-point coordinate one\n"
    "\n"
    "@args double_path\n"
    "\n"
    "This method has been added in version 0.15."
  ) +
  method ("transformed|#transformed_cplx", &db::Path::transformed<db::ICplxTrans>,
    "@brief Transform the path.\n"
    "@args t\n"
    "\n"
    "Transforms the path with the given complex transformation.\n"
    "Does not modify the path but returns the transformed path.\n"
    "\n"
    "@param t The transformation to apply.\n"
    "\n"
    "@return The transformed path (in this case an integer coordinate path).\n"
    "\n"
    "This method has been introduced in version 0.18.\n"
  ),
  "@brief A path class\n"
  "\n"
  "A path consists of an sequence of line segments forming the 'spine' of the path "
  "and a width. In addition, the starting point can be drawn back by a certain extent (the 'begin extension') "
  "and the end point can be pulled forward somewhat (by the 'end extension').\n"
  "\n"
  "A path may have round ends for special purposes. In particular, a round-ended path with a single point "
  "can represent a circle. Round-ended paths should have being and end extensions equal to half the width. "
  "Non-round-ended paths with a single point are allowed but the definition "
  "of the resulting shape in not well defined and may differ in other tools.\n"
  "\n"
  "See @<a href=\"/programming/database_api.xml\">The Database API@</a> for more details about the "
  "database objects."
);

Class<db::DPath> decl_DPath ("DPath", 
  path_defs<db::DPath>::methods () +
  method ("from_ipath", &from_p, 
    "@brief Construct a floating-point coordinate path from an integer coordinate one"
    "\n"
    "@args int_path\n"
    "\n"
    "This method has been added in version 0.15."
  ),
  "@brief A path class\n"
  "\n"
  "A path consists of an sequence of line segments forming the 'spine' of the path "
  "and a width. In addition, the starting point can be drawn back by a certain extent (the 'begin extension') "
  "and the end point can be pulled forward somewhat (by the 'end extension').\n"
  "\n"
  "A path may have round ends for special purposes. In particular, a round-ended path with a single point "
  "can represent a circle. Round-ended paths should have being and end extensions equal to half the width. "
  "Non-round-ended paths with a single point are allowed but the definition "
  "of the resulting shape in not well defined and may differ in other tools.\n"
  "\n"
  "See @<a href=\"/programming/database_api.xml\">The Database API@</a> for more details about the "
  "database objects."
);

}

