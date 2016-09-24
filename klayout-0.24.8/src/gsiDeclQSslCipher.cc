
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
*  @file gsiDeclQSslCipher.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtNetwork.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQSslCipher_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QSslCipher

//  Constructor QSslCipher::QSslCipher()


static void _init_ctor_QSslCipher_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QSslCipher *> ();
}

static void _call_ctor_QSslCipher_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSslCipher *> (new QSslCipher ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSslCipher_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSslCipher::QSslCipher()\nThis method creates an object of class QSslCipher.", &_init_ctor_QSslCipher_0, &_call_ctor_QSslCipher_0);
}

//  Constructor QSslCipher::QSslCipher(const QString &name, QSsl::SslProtocol protocol)


static void _init_ctor_QSslCipher_4012 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("protocol");
  decl->add_arg<const qt_gsi::Converter<QSsl::SslProtocol>::target_type & > (argspec_1);
  decl->set_return_new<QSslCipher *> ();
}

static void _call_ctor_QSslCipher_4012 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  const qt_gsi::Converter<QSsl::SslProtocol>::target_type & arg2 = args.read<const qt_gsi::Converter<QSsl::SslProtocol>::target_type & > ();
  ret.write<QSslCipher *> (new QSslCipher (arg1, qt_gsi::QtToCppAdaptor<QSsl::SslProtocol>(arg2).cref()));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSslCipher_4012 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSslCipher::QSslCipher(const QString &name, QSsl::SslProtocol protocol)\nThis method creates an object of class QSslCipher.", &_init_ctor_QSslCipher_4012, &_call_ctor_QSslCipher_4012);
}

//  Constructor QSslCipher::QSslCipher(const QSslCipher &other)


static void _init_ctor_QSslCipher_2303 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslCipher & > (argspec_0);
  decl->set_return_new<QSslCipher *> ();
}

static void _call_ctor_QSslCipher_2303 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslCipher &arg1 = args.read<const QSslCipher & > ();
  ret.write<QSslCipher *> (new QSslCipher (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSslCipher_2303 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSslCipher::QSslCipher(const QSslCipher &other)\nThis method creates an object of class QSslCipher.", &_init_ctor_QSslCipher_2303, &_call_ctor_QSslCipher_2303);
}

// QString QSslCipher::authenticationMethod()


static void _init_f_authenticationMethod_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_authenticationMethod_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QSslCipher *)cls)->authenticationMethod ());
}

static qt_gsi::GenericMethod *_create_f_authenticationMethod_c0 ()
{
  return new qt_gsi::GenericMethod ("authenticationMethod", "@brief Method QString QSslCipher::authenticationMethod()\n", true, &_init_f_authenticationMethod_c0, &_call_f_authenticationMethod_c0);
}

// QString QSslCipher::encryptionMethod()


static void _init_f_encryptionMethod_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_encryptionMethod_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QSslCipher *)cls)->encryptionMethod ());
}

static qt_gsi::GenericMethod *_create_f_encryptionMethod_c0 ()
{
  return new qt_gsi::GenericMethod ("encryptionMethod", "@brief Method QString QSslCipher::encryptionMethod()\n", true, &_init_f_encryptionMethod_c0, &_call_f_encryptionMethod_c0);
}

// bool QSslCipher::isNull()


static void _init_f_isNull_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isNull_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QSslCipher *)cls)->isNull ());
}

static qt_gsi::GenericMethod *_create_f_isNull_c0 ()
{
  return new qt_gsi::GenericMethod ("isNull?", "@brief Method bool QSslCipher::isNull()\n", true, &_init_f_isNull_c0, &_call_f_isNull_c0);
}

// QString QSslCipher::keyExchangeMethod()


static void _init_f_keyExchangeMethod_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_keyExchangeMethod_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QSslCipher *)cls)->keyExchangeMethod ());
}

static qt_gsi::GenericMethod *_create_f_keyExchangeMethod_c0 ()
{
  return new qt_gsi::GenericMethod ("keyExchangeMethod", "@brief Method QString QSslCipher::keyExchangeMethod()\n", true, &_init_f_keyExchangeMethod_c0, &_call_f_keyExchangeMethod_c0);
}

// QString QSslCipher::name()


static void _init_f_name_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_name_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QSslCipher *)cls)->name ());
}

static qt_gsi::GenericMethod *_create_f_name_c0 ()
{
  return new qt_gsi::GenericMethod ("name", "@brief Method QString QSslCipher::name()\n", true, &_init_f_name_c0, &_call_f_name_c0);
}

// bool QSslCipher::operator!=(const QSslCipher &other)


