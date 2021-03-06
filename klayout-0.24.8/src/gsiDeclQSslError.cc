
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
*  @file gsiDeclQSslError.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtNetwork.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQSslError_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QSslError

//  Constructor QSslError::QSslError()


static void _init_ctor_QSslError_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QSslError *> ();
}

static void _call_ctor_QSslError_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSslError *> (new QSslError ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSslError_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSslError::QSslError()\nThis method creates an object of class QSslError.", &_init_ctor_QSslError_0, &_call_ctor_QSslError_0);
}

//  Constructor QSslError::QSslError(QSslError::SslError error)


static void _init_ctor_QSslError_2289 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("error");
  decl->add_arg<const qt_gsi::Converter<QSslError::SslError>::target_type & > (argspec_0);
  decl->set_return_new<QSslError *> ();
}

static void _call_ctor_QSslError_2289 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QSslError::SslError>::target_type & arg1 = args.read<const qt_gsi::Converter<QSslError::SslError>::target_type & > ();
  ret.write<QSslError *> (new QSslError (qt_gsi::QtToCppAdaptor<QSslError::SslError>(arg1).cref()));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSslError_2289 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSslError::QSslError(QSslError::SslError error)\nThis method creates an object of class QSslError.", &_init_ctor_QSslError_2289, &_call_ctor_QSslError_2289);
}

//  Constructor QSslError::QSslError(QSslError::SslError error, const QSslCertificate &certificate)


static void _init_ctor_QSslError_5004 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("error");
  decl->add_arg<const qt_gsi::Converter<QSslError::SslError>::target_type & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("certificate");
  decl->add_arg<const QSslCertificate & > (argspec_1);
  decl->set_return_new<QSslError *> ();
}

static void _call_ctor_QSslError_5004 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QSslError::SslError>::target_type & arg1 = args.read<const qt_gsi::Converter<QSslError::SslError>::target_type & > ();
  const QSslCertificate &arg2 = args.read<const QSslCertificate & > ();
  ret.write<QSslError *> (new QSslError (qt_gsi::QtToCppAdaptor<QSslError::SslError>(arg1).cref(), arg2));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSslError_5004 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSslError::QSslError(QSslError::SslError error, const QSslCertificate &certificate)\nThis method creates an object of class QSslError.", &_init_ctor_QSslError_5004, &_call_ctor_QSslError_5004);
}

//  Constructor QSslError::QSslError(const QSslError &other)


static void _init_ctor_QSslError_2222 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslError & > (argspec_0);
  decl->set_return_new<QSslError *> ();
}

static void _call_ctor_QSslError_2222 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslError &arg1 = args.read<const QSslError & > ();
  ret.write<QSslError *> (new QSslError (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSslError_2222 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSslError::QSslError(const QSslError &other)\nThis method creates an object of class QSslError.", &_init_ctor_QSslError_2222, &_call_ctor_QSslError_2222);
}

// QSslCertificate QSslError::certificate()


static void _init_f_certificate_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QSslCertificate > ();
}

static void _call_f_certificate_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSslCertificate > ((QSslCertificate)((QSslError *)cls)->certificate ());
}

static qt_gsi::GenericMethod *_create_f_certificate_c0 ()
{
  return new qt_gsi::GenericMethod ("certificate", "@brief Method QSslCertificate QSslError::certificate()\n", true, &_init_f_certificate_c0, &_call_f_certificate_c0);
}

// QSslError::SslError QSslError::error()


static void _init_f_error_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QSslError::SslError>::target_type > ();
}

static void _call_f_error_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QSslError::SslError>::target_type > ((qt_gsi::Converter<QSslError::SslError>::target_type)qt_gsi::CppToQtAdaptor<QSslError::SslError>(((QSslError *)cls)->error ()));
}

static qt_gsi::GenericMethod *_create_f_error_c0 ()
{
  return new qt_gsi::GenericMethod ("error", "@brief Method QSslError::SslError QSslError::error()\n", true, &_init_f_error_c0, &_call_f_error_c0);
}

// QString QSslError::errorString()


static void _init_f_errorString_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_errorString_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QSslError *)cls)->errorString ());
}

