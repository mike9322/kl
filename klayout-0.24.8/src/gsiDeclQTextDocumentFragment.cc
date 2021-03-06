
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
*  @file gsiDeclQTextDocumentFragment.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQTextDocumentFragment_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QTextDocumentFragment

//  Constructor QTextDocumentFragment::QTextDocumentFragment()


static void _init_ctor_QTextDocumentFragment_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QTextDocumentFragment *> ();
}

static void _call_ctor_QTextDocumentFragment_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QTextDocumentFragment *> (new QTextDocumentFragment ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextDocumentFragment_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextDocumentFragment::QTextDocumentFragment()\nThis method creates an object of class QTextDocumentFragment.", &_init_ctor_QTextDocumentFragment_0, &_call_ctor_QTextDocumentFragment_0);
}

//  Constructor QTextDocumentFragment::QTextDocumentFragment(const QTextDocument *document)


static void _init_ctor_QTextDocumentFragment_2650 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("document");
  decl->add_arg<const QTextDocument * > (argspec_0);
  decl->set_return_new<QTextDocumentFragment *> ();
}

static void _call_ctor_QTextDocumentFragment_2650 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextDocument *arg1 = args.read<const QTextDocument * > ();
  ret.write<QTextDocumentFragment *> (new QTextDocumentFragment (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextDocumentFragment_2650 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextDocumentFragment::QTextDocumentFragment(const QTextDocument *document)\nThis method creates an object of class QTextDocumentFragment.", &_init_ctor_QTextDocumentFragment_2650, &_call_ctor_QTextDocumentFragment_2650);
}

//  Constructor QTextDocumentFragment::QTextDocumentFragment(const QTextCursor &range)


static void _init_ctor_QTextDocumentFragment_2453 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("range");
  decl->add_arg<const QTextCursor & > (argspec_0);
  decl->set_return_new<QTextDocumentFragment *> ();
}

static void _call_ctor_QTextDocumentFragment_2453 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextCursor &arg1 = args.read<const QTextCursor & > ();
  ret.write<QTextDocumentFragment *> (new QTextDocumentFragment (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextDocumentFragment_2453 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextDocumentFragment::QTextDocumentFragment(const QTextCursor &range)\nThis method creates an object of class QTextDocumentFragment.", &_init_ctor_QTextDocumentFragment_2453, &_call_ctor_QTextDocumentFragment_2453);
}

//  Constructor QTextDocumentFragment::QTextDocumentFragment(const QTextDocumentFragment &rhs)


static void _init_ctor_QTextDocumentFragment_3466 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("rhs");
  decl->add_arg<const QTextDocumentFragment & > (argspec_0);
  decl->set_return_new<QTextDocumentFragment *> ();
}

static void _call_ctor_QTextDocumentFragment_3466 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextDocumentFragment &arg1 = args.read<const QTextDocumentFragment & > ();
  ret.write<QTextDocumentFragment *> (new QTextDocumentFragment (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextDocumentFragment_3466 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextDocumentFragment::QTextDocumentFragment(const QTextDocumentFragment &rhs)\nThis method creates an object of class QTextDocumentFragment.", &_init_ctor_QTextDocumentFragment_3466, &_call_ctor_QTextDocumentFragment_3466);
}

// bool QTextDocumentFragment::isEmpty()


static void _init_f_isEmpty_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isEmpty_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QTextDocumentFragment *)cls)->isEmpty ());
}

static qt_gsi::GenericMethod *_create_f_isEmpty_c0 ()
{
  return new qt_gsi::GenericMethod ("isEmpty?", "@brief Method bool QTextDocumentFragment::isEmpty()\n", true, &_init_f_isEmpty_c0, &_call_f_isEmpty_c0);
}

// QTextDocumentFragment &QTextDocumentFragment::operator=(const QTextDocumentFragment &rhs)


static void _init_f_operator_eq__3466 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("rhs");
  decl->add_arg<const QTextDocumentFragment & > (argspec_0);
  decl->set_return<QTextDocumentFragment & > ();
}

static void _call_f_operator_eq__3466 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextDocumentFragment &arg1 = args.read<const QTextDocumentFragment & > ();
  ret.write<QTextDocumentFragment & > ((QTextDocumentFragment &)((QTextDocumentFragment *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__3466 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QTextDocumentFragment &QTextDocumentFragment::operator=(const QTextDocumentFragment &rhs)\n", false, &_init_f_operator_eq__3466, &_call_f_operator_eq__3466);
}

// QString QTextDocumentFragment::toHtml()


static void _init_f_toHtml_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_toHtml_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QTextDocumentFragment *)cls)->toHtml ());
}

static qt_gsi::GenericMethod *_create_f_toHtml_c0 ()
{
  return new qt_gsi::GenericMethod ("toHtml", "@brief Method QString QTextDocumentFragment::toHtml()\n", true, &_init_f_toHtml_c0, &_call_f_toHtml_c0);
}

