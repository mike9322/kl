
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
*  @file gsiDeclQTouchEvent_TouchPoint_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQTouchEvent_TouchPoint_Enums
#define _HDR_gsiDeclQTouchEvent_TouchPoint_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum Qt::TouchPointState>
class Qt_TouchPointState_Enums : public QFlags<enum Qt::TouchPointState> {
public:
  Qt_TouchPointState_Enums () : m_flags () { }
  Qt_TouchPointState_Enums (enum Qt::TouchPointState v) : m_flags (v) { }
  Qt_TouchPointState_Enums (const QFlags<enum Qt::TouchPointState> &v) : m_flags (v) { }
  QFlags<enum Qt::TouchPointState> flags () const { return m_flags; }
private:
  QFlags<Qt::TouchPointState> m_flags;
};

//  Wrapper class for enum Qt::TouchPointState
class Qt_TouchPointState_Enum : public Qt_TouchPointState_Enums {
public:
  Qt_TouchPointState_Enum () { }
  Qt_TouchPointState_Enum (enum Qt::TouchPointState v) : Qt_TouchPointState_Enums (v) { }
  enum Qt::TouchPointState value () const { return (enum Qt::TouchPointState) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::TouchPointState>
template <>
struct Converter<QFlags<enum Qt::TouchPointState> >
{
public:
  typedef QFlags<enum Qt::TouchPointState> source_type;
  typedef Qt_TouchPointState_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::TouchPointState
template <>
struct Converter<enum Qt::TouchPointState>
{
public:
  typedef enum Qt::TouchPointState source_type;
  typedef Qt_TouchPointState_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
