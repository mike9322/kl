
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
*  @file gsiDeclQPrinter_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQPrinter_Enums
#define _HDR_gsiDeclQPrinter_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QPaintDevice::PaintDeviceMetric>
class QPaintDevice_PaintDeviceMetric_Enums : public QFlags<enum QPaintDevice::PaintDeviceMetric> {
public:
  QPaintDevice_PaintDeviceMetric_Enums () : m_flags () { }
  QPaintDevice_PaintDeviceMetric_Enums (enum QPaintDevice::PaintDeviceMetric v) : m_flags (v) { }
  QPaintDevice_PaintDeviceMetric_Enums (const QFlags<enum QPaintDevice::PaintDeviceMetric> &v) : m_flags (v) { }
  QFlags<enum QPaintDevice::PaintDeviceMetric> flags () const { return m_flags; }
private:
  QFlags<QPaintDevice::PaintDeviceMetric> m_flags;
};

//  Wrapper class for enum QPaintDevice::PaintDeviceMetric
class QPaintDevice_PaintDeviceMetric_Enum : public QPaintDevice_PaintDeviceMetric_Enums {
public:
  QPaintDevice_PaintDeviceMetric_Enum () { }
  QPaintDevice_PaintDeviceMetric_Enum (enum QPaintDevice::PaintDeviceMetric v) : QPaintDevice_PaintDeviceMetric_Enums (v) { }
  enum QPaintDevice::PaintDeviceMetric value () const { return (enum QPaintDevice::PaintDeviceMetric) flags ().operator int (); }
};