// QString QTextDocumentFragment::toHtml(const QByteArray &encoding)


static void _init_f_toHtml_c2309 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("encoding");
  decl->add_arg<const QByteArray & > (argspec_0);
  decl->set_return<QString > ();
}

static void _call_f_toHtml_c2309 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QByteArray &arg1 = args.read<const QByteArray & > ();
  ret.write<QString > ((QString)((QTextDocumentFragment *)cls)->toHtml (arg1));
}

static qt_gsi::GenericMethod *_create_f_toHtml_c2309 ()
{
  return new qt_gsi::GenericMethod ("toHtml", "@brief Method QString QTextDocumentFragment::toHtml(const QByteArray &encoding)\n", true, &_init_f_toHtml_c2309, &_call_f_toHtml_c2309);
}

// QString QTextDocumentFragment::toPlainText()


static void _init_f_toPlainText_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_toPlainText_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QTextDocumentFragment *)cls)->toPlainText ());
}

static qt_gsi::GenericMethod *_create_f_toPlainText_c0 ()
{
  return new qt_gsi::GenericMethod ("toPlainText", "@brief Method QString QTextDocumentFragment::toPlainText()\n", true, &_init_f_toPlainText_c0, &_call_f_toPlainText_c0);
}

// static QTextDocumentFragment QTextDocumentFragment::fromHtml(const QString &html)


static void _init_f_fromHtml_2025 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("html");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<QTextDocumentFragment > ();
}

static void _call_f_fromHtml_2025 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ret.write<QTextDocumentFragment > ((QTextDocumentFragment)QTextDocumentFragment::fromHtml (arg1));
}

static qt_gsi::GenericStaticMethod *_create_f_fromHtml_2025 ()
{
  return new qt_gsi::GenericStaticMethod ("fromHtml", "@brief Static method QTextDocumentFragment QTextDocumentFragment::fromHtml(const QString &html)\nThis method is static and can be called without an instance.", &_init_f_fromHtml_2025, &_call_f_fromHtml_2025);
}

// static QTextDocumentFragment QTextDocumentFragment::fromHtml(const QString &html, const QTextDocument *resourceProvider)


static void _init_f_fromHtml_4567 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("html");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("resourceProvider");
  decl->add_arg<const QTextDocument * > (argspec_1);
  decl->set_return<QTextDocumentFragment > ();
}

static void _call_f_fromHtml_4567 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  const QTextDocument *arg2 = args.read<const QTextDocument * > ();
  ret.write<QTextDocumentFragment > ((QTextDocumentFragment)QTextDocumentFragment::fromHtml (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_f_fromHtml_4567 ()
{
  return new qt_gsi::GenericStaticMethod ("fromHtml", "@brief Static method QTextDocumentFragment QTextDocumentFragment::fromHtml(const QString &html, const QTextDocument *resourceProvider)\nThis method is static and can be called without an instance.", &_init_f_fromHtml_4567, &_call_f_fromHtml_4567);
}

// static QTextDocumentFragment QTextDocumentFragment::fromPlainText(const QString &plainText)


static void _init_f_fromPlainText_2025 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("plainText");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<QTextDocumentFragment > ();
}

static void _call_f_fromPlainText_2025 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ret.write<QTextDocumentFragment > ((QTextDocumentFragment)QTextDocumentFragment::fromPlainText (arg1));
}

static qt_gsi::GenericStaticMethod *_create_f_fromPlainText_2025 ()
{
  return new qt_gsi::GenericStaticMethod ("fromPlainText", "@brief Static method QTextDocumentFragment QTextDocumentFragment::fromPlainText(const QString &plainText)\nThis method is static and can be called without an instance.", &_init_f_fromPlainText_2025, &_call_f_fromPlainText_2025);
}


namespace gsi
{
gsi::Class<QTextDocumentFragment> decl_QTextDocumentFragment ("QTextDocumentFragment",
  gsi::Methods(_create_ctor_QTextDocumentFragment_0 ()) +
  gsi::Methods(_create_ctor_QTextDocumentFragment_2650 ()) +
  gsi::Methods(_create_ctor_QTextDocumentFragment_2453 ()) +
  gsi::Methods(_create_ctor_QTextDocumentFragment_3466 ()) +
  gsi::Methods(_create_f_isEmpty_c0 ()) +
  gsi::Methods(_create_f_operator_eq__3466 ()) +
  gsi::Methods(_create_f_toHtml_c0 ()) +
  gsi::Methods(_create_f_toHtml_c2309 ()) +
  gsi::Methods(_create_f_toPlainText_c0 ()) +
  gsi::Methods(_create_f_fromHtml_2025 ()) +
  gsi::Methods(_create_f_fromHtml_4567 ()) +
  gsi::Methods(_create_f_fromPlainText_2025 ()),
  "@qt\n@brief Binding of QTextDocumentFragment");

}

