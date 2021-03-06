
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
*  @file gsiDeclQFileInfo_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQFileInfo_Enums
#define _HDR_gsiDeclQFileInfo_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QFile::Permission>
class QFile_Permission_Enums : public QFlags<enum QFile::Permission> {
public:
  QFile_Permission_Enums () : m_flags () { }
  QFile_Permission_Enums (enum QFile::Permission v) : m_flags (v) { }
  QFile_Permission_Enums (const QFlags<enum QFile::Permission> &v) : m_flags (v) { }
  QFlags<enum QFile::Permission> flags () const { return m_flags; }
private:
  QFlags<QFile::Permission> m_flags;
};

//  Wrapper class for enum QFile::Permission
class QFile_Permission_Enum : public QFile_Permission_Enums {
public:
  QFile_Permission_Enum () { }
  QFile_Permission_Enum (enum QFile::Permission v) : QFile_Permission_Enums (v) { }
  enum QFile::Permission value () const { return (enum QFile::Permission) flags ().operator int (); }
};

//  Converter for QFlags<enum QFile::Permission>
template <>
struct Converter<QFlags<enum QFile::Permission> >
{
public:
  typedef QFlags<enum QFile::Permission> source_type;
  typedef QFile_Permission_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QFile::Permission
template <>
struct Converter<enum QFile::Permission>
{
public:
  typedef enum QFile::Permission source_type;
  typedef QFile_Permission_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
