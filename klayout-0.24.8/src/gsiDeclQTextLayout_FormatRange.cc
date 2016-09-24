
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

/**
*  @file gsiDeclQTextLayout_FormatRange.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQTextLayout_FormatRange_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QTextLayout::FormatRange

//  Constructor QTextLayout::FormatRange::FormatRange()


static void _init_ctor_QTextLayout_FormatRange_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QTextLayout::FormatRange *> ();
}

static void _call_ctor_QTextLayout_FormatRange_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QTextLayout::FormatRange *> (new QTextLayout::FormatRange ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextLayout_FormatRange_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextLayout::FormatRange::FormatRange()\nThis method creates an object of class QTextLayout::FormatRange.", &_init_ctor_QTextLayout_FormatRange_0, &_call_ctor_QTextLayout_FormatRange_0);
}


namespace gsi
{
gsi::Class<QTextLayout::FormatRange> decl_QTextLayout_FormatRange ("QTextLayout_FormatRange",
  gsi::Methods(_create_ctor_QTextLayout_FormatRange_0 ()),
  "@qt\n@brief Binding of QTextLayout::FormatRange");

gsi::ClassExt<QTextLayout> decl_QTextLayout_FormatRange_as_child (decl_QTextLayout_FormatRange, "FormatRange");
}

