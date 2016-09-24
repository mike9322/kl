
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
*  @file gsiDeclQStringMatcher.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtCore.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQStringMatcher_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QStringMatcher

//  Constructor QStringMatcher::QStringMatcher()


static void _init_ctor_QStringMatcher_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QStringMatcher *> ();
}

static void _call_ctor_QStringMatcher_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QStringMatcher *> (new QStringMatcher ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStringMatcher_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStringMatcher::QStringMatcher()\nThis method creates an object of class QStringMatcher.", &_init_ctor_QStringMatcher_0, &_call_ctor_QStringMatcher_0);
}

//  Constructor QStringMatcher::QStringMatcher(const QString &pattern, Qt::CaseSensitivity cs)


static void _init_ctor_QStringMatcher_4241 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("pattern");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("cs", true, "Qt::CaseSensitive");
  decl->add_arg<const qt_gsi::Converter<Qt::CaseSensitivity>::target_type & > (argspec_1);
  decl->set_return_new<QStringMatcher *> ();
}

static void _call_ctor_QStringMatcher_4241 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  tl::Heap heap;
  const qt_gsi::Converter<Qt::CaseSensitivity>::target_type & arg2 = args ? args.read<const qt_gsi::Converter<Qt::CaseSensitivity>::target_type & > () : (const qt_gsi::Converter<Qt::CaseSensitivity>::target_type &)(qt_gsi::CppToQtReadAdaptor<Qt::CaseSensitivity>(heap, Qt::CaseSensitive));
  ret.write<QStringMatcher *> (new QStringMatcher (arg1, qt_gsi::QtToCppAdaptor<Qt::CaseSensitivity>(arg2).cref()));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStringMatcher_4241 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStringMatcher::QStringMatcher(const QString &pattern, Qt::CaseSensitivity cs)\nThis method creates an object of class QStringMatcher.", &_init_ctor_QStringMatcher_4241, &_call_ctor_QStringMatcher_4241);
}

//  Constructor QStringMatcher::QStringMatcher(const QStringMatcher &other)


static void _init_ctor_QStringMatcher_2733 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStringMatcher & > (argspec_0);
  decl->set_return_new<QStringMatcher *> ();
}

static void _call_ctor_QStringMatcher_2733 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStringMatcher &arg1 = args.read<const QStringMatcher & > ();
  ret.write<QStringMatcher *> (new QStringMatcher (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QStringMatcher_2733 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QStringMatcher::QStringMatcher(const QStringMatcher &other)\nThis method creates an object of class QStringMatcher.", &_init_ctor_QStringMatcher_2733, &_call_ctor_QStringMatcher_2733);
}

// Qt::CaseSensitivity QStringMatcher::caseSensitivity()


static void _init_f_caseSensitivity_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<Qt::CaseSensitivity>::target_type > ();
}

static void _call_f_caseSensitivity_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<Qt::CaseSensitivity>::target_type > ((qt_gsi::Converter<Qt::CaseSensitivity>::target_type)qt_gsi::CppToQtAdaptor<Qt::CaseSensitivity>(((QStringMatcher *)cls)->caseSensitivity ()));
}

static qt_gsi::GenericMethod *_create_f_caseSensitivity_c0 ()
{
  return new qt_gsi::GenericMethod (":caseSensitivity", "@brief Method Qt::CaseSensitivity QStringMatcher::caseSensitivity()\n", true, &_init_f_caseSensitivity_c0, &_call_f_caseSensitivity_c0);
}

// int QStringMatcher::indexIn(const QString &str, int from)


static void _init_f_indexIn_c2684 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("str");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("from", true, "0");
  decl->add_arg<int > (argspec_1);
  decl->set_return<int > ();
}

static void _call_f_indexIn_c2684 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  int arg2 = args ? args.read<int > () : (int)(0);
  ret.write<int > ((int)((QStringMatcher *)cls)->indexIn (arg1, arg2));
}

static qt_gsi::GenericMethod *_create_f_indexIn_c2684 ()
{
  return new qt_gsi::GenericMethod ("indexIn", "@brief Method int QStringMatcher::indexIn(const QString &str, int from)\n", true, &_init_f_indexIn_c2684, &_call_f_indexIn_c2684);
}

// QStringMatcher &QStringMatcher::operator=(const QStringMatcher &other)


static void _init_f_operator_eq__2733 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QStringMatcher & > (argspec_0);
  decl->set_return<QStringMatcher & > ();
}

static void _call_f_operator_eq__2733 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QStringMatcher &arg1 = args.read<const QStringMatcher & > ();
  ret.write<QStringMatcher & > ((QStringMatcher &)((QStringMatcher *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__2733 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QStringMatcher &QStringMatcher::operator=(const QStringMatcher &other)\n", false, &_init_f_operator_eq__2733, &_call_f_operator_eq__2733);
}

// QString QStringMatcher::pattern()


static void _init_f_pattern_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_pattern_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QStringMatcher *)cls)->pattern ());
}

static qt_gsi::GenericMethod *_create_f_pattern_c0 ()
{
  return new qt_gsi::GenericMethod (":pattern", "@brief Method QString QStringMatcher::pattern()\n", true, &_init_f_pattern_c0, &_call_f_pattern_c0);
}

// void QStringMatcher::setCaseSensitivity(Qt::CaseSensitivity cs)


static void _init_f_setCaseSensitivity_2324 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("cs");
  decl->add_arg<const qt_gsi::Converter<Qt::CaseSensitivity>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setCaseSensitivity_2324 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<Qt::CaseSensitivity>::target_type & arg1 = args.read<const qt_gsi::Converter<Qt::CaseSensitivity>::target_type & > ();
  ((QStringMatcher *)cls)->setCaseSensitivity (qt_gsi::QtToCppAdaptor<Qt::CaseSensitivity>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setCaseSensitivity_2324 ()
{
  return new qt_gsi::GenericMethod ("setCaseSensitivity|caseSensitivity=", "@brief Method void QStringMatcher::setCaseSensitivity(Qt::CaseSensitivity cs)\n", false, &_init_f_setCaseSensitivity_2324, &_call_f_setCaseSensitivity_2324);
}

// void QStringMatcher::setPattern(const QString &pattern)


static void _init_f_setPattern_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("pattern");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setPattern_2025 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ((QStringMatcher *)cls)->setPattern (arg1);
}

static qt_gsi::GenericMethod *_create_f_setPattern_2025 ()
{
  return new qt_gsi::GenericMethod ("setPattern|pattern=", "@brief Method void QStringMatcher::setPattern(const QString &pattern)\n", false, &_init_f_setPattern_2025, &_call_f_setPattern_2025);
}


namespace gsi
{
gsi::Class<QStringMatcher> decl_QStringMatcher ("QStringMatcher",
  gsi::Methods(_create_ctor_QStringMatcher_0 ()) +
  gsi::Methods(_create_ctor_QStringMatcher_4241 ()) +
  gsi::Methods(_create_ctor_QStringMatcher_2733 ()) +
  gsi::Methods(_create_f_caseSensitivity_c0 ()) +
  gsi::Methods(_create_f_indexIn_c2684 ()) +
  gsi::Methods(_create_f_operator_eq__2733 ()) +
  gsi::Methods(_create_f_pattern_c0 ()) +
  gsi::Methods(_create_f_setCaseSensitivity_2324 ()) +
  gsi::Methods(_create_f_setPattern_2025 ()),
  "@qt\n@brief Binding of QStringMatcher");

}