//  Converter for QFlags<enum QPaintDevice::PaintDeviceMetric>
template <>
struct Converter<QFlags<enum QPaintDevice::PaintDeviceMetric> >
{
public:
  typedef QFlags<enum QPaintDevice::PaintDeviceMetric> source_type;
  typedef QPaintDevice_PaintDeviceMetric_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPaintDevice::PaintDeviceMetric
template <>
struct Converter<enum QPaintDevice::PaintDeviceMetric>
{
public:
  typedef enum QPaintDevice::PaintDeviceMetric source_type;
  typedef QPaintDevice_PaintDeviceMetric_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::ColorMode>
class QPrinter_ColorMode_Enums : public QFlags<enum QPrinter::ColorMode> {
public:
  QPrinter_ColorMode_Enums () : m_flags () { }
  QPrinter_ColorMode_Enums (enum QPrinter::ColorMode v) : m_flags (v) { }
  QPrinter_ColorMode_Enums (const QFlags<enum QPrinter::ColorMode> &v) : m_flags (v) { }
  QFlags<enum QPrinter::ColorMode> flags () const { return m_flags; }
private:
  QFlags<QPrinter::ColorMode> m_flags;
};

//  Wrapper class for enum QPrinter::ColorMode
class QPrinter_ColorMode_Enum : public QPrinter_ColorMode_Enums {
public:
  QPrinter_ColorMode_Enum () { }
  QPrinter_ColorMode_Enum (enum QPrinter::ColorMode v) : QPrinter_ColorMode_Enums (v) { }
  enum QPrinter::ColorMode value () const { return (enum QPrinter::ColorMode) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::ColorMode>
template <>
struct Converter<QFlags<enum QPrinter::ColorMode> >
{
public:
  typedef QFlags<enum QPrinter::ColorMode> source_type;
  typedef QPrinter_ColorMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::ColorMode
template <>
struct Converter<enum QPrinter::ColorMode>
{
public:
  typedef enum QPrinter::ColorMode source_type;
  typedef QPrinter_ColorMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::DuplexMode>
class QPrinter_DuplexMode_Enums : public QFlags<enum QPrinter::DuplexMode> {
public:
  QPrinter_DuplexMode_Enums () : m_flags () { }
  QPrinter_DuplexMode_Enums (enum QPrinter::DuplexMode v) : m_flags (v) { }
  QPrinter_DuplexMode_Enums (const QFlags<enum QPrinter::DuplexMode> &v) : m_flags (v) { }
  QFlags<enum QPrinter::DuplexMode> flags () const { return m_flags; }
private:
  QFlags<QPrinter::DuplexMode> m_flags;
};

//  Wrapper class for enum QPrinter::DuplexMode
class QPrinter_DuplexMode_Enum : public QPrinter_DuplexMode_Enums {
public:
  QPrinter_DuplexMode_Enum () { }
  QPrinter_DuplexMode_Enum (enum QPrinter::DuplexMode v) : QPrinter_DuplexMode_Enums (v) { }
  enum QPrinter::DuplexMode value () const { return (enum QPrinter::DuplexMode) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::DuplexMode>
template <>
struct Converter<QFlags<enum QPrinter::DuplexMode> >
{
public:
  typedef QFlags<enum QPrinter::DuplexMode> source_type;
  typedef QPrinter_DuplexMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::DuplexMode
template <>
struct Converter<enum QPrinter::DuplexMode>
{
public:
  typedef enum QPrinter::DuplexMode source_type;
  typedef QPrinter_DuplexMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::Orientation>
class QPrinter_Orientation_Enums : public QFlags<enum QPrinter::Orientation> {
public:
  QPrinter_Orientation_Enums () : m_flags () { }
  QPrinter_Orientation_Enums (enum QPrinter::Orientation v) : m_flags (v) { }
  QPrinter_Orientation_Enums (const QFlags<enum QPrinter::Orientation> &v) : m_flags (v) { }
  QFlags<enum QPrinter::Orientation> flags () const { return m_flags; }
private:
  QFlags<QPrinter::Orientation> m_flags;
};

//  Wrapper class for enum QPrinter::Orientation
class QPrinter_Orientation_Enum : public QPrinter_Orientation_Enums {
public:
  QPrinter_Orientation_Enum () { }
  QPrinter_Orientation_Enum (enum QPrinter::Orientation v) : QPrinter_Orientation_Enums (v) { }
  enum QPrinter::Orientation value () const { return (enum QPrinter::Orientation) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::Orientation>
template <>
struct Converter<QFlags<enum QPrinter::Orientation> >
{
public:
  typedef QFlags<enum QPrinter::Orientation> source_type;
  typedef QPrinter_Orientation_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::Orientation
template <>
struct Converter<enum QPrinter::Orientation>
{
public:
  typedef enum QPrinter::Orientation source_type;
  typedef QPrinter_Orientation_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::OutputFormat>
class QPrinter_OutputFormat_Enums : public QFlags<enum QPrinter::OutputFormat> {
public:
  QPrinter_OutputFormat_Enums () : m_flags () { }
  QPrinter_OutputFormat_Enums (enum QPrinter::OutputFormat v) : m_flags (v) { }
  QPrinter_OutputFormat_Enums (const QFlags<enum QPrinter::OutputFormat> &v) : m_flags (v) { }
  QFlags<enum QPrinter::OutputFormat> flags () const { return m_flags; }
private:
  QFlags<QPrinter::OutputFormat> m_flags;
};

//  Wrapper class for enum QPrinter::OutputFormat
class QPrinter_OutputFormat_Enum : public QPrinter_OutputFormat_Enums {
public:
  QPrinter_OutputFormat_Enum () { }
  QPrinter_OutputFormat_Enum (enum QPrinter::OutputFormat v) : QPrinter_OutputFormat_Enums (v) { }
  enum QPrinter::OutputFormat value () const { return (enum QPrinter::OutputFormat) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::OutputFormat>
template <>
struct Converter<QFlags<enum QPrinter::OutputFormat> >
{
public:
  typedef QFlags<enum QPrinter::OutputFormat> source_type;
  typedef QPrinter_OutputFormat_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::OutputFormat
template <>
struct Converter<enum QPrinter::OutputFormat>
{
public:
  typedef enum QPrinter::OutputFormat source_type;
  typedef QPrinter_OutputFormat_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::PageOrder>
class QPrinter_PageOrder_Enums : public QFlags<enum QPrinter::PageOrder> {
public:
  QPrinter_PageOrder_Enums () : m_flags () { }
  QPrinter_PageOrder_Enums (enum QPrinter::PageOrder v) : m_flags (v) { }
  QPrinter_PageOrder_Enums (const QFlags<enum QPrinter::PageOrder> &v) : m_flags (v) { }
  QFlags<enum QPrinter::PageOrder> flags () const { return m_flags; }
private:
  QFlags<QPrinter::PageOrder> m_flags;
};

//  Wrapper class for enum QPrinter::PageOrder
class QPrinter_PageOrder_Enum : public QPrinter_PageOrder_Enums {
public:
  QPrinter_PageOrder_Enum () { }
  QPrinter_PageOrder_Enum (enum QPrinter::PageOrder v) : QPrinter_PageOrder_Enums (v) { }
  enum QPrinter::PageOrder value () const { return (enum QPrinter::PageOrder) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::PageOrder>
template <>
struct Converter<QFlags<enum QPrinter::PageOrder> >
{
public:
  typedef QFlags<enum QPrinter::PageOrder> source_type;
  typedef QPrinter_PageOrder_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::PageOrder
template <>
struct Converter<enum QPrinter::PageOrder>
{
public:
  typedef enum QPrinter::PageOrder source_type;
  typedef QPrinter_PageOrder_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::PageSize>
class QPrinter_PageSize_Enums : public QFlags<enum QPrinter::PageSize> {
public:
  QPrinter_PageSize_Enums () : m_flags () { }
  QPrinter_PageSize_Enums (enum QPrinter::PageSize v) : m_flags (v) { }
  QPrinter_PageSize_Enums (const QFlags<enum QPrinter::PageSize> &v) : m_flags (v) { }
  QFlags<enum QPrinter::PageSize> flags () const { return m_flags; }
private:
  QFlags<QPrinter::PageSize> m_flags;
};

//  Wrapper class for enum QPrinter::PageSize
class QPrinter_PageSize_Enum : public QPrinter_PageSize_Enums {
public:
  QPrinter_PageSize_Enum () { }
  QPrinter_PageSize_Enum (enum QPrinter::PageSize v) : QPrinter_PageSize_Enums (v) { }
  enum QPrinter::PageSize value () const { return (enum QPrinter::PageSize) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::PageSize>
template <>
struct Converter<QFlags<enum QPrinter::PageSize> >
{
public:
  typedef QFlags<enum QPrinter::PageSize> source_type;
  typedef QPrinter_PageSize_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::PageSize
template <>
struct Converter<enum QPrinter::PageSize>
{
public:
  typedef enum QPrinter::PageSize source_type;
  typedef QPrinter_PageSize_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::PaperSource>
class QPrinter_PaperSource_Enums : public QFlags<enum QPrinter::PaperSource> {
public:
  QPrinter_PaperSource_Enums () : m_flags () { }
  QPrinter_PaperSource_Enums (enum QPrinter::PaperSource v) : m_flags (v) { }
  QPrinter_PaperSource_Enums (const QFlags<enum QPrinter::PaperSource> &v) : m_flags (v) { }
  QFlags<enum QPrinter::PaperSource> flags () const { return m_flags; }
private:
  QFlags<QPrinter::PaperSource> m_flags;
};

//  Wrapper class for enum QPrinter::PaperSource
class QPrinter_PaperSource_Enum : public QPrinter_PaperSource_Enums {
public:
  QPrinter_PaperSource_Enum () { }
  QPrinter_PaperSource_Enum (enum QPrinter::PaperSource v) : QPrinter_PaperSource_Enums (v) { }
  enum QPrinter::PaperSource value () const { return (enum QPrinter::PaperSource) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::PaperSource>
template <>
struct Converter<QFlags<enum QPrinter::PaperSource> >
{
public:
  typedef QFlags<enum QPrinter::PaperSource> source_type;
  typedef QPrinter_PaperSource_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::PaperSource
template <>
struct Converter<enum QPrinter::PaperSource>
{
public:
  typedef enum QPrinter::PaperSource source_type;
  typedef QPrinter_PaperSource_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::PrintRange>
class QPrinter_PrintRange_Enums : public QFlags<enum QPrinter::PrintRange> {
public:
  QPrinter_PrintRange_Enums () : m_flags () { }
  QPrinter_PrintRange_Enums (enum QPrinter::PrintRange v) : m_flags (v) { }
  QPrinter_PrintRange_Enums (const QFlags<enum QPrinter::PrintRange> &v) : m_flags (v) { }
  QFlags<enum QPrinter::PrintRange> flags () const { return m_flags; }
private:
  QFlags<QPrinter::PrintRange> m_flags;
};

//  Wrapper class for enum QPrinter::PrintRange
class QPrinter_PrintRange_Enum : public QPrinter_PrintRange_Enums {
public:
  QPrinter_PrintRange_Enum () { }
  QPrinter_PrintRange_Enum (enum QPrinter::PrintRange v) : QPrinter_PrintRange_Enums (v) { }
  enum QPrinter::PrintRange value () const { return (enum QPrinter::PrintRange) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::PrintRange>
template <>
struct Converter<QFlags<enum QPrinter::PrintRange> >
{
public:
  typedef QFlags<enum QPrinter::PrintRange> source_type;
  typedef QPrinter_PrintRange_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::PrintRange
template <>
struct Converter<enum QPrinter::PrintRange>
{
public:
  typedef enum QPrinter::PrintRange source_type;
  typedef QPrinter_PrintRange_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::PrinterMode>
class QPrinter_PrinterMode_Enums : public QFlags<enum QPrinter::PrinterMode> {
public:
  QPrinter_PrinterMode_Enums () : m_flags () { }
  QPrinter_PrinterMode_Enums (enum QPrinter::PrinterMode v) : m_flags (v) { }
  QPrinter_PrinterMode_Enums (const QFlags<enum QPrinter::PrinterMode> &v) : m_flags (v) { }
  QFlags<enum QPrinter::PrinterMode> flags () const { return m_flags; }
private:
  QFlags<QPrinter::PrinterMode> m_flags;
};

//  Wrapper class for enum QPrinter::PrinterMode
class QPrinter_PrinterMode_Enum : public QPrinter_PrinterMode_Enums {
public:
  QPrinter_PrinterMode_Enum () { }
  QPrinter_PrinterMode_Enum (enum QPrinter::PrinterMode v) : QPrinter_PrinterMode_Enums (v) { }
  enum QPrinter::PrinterMode value () const { return (enum QPrinter::PrinterMode) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::PrinterMode>
template <>
struct Converter<QFlags<enum QPrinter::PrinterMode> >
{
public:
  typedef QFlags<enum QPrinter::PrinterMode> source_type;
  typedef QPrinter_PrinterMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::PrinterMode
template <>
struct Converter<enum QPrinter::PrinterMode>
{
public:
  typedef enum QPrinter::PrinterMode source_type;
  typedef QPrinter_PrinterMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::PrinterState>
class QPrinter_PrinterState_Enums : public QFlags<enum QPrinter::PrinterState> {
public:
  QPrinter_PrinterState_Enums () : m_flags () { }
  QPrinter_PrinterState_Enums (enum QPrinter::PrinterState v) : m_flags (v) { }
  QPrinter_PrinterState_Enums (const QFlags<enum QPrinter::PrinterState> &v) : m_flags (v) { }
  QFlags<enum QPrinter::PrinterState> flags () const { return m_flags; }
private:
  QFlags<QPrinter::PrinterState> m_flags;
};

//  Wrapper class for enum QPrinter::PrinterState
class QPrinter_PrinterState_Enum : public QPrinter_PrinterState_Enums {
public:
  QPrinter_PrinterState_Enum () { }
  QPrinter_PrinterState_Enum (enum QPrinter::PrinterState v) : QPrinter_PrinterState_Enums (v) { }
  enum QPrinter::PrinterState value () const { return (enum QPrinter::PrinterState) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::PrinterState>
template <>
struct Converter<QFlags<enum QPrinter::PrinterState> >
{
public:
  typedef QFlags<enum QPrinter::PrinterState> source_type;
  typedef QPrinter_PrinterState_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::PrinterState
template <>
struct Converter<enum QPrinter::PrinterState>
{
public:
  typedef enum QPrinter::PrinterState source_type;
  typedef QPrinter_PrinterState_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QPrinter::Unit>
class QPrinter_Unit_Enums : public QFlags<enum QPrinter::Unit> {
public:
  QPrinter_Unit_Enums () : m_flags () { }
  QPrinter_Unit_Enums (enum QPrinter::Unit v) : m_flags (v) { }
  QPrinter_Unit_Enums (const QFlags<enum QPrinter::Unit> &v) : m_flags (v) { }
  QFlags<enum QPrinter::Unit> flags () const { return m_flags; }
private:
  QFlags<QPrinter::Unit> m_flags;
};

//  Wrapper class for enum QPrinter::Unit
class QPrinter_Unit_Enum : public QPrinter_Unit_Enums {
public:
  QPrinter_Unit_Enum () { }
  QPrinter_Unit_Enum (enum QPrinter::Unit v) : QPrinter_Unit_Enums (v) { }
  enum QPrinter::Unit value () const { return (enum QPrinter::Unit) flags ().operator int (); }
};

//  Converter for QFlags<enum QPrinter::Unit>
template <>
struct Converter<QFlags<enum QPrinter::Unit> >
{
public:
  typedef QFlags<enum QPrinter::Unit> source_type;
  typedef QPrinter_Unit_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPrinter::Unit
template <>
struct Converter<enum QPrinter::Unit>
{
public:
  typedef enum QPrinter::Unit source_type;
  typedef QPrinter_Unit_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
