
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
*  @file gsiDeclQSqlField.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtSql.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQSqlField_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QSqlField

//  Constructor QSqlField::QSqlField(const QString &fieldName, QVariant::Type type)


static void _init_ctor_QSqlField_3693 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("fieldName", true, "QString()");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("type", true, "QVariant::Invalid");
  decl->add_arg<const qt_gsi::Converter<QVariant::Type>::target_type & > (argspec_1);
  decl->set_return_new<QSqlField *> ();
}

static void _call_ctor_QSqlField_3693 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args ? args.read<const QString & > () : (const QString &)(QString());
  tl::Heap heap;
  const qt_gsi::Converter<QVariant::Type>::target_type & arg2 = args ? args.read<const qt_gsi::Converter<QVariant::Type>::target_type & > () : (const qt_gsi::Converter<QVariant::Type>::target_type &)(qt_gsi::CppToQtReadAdaptor<QVariant::Type>(heap, QVariant::Invalid));
  ret.write<QSqlField *> (new QSqlField (arg1, qt_gsi::QtToCppAdaptor<QVariant::Type>(arg2).cref()));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSqlField_3693 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSqlField::QSqlField(const QString &fieldName, QVariant::Type type)\nThis method creates an object of class QSqlField.", &_init_ctor_QSqlField_3693, &_call_ctor_QSqlField_3693);
}

//  Constructor QSqlField::QSqlField(const QSqlField &other)


static void _init_ctor_QSqlField_2182 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSqlField & > (argspec_0);
  decl->set_return_new<QSqlField *> ();
}

static void _call_ctor_QSqlField_2182 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSqlField &arg1 = args.read<const QSqlField & > ();
  ret.write<QSqlField *> (new QSqlField (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSqlField_2182 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSqlField::QSqlField(const QSqlField &other)\nThis method creates an object of class QSqlField.", &_init_ctor_QSqlField_2182, &_call_ctor_QSqlField_2182);
}

// void QSqlField::clear()


static void _init_f_clear_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<void > ();
}

static void _call_f_clear_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ((QSqlField *)cls)->clear ();
}

static qt_gsi::GenericMethod *_create_f_clear_0 ()
{
  return new qt_gsi::GenericMethod ("clear", "@brief Method void QSqlField::clear()\n", false, &_init_f_clear_0, &_call_f_clear_0);
}

// QVariant QSqlField::defaultValue()


static void _init_f_defaultValue_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QVariant > ();
}

static void _call_f_defaultValue_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QVariant > ((QVariant)((QSqlField *)cls)->defaultValue ());
}

static qt_gsi::GenericMethod *_create_f_defaultValue_c0 ()
{
  return new qt_gsi::GenericMethod (":defaultValue", "@brief Method QVariant QSqlField::defaultValue()\n", true, &_init_f_defaultValue_c0, &_call_f_defaultValue_c0);
}

// bool QSqlField::isAutoValue()


static void _init_f_isAutoValue_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isAutoValue_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QSqlField *)cls)->isAutoValue ());
}

static qt_gsi::GenericMethod *_create_f_isAutoValue_c0 ()
{
  return new qt_gsi::GenericMethod ("isAutoValue?|:autoValue", "@brief Method bool QSqlField::isAutoValue()\n", true, &_init_f_isAutoValue_c0, &_call_f_isAutoValue_c0);
}

// bool QSqlField::isGenerated()


static void _init_f_isGenerated_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isGenerated_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QSqlField *)cls)->isGenerated ());
}

static qt_gsi::GenericMethod *_create_f_isGenerated_c0 ()
{
  return new qt_gsi::GenericMethod ("isGenerated?|:generated", "@brief Method bool QSqlField::isGenerated()\n", true, &_init_f_isGenerated_c0, &_call_f_isGenerated_c0);
}

// bool QSqlField::isNull()


static void _init_f_isNull_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isNull_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QSqlField *)cls)->isNull ());
}

static qt_gsi::GenericMethod *_create_f_isNull_c0 ()
{
  return new qt_gsi::GenericMethod ("isNull?", "@brief Method bool QSqlField::isNull()\n", true, &_init_f_isNull_c0, &_call_f_isNull_c0);
}

// bool QSqlField::isReadOnly()


static void _init_f_isReadOnly_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isReadOnly_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QSqlField *)cls)->isReadOnly ());
}

