
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
*  @file gsiDeclQStylePainter_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQStylePainter_Enums
#define _HDR_gsiDeclQStylePainter_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QPainter::CompositionMode>
class QPainter_CompositionMode_Enums : public QFlags<enum QPainter::CompositionMode> {
public:
  QPainter_CompositionMode_Enums () : m_flags () { }
  QPainter_CompositionMode_Enums (enum QPainter::CompositionMode v) : m_flags (v) { }
  QPainter_CompositionMode_Enums (const QFlags<enum QPainter::CompositionMode> &v) : m_flags (v) { }
  QFlags<enum QPainter::CompositionMode> flags () const { return m_flags; }
private:
  QFlags<QPainter::CompositionMode> m_flags;
};

//  Wrapper class for enum QPainter::CompositionMode
class QPainter_CompositionMode_Enum : public QPainter_CompositionMode_Enums {
public:
  QPainter_CompositionMode_Enum () { }
  QPainter_CompositionMode_Enum (enum QPainter::CompositionMode v) : QPainter_CompositionMode_Enums (v) { }
  enum QPainter::CompositionMode value () const { return (enum QPainter::CompositionMode) flags ().operator int (); }
};

//  Converter for QFlags<enum QPainter::CompositionMode>
template <>
struct Converter<QFlags<enum QPainter::CompositionMode> >
{
public:
  typedef QFlags<enum QPainter::CompositionMode> source_type;
  typedef QPainter_CompositionMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPainter::CompositionMode
template <>
struct Converter<enum QPainter::CompositionMode>
{
public:
  typedef enum QPainter::CompositionMode source_type;
  typedef QPainter_CompositionMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPainter::RenderHint>
class QPainter_RenderHint_Enums : public QFlags<enum QPainter::RenderHint> {
public:
  QPainter_RenderHint_Enums () : m_flags () { }
  QPainter_RenderHint_Enums (enum QPainter::RenderHint v) : m_flags (v) { }
  QPainter_RenderHint_Enums (const QFlags<enum QPainter::RenderHint> &v) : m_flags (v) { }
  QFlags<enum QPainter::RenderHint> flags () const { return m_flags; }
private:
  QFlags<QPainter::RenderHint> m_flags;
};

//  Wrapper class for enum QPainter::RenderHint
class QPainter_RenderHint_Enum : public QPainter_RenderHint_Enums {
public:
  QPainter_RenderHint_Enum () { }
  QPainter_RenderHint_Enum (enum QPainter::RenderHint v) : QPainter_RenderHint_Enums (v) { }
  enum QPainter::RenderHint value () const { return (enum QPainter::RenderHint) flags ().operator int (); }
};

//  Converter for QFlags<enum QPainter::RenderHint>
template <>
struct Converter<QFlags<enum QPainter::RenderHint> >
{
public:
  typedef QFlags<enum QPainter::RenderHint> source_type;
  typedef QPainter_RenderHint_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPainter::RenderHint
template <>
struct Converter<enum QPainter::RenderHint>
{
public:
  typedef enum QPainter::RenderHint source_type;
  typedef QPainter_RenderHint_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPalette::ColorRole>
class QPalette_ColorRole_Enums : public QFlags<enum QPalette::ColorRole> {
public:
  QPalette_ColorRole_Enums () : m_flags () { }
  QPalette_ColorRole_Enums (enum QPalette::ColorRole v) : m_flags (v) { }
  QPalette_ColorRole_Enums (const QFlags<enum QPalette::ColorRole> &v) : m_flags (v) { }
  QFlags<enum QPalette::ColorRole> flags () const { return m_flags; }
private:
  QFlags<QPalette::ColorRole> m_flags;
};

//  Wrapper class for enum QPalette::ColorRole
class QPalette_ColorRole_Enum : public QPalette_ColorRole_Enums {
public:
  QPalette_ColorRole_Enum () { }
  QPalette_ColorRole_Enum (enum QPalette::ColorRole v) : QPalette_ColorRole_Enums (v) { }
  enum QPalette::ColorRole value () const { return (enum QPalette::ColorRole) flags ().operator int (); }
};

//  Converter for QFlags<enum QPalette::ColorRole>
template <>
struct Converter<QFlags<enum QPalette::ColorRole> >
{
public:
  typedef QFlags<enum QPalette::ColorRole> source_type;
  typedef QPalette_ColorRole_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPalette::ColorRole
template <>
struct Converter<enum QPalette::ColorRole>
{
public:
  typedef enum QPalette::ColorRole source_type;
  typedef QPalette_ColorRole_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QStyle::ComplexControl>
class QStyle_ComplexControl_Enums : public QFlags<enum QStyle::ComplexControl> {
public:
  QStyle_ComplexControl_Enums () : m_flags () { }
  QStyle_ComplexControl_Enums (enum QStyle::ComplexControl v) : m_flags (v) { }
  QStyle_ComplexControl_Enums (const QFlags<enum QStyle::ComplexControl> &v) : m_flags (v) { }
  QFlags<enum QStyle::ComplexControl> flags () const { return m_flags; }
private:
  QFlags<QStyle::ComplexControl> m_flags;
};

//  Wrapper class for enum QStyle::ComplexControl
class QStyle_ComplexControl_Enum : public QStyle_ComplexControl_Enums {
public:
  QStyle_ComplexControl_Enum () { }
  QStyle_ComplexControl_Enum (enum QStyle::ComplexControl v) : QStyle_ComplexControl_Enums (v) { }
  enum QStyle::ComplexControl value () const { return (enum QStyle::ComplexControl) flags ().operator int (); }
};

//  Converter for QFlags<enum QStyle::ComplexControl>
template <>
struct Converter<QFlags<enum QStyle::ComplexControl> >
{
public:
  typedef QFlags<enum QStyle::ComplexControl> source_type;
  typedef QStyle_ComplexControl_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QStyle::ComplexControl
template <>
struct Converter<enum QStyle::ComplexControl>
{
public:
  typedef enum QStyle::ComplexControl source_type;
  typedef QStyle_ComplexControl_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QStyle::ControlElement>
class QStyle_ControlElement_Enums : public QFlags<enum QStyle::ControlElement> {
public:
  QStyle_ControlElement_Enums () : m_flags () { }
  QStyle_ControlElement_Enums (enum QStyle::ControlElement v) : m_flags (v) { }
  QStyle_ControlElement_Enums (const QFlags<enum QStyle::ControlElement> &v) : m_flags (v) { }
  QFlags<enum QStyle::ControlElement> flags () const { return m_flags; }
private:
  QFlags<QStyle::ControlElement> m_flags;
};

//  Wrapper class for enum QStyle::ControlElement
class QStyle_ControlElement_Enum : public QStyle_ControlElement_Enums {
public:
  QStyle_ControlElement_Enum () { }
  QStyle_ControlElement_Enum (enum QStyle::ControlElement v) : QStyle_ControlElement_Enums (v) { }
  enum QStyle::ControlElement value () const { return (enum QStyle::ControlElement) flags ().operator int (); }
};

//  Converter for QFlags<enum QStyle::ControlElement>
template <>
struct Converter<QFlags<enum QStyle::ControlElement> >
{
public:
  typedef QFlags<enum QStyle::ControlElement> source_type;
  typedef QStyle_ControlElement_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QStyle::ControlElement
template <>
struct Converter<enum QStyle::ControlElement>
{
public:
  typedef enum QStyle::ControlElement source_type;
  typedef QStyle_ControlElement_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QStyle::PrimitiveElement>
class QStyle_PrimitiveElement_Enums : public QFlags<enum QStyle::PrimitiveElement> {
public:
  QStyle_PrimitiveElement_Enums () : m_flags () { }
  QStyle_PrimitiveElement_Enums (enum QStyle::PrimitiveElement v) : m_flags (v) { }
  QStyle_PrimitiveElement_Enums (const QFlags<enum QStyle::PrimitiveElement> &v) : m_flags (v) { }
  QFlags<enum QStyle::PrimitiveElement> flags () const { return m_flags; }
private:
  QFlags<QStyle::PrimitiveElement> m_flags;
};

//  Wrapper class for enum QStyle::PrimitiveElement
class QStyle_PrimitiveElement_Enum : public QStyle_PrimitiveElement_Enums {
public:
  QStyle_PrimitiveElement_Enum () { }
  QStyle_PrimitiveElement_Enum (enum QStyle::PrimitiveElement v) : QStyle_PrimitiveElement_Enums (v) { }
  enum QStyle::PrimitiveElement value () const { return (enum QStyle::PrimitiveElement) flags ().operator int (); }
};

//  Converter for QFlags<enum QStyle::PrimitiveElement>
template <>
struct Converter<QFlags<enum QStyle::PrimitiveElement> >
{
public:
  typedef QFlags<enum QStyle::PrimitiveElement> source_type;
  typedef QStyle_PrimitiveElement_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QStyle::PrimitiveElement
template <>
struct Converter<enum QStyle::PrimitiveElement>
{
public:
  typedef enum QStyle::PrimitiveElement source_type;
  typedef QStyle_PrimitiveElement_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::BGMode>
class Qt_BGMode_Enums : public QFlags<enum Qt::BGMode> {
public:
  Qt_BGMode_Enums () : m_flags () { }
  Qt_BGMode_Enums (enum Qt::BGMode v) : m_flags (v) { }
  Qt_BGMode_Enums (const QFlags<enum Qt::BGMode> &v) : m_flags (v) { }
  QFlags<enum Qt::BGMode> flags () const { return m_flags; }
private:
  QFlags<Qt::BGMode> m_flags;
};

//  Wrapper class for enum Qt::BGMode
class Qt_BGMode_Enum : public Qt_BGMode_Enums {
public:
  Qt_BGMode_Enum () { }
  Qt_BGMode_Enum (enum Qt::BGMode v) : Qt_BGMode_Enums (v) { }
  enum Qt::BGMode value () const { return (enum Qt::BGMode) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::BGMode>
template <>
struct Converter<QFlags<enum Qt::BGMode> >
{
public:
  typedef QFlags<enum Qt::BGMode> source_type;
  typedef Qt_BGMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::BGMode
template <>
struct Converter<enum Qt::BGMode>
{
public:
  typedef enum Qt::BGMode source_type;
  typedef Qt_BGMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::BrushStyle>
class Qt_BrushStyle_Enums : public QFlags<enum Qt::BrushStyle> {
public:
  Qt_BrushStyle_Enums () : m_flags () { }
  Qt_BrushStyle_Enums (enum Qt::BrushStyle v) : m_flags (v) { }
  Qt_BrushStyle_Enums (const QFlags<enum Qt::BrushStyle> &v) : m_flags (v) { }
  QFlags<enum Qt::BrushStyle> flags () const { return m_flags; }
private:
  QFlags<Qt::BrushStyle> m_flags;
};

//  Wrapper class for enum Qt::BrushStyle
class Qt_BrushStyle_Enum : public Qt_BrushStyle_Enums {
public:
  Qt_BrushStyle_Enum () { }
  Qt_BrushStyle_Enum (enum Qt::BrushStyle v) : Qt_BrushStyle_Enums (v) { }
  enum Qt::BrushStyle value () const { return (enum Qt::BrushStyle) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::BrushStyle>
template <>
struct Converter<QFlags<enum Qt::BrushStyle> >
{
public:
  typedef QFlags<enum Qt::BrushStyle> source_type;
  typedef Qt_BrushStyle_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::BrushStyle
template <>
struct Converter<enum Qt::BrushStyle>
{
public:
  typedef enum Qt::BrushStyle source_type;
  typedef Qt_BrushStyle_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::ClipOperation>
class Qt_ClipOperation_Enums : public QFlags<enum Qt::ClipOperation> {
public:
  Qt_ClipOperation_Enums () : m_flags () { }
  Qt_ClipOperation_Enums (enum Qt::ClipOperation v) : m_flags (v) { }
  Qt_ClipOperation_Enums (const QFlags<enum Qt::ClipOperation> &v) : m_flags (v) { }
  QFlags<enum Qt::ClipOperation> flags () const { return m_flags; }
private:
  QFlags<Qt::ClipOperation> m_flags;
};

//  Wrapper class for enum Qt::ClipOperation
class Qt_ClipOperation_Enum : public Qt_ClipOperation_Enums {
public:
  Qt_ClipOperation_Enum () { }
  Qt_ClipOperation_Enum (enum Qt::ClipOperation v) : Qt_ClipOperation_Enums (v) { }
  enum Qt::ClipOperation value () const { return (enum Qt::ClipOperation) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::ClipOperation>
template <>
struct Converter<QFlags<enum Qt::ClipOperation> >
{
public:
  typedef QFlags<enum Qt::ClipOperation> source_type;
  typedef Qt_ClipOperation_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::ClipOperation
template <>
struct Converter<enum Qt::ClipOperation>
{
public:
  typedef enum Qt::ClipOperation source_type;
  typedef Qt_ClipOperation_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::FillRule>
class Qt_FillRule_Enums : public QFlags<enum Qt::FillRule> {
public:
  Qt_FillRule_Enums () : m_flags () { }
  Qt_FillRule_Enums (enum Qt::FillRule v) : m_flags (v) { }
  Qt_FillRule_Enums (const QFlags<enum Qt::FillRule> &v) : m_flags (v) { }
  QFlags<enum Qt::FillRule> flags () const { return m_flags; }
private:
  QFlags<Qt::FillRule> m_flags;
};

//  Wrapper class for enum Qt::FillRule
class Qt_FillRule_Enum : public Qt_FillRule_Enums {
public:
  Qt_FillRule_Enum () { }
  Qt_FillRule_Enum (enum Qt::FillRule v) : Qt_FillRule_Enums (v) { }
  enum Qt::FillRule value () const { return (enum Qt::FillRule) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::FillRule>
template <>
struct Converter<QFlags<enum Qt::FillRule> >
{
public:
  typedef QFlags<enum Qt::FillRule> source_type;
  typedef Qt_FillRule_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::FillRule
template <>
struct Converter<enum Qt::FillRule>
{
public:
  typedef enum Qt::FillRule source_type;
  typedef Qt_FillRule_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::GlobalColor>
class Qt_GlobalColor_Enums : public QFlags<enum Qt::GlobalColor> {
public:
  Qt_GlobalColor_Enums () : m_flags () { }
  Qt_GlobalColor_Enums (enum Qt::GlobalColor v) : m_flags (v) { }
  Qt_GlobalColor_Enums (const QFlags<enum Qt::GlobalColor> &v) : m_flags (v) { }
  QFlags<enum Qt::GlobalColor> flags () const { return m_flags; }
private:
  QFlags<Qt::GlobalColor> m_flags;
};

//  Wrapper class for enum Qt::GlobalColor
class Qt_GlobalColor_Enum : public Qt_GlobalColor_Enums {
public:
  Qt_GlobalColor_Enum () { }
  Qt_GlobalColor_Enum (enum Qt::GlobalColor v) : Qt_GlobalColor_Enums (v) { }
  enum Qt::GlobalColor value () const { return (enum Qt::GlobalColor) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::GlobalColor>
template <>
struct Converter<QFlags<enum Qt::GlobalColor> >
{
public:
  typedef QFlags<enum Qt::GlobalColor> source_type;
  typedef Qt_GlobalColor_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::GlobalColor
template <>
struct Converter<enum Qt::GlobalColor>
{
public:
  typedef enum Qt::GlobalColor source_type;
  typedef Qt_GlobalColor_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::ImageConversionFlag>
class Qt_ImageConversionFlag_Enums : public QFlags<enum Qt::ImageConversionFlag> {
public:
  Qt_ImageConversionFlag_Enums () : m_flags () { }
  Qt_ImageConversionFlag_Enums (enum Qt::ImageConversionFlag v) : m_flags (v) { }
  Qt_ImageConversionFlag_Enums (const QFlags<enum Qt::ImageConversionFlag> &v) : m_flags (v) { }
  QFlags<enum Qt::ImageConversionFlag> flags () const { return m_flags; }
private:
  QFlags<Qt::ImageConversionFlag> m_flags;
};

//  Wrapper class for enum Qt::ImageConversionFlag
class Qt_ImageConversionFlag_Enum : public Qt_ImageConversionFlag_Enums {
public:
  Qt_ImageConversionFlag_Enum () { }
  Qt_ImageConversionFlag_Enum (enum Qt::ImageConversionFlag v) : Qt_ImageConversionFlag_Enums (v) { }
  enum Qt::ImageConversionFlag value () const { return (enum Qt::ImageConversionFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::ImageConversionFlag>
template <>
struct Converter<QFlags<enum Qt::ImageConversionFlag> >
{
public:
  typedef QFlags<enum Qt::ImageConversionFlag> source_type;
  typedef Qt_ImageConversionFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::ImageConversionFlag
template <>
struct Converter<enum Qt::ImageConversionFlag>
{
public:
  typedef enum Qt::ImageConversionFlag source_type;
  typedef Qt_ImageConversionFlag_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::LayoutDirection>
class Qt_LayoutDirection_Enums : public QFlags<enum Qt::LayoutDirection> {
public:
  Qt_LayoutDirection_Enums () : m_flags () { }
  Qt_LayoutDirection_Enums (enum Qt::LayoutDirection v) : m_flags (v) { }
  Qt_LayoutDirection_Enums (const QFlags<enum Qt::LayoutDirection> &v) : m_flags (v) { }
  QFlags<enum Qt::LayoutDirection> flags () const { return m_flags; }
private:
  QFlags<Qt::LayoutDirection> m_flags;
};

//  Wrapper class for enum Qt::LayoutDirection
class Qt_LayoutDirection_Enum : public Qt_LayoutDirection_Enums {
public:
  Qt_LayoutDirection_Enum () { }
  Qt_LayoutDirection_Enum (enum Qt::LayoutDirection v) : Qt_LayoutDirection_Enums (v) { }
  enum Qt::LayoutDirection value () const { return (enum Qt::LayoutDirection) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::LayoutDirection>
template <>
struct Converter<QFlags<enum Qt::LayoutDirection> >
{
public:
  typedef QFlags<enum Qt::LayoutDirection> source_type;
  typedef Qt_LayoutDirection_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::LayoutDirection
template <>
struct Converter<enum Qt::LayoutDirection>
{
public:
  typedef enum Qt::LayoutDirection source_type;
  typedef Qt_LayoutDirection_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::PenStyle>
class Qt_PenStyle_Enums : public QFlags<enum Qt::PenStyle> {
public:
  Qt_PenStyle_Enums () : m_flags () { }
  Qt_PenStyle_Enums (enum Qt::PenStyle v) : m_flags (v) { }
  Qt_PenStyle_Enums (const QFlags<enum Qt::PenStyle> &v) : m_flags (v) { }
  QFlags<enum Qt::PenStyle> flags () const { return m_flags; }
private:
  QFlags<Qt::PenStyle> m_flags;
};

//  Wrapper class for enum Qt::PenStyle
class Qt_PenStyle_Enum : public Qt_PenStyle_Enums {
public:
  Qt_PenStyle_Enum () { }
  Qt_PenStyle_Enum (enum Qt::PenStyle v) : Qt_PenStyle_Enums (v) { }
  enum Qt::PenStyle value () const { return (enum Qt::PenStyle) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::PenStyle>
template <>
struct Converter<QFlags<enum Qt::PenStyle> >
{
public:
  typedef QFlags<enum Qt::PenStyle> source_type;
  typedef Qt_PenStyle_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::PenStyle
template <>
struct Converter<enum Qt::PenStyle>
{
public:
  typedef enum Qt::PenStyle source_type;
  typedef Qt_PenStyle_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::SizeMode>
class Qt_SizeMode_Enums : public QFlags<enum Qt::SizeMode> {
public:
  Qt_SizeMode_Enums () : m_flags () { }
  Qt_SizeMode_Enums (enum Qt::SizeMode v) : m_flags (v) { }
  Qt_SizeMode_Enums (const QFlags<enum Qt::SizeMode> &v) : m_flags (v) { }
  QFlags<enum Qt::SizeMode> flags () const { return m_flags; }
private:
  QFlags<Qt::SizeMode> m_flags;
};

//  Wrapper class for enum Qt::SizeMode
class Qt_SizeMode_Enum : public Qt_SizeMode_Enums {
public:
  Qt_SizeMode_Enum () { }
  Qt_SizeMode_Enum (enum Qt::SizeMode v) : Qt_SizeMode_Enums (v) { }
  enum Qt::SizeMode value () const { return (enum Qt::SizeMode) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::SizeMode>
template <>
struct Converter<QFlags<enum Qt::SizeMode> >
{
public:
  typedef QFlags<enum Qt::SizeMode> source_type;
  typedef Qt_SizeMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::SizeMode
template <>
struct Converter<enum Qt::SizeMode>
{
public:
  typedef enum Qt::SizeMode source_type;
  typedef Qt_SizeMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
