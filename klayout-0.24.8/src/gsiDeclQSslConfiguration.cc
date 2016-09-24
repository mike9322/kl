
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
*  @file gsiDeclQSslConfiguration.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtNetwork.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQSslConfiguration_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QSslConfiguration

//  Constructor QSslConfiguration::QSslConfiguration()


static void _init_ctor_QSslConfiguration_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QSslConfiguration *> ();
}

static void _call_ctor_QSslConfiguration_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSslConfiguration *> (new QSslConfiguration ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSslConfiguration_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSslConfiguration::QSslConfiguration()\nThis method creates an object of class QSslConfiguration.", &_init_ctor_QSslConfiguration_0, &_call_ctor_QSslConfiguration_0);
}

//  Constructor QSslConfiguration::QSslConfiguration(const QSslConfiguration &other)


static void _init_ctor_QSslConfiguration_3068 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslConfiguration & > (argspec_0);
  decl->set_return_new<QSslConfiguration *> ();
}

static void _call_ctor_QSslConfiguration_3068 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslConfiguration &arg1 = args.read<const QSslConfiguration & > ();
  ret.write<QSslConfiguration *> (new QSslConfiguration (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSslConfiguration_3068 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSslConfiguration::QSslConfiguration(const QSslConfiguration &other)\nThis method creates an object of class QSslConfiguration.", &_init_ctor_QSslConfiguration_3068, &_call_ctor_QSslConfiguration_3068);
}

// QList<QSslCertificate> QSslConfiguration::caCertificates()


static void _init_f_caCertificates_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QSslCertificate> >::target_type > ();
}

static void _call_f_caCertificates_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QSslCertificate> >::target_type > ((qt_gsi::Converter<QList<QSslCertificate> >::target_type)qt_gsi::CppToQtAdaptor<QList<QSslCertificate> >(((QSslConfiguration *)cls)->caCertificates ()));
}

static qt_gsi::GenericMethod *_create_f_caCertificates_c0 ()
{
  return new qt_gsi::GenericMethod (":caCertificates", "@brief Method QList<QSslCertificate> QSslConfiguration::caCertificates()\n", true, &_init_f_caCertificates_c0, &_call_f_caCertificates_c0);
}

// QList<QSslCipher> QSslConfiguration::ciphers()


static void _init_f_ciphers_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QSslCipher> >::target_type > ();
}

static void _call_f_ciphers_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QSslCipher> >::target_type > ((qt_gsi::Converter<QList<QSslCipher> >::target_type)qt_gsi::CppToQtAdaptor<QList<QSslCipher> >(((QSslConfiguration *)cls)->ciphers ()));
}

static qt_gsi::GenericMethod *_create_f_ciphers_c0 ()
{
  return new qt_gsi::GenericMethod (":ciphers", "@brief Method QList<QSslCipher> QSslConfiguration::ciphers()\n", true, &_init_f_ciphers_c0, &_call_f_ciphers_c0);
}

// bool QSslConfiguration::isNull()


static void _init_f_isNull_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isNull_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QSslConfiguration *)cls)->isNull ());
}

static qt_gsi::GenericMethod *_create_f_isNull_c0 ()
{
  return new qt_gsi::GenericMethod ("isNull?", "@brief Method bool QSslConfiguration::isNull()\n", true, &_init_f_isNull_c0, &_call_f_isNull_c0);
}

// QSslCertificate QSslConfiguration::localCertificate()


static void _init_f_localCertificate_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QSslCertificate > ();
}

static void _call_f_localCertificate_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSslCertificate > ((QSslCertificate)((QSslConfiguration *)cls)->localCertificate ());
}

static qt_gsi::GenericMethod *_create_f_localCertificate_c0 ()
{
  return new qt_gsi::GenericMethod (":localCertificate", "@brief Method QSslCertificate QSslConfiguration::localCertificate()\n", true, &_init_f_localCertificate_c0, &_call_f_localCertificate_c0);
}

// bool QSslConfiguration::operator!=(const QSslConfiguration &other)


