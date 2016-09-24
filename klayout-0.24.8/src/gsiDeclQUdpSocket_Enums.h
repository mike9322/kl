
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
*  @file gsiDeclQUdpSocket_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQUdpSocket_Enums
#define _HDR_gsiDeclQUdpSocket_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QAbstractSocket::SocketError>
class QAbstractSocket_SocketError_Enums : public QFlags<enum QAbstractSocket::SocketError> {
public:
  QAbstractSocket_SocketError_Enums () : m_flags () { }
  QAbstractSocket_SocketError_Enums (enum QAbstractSocket::SocketError v) : m_flags (v) { }
  QAbstractSocket_SocketError_Enums (const QFlags<enum QAbstractSocket::SocketError> &v) : m_flags (v) { }
  QFlags<enum QAbstractSocket::SocketError> flags () const { return m_flags; }
private:
  QFlags<QAbstractSocket::SocketError> m_flags;
};

//  Wrapper class for enum QAbstractSocket::SocketError
class QAbstractSocket_SocketError_Enum : public QAbstractSocket_SocketError_Enums {
public:
  QAbstractSocket_SocketError_Enum () { }
  QAbstractSocket_SocketError_Enum (enum QAbstractSocket::SocketError v) : QAbstractSocket_SocketError_Enums (v) { }
  enum QAbstractSocket::SocketError value () const { return (enum QAbstractSocket::SocketError) flags ().operator int (); }
};

