
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
*  @file gsiDeclQTextTableCell.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQTextTableCell_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QTextTableCell

//  Constructor QTextTableCell::QTextTableCell()


static void _init_ctor_QTextTableCell_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QTextTableCell *> ();
}

static void _call_ctor_QTextTableCell_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QTextTableCell *> (new QTextTableCell ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextTableCell_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextTableCell::QTextTableCell()\nThis method creates an object of class QTextTableCell.", &_init_ctor_QTextTableCell_0, &_call_ctor_QTextTableCell_0);
}

//  Constructor QTextTableCell::QTextTableCell(const QTextTableCell &o)


static void _init_ctor_QTextTableCell_2687 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("o");
  decl->add_arg<const QTextTableCell & > (argspec_0);
  decl->set_return_new<QTextTableCell *> ();
}

static void _call_ctor_QTextTableCell_2687 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextTableCell &arg1 = args.read<const QTextTableCell & > ();
  ret.write<QTextTableCell *> (new QTextTableCell (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextTableCell_2687 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextTableCell::QTextTableCell(const QTextTableCell &o)\nThis method creates an object of class QTextTableCell.", &_init_ctor_QTextTableCell_2687, &_call_ctor_QTextTableCell_2687);
}

// int QTextTableCell::column()


static void _init_f_column_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_column_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QTextTableCell *)cls)->column ());
}

static qt_gsi::GenericMethod *_create_f_column_c0 ()
{
  return new qt_gsi::GenericMethod ("column", "@brief Method int QTextTableCell::column()\n", true, &_init_f_column_c0, &_call_f_column_c0);
}

// int QTextTableCell::columnSpan()


static void _init_f_columnSpan_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_columnSpan_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QTextTableCell *)cls)->columnSpan ());
}

static qt_gsi::GenericMethod *_create_f_columnSpan_c0 ()
{
  return new qt_gsi::GenericMethod ("columnSpan", "@brief Method int QTextTableCell::columnSpan()\n", true, &_init_f_columnSpan_c0, &_call_f_columnSpan_c0);
}

// QTextCursor QTextTableCell::firstCursorPosition()


static void _init_f_firstCursorPosition_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QTextCursor > ();
}

static void _call_f_firstCursorPosition_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QTextCursor > ((QTextCursor)((QTextTableCell *)cls)->firstCursorPosition ());
}

static qt_gsi::GenericMethod *_create_f_firstCursorPosition_c0 ()
{
  return new qt_gsi::GenericMethod ("firstCursorPosition", "@brief Method QTextCursor QTextTableCell::firstCursorPosition()\n", true, &_init_f_firstCursorPosition_c0, &_call_f_firstCursorPosition_c0);
}

// int QTextTableCell::firstPosition()


static void _init_f_firstPosition_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_firstPosition_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QTextTableCell *)cls)->firstPosition ());
}

static qt_gsi::GenericMethod *_create_f_firstPosition_c0 ()
{
  return new qt_gsi::GenericMethod ("firstPosition", "@brief Method int QTextTableCell::firstPosition()\n", true, &_init_f_firstPosition_c0, &_call_f_firstPosition_c0);
}

// QTextCharFormat QTextTableCell::format()


static void _init_f_format_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QTextCharFormat > ();
}

static void _call_f_format_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QTextCharFormat > ((QTextCharFormat)((QTextTableCell *)cls)->format ());
}

static qt_gsi::GenericMethod *_create_f_format_c0 ()
{
  return new qt_gsi::GenericMethod (":format", "@brief Method QTextCharFormat QTextTableCell::format()\n", true, &_init_f_format_c0, &_call_f_format_c0);
}

// bool QTextTableCell::isValid()


static void _init_f_isValid_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isValid_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QTextTableCell *)cls)->isValid ());
}

static qt_gsi::GenericMethod *_create_f_isValid_c0 ()
{
  return new qt_gsi::GenericMethod ("isValid?", "@brief Method bool QTextTableCell::isValid()\n", true, &_init_f_isValid_c0, &_call_f_isValid_c0);
}

// QTextCursor QTextTableCell::lastCursorPosition()


static void _init_f_lastCursorPosition_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QTextCursor > ();
}

static void _call_f_lastCursorPosition_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QTextCursor > ((QTextCursor)((QTextTableCell *)cls)->lastCursorPosition ());
}

static qt_gsi::GenericMethod *_create_f_lastCursorPosition_c0 ()
{
  return new qt_gsi::GenericMethod ("lastCursorPosition", "@brief Method QTextCursor QTextTableCell::lastCursorPosition()\n", true, &_init_f_lastCursorPosition_c0, &_call_f_lastCursorPosition_c0);
}

// int QTextTableCell::lastPosition()


static void _init_f_lastPosition_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_lastPosition_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QTextTableCell *)cls)->lastPosition ());
}

static qt_gsi::GenericMethod *_create_f_lastPosition_c0 ()
{
  return new qt_gsi::GenericMethod ("lastPosition", "@brief Method int QTextTableCell::lastPosition()\n", true, &_init_f_lastPosition_c0, &_call_f_lastPosition_c0);
}

// bool QTextTableCell::operator!=(const QTextTableCell &other)