static qt_gsi::GenericMethod *_create_f_isReadOnly_c0 ()
{
  return new qt_gsi::GenericMethod ("isReadOnly?|:readOnly", "@brief Method bool QSqlField::isReadOnly()\n", true, &_init_f_isReadOnly_c0, &_call_f_isReadOnly_c0);
}

// bool QSqlField::isValid()


static void _init_f_isValid_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isValid_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QSqlField *)cls)->isValid ());
}

static qt_gsi::GenericMethod *_create_f_isValid_c0 ()
{
  return new qt_gsi::GenericMethod ("isValid?", "@brief Method bool QSqlField::isValid()\n", true, &_init_f_isValid_c0, &_call_f_isValid_c0);
}

// int QSqlField::length()


static void _init_f_length_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_length_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QSqlField *)cls)->length ());
}

static qt_gsi::GenericMethod *_create_f_length_c0 ()
{
  return new qt_gsi::GenericMethod (":length", "@brief Method int QSqlField::length()\n", true, &_init_f_length_c0, &_call_f_length_c0);
}

// QString QSqlField::name()


static void _init_f_name_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_name_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QSqlField *)cls)->name ());
}

static qt_gsi::GenericMethod *_create_f_name_c0 ()
{
  return new qt_gsi::GenericMethod (":name", "@brief Method QString QSqlField::name()\n", true, &_init_f_name_c0, &_call_f_name_c0);
}

// bool QSqlField::operator!=(const QSqlField &other)


static void _init_f_operator_excl__eq__c2182 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSqlField & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_excl__eq__c2182 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSqlField &arg1 = args.read<const QSqlField & > ();
  ret.write<bool > ((bool)((QSqlField *)cls)->operator!= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_excl__eq__c2182 ()
{
  return new qt_gsi::GenericMethod ("!=", "@brief Method bool QSqlField::operator!=(const QSqlField &other)\n", true, &_init_f_operator_excl__eq__c2182, &_call_f_operator_excl__eq__c2182);
}

// QSqlField &QSqlField::operator=(const QSqlField &other)


static void _init_f_operator_eq__2182 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSqlField & > (argspec_0);
  decl->set_return<QSqlField & > ();
}

static void _call_f_operator_eq__2182 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSqlField &arg1 = args.read<const QSqlField & > ();
  ret.write<QSqlField & > ((QSqlField &)((QSqlField *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__2182 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QSqlField &QSqlField::operator=(const QSqlField &other)\n", false, &_init_f_operator_eq__2182, &_call_f_operator_eq__2182);
}

// bool QSqlField::operator==(const QSqlField &other)


static void _init_f_operator_eq__eq__c2182 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSqlField & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_eq__eq__c2182 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSqlField &arg1 = args.read<const QSqlField & > ();
  ret.write<bool > ((bool)((QSqlField *)cls)->operator== (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__eq__c2182 ()
{
  return new qt_gsi::GenericMethod ("==", "@brief Method bool QSqlField::operator==(const QSqlField &other)\n", true, &_init_f_operator_eq__eq__c2182, &_call_f_operator_eq__eq__c2182);
}

// int QSqlField::precision()


static void _init_f_precision_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_precision_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QSqlField *)cls)->precision ());
}

static qt_gsi::GenericMethod *_create_f_precision_c0 ()
{
  return new qt_gsi::GenericMethod (":precision", "@brief Method int QSqlField::precision()\n", true, &_init_f_precision_c0, &_call_f_precision_c0);
}

// QSqlField::RequiredStatus QSqlField::requiredStatus()


static void _init_f_requiredStatus_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QSqlField::RequiredStatus>::target_type > ();
}

static void _call_f_requiredStatus_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QSqlField::RequiredStatus>::target_type > ((qt_gsi::Converter<QSqlField::RequiredStatus>::target_type)qt_gsi::CppToQtAdaptor<QSqlField::RequiredStatus>(((QSqlField *)cls)->requiredStatus ()));
}

static qt_gsi::GenericMethod *_create_f_requiredStatus_c0 ()
{
  return new qt_gsi::GenericMethod (":requiredStatus", "@brief Method QSqlField::RequiredStatus QSqlField::requiredStatus()\n", true, &_init_f_requiredStatus_c0, &_call_f_requiredStatus_c0);
}

// void QSqlField::setAutoValue(bool autoVal)


static void _init_f_setAutoValue_864 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("autoVal");
  decl->add_arg<bool > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setAutoValue_864 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  bool arg1 = args.read<bool > ();
  ((QSqlField *)cls)->setAutoValue (arg1);
}

