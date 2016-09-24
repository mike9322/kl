
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
*  @file gsiDeclQCommandLinkButton_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQCommandLinkButton_Enums
#define _HDR_gsiDeclQCommandLinkButton_Enums

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

//  Wrapper class for QFlags<enum QSizePolicy::Policy>
class QSizePolicy_Policy_Enums : public QFlags<enum QSizePolicy::Policy> {
public:
  QSizePolicy_Policy_Enums () : m_flags () { }
  QSizePolicy_Policy_Enums (enum QSizePolicy::Policy v) : m_flags (v) { }
  QSizePolicy_Policy_Enums (const QFlags<enum QSizePolicy::Policy> &v) : m_flags (v) { }
  QFlags<enum QSizePolicy::Policy> flags () const { return m_flags; }
private:
  QFlags<QSizePolicy::Policy> m_flags;
};

//  Wrapper class for enum QSizePolicy::Policy
class QSizePolicy_Policy_Enum : public QSizePolicy_Policy_Enums {
public:
  QSizePolicy_Policy_Enum () { }
  QSizePolicy_Policy_Enum (enum QSizePolicy::Policy v) : QSizePolicy_Policy_Enums (v) { }
  enum QSizePolicy::Policy value () const { return (enum QSizePolicy::Policy) flags ().operator int (); }
};

