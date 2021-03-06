
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
*  @file gsiDeclQMetaMethod_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQMetaMethod_Enums
#define _HDR_gsiDeclQMetaMethod_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QMetaMethod::Access>
class QMetaMethod_Access_Enums : public QFlags<enum QMetaMethod::Access> {
public:
  QMetaMethod_Access_Enums () : m_flags () { }
  QMetaMethod_Access_Enums (enum QMetaMethod::Access v) : m_flags (v) { }
  QMetaMethod_Access_Enums (const QFlags<enum QMetaMethod::Access> &v) : m_flags (v) { }
  QFlags<enum QMetaMethod::Access> flags () const { return m_flags; }
private:
  QFlags<QMetaMethod::Access> m_flags;
};

//  Wrapper class for enum QMetaMethod::Access
class QMetaMethod_Access_Enum : public QMetaMethod_Access_Enums {
public:
  QMetaMethod_Access_Enum () { }
  QMetaMethod_Access_Enum (enum QMetaMethod::Access v) : QMetaMethod_Access_Enums (v) { }
  enum QMetaMethod::Access value () const { return (enum QMetaMethod::Access) flags ().operator int (); }
};

//  Converter for QFlags<enum QMetaMethod::Access>
template <>
struct Converter<QFlags<enum QMetaMethod::Access> >
{
public:
  typedef QFlags<enum QMetaMethod::Access> source_type;
  typedef QMetaMethod_Access_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QMetaMethod::Access
template <>
struct Converter<enum QMetaMethod::Access>
{
public:
  typedef enum QMetaMethod::Access source_type;
  typedef QMetaMethod_Access_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QMetaMethod::MethodType>
class QMetaMethod_MethodType_Enums : public QFlags<enum QMetaMethod::MethodType> {
public:
  QMetaMethod_MethodType_Enums () : m_flags () { }
  QMetaMethod_MethodType_Enums (enum QMetaMethod::MethodType v) : m_flags (v) { }
  QMetaMethod_MethodType_Enums (const QFlags<enum QMetaMethod::MethodType> &v) : m_flags (v) { }
  QFlags<enum QMetaMethod::MethodType> flags () const { return m_flags; }
private:
  QFlags<QMetaMethod::MethodType> m_flags;
};

//  Wrapper class for enum QMetaMethod::MethodType
class QMetaMethod_MethodType_Enum : public QMetaMethod_MethodType_Enums {
public:
  QMetaMethod_MethodType_Enum () { }
  QMetaMethod_MethodType_Enum (enum QMetaMethod::MethodType v) : QMetaMethod_MethodType_Enums (v) { }
  enum QMetaMethod::MethodType value () const { return (enum QMetaMethod::MethodType) flags ().operator int (); }
};

//  Converter for QFlags<enum QMetaMethod::MethodType>
template <>
struct Converter<QFlags<enum QMetaMethod::MethodType> >
{
public:
  typedef QFlags<enum QMetaMethod::MethodType> source_type;
  typedef QMetaMethod_MethodType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QMetaMethod::MethodType
template <>
struct Converter<enum QMetaMethod::MethodType>
{
public:
  typedef enum QMetaMethod::MethodType source_type;
  typedef QMetaMethod_MethodType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