static qt_gsi::GenericMethod *_create_f_setAutoValue_864 ()
{
  return new qt_gsi::GenericMethod ("setAutoValue|autoValue=", "@brief Method void QSqlField::setAutoValue(bool autoVal)\n", false, &_init_f_setAutoValue_864, &_call_f_setAutoValue_864);
}

// void QSqlField::setDefaultValue(const QVariant &value)


static void _init_f_setDefaultValue_2119 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("value");
  decl->add_arg<const QVariant & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setDefaultValue_2119 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QVariant &arg1 = args.read<const QVariant & > ();
  ((QSqlField *)cls)->setDefaultValue (arg1);
}

static qt_gsi::GenericMethod *_create_f_setDefaultValue_2119 ()
{
  return new qt_gsi::GenericMethod ("setDefaultValue|defaultValue=", "@brief Method void QSqlField::setDefaultValue(const QVariant &value)\n", false, &_init_f_setDefaultValue_2119, &_call_f_setDefaultValue_2119);
}

// void QSqlField::setGenerated(bool gen)


static void _init_f_setGenerated_864 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("gen");
  decl->add_arg<bool > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setGenerated_864 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  bool arg1 = args.read<bool > ();
  ((QSqlField *)cls)->setGenerated (arg1);
}

static qt_gsi::GenericMethod *_create_f_setGenerated_864 ()
{
  return new qt_gsi::GenericMethod ("setGenerated|generated=", "@brief Method void QSqlField::setGenerated(bool gen)\n", false, &_init_f_setGenerated_864, &_call_f_setGenerated_864);
}

// void QSqlField::setLength(int fieldLength)


static void _init_f_setLength_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("fieldLength");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setLength_767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ((QSqlField *)cls)->setLength (arg1);
}

static qt_gsi::GenericMethod *_create_f_setLength_767 ()
{
  return new qt_gsi::GenericMethod ("setLength|length=", "@brief Method void QSqlField::setLength(int fieldLength)\n", false, &_init_f_setLength_767, &_call_f_setLength_767);
}

// void QSqlField::setName(const QString &name)


static void _init_f_setName_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setName_2025 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ((QSqlField *)cls)->setName (arg1);
}

static qt_gsi::GenericMethod *_create_f_setName_2025 ()
{
  return new qt_gsi::GenericMethod ("setName|name=", "@brief Method void QSqlField::setName(const QString &name)\n", false, &_init_f_setName_2025, &_call_f_setName_2025);
}

// void QSqlField::setPrecision(int precision)


static void _init_f_setPrecision_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("precision");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setPrecision_767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ((QSqlField *)cls)->setPrecision (arg1);
}

static qt_gsi::GenericMethod *_create_f_setPrecision_767 ()
{
  return new qt_gsi::GenericMethod ("setPrecision|precision=", "@brief Method void QSqlField::setPrecision(int precision)\n", false, &_init_f_setPrecision_767, &_call_f_setPrecision_767);
}

// void QSqlField::setReadOnly(bool readOnly)


static void _init_f_setReadOnly_864 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("readOnly");
  decl->add_arg<bool > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setReadOnly_864 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  bool arg1 = args.read<bool > ();
  ((QSqlField *)cls)->setReadOnly (arg1);
}

static qt_gsi::GenericMethod *_create_f_setReadOnly_864 ()
{
  return new qt_gsi::GenericMethod ("setReadOnly|readOnly=", "@brief Method void QSqlField::setReadOnly(bool readOnly)\n", false, &_init_f_setReadOnly_864, &_call_f_setReadOnly_864);
}

// void QSqlField::setRequired(bool required)


static void _init_f_setRequired_864 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("required");
  decl->add_arg<bool > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setRequired_864 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  bool arg1 = args.read<bool > ();
  ((QSqlField *)cls)->setRequired (arg1);
}

static qt_gsi::GenericMethod *_create_f_setRequired_864 ()
{
  return new qt_gsi::GenericMethod ("setRequired", "@brief Method void QSqlField::setRequired(bool required)\n", false, &_init_f_setRequired_864, &_call_f_setRequired_864);
}

// void QSqlField::setRequiredStatus(QSqlField::RequiredStatus status)


