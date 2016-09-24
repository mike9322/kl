
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
*  @file gsiDeclQProcessEnvironment.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtCore.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQProcessEnvironment_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QProcessEnvironment

//  Constructor QProcessEnvironment::QProcessEnvironment()


static void _init_ctor_QProcessEnvironment_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QProcessEnvironment *> ();
}

static void _call_ctor_QProcessEnvironment_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QProcessEnvironment *> (new QProcessEnvironment ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QProcessEnvironment_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QProcessEnvironment::QProcessEnvironment()\nThis method creates an object of class QProcessEnvironment.", &_init_ctor_QProcessEnvironment_0, &_call_ctor_QProcessEnvironment_0);
}

//  Constructor QProcessEnvironment::QProcessEnvironment(const QProcessEnvironment &other)


static void _init_ctor_QProcessEnvironment_3302 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QProcessEnvironment & > (argspec_0);
  decl->set_return_new<QProcessEnvironment *> ();
}

static void _call_ctor_QProcessEnvironment_3302 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QProcessEnvironment &arg1 = args.read<const QProcessEnvironment & > ();
  ret.write<QProcessEnvironment *> (new QProcessEnvironment (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QProcessEnvironment_3302 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QProcessEnvironment::QProcessEnvironment(const QProcessEnvironment &other)\nThis method creates an object of class QProcessEnvironment.", &_init_ctor_QProcessEnvironment_3302, &_call_ctor_QProcessEnvironment_3302);
}

// void QProcessEnvironment::clear()


static void _init_f_clear_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<void > ();
}

static void _call_f_clear_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ((QProcessEnvironment *)cls)->clear ();
}

static qt_gsi::GenericMethod *_create_f_clear_0 ()
{
  return new qt_gsi::GenericMethod ("clear", "@brief Method void QProcessEnvironment::clear()\n", false, &_init_f_clear_0, &_call_f_clear_0);
}

// bool QProcessEnvironment::contains(const QString &name)


static void _init_f_contains_c2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_contains_c2025 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ret.write<bool > ((bool)((QProcessEnvironment *)cls)->contains (arg1));
}

static qt_gsi::GenericMethod *_create_f_contains_c2025 ()
{
  return new qt_gsi::GenericMethod ("contains", "@brief Method bool QProcessEnvironment::contains(const QString &name)\n", true, &_init_f_contains_c2025, &_call_f_contains_c2025);
}

// void QProcessEnvironment::insert(const QString &name, const QString &value)


static void _init_f_insert_3942 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("value");
  decl->add_arg<const QString & > (argspec_1);
  decl->set_return<void > ();
}

static void _call_f_insert_3942 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  const QString &arg2 = args.read<const QString & > ();
  ((QProcessEnvironment *)cls)->insert (arg1, arg2);
}

static qt_gsi::GenericMethod *_create_f_insert_3942 ()
{
  return new qt_gsi::GenericMethod ("insert", "@brief Method void QProcessEnvironment::insert(const QString &name, const QString &value)\n", false, &_init_f_insert_3942, &_call_f_insert_3942);
}

// bool QProcessEnvironment::isEmpty()


static void _init_f_isEmpty_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isEmpty_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QProcessEnvironment *)cls)->isEmpty ());
}

static qt_gsi::GenericMethod *_create_f_isEmpty_c0 ()
{
  return new qt_gsi::GenericMethod ("isEmpty?", "@brief Method bool QProcessEnvironment::isEmpty()\n", true, &_init_f_isEmpty_c0, &_call_f_isEmpty_c0);
}

// bool QProcessEnvironment::operator!=(const QProcessEnvironment &other)


static void _init_f_operator_excl__eq__c3302 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QProcessEnvironment & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_excl__eq__c3302 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QProcessEnvironment &arg1 = args.read<const QProcessEnvironment & > ();
  ret.write<bool > ((bool)((QProcessEnvironment *)cls)->operator!= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_excl__eq__c3302 ()
{
  return new qt_gsi::GenericMethod ("!=", "@brief Method bool QProcessEnvironment::operator!=(const QProcessEnvironment &other)\n", true, &_init_f_operator_excl__eq__c3302, &_call_f_operator_excl__eq__c3302);
}

// QProcessEnvironment &QProcessEnvironment::operator=(const QProcessEnvironment &other)


static void _init_f_operator_eq__3302 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QProcessEnvironment & > (argspec_0);
  decl->set_return<QProcessEnvironment & > ();
}

