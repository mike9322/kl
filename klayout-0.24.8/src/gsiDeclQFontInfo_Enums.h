
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
*  @file gsiDeclQFontInfo_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQFontInfo_Enums
#define _HDR_gsiDeclQFontInfo_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QFont::Style>
class QFont_Style_Enums : public QFlags<enum QFont::Style> {
public:
  QFont_Style_Enums () : m_flags () { }
  QFont_Style_Enums (enum QFont::Style v) : m_flags (v) { }
  QFont_Style_Enums (const QFlags<enum QFont::Style> &v) : m_flags (v) { }
  QFlags<enum QFont::Style> flags () const { return m_flags; }
private:
  QFlags<QFont::Style> m_flags;
};

//  Wrapper class for enum QFont::Style
class QFont_Style_Enum : public QFont_Style_Enums {
public:
  QFont_Style_Enum () { }
  QFont_Style_Enum (enum QFont::Style v) : QFont_Style_Enums (v) { }
  enum QFont::Style value () const { return (enum QFont::Style) flags ().operator int (); }
};

//  Converter for QFlags<enum QFont::Style>
template <>
struct Converter<QFlags<enum QFont::Style> >
{
public:
  typedef QFlags<enum QFont::Style> source_type;
  typedef QFont_Style_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QFont::Style
template <>
struct Converter<enum QFont::Style>
{
public:
  typedef enum QFont::Style source_type;
  typedef QFont_Style_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QFont::StyleHint>
class QFont_StyleHint_Enums : public QFlags<enum QFont::StyleHint> {
public:
  QFont_StyleHint_Enums () : m_flags () { }
  QFont_StyleHint_Enums (enum QFont::StyleHint v) : m_flags (v) { }
  QFont_StyleHint_Enums (const QFlags<enum QFont::StyleHint> &v) : m_flags (v) { }
  QFlags<enum QFont::StyleHint> flags () const { return m_flags; }
private:
  QFlags<QFont::StyleHint> m_flags;
};

//  Wrapper class for enum QFont::StyleHint
class QFont_StyleHint_Enum : public QFont_StyleHint_Enums {
public:
  QFont_StyleHint_Enum () { }
  QFont_StyleHint_Enum (enum QFont::StyleHint v) : QFont_StyleHint_Enums (v) { }
  enum QFont::StyleHint value () const { return (enum QFont::StyleHint) flags ().operator int (); }
};

//  Converter for QFlags<enum QFont::StyleHint>
template <>
struct Converter<QFlags<enum QFont::StyleHint> >
{
public:
  typedef QFlags<enum QFont::StyleHint> source_type;
  typedef QFont_StyleHint_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QFont::StyleHint
template <>
struct Converter<enum QFont::StyleHint>
{
public:
  typedef enum QFont::StyleHint source_type;
  typedef QFont_StyleHint_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
