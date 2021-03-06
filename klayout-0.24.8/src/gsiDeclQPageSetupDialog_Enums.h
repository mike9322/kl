
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
*  @file gsiDeclQPageSetupDialog_Enums.h 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQPageSetupDialog_Enums
#define _HDR_gsiDeclQPageSetupDialog_Enums

#include <QtCore/QFlags>

namespace qt_gsi
{

//  Wrapper class for QFlags<enum QPageSetupDialog::PageSetupDialogOption>
class QPageSetupDialog_PageSetupDialogOption_Enums : public QFlags<enum QPageSetupDialog::PageSetupDialogOption> {
public:
  QPageSetupDialog_PageSetupDialogOption_Enums () : m_flags () { }
  QPageSetupDialog_PageSetupDialogOption_Enums (enum QPageSetupDialog::PageSetupDialogOption v) : m_flags (v) { }
  QPageSetupDialog_PageSetupDialogOption_Enums (const QFlags<enum QPageSetupDialog::PageSetupDialogOption> &v) : m_flags (v) { }
  QFlags<enum QPageSetupDialog::PageSetupDialogOption> flags () const { return m_flags; }
private:
  QFlags<QPageSetupDialog::PageSetupDialogOption> m_flags;
};

//  Wrapper class for enum QPageSetupDialog::PageSetupDialogOption
class QPageSetupDialog_PageSetupDialogOption_Enum : public QPageSetupDialog_PageSetupDialogOption_Enums {
public:
  QPageSetupDialog_PageSetupDialogOption_Enum () { }
  QPageSetupDialog_PageSetupDialogOption_Enum (enum QPageSetupDialog::PageSetupDialogOption v) : QPageSetupDialog_PageSetupDialogOption_Enums (v) { }
  enum QPageSetupDialog::PageSetupDialogOption value () const { return (enum QPageSetupDialog::PageSetupDialogOption) flags ().operator int (); }
};

//  Converter for QFlags<enum QPageSetupDialog::PageSetupDialogOption>
template <>
struct Converter<QFlags<enum QPageSetupDialog::PageSetupDialogOption> >
{
public:
  typedef QFlags<enum QPageSetupDialog::PageSetupDialogOption> source_type;
  typedef QPageSetupDialog_PageSetupDialogOption_Enums target_type;
  static source_type toq (const target_type &c) { return c.flags (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

//  Converter for enum QPageSetupDialog::PageSetupDialogOption
template <>
struct Converter<enum QPageSetupDialog::PageSetupDialogOption>
{
public:
  typedef enum QPageSetupDialog::PageSetupDialogOption source_type;
  typedef QPageSetupDialog_PageSetupDialogOption_Enum target_type;
  static source_type toq (const target_type &c) { return c.value (); }
  static target_type toc (const source_type &qc) { return target_type (qc); }
};

}

#endif
