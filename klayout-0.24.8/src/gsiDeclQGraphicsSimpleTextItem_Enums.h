
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
*  @file gsiDeclQGraphicsSimpleTextItem_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQGraphicsSimpleTextItem_Enums
#define _HDR_gsiDeclQGraphicsSimpleTextItem_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QGraphicsItem::CacheMode>
class QGraphicsItem_CacheMode_Enums : public QFlags<enum QGraphicsItem::CacheMode> {
public:
  QGraphicsItem_CacheMode_Enums () : m_flags () { }
  QGraphicsItem_CacheMode_Enums (enum QGraphicsItem::CacheMode v) : m_flags (v) { }
  QGraphicsItem_CacheMode_Enums (const QFlags<enum QGraphicsItem::CacheMode> &v) : m_flags (v) { }
  QFlags<enum QGraphicsItem::CacheMode> flags () const { return m_flags; }
private:
  QFlags<QGraphicsItem::CacheMode> m_flags;
};

//  Wrapper class for enum QGraphicsItem::CacheMode
class QGraphicsItem_CacheMode_Enum : public QGraphicsItem_CacheMode_Enums {
public:
  QGraphicsItem_CacheMode_Enum () { }
  QGraphicsItem_CacheMode_Enum (enum QGraphicsItem::CacheMode v) : QGraphicsItem_CacheMode_Enums (v) { }
  enum QGraphicsItem::CacheMode value () const { return (enum QGraphicsItem::CacheMode) flags ().operator int (); }
};

