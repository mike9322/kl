
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



#include "dbPCellDeclaration.h"

namespace db
{

PCellDeclaration::PCellDeclaration ()
  : m_ref_count (0), m_id (0), m_has_parameter_declarations (false)
{ 
  // .. nothing yet ..
}

void 
PCellDeclaration::add_ref ()
{
  //  For script clients this line makes the object C++-owned
  if (m_ref_count == 0) {
    keep ();
  }
  ++m_ref_count;
}

void 
PCellDeclaration::release_ref ()
{
  --m_ref_count;
  if (m_ref_count <= 0) {
    delete this;
  }
}

pcell_parameters_type
PCellDeclaration::map_parameters (const std::map<size_t, tl::Variant> &param_by_name) const
{
  db::pcell_parameters_type new_param;
  size_t i = 0;
  for (std::vector<PCellParameterDeclaration>::const_iterator pd = parameter_declarations ().begin (); pd != parameter_declarations ().end (); ++pd, ++i) {
    std::map<size_t, tl::Variant>::const_iterator p = param_by_name.find (i);
    if (p != param_by_name.end ()) {
      new_param.push_back (p->second);
    } else {
      new_param.push_back (pd->get_default ());
    }
  }

  return new_param;
}

pcell_parameters_type
PCellDeclaration::map_parameters (const std::map<std::string, tl::Variant> &param_by_name) const
{
  db::pcell_parameters_type new_param;
  for (std::vector<PCellParameterDeclaration>::const_iterator pd = parameter_declarations ().begin (); pd != parameter_declarations ().end (); ++pd) {
    std::map<std::string, tl::Variant>::const_iterator p = param_by_name.find (pd->get_name ());
    if (p != param_by_name.end ()) {
      new_param.push_back (p->second);
    } else {
      new_param.push_back (pd->get_default ());
    }
  }

  return new_param;
}

}

