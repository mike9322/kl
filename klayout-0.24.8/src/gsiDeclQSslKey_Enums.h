
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
*  @file gsiDeclQSslKey_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQSslKey_Enums
#define _HDR_gsiDeclQSslKey_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QSsl::EncodingFormat>
class QSsl_EncodingFormat_Enums : public QFlags<enum QSsl::EncodingFormat> {
public:
  QSsl_EncodingFormat_Enums () : m_flags () { }
  QSsl_EncodingFormat_Enums (enum QSsl::EncodingFormat v) : m_flags (v) { }
  QSsl_EncodingFormat_Enums (const QFlags<enum QSsl::EncodingFormat> &v) : m_flags (v) { }
  QFlags<enum QSsl::EncodingFormat> flags () const { return m_flags; }
private:
  QFlags<QSsl::EncodingFormat> m_flags;
};

//  Wrapper class for enum QSsl::EncodingFormat
class QSsl_EncodingFormat_Enum : public QSsl_EncodingFormat_Enums {
public:
  QSsl_EncodingFormat_Enum () { }
  QSsl_EncodingFormat_Enum (enum QSsl::EncodingFormat v) : QSsl_EncodingFormat_Enums (v) { }
  enum QSsl::EncodingFormat value () const { return (enum QSsl::EncodingFormat) flags ().operator int (); }
};

//  Converter for QFlags<enum QSsl::EncodingFormat>
template <>
struct Converter<QFlags<enum QSsl::EncodingFormat> >
{
public:
  typedef QFlags<enum QSsl::EncodingFormat> source_type;
  typedef QSsl_EncodingFormat_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QSsl::EncodingFormat
template <>
struct Converter<enum QSsl::EncodingFormat>
{
public:
  typedef enum QSsl::EncodingFormat source_type;
  typedef QSsl_EncodingFormat_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QSsl::KeyAlgorithm>
class QSsl_KeyAlgorithm_Enums : public QFlags<enum QSsl::KeyAlgorithm> {
public:
  QSsl_KeyAlgorithm_Enums () : m_flags () { }
  QSsl_KeyAlgorithm_Enums (enum QSsl::KeyAlgorithm v) : m_flags (v) { }
  QSsl_KeyAlgorithm_Enums (const QFlags<enum QSsl::KeyAlgorithm> &v) : m_flags (v) { }
  QFlags<enum QSsl::KeyAlgorithm> flags () const { return m_flags; }
private:
  QFlags<QSsl::KeyAlgorithm> m_flags;
};

//  Wrapper class for enum QSsl::KeyAlgorithm
class QSsl_KeyAlgorithm_Enum : public QSsl_KeyAlgorithm_Enums {
public:
  QSsl_KeyAlgorithm_Enum () { }
  QSsl_KeyAlgorithm_Enum (enum QSsl::KeyAlgorithm v) : QSsl_KeyAlgorithm_Enums (v) { }
  enum QSsl::KeyAlgorithm value () const { return (enum QSsl::KeyAlgorithm) flags ().operator int (); }
};

//  Converter for QFlags<enum QSsl::KeyAlgorithm>
template <>
struct Converter<QFlags<enum QSsl::KeyAlgorithm> >
{
public:
  typedef QFlags<enum QSsl::KeyAlgorithm> source_type;
  typedef QSsl_KeyAlgorithm_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QSsl::KeyAlgorithm
template <>
struct Converter<enum QSsl::KeyAlgorithm>
{
public:
  typedef enum QSsl::KeyAlgorithm source_type;
  typedef QSsl_KeyAlgorithm_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QSsl::KeyType>
class QSsl_KeyType_Enums : public QFlags<enum QSsl::KeyType> {
public:
  QSsl_KeyType_Enums () : m_flags () { }
  QSsl_KeyType_Enums (enum QSsl::KeyType v) : m_flags (v) { }
  QSsl_KeyType_Enums (const QFlags<enum QSsl::KeyType> &v) : m_flags (v) { }
  QFlags<enum QSsl::KeyType> flags () const { return m_flags; }
private:
  QFlags<QSsl::KeyType> m_flags;
};

//  Wrapper class for enum QSsl::KeyType
class QSsl_KeyType_Enum : public QSsl_KeyType_Enums {
public:
  QSsl_KeyType_Enum () { }
  QSsl_KeyType_Enum (enum QSsl::KeyType v) : QSsl_KeyType_Enums (v) { }
  enum QSsl::KeyType value () const { return (enum QSsl::KeyType) flags ().operator int (); }
};

//  Converter for QFlags<enum QSsl::KeyType>
template <>
struct Converter<QFlags<enum QSsl::KeyType> >
{
public:
  typedef QFlags<enum QSsl::KeyType> source_type;
  typedef QSsl_KeyType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QSsl::KeyType
template <>
struct Converter<enum QSsl::KeyType>
{
public:
  typedef enum QSsl::KeyType source_type;
  typedef QSsl_KeyType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