static qt_gsi::GenericMethod *_create_f_errorString_c0 ()
{
  return new qt_gsi::GenericMethod ("errorString", "@brief Method QString QSslError::errorString()\n", true, &_init_f_errorString_c0, &_call_f_errorString_c0);
}

// bool QSslError::operator!=(const QSslError &other)


static void _init_f_operator_excl__eq__c2222 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslError & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_excl__eq__c2222 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslError &arg1 = args.read<const QSslError & > ();
  ret.write<bool > ((bool)((QSslError *)cls)->operator!= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_excl__eq__c2222 ()
{
  return new qt_gsi::GenericMethod ("!=", "@brief Method bool QSslError::operator!=(const QSslError &other)\n", true, &_init_f_operator_excl__eq__c2222, &_call_f_operator_excl__eq__c2222);
}

// QSslError &QSslError::operator=(const QSslError &other)


static void _init_f_operator_eq__2222 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslError & > (argspec_0);
  decl->set_return<QSslError & > ();
}

static void _call_f_operator_eq__2222 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslError &arg1 = args.read<const QSslError & > ();
  ret.write<QSslError & > ((QSslError &)((QSslError *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__2222 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QSslError &QSslError::operator=(const QSslError &other)\n", false, &_init_f_operator_eq__2222, &_call_f_operator_eq__2222);
}

// bool QSslError::operator==(const QSslError &other)


static void _init_f_operator_eq__eq__c2222 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("other");
  decl->add_arg<const QSslError & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_operator_eq__eq__c2222 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSslError &arg1 = args.read<const QSslError & > ();
  ret.write<bool > ((bool)((QSslError *)cls)->operator== (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__eq__c2222 ()
{
  return new qt_gsi::GenericMethod ("==", "@brief Method bool QSslError::operator==(const QSslError &other)\n", true, &_init_f_operator_eq__eq__c2222, &_call_f_operator_eq__eq__c2222);
}


namespace gsi
{
gsi::Class<QSslError> decl_QSslError ("QSslError",
  gsi::Methods(_create_ctor_QSslError_0 ()) +
  gsi::Methods(_create_ctor_QSslError_2289 ()) +
  gsi::Methods(_create_ctor_QSslError_5004 ()) +
  gsi::Methods(_create_ctor_QSslError_2222 ()) +
  gsi::Methods(_create_f_certificate_c0 ()) +
  gsi::Methods(_create_f_error_c0 ()) +
  gsi::Methods(_create_f_errorString_c0 ()) +
  gsi::Methods(_create_f_operator_excl__eq__c2222 ()) +
  gsi::Methods(_create_f_operator_eq__2222 ()) +
  gsi::Methods(_create_f_operator_eq__eq__c2222 ()),
  "@qt\n@brief Binding of QSslError");

}


//  Implementation of the enum wrapper class for QSslError::SslError
namespace qt_gsi
{

static QSslError_SslError_Enum *c_1_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::NoError); }
static QSslError_SslError_Enum *c_2_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::UnableToGetIssuerCertificate); }
static QSslError_SslError_Enum *c_3_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::UnableToDecryptCertificateSignature); }
static QSslError_SslError_Enum *c_4_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::UnableToDecodeIssuerPublicKey); }
static QSslError_SslError_Enum *c_5_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::CertificateSignatureFailed); }
static QSslError_SslError_Enum *c_6_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::CertificateNotYetValid); }
static QSslError_SslError_Enum *c_7_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::CertificateExpired); }
static QSslError_SslError_Enum *c_8_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::InvalidNotBeforeField); }
static QSslError_SslError_Enum *c_9_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::InvalidNotAfterField); }
static QSslError_SslError_Enum *c_10_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::SelfSignedCertificate); }
static QSslError_SslError_Enum *c_11_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::SelfSignedCertificateInChain); }
static QSslError_SslError_Enum *c_12_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::UnableToGetLocalIssuerCertificate); }
static QSslError_SslError_Enum *c_13_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::UnableToVerifyFirstCertificate); }
static QSslError_SslError_Enum *c_14_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::CertificateRevoked); }
static QSslError_SslError_Enum *c_15_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::InvalidCaCertificate); }
static QSslError_SslError_Enum *c_16_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::PathLengthExceeded); }
static QSslError_SslError_Enum *c_17_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::InvalidPurpose); }
static QSslError_SslError_Enum *c_18_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::CertificateUntrusted); }
static QSslError_SslError_Enum *c_19_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::CertificateRejected); }
static QSslError_SslError_Enum *c_20_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::SubjectIssuerMismatch); }
static QSslError_SslError_Enum *c_21_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::AuthorityIssuerSerialNumberMismatch); }
static QSslError_SslError_Enum *c_22_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::NoPeerCertificate); }
static QSslError_SslError_Enum *c_23_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::HostNameMismatch); }
static QSslError_SslError_Enum *c_24_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::NoSslSupport); }
static QSslError_SslError_Enum *c_25_QSslError_SslError_Enum () { return new QSslError_SslError_Enum (QSslError::UnspecifiedError); }

