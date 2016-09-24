
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
*  @file gsiDeclQDomDocumentType.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtXml.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQDomDocumentType_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QDomDocumentType

//  Constructor QDomDocumentType::QDomDocumentType()


static void _init_ctor_QDomDocumentType_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QDomDocumentType *> ();
}

static void _call_ctor_QDomDocumentType_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QDomDocumentType *> (new QDomDocumentType ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QDomDocumentType_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QDomDocumentType::QDomDocumentType()\nThis method creates an object of class QDomDocumentType.", &_init_ctor_QDomDocumentType_0, &_call_ctor_QDomDocumentType_0);
}

//  Constructor QDomDocumentType::QDomDocumentType(const QDomDocumentType &x)


static void _init_ctor_QDomDocumentType_2931 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("x");
  decl->add_arg<const QDomDocumentType & > (argspec_0);
  decl->set_return_new<QDomDocumentType *> ();
}

static void _call_ctor_QDomDocumentType_2931 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QDomDocumentType &arg1 = args.read<const QDomDocumentType & > ();
  ret.write<QDomDocumentType *> (new QDomDocumentType (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QDomDocumentType_2931 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QDomDocumentType::QDomDocumentType(const QDomDocumentType &x)\nThis method creates an object of class QDomDocumentType.", &_init_ctor_QDomDocumentType_2931, &_call_ctor_QDomDocumentType_2931);
}

// QDomNamedNodeMap QDomDocumentType::entities()


static void _init_f_entities_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QDomNamedNodeMap > ();
}

static void _call_f_entities_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QDomNamedNodeMap > ((QDomNamedNodeMap)((QDomDocumentType *)cls)->entities ());
}

static qt_gsi::GenericMethod *_create_f_entities_c0 ()
{
  return new qt_gsi::GenericMethod ("entities", "@brief Method QDomNamedNodeMap QDomDocumentType::entities()\n", true, &_init_f_entities_c0, &_call_f_entities_c0);
}

// QString QDomDocumentType::internalSubset()


static void _init_f_internalSubset_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_internalSubset_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QDomDocumentType *)cls)->internalSubset ());
}

static qt_gsi::GenericMethod *_create_f_internalSubset_c0 ()
{
  return new qt_gsi::GenericMethod ("internalSubset", "@brief Method QString QDomDocumentType::internalSubset()\n", true, &_init_f_internalSubset_c0, &_call_f_internalSubset_c0);
}

// QString QDomDocumentType::name()


static void _init_f_name_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_name_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QDomDocumentType *)cls)->name ());
}

static qt_gsi::GenericMethod *_create_f_name_c0 ()
{
  return new qt_gsi::GenericMethod ("name", "@brief Method QString QDomDocumentType::name()\n", true, &_init_f_name_c0, &_call_f_name_c0);
}

// QDomNode::NodeType QDomDocumentType::nodeType()


static void _init_f_nodeType_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QDomNode::NodeType>::target_type > ();
}

static void _call_f_nodeType_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QDomNode::NodeType>::target_type > ((qt_gsi::Converter<QDomNode::NodeType>::target_type)qt_gsi::CppToQtAdaptor<QDomNode::NodeType>(((QDomDocumentType *)cls)->nodeType ()));
}

static qt_gsi::GenericMethod *_create_f_nodeType_c0 ()
{
  return new qt_gsi::GenericMethod ("nodeType", "@brief Method QDomNode::NodeType QDomDocumentType::nodeType()\n", true, &_init_f_nodeType_c0, &_call_f_nodeType_c0);
}

// QDomNamedNodeMap QDomDocumentType::notations()


static void _init_f_notations_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QDomNamedNodeMap > ();
}

static void _call_f_notations_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QDomNamedNodeMap > ((QDomNamedNodeMap)((QDomDocumentType *)cls)->notations ());
}

static qt_gsi::GenericMethod *_create_f_notations_c0 ()
{
  return new qt_gsi::GenericMethod ("notations", "@brief Method QDomNamedNodeMap QDomDocumentType::notations()\n", true, &_init_f_notations_c0, &_call_f_notations_c0);
}

// QDomDocumentType &QDomDocumentType::operator=(const QDomDocumentType &)


static void _init_f_operator_eq__2931 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<const QDomDocumentType & > (argspec_0);
  decl->set_return<QDomDocumentType & > ();
}

static void _call_f_operator_eq__2931 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QDomDocumentType &arg1 = args.read<const QDomDocumentType & > ();
  ret.write<QDomDocumentType & > ((QDomDocumentType &)((QDomDocumentType *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__2931 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QDomDocumentType &QDomDocumentType::operator=(const QDomDocumentType &)\n", false, &_init_f_operator_eq__2931, &_call_f_operator_eq__2931);
}

// QString QDomDocumentType::publicId()


static void _init_f_publicId_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_publicId_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QDomDocumentType *)cls)->publicId ());
}

static qt_gsi::GenericMethod *_create_f_publicId_c0 ()
{
  return new qt_gsi::GenericMethod ("publicId", "@brief Method QString QDomDocumentType::publicId()\n", true, &_init_f_publicId_c0, &_call_f_publicId_c0);
}

// QString QDomDocumentType::systemId()


static void _init_f_systemId_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_systemId_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QDomDocumentType *)cls)->systemId ());
}

static qt_gsi::GenericMethod *_create_f_systemId_c0 ()
{
  return new qt_gsi::GenericMethod ("systemId", "@brief Method QString QDomDocumentType::systemId()\n", true, &_init_f_systemId_c0, &_call_f_systemId_c0);
}


namespace gsi
{
extern gsi::Class<QDomNode> decl_QDomNode;

gsi::Class<QDomDocumentType> decl_QDomDocumentType (decl_QDomNode, "QDomDocumentType",
  gsi::Methods(_create_ctor_QDomDocumentType_0 ()) +
  gsi::Methods(_create_ctor_QDomDocumentType_2931 ()) +
  gsi::Methods(_create_f_entities_c0 ()) +
  gsi::Methods(_create_f_internalSubset_c0 ()) +
  gsi::Methods(_create_f_name_c0 ()) +
  gsi::Methods(_create_f_nodeType_c0 ()) +
  gsi::Methods(_create_f_notations_c0 ()) +
  gsi::Methods(_create_f_operator_eq__2931 ()) +
  gsi::Methods(_create_f_publicId_c0 ()) +
  gsi::Methods(_create_f_systemId_c0 ()),
  "@qt\n@brief Binding of QDomDocumentType");

}
