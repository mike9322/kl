
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
*  @file gsiDeclQKeySequence_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQKeySequence_Enums
#define _HDR_gsiDeclQKeySequence_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QKeySequence::SequenceFormat>
class QKeySequence_SequenceFormat_Enums : public QFlags<enum QKeySequence::SequenceFormat> {
public:
  QKeySequence_SequenceFormat_Enums () : m_flags () { }
  QKeySequence_SequenceFormat_Enums (enum QKeySequence::SequenceFormat v) : m_flags (v) { }
  QKeySequence_SequenceFormat_Enums (const QFlags<enum QKeySequence::SequenceFormat> &v) : m_flags (v) { }
  QFlags<enum QKeySequence::SequenceFormat> flags () const { return m_flags; }
private:
  QFlags<QKeySequence::SequenceFormat> m_flags;
};

//  Wrapper class for enum QKeySequence::SequenceFormat
class QKeySequence_SequenceFormat_Enum : public QKeySequence_SequenceFormat_Enums {
public:
  QKeySequence_SequenceFormat_Enum () { }
  QKeySequence_SequenceFormat_Enum (enum QKeySequence::SequenceFormat v) : QKeySequence_SequenceFormat_Enums (v) { }
  enum QKeySequence::SequenceFormat value () const { return (enum QKeySequence::SequenceFormat) flags ().operator int (); }
};

//  Converter for QFlags<enum QKeySequence::SequenceFormat>
template <>
struct Converter<QFlags<enum QKeySequence::SequenceFormat> >
{
public:
  typedef QFlags<enum QKeySequence::SequenceFormat> source_type;
  typedef QKeySequence_SequenceFormat_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QKeySequence::SequenceFormat
template <>
struct Converter<enum QKeySequence::SequenceFormat>
{
public:
  typedef enum QKeySequence::SequenceFormat source_type;
  typedef QKeySequence_SequenceFormat_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QKeySequence::SequenceMatch>
class QKeySequence_SequenceMatch_Enums : public QFlags<enum QKeySequence::SequenceMatch> {
public:
  QKeySequence_SequenceMatch_Enums () : m_flags () { }
  QKeySequence_SequenceMatch_Enums (enum QKeySequence::SequenceMatch v) : m_flags (v) { }
  QKeySequence_SequenceMatch_Enums (const QFlags<enum QKeySequence::SequenceMatch> &v) : m_flags (v) { }
  QFlags<enum QKeySequence::SequenceMatch> flags () const { return m_flags; }
private:
  QFlags<QKeySequence::SequenceMatch> m_flags;
};

//  Wrapper class for enum QKeySequence::SequenceMatch
class QKeySequence_SequenceMatch_Enum : public QKeySequence_SequenceMatch_Enums {
public:
  QKeySequence_SequenceMatch_Enum () { }
  QKeySequence_SequenceMatch_Enum (enum QKeySequence::SequenceMatch v) : QKeySequence_SequenceMatch_Enums (v) { }
  enum QKeySequence::SequenceMatch value () const { return (enum QKeySequence::SequenceMatch) flags ().operator int (); }
};

//  Converter for QFlags<enum QKeySequence::SequenceMatch>
template <>
struct Converter<QFlags<enum QKeySequence::SequenceMatch> >
{
public:
  typedef QFlags<enum QKeySequence::SequenceMatch> source_type;
  typedef QKeySequence_SequenceMatch_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QKeySequence::SequenceMatch
template <>
struct Converter<enum QKeySequence::SequenceMatch>
{
public:
  typedef enum QKeySequence::SequenceMatch source_type;
  typedef QKeySequence_SequenceMatch_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QKeySequence::StandardKey>
class QKeySequence_StandardKey_Enums : public QFlags<enum QKeySequence::StandardKey> {
public:
  QKeySequence_StandardKey_Enums () : m_flags () { }
  QKeySequence_StandardKey_Enums (enum QKeySequence::StandardKey v) : m_flags (v) { }
  QKeySequence_StandardKey_Enums (const QFlags<enum QKeySequence::StandardKey> &v) : m_flags (v) { }
  QFlags<enum QKeySequence::StandardKey> flags () const { return m_flags; }
private:
  QFlags<QKeySequence::StandardKey> m_flags;
};

//  Wrapper class for enum QKeySequence::StandardKey
class QKeySequence_StandardKey_Enum : public QKeySequence_StandardKey_Enums {
public:
  QKeySequence_StandardKey_Enum () { }
  QKeySequence_StandardKey_Enum (enum QKeySequence::StandardKey v) : QKeySequence_StandardKey_Enums (v) { }
  enum QKeySequence::StandardKey value () const { return (enum QKeySequence::StandardKey) flags ().operator int (); }
};

//  Converter for QFlags<enum QKeySequence::StandardKey>
template <>
struct Converter<QFlags<enum QKeySequence::StandardKey> >
{
public:
  typedef QFlags<enum QKeySequence::StandardKey> source_type;
  typedef QKeySequence_StandardKey_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QKeySequence::StandardKey
template <>
struct Converter<enum QKeySequence::StandardKey>
{
public:
  typedef enum QKeySequence::StandardKey source_type;
  typedef QKeySequence_StandardKey_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
