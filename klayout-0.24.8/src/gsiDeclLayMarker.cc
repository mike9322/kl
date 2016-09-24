
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
#include "layMarker.h"
#include "layLayoutView.h"

namespace gsi
{

static 
lay::DMarker *create_marker (lay::LayoutView *view) 
{
  return new lay::DMarker (view);
}

static 
void reset_frame_color (lay::DMarker *marker)
{
  marker->set_frame_color (QColor ());
}

static 
void set_frame_color (lay::DMarker *marker, unsigned int color) 
{
  marker->set_frame_color (QColor (color));
}

static 
unsigned int get_frame_color (const lay::DMarker *marker) 
{
  return marker->get_frame_color ().rgb ();
}

static 
bool has_frame_color (const lay::DMarker *marker) 
{
  return marker->get_frame_color ().isValid ();
}

static 
void reset_color (lay::DMarker *marker)
{
  marker->set_color (QColor ());
}

static 
void set_color (lay::DMarker *marker, unsigned int color) 
{
  marker->set_color (QColor (color));
}

static 
unsigned int get_color (const lay::DMarker *marker) 
{
  return marker->get_color ().rgb ();
}

static 
bool has_color (const lay::DMarker *marker) 
{
  return marker->get_color ().isValid ();
}

Class<lay::DMarker> decl_Marker ("Marker", 
  gsi::constructor ("new", &create_marker,
    "@brief The constructor for a marker\n"
    "@args view\n"
    "\n"
    "A marker is always associated with a view, in which it is shown. The "
    "view this marker is associated with must be passed to the constructor."
  ) +
  gsi::method ("set|set_box", (void (lay::DMarker::*) (const db::DBox &)) &lay::DMarker::set,
    "@brief Set the box the marker is to display\n"
    "@args box\n"
    "\n"
    "Makes the marker show a box. The box must be given in micron units.\n"
    "If the box is empty, no marker is drawn.\n"
    "The set method has been added in version 0.20.\n"
  ) +
  gsi::method ("set|set_text", (void (lay::DMarker::*) (const db::DText &)) &lay::DMarker::set,
    "@brief Set the text the marker is to display\n"
    "@args text\n"
    "\n"
    "Makes the marker show a text. The text must be given in micron units.\n"
    "The set method has been added in version 0.20.\n"
  ) +
  gsi::method ("set|set_edge", (void (lay::DMarker::*) (const db::DEdge &)) &lay::DMarker::set,
    "@brief Set the edge the marker is to display\n"
    "@args edge\n"
    "\n"
    "Makes the marker show a edge. The edge must be given in micron units.\n"
    "The set method has been added in version 0.20.\n"
  ) +
  gsi::method ("set|set_path", (void (lay::DMarker::*) (const db::DPath &)) &lay::DMarker::set,
    "@brief Set the path the marker is to display\n"
    "@args path\n"
    "\n"
    "Makes the marker show a path. The path must be given in micron units.\n"
    "The set method has been added in version 0.20.\n"
  ) +
  gsi::method ("set|set_polygon", (void (lay::DMarker::*) (const db::DPolygon &)) &lay::DMarker::set,
    "@brief Set the polygon the marker is to display\n"
    "@args polygon\n"
    "\n"
    "Makes the marker show a polygon. The polygon must be given in micron units.\n"
    "The set method has been added in version 0.20.\n"
  ) + 
  gsi::method_ext ("color=", set_color,
    "@brief Set the color of the marker\n"
    "@args color\n"
    "The color is a 32bit unsigned integer encoding the RGB values in the lower 3 bytes (blue in the lowest significant byte). "
    "The color can be reset with \\reset_color, in which case, the default foreground color is used."
  ) +
  gsi::method_ext ("reset_color", reset_color,
    "@brief Reset the color of the marker\n"
    "See \\set_color for a description of the color property of the marker."
  ) +
  gsi::method_ext ("color", get_color,
    "@brief Get the color of the marker\n"
    "This value is valid only if \\has_color? is true."
  ) +
  gsi::method_ext ("has_color?", has_color,
    "@brief True, if the marker has a specific color\n"
  ) +
  gsi::method_ext ("frame_color=", set_frame_color,
    "@brief Set the frame color of the marker\n"
    "@args color\n"
    "The color is a 32bit unsigned integer encoding the RGB values in the lower 3 bytes (blue in the lowest significant byte). "
    "The color can be reset with \\reset_frame_color, in which case the fill color is used.\n"
    "The set method has been added in version 0.20.\n"
  ) +
  gsi::method_ext ("reset_frame_color", reset_frame_color,
    "@brief Reset the frame color of the marker\n"
    "See \\set_frame_color for a description of the frame color property of the marker."
    "The set method has been added in version 0.20.\n"
  ) +
  gsi::method_ext ("frame_color", get_frame_color,
    "@brief Get the frame color of the marker\n"
    "This value is valid only if \\has_frame_color? is true."
    "The set method has been added in version 0.20.\n"
  ) +
  gsi::method_ext ("has_frame_color?", has_frame_color,
    "@brief True, if the marker has a specific frame color\n"
    "The set method has been added in version 0.20.\n"
  ) +
  gsi::method ("line_width=", &lay::DMarker::set_line_width,
    "@brief Set the line width of the marker\n"
    "@args width\n"
    "This is the width of the line drawn for the outline of the marker."
  ) +
  gsi::method ("line_width", &lay::DMarker::get_line_width,
    "@brief Get the line width of the marker\n"
    "See \\line_width= for a description of the line width."
  ) +
  gsi::method ("vertex_size=", &lay::DMarker::set_vertex_size,
    "@brief Set the vertex size of the marker\n"
    "@args size\n"
    "This is the size of the rectangles drawn for the vertices object."
  ) +
  gsi::method ("vertex_size", &lay::DMarker::get_vertex_size,
    "@brief Get the vertex size of the marker\n"
    "See \\vertex_size= for a description."
  ) +
  gsi::method ("halo=", &lay::DMarker::set_halo,
    "@brief Set the halo flag\n"
    "@args halo\n"
    "The halo flag is either -1 (for taking the default), 0 to disable the halo or 1 to enable it. "
    "If the halo is enabled, a pixel border with the background color is drawn around the marker, the "
    "vertices and texts."
  ) +
  gsi::method ("halo", &lay::DMarker::get_halo,
    "@brief Get the halo flag\n"
    "See \\halo= for a description of the halo flag."
  ) +
  gsi::method ("dither_pattern=", &lay::DMarker::set_dither_pattern,
    "@brief Set the stipple pattern index\n"
    "@args index\n"
    "A value of -1 or less than zero indicates that the marker is not filled. Otherwise, the "
    "value indicates which pattern to use for filling the marker."
  ) +
  gsi::method ("dither_pattern", &lay::DMarker::get_dither_pattern,
    "@brief Get the stipple pattern index\n"
    "See \\dither_pattern= for a description of the stipple pattern index."
  ),
  "@brief The floating-point coordinate marker object\n"
  "\n"
  "The marker is a visual object that \"marks\" (highlights) a \n"
  "certain area of the layout, given by a database object. "
  "This object accepts database objects with floating-point coordinates in micron values.\n"
);
  
}

