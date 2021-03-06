
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
*  @file gsiDeclQTextCursor_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQTextCursor_Enums
#define _HDR_gsiDeclQTextCursor_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QTextCursor::MoveMode>
class QTextCursor_MoveMode_Enums : public QFlags<enum QTextCursor::MoveMode> {
public:
  QTextCursor_MoveMode_Enums () : m_flags () { }
  QTextCursor_MoveMode_Enums (enum QTextCursor::MoveMode v) : m_flags (v) { }
  QTextCursor_MoveMode_Enums (const QFlags<enum QTextCursor::MoveMode> &v) : m_flags (v) { }
  QFlags<enum QTextCursor::MoveMode> flags () const { return m_flags; }
private:
  QFlags<QTextCursor::MoveMode> m_flags;
};

//  Wrapper class for enum QTextCursor::MoveMode
class QTextCursor_MoveMode_Enum : public QTextCursor_MoveMode_Enums {
public:
  QTextCursor_MoveMode_Enum () { }
  QTextCursor_MoveMode_Enum (enum QTextCursor::MoveMode v) : QTextCursor_MoveMode_Enums (v) { }
  enum QTextCursor::MoveMode value () const { return (enum QTextCursor::MoveMode) flags ().operator int (); }
};

//  Converter for QFlags<enum QTextCursor::MoveMode>
template <>
struct Converter<QFlags<enum QTextCursor::MoveMode> >
{
public:
  typedef QFlags<enum QTextCursor::MoveMode> source_type;
  typedef QTextCursor_MoveMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QTextCursor::MoveMode
template <>
struct Converter<enum QTextCursor::MoveMode>
{
public:
  typedef enum QTextCursor::MoveMode source_type;
  typedef QTextCursor_MoveMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QTextCursor::MoveOperation>
class QTextCursor_MoveOperation_Enums : public QFlags<enum QTextCursor::MoveOperation> {
public:
  QTextCursor_MoveOperation_Enums () : m_flags () { }
  QTextCursor_MoveOperation_Enums (enum QTextCursor::MoveOperation v) : m_flags (v) { }
  QTextCursor_MoveOperation_Enums (const QFlags<enum QTextCursor::MoveOperation> &v) : m_flags (v) { }
  QFlags<enum QTextCursor::MoveOperation> flags () const { return m_flags; }
private:
  QFlags<QTextCursor::MoveOperation> m_flags;
};

//  Wrapper class for enum QTextCursor::MoveOperation
class QTextCursor_MoveOperation_Enum : public QTextCursor_MoveOperation_Enums {
public:
  QTextCursor_MoveOperation_Enum () { }
  QTextCursor_MoveOperation_Enum (enum QTextCursor::MoveOperation v) : QTextCursor_MoveOperation_Enums (v) { }
  enum QTextCursor::MoveOperation value () const { return (enum QTextCursor::MoveOperation) flags ().operator int (); }
};

//  Converter for QFlags<enum QTextCursor::MoveOperation>
template <>
struct Converter<QFlags<enum QTextCursor::MoveOperation> >
{
public:
  typedef QFlags<enum QTextCursor::MoveOperation> source_type;
  typedef QTextCursor_MoveOperation_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QTextCursor::MoveOperation
template <>
struct Converter<enum QTextCursor::MoveOperation>
{
public:
  typedef enum QTextCursor::MoveOperation source_type;
  typedef QTextCursor_MoveOperation_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QTextCursor::SelectionType>
class QTextCursor_SelectionType_Enums : public QFlags<enum QTextCursor::SelectionType> {
public:
  QTextCursor_SelectionType_Enums () : m_flags () { }
  QTextCursor_SelectionType_Enums (enum QTextCursor::SelectionType v) : m_flags (v) { }
  QTextCursor_SelectionType_Enums (const QFlags<enum QTextCursor::SelectionType> &v) : m_flags (v) { }
  QFlags<enum QTextCursor::SelectionType> flags () const { return m_flags; }
private:
  QFlags<QTextCursor::SelectionType> m_flags;
};

//  Wrapper class for enum QTextCursor::SelectionType
class QTextCursor_SelectionType_Enum : public QTextCursor_SelectionType_Enums {
public:
  QTextCursor_SelectionType_Enum () { }
  QTextCursor_SelectionType_Enum (enum QTextCursor::SelectionType v) : QTextCursor_SelectionType_Enums (v) { }
  enum QTextCursor::SelectionType value () const { return (enum QTextCursor::SelectionType) flags ().operator int (); }
};

//  Converter for QFlags<enum QTextCursor::SelectionType>
template <>
struct Converter<QFlags<enum QTextCursor::SelectionType> >
{
public:
  typedef QFlags<enum QTextCursor::SelectionType> source_type;
  typedef QTextCursor_SelectionType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QTextCursor::SelectionType
template <>
struct Converter<enum QTextCursor::SelectionType>
{
public:
  typedef enum QTextCursor::SelectionType source_type;
  typedef QTextCursor_SelectionType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QTextFrameFormat::Position>
class QTextFrameFormat_Position_Enums : public QFlags<enum QTextFrameFormat::Position> {
public:
  QTextFrameFormat_Position_Enums () : m_flags () { }
  QTextFrameFormat_Position_Enums (enum QTextFrameFormat::Position v) : m_flags (v) { }
  QTextFrameFormat_Position_Enums (const QFlags<enum QTextFrameFormat::Position> &v) : m_flags (v) { }
  QFlags<enum QTextFrameFormat::Position> flags () const { return m_flags; }
private:
  QFlags<QTextFrameFormat::Position> m_flags;
};

//  Wrapper class for enum QTextFrameFormat::Position
class QTextFrameFormat_Position_Enum : public QTextFrameFormat_Position_Enums {
public:
  QTextFrameFormat_Position_Enum () { }
  QTextFrameFormat_Position_Enum (enum QTextFrameFormat::Position v) : QTextFrameFormat_Position_Enums (v) { }
  enum QTextFrameFormat::Position value () const { return (enum QTextFrameFormat::Position) flags ().operator int (); }
};

//  Converter for QFlags<enum QTextFrameFormat::Position>
template <>
struct Converter<QFlags<enum QTextFrameFormat::Position> >
{
public:
  typedef QFlags<enum QTextFrameFormat::Position> source_type;
  typedef QTextFrameFormat_Position_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QTextFrameFormat::Position
template <>
struct Converter<enum QTextFrameFormat::Position>
{
public:
  typedef enum QTextFrameFormat::Position source_type;
  typedef QTextFrameFormat_Position_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QTextListFormat::Style>
class QTextListFormat_Style_Enums : public QFlags<enum QTextListFormat::Style> {
public:
  QTextListFormat_Style_Enums () : m_flags () { }
  QTextListFormat_Style_Enums (enum QTextListFormat::Style v) : m_flags (v) { }
  QTextListFormat_Style_Enums (const QFlags<enum QTextListFormat::Style> &v) : m_flags (v) { }
  QFlags<enum QTextListFormat::Style> flags () const { return m_flags; }
private:
  QFlags<QTextListFormat::Style> m_flags;
};

//  Wrapper class for enum QTextListFormat::Style
class QTextListFormat_Style_Enum : public QTextListFormat_Style_Enums {
public:
  QTextListFormat_Style_Enum () { }
  QTextListFormat_Style_Enum (enum QTextListFormat::Style v) : QTextListFormat_Style_Enums (v) { }
  enum QTextListFormat::Style value () const { return (enum QTextListFormat::Style) flags ().operator int (); }
};

//  Converter for QFlags<enum QTextListFormat::Style>
template <>
struct Converter<QFlags<enum QTextListFormat::Style> >
{
public:
  typedef QFlags<enum QTextListFormat::Style> source_type;
  typedef QTextListFormat_Style_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QTextListFormat::Style
template <>
struct Converter<enum QTextListFormat::Style>
{
public:
  typedef enum QTextListFormat::Style source_type;
  typedef QTextListFormat_Style_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
