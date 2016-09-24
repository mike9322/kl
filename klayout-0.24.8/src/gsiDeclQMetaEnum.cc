
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
*  @file gsiDeclQMetaEnum.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtCore.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQMetaEnum_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QMetaEnum

//  Constructor QMetaEnum::QMetaEnum()


static void _init_ctor_QMetaEnum_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QMetaEnum *> ();
}

static void _call_ctor_QMetaEnum_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QMetaEnum *> (new QMetaEnum ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QMetaEnum_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QMetaEnum::QMetaEnum()\nThis method creates an object of class QMetaEnum.", &_init_ctor_QMetaEnum_0, &_call_ctor_QMetaEnum_0);
}

// const QMetaObject *QMetaEnum::enclosingMetaObject()


static void _init_f_enclosingMetaObject_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<const QMetaObject * > ();
}

static void _call_f_enclosingMetaObject_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const QMetaObject * > ((const QMetaObject *)((QMetaEnum *)cls)->enclosingMetaObject ());
}

static qt_gsi::GenericMethod *_create_f_enclosingMetaObject_c0 ()
{
  return new qt_gsi::GenericMethod ("enclosingMetaObject", "@brief Method const QMetaObject *QMetaEnum::enclosingMetaObject()\n", true, &_init_f_enclosingMetaObject_c0, &_call_f_enclosingMetaObject_c0);
}

// bool QMetaEnum::isFlag()


static void _init_f_isFlag_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isFlag_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QMetaEnum *)cls)->isFlag ());
}

static qt_gsi::GenericMethod *_create_f_isFlag_c0 ()
{
  return new qt_gsi::GenericMethod ("isFlag?", "@brief Method bool QMetaEnum::isFlag()\n", true, &_init_f_isFlag_c0, &_call_f_isFlag_c0);
}

// bool QMetaEnum::isValid()


static void _init_f_isValid_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isValid_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QMetaEnum *)cls)->isValid ());
}

static qt_gsi::GenericMethod *_create_f_isValid_c0 ()
{
  return new qt_gsi::GenericMethod ("isValid?", "@brief Method bool QMetaEnum::isValid()\n", true, &_init_f_isValid_c0, &_call_f_isValid_c0);
}

// const char *QMetaEnum::key(int index)


static void _init_f_key_c767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("index");
  decl->add_arg<int > (argspec_0);
  decl->set_return<const char * > ();
}

static void _call_f_key_c767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ret.write<const char * > ((const char *)((QMetaEnum *)cls)->key (arg1));
}

static qt_gsi::GenericMethod *_create_f_key_c767 ()
{
  return new qt_gsi::GenericMethod ("key", "@brief Method const char *QMetaEnum::key(int index)\n", true, &_init_f_key_c767, &_call_f_key_c767);
}

// int QMetaEnum::keyCount()


static void _init_f_keyCount_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_keyCount_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QMetaEnum *)cls)->keyCount ());
}

static qt_gsi::GenericMethod *_create_f_keyCount_c0 ()
{
  return new qt_gsi::GenericMethod ("keyCount", "@brief Method int QMetaEnum::keyCount()\n", true, &_init_f_keyCount_c0, &_call_f_keyCount_c0);
}

// int QMetaEnum::keyToValue(const char *key)


static void _init_f_keyToValue_c1731 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("key");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<int > ();
}

static void _call_f_keyToValue_c1731 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  ret.write<int > ((int)((QMetaEnum *)cls)->keyToValue (arg1));
}

static qt_gsi::GenericMethod *_create_f_keyToValue_c1731 ()
{
  return new qt_gsi::GenericMethod ("keyToValue", "@brief Method int QMetaEnum::keyToValue(const char *key)\n", true, &_init_f_keyToValue_c1731, &_call_f_keyToValue_c1731);
}

// int QMetaEnum::keysToValue(const char *keys)


static void _init_f_keysToValue_c1731 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("keys");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<int > ();
}

static void _call_f_keysToValue_c1731 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  ret.write<int > ((int)((QMetaEnum *)cls)->keysToValue (arg1));
}

