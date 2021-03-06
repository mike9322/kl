
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
*  @file gsiDeclQDomEntityReference.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtXml.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQDomEntityReference_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QDomEntityReference

//  Constructor QDomEntityReference::QDomEntityReference()


static void _init_ctor_QDomEntityReference_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QDomEntityReference *> ();
}

static void _call_ctor_QDomEntityReference_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QDomEntityReference *> (new QDomEntityReference ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QDomEntityReference_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QDomEntityReference::QDomEntityReference()\nThis method creates an object of class QDomEntityReference.", &_init_ctor_QDomEntityReference_0, &_call_ctor_QDomEntityReference_0);
}

//  Constructor QDomEntityReference::QDomEntityReference(const QDomEntityReference &x)


static void _init_ctor_QDomEntityReference_3230 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("x");
  decl->add_arg<const QDomEntityReference & > (argspec_0);
  decl->set_return_new<QDomEntityReference *> ();
}

static void _call_ctor_QDomEntityReference_3230 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QDomEntityReference &arg1 = args.read<const QDomEntityReference & > ();
  ret.write<QDomEntityReference *> (new QDomEntityReference (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QDomEntityReference_3230 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QDomEntityReference::QDomEntityReference(const QDomEntityReference &x)\nThis method creates an object of class QDomEntityReference.", &_init_ctor_QDomEntityReference_3230, &_call_ctor_QDomEntityReference_3230);
}

// QDomNode::NodeType QDomEntityReference::nodeType()


static void _init_f_nodeType_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QDomNode::NodeType>::target_type > ();
}

static void _call_f_nodeType_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QDomNode::NodeType>::target_type > ((qt_gsi::Converter<QDomNode::NodeType>::target_type)qt_gsi::CppToQtAdaptor<QDomNode::NodeType>(((QDomEntityReference *)cls)->nodeType ()));
}

static qt_gsi::GenericMethod *_create_f_nodeType_c0 ()
{
  return new qt_gsi::GenericMethod ("nodeType", "@brief Method QDomNode::NodeType QDomEntityReference::nodeType()\n", true, &_init_f_nodeType_c0, &_call_f_nodeType_c0);
}

// QDomEntityReference &QDomEntityReference::operator=(const QDomEntityReference &)


static void _init_f_operator_eq__3230 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<const QDomEntityReference & > (argspec_0);
  decl->set_return<QDomEntityReference & > ();
}

static void _call_f_operator_eq__3230 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QDomEntityReference &arg1 = args.read<const QDomEntityReference & > ();
  ret.write<QDomEntityReference & > ((QDomEntityReference &)((QDomEntityReference *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__3230 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QDomEntityReference &QDomEntityReference::operator=(const QDomEntityReference &)\n", false, &_init_f_operator_eq__3230, &_call_f_operator_eq__3230);
}


namespace gsi
{
extern gsi::Class<QDomNode> decl_QDomNode;

gsi::Class<QDomEntityReference> decl_QDomEntityReference (decl_QDomNode, "QDomEntityReference",
  gsi::Methods(_create_ctor_QDomEntityReference_0 ()) +
  gsi::Methods(_create_ctor_QDomEntityReference_3230 ()) +
  gsi::Methods(_create_f_nodeType_c0 ()) +
  gsi::Methods(_create_f_operator_eq__3230 ()),
  "@qt\n@brief Binding of QDomEntityReference");

}