static void _call_f_operator_eq__3302 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QProcessEnvironment &arg1 = args.read<const QProcessEnvironment & > ();
  ret.write<QProcessEnvironment & > ((QProcessEnvironment &)((QProcessEnvironment *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__3302 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QProcessEnvironment &QProcessEnvironment::operator=(const QProcessEnvironment &other)\n", false, &_init_f_operator_eq__3302, &_call_f_operator_eq__3302);
}

// bool QProcessEnvironment::operator==(const QProcessEnvironment &other)


static void _init_f_operator_eq__eq__c3302 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QProcessEnvironment & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_eq__eq__c3302 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QProcessEnvironment &arg1 = args.read<const QProcessEnvironment & > ();
  ret.write<bool > ((bool)((QProcessEnvironment *)cls)->operator== (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__eq__c3302 ()
{
  return new qt_gsi::GenericMethod ("==", "@brief Method bool QProcessEnvironment::operator==(const QProcessEnvironment &other)\n", true, &_init_f_operator_eq__eq__c3302, &_call_f_operator_eq__eq__c3302);
}

// void QProcessEnvironment::remove(const QString &name)


static void _init_f_remove_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_remove_2025 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ((QProcessEnvironment *)cls)->remove (arg1);
}

static qt_gsi::GenericMethod *_create_f_remove_2025 ()
{
  return new qt_gsi::GenericMethod ("remove", "@brief Method void QProcessEnvironment::remove(const QString &name)\n", false, &_init_f_remove_2025, &_call_f_remove_2025);
}

// QStringList QProcessEnvironment::toStringList()


static void _init_f_toStringList_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QStringList>::target_type > ();
}

static void _call_f_toStringList_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QStringList>::target_type > ((qt_gsi::Converter<QStringList>::target_type)qt_gsi::CppToQtAdaptor<QStringList>(((QProcessEnvironment *)cls)->toStringList ()));
}

static qt_gsi::GenericMethod *_create_f_toStringList_c0 ()
{
  return new qt_gsi::GenericMethod ("toStringList", "@brief Method QStringList QProcessEnvironment::toStringList()\n", true, &_init_f_toStringList_c0, &_call_f_toStringList_c0);
}

// QString QProcessEnvironment::value(const QString &name, const QString &defaultValue)


static void _init_f_value_c3942 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("defaultValue", true, "QString()");
  decl->add_arg<const QString & > (argspec_1);
  decl->set_return<QString > ();
}

static void _call_f_value_c3942 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  const QString &arg2 = args ? args.read<const QString & > () : (const QString &)(QString());
  ret.write<QString > ((QString)((QProcessEnvironment *)cls)->value (arg1, arg2));
}

static qt_gsi::GenericMethod *_create_f_value_c3942 ()
{
  return new qt_gsi::GenericMethod ("value", "@brief Method QString QProcessEnvironment::value(const QString &name, const QString &defaultValue)\n", true, &_init_f_value_c3942, &_call_f_value_c3942);
}

// static QProcessEnvironment QProcessEnvironment::systemEnvironment()


static void _init_f_systemEnvironment_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<QProcessEnvironment > ();
}

static void _call_f_systemEnvironment_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QProcessEnvironment > ((QProcessEnvironment)QProcessEnvironment::systemEnvironment ());
}

static qt_gsi::GenericStaticMethod *_create_f_systemEnvironment_0 ()
{
  return new qt_gsi::GenericStaticMethod ("systemEnvironment", "@brief Static method QProcessEnvironment QProcessEnvironment::systemEnvironment()\nThis method is static and can be called without an instance.", &_init_f_systemEnvironment_0, &_call_f_systemEnvironment_0);
}


namespace gsi
{
gsi::Class<QProcessEnvironment> decl_QProcessEnvironment ("QProcessEnvironment",
  gsi::Methods(_create_ctor_QProcessEnvironment_0 ()) +
  gsi::Methods(_create_ctor_QProcessEnvironment_3302 ()) +
  gsi::Methods(_create_f_clear_0 ()) +
  gsi::Methods(_create_f_contains_c2025 ()) +
  gsi::Methods(_create_f_insert_3942 ()) +
  gsi::Methods(_create_f_isEmpty_c0 ()) +
  gsi::Methods(_create_f_operator_excl__eq__c3302 ()) +
  gsi::Methods(_create_f_operator_eq__3302 ()) +
  gsi::Methods(_create_f_operator_eq__eq__c3302 ()) +
  gsi::Methods(_create_f_remove_2025 ()) +
  gsi::Methods(_create_f_toStringList_c0 ()) +
  gsi::Methods(_create_f_value_c3942 ()) +
  gsi::Methods(_create_f_systemEnvironment_0 ()),
  "@qt\n@brief Binding of QProcessEnvironment");

}
