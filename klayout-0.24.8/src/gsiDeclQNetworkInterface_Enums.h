
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
*  @file gsiDeclQNetworkInterface_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQNetworkInterface_Enums
#define _HDR_gsiDeclQNetworkInterface_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QNetworkInterface::InterfaceFlag>
class QNetworkInterface_InterfaceFlag_Enums : public QFlags<enum QNetworkInterface::InterfaceFlag> {
public:
  QNetworkInterface_InterfaceFlag_Enums () : m_flags () { }
  QNetworkInterface_InterfaceFlag_Enums (enum QNetworkInterface::InterfaceFlag v) : m_flags (v) { }
  QNetworkInterface_InterfaceFlag_Enums (const QFlags<enum QNetworkInterface::InterfaceFlag> &v) : m_flags (v) { }
  QFlags<enum QNetworkInterface::InterfaceFlag> flags () const { return m_flags; }
private:
  QFlags<QNetworkInterface::InterfaceFlag> m_flags;
};

//  Wrapper class for enum QNetworkInterface::InterfaceFlag
class QNetworkInterface_InterfaceFlag_Enum : public QNetworkInterface_InterfaceFlag_Enums {
public:
  QNetworkInterface_InterfaceFlag_Enum () { }
  QNetworkInterface_InterfaceFlag_Enum (enum QNetworkInterface::InterfaceFlag v) : QNetworkInterface_InterfaceFlag_Enums (v) { }
  enum QNetworkInterface::InterfaceFlag value () const { return (enum QNetworkInterface::InterfaceFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum QNetworkInterface::InterfaceFlag>
template <>
struct Converter<QFlags<enum QNetworkInterface::InterfaceFlag> >
{
public:
  typedef QFlags<enum QNetworkInterface::InterfaceFlag> source_type;
  typedef QNetworkInterface_InterfaceFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QNetworkInterface::InterfaceFlag
template <>
struct Converter<enum QNetworkInterface::InterfaceFlag>
{
public:
  typedef enum QNetworkInterface::InterfaceFlag source_type;
  typedef QNetworkInterface_InterfaceFlag_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