static void _init_f_operator_excl__eq__c3068 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslConfiguration & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_excl__eq__c3068 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslConfiguration &arg1 = args.read<const QSslConfiguration & > ();
  ret.write<bool > ((bool)((QSslConfiguration *)cls)->operator!= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_excl__eq__c3068 ()
{
  return new qt_gsi::GenericMethod ("!=", "@brief Method bool QSslConfiguration::operator!=(const QSslConfiguration &other)\n", true, &_init_f_operator_excl__eq__c3068, &_call_f_operator_excl__eq__c3068);
}

// QSslConfiguration &QSslConfiguration::operator=(const QSslConfiguration &other)


static void _init_f_operator_eq__3068 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslConfiguration & > (argspec_0);
  decl->set_return<QSslConfiguration & > ();
}

static void _call_f_operator_eq__3068 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslConfiguration &arg1 = args.read<const QSslConfiguration & > ();
  ret.write<QSslConfiguration & > ((QSslConfiguration &)((QSslConfiguration *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__3068 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QSslConfiguration &QSslConfiguration::operator=(const QSslConfiguration &other)\n", false, &_init_f_operator_eq__3068, &_call_f_operator_eq__3068);
}

// bool QSslConfiguration::operator==(const QSslConfiguration &other)


static void _init_f_operator_eq__eq__c3068 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslConfiguration & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_eq__eq__c3068 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslConfiguration &arg1 = args.read<const QSslConfiguration & > ();
  ret.write<bool > ((bool)((QSslConfiguration *)cls)->operator== (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__eq__c3068 ()
{
  return new qt_gsi::GenericMethod ("==", "@brief Method bool QSslConfiguration::operator==(const QSslConfiguration &other)\n", true, &_init_f_operator_eq__eq__c3068, &_call_f_operator_eq__eq__c3068);
}

// QSslCertificate QSslConfiguration::peerCertificate()


static void _init_f_peerCertificate_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QSslCertificate > ();
}

static void _call_f_peerCertificate_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSslCertificate > ((QSslCertificate)((QSslConfiguration *)cls)->peerCertificate ());
}

static qt_gsi::GenericMethod *_create_f_peerCertificate_c0 ()
{
  return new qt_gsi::GenericMethod ("peerCertificate", "@brief Method QSslCertificate QSslConfiguration::peerCertificate()\n", true, &_init_f_peerCertificate_c0, &_call_f_peerCertificate_c0);
}

// QList<QSslCertificate> QSslConfiguration::peerCertificateChain()


static void _init_f_peerCertificateChain_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QSslCertificate> >::target_type > ();
}

static void _call_f_peerCertificateChain_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QSslCertificate> >::target_type > ((qt_gsi::Converter<QList<QSslCertificate> >::target_type)qt_gsi::CppToQtAdaptor<QList<QSslCertificate> >(((QSslConfiguration *)cls)->peerCertificateChain ()));
}

static qt_gsi::GenericMethod *_create_f_peerCertificateChain_c0 ()
{
  return new qt_gsi::GenericMethod ("peerCertificateChain", "@brief Method QList<QSslCertificate> QSslConfiguration::peerCertificateChain()\n", true, &_init_f_peerCertificateChain_c0, &_call_f_peerCertificateChain_c0);
}

// int QSslConfiguration::peerVerifyDepth()


static void _init_f_peerVerifyDepth_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_peerVerifyDepth_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QSslConfiguration *)cls)->peerVerifyDepth ());
}

static qt_gsi::GenericMethod *_create_f_peerVerifyDepth_c0 ()
{
  return new qt_gsi::GenericMethod (":peerVerifyDepth", "@brief Method int QSslConfiguration::peerVerifyDepth()\n", true, &_init_f_peerVerifyDepth_c0, &_call_f_peerVerifyDepth_c0);
}

// QSslSocket::PeerVerifyMode QSslConfiguration::peerVerifyMode()


static void _init_f_peerVerifyMode_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QSslSocket::PeerVerifyMode>::target_type > ();
}