static void _init_f_operator_excl__eq__c2303 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslCipher & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_excl__eq__c2303 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslCipher &arg1 = args.read<const QSslCipher & > ();
  ret.write<bool > ((bool)((QSslCipher *)cls)->operator!= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_excl__eq__c2303 ()
{
  return new qt_gsi::GenericMethod ("!=", "@brief Method bool QSslCipher::operator!=(const QSslCipher &other)\n", true, &_init_f_operator_excl__eq__c2303, &_call_f_operator_excl__eq__c2303);
}

// QSslCipher &QSslCipher::operator=(const QSslCipher &other)


static void _init_f_operator_eq__2303 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslCipher & > (argspec_0);
  decl->set_return<QSslCipher & > ();
}

static void _call_f_operator_eq__2303 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslCipher &arg1 = args.read<const QSslCipher & > ();
  ret.write<QSslCipher & > ((QSslCipher &)((QSslCipher *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__2303 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QSslCipher &QSslCipher::operator=(const QSslCipher &other)\n", false, &_init_f_operator_eq__2303, &_call_f_operator_eq__2303);
}

// bool QSslCipher::operator==(const QSslCipher &other)


static void _init_f_operator_eq__eq__c2303 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslCipher & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_eq__eq__c2303 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslCipher &arg1 = args.read<const QSslCipher & > ();
  ret.write<bool > ((bool)((QSslCipher *)cls)->operator== (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__eq__c2303 ()
{
  return new qt_gsi::GenericMethod ("==", "@brief Method bool QSslCipher::operator==(const QSslCipher &other)\n", true, &_init_f_operator_eq__eq__c2303, &_call_f_operator_eq__eq__c2303);
}

// QSsl::SslProtocol QSslCipher::protocol()


static void _init_f_protocol_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QSsl::SslProtocol>::target_type > ();
}

static void _call_f_protocol_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QSsl::SslProtocol>::target_type > ((qt_gsi::Converter<QSsl::SslProtocol>::target_type)qt_gsi::CppToQtAdaptor<QSsl::SslProtocol>(((QSslCipher *)cls)->protocol ()));
}

static qt_gsi::GenericMethod *_create_f_protocol_c0 ()
{
  return new qt_gsi::GenericMethod ("protocol", "@brief Method QSsl::SslProtocol QSslCipher::protocol()\n", true, &_init_f_protocol_c0, &_call_f_protocol_c0);
}

// QString QSslCipher::protocolString()


static void _init_f_protocolString_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_protocolString_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QSslCipher *)cls)->protocolString ());
}

static qt_gsi::GenericMethod *_create_f_protocolString_c0 ()
{
  return new qt_gsi::GenericMethod ("protocolString", "@brief Method QString QSslCipher::protocolString()\n", true, &_init_f_protocolString_c0, &_call_f_protocolString_c0);
}

// int QSslCipher::supportedBits()


static void _init_f_supportedBits_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_supportedBits_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QSslCipher *)cls)->supportedBits ());
}

static qt_gsi::GenericMethod *_create_f_supportedBits_c0 ()
{
  return new qt_gsi::GenericMethod ("supportedBits", "@brief Method int QSslCipher::supportedBits()\n", true, &_init_f_supportedBits_c0, &_call_f_supportedBits_c0);
}

// int QSslCipher::usedBits()


static void _init_f_usedBits_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_usedBits_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QSslCipher *)cls)->usedBits ());
}

static qt_gsi::GenericMethod *_create_f_usedBits_c0 ()
{
  return new qt_gsi::GenericMethod ("usedBits", "@brief Method int QSslCipher::usedBits()\n", true, &_init_f_usedBits_c0, &_call_f_usedBits_c0);
}


namespace gsi
{
gsi::Class<QSslCipher> decl_QSslCipher ("QSslCipher",
  gsi::Methods(_create_ctor_QSslCipher_0 ()) +
  gsi::Methods(_create_ctor_QSslCipher_4012 ()) +
  gsi::Methods(_create_ctor_QSslCipher_2303 ()) +
  gsi::Methods(_create_f_authenticationMethod_c0 ()) +
  gsi::Methods(_create_f_encryptionMethod_c0 ()) +
  gsi::Methods(_create_f_isNull_c0 ()) +
  gsi::Methods(_create_f_keyExchangeMethod_c0 ()) +
  gsi::Methods(_create_f_name_c0 ()) +
  gsi::Methods(_create_f_operator_excl__eq__c2303 ()) +
  gsi::Methods(_create_f_operator_eq__2303 ()) +
  gsi::Methods(_create_f_operator_eq__eq__c2303 ()) +
  gsi::Methods(_create_f_protocol_c0 ()) +
  gsi::Methods(_create_f_protocolString_c0 ()) +
  gsi::Methods(_create_f_supportedBits_c0 ()) +
  gsi::Methods(_create_f_usedBits_c0 ()),
  "@qt\n@brief Binding of QSslCipher");

}

