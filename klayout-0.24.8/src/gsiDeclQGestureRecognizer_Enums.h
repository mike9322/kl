
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
*  @file gsiDeclQGestureRecognizer_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQGestureRecognizer_Enums
#define _HDR_gsiDeclQGestureRecognizer_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QGestureRecognizer::ResultFlag>
class QGestureRecognizer_ResultFlag_Enums : public QFlags<enum QGestureRecognizer::ResultFlag> {
public:
  QGestureRecognizer_ResultFlag_Enums () : m_flags () { }
  QGestureRecognizer_ResultFlag_Enums (enum QGestureRecognizer::ResultFlag v) : m_flags (v) { }
  QGestureRecognizer_ResultFlag_Enums (const QFlags<enum QGestureRecognizer::ResultFlag> &v) : m_flags (v) { }
  QFlags<enum QGestureRecognizer::ResultFlag> flags () const { return m_flags; }
private:
  QFlags<QGestureRecognizer::ResultFlag> m_flags;
};

//  Wrapper class for enum QGestureRecognizer::ResultFlag
class QGestureRecognizer_ResultFlag_Enum : public QGestureRecognizer_ResultFlag_Enums {
public:
  QGestureRecognizer_ResultFlag_Enum () { }
  QGestureRecognizer_ResultFlag_Enum (enum QGestureRecognizer::ResultFlag v) : QGestureRecognizer_ResultFlag_Enums (v) { }
  enum QGestureRecognizer::ResultFlag value () const { return (enum QGestureRecognizer::ResultFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum QGestureRecognizer::ResultFlag>
template <>
struct Converter<QFlags<enum QGestureRecognizer::ResultFlag> >
{
public:
  typedef QFlags<enum QGestureRecognizer::ResultFlag> source_type;
  typedef QGestureRecognizer_ResultFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QGestureRecognizer::ResultFlag
template <>
struct Converter<enum QGestureRecognizer::ResultFlag>
{
public:
  typedef enum QGestureRecognizer::ResultFlag source_type;
  typedef QGestureRecognizer_ResultFlag_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::GestureType>
class Qt_GestureType_Enums : public QFlags<enum Qt::GestureType> {
public:
  Qt_GestureType_Enums () : m_flags () { }
  Qt_GestureType_Enums (enum Qt::GestureType v) : m_flags (v) { }
  Qt_GestureType_Enums (const QFlags<enum Qt::GestureType> &v) : m_flags (v) { }
  QFlags<enum Qt::GestureType> flags () const { return m_flags; }
private:
  QFlags<Qt::GestureType> m_flags;
};

//  Wrapper class for enum Qt::GestureType
class Qt_GestureType_Enum : public Qt_GestureType_Enums {
public:
  Qt_GestureType_Enum () { }
  Qt_GestureType_Enum (enum Qt::GestureType v) : Qt_GestureType_Enums (v) { }
  enum Qt::GestureType value () const { return (enum Qt::GestureType) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::GestureType>
template <>
struct Converter<QFlags<enum Qt::GestureType> >
{
public:
  typedef QFlags<enum Qt::GestureType> source_type;
  typedef Qt_GestureType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::GestureType
template <>
struct Converter<enum Qt::GestureType>
{
public:
  typedef enum Qt::GestureType source_type;
  typedef Qt_GestureType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