static void _call_f_peerVerifyMode_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QSslSocket::PeerVerifyMode>::target_type > ((qt_gsi::Converter<QSslSocket::PeerVerifyMode>::target_type)qt_gsi::CppToQtAdaptor<QSslSocket::PeerVerifyMode>(((QSslConfiguration *)cls)->peerVerifyMode ()));
}

static qt_gsi::GenericMethod *_create_f_peerVerifyMode_c0 ()
{
  return new qt_gsi::GenericMethod (":peerVerifyMode", "@brief Method QSslSocket::PeerVerifyMode QSslConfiguration::peerVerifyMode()\n", true, &_init_f_peerVerifyMode_c0, &_call_f_peerVerifyMode_c0);
}

// QSslKey QSslConfiguration::privateKey()


static void _init_f_privateKey_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QSslKey > ();
}

static void _call_f_privateKey_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSslKey > ((QSslKey)((QSslConfiguration *)cls)->privateKey ());
}

static qt_gsi::GenericMethod *_create_f_privateKey_c0 ()
{
  return new qt_gsi::GenericMethod (":privateKey", "@brief Method QSslKey QSslConfiguration::privateKey()\n", true, &_init_f_privateKey_c0, &_call_f_privateKey_c0);
}

// QSsl::SslProtocol QSslConfiguration::protocol()


static void _init_f_protocol_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QSsl::SslProtocol>::target_type > ();
}

static void _call_f_protocol_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QSsl::SslProtocol>::target_type > ((qt_gsi::Converter<QSsl::SslProtocol>::target_type)qt_gsi::CppToQtAdaptor<QSsl::SslProtocol>(((QSslConfiguration *)cls)->protocol ()));
}

static qt_gsi::GenericMethod *_create_f_protocol_c0 ()
{
  return new qt_gsi::GenericMethod (":protocol", "@brief Method QSsl::SslProtocol QSslConfiguration::protocol()\n", true, &_init_f_protocol_c0, &_call_f_protocol_c0);
}

// QSslCipher QSslConfiguration::sessionCipher()


static void _init_f_sessionCipher_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QSslCipher > ();
}

static void _call_f_sessionCipher_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSslCipher > ((QSslCipher)((QSslConfiguration *)cls)->sessionCipher ());
}

static qt_gsi::GenericMethod *_create_f_sessionCipher_c0 ()
{
  return new qt_gsi::GenericMethod ("sessionCipher", "@brief Method QSslCipher QSslConfiguration::sessionCipher()\n", true, &_init_f_sessionCipher_c0, &_call_f_sessionCipher_c0);
}

// void QSslConfiguration::setCaCertificates(const QList<QSslCertificate> &certificates)


