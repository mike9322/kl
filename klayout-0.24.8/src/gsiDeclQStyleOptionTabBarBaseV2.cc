
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
*  @file gsiDeclQStyleOptionTabBarBaseV2.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQStyleOptionTabBarBaseV2_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QStyleOptionTabBarBaseV2

//  Constructor QStyleOptionTabBarBaseV2::QStyleOptionTabBarBaseV2()


static void _init_ctor_QStyleOptionTabBarBaseV2_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QStyleOptionTabBarBaseV2 *> ();
}

static void _call_ctor_QStyleOptionTabBarBaseV2_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QStyleOptionTabBarBaseV2 *> (new QStyleOptionTabBarBaseV2 ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionTabBarBaseV2_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionTabBarBaseV2::QStyleOptionTabBarBaseV2()\nThis method creates an object of class QStyleOptionTabBarBaseV2.", &_init_ctor_QStyleOptionTabBarBaseV2_0, &_call_ctor_QStyleOptionTabBarBaseV2_0);
}

//  Constructor QStyleOptionTabBarBaseV2::QStyleOptionTabBarBaseV2(const QStyleOptionTabBarBaseV2 &other)


static void _init_ctor_QStyleOptionTabBarBaseV2_3627 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionTabBarBaseV2 & > (argspec_0);
  decl->set_return_new<QStyleOptionTabBarBaseV2 *> ();
}

static void _call_ctor_QStyleOptionTabBarBaseV2_3627 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionTabBarBaseV2 &arg1 = args.read<const QStyleOptionTabBarBaseV2 & > ();
  ret.write<QStyleOptionTabBarBaseV2 *> (new QStyleOptionTabBarBaseV2 (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionTabBarBaseV2_3627 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionTabBarBaseV2::QStyleOptionTabBarBaseV2(const QStyleOptionTabBarBaseV2 &other)\nThis method creates an object of class QStyleOptionTabBarBaseV2.", &_init_ctor_QStyleOptionTabBarBaseV2_3627, &_call_ctor_QStyleOptionTabBarBaseV2_3627);
}

//  Constructor QStyleOptionTabBarBaseV2::QStyleOptionTabBarBaseV2(const QStyleOptionTabBarBase &other)


static void _init_ctor_QStyleOptionTabBarBaseV2_3491 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionTabBarBase & > (argspec_0);
  decl->set_return_new<QStyleOptionTabBarBaseV2 *> ();
}

static void _call_ctor_QStyleOptionTabBarBaseV2_3491 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionTabBarBase &arg1 = args.read<const QStyleOptionTabBarBase & > ();
  ret.write<QStyleOptionTabBarBaseV2 *> (new QStyleOptionTabBarBaseV2 (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionTabBarBaseV2_3491 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionTabBarBaseV2::QStyleOptionTabBarBaseV2(const QStyleOptionTabBarBase &other)\nThis method creates an object of class QStyleOptionTabBarBaseV2.", &_init_ctor_QStyleOptionTabBarBaseV2_3491, &_call_ctor_QStyleOptionTabBarBaseV2_3491);
}

// QStyleOptionTabBarBaseV2 &QStyleOptionTabBarBaseV2::operator=(const QStyleOptionTabBarBase &other)


static void _init_f_operator_eq__3491 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionTabBarBase & > (argspec_0);
  decl->set_return<QStyleOptionTabBarBaseV2 & > ();
}

static void _call_f_operator_eq__3491 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionTabBarBase &arg1 = args.read<const QStyleOptionTabBarBase & > ();
  ret.write<QStyleOptionTabBarBaseV2 & > ((QStyleOptionTabBarBaseV2 &)((QStyleOptionTabBarBaseV2 *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__3491 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QStyleOptionTabBarBaseV2 &QStyleOptionTabBarBaseV2::operator=(const QStyleOptionTabBarBase &other)\n", false, &_init_f_operator_eq__3491, &_call_f_operator_eq__3491);
}


namespace gsi
{
extern gsi::Class<QStyleOptionTabBarBase> decl_QStyleOptionTabBarBase;

gsi::Class<QStyleOptionTabBarBaseV2> decl_QStyleOptionTabBarBaseV2 (decl_QStyleOptionTabBarBase, "QStyleOptionTabBarBaseV2",
  gsi::Methods(_create_ctor_QStyleOptionTabBarBaseV2_0 ()) +
  gsi::Methods(_create_ctor_QStyleOptionTabBarBaseV2_3627 ()) +
  gsi::Methods(_create_ctor_QStyleOptionTabBarBaseV2_3491 ()) +
  gsi::Methods(_create_f_operator_eq__3491 ()),
  "@qt\n@brief Binding of QStyleOptionTabBarBaseV2");

}

