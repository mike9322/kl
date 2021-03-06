
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
*  @file gsiDeclQStyleOptionTabV3.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQStyleOptionTabV3_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QStyleOptionTabV3

//  Constructor QStyleOptionTabV3::QStyleOptionTabV3()


static void _init_ctor_QStyleOptionTabV3_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QStyleOptionTabV3 *> ();
}

static void _call_ctor_QStyleOptionTabV3_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QStyleOptionTabV3 *> (new QStyleOptionTabV3 ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionTabV3_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionTabV3::QStyleOptionTabV3()\nThis method creates an object of class QStyleOptionTabV3.", &_init_ctor_QStyleOptionTabV3_0, &_call_ctor_QStyleOptionTabV3_0);
}

//  Constructor QStyleOptionTabV3::QStyleOptionTabV3(const QStyleOptionTabV3 &other)


static void _init_ctor_QStyleOptionTabV3_2972 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionTabV3 & > (argspec_0);
  decl->set_return_new<QStyleOptionTabV3 *> ();
}

static void _call_ctor_QStyleOptionTabV3_2972 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionTabV3 &arg1 = args.read<const QStyleOptionTabV3 & > ();
  ret.write<QStyleOptionTabV3 *> (new QStyleOptionTabV3 (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionTabV3_2972 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionTabV3::QStyleOptionTabV3(const QStyleOptionTabV3 &other)\nThis method creates an object of class QStyleOptionTabV3.", &_init_ctor_QStyleOptionTabV3_2972, &_call_ctor_QStyleOptionTabV3_2972);
}

//  Constructor QStyleOptionTabV3::QStyleOptionTabV3(const QStyleOptionTabV2 &other)


static void _init_ctor_QStyleOptionTabV3_2971 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionTabV2 & > (argspec_0);
  decl->set_return_new<QStyleOptionTabV3 *> ();
}

static void _call_ctor_QStyleOptionTabV3_2971 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionTabV2 &arg1 = args.read<const QStyleOptionTabV2 & > ();
  ret.write<QStyleOptionTabV3 *> (new QStyleOptionTabV3 (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionTabV3_2971 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionTabV3::QStyleOptionTabV3(const QStyleOptionTabV2 &other)\nThis method creates an object of class QStyleOptionTabV3.", &_init_ctor_QStyleOptionTabV3_2971, &_call_ctor_QStyleOptionTabV3_2971);
}

//  Constructor QStyleOptionTabV3::QStyleOptionTabV3(const QStyleOptionTab &other)


static void _init_ctor_QStyleOptionTabV3_2835 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionTab & > (argspec_0);
  decl->set_return_new<QStyleOptionTabV3 *> ();
}

static void _call_ctor_QStyleOptionTabV3_2835 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionTab &arg1 = args.read<const QStyleOptionTab & > ();
  ret.write<QStyleOptionTabV3 *> (new QStyleOptionTabV3 (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionTabV3_2835 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionTabV3::QStyleOptionTabV3(const QStyleOptionTab &other)\nThis method creates an object of class QStyleOptionTabV3.", &_init_ctor_QStyleOptionTabV3_2835, &_call_ctor_QStyleOptionTabV3_2835);
}

// QStyleOptionTabV3 &QStyleOptionTabV3::operator=(const QStyleOptionTab &other)


static void _init_f_operator_eq__2835 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionTab & > (argspec_0);
  decl->set_return<QStyleOptionTabV3 & > ();
}

static void _call_f_operator_eq__2835 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionTab &arg1 = args.read<const QStyleOptionTab & > ();
  ret.write<QStyleOptionTabV3 & > ((QStyleOptionTabV3 &)((QStyleOptionTabV3 *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__2835 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QStyleOptionTabV3 &QStyleOptionTabV3::operator=(const QStyleOptionTab &other)\n", false, &_init_f_operator_eq__2835, &_call_f_operator_eq__2835);
}


namespace gsi
{
extern gsi::Class<QStyleOptionTabV2> decl_QStyleOptionTabV2;

gsi::Class<QStyleOptionTabV3> decl_QStyleOptionTabV3 (decl_QStyleOptionTabV2, "QStyleOptionTabV3",
  gsi::Methods(_create_ctor_QStyleOptionTabV3_0 ()) +
  gsi::Methods(_create_ctor_QStyleOptionTabV3_2972 ()) +
  gsi::Methods(_create_ctor_QStyleOptionTabV3_2971 ()) +
  gsi::Methods(_create_ctor_QStyleOptionTabV3_2835 ()) +
  gsi::Methods(_create_f_operator_eq__2835 ()),
  "@qt\n@brief Binding of QStyleOptionTabV3");

}

