
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
*  @file gsiDeclQCoreApplication_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQCoreApplication_Enums
#define _HDR_gsiDeclQCoreApplication_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QCoreApplication::Encoding>
class QCoreApplication_Encoding_Enums : public QFlags<enum QCoreApplication::Encoding> {
public:
  QCoreApplication_Encoding_Enums () : m_flags () { }
  QCoreApplication_Encoding_Enums (enum QCoreApplication::Encoding v) : m_flags (v) { }
  QCoreApplication_Encoding_Enums (const QFlags<enum QCoreApplication::Encoding> &v) : m_flags (v) { }
  QFlags<enum QCoreApplication::Encoding> flags () const { return m_flags; }
private:
  QFlags<QCoreApplication::Encoding> m_flags;
};

//  Wrapper class for enum QCoreApplication::Encoding
class QCoreApplication_Encoding_Enum : public QCoreApplication_Encoding_Enums {
public:
  QCoreApplication_Encoding_Enum () { }
  QCoreApplication_Encoding_Enum (enum QCoreApplication::Encoding v) : QCoreApplication_Encoding_Enums (v) { }
  enum QCoreApplication::Encoding value () const { return (enum QCoreApplication::Encoding) flags ().operator int (); }
};

//  Converter for QFlags<enum QCoreApplication::Encoding>
template <>
struct Converter<QFlags<enum QCoreApplication::Encoding> >
{
public:
  typedef QFlags<enum QCoreApplication::Encoding> source_type;
  typedef QCoreApplication_Encoding_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QCoreApplication::Encoding
template <>
struct Converter<enum QCoreApplication::Encoding>
{
public:
  typedef enum QCoreApplication::Encoding source_type;
  typedef QCoreApplication_Encoding_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QEventLoop::ProcessEventsFlag>
class QEventLoop_ProcessEventsFlag_Enums : public QFlags<enum QEventLoop::ProcessEventsFlag> {
public:
  QEventLoop_ProcessEventsFlag_Enums () : m_flags () { }
  QEventLoop_ProcessEventsFlag_Enums (enum QEventLoop::ProcessEventsFlag v) : m_flags (v) { }
  QEventLoop_ProcessEventsFlag_Enums (const QFlags<enum QEventLoop::ProcessEventsFlag> &v) : m_flags (v) { }
  QFlags<enum QEventLoop::ProcessEventsFlag> flags () const { return m_flags; }
private:
  QFlags<QEventLoop::ProcessEventsFlag> m_flags;
};

//  Wrapper class for enum QEventLoop::ProcessEventsFlag
class QEventLoop_ProcessEventsFlag_Enum : public QEventLoop_ProcessEventsFlag_Enums {
public:
  QEventLoop_ProcessEventsFlag_Enum () { }
  QEventLoop_ProcessEventsFlag_Enum (enum QEventLoop::ProcessEventsFlag v) : QEventLoop_ProcessEventsFlag_Enums (v) { }
  enum QEventLoop::ProcessEventsFlag value () const { return (enum QEventLoop::ProcessEventsFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum QEventLoop::ProcessEventsFlag>
template <>
struct Converter<QFlags<enum QEventLoop::ProcessEventsFlag> >
{
public:
  typedef QFlags<enum QEventLoop::ProcessEventsFlag> source_type;
  typedef QEventLoop_ProcessEventsFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QEventLoop::ProcessEventsFlag
template <>
struct Converter<enum QEventLoop::ProcessEventsFlag>
{
public:
  typedef enum QEventLoop::ProcessEventsFlag source_type;
  typedef QEventLoop_ProcessEventsFlag_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::ApplicationAttribute>
class Qt_ApplicationAttribute_Enums : public QFlags<enum Qt::ApplicationAttribute> {
public:
  Qt_ApplicationAttribute_Enums () : m_flags () { }
  Qt_ApplicationAttribute_Enums (enum Qt::ApplicationAttribute v) : m_flags (v) { }
  Qt_ApplicationAttribute_Enums (const QFlags<enum Qt::ApplicationAttribute> &v) : m_flags (v) { }
  QFlags<enum Qt::ApplicationAttribute> flags () const { return m_flags; }
private:
  QFlags<Qt::ApplicationAttribute> m_flags;
};

//  Wrapper class for enum Qt::ApplicationAttribute
class Qt_ApplicationAttribute_Enum : public Qt_ApplicationAttribute_Enums {
public:
  Qt_ApplicationAttribute_Enum () { }
  Qt_ApplicationAttribute_Enum (enum Qt::ApplicationAttribute v) : Qt_ApplicationAttribute_Enums (v) { }
  enum Qt::ApplicationAttribute value () const { return (enum Qt::ApplicationAttribute) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::ApplicationAttribute>
template <>
struct Converter<QFlags<enum Qt::ApplicationAttribute> >
{
public:
  typedef QFlags<enum Qt::ApplicationAttribute> source_type;
  typedef Qt_ApplicationAttribute_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::ApplicationAttribute
template <>
struct Converter<enum Qt::ApplicationAttribute>
{
public:
  typedef enum Qt::ApplicationAttribute source_type;
  typedef Qt_ApplicationAttribute_Enum target_type;
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