static void _init_f_setCaCertificates_3438 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("certificates");
  decl->add_arg<const qt_gsi::Converter<QList<QSslCertificate> >::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setCaCertificates_3438 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QList<QSslCertificate> >::target_type & arg1 = args.read<const qt_gsi::Converter<QList<QSslCertificate> >::target_type & > ();
  ((QSslConfiguration *)cls)->setCaCertificates (qt_gsi::QtToCppAdaptor<QList<QSslCertificate> >(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setCaCertificates_3438 ()
{
  return new qt_gsi::GenericMethod ("setCaCertificates|caCertificates=", "@brief Method void QSslConfiguration::setCaCertificates(const QList<QSslCertificate> &certificates)\n", false, &_init_f_setCaCertificates_3438, &_call_f_setCaCertificates_3438);
}

// void QSslConfiguration::setCiphers(const QList<QSslCipher> &ciphers)


static void _init_f_setCiphers_2918 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("ciphers");
  decl->add_arg<const qt_gsi::Converter<QList<QSslCipher> >::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setCiphers_2918 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QList<QSslCipher> >::target_type & arg1 = args.read<const qt_gsi::Converter<QList<QSslCipher> >::target_type & > ();
  ((QSslConfiguration *)cls)->setCiphers (qt_gsi::QtToCppAdaptor<QList<QSslCipher> >(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setCiphers_2918 ()
{
  return new qt_gsi::GenericMethod ("setCiphers|ciphers=", "@brief Method void QSslConfiguration::setCiphers(const QList<QSslCipher> &ciphers)\n", false, &_init_f_setCiphers_2918, &_call_f_setCiphers_2918);
}

// void QSslConfiguration::setLocalCertificate(const QSslCertificate &certificate)


static void _init_f_setLocalCertificate_2823 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("certificate");
  decl->add_arg<const QSslCertificate & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setLocalCertificate_2823 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslCertificate &arg1 = args.read<const QSslCertificate & > ();
  ((QSslConfiguration *)cls)->setLocalCertificate (arg1);
}

static qt_gsi::GenericMethod *_create_f_setLocalCertificate_2823 ()
{
  return new qt_gsi::GenericMethod ("setLocalCertificate|localCertificate=", "@brief Method void QSslConfiguration::setLocalCertificate(const QSslCertificate &certificate)\n", false, &_init_f_setLocalCertificate_2823, &_call_f_setLocalCertificate_2823);
}

// void QSslConfiguration::setPeerVerifyDepth(int depth)


static void _init_f_setPeerVerifyDepth_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("depth");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setPeerVerifyDepth_767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ((QSslConfiguration *)cls)->setPeerVerifyDepth (arg1);
}

static qt_gsi::GenericMethod *_create_f_setPeerVerifyDepth_767 ()
{
  return new qt_gsi::GenericMethod ("setPeerVerifyDepth|peerVerifyDepth=", "@brief Method void QSslConfiguration::setPeerVerifyDepth(int depth)\n", false, &_init_f_setPeerVerifyDepth_767, &_call_f_setPeerVerifyDepth_767);
}

// void QSslConfiguration::setPeerVerifyMode(QSslSocket::PeerVerifyMode mode)


static void _init_f_setPeerVerifyMode_2970 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("mode");
  decl->add_arg<const qt_gsi::Converter<QSslSocket::PeerVerifyMode>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setPeerVerifyMode_2970 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QSslSocket::PeerVerifyMode>::target_type & arg1 = args.read<const qt_gsi::Converter<QSslSocket::PeerVerifyMode>::target_type & > ();
  ((QSslConfiguration *)cls)->setPeerVerifyMode (qt_gsi::QtToCppAdaptor<QSslSocket::PeerVerifyMode>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setPeerVerifyMode_2970 ()
{
  return new qt_gsi::GenericMethod ("setPeerVerifyMode|peerVerifyMode=", "@brief Method void QSslConfiguration::setPeerVerifyMode(QSslSocket::PeerVerifyMode mode)\n", false, &_init_f_setPeerVerifyMode_2970, &_call_f_setPeerVerifyMode_2970);
}

// void QSslConfiguration::setPrivateKey(const QSslKey &key)


static void _init_f_setPrivateKey_1997 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("key");
  decl->add_arg<const QSslKey & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setPrivateKey_1997 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslKey &arg1 = args.read<const QSslKey & > ();
  ((QSslConfiguration *)cls)->setPrivateKey (arg1);
}

static qt_gsi::GenericMethod *_create_f_setPrivateKey_1997 ()
{
  return new qt_gsi::GenericMethod ("setPrivateKey|privateKey=", "@brief Method void QSslConfiguration::setPrivateKey(const QSslKey &key)\n", false, &_init_f_setPrivateKey_1997, &_call_f_setPrivateKey_1997);
}

// void QSslConfiguration::setProtocol(QSsl::SslProtocol protocol)


static void _init_f_setProtocol_2095 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("protocol");
  decl->add_arg<const qt_gsi::Converter<QSsl::SslProtocol>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setProtocol_2095 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QSsl::SslProtocol>::target_type & arg1 = args.read<const qt_gsi::Converter<QSsl::SslProtocol>::target_type & > ();
  ((QSslConfiguration *)cls)->setProtocol (qt_gsi::QtToCppAdaptor<QSsl::SslProtocol>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setProtocol_2095 ()
{
  return new qt_gsi::GenericMethod ("setProtocol|protocol=", "@brief Method void QSslConfiguration::setProtocol(QSsl::SslProtocol protocol)\n", false, &_init_f_setProtocol_2095, &_call_f_setProtocol_2095);
}

// static QSslConfiguration QSslConfiguration::defaultConfiguration()


static void _init_f_defaultConfiguration_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<QSslConfiguration > ();
}

static void _call_f_defaultConfiguration_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSslConfiguration > ((QSslConfiguration)QSslConfiguration::defaultConfiguration ());
}

static qt_gsi::GenericStaticMethod *_create_f_defaultConfiguration_0 ()
{
  return new qt_gsi::GenericStaticMethod (":defaultConfiguration", "@brief Static method QSslConfiguration QSslConfiguration::defaultConfiguration()\nThis method is static and can be called without an instance.", &_init_f_defaultConfiguration_0, &_call_f_defaultConfiguration_0);
}

// static void QSslConfiguration::setDefaultConfiguration(const QSslConfiguration &configuration)


static void _init_f_setDefaultConfiguration_3068 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("configuration");
  decl->add_arg<const QSslConfiguration & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setDefaultConfiguration_3068 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslConfiguration &arg1 = args.read<const QSslConfiguration & > ();
  QSslConfiguration::setDefaultConfiguration (arg1);
}

