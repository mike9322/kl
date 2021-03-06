
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
*  @file gsiDeclQStyleOptionProgressBar.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQStyleOptionProgressBar_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QStyleOptionProgressBar

//  Constructor QStyleOptionProgressBar::QStyleOptionProgressBar()


static void _init_ctor_QStyleOptionProgressBar_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QStyleOptionProgressBar *> ();
}

static void _call_ctor_QStyleOptionProgressBar_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QStyleOptionProgressBar *> (new QStyleOptionProgressBar ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionProgressBar_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionProgressBar::QStyleOptionProgressBar()\nThis method creates an object of class QStyleOptionProgressBar.", &_init_ctor_QStyleOptionProgressBar_0, &_call_ctor_QStyleOptionProgressBar_0);
}

//  Constructor QStyleOptionProgressBar::QStyleOptionProgressBar(const QStyleOptionProgressBar &other)


static void _init_ctor_QStyleOptionProgressBar_3686 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStyleOptionProgressBar & > (argspec_0);
  decl->set_return_new<QStyleOptionProgressBar *> ();
}

static void _call_ctor_QStyleOptionProgressBar_3686 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStyleOptionProgressBar &arg1 = args.read<const QStyleOptionProgressBar & > ();
  ret.write<QStyleOptionProgressBar *> (new QStyleOptionProgressBar (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStyleOptionProgressBar_3686 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStyleOptionProgressBar::QStyleOptionProgressBar(const QStyleOptionProgressBar &other)\nThis method creates an object of class QStyleOptionProgressBar.", &_init_ctor_QStyleOptionProgressBar_3686, &_call_ctor_QStyleOptionProgressBar_3686);
}


namespace gsi
{
extern gsi::Class<QStyleOption> decl_QStyleOption;

gsi::Class<QStyleOptionProgressBar> decl_QStyleOptionProgressBar (decl_QStyleOption, "QStyleOptionProgressBar",
  gsi::Methods(_create_ctor_QStyleOptionProgressBar_0 ()) +
  gsi::Methods(_create_ctor_QStyleOptionProgressBar_3686 ()),
  "@qt\n@brief Binding of QStyleOptionProgressBar");

}

