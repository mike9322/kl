
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
*  @file gsiDeclQPluginLoader_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQPluginLoader_Enums
#define _HDR_gsiDeclQPluginLoader_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QLibrary::LoadHint>
class QLibrary_LoadHint_Enums : public QFlags<enum QLibrary::LoadHint> {
public:
  QLibrary_LoadHint_Enums () : m_flags () { }
  QLibrary_LoadHint_Enums (enum QLibrary::LoadHint v) : m_flags (v) { }
  QLibrary_LoadHint_Enums (const QFlags<enum QLibrary::LoadHint> &v) : m_flags (v) { }
  QFlags<enum QLibrary::LoadHint> flags () const { return m_flags; }
private:
  QFlags<QLibrary::LoadHint> m_flags;
};

//  Wrapper class for enum QLibrary::LoadHint
class QLibrary_LoadHint_Enum : public QLibrary_LoadHint_Enums {
public:
  QLibrary_LoadHint_Enum () { }
  QLibrary_LoadHint_Enum (enum QLibrary::LoadHint v) : QLibrary_LoadHint_Enums (v) { }
  enum QLibrary::LoadHint value () const { return (enum QLibrary::LoadHint) flags ().operator int (); }
};

//  Converter for QFlags<enum QLibrary::LoadHint>
template <>
struct Converter<QFlags<enum QLibrary::LoadHint> >
{
public:
  typedef QFlags<enum QLibrary::LoadHint> source_type;
  typedef QLibrary_LoadHint_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QLibrary::LoadHint
template <>
struct Converter<enum QLibrary::LoadHint>
{
public:
  typedef enum QLibrary::LoadHint source_type;
  typedef QLibrary_LoadHint_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::ConnectionType>
class Qt_ConnectionType_Enums : public QFlags<enum Qt::ConnectionType> {
public:
  Qt_ConnectionType_Enums () : m_flags () { }
  Qt_ConnectionType_Enums (enum Qt::ConnectionType v) : m_flags (v) { }
  Qt_ConnectionType_Enums (const QFlags<enum Qt::ConnectionType> &v) : m_flags (v) { }
  QFlags<enum Qt::ConnectionType> flags () const { return m_flags; }
private:
  QFlags<Qt::ConnectionType> m_flags;
};

//  Wrapper class for enum Qt::ConnectionType
class Qt_ConnectionType_Enum : public Qt_ConnectionType_Enums {
public:
  Qt_ConnectionType_Enum () { }
  Qt_ConnectionType_Enum (enum Qt::ConnectionType v) : Qt_ConnectionType_Enums (v) { }
  enum Qt::ConnectionType value () const { return (enum Qt::ConnectionType) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::ConnectionType>
template <>
struct Converter<QFlags<enum Qt::ConnectionType> >
{
public:
  typedef QFlags<enum Qt::ConnectionType> source_type;
  typedef Qt_ConnectionType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::ConnectionType
template <>
struct Converter<enum Qt::ConnectionType>
{
public:
  typedef enum Qt::ConnectionType source_type;
  typedef Qt_ConnectionType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
