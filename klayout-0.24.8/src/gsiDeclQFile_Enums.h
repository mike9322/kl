
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
*  @file gsiDeclQFile_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQFile_Enums
#define _HDR_gsiDeclQFile_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QFile::FileError>
class QFile_FileError_Enums : public QFlags<enum QFile::FileError> {
public:
  QFile_FileError_Enums () : m_flags () { }
  QFile_FileError_Enums (enum QFile::FileError v) : m_flags (v) { }
  QFile_FileError_Enums (const QFlags<enum QFile::FileError> &v) : m_flags (v) { }
  QFlags<enum QFile::FileError> flags () const { return m_flags; }
private:
  QFlags<QFile::FileError> m_flags;
};

//  Wrapper class for enum QFile::FileError
class QFile_FileError_Enum : public QFile_FileError_Enums {
public:
  QFile_FileError_Enum () { }
  QFile_FileError_Enum (enum QFile::FileError v) : QFile_FileError_Enums (v) { }
  enum QFile::FileError value () const { return (enum QFile::FileError) flags ().operator int (); }
};

//  Converter for QFlags<enum QFile::FileError>
template <>
struct Converter<QFlags<enum QFile::FileError> >
{
public:
  typedef QFlags<enum QFile::FileError> source_type;
  typedef QFile_FileError_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QFile::FileError
template <>
struct Converter<enum QFile::FileError>
{
public:
  typedef enum QFile::FileError source_type;
  typedef QFile_FileError_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

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
