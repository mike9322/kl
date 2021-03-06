
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
*  @file gsiDeclQGraphicsLayout_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQGraphicsLayout_Enums
#define _HDR_gsiDeclQGraphicsLayout_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QSizePolicy::ControlType>
class QSizePolicy_ControlType_Enums : public QFlags<enum QSizePolicy::ControlType> {
public:
  QSizePolicy_ControlType_Enums () : m_flags () { }
  QSizePolicy_ControlType_Enums (enum QSizePolicy::ControlType v) : m_flags (v) { }
  QSizePolicy_ControlType_Enums (const QFlags<enum QSizePolicy::ControlType> &v) : m_flags (v) { }
  QFlags<enum QSizePolicy::ControlType> flags () const { return m_flags; }
private:
  QFlags<QSizePolicy::ControlType> m_flags;
};

//  Wrapper class for enum QSizePolicy::ControlType
class QSizePolicy_ControlType_Enum : public QSizePolicy_ControlType_Enums {
public:
  QSizePolicy_ControlType_Enum () { }
  QSizePolicy_ControlType_Enum (enum QSizePolicy::ControlType v) : QSizePolicy_ControlType_Enums (v) { }
  enum QSizePolicy::ControlType value () const { return (enum QSizePolicy::ControlType) flags ().operator int (); }
};

//  Converter for QFlags<enum QSizePolicy::ControlType>
template <>
struct Converter<QFlags<enum QSizePolicy::ControlType> >
{
public:
  typedef QFlags<enum QSizePolicy::ControlType> source_type;
  typedef QSizePolicy_ControlType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QSizePolicy::ControlType
template <>
struct Converter<enum QSizePolicy::ControlType>
{
public:
  typedef enum QSizePolicy::ControlType source_type;
  typedef QSizePolicy_ControlType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QSizePolicy::Policy>
class QSizePolicy_Policy_Enums : public QFlags<enum QSizePolicy::Policy> {
public:
  QSizePolicy_Policy_Enums () : m_flags () { }
  QSizePolicy_Policy_Enums (enum QSizePolicy::Policy v) : m_flags (v) { }
  QSizePolicy_Policy_Enums (const QFlags<enum QSizePolicy::Policy> &v) : m_flags (v) { }
  QFlags<enum QSizePolicy::Policy> flags () const { return m_flags; }
private:
  QFlags<QSizePolicy::Policy> m_flags;
};

//  Wrapper class for enum QSizePolicy::Policy
class QSizePolicy_Policy_Enum : public QSizePolicy_Policy_Enums {
public:
  QSizePolicy_Policy_Enum () { }
  QSizePolicy_Policy_Enum (enum QSizePolicy::Policy v) : QSizePolicy_Policy_Enums (v) { }
  enum QSizePolicy::Policy value () const { return (enum QSizePolicy::Policy) flags ().operator int (); }
};

//  Converter for QFlags<enum QSizePolicy::Policy>
template <>
struct Converter<QFlags<enum QSizePolicy::Policy> >
{
public:
  typedef QFlags<enum QSizePolicy::Policy> source_type;
  typedef QSizePolicy_Policy_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QSizePolicy::Policy
template <>
struct Converter<enum QSizePolicy::Policy>
{
public:
  typedef enum QSizePolicy::Policy source_type;
  typedef QSizePolicy_Policy_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::SizeHint>
class Qt_SizeHint_Enums : public QFlags<enum Qt::SizeHint> {
public:
  Qt_SizeHint_Enums () : m_flags () { }
  Qt_SizeHint_Enums (enum Qt::SizeHint v) : m_flags (v) { }
  Qt_SizeHint_Enums (const QFlags<enum Qt::SizeHint> &v) : m_flags (v) { }
  QFlags<enum Qt::SizeHint> flags () const { return m_flags; }
private:
  QFlags<Qt::SizeHint> m_flags;
};

//  Wrapper class for enum Qt::SizeHint
class Qt_SizeHint_Enum : public Qt_SizeHint_Enums {
public:
  Qt_SizeHint_Enum () { }
  Qt_SizeHint_Enum (enum Qt::SizeHint v) : Qt_SizeHint_Enums (v) { }
  enum Qt::SizeHint value () const { return (enum Qt::SizeHint) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::SizeHint>
template <>
struct Converter<QFlags<enum Qt::SizeHint> >
{
public:
  typedef QFlags<enum Qt::SizeHint> source_type;
  typedef Qt_SizeHint_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::SizeHint
template <>
struct Converter<enum Qt::SizeHint>
{
public:
  typedef enum Qt::SizeHint source_type;
  typedef Qt_SizeHint_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