static gsi::Methods mkdefs_QSslError_SslError () {
  return
    gsi::constant ("NoError", &qt_gsi::c_1_QSslError_SslError_Enum, "@brief Enum constant QSslError::NoError") +
    gsi::constant ("UnableToGetIssuerCertificate", &qt_gsi::c_2_QSslError_SslError_Enum, "@brief Enum constant QSslError::UnableToGetIssuerCertificate") +
    gsi::constant ("UnableToDecryptCertificateSignature", &qt_gsi::c_3_QSslError_SslError_Enum, "@brief Enum constant QSslError::UnableToDecryptCertificateSignature") +
    gsi::constant ("UnableToDecodeIssuerPublicKey", &qt_gsi::c_4_QSslError_SslError_Enum, "@brief Enum constant QSslError::UnableToDecodeIssuerPublicKey") +
    gsi::constant ("CertificateSignatureFailed", &qt_gsi::c_5_QSslError_SslError_Enum, "@brief Enum constant QSslError::CertificateSignatureFailed") +
    gsi::constant ("CertificateNotYetValid", &qt_gsi::c_6_QSslError_SslError_Enum, "@brief Enum constant QSslError::CertificateNotYetValid") +
    gsi::constant ("CertificateExpired", &qt_gsi::c_7_QSslError_SslError_Enum, "@brief Enum constant QSslError::CertificateExpired") +
    gsi::constant ("InvalidNotBeforeField", &qt_gsi::c_8_QSslError_SslError_Enum, "@brief Enum constant QSslError::InvalidNotBeforeField") +
    gsi::constant ("InvalidNotAfterField", &qt_gsi::c_9_QSslError_SslError_Enum, "@brief Enum constant QSslError::InvalidNotAfterField") +
    gsi::constant ("SelfSignedCertificate", &qt_gsi::c_10_QSslError_SslError_Enum, "@brief Enum constant QSslError::SelfSignedCertificate") +
    gsi::constant ("SelfSignedCertificateInChain", &qt_gsi::c_11_QSslError_SslError_Enum, "@brief Enum constant QSslError::SelfSignedCertificateInChain") +
    gsi::constant ("UnableToGetLocalIssuerCertificate", &qt_gsi::c_12_QSslError_SslError_Enum, "@brief Enum constant QSslError::UnableToGetLocalIssuerCertificate") +
    gsi::constant ("UnableToVerifyFirstCertificate", &qt_gsi::c_13_QSslError_SslError_Enum, "@brief Enum constant QSslError::UnableToVerifyFirstCertificate") +
    gsi::constant ("CertificateRevoked", &qt_gsi::c_14_QSslError_SslError_Enum, "@brief Enum constant QSslError::CertificateRevoked") +
    gsi::constant ("InvalidCaCertificate", &qt_gsi::c_15_QSslError_SslError_Enum, "@brief Enum constant QSslError::InvalidCaCertificate") +
    gsi::constant ("PathLengthExceeded", &qt_gsi::c_16_QSslError_SslError_Enum, "@brief Enum constant QSslError::PathLengthExceeded") +
    gsi::constant ("InvalidPurpose", &qt_gsi::c_17_QSslError_SslError_Enum, "@brief Enum constant QSslError::InvalidPurpose") +
    gsi::constant ("CertificateUntrusted", &qt_gsi::c_18_QSslError_SslError_Enum, "@brief Enum constant QSslError::CertificateUntrusted") +
    gsi::constant ("CertificateRejected", &qt_gsi::c_19_QSslError_SslError_Enum, "@brief Enum constant QSslError::CertificateRejected") +
    gsi::constant ("SubjectIssuerMismatch", &qt_gsi::c_20_QSslError_SslError_Enum, "@brief Enum constant QSslError::SubjectIssuerMismatch") +
    gsi::constant ("AuthorityIssuerSerialNumberMismatch", &qt_gsi::c_21_QSslError_SslError_Enum, "@brief Enum constant QSslError::AuthorityIssuerSerialNumberMismatch") +
    gsi::constant ("NoPeerCertificate", &qt_gsi::c_22_QSslError_SslError_Enum, "@brief Enum constant QSslError::NoPeerCertificate") +
    gsi::constant ("HostNameMismatch", &qt_gsi::c_23_QSslError_SslError_Enum, "@brief Enum constant QSslError::HostNameMismatch") +
    gsi::constant ("NoSslSupport", &qt_gsi::c_24_QSslError_SslError_Enum, "@brief Enum constant QSslError::NoSslSupport") +
    gsi::constant ("UnspecifiedError", &qt_gsi::c_25_QSslError_SslError_Enum, "@brief Enum constant QSslError::UnspecifiedError");
}

