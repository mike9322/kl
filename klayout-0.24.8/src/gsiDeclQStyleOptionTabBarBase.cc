
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
*  @file gsiDeclQStyleOptionTabBarBase.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQStyleOptionTabBarBase_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QStyleOptionTabBarBase

//  Constructor QStyleOptionTabBarBase::QStyleOptionTabBarBase()


static void _init_ctor_QStyleOptionTabBarBase_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QStyleOptionTabBarBase *> ();
}

static void _call_ctor_QStyleOptionTabBarBase_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QStyleOptionTabBarBase *> (new QStyleOptionTabBarBase ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionTabBarBase_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionTabBarBase::QStyleOptionTabBarBase()\nThis method creates an object of class QStyleOptionTabBarBase.", &_init_ctor_QStyleOptionTabBarBase_0, &_call_ctor_QStyleOptionTabBarBase_0);
}

//  Constructor QStyleOptionTabBarBase::QStyleOptionTabBarBase(const QStyleOptionTabBarBase &other)


static void _init_ctor_QStyleOptionTabBarBase_3491 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionTabBarBase & > (argspec_0);
  decl->set_return_new<QStyleOptionTabBarBase *> ();
}

static void _call_ctor_QStyleOptionTabBarBase_3491 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionTabBarBase &arg1 = args.read<const QStyleOptionTabBarBase & > ();
  ret.write<QStyleOptionTabBarBase *> (new QStyleOptionTabBarBase (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionTabBarBase_3491 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionTabBarBase::QStyleOptionTabBarBase(const QStyleOptionTabBarBase &other)\nThis method creates an object of class QStyleOptionTabBarBase.", &_init_ctor_QStyleOptionTabBarBase_3491, &_call_ctor_QStyleOptionTabBarBase_3491);
}


namespace gsi
{
extern gsi::Class<QStyleOption> decl_QStyleOption;

gsi::Class<QStyleOptionTabBarBase> decl_QStyleOptionTabBarBase (decl_QStyleOption, "QStyleOptionTabBarBase",
  gsi::Methods(_create_ctor_QStyleOptionTabBarBase_0 ()) +
  gsi::Methods(_create_ctor_QStyleOptionTabBarBase_3491 ()),
  "@qt\n@brief Binding of QStyleOptionTabBarBase");

}