static void _init_f_setRequiredStatus_2898 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("status");
  decl->add_arg<const qt_gsi::Converter<QSqlField::RequiredStatus>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setRequiredStatus_2898 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QSqlField::RequiredStatus>::target_type & arg1 = args.read<const qt_gsi::Converter<QSqlField::RequiredStatus>::target_type & > ();
  ((QSqlField *)cls)->setRequiredStatus (qt_gsi::QtToCppAdaptor<QSqlField::RequiredStatus>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setRequiredStatus_2898 ()
{
  return new qt_gsi::GenericMethod ("setRequiredStatus|requiredStatus=", "@brief Method void QSqlField::setRequiredStatus(QSqlField::RequiredStatus status)\n", false, &_init_f_setRequiredStatus_2898, &_call_f_setRequiredStatus_2898);
}

// void QSqlField::setSqlType(int type)


static void _init_f_setSqlType_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("type");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setSqlType_767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ((QSqlField *)cls)->setSqlType (arg1);
}

static qt_gsi::GenericMethod *_create_f_setSqlType_767 ()
{
  return new qt_gsi::GenericMethod ("setSqlType", "@brief Method void QSqlField::setSqlType(int type)\n", false, &_init_f_setSqlType_767, &_call_f_setSqlType_767);
}

// void QSqlField::setType(QVariant::Type type)


static void _init_f_setType_1776 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("type");
  decl->add_arg<const qt_gsi::Converter<QVariant::Type>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setType_1776 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QVariant::Type>::target_type & arg1 = args.read<const qt_gsi::Converter<QVariant::Type>::target_type & > ();
  ((QSqlField *)cls)->setType (qt_gsi::QtToCppAdaptor<QVariant::Type>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setType_1776 ()
{
  return new qt_gsi::GenericMethod ("setType|type=", "@brief Method void QSqlField::setType(QVariant::Type type)\n", false, &_init_f_setType_1776, &_call_f_setType_1776);
}

// void QSqlField::setValue(const QVariant &value)


static void _init_f_setValue_2119 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("value");
  decl->add_arg<const QVariant & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setValue_2119 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QVariant &arg1 = args.read<const QVariant & > ();
  ((QSqlField *)cls)->setValue (arg1);
}

static qt_gsi::GenericMethod *_create_f_setValue_2119 ()
{
  return new qt_gsi::GenericMethod ("setValue|value=", "@brief Method void QSqlField::setValue(const QVariant &value)\n", false, &_init_f_setValue_2119, &_call_f_setValue_2119);
}

// QVariant::Type QSqlField::type()


static void _init_f_type_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QVariant::Type>::target_type > ();
}

static void _call_f_type_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QVariant::Type>::target_type > ((qt_gsi::Converter<QVariant::Type>::target_type)qt_gsi::CppToQtAdaptor<QVariant::Type>(((QSqlField *)cls)->type ()));
}

static qt_gsi::GenericMethod *_create_f_type_c0 ()
{
  return new qt_gsi::GenericMethod (":type", "@brief Method QVariant::Type QSqlField::type()\n", true, &_init_f_type_c0, &_call_f_type_c0);
}

// int QSqlField::typeID()


static void _init_f_typeID_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_typeID_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QSqlField *)cls)->typeID ());
}

static qt_gsi::GenericMethod *_create_f_typeID_c0 ()
{
  return new qt_gsi::GenericMethod ("typeID", "@brief Method int QSqlField::typeID()\n", true, &_init_f_typeID_c0, &_call_f_typeID_c0);
}

// QVariant QSqlField::value()


static void _init_f_value_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QVariant > ();
}

static void _call_f_value_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QVariant > ((QVariant)((QSqlField *)cls)->value ());
}

static qt_gsi::GenericMethod *_create_f_value_c0 ()
{
  return new qt_gsi::GenericMethod (":value", "@brief Method QVariant QSqlField::value()\n", true, &_init_f_value_c0, &_call_f_value_c0);
}


