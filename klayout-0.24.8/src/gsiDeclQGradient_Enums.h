
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
*  @file gsiDeclQGradient_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQGradient_Enums
#define _HDR_gsiDeclQGradient_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QGradient::CoordinateMode>
class QGradient_CoordinateMode_Enums : public QFlags<enum QGradient::CoordinateMode> {
public:
  QGradient_CoordinateMode_Enums () : m_flags () { }
  QGradient_CoordinateMode_Enums (enum QGradient::CoordinateMode v) : m_flags (v) { }
  QGradient_CoordinateMode_Enums (const QFlags<enum QGradient::CoordinateMode> &v) : m_flags (v) { }
  QFlags<enum QGradient::CoordinateMode> flags () const { return m_flags; }
private:
  QFlags<QGradient::CoordinateMode> m_flags;
};

//  Wrapper class for enum QGradient::CoordinateMode
class QGradient_CoordinateMode_Enum : public QGradient_CoordinateMode_Enums {
public:
  QGradient_CoordinateMode_Enum () { }
  QGradient_CoordinateMode_Enum (enum QGradient::CoordinateMode v) : QGradient_CoordinateMode_Enums (v) { }
  enum QGradient::CoordinateMode value () const { return (enum QGradient::CoordinateMode) flags ().operator int (); }
};

//  Converter for QFlags<enum QGradient::CoordinateMode>
template <>
struct Converter<QFlags<enum QGradient::CoordinateMode> >
{
public:
  typedef QFlags<enum QGradient::CoordinateMode> source_type;
  typedef QGradient_CoordinateMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QGradient::CoordinateMode
template <>
struct Converter<enum QGradient::CoordinateMode>
{
public:
  typedef enum QGradient::CoordinateMode source_type;
  typedef QGradient_CoordinateMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QGradient::InterpolationMode>
class QGradient_InterpolationMode_Enums : public QFlags<enum QGradient::InterpolationMode> {
public:
  QGradient_InterpolationMode_Enums () : m_flags () { }
  QGradient_InterpolationMode_Enums (enum QGradient::InterpolationMode v) : m_flags (v) { }
  QGradient_InterpolationMode_Enums (const QFlags<enum QGradient::InterpolationMode> &v) : m_flags (v) { }
  QFlags<enum QGradient::InterpolationMode> flags () const { return m_flags; }
private:
  QFlags<QGradient::InterpolationMode> m_flags;
};

//  Wrapper class for enum QGradient::InterpolationMode
class QGradient_InterpolationMode_Enum : public QGradient_InterpolationMode_Enums {
public:
  QGradient_InterpolationMode_Enum () { }
  QGradient_InterpolationMode_Enum (enum QGradient::InterpolationMode v) : QGradient_InterpolationMode_Enums (v) { }
  enum QGradient::InterpolationMode value () const { return (enum QGradient::InterpolationMode) flags ().operator int (); }
};

//  Converter for QFlags<enum QGradient::InterpolationMode>
template <>
struct Converter<QFlags<enum QGradient::InterpolationMode> >
{
public:
  typedef QFlags<enum QGradient::InterpolationMode> source_type;
  typedef QGradient_InterpolationMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QGradient::InterpolationMode
template <>
struct Converter<enum QGradient::InterpolationMode>
{
public:
  typedef enum QGradient::InterpolationMode source_type;
  typedef QGradient_InterpolationMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QGradient::Spread>
class QGradient_Spread_Enums : public QFlags<enum QGradient::Spread> {
public:
  QGradient_Spread_Enums () : m_flags () { }
  QGradient_Spread_Enums (enum QGradient::Spread v) : m_flags (v) { }
  QGradient_Spread_Enums (const QFlags<enum QGradient::Spread> &v) : m_flags (v) { }
  QFlags<enum QGradient::Spread> flags () const { return m_flags; }
private:
  QFlags<QGradient::Spread> m_flags;
};

//  Wrapper class for enum QGradient::Spread
class QGradient_Spread_Enum : public QGradient_Spread_Enums {
public:
  QGradient_Spread_Enum () { }
  QGradient_Spread_Enum (enum QGradient::Spread v) : QGradient_Spread_Enums (v) { }
  enum QGradient::Spread value () const { return (enum QGradient::Spread) flags ().operator int (); }
};

//  Converter for QFlags<enum QGradient::Spread>
template <>
struct Converter<QFlags<enum QGradient::Spread> >
{
public:
  typedef QFlags<enum QGradient::Spread> source_type;
  typedef QGradient_Spread_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QGradient::Spread
template <>
struct Converter<enum QGradient::Spread>
{
public:
  typedef enum QGradient::Spread source_type;
  typedef QGradient_Spread_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QGradient::Type>
class QGradient_Type_Enums : public QFlags<enum QGradient::Type> {
public:
  QGradient_Type_Enums () : m_flags () { }
  QGradient_Type_Enums (enum QGradient::Type v) : m_flags (v) { }
  QGradient_Type_Enums (const QFlags<enum QGradient::Type> &v) : m_flags (v) { }
  QFlags<enum QGradient::Type> flags () const { return m_flags; }
private:
  QFlags<QGradient::Type> m_flags;
};

//  Wrapper class for enum QGradient::Type
class QGradient_Type_Enum : public QGradient_Type_Enums {
public:
  QGradient_Type_Enum () { }
  QGradient_Type_Enum (enum QGradient::Type v) : QGradient_Type_Enums (v) { }
  enum QGradient::Type value () const { return (enum QGradient::Type) flags ().operator int (); }
};

//  Converter for QFlags<enum QGradient::Type>
template <>
struct Converter<QFlags<enum QGradient::Type> >
{
public:
  typedef QFlags<enum QGradient::Type> source_type;
  typedef QGradient_Type_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QGradient::Type
template <>
struct Converter<enum QGradient::Type>
{
public:
  typedef enum QGradient::Type source_type;
  typedef QGradient_Type_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