static void _init_f_operator_excl__eq__c2687 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QTextTableCell & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_excl__eq__c2687 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextTableCell &arg1 = args.read<const QTextTableCell & > ();
  ret.write<bool > ((bool)((QTextTableCell *)cls)->operator!= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_excl__eq__c2687 ()
{
  return new qt_gsi::GenericMethod ("!=", "@brief Method bool QTextTableCell::operator!=(const QTextTableCell &other)\n", true, &_init_f_operator_excl__eq__c2687, &_call_f_operator_excl__eq__c2687);
}

// QTextTableCell &QTextTableCell::operator=(const QTextTableCell &o)


static void _init_f_operator_eq__2687 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("o");
  decl->add_arg<const QTextTableCell & > (argspec_0);
  decl->set_return<QTextTableCell & > ();
}

static void _call_f_operator_eq__2687 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextTableCell &arg1 = args.read<const QTextTableCell & > ();
  ret.write<QTextTableCell & > ((QTextTableCell &)((QTextTableCell *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__2687 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QTextTableCell &QTextTableCell::operator=(const QTextTableCell &o)\n", false, &_init_f_operator_eq__2687, &_call_f_operator_eq__2687);
}

// bool QTextTableCell::operator==(const QTextTableCell &other)


static void _init_f_operator_eq__eq__c2687 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QTextTableCell & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_eq__eq__c2687 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextTableCell &arg1 = args.read<const QTextTableCell & > ();
  ret.write<bool > ((bool)((QTextTableCell *)cls)->operator== (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__eq__c2687 ()
{
  return new qt_gsi::GenericMethod ("==", "@brief Method bool QTextTableCell::operator==(const QTextTableCell &other)\n", true, &_init_f_operator_eq__eq__c2687, &_call_f_operator_eq__eq__c2687);
}

// int QTextTableCell::row()


static void _init_f_row_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_row_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QTextTableCell *)cls)->row ());
}

static qt_gsi::GenericMethod *_create_f_row_c0 ()
{
  return new qt_gsi::GenericMethod ("row", "@brief Method int QTextTableCell::row()\n", true, &_init_f_row_c0, &_call_f_row_c0);
}

// int QTextTableCell::rowSpan()


static void _init_f_rowSpan_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_rowSpan_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QTextTableCell *)cls)->rowSpan ());
}

static qt_gsi::GenericMethod *_create_f_rowSpan_c0 ()
{
  return new qt_gsi::GenericMethod ("rowSpan", "@brief Method int QTextTableCell::rowSpan()\n", true, &_init_f_rowSpan_c0, &_call_f_rowSpan_c0);
}

// void QTextTableCell::setFormat(const QTextCharFormat &format)


static void _init_f_setFormat_2814 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("format");
  decl->add_arg<const QTextCharFormat & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setFormat_2814 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextCharFormat &arg1 = args.read<const QTextCharFormat & > ();
  ((QTextTableCell *)cls)->setFormat (arg1);
}

static qt_gsi::GenericMethod *_create_f_setFormat_2814 ()
{
  return new qt_gsi::GenericMethod ("setFormat|format=", "@brief Method void QTextTableCell::setFormat(const QTextCharFormat &format)\n", false, &_init_f_setFormat_2814, &_call_f_setFormat_2814);
}

// int QTextTableCell::tableCellFormatIndex()


static void _init_f_tableCellFormatIndex_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_tableCellFormatIndex_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QTextTableCell *)cls)->tableCellFormatIndex ());
}

static qt_gsi::GenericMethod *_create_f_tableCellFormatIndex_c0 ()
{
  return new qt_gsi::GenericMethod ("tableCellFormatIndex", "@brief Method int QTextTableCell::tableCellFormatIndex()\n", true, &_init_f_tableCellFormatIndex_c0, &_call_f_tableCellFormatIndex_c0);
}


namespace gsi
{
gsi::Class<QTextTableCell> decl_QTextTableCell ("QTextTableCell",
  gsi::Methods(_create_ctor_QTextTableCell_0 ()) +
  gsi::Methods(_create_ctor_QTextTableCell_2687 ()) +
  gsi::Methods(_create_f_column_c0 ()) +
  gsi::Methods(_create_f_columnSpan_c0 ()) +
  gsi::Methods(_create_f_firstCursorPosition_c0 ()) +
  gsi::Methods(_create_f_firstPosition_c0 ()) +
  gsi::Methods(_create_f_format_c0 ()) +
  gsi::Methods(_create_f_isValid_c0 ()) +
  gsi::Methods(_create_f_lastCursorPosition_c0 ()) +
  gsi::Methods(_create_f_lastPosition_c0 ()) +
  gsi::Methods(_create_f_operator_excl__eq__c2687 ()) +
  gsi::Methods(_create_f_operator_eq__2687 ()) +
  gsi::Methods(_create_f_operator_eq__eq__c2687 ()) +
  gsi::Methods(_create_f_row_c0 ()) +
  gsi::Methods(_create_f_rowSpan_c0 ()) +
  gsi::Methods(_create_f_setFormat_2814 ()) +
  gsi::Methods(_create_f_tableCellFormatIndex_c0 ()),
  "@qt\n@brief Binding of QTextTableCell");

}

