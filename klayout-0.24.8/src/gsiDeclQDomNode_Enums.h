
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
*  @file gsiDeclQDomNode_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQDomNode_Enums
#define _HDR_gsiDeclQDomNode_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QDomNode::EncodingPolicy>
class QDomNode_EncodingPolicy_Enums : public QFlags<enum QDomNode::EncodingPolicy> {
public:
  QDomNode_EncodingPolicy_Enums () : m_flags () { }
  QDomNode_EncodingPolicy_Enums (enum QDomNode::EncodingPolicy v) : m_flags (v) { }
  QDomNode_EncodingPolicy_Enums (const QFlags<enum QDomNode::EncodingPolicy> &v) : m_flags (v) { }
  QFlags<enum QDomNode::EncodingPolicy> flags () const { return m_flags; }
private:
  QFlags<QDomNode::EncodingPolicy> m_flags;
};

//  Wrapper class for enum QDomNode::EncodingPolicy
class QDomNode_EncodingPolicy_Enum : public QDomNode_EncodingPolicy_Enums {
public:
  QDomNode_EncodingPolicy_Enum () { }
  QDomNode_EncodingPolicy_Enum (enum QDomNode::EncodingPolicy v) : QDomNode_EncodingPolicy_Enums (v) { }
  enum QDomNode::EncodingPolicy value () const { return (enum QDomNode::EncodingPolicy) flags ().operator int (); }
};

//  Converter for QFlags<enum QDomNode::EncodingPolicy>
template <>
struct Converter<QFlags<enum QDomNode::EncodingPolicy> >
{
public:
  typedef QFlags<enum QDomNode::EncodingPolicy> source_type;
  typedef QDomNode_EncodingPolicy_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QDomNode::EncodingPolicy
template <>
struct Converter<enum QDomNode::EncodingPolicy>
{
public:
  typedef enum QDomNode::EncodingPolicy source_type;
  typedef QDomNode_EncodingPolicy_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QDomNode::NodeType>
class QDomNode_NodeType_Enums : public QFlags<enum QDomNode::NodeType> {
public:
  QDomNode_NodeType_Enums () : m_flags () { }
  QDomNode_NodeType_Enums (enum QDomNode::NodeType v) : m_flags (v) { }
  QDomNode_NodeType_Enums (const QFlags<enum QDomNode::NodeType> &v) : m_flags (v) { }
  QFlags<enum QDomNode::NodeType> flags () const { return m_flags; }
private:
  QFlags<QDomNode::NodeType> m_flags;
};

//  Wrapper class for enum QDomNode::NodeType
class QDomNode_NodeType_Enum : public QDomNode_NodeType_Enums {
public:
  QDomNode_NodeType_Enum () { }
  QDomNode_NodeType_Enum (enum QDomNode::NodeType v) : QDomNode_NodeType_Enums (v) { }
  enum QDomNode::NodeType value () const { return (enum QDomNode::NodeType) flags ().operator int (); }
};

//  Converter for QFlags<enum QDomNode::NodeType>
template <>
struct Converter<QFlags<enum QDomNode::NodeType> >
{
public:
  typedef QFlags<enum QDomNode::NodeType> source_type;
  typedef QDomNode_NodeType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QDomNode::NodeType
template <>
struct Converter<enum QDomNode::NodeType>
{
public:
  typedef enum QDomNode::NodeType source_type;
  typedef QDomNode_NodeType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