static qt_gsi::GenericStaticMethod *_create_f_setDefaultConfiguration_3068 ()
{
  return new qt_gsi::GenericStaticMethod ("setDefaultConfiguration|defaultConfiguration=", "@brief Static method void QSslConfiguration::setDefaultConfiguration(const QSslConfiguration &configuration)\nThis method is static and can be called without an instance.", &_init_f_setDefaultConfiguration_3068, &_call_f_setDefaultConfiguration_3068);
}


namespace gsi
{
gsi::Class<QSslConfiguration> decl_QSslConfiguration ("QSslConfiguration",
  gsi::Methods(_create_ctor_QSslConfiguration_0 ()) +
  gsi::Methods(_create_ctor_QSslConfiguration_3068 ()) +
  gsi::Methods(_create_f_caCertificates_c0 ()) +
  gsi::Methods(_create_f_ciphers_c0 ()) +
  gsi::Methods(_create_f_isNull_c0 ()) +
  gsi::Methods(_create_f_localCertificate_c0 ()) +
  gsi::Methods(_create_f_operator_excl__eq__c3068 ()) +
  gsi::Methods(_create_f_operator_eq__3068 ()) +
  gsi::Methods(_create_f_operator_eq__eq__c3068 ()) +
  gsi::Methods(_create_f_peerCertificate_c0 ()) +
  gsi::Methods(_create_f_peerCertificateChain_c0 ()) +
  gsi::Methods(_create_f_peerVerifyDepth_c0 ()) +
  gsi::Methods(_create_f_peerVerifyMode_c0 ()) +
  gsi::Methods(_create_f_privateKey_c0 ()) +
  gsi::Methods(_create_f_protocol_c0 ()) +
  gsi::Methods(_create_f_sessionCipher_c0 ()) +
  gsi::Methods(_create_f_setCaCertificates_3438 ()) +
  gsi::Methods(_create_f_setCiphers_2918 ()) +
  gsi::Methods(_create_f_setLocalCertificate_2823 ()) +
  gsi::Methods(_create_f_setPeerVerifyDepth_767 ()) +
  gsi::Methods(_create_f_setPeerVerifyMode_2970 ()) +
  gsi::Methods(_create_f_setPrivateKey_1997 ()) +
  gsi::Methods(_create_f_setProtocol_2095 ()) +
  gsi::Methods(_create_f_defaultConfiguration_0 ()) +
  gsi::Methods(_create_f_setDefaultConfiguration_3068 ()),
  "@qt\n@brief Binding of QSslConfiguration");

}

