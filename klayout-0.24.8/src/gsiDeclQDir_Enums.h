
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
*  @file gsiDeclQDir_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQDir_Enums
#define _HDR_gsiDeclQDir_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QDir::Filter>
class QDir_Filter_Enums : public QFlags<enum QDir::Filter> {
public:
  QDir_Filter_Enums () : m_flags () { }
  QDir_Filter_Enums (enum QDir::Filter v) : m_flags (v) { }
  QDir_Filter_Enums (const QFlags<enum QDir::Filter> &v) : m_flags (v) { }
  QFlags<enum QDir::Filter> flags () const { return m_flags; }
private:
  QFlags<QDir::Filter> m_flags;
};

//  Wrapper class for enum QDir::Filter
class QDir_Filter_Enum : public QDir_Filter_Enums {
public:
  QDir_Filter_Enum () { }
  QDir_Filter_Enum (enum QDir::Filter v) : QDir_Filter_Enums (v) { }
  enum QDir::Filter value () const { return (enum QDir::Filter) flags ().operator int (); }
};

//  Converter for QFlags<enum QDir::Filter>
template <>
struct Converter<QFlags<enum QDir::Filter> >
{
public:
  typedef QFlags<enum QDir::Filter> source_type;
  typedef QDir_Filter_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QDir::Filter
template <>
struct Converter<enum QDir::Filter>
{
public:
  typedef enum QDir::Filter source_type;
  typedef QDir_Filter_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QDir::SortFlag>
class QDir_SortFlag_Enums : public QFlags<enum QDir::SortFlag> {
public:
  QDir_SortFlag_Enums () : m_flags () { }
  QDir_SortFlag_Enums (enum QDir::SortFlag v) : m_flags (v) { }
  QDir_SortFlag_Enums (const QFlags<enum QDir::SortFlag> &v) : m_flags (v) { }
  QFlags<enum QDir::SortFlag> flags () const { return m_flags; }
private:
  QFlags<QDir::SortFlag> m_flags;
};

//  Wrapper class for enum QDir::SortFlag
class QDir_SortFlag_Enum : public QDir_SortFlag_Enums {
public:
  QDir_SortFlag_Enum () { }
  QDir_SortFlag_Enum (enum QDir::SortFlag v) : QDir_SortFlag_Enums (v) { }
  enum QDir::SortFlag value () const { return (enum QDir::SortFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum QDir::SortFlag>
template <>
struct Converter<QFlags<enum QDir::SortFlag> >
{
public:
  typedef QFlags<enum QDir::SortFlag> source_type;
  typedef QDir_SortFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QDir::SortFlag
template <>
struct Converter<enum QDir::SortFlag>
{
public:
  typedef enum QDir::SortFlag source_type;
  typedef QDir_SortFlag_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif