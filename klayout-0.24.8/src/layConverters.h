
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


#ifndef HDR_layConverters
#define HDR_layConverters

#include "config.h"

#include <QtGui/QColor>

#include "dbLayerProperties.h"

namespace lay
{

/**
 *  @brief A color converter class for converting colors to strings and vice versa
 */
struct KLAYOUT_DLL ColorConverter 
{
  std::string to_string (const QColor &c) const;
  void from_string (const std::string &s, QColor &c) const;
};

/**
 *  @brief A converter for transformations
 *
 *  T is supposed a transformation type such as "db::DCplxTrans".
 */
template <class T>
struct KLAYOUT_DLL TransformationConverter
{
  std::string to_string (const T &t) const
  {
    return t.to_string ();
  }

  void from_string (const std::string &s, T &t) const
  {
    tl::Extractor ex (s.c_str ());
    ex.read (t);
    ex.expect_end ();
  }
};

/**
 *  @brief A converter for layout layers
 */
struct KLAYOUT_DLL LayoutLayerConverter
{
  std::string to_string (const db::LayerProperties &p) const
  {
    return p.to_string ();
  }

  void from_string (const std::string &s, db::LayerProperties &p) const
  {
    tl::Extractor ex (s.c_str ());
    p.read (ex);
    ex.expect_end ();
  }
};

/**
 *  @brief A converter for points
 *
 *  P is supposed to be a point type (i.e. db::DPoint).
 */
template <class P>
struct KLAYOUT_DLL PointConverter
{
  std::string to_string (const P &p) const
  {
    return tl::to_string (p.x ()) + "," + tl::to_string (p.y ());
  }

  void from_string (const std::string &s, P &p) const
  {
    typename P::coord_type x, y;
    tl::Extractor ex (s.c_str ());
    ex.read (x);
    ex.expect (",");
    ex.read (y);
    p = P (x, y);
    ex.expect_end ();
  }
};

}

#endif

