
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
*  @file gsiDeclQStyleOptionQ3ListViewItem.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQStyleOptionQ3ListViewItem_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QStyleOptionQ3ListViewItem

//  Constructor QStyleOptionQ3ListViewItem::QStyleOptionQ3ListViewItem()


static void _init_ctor_QStyleOptionQ3ListViewItem_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QStyleOptionQ3ListViewItem *> ();
}

static void _call_ctor_QStyleOptionQ3ListViewItem_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QStyleOptionQ3ListViewItem *> (new QStyleOptionQ3ListViewItem ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionQ3ListViewItem_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionQ3ListViewItem::QStyleOptionQ3ListViewItem()\nThis method creates an object of class QStyleOptionQ3ListViewItem.", &_init_ctor_QStyleOptionQ3ListViewItem_0, &_call_ctor_QStyleOptionQ3ListViewItem_0);
}

//  Constructor QStyleOptionQ3ListViewItem::QStyleOptionQ3ListViewItem(const QStyleOptionQ3ListViewItem &other)


static void _init_ctor_QStyleOptionQ3ListViewItem_3910 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionQ3ListViewItem & > (argspec_0);
  decl->set_return_new<QStyleOptionQ3ListViewItem *> ();
}

static void _call_ctor_QStyleOptionQ3ListViewItem_3910 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionQ3ListViewItem &arg1 = args.read<const QStyleOptionQ3ListViewItem & > ();
  ret.write<QStyleOptionQ3ListViewItem *> (new QStyleOptionQ3ListViewItem (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionQ3ListViewItem_3910 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionQ3ListViewItem::QStyleOptionQ3ListViewItem(const QStyleOptionQ3ListViewItem &other)\nThis method creates an object of class QStyleOptionQ3ListViewItem.", &_init_ctor_QStyleOptionQ3ListViewItem_3910, &_call_ctor_QStyleOptionQ3ListViewItem_3910);
}


namespace gsi
{
extern gsi::Class<QStyleOption> decl_QStyleOption;

gsi::Class<QStyleOptionQ3ListViewItem> decl_QStyleOptionQ3ListViewItem (decl_QStyleOption, "QStyleOptionQ3ListViewItem",
  gsi::Methods(_create_ctor_QStyleOptionQ3ListViewItem_0 ()) +
  gsi::Methods(_create_ctor_QStyleOptionQ3ListViewItem_3910 ()),
  "@qt\n@brief Binding of QStyleOptionQ3ListViewItem");

}