namespace gsi
{
gsi::Class<QSqlField> decl_QSqlField ("QSqlField",
  gsi::Methods(_create_ctor_QSqlField_3693 ()) +
  gsi::Methods(_create_ctor_QSqlField_2182 ()) +
  gsi::Methods(_create_f_clear_0 ()) +
  gsi::Methods(_create_f_defaultValue_c0 ()) +
  gsi::Methods(_create_f_isAutoValue_c0 ()) +
  gsi::Methods(_create_f_isGenerated_c0 ()) +
  gsi::Methods(_create_f_isNull_c0 ()) +
  gsi::Methods(_create_f_isReadOnly_c0 ()) +
  gsi::Methods(_create_f_isValid_c0 ()) +
  gsi::Methods(_create_f_length_c0 ()) +
  gsi::Methods(_create_f_name_c0 ()) +
  gsi::Methods(_create_f_operator_excl__eq__c2182 ()) +
  gsi::Methods(_create_f_operator_eq__2182 ()) +
  gsi::Methods(_create_f_operator_eq__eq__c2182 ()) +
  gsi::Methods(_create_f_precision_c0 ()) +
  gsi::Methods(_create_f_requiredStatus_c0 ()) +
  gsi::Methods(_create_f_setAutoValue_864 ()) +
  gsi::Methods(_create_f_setDefaultValue_2119 ()) +
  gsi::Methods(_create_f_setGenerated_864 ()) +
  gsi::Methods(_create_f_setLength_767 ()) +
  gsi::Methods(_create_f_setName_2025 ()) +
  gsi::Methods(_create_f_setPrecision_767 ()) +
  gsi::Methods(_create_f_setReadOnly_864 ()) +
  gsi::Methods(_create_f_setRequired_864 ()) +
  gsi::Methods(_create_f_setRequiredStatus_2898 ()) +
  gsi::Methods(_create_f_setSqlType_767 ()) +
  gsi::Methods(_create_f_setType_1776 ()) +
  gsi::Methods(_create_f_setValue_2119 ()) +
  gsi::Methods(_create_f_type_c0 ()) +
  gsi::Methods(_create_f_typeID_c0 ()) +
  gsi::Methods(_create_f_value_c0 ()),
  "@qt\n@brief Binding of QSqlField");

}