static qt_gsi::GenericMethod *_create_f_keysToValue_c1731 ()
{
  return new qt_gsi::GenericMethod ("keysToValue", "@brief Method int QMetaEnum::keysToValue(const char *keys)\n", true, &_init_f_keysToValue_c1731, &_call_f_keysToValue_c1731);
}

// const char *QMetaEnum::name()


static void _init_f_name_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<const char * > ();
}

static void _call_f_name_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const char * > ((const char *)((QMetaEnum *)cls)->name ());
}

static qt_gsi::GenericMethod *_create_f_name_c0 ()
{
  return new qt_gsi::GenericMethod ("name", "@brief Method const char *QMetaEnum::name()\n", true, &_init_f_name_c0, &_call_f_name_c0);
}

// const char *QMetaEnum::scope()


static void _init_f_scope_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<const char * > ();
}

static void _call_f_scope_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const char * > ((const char *)((QMetaEnum *)cls)->scope ());
}

static qt_gsi::GenericMethod *_create_f_scope_c0 ()
{
  return new qt_gsi::GenericMethod ("scope", "@brief Method const char *QMetaEnum::scope()\n", true, &_init_f_scope_c0, &_call_f_scope_c0);
}

// int QMetaEnum::value(int index)


static void _init_f_value_c767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("index");
  decl->add_arg<int > (argspec_0);
  decl->set_return<int > ();
}

static void _call_f_value_c767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ret.write<int > ((int)((QMetaEnum *)cls)->value (arg1));
}

static qt_gsi::GenericMethod *_create_f_value_c767 ()
{
  return new qt_gsi::GenericMethod ("value", "@brief Method int QMetaEnum::value(int index)\n", true, &_init_f_value_c767, &_call_f_value_c767);
}

// const char *QMetaEnum::valueToKey(int value)


static void _init_f_valueToKey_c767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("value");
  decl->add_arg<int > (argspec_0);
  decl->set_return<const char * > ();
}

static void _call_f_valueToKey_c767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ret.write<const char * > ((const char *)((QMetaEnum *)cls)->valueToKey (arg1));
}

static qt_gsi::GenericMethod *_create_f_valueToKey_c767 ()
{
  return new qt_gsi::GenericMethod ("valueToKey", "@brief Method const char *QMetaEnum::valueToKey(int value)\n", true, &_init_f_valueToKey_c767, &_call_f_valueToKey_c767);
}

// QByteArray QMetaEnum::valueToKeys(int value)


static void _init_f_valueToKeys_c767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("value");
  decl->add_arg<int > (argspec_0);
  decl->set_return<QByteArray > ();
}

static void _call_f_valueToKeys_c767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ret.write<QByteArray > ((QByteArray)((QMetaEnum *)cls)->valueToKeys (arg1));
}

static qt_gsi::GenericMethod *_create_f_valueToKeys_c767 ()
{
  return new qt_gsi::GenericMethod ("valueToKeys", "@brief Method QByteArray QMetaEnum::valueToKeys(int value)\n", true, &_init_f_valueToKeys_c767, &_call_f_valueToKeys_c767);
}


namespace gsi
{
gsi::Class<QMetaEnum> decl_QMetaEnum ("QMetaEnum",
  gsi::Methods(_create_ctor_QMetaEnum_0 ()) +
  gsi::Methods(_create_f_enclosingMetaObject_c0 ()) +
  gsi::Methods(_create_f_isFlag_c0 ()) +
  gsi::Methods(_create_f_isValid_c0 ()) +
  gsi::Methods(_create_f_key_c767 ()) +
  gsi::Methods(_create_f_keyCount_c0 ()) +
  gsi::Methods(_create_f_keyToValue_c1731 ()) +
  gsi::Methods(_create_f_keysToValue_c1731 ()) +
  gsi::Methods(_create_f_name_c0 ()) +
  gsi::Methods(_create_f_scope_c0 ()) +
  gsi::Methods(_create_f_value_c767 ()) +
  gsi::Methods(_create_f_valueToKey_c767 ()) +
  gsi::Methods(_create_f_valueToKeys_c767 ()),
  "@qt\n@brief Binding of QMetaEnum");

}

