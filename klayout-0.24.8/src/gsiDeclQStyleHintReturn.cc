
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
*  @file gsiDeclQStyleHintReturn.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQStyleHintReturn_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QStyleHintReturn

//  Constructor QStyleHintReturn::QStyleHintReturn(int version, int type)


static void _init_ctor_QStyleHintReturn_1426 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("version", true, "QStyleOption::Version");
  decl->add_arg<int > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("type", true, "QStyleHintReturn::SH_Default");
  decl->add_arg<int > (argspec_1);
  decl->set_return_new<QStyleHintReturn *> ();
}

static void _call_ctor_QStyleHintReturn_1426 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args ? args.read<int > () : (int)(QStyleOption::Version);
  int arg2 = args ? args.read<int > () : (int)(QStyleHintReturn::SH_Default);
  ret.write<QStyleHintReturn *> (new QStyleHintReturn (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleHintReturn_1426 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleHintReturn::QStyleHintReturn(int version, int type)\nThis method creates an object of class QStyleHintReturn.", &_init_ctor_QStyleHintReturn_1426, &_call_ctor_QStyleHintReturn_1426);
}


namespace gsi
{
gsi::Class<QStyleHintReturn> decl_QStyleHintReturn ("QStyleHintReturn",
  gsi::Methods(_create_ctor_QStyleHintReturn_1426 ()),
  "@qt\n@brief Binding of QStyleHintReturn");

}