//  Implementation of the enum wrapper class for QSqlField::RequiredStatus
namespace qt_gsi
{

static QSqlField_RequiredStatus_Enum *c_1_QSqlField_RequiredStatus_Enum () { return new QSqlField_RequiredStatus_Enum (QSqlField::Unknown); }
static QSqlField_RequiredStatus_Enum *c_2_QSqlField_RequiredStatus_Enum () { return new QSqlField_RequiredStatus_Enum (QSqlField::Optional); }
static QSqlField_RequiredStatus_Enum *c_3_QSqlField_RequiredStatus_Enum () { return new QSqlField_RequiredStatus_Enum (QSqlField::Required); }

static gsi::Methods mkdefs_QSqlField_RequiredStatus () {
  return
    gsi::constant ("Unknown", &qt_gsi::c_1_QSqlField_RequiredStatus_Enum, "@brief Enum constant QSqlField::Unknown") +
    gsi::constant ("Optional", &qt_gsi::c_2_QSqlField_RequiredStatus_Enum, "@brief Enum constant QSqlField::Optional") +
    gsi::constant ("Required", &qt_gsi::c_3_QSqlField_RequiredStatus_Enum, "@brief Enum constant QSqlField::Required");
}

static std::string to_s_QSqlField_RequiredStatus_Enum (const QSqlField_RequiredStatus_Enum *e)
{
  if (e->value () == QSqlField::Unknown) { return tl::sprintf ("Unknown (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSqlField::Optional) { return tl::sprintf ("Optional (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSqlField::Required) { return tl::sprintf ("Required (%u)", (unsigned int) e->value ()); }
  return std::string ("(not a valid enum evalue)");
}

static unsigned int to_i_QSqlField_RequiredStatus_Enum (const QSqlField_RequiredStatus_Enum *e)
{
  return (unsigned int) e->value ();
}

static QSqlField_RequiredStatus_Enum *from_i_QSqlField_RequiredStatus_Enum (unsigned int i)
{
  return new QSqlField_RequiredStatus_Enum ((QSqlField::RequiredStatus) i);
}

static bool equalQSqlField_RequiredStatus_Enum (const QSqlField_RequiredStatus_Enum *e, QSqlField_RequiredStatus_Enum d)
{
  return e->value () == d.value ();
}

static bool equal2QSqlField_RequiredStatus_Enum (const QSqlField_RequiredStatus_Enum *e, unsigned int i)
{
  return (unsigned int) e->value () == i;
}

static QSqlField_RequiredStatus_Enums oropQSqlField_RequiredStatus_Enums (const QSqlField_RequiredStatus_Enums *e, const QSqlField_RequiredStatus_Enums &d)
{
  return e->flags () | d.flags ();
}

static QSqlField_RequiredStatus_Enums andopQSqlField_RequiredStatus_Enums (const QSqlField_RequiredStatus_Enums *e, const QSqlField_RequiredStatus_Enums &d)
{
  return e->flags () & d.flags ();
}

static QSqlField_RequiredStatus_Enums xoropQSqlField_RequiredStatus_Enums (const QSqlField_RequiredStatus_Enums *e, const QSqlField_RequiredStatus_Enums &d)
{
  return e->flags () ^ d.flags ();
}

static std::string to_s_QSqlField_RequiredStatus_Enums (const QSqlField_RequiredStatus_Enums *e)
{
  std::string l;
  if (e->testFlag (QSqlField::Unknown)) { if (!l.empty ()) l += "|"; l += "Unknown"; }
  if (e->testFlag (QSqlField::Optional)) { if (!l.empty ()) l += "|"; l += "Optional"; }
  if (e->testFlag (QSqlField::Required)) { if (!l.empty ()) l += "|"; l += "Required"; }
  return tl::sprintf ("%u (%s)", (unsigned int) (e->flags ()), l);
}

static int to_i_QSqlField_RequiredStatus_Enums (const QSqlField_RequiredStatus_Enums *e)
{
  return int (e->flags ());
}

static bool testFlag_QSqlField_RequiredStatus_Enums (const QSqlField_RequiredStatus_Enums *e, const QSqlField_RequiredStatus_Enum &d)
{
  return e->flags ().testFlag (d.value ());
}

}

namespace gsi
{

//  Declarations for QFlags<enum> wrapper class
gsi::Class<qt_gsi::QSqlField_RequiredStatus_Enums> decl_QSqlField_RequiredStatus_Enums ("QSqlField_QFlags_RequiredStatus",
  gsi::method_ext ("|", &qt_gsi::oropQSqlField_RequiredStatus_Enums, gsi::arg ("other"), "@brief 'or' operator between two flag sets") +
  gsi::method_ext ("&", &qt_gsi::andopQSqlField_RequiredStatus_Enums, gsi::arg ("other"), "@brief 'and' operator between two flag sets") +
  gsi::method_ext ("^", &qt_gsi::xoropQSqlField_RequiredStatus_Enums, gsi::arg ("other"), "@brief 'xor' operator between two flag sets") +
  gsi::method_ext ("to_s|inspect", &qt_gsi::to_s_QSqlField_RequiredStatus_Enums, "@brief Converts the flag set to a string") +
  gsi::method_ext ("to_i", &qt_gsi::to_i_QSqlField_RequiredStatus_Enums, "@brief Returns the integer value encoding the flag set") +
  gsi::method_ext ("testFlag", &qt_gsi::testFlag_QSqlField_RequiredStatus_Enums, gsi::arg ("flag"), "@brief Tests whether the flag is contained in the flag set"),
  "@qt\n@brief This class represents the QFlags<QSqlField::RequiredStatus> flag set");

//  Declarations for enum wrapper class
gsi::Class<qt_gsi::QSqlField_RequiredStatus_Enum> decl_QSqlField_RequiredStatus_Enum (decl_QSqlField_RequiredStatus_Enums, "QSqlField_RequiredStatus",
  qt_gsi::mkdefs_QSqlField_RequiredStatus () +
  gsi::method_ext ("to_s|inspect", &qt_gsi::to_s_QSqlField_RequiredStatus_Enum, "@brief Converts the enum class to a string") +
  gsi::method_ext ("to_i", &qt_gsi::to_i_QSqlField_RequiredStatus_Enum, "@brief Converts the enum class to an integer") +
  gsi::method_ext ("==", &qt_gsi::equalQSqlField_RequiredStatus_Enum, gsi::arg ("other"), "@brief Compares the enum class against an enum of it's own type") +
  gsi::method_ext ("==", &qt_gsi::equal2QSqlField_RequiredStatus_Enum, gsi::arg ("other"), "@brief Compares the enum class against an integer") +
  gsi::constructor ("new", &qt_gsi::from_i_QSqlField_RequiredStatus_Enum, gsi::arg ("value"), "@brief Creates the enum object from an integer"),
  "@qt\n@brief This class represents the QSqlField::RequiredStatus enum");

//  Inject the declarations into the parent
static gsi::ClassExt<QSqlField> inject_QSqlField_RequiredStatus_Enum_in_parent (qt_gsi::mkdefs_QSqlField_RequiredStatus ());
static gsi::ClassExt<QSqlField> decl_QSqlField_RequiredStatus_Enum_as_child (decl_QSqlField_RequiredStatus_Enum, "RequiredStatus");

}

