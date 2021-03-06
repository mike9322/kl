
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
*  @file gsiDeclQDomDocumentFragment.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtXml.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQDomDocumentFragment_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QDomDocumentFragment

//  Constructor QDomDocumentFragment::QDomDocumentFragment()


static void _init_ctor_QDomDocumentFragment_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QDomDocumentFragment *> ();
}

static void _call_ctor_QDomDocumentFragment_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QDomDocumentFragment *> (new QDomDocumentFragment ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QDomDocumentFragment_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QDomDocumentFragment::QDomDocumentFragment()\nThis method creates an object of class QDomDocumentFragment.", &_init_ctor_QDomDocumentFragment_0, &_call_ctor_QDomDocumentFragment_0);
}

//  Constructor QDomDocumentFragment::QDomDocumentFragment(const QDomDocumentFragment &x)


static void _init_ctor_QDomDocumentFragment_3333 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("x");
  decl->add_arg<const QDomDocumentFragment & > (argspec_0);
  decl->set_return_new<QDomDocumentFragment *> ();
}

static void _call_ctor_QDomDocumentFragment_3333 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QDomDocumentFragment &arg1 = args.read<const QDomDocumentFragment & > ();
  ret.write<QDomDocumentFragment *> (new QDomDocumentFragment (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QDomDocumentFragment_3333 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QDomDocumentFragment::QDomDocumentFragment(const QDomDocumentFragment &x)\nThis method creates an object of class QDomDocumentFragment.", &_init_ctor_QDomDocumentFragment_3333, &_call_ctor_QDomDocumentFragment_3333);
}

// QDomNode::NodeType QDomDocumentFragment::nodeType()


static void _init_f_nodeType_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QDomNode::NodeType>::target_type > ();
}

static void _call_f_nodeType_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QDomNode::NodeType>::target_type > ((qt_gsi::Converter<QDomNode::NodeType>::target_type)qt_gsi::CppToQtAdaptor<QDomNode::NodeType>(((QDomDocumentFragment *)cls)->nodeType ()));
}

static qt_gsi::GenericMethod *_create_f_nodeType_c0 ()
{
  return new qt_gsi::GenericMethod ("nodeType", "@brief Method QDomNode::NodeType QDomDocumentFragment::nodeType()\n", true, &_init_f_nodeType_c0, &_call_f_nodeType_c0);
}

// QDomDocumentFragment &QDomDocumentFragment::operator=(const QDomDocumentFragment &)


static void _init_f_operator_eq__3333 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<const QDomDocumentFragment & > (argspec_0);
  decl->set_return<QDomDocumentFragment & > ();
}

static void _call_f_operator_eq__3333 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QDomDocumentFragment &arg1 = args.read<const QDomDocumentFragment & > ();
  ret.write<QDomDocumentFragment & > ((QDomDocumentFragment &)((QDomDocumentFragment *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__3333 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QDomDocumentFragment &QDomDocumentFragment::operator=(const QDomDocumentFragment &)\n", false, &_init_f_operator_eq__3333, &_call_f_operator_eq__3333);
}


namespace gsi
{
extern gsi::Class<QDomNode> decl_QDomNode;

gsi::Class<QDomDocumentFragment> decl_QDomDocumentFragment (decl_QDomNode, "QDomDocumentFragment",
  gsi::Methods(_create_ctor_QDomDocumentFragment_0 ()) +
  gsi::Methods(_create_ctor_QDomDocumentFragment_3333 ()) +
  gsi::Methods(_create_f_nodeType_c0 ()) +
  gsi::Methods(_create_f_operator_eq__3333 ()),
  "@qt\n@brief Binding of QDomDocumentFragment");

}