//  Converter for QFlags<enum QGraphicsItem::CacheMode>
template <>
struct Converter<QFlags<enum QGraphicsItem::CacheMode> >
{
public:
  typedef QFlags<enum QGraphicsItem::CacheMode> source_type;
  typedef QGraphicsItem_CacheMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QGraphicsItem::CacheMode
template <>
struct Converter<enum QGraphicsItem::CacheMode>
{
public:
  typedef enum QGraphicsItem::CacheMode source_type;
  typedef QGraphicsItem_CacheMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QGraphicsItem::GraphicsItemChange>
class QGraphicsItem_GraphicsItemChange_Enums : public QFlags<enum QGraphicsItem::GraphicsItemChange> {
public:
  QGraphicsItem_GraphicsItemChange_Enums () : m_flags () { }
  QGraphicsItem_GraphicsItemChange_Enums (enum QGraphicsItem::GraphicsItemChange v) : m_flags (v) { }
  QGraphicsItem_GraphicsItemChange_Enums (const QFlags<enum QGraphicsItem::GraphicsItemChange> &v) : m_flags (v) { }
  QFlags<enum QGraphicsItem::GraphicsItemChange> flags () const { return m_flags; }
private:
  QFlags<QGraphicsItem::GraphicsItemChange> m_flags;
};

//  Wrapper class for enum QGraphicsItem::GraphicsItemChange
class QGraphicsItem_GraphicsItemChange_Enum : public QGraphicsItem_GraphicsItemChange_Enums {
public:
  QGraphicsItem_GraphicsItemChange_Enum () { }
  QGraphicsItem_GraphicsItemChange_Enum (enum QGraphicsItem::GraphicsItemChange v) : QGraphicsItem_GraphicsItemChange_Enums (v) { }
  enum QGraphicsItem::GraphicsItemChange value () const { return (enum QGraphicsItem::GraphicsItemChange) flags ().operator int (); }
};

//  Converter for QFlags<enum QGraphicsItem::GraphicsItemChange>
template <>
struct Converter<QFlags<enum QGraphicsItem::GraphicsItemChange> >
{
public:
  typedef QFlags<enum QGraphicsItem::GraphicsItemChange> source_type;
  typedef QGraphicsItem_GraphicsItemChange_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QGraphicsItem::GraphicsItemChange
template <>
struct Converter<enum QGraphicsItem::GraphicsItemChange>
{
public:
  typedef enum QGraphicsItem::GraphicsItemChange source_type;
  typedef QGraphicsItem_GraphicsItemChange_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QGraphicsItem::GraphicsItemFlag>
class QGraphicsItem_GraphicsItemFlag_Enums : public QFlags<enum QGraphicsItem::GraphicsItemFlag> {
public:
  QGraphicsItem_GraphicsItemFlag_Enums () : m_flags () { }
  QGraphicsItem_GraphicsItemFlag_Enums (enum QGraphicsItem::GraphicsItemFlag v) : m_flags (v) { }
  QGraphicsItem_GraphicsItemFlag_Enums (const QFlags<enum QGraphicsItem::GraphicsItemFlag> &v) : m_flags (v) { }
  QFlags<enum QGraphicsItem::GraphicsItemFlag> flags () const { return m_flags; }
private:
  QFlags<QGraphicsItem::GraphicsItemFlag> m_flags;
};

//  Wrapper class for enum QGraphicsItem::GraphicsItemFlag
class QGraphicsItem_GraphicsItemFlag_Enum : public QGraphicsItem_GraphicsItemFlag_Enums {
public:
  QGraphicsItem_GraphicsItemFlag_Enum () { }
  QGraphicsItem_GraphicsItemFlag_Enum (enum QGraphicsItem::GraphicsItemFlag v) : QGraphicsItem_GraphicsItemFlag_Enums (v) { }
  enum QGraphicsItem::GraphicsItemFlag value () const { return (enum QGraphicsItem::GraphicsItemFlag) flags ().operator int (); }
};

//  Converter for QFlags<enum QGraphicsItem::GraphicsItemFlag>
template <>
struct Converter<QFlags<enum QGraphicsItem::GraphicsItemFlag> >
{
public:
  typedef QFlags<enum QGraphicsItem::GraphicsItemFlag> source_type;
  typedef QGraphicsItem_GraphicsItemFlag_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QGraphicsItem::GraphicsItemFlag
template <>
struct Converter<enum QGraphicsItem::GraphicsItemFlag>
{
public:
  typedef enum QGraphicsItem::GraphicsItemFlag source_type;
  typedef QGraphicsItem_GraphicsItemFlag_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum QGraphicsItem::PanelModality>
class QGraphicsItem_PanelModality_Enums : public QFlags<enum QGraphicsItem::PanelModality> {
public:
  QGraphicsItem_PanelModality_Enums () : m_flags () { }
  QGraphicsItem_PanelModality_Enums (enum QGraphicsItem::PanelModality v) : m_flags (v) { }
  QGraphicsItem_PanelModality_Enums (const QFlags<enum QGraphicsItem::PanelModality> &v) : m_flags (v) { }
  QFlags<enum QGraphicsItem::PanelModality> flags () const { return m_flags; }
private:
  QFlags<QGraphicsItem::PanelModality> m_flags;
};

//  Wrapper class for enum QGraphicsItem::PanelModality
class QGraphicsItem_PanelModality_Enum : public QGraphicsItem_PanelModality_Enums {
public:
  QGraphicsItem_PanelModality_Enum () { }
  QGraphicsItem_PanelModality_Enum (enum QGraphicsItem::PanelModality v) : QGraphicsItem_PanelModality_Enums (v) { }
  enum QGraphicsItem::PanelModality value () const { return (enum QGraphicsItem::PanelModality) flags ().operator int (); }
};

//  Converter for QFlags<enum QGraphicsItem::PanelModality>
template <>
struct Converter<QFlags<enum QGraphicsItem::PanelModality> >
{
public:
  typedef QFlags<enum QGraphicsItem::PanelModality> source_type;
  typedef QGraphicsItem_PanelModality_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QGraphicsItem::PanelModality
template <>
struct Converter<enum QGraphicsItem::PanelModality>
{
public:
  typedef enum QGraphicsItem::PanelModality source_type;
  typedef QGraphicsItem_PanelModality_Enum target_type;
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

//  Wrapper class for QFlags<enum Qt::ItemSelectionMode>
class Qt_ItemSelectionMode_Enums : public QFlags<enum Qt::ItemSelectionMode> {
public:
  Qt_ItemSelectionMode_Enums () : m_flags () { }
  Qt_ItemSelectionMode_Enums (enum Qt::ItemSelectionMode v) : m_flags (v) { }
  Qt_ItemSelectionMode_Enums (const QFlags<enum Qt::ItemSelectionMode> &v) : m_flags (v) { }
  QFlags<enum Qt::ItemSelectionMode> flags () const { return m_flags; }
private:
  QFlags<Qt::ItemSelectionMode> m_flags;
};

//  Wrapper class for enum Qt::ItemSelectionMode
class Qt_ItemSelectionMode_Enum : public Qt_ItemSelectionMode_Enums {
public:
  Qt_ItemSelectionMode_Enum () { }
  Qt_ItemSelectionMode_Enum (enum Qt::ItemSelectionMode v) : Qt_ItemSelectionMode_Enums (v) { }
  enum Qt::ItemSelectionMode value () const { return (enum Qt::ItemSelectionMode) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::ItemSelectionMode>
template <>
struct Converter<QFlags<enum Qt::ItemSelectionMode> >
{
public:
  typedef QFlags<enum Qt::ItemSelectionMode> source_type;
  typedef Qt_ItemSelectionMode_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::ItemSelectionMode
template <>
struct Converter<enum Qt::ItemSelectionMode>
{
public:
  typedef enum Qt::ItemSelectionMode source_type;
  typedef Qt_ItemSelectionMode_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Wrapper class for QFlags<enum Qt::MouseButton>
class Qt_MouseButton_Enums : public QFlags<enum Qt::MouseButton> {
public:
  Qt_MouseButton_Enums () : m_flags () { }
  Qt_MouseButton_Enums (enum Qt::MouseButton v) : m_flags (v) { }
  Qt_MouseButton_Enums (const QFlags<enum Qt::MouseButton> &v) : m_flags (v) { }
  QFlags<enum Qt::MouseButton> flags () const { return m_flags; }
private:
  QFlags<Qt::MouseButton> m_flags;
};

//  Wrapper class for enum Qt::MouseButton
class Qt_MouseButton_Enum : public Qt_MouseButton_Enums {
public:
  Qt_MouseButton_Enum () { }
  Qt_MouseButton_Enum (enum Qt::MouseButton v) : Qt_MouseButton_Enums (v) { }
  enum Qt::MouseButton value () const { return (enum Qt::MouseButton) flags ().operator int (); }
};

//  Converter for QFlags<enum Qt::MouseButton>
template <>
struct Converter<QFlags<enum Qt::MouseButton> >
{
public:
  typedef QFlags<enum Qt::MouseButton> source_type;
  typedef Qt_MouseButton_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum Qt::MouseButton
template <>
struct Converter<enum Qt::MouseButton>
{
public:
  typedef enum Qt::MouseButton source_type;
  typedef Qt_MouseButton_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
