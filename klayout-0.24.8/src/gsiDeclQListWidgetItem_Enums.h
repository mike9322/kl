
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
*  @file gsiDeclQListWidgetItem_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQListWidgetItem_Enums
#define _HDR_gsiDeclQListWidgetItem_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum Qt::CheckState>
class Qt_CheckState_Enums : public QFlags<enum Qt::CheckState> {
public:
  Qt_CheckState_Enums () : m_flags () { }
  Qt_CheckState_Enums (enum Qt::CheckState v) : m_flags (v) { }
  Qt_CheckState_Enums (const QFlags<enum Qt::CheckState> &v) : m_flags (v) { }
  QFlags<enum Qt::CheckState> flags () const { return m_flags; }
private:
  QFlags<Qt::CheckState> m_flags;
};

//  Wrapper class for enum Qt::CheckState
class Qt_CheckState_Enum : public Qt_CheckState_Enums {
public:
  Qt_CheckState_Enum () { }
  Qt_CheckState_Enum (enum Qt::CheckState v) : Qt_CheckState_Enums (v) { }
  enum Qt::CheckState value () const { return (enum Qt::CheckState) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::CheckState>
template <>
struct Converter<QFlags<enum Qt::CheckState> >
{
public:
  typedef QFlags<enum Qt::CheckState> source_type;
  typedef Qt_CheckState_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::CheckState
template <>
struct Converter<enum Qt::CheckState>
{
public:
  typedef enum Qt::CheckState source_type;
  typedef Qt_CheckState_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::ItemFlag>
class Qt_ItemFlag_Enums : public QFlags<enum Qt::ItemFlag> {
public:
  Qt_ItemFlag_Enums () : m_flags () { }
  Qt_ItemFlag_Enums (enum Qt::ItemFlag v) : m_flags (v) { }
  Qt_ItemFlag_Enums (const QFlags<enum Qt::ItemFlag> &v) : m_flags (v) { }
  QFlags<enum Qt::ItemFlag> flags () const { return m_flags; }
private:
  QFlags<Qt::ItemFlag> m_flags;
};

//  Wrapper class for enum Qt::ItemFlag
class Qt_ItemFlag_Enum : public Qt_ItemFlag_Enums {
public:
  Qt_ItemFlag_Enum () { }
  Qt_ItemFlag_Enum (enum Qt::ItemFlag v) : Qt_ItemFlag_Enums (v) { }
  enum Qt::ItemFlag value () const { return (enum Qt::ItemFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::ItemFlag>
template <>
struct Converter<QFlags<enum Qt::ItemFlag> >
{
public:
  typedef QFlags<enum Qt::ItemFlag> source_type;
  typedef Qt_ItemFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::ItemFlag
template <>
struct Converter<enum Qt::ItemFlag>
{
public:
  typedef enum Qt::ItemFlag source_type;
  typedef Qt_ItemFlag_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