static std::string to_s_QSslError_SslError_Enum (const QSslError_SslError_Enum *e)
{
  if (e->value () == QSslError::NoError) { return tl::sprintf ("NoError (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::UnableToGetIssuerCertificate) { return tl::sprintf ("UnableToGetIssuerCertificate (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::UnableToDecryptCertificateSignature) { return tl::sprintf ("UnableToDecryptCertificateSignature (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::UnableToDecodeIssuerPublicKey) { return tl::sprintf ("UnableToDecodeIssuerPublicKey (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::CertificateSignatureFailed) { return tl::sprintf ("CertificateSignatureFailed (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::CertificateNotYetValid) { return tl::sprintf ("CertificateNotYetValid (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::CertificateExpired) { return tl::sprintf ("CertificateExpired (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::InvalidNotBeforeField) { return tl::sprintf ("InvalidNotBeforeField (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::InvalidNotAfterField) { return tl::sprintf ("InvalidNotAfterField (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::SelfSignedCertificate) { return tl::sprintf ("SelfSignedCertificate (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::SelfSignedCertificateInChain) { return tl::sprintf ("SelfSignedCertificateInChain (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::UnableToGetLocalIssuerCertificate) { return tl::sprintf ("UnableToGetLocalIssuerCertificate (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::UnableToVerifyFirstCertificate) { return tl::sprintf ("UnableToVerifyFirstCertificate (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::CertificateRevoked) { return tl::sprintf ("CertificateRevoked (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::InvalidCaCertificate) { return tl::sprintf ("InvalidCaCertificate (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::PathLengthExceeded) { return tl::sprintf ("PathLengthExceeded (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::InvalidPurpose) { return tl::sprintf ("InvalidPurpose (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::CertificateUntrusted) { return tl::sprintf ("CertificateUntrusted (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::CertificateRejected) { return tl::sprintf ("CertificateRejected (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::SubjectIssuerMismatch) { return tl::sprintf ("SubjectIssuerMismatch (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::AuthorityIssuerSerialNumberMismatch) { return tl::sprintf ("AuthorityIssuerSerialNumberMismatch (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::NoPeerCertificate) { return tl::sprintf ("NoPeerCertificate (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::HostNameMismatch) { return tl::sprintf ("HostNameMismatch (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::NoSslSupport) { return tl::sprintf ("NoSslSupport (%u)", (unsigned int) e->value ()); }
  if (e->value () == QSslError::UnspecifiedError) { return tl::sprintf ("UnspecifiedError (%u)", (unsigned int) e->value ()); }
  return std::string ("(not a valid enum evalue)");
}

static unsigned int to_i_QSslError_SslError_Enum (const QSslError_SslError_Enum *e)
{
  return (unsigned int) e->value ();
}

static QSslError_SslError_Enum *from_i_QSslError_SslError_Enum (unsigned int i)
{
  return new QSslError_SslError_Enum ((QSslError::SslError) i);
}

static bool equalQSslError_SslError_Enum (const QSslError_SslError_Enum *e, QSslError_SslError_Enum d)
{
  return e->value () == d.value ();
}

static bool equal2QSslError_SslError_Enum (const QSslError_SslError_Enum *e, unsigned int i)
{
  return (unsigned int) e->value () == i;
}

static QSslError_SslError_Enums oropQSslError_SslError_Enums (const QSslError_SslError_Enums *e, const QSslError_SslError_Enums &d)
{
  return e->flags () | d.flags ();
}

static QSslError_SslError_Enums andopQSslError_SslError_Enums (const QSslError_SslError_Enums *e, const QSslError_SslError_Enums &d)
{
  return e->flags () & d.flags ();
}

static QSslError_SslError_Enums xoropQSslError_SslError_Enums (const QSslError_SslError_Enums *e, const QSslError_SslError_Enums &d)
{
  return e->flags () ^ d.flags ();
}

static std::string to_s_QSslError_SslError_Enums (const QSslError_SslError_Enums *e)
{
  std::string l;
  if (e->testFlag (QSslError::NoError)) { if (!l.empty ()) l += "|"; l += "NoError"; }
  if (e->testFlag (QSslError::UnableToGetIssuerCertificate)) { if (!l.empty ()) l += "|"; l += "UnableToGetIssuerCertificate"; }
  if (e->testFlag (QSslError::UnableToDecryptCertificateSignature)) { if (!l.empty ()) l += "|"; l += "UnableToDecryptCertificateSignature"; }
  if (e->testFlag (QSslError::UnableToDecodeIssuerPublicKey)) { if (!l.empty ()) l += "|"; l += "UnableToDecodeIssuerPublicKey"; }
  if (e->testFlag (QSslError::CertificateSignatureFailed)) { if (!l.empty ()) l += "|"; l += "CertificateSignatureFailed"; }
  if (e->testFlag (QSslError::CertificateNotYetValid)) { if (!l.empty ()) l += "|"; l += "CertificateNotYetValid"; }
  if (e->testFlag (QSslError::CertificateExpired)) { if (!l.empty ()) l += "|"; l += "CertificateExpired"; }
  if (e->testFlag (QSslError::InvalidNotBeforeField)) { if (!l.empty ()) l += "|"; l += "InvalidNotBeforeField"; }
  if (e->testFlag (QSslError::InvalidNotAfterField)) { if (!l.empty ()) l += "|"; l += "InvalidNotAfterField"; }
  if (e->testFlag (QSslError::SelfSignedCertificate)) { if (!l.empty ()) l += "|"; l += "SelfSignedCertificate"; }
  if (e->testFlag (QSslError::SelfSignedCertificateInChain)) { if (!l.empty ()) l += "|"; l += "SelfSignedCertificateInChain"; }
  if (e->testFlag (QSslError::UnableToGetLocalIssuerCertificate)) { if (!l.empty ()) l += "|"; l += "UnableToGetLocalIssuerCertificate"; }
  if (e->testFlag (QSslError::UnableToVerifyFirstCertificate)) { if (!l.empty ()) l += "|"; l += "UnableToVerifyFirstCertificate"; }
  if (e->testFlag (QSslError::CertificateRevoked)) { if (!l.empty ()) l += "|"; l += "CertificateRevoked"; }
  if (e->testFlag (QSslError::InvalidCaCertificate)) { if (!l.empty ()) l += "|"; l += "InvalidCaCertificate"; }
  if (e->testFlag (QSslError::PathLengthExceeded)) { if (!l.empty ()) l += "|"; l += "PathLengthExceeded"; }
  if (e->testFlag (QSslError::InvalidPurpose)) { if (!l.empty ()) l += "|"; l += "InvalidPurpose"; }
  if (e->testFlag (QSslError::CertificateUntrusted)) { if (!l.empty ()) l += "|"; l += "CertificateUntrusted"; }
  if (e->testFlag (QSslError::CertificateRejected)) { if (!l.empty ()) l += "|"; l += "CertificateRejected"; }
  if (e->testFlag (QSslError::SubjectIssuerMismatch)) { if (!l.empty ()) l += "|"; l += "SubjectIssuerMismatch"; }
  if (e->testFlag (QSslError::AuthorityIssuerSerialNumberMismatch)) { if (!l.empty ()) l += "|"; l += "AuthorityIssuerSerialNumberMismatch"; }
  if (e->testFlag (QSslError::NoPeerCertificate)) { if (!l.empty ()) l += "|"; l += "NoPeerCertificate"; }
  if (e->testFlag (QSslError::HostNameMismatch)) { if (!l.empty ()) l += "|"; l += "HostNameMismatch"; }
  if (e->testFlag (QSslError::NoSslSupport)) { if (!l.empty ()) l += "|"; l += "NoSslSupport"; }
  if (e->testFlag (QSslError::UnspecifiedError)) { if (!l.empty ()) l += "|"; l += "UnspecifiedError"; }
  return tl::sprintf ("%u (%s)", (unsigned int) (e->flags ()), l);
}

static int to_i_QSslError_SslError_Enums (const QSslError_SslError_Enums *e)
{
  return int (e->flags ());
}

static bool testFlag_QSslError_SslError_Enums (const QSslError_SslError_Enums *e, const QSslError_SslError_Enum &d)
{
  return e->flags ().testFlag (d.value ());
}

}

namespace gsi
{

//  Declarations for QFlags<enum> wrapper class
gsi::Class<qt_gsi::QSslError_SslError_Enums> decl_QSslError_SslError_Enums ("QSslError_QFlags_SslError",
  gsi::method_ext ("|", &qt_gsi::oropQSslError_SslError_Enums, gsi::arg ("other"), "@brief 'or' operator between two flag sets") +
  gsi::method_ext ("&", &qt_gsi::andopQSslError_SslError_Enums, gsi::arg ("other"), "@brief 'and' operator between two flag sets") +
  gsi::method_ext ("^", &qt_gsi::xoropQSslError_SslError_Enums, gsi::arg ("other"), "@brief 'xor' operator between two flag sets") +
  gsi::method_ext ("to_s|inspect", &qt_gsi::to_s_QSslError_SslError_Enums, "@brief Converts the flag set to a string") +
  gsi::method_ext ("to_i", &qt_gsi::to_i_QSslError_SslError_Enums, "@brief Returns the integer value encoding the flag set") +
  gsi::method_ext ("testFlag", &qt_gsi::testFlag_QSslError_SslError_Enums, gsi::arg ("flag"), "@brief Tests whether the flag is contained in the flag set"),
  "@qt\n@brief This class represents the QFlags<QSslError::SslError> flag set");

//  Declarations for enum wrapper class
gsi::Class<qt_gsi::QSslError_SslError_Enum> decl_QSslError_SslError_Enum (decl_QSslError_SslError_Enums, "QSslError_SslError",
  qt_gsi::mkdefs_QSslError_SslError () +
  gsi::method_ext ("to_s|inspect", &qt_gsi::to_s_QSslError_SslError_Enum, "@brief Converts the enum class to a string") +
  gsi::method_ext ("to_i", &qt_gsi::to_i_QSslError_SslError_Enum, "@brief Converts the enum class to an integer") +
  gsi::method_ext ("==", &qt_gsi::equalQSslError_SslError_Enum, gsi::arg ("other"), "@brief Compares the enum class against an enum of it's own type") +
  gsi::method_ext ("==", &qt_gsi::equal2QSslError_SslError_Enum, gsi::arg ("other"), "@brief Compares the enum class against an integer") +
  gsi::constructor ("new", &qt_gsi::from_i_QSslError_SslError_Enum, gsi::arg ("value"), "@brief Creates the enum object from an integer"),
  "@qt\n@brief This class represents the QSslError::SslError enum");

//  Inject the declarations into the parent
static gsi::ClassExt<QSslError> inject_QSslError_SslError_Enum_in_parent (qt_gsi::mkdefs_QSslError_SslError ());
static gsi::ClassExt<QSslError> decl_QSslError_SslError_Enum_as_child (decl_QSslError_SslError_Enum, "SslError");

}