//  Converter for QFlags<enum QAbstractSocket::SocketError>
template <>
struct Converter<QFlags<enum QAbstractSocket::SocketError> >
{
public:
  typedef QFlags<enum QAbstractSocket::SocketError> source_type;
  typedef QAbstractSocket_SocketError_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QAbstractSocket::SocketError
template <>
struct Converter<enum QAbstractSocket::SocketError>
{
public:
  typedef enum QAbstractSocket::SocketError source_type;
  typedef QAbstractSocket_SocketError_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QAbstractSocket::SocketOption>
class QAbstractSocket_SocketOption_Enums : public QFlags<enum QAbstractSocket::SocketOption> {
public:
  QAbstractSocket_SocketOption_Enums () : m_flags () { }
  QAbstractSocket_SocketOption_Enums (enum QAbstractSocket::SocketOption v) : m_flags (v) { }
  QAbstractSocket_SocketOption_Enums (const QFlags<enum QAbstractSocket::SocketOption> &v) : m_flags (v) { }
  QFlags<enum QAbstractSocket::SocketOption> flags () const { return m_flags; }
private:
  QFlags<QAbstractSocket::SocketOption> m_flags;
};

//  Wrapper class for enum QAbstractSocket::SocketOption
class QAbstractSocket_SocketOption_Enum : public QAbstractSocket_SocketOption_Enums {
public:
  QAbstractSocket_SocketOption_Enum () { }
  QAbstractSocket_SocketOption_Enum (enum QAbstractSocket::SocketOption v) : QAbstractSocket_SocketOption_Enums (v) { }
  enum QAbstractSocket::SocketOption value () const { return (enum QAbstractSocket::SocketOption) flags ().operator int (); }
};

//  Converter for QFlags<enum QAbstractSocket::SocketOption>
template <>
struct Converter<QFlags<enum QAbstractSocket::SocketOption> >
{
public:
  typedef QFlags<enum QAbstractSocket::SocketOption> source_type;
  typedef QAbstractSocket_SocketOption_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QAbstractSocket::SocketOption
template <>
struct Converter<enum QAbstractSocket::SocketOption>
{
public:
  typedef enum QAbstractSocket::SocketOption source_type;
  typedef QAbstractSocket_SocketOption_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QAbstractSocket::SocketState>
class QAbstractSocket_SocketState_Enums : public QFlags<enum QAbstractSocket::SocketState> {
public:
  QAbstractSocket_SocketState_Enums () : m_flags () { }
  QAbstractSocket_SocketState_Enums (enum QAbstractSocket::SocketState v) : m_flags (v) { }
  QAbstractSocket_SocketState_Enums (const QFlags<enum QAbstractSocket::SocketState> &v) : m_flags (v) { }
  QFlags<enum QAbstractSocket::SocketState> flags () const { return m_flags; }
private:
  QFlags<QAbstractSocket::SocketState> m_flags;
};

//  Wrapper class for enum QAbstractSocket::SocketState
class QAbstractSocket_SocketState_Enum : public QAbstractSocket_SocketState_Enums {
public:
  QAbstractSocket_SocketState_Enum () { }
  QAbstractSocket_SocketState_Enum (enum QAbstractSocket::SocketState v) : QAbstractSocket_SocketState_Enums (v) { }
  enum QAbstractSocket::SocketState value () const { return (enum QAbstractSocket::SocketState) flags ().operator int (); }
};

//  Converter for QFlags<enum QAbstractSocket::SocketState>
template <>
struct Converter<QFlags<enum QAbstractSocket::SocketState> >
{
public:
  typedef QFlags<enum QAbstractSocket::SocketState> source_type;
  typedef QAbstractSocket_SocketState_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QAbstractSocket::SocketState
template <>
struct Converter<enum QAbstractSocket::SocketState>
{
public:
  typedef enum QAbstractSocket::SocketState source_type;
  typedef QAbstractSocket_SocketState_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QAbstractSocket::SocketType>
class QAbstractSocket_SocketType_Enums : public QFlags<enum QAbstractSocket::SocketType> {
public:
  QAbstractSocket_SocketType_Enums () : m_flags () { }
  QAbstractSocket_SocketType_Enums (enum QAbstractSocket::SocketType v) : m_flags (v) { }
  QAbstractSocket_SocketType_Enums (const QFlags<enum QAbstractSocket::SocketType> &v) : m_flags (v) { }
  QFlags<enum QAbstractSocket::SocketType> flags () const { return m_flags; }
private:
  QFlags<QAbstractSocket::SocketType> m_flags;
};

//  Wrapper class for enum QAbstractSocket::SocketType
class QAbstractSocket_SocketType_Enum : public QAbstractSocket_SocketType_Enums {
public:
  QAbstractSocket_SocketType_Enum () { }
  QAbstractSocket_SocketType_Enum (enum QAbstractSocket::SocketType v) : QAbstractSocket_SocketType_Enums (v) { }
  enum QAbstractSocket::SocketType value () const { return (enum QAbstractSocket::SocketType) flags ().operator int (); }
};

//  Converter for QFlags<enum QAbstractSocket::SocketType>
template <>
struct Converter<QFlags<enum QAbstractSocket::SocketType> >
{
public:
  typedef QFlags<enum QAbstractSocket::SocketType> source_type;
  typedef QAbstractSocket_SocketType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QAbstractSocket::SocketType
template <>
struct Converter<enum QAbstractSocket::SocketType>
{
public:
  typedef enum QAbstractSocket::SocketType source_type;
  typedef QAbstractSocket_SocketType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QIODevice::OpenModeFlag>
class QIODevice_OpenModeFlag_Enums : public QFlags<enum QIODevice::OpenModeFlag> {
public:
  QIODevice_OpenModeFlag_Enums () : m_flags () { }
  QIODevice_OpenModeFlag_Enums (enum QIODevice::OpenModeFlag v) : m_flags (v) { }
  QIODevice_OpenModeFlag_Enums (const QFlags<enum QIODevice::OpenModeFlag> &v) : m_flags (v) { }
  QFlags<enum QIODevice::OpenModeFlag> flags () const { return m_flags; }
private:
  QFlags<QIODevice::OpenModeFlag> m_flags;
};

//  Wrapper class for enum QIODevice::OpenModeFlag
class QIODevice_OpenModeFlag_Enum : public QIODevice_OpenModeFlag_Enums {
public:
  QIODevice_OpenModeFlag_Enum () { }
  QIODevice_OpenModeFlag_Enum (enum QIODevice::OpenModeFlag v) : QIODevice_OpenModeFlag_Enums (v) { }
  enum QIODevice::OpenModeFlag value () const { return (enum QIODevice::OpenModeFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum QIODevice::OpenModeFlag>
template <>
struct Converter<QFlags<enum QIODevice::OpenModeFlag> >
{
public:
  typedef QFlags<enum QIODevice::OpenModeFlag> source_type;
  typedef QIODevice_OpenModeFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QIODevice::OpenModeFlag
template <>
struct Converter<enum QIODevice::OpenModeFlag>
{
public:
  typedef enum QIODevice::OpenModeFlag source_type;
  typedef QIODevice_OpenModeFlag_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QUdpSocket::BindFlag>
class QUdpSocket_BindFlag_Enums : public QFlags<enum QUdpSocket::BindFlag> {
public:
  QUdpSocket_BindFlag_Enums () : m_flags () { }
  QUdpSocket_BindFlag_Enums (enum QUdpSocket::BindFlag v) : m_flags (v) { }
  QUdpSocket_BindFlag_Enums (const QFlags<enum QUdpSocket::BindFlag> &v) : m_flags (v) { }
  QFlags<enum QUdpSocket::BindFlag> flags () const { return m_flags; }
private:
  QFlags<QUdpSocket::BindFlag> m_flags;
};

//  Wrapper class for enum QUdpSocket::BindFlag
class QUdpSocket_BindFlag_Enum : public QUdpSocket_BindFlag_Enums {
public:
  QUdpSocket_BindFlag_Enum () { }
  QUdpSocket_BindFlag_Enum (enum QUdpSocket::BindFlag v) : QUdpSocket_BindFlag_Enums (v) { }
  enum QUdpSocket::BindFlag value () const { return (enum QUdpSocket::BindFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum QUdpSocket::BindFlag>
template <>
struct Converter<QFlags<enum QUdpSocket::BindFlag> >
{
public:
  typedef QFlags<enum QUdpSocket::BindFlag> source_type;
  typedef QUdpSocket_BindFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QUdpSocket::BindFlag
template <>
struct Converter<enum QUdpSocket::BindFlag>
{
public:
  typedef enum QUdpSocket::BindFlag source_type;
  typedef QUdpSocket_BindFlag_Enum target_type;
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