//  Converter for QFlags<enum QSizePolicy::Policy>
template <>
struct Converter<QFlags<enum QSizePolicy::Policy> >
{
public:
  typedef QFlags<enum QSizePolicy::Policy> source_type;
  typedef QSizePolicy_Policy_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QSizePolicy::Policy
template <>
struct Converter<enum QSizePolicy::Policy>
{
public:
  typedef enum QSizePolicy::Policy source_type;
  typedef QSizePolicy_Policy_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QWidget::RenderFlag>
class QWidget_RenderFlag_Enums : public QFlags<enum QWidget::RenderFlag> {
public:
  QWidget_RenderFlag_Enums () : m_flags () { }
  QWidget_RenderFlag_Enums (enum QWidget::RenderFlag v) : m_flags (v) { }
  QWidget_RenderFlag_Enums (const QFlags<enum QWidget::RenderFlag> &v) : m_flags (v) { }
  QFlags<enum QWidget::RenderFlag> flags () const { return m_flags; }
private:
  QFlags<QWidget::RenderFlag> m_flags;
};

//  Wrapper class for enum QWidget::RenderFlag
class QWidget_RenderFlag_Enum : public QWidget_RenderFlag_Enums {
public:
  QWidget_RenderFlag_Enum () { }
  QWidget_RenderFlag_Enum (enum QWidget::RenderFlag v) : QWidget_RenderFlag_Enums (v) { }
  enum QWidget::RenderFlag value () const { return (enum QWidget::RenderFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum QWidget::RenderFlag>
template <>
struct Converter<QFlags<enum QWidget::RenderFlag> >
{
public:
  typedef QFlags<enum QWidget::RenderFlag> source_type;
  typedef QWidget_RenderFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QWidget::RenderFlag
template <>
struct Converter<enum QWidget::RenderFlag>
{
public:
  typedef enum QWidget::RenderFlag source_type;
  typedef QWidget_RenderFlag_Enum target_type;
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

//  Wrapper class for QFlags<enum Qt::ContextMenuPolicy>
class Qt_ContextMenuPolicy_Enums : public QFlags<enum Qt::ContextMenuPolicy> {
public:
  Qt_ContextMenuPolicy_Enums () : m_flags () { }
  Qt_ContextMenuPolicy_Enums (enum Qt::ContextMenuPolicy v) : m_flags (v) { }
  Qt_ContextMenuPolicy_Enums (const QFlags<enum Qt::ContextMenuPolicy> &v) : m_flags (v) { }
  QFlags<enum Qt::ContextMenuPolicy> flags () const { return m_flags; }
private:
  QFlags<Qt::ContextMenuPolicy> m_flags;
};

//  Wrapper class for enum Qt::ContextMenuPolicy
class Qt_ContextMenuPolicy_Enum : public Qt_ContextMenuPolicy_Enums {
public:
  Qt_ContextMenuPolicy_Enum () { }
  Qt_ContextMenuPolicy_Enum (enum Qt::ContextMenuPolicy v) : Qt_ContextMenuPolicy_Enums (v) { }
  enum Qt::ContextMenuPolicy value () const { return (enum Qt::ContextMenuPolicy) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::ContextMenuPolicy>
template <>
struct Converter<QFlags<enum Qt::ContextMenuPolicy> >
{
public:
  typedef QFlags<enum Qt::ContextMenuPolicy> source_type;
  typedef Qt_ContextMenuPolicy_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::ContextMenuPolicy
template <>
struct Converter<enum Qt::ContextMenuPolicy>
{
public:
  typedef enum Qt::ContextMenuPolicy source_type;
  typedef Qt_ContextMenuPolicy_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::FocusPolicy>
class Qt_FocusPolicy_Enums : public QFlags<enum Qt::FocusPolicy> {
public:
  Qt_FocusPolicy_Enums () : m_flags () { }
  Qt_FocusPolicy_Enums (enum Qt::FocusPolicy v) : m_flags (v) { }
  Qt_FocusPolicy_Enums (const QFlags<enum Qt::FocusPolicy> &v) : m_flags (v) { }
  QFlags<enum Qt::FocusPolicy> flags () const { return m_flags; }
private:
  QFlags<Qt::FocusPolicy> m_flags;
};

//  Wrapper class for enum Qt::FocusPolicy
class Qt_FocusPolicy_Enum : public Qt_FocusPolicy_Enums {
public:
  Qt_FocusPolicy_Enum () { }
  Qt_FocusPolicy_Enum (enum Qt::FocusPolicy v) : Qt_FocusPolicy_Enums (v) { }
  enum Qt::FocusPolicy value () const { return (enum Qt::FocusPolicy) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::FocusPolicy>
template <>
struct Converter<QFlags<enum Qt::FocusPolicy> >
{
public:
  typedef QFlags<enum Qt::FocusPolicy> source_type;
  typedef Qt_FocusPolicy_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::FocusPolicy
template <>
struct Converter<enum Qt::FocusPolicy>
{
public:
  typedef enum Qt::FocusPolicy source_type;
  typedef Qt_FocusPolicy_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::FocusReason>
class Qt_FocusReason_Enums : public QFlags<enum Qt::FocusReason> {
public:
  Qt_FocusReason_Enums () : m_flags () { }
  Qt_FocusReason_Enums (enum Qt::FocusReason v) : m_flags (v) { }
  Qt_FocusReason_Enums (const QFlags<enum Qt::FocusReason> &v) : m_flags (v) { }
  QFlags<enum Qt::FocusReason> flags () const { return m_flags; }
private:
  QFlags<Qt::FocusReason> m_flags;
};

//  Wrapper class for enum Qt::FocusReason
class Qt_FocusReason_Enum : public Qt_FocusReason_Enums {
public:
  Qt_FocusReason_Enum () { }
  Qt_FocusReason_Enum (enum Qt::FocusReason v) : Qt_FocusReason_Enums (v) { }
  enum Qt::FocusReason value () const { return (enum Qt::FocusReason) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::FocusReason>
template <>
struct Converter<QFlags<enum Qt::FocusReason> >
{
public:
  typedef QFlags<enum Qt::FocusReason> source_type;
  typedef Qt_FocusReason_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::FocusReason
template <>
struct Converter<enum Qt::FocusReason>
{
public:
  typedef enum Qt::FocusReason source_type;
  typedef Qt_FocusReason_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::GestureFlag>
class Qt_GestureFlag_Enums : public QFlags<enum Qt::GestureFlag> {
public:
  Qt_GestureFlag_Enums () : m_flags () { }
  Qt_GestureFlag_Enums (enum Qt::GestureFlag v) : m_flags (v) { }
  Qt_GestureFlag_Enums (const QFlags<enum Qt::GestureFlag> &v) : m_flags (v) { }
  QFlags<enum Qt::GestureFlag> flags () const { return m_flags; }
private:
  QFlags<Qt::GestureFlag> m_flags;
};

//  Wrapper class for enum Qt::GestureFlag
class Qt_GestureFlag_Enum : public Qt_GestureFlag_Enums {
public:
  Qt_GestureFlag_Enum () { }
  Qt_GestureFlag_Enum (enum Qt::GestureFlag v) : Qt_GestureFlag_Enums (v) { }
  enum Qt::GestureFlag value () const { return (enum Qt::GestureFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::GestureFlag>
template <>
struct Converter<QFlags<enum Qt::GestureFlag> >
{
public:
  typedef QFlags<enum Qt::GestureFlag> source_type;
  typedef Qt_GestureFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::GestureFlag
template <>
struct Converter<enum Qt::GestureFlag>
{
public:
  typedef enum Qt::GestureFlag source_type;
  typedef Qt_GestureFlag_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::GestureType>
class Qt_GestureType_Enums : public QFlags<enum Qt::GestureType> {
public:
  Qt_GestureType_Enums () : m_flags () { }
  Qt_GestureType_Enums (enum Qt::GestureType v) : m_flags (v) { }
  Qt_GestureType_Enums (const QFlags<enum Qt::GestureType> &v) : m_flags (v) { }
  QFlags<enum Qt::GestureType> flags () const { return m_flags; }
private:
  QFlags<Qt::GestureType> m_flags;
};

//  Wrapper class for enum Qt::GestureType
class Qt_GestureType_Enum : public Qt_GestureType_Enums {
public:
  Qt_GestureType_Enum () { }
  Qt_GestureType_Enum (enum Qt::GestureType v) : Qt_GestureType_Enums (v) { }
  enum Qt::GestureType value () const { return (enum Qt::GestureType) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::GestureType>
template <>
struct Converter<QFlags<enum Qt::GestureType> >
{
public:
  typedef QFlags<enum Qt::GestureType> source_type;
  typedef Qt_GestureType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::GestureType
template <>
struct Converter<enum Qt::GestureType>
{
public:
  typedef enum Qt::GestureType source_type;
  typedef Qt_GestureType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::InputMethodHint>
class Qt_InputMethodHint_Enums : public QFlags<enum Qt::InputMethodHint> {
public:
  Qt_InputMethodHint_Enums () : m_flags () { }
  Qt_InputMethodHint_Enums (enum Qt::InputMethodHint v) : m_flags (v) { }
  Qt_InputMethodHint_Enums (const QFlags<enum Qt::InputMethodHint> &v) : m_flags (v) { }
  QFlags<enum Qt::InputMethodHint> flags () const { return m_flags; }
private:
  QFlags<Qt::InputMethodHint> m_flags;
};

//  Wrapper class for enum Qt::InputMethodHint
class Qt_InputMethodHint_Enum : public Qt_InputMethodHint_Enums {
public:
  Qt_InputMethodHint_Enum () { }
  Qt_InputMethodHint_Enum (enum Qt::InputMethodHint v) : Qt_InputMethodHint_Enums (v) { }
  enum Qt::InputMethodHint value () const { return (enum Qt::InputMethodHint) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::InputMethodHint>
template <>
struct Converter<QFlags<enum Qt::InputMethodHint> >
{
public:
  typedef QFlags<enum Qt::InputMethodHint> source_type;
  typedef Qt_InputMethodHint_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::InputMethodHint
template <>
struct Converter<enum Qt::InputMethodHint>
{
public:
  typedef enum Qt::InputMethodHint source_type;
  typedef Qt_InputMethodHint_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::InputMethodQuery>
class Qt_InputMethodQuery_Enums : public QFlags<enum Qt::InputMethodQuery> {
public:
  Qt_InputMethodQuery_Enums () : m_flags () { }
  Qt_InputMethodQuery_Enums (enum Qt::InputMethodQuery v) : m_flags (v) { }
  Qt_InputMethodQuery_Enums (const QFlags<enum Qt::InputMethodQuery> &v) : m_flags (v) { }
  QFlags<enum Qt::InputMethodQuery> flags () const { return m_flags; }
private:
  QFlags<Qt::InputMethodQuery> m_flags;
};

//  Wrapper class for enum Qt::InputMethodQuery
class Qt_InputMethodQuery_Enum : public Qt_InputMethodQuery_Enums {
public:
  Qt_InputMethodQuery_Enum () { }
  Qt_InputMethodQuery_Enum (enum Qt::InputMethodQuery v) : Qt_InputMethodQuery_Enums (v) { }
  enum Qt::InputMethodQuery value () const { return (enum Qt::InputMethodQuery) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::InputMethodQuery>
template <>
struct Converter<QFlags<enum Qt::InputMethodQuery> >
{
public:
  typedef QFlags<enum Qt::InputMethodQuery> source_type;
  typedef Qt_InputMethodQuery_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::InputMethodQuery
template <>
struct Converter<enum Qt::InputMethodQuery>
{
public:
  typedef enum Qt::InputMethodQuery source_type;
  typedef Qt_InputMethodQuery_Enum target_type;
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

//  Wrapper class for QFlags<enum Qt::ShortcutContext>
class Qt_ShortcutContext_Enums : public QFlags<enum Qt::ShortcutContext> {
public:
  Qt_ShortcutContext_Enums () : m_flags () { }
  Qt_ShortcutContext_Enums (enum Qt::ShortcutContext v) : m_flags (v) { }
  Qt_ShortcutContext_Enums (const QFlags<enum Qt::ShortcutContext> &v) : m_flags (v) { }
  QFlags<enum Qt::ShortcutContext> flags () const { return m_flags; }
private:
  QFlags<Qt::ShortcutContext> m_flags;
};

//  Wrapper class for enum Qt::ShortcutContext
class Qt_ShortcutContext_Enum : public Qt_ShortcutContext_Enums {
public:
  Qt_ShortcutContext_Enum () { }
  Qt_ShortcutContext_Enum (enum Qt::ShortcutContext v) : Qt_ShortcutContext_Enums (v) { }
  enum Qt::ShortcutContext value () const { return (enum Qt::ShortcutContext) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::ShortcutContext>
template <>
struct Converter<QFlags<enum Qt::ShortcutContext> >
{
public:
  typedef QFlags<enum Qt::ShortcutContext> source_type;
  typedef Qt_ShortcutContext_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::ShortcutContext
template <>
struct Converter<enum Qt::ShortcutContext>
{
public:
  typedef enum Qt::ShortcutContext source_type;
  typedef Qt_ShortcutContext_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::WidgetAttribute>
class Qt_WidgetAttribute_Enums : public QFlags<enum Qt::WidgetAttribute> {
public:
  Qt_WidgetAttribute_Enums () : m_flags () { }
  Qt_WidgetAttribute_Enums (enum Qt::WidgetAttribute v) : m_flags (v) { }
  Qt_WidgetAttribute_Enums (const QFlags<enum Qt::WidgetAttribute> &v) : m_flags (v) { }
  QFlags<enum Qt::WidgetAttribute> flags () const { return m_flags; }
private:
  QFlags<Qt::WidgetAttribute> m_flags;
};

//  Wrapper class for enum Qt::WidgetAttribute
class Qt_WidgetAttribute_Enum : public Qt_WidgetAttribute_Enums {
public:
  Qt_WidgetAttribute_Enum () { }
  Qt_WidgetAttribute_Enum (enum Qt::WidgetAttribute v) : Qt_WidgetAttribute_Enums (v) { }
  enum Qt::WidgetAttribute value () const { return (enum Qt::WidgetAttribute) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::WidgetAttribute>
template <>
struct Converter<QFlags<enum Qt::WidgetAttribute> >
{
public:
  typedef QFlags<enum Qt::WidgetAttribute> source_type;
  typedef Qt_WidgetAttribute_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::WidgetAttribute
template <>
struct Converter<enum Qt::WidgetAttribute>
{
public:
  typedef enum Qt::WidgetAttribute source_type;
  typedef Qt_WidgetAttribute_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::WindowModality>
class Qt_WindowModality_Enums : public QFlags<enum Qt::WindowModality> {
public:
  Qt_WindowModality_Enums () : m_flags () { }
  Qt_WindowModality_Enums (enum Qt::WindowModality v) : m_flags (v) { }
  Qt_WindowModality_Enums (const QFlags<enum Qt::WindowModality> &v) : m_flags (v) { }
  QFlags<enum Qt::WindowModality> flags () const { return m_flags; }
private:
  QFlags<Qt::WindowModality> m_flags;
};

//  Wrapper class for enum Qt::WindowModality
class Qt_WindowModality_Enum : public Qt_WindowModality_Enums {
public:
  Qt_WindowModality_Enum () { }
  Qt_WindowModality_Enum (enum Qt::WindowModality v) : Qt_WindowModality_Enums (v) { }
  enum Qt::WindowModality value () const { return (enum Qt::WindowModality) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::WindowModality>
template <>
struct Converter<QFlags<enum Qt::WindowModality> >
{
public:
  typedef QFlags<enum Qt::WindowModality> source_type;
  typedef Qt_WindowModality_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::WindowModality
template <>
struct Converter<enum Qt::WindowModality>
{
public:
  typedef enum Qt::WindowModality source_type;
  typedef Qt_WindowModality_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::WindowState>
class Qt_WindowState_Enums : public QFlags<enum Qt::WindowState> {
public:
  Qt_WindowState_Enums () : m_flags () { }
  Qt_WindowState_Enums (enum Qt::WindowState v) : m_flags (v) { }
  Qt_WindowState_Enums (const QFlags<enum Qt::WindowState> &v) : m_flags (v) { }
  QFlags<enum Qt::WindowState> flags () const { return m_flags; }
private:
  QFlags<Qt::WindowState> m_flags;
};

//  Wrapper class for enum Qt::WindowState
class Qt_WindowState_Enum : public Qt_WindowState_Enums {
public:
  Qt_WindowState_Enum () { }
  Qt_WindowState_Enum (enum Qt::WindowState v) : Qt_WindowState_Enums (v) { }
  enum Qt::WindowState value () const { return (enum Qt::WindowState) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::WindowState>
template <>
struct Converter<QFlags<enum Qt::WindowState> >
{
public:
  typedef QFlags<enum Qt::WindowState> source_type;
  typedef Qt_WindowState_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::WindowState
template <>
struct Converter<enum Qt::WindowState>
{
public:
  typedef enum Qt::WindowState source_type;
  typedef Qt_WindowState_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::WindowType>
class Qt_WindowType_Enums : public QFlags<enum Qt::WindowType> {
public:
  Qt_WindowType_Enums () : m_flags () { }
  Qt_WindowType_Enums (enum Qt::WindowType v) : m_flags (v) { }
  Qt_WindowType_Enums (const QFlags<enum Qt::WindowType> &v) : m_flags (v) { }
  QFlags<enum Qt::WindowType> flags () const { return m_flags; }
private:
  QFlags<Qt::WindowType> m_flags;
};

//  Wrapper class for enum Qt::WindowType
class Qt_WindowType_Enum : public Qt_WindowType_Enums {
public:
  Qt_WindowType_Enum () { }
  Qt_WindowType_Enum (enum Qt::WindowType v) : Qt_WindowType_Enums (v) { }
  enum Qt::WindowType value () const { return (enum Qt::WindowType) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::WindowType>
template <>
struct Converter<QFlags<enum Qt::WindowType> >
{
public:
  typedef QFlags<enum Qt::WindowType> source_type;
  typedef Qt_WindowType_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::WindowType
template <>
struct Converter<enum Qt::WindowType>
{
public:
  typedef enum Qt::WindowType source_type;
  typedef Qt_WindowType_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
