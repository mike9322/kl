
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
*  @file gsiDeclQHostInfo.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtNetwork.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQHostInfo_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QHostInfo

//  Constructor QHostInfo::QHostInfo(int lookupId)


static void _init_ctor_QHostInfo_767 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("lookupId", true, "-1");
  decl->add_arg<int > (argspec_0);
  decl->set_return_new<QHostInfo *> ();
}

static void _call_ctor_QHostInfo_767 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args ? args.read<int > () : (int)(-1);
  ret.write<QHostInfo *> (new QHostInfo (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QHostInfo_767 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QHostInfo::QHostInfo(int lookupId)\nThis method creates an object of class QHostInfo.", &_init_ctor_QHostInfo_767, &_call_ctor_QHostInfo_767);
}

//  Constructor QHostInfo::QHostInfo(const QHostInfo &d)


static void _init_ctor_QHostInfo_2204 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("d");
  decl->add_arg<const QHostInfo & > (argspec_0);
  decl->set_return_new<QHostInfo *> ();
}

static void _call_ctor_QHostInfo_2204 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QHostInfo &arg1 = args.read<const QHostInfo & > ();
  ret.write<QHostInfo *> (new QHostInfo (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QHostInfo_2204 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QHostInfo::QHostInfo(const QHostInfo &d)\nThis method creates an object of class QHostInfo.", &_init_ctor_QHostInfo_2204, &_call_ctor_QHostInfo_2204);
}

// QList<QHostAddress> QHostInfo::addresses()


static void _init_f_addresses_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QHostAddress> >::target_type > ();
}

static void _call_f_addresses_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QHostAddress> >::target_type > ((qt_gsi::Converter<QList<QHostAddress> >::target_type)qt_gsi::CppToQtAdaptor<QList<QHostAddress> >(((QHostInfo *)cls)->addresses ()));
}

static qt_gsi::GenericMethod *_create_f_addresses_c0 ()
{
  return new qt_gsi::GenericMethod (":addresses", "@brief Method QList<QHostAddress> QHostInfo::addresses()\n", true, &_init_f_addresses_c0, &_call_f_addresses_c0);
}

// QHostInfo::HostInfoError QHostInfo::error()


static void _init_f_error_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QHostInfo::HostInfoError>::target_type > ();
}

static void _call_f_error_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QHostInfo::HostInfoError>::target_type > ((qt_gsi::Converter<QHostInfo::HostInfoError>::target_type)qt_gsi::CppToQtAdaptor<QHostInfo::HostInfoError>(((QHostInfo *)cls)->error ()));
}

static qt_gsi::GenericMethod *_create_f_error_c0 ()
{
  return new qt_gsi::GenericMethod (":error", "@brief Method QHostInfo::HostInfoError QHostInfo::error()\n", true, &_init_f_error_c0, &_call_f_error_c0);
}

// QString QHostInfo::errorString()


static void _init_f_errorString_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_errorString_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QHostInfo *)cls)->errorString ());
}

static qt_gsi::GenericMethod *_create_f_errorString_c0 ()
{
  return new qt_gsi::GenericMethod (":errorString", "@brief Method QString QHostInfo::errorString()\n", true, &_init_f_errorString_c0, &_call_f_errorString_c0);
}

// QString QHostInfo::hostName()


static void _init_f_hostName_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_hostName_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QHostInfo *)cls)->hostName ());
}

static qt_gsi::GenericMethod *_create_f_hostName_c0 ()
{
  return new qt_gsi::GenericMethod (":hostName", "@brief Method QString QHostInfo::hostName()\n", true, &_init_f_hostName_c0, &_call_f_hostName_c0);
}

// int QHostInfo::lookupId()


static void _init_f_lookupId_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_lookupId_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QHostInfo *)cls)->lookupId ());
}

static qt_gsi::GenericMethod *_create_f_lookupId_c0 ()
{
  return new qt_gsi::GenericMethod (":lookupId", "@brief Method int QHostInfo::lookupId()\n", true, &_init_f_lookupId_c0, &_call_f_lookupId_c0);
}

// QHostInfo &QHostInfo::operator=(const QHostInfo &d)


static void _init_f_operator_eq__2204 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("d");
  decl->add_arg<const QHostInfo & > (argspec_0);
  decl->set_return<QHostInfo & > ();
}

static void _call_f_operator_eq__2204 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QHostInfo &arg1 = args.read<const QHostInfo & > ();
  ret.write<QHostInfo & > ((QHostInfo &)((QHostInfo *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__2204 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QHostInfo &QHostInfo::operator=(const QHostInfo &d)\n", false, &_init_f_operator_eq__2204, &_call_f_operator_eq__2204);
}

// void QHostInfo::setAddresses(const QList<QHostAddress> &addresses)


static void _init_f_setAddresses_3133 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("addresses");
  decl->add_arg<const qt_gsi::Converter<QList<QHostAddress> >::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setAddresses_3133 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QList<QHostAddress> >::target_type & arg1 = args.read<const qt_gsi::Converter<QList<QHostAddress> >::target_type & > ();
  ((QHostInfo *)cls)->setAddresses (qt_gsi::QtToCppAdaptor<QList<QHostAddress> >(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setAddresses_3133 ()
{
  return new qt_gsi::GenericMethod ("setAddresses|addresses=", "@brief Method void QHostInfo::setAddresses(const QList<QHostAddress> &addresses)\n", false, &_init_f_setAddresses_3133, &_call_f_setAddresses_3133);
}

// void QHostInfo::setError(QHostInfo::HostInfoError error)


static void _init_f_setError_2775 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("error");
  decl->add_arg<const qt_gsi::Converter<QHostInfo::HostInfoError>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setError_2775 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QHostInfo::HostInfoError>::target_type & arg1 = args.read<const qt_gsi::Converter<QHostInfo::HostInfoError>::target_type & > ();
  ((QHostInfo *)cls)->setError (qt_gsi::QtToCppAdaptor<QHostInfo::HostInfoError>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setError_2775 ()
{
  return new qt_gsi::GenericMethod ("setError|error=", "@brief Method void QHostInfo::setError(QHostInfo::HostInfoError error)\n", false, &_init_f_setError_2775, &_call_f_setError_2775);
}

// void QHostInfo::setErrorString(const QString &errorString)


static void _init_f_setErrorString_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("errorString");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setErrorString_2025 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ((QHostInfo *)cls)->setErrorString (arg1);
}

static qt_gsi::GenericMethod *_create_f_setErrorString_2025 ()
{
  return new qt_gsi::GenericMethod ("setErrorString|errorString=", "@brief Method void QHostInfo::setErrorString(const QString &errorString)\n", false, &_init_f_setErrorString_2025, &_call_f_setErrorString_2025);
}

// void QHostInfo::setHostName(const QString &name)


static void _init_f_setHostName_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setHostName_2025 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ((QHostInfo *)cls)->setHostName (arg1);
}

static qt_gsi::GenericMethod *_create_f_setHostName_2025 ()
{
  return new qt_gsi::GenericMethod ("setHostName|hostName=", "@brief Method void QHostInfo::setHostName(const QString &name)\n", false, &_init_f_setHostName_2025, &_call_f_setHostName_2025);
}

// void QHostInfo::setLookupId(int id)


static void _init_f_setLookupId_767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("id");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setLookupId_767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ((QHostInfo *)cls)->setLookupId (arg1);
}

static qt_gsi::GenericMethod *_create_f_setLookupId_767 ()
{
  return new qt_gsi::GenericMethod ("setLookupId|lookupId=", "@brief Method void QHostInfo::setLookupId(int id)\n", false, &_init_f_setLookupId_767, &_call_f_setLookupId_767);
}

// static void QHostInfo::abortHostLookup(int lookupId)


static void _init_f_abortHostLookup_767 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("lookupId");
  decl->add_arg<int > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_abortHostLookup_767 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  QHostInfo::abortHostLookup (arg1);
}

static qt_gsi::GenericStaticMethod *_create_f_abortHostLookup_767 ()
{
  return new qt_gsi::GenericStaticMethod ("abortHostLookup", "@brief Static method void QHostInfo::abortHostLookup(int lookupId)\nThis method is static and can be called without an instance.", &_init_f_abortHostLookup_767, &_call_f_abortHostLookup_767);
}

// static QHostInfo QHostInfo::fromName(const QString &name)


static void _init_f_fromName_2025 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<QHostInfo > ();
}

static void _call_f_fromName_2025 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ret.write<QHostInfo > ((QHostInfo)QHostInfo::fromName (arg1));
}

static qt_gsi::GenericStaticMethod *_create_f_fromName_2025 ()
{
  return new qt_gsi::GenericStaticMethod ("fromName", "@brief Static method QHostInfo QHostInfo::fromName(const QString &name)\nThis method is static and can be called without an instance.", &_init_f_fromName_2025, &_call_f_fromName_2025);
}

// static QString QHostInfo::localDomainName()


static void _init_f_localDomainName_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_localDomainName_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)QHostInfo::localDomainName ());
}

static qt_gsi::GenericStaticMethod *_create_f_localDomainName_0 ()
{
  return new qt_gsi::GenericStaticMethod ("localDomainName", "@brief Static method QString QHostInfo::localDomainName()\nThis method is static and can be called without an instance.", &_init_f_localDomainName_0, &_call_f_localDomainName_0);
}

// static QString QHostInfo::localHostName()


static void _init_f_localHostName_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_localHostName_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)QHostInfo::localHostName ());
}

static qt_gsi::GenericStaticMethod *_create_f_localHostName_0 ()
{
  return new qt_gsi::GenericStaticMethod ("localHostName", "@brief Static method QString QHostInfo::localHostName()\nThis method is static and can be called without an instance.", &_init_f_localHostName_0, &_call_f_localHostName_0);
}

// static int QHostInfo::lookupHost(const QString &name, QObject *receiver, const char *member)


static void _init_f_lookupHost_4842 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("name");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("receiver");
  decl->add_arg<QObject * > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("member");
  decl->add_arg<const char * > (argspec_2);
  decl->set_return<int > ();
}

static void _call_f_lookupHost_4842 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  QObject *arg2 = args.read<QObject * > ();
  const char *arg3 = args.read<const char * > ();
  ret.write<int > ((int)QHostInfo::lookupHost (arg1, arg2, arg3));
}

static qt_gsi::GenericStaticMethod *_create_f_lookupHost_4842 ()
{
  return new qt_gsi::GenericStaticMethod ("lookupHost", "@brief Static method int QHostInfo::lookupHost(const QString &name, QObject *receiver, const char *member)\nThis method is static and can be called without an instance.", &_init_f_lookupHost_4842, &_call_f_lookupHost_4842);
}


namespace gsi
{
gsi::Class<QHostInfo> decl_QHostInfo ("QHostInfo",
  gsi::Methods(_create_ctor_QHostInfo_767 ()) +
  gsi::Methods(_create_ctor_QHostInfo_2204 ()) +
  gsi::Methods(_create_f_addresses_c0 ()) +
  gsi::Methods(_create_f_error_c0 ()) +
  gsi::Methods(_create_f_errorString_c0 ()) +
  gsi::Methods(_create_f_hostName_c0 ()) +
  gsi::Methods(_create_f_lookupId_c0 ()) +
  gsi::Methods(_create_f_operator_eq__2204 ()) +
  gsi::Methods(_create_f_setAddresses_3133 ()) +
  gsi::Methods(_create_f_setError_2775 ()) +
  gsi::Methods(_create_f_setErrorString_2025 ()) +
  gsi::Methods(_create_f_setHostName_2025 ()) +
  gsi::Methods(_create_f_setLookupId_767 ()) +
  gsi::Methods(_create_f_abortHostLookup_767 ()) +
  gsi::Methods(_create_f_fromName_2025 ()) +
  gsi::Methods(_create_f_localDomainName_0 ()) +
  gsi::Methods(_create_f_localHostName_0 ()) +
  gsi::Methods(_create_f_lookupHost_4842 ()),
  "@qt\n@brief Binding of QHostInfo");

}


//  Implementation of the enum wrapper class for QHostInfo::HostInfoError
namespace qt_gsi
{

static QHostInfo_HostInfoError_Enum *c_1_QHostInfo_HostInfoError_Enum () { return new QHostInfo_HostInfoError_Enum (QHostInfo::NoError); }
static QHostInfo_HostInfoError_Enum *c_2_QHostInfo_HostInfoError_Enum () { return new QHostInfo_HostInfoError_Enum (QHostInfo::HostNotFound); }
static QHostInfo_HostInfoError_Enum *c_3_QHostInfo_HostInfoError_Enum () { return new QHostInfo_HostInfoError_Enum (QHostInfo::UnknownError); }

static gsi::Methods mkdefs_QHostInfo_HostInfoError () {
  return
    gsi::constant ("NoError", &qt_gsi::c_1_QHostInfo_HostInfoError_Enum, "@brief Enum constant QHostInfo::NoError") +
    gsi::constant ("HostNotFound", &qt_gsi::c_2_QHostInfo_HostInfoError_Enum, "@brief Enum constant QHostInfo::HostNotFound") +
    gsi::constant ("UnknownError", &qt_gsi::c_3_QHostInfo_HostInfoError_Enum, "@brief Enum constant QHostInfo::UnknownError");
}

static std::string to_s_QHostInfo_HostInfoError_Enum (const QHostInfo_HostInfoError_Enum *e)
{
  if (e->value () == QHostInfo::NoError) { return tl::sprintf ("NoError (%u)", (unsigned int) e->value ()); }
  if (e->value () == QHostInfo::HostNotFound) { return tl::sprintf ("HostNotFound (%u)", (unsigned int) e->value ()); }
  if (e->value () == QHostInfo::UnknownError) { return tl::sprintf ("UnknownError (%u)", (unsigned int) e->value ()); }
  return std::string ("(not a valid enum evalue)");
}

static unsigned int to_i_QHostInfo_HostInfoError_Enum (const QHostInfo_HostInfoError_Enum *e)
{
  return (unsigned int) e->value ();
}

static QHostInfo_HostInfoError_Enum *from_i_QHostInfo_HostInfoError_Enum (unsigned int i)
{
  return new QHostInfo_HostInfoError_Enum ((QHostInfo::HostInfoError) i);
}

static bool equalQHostInfo_HostInfoError_Enum (const QHostInfo_HostInfoError_Enum *e, QHostInfo_HostInfoError_Enum d)
{
  return e->value () == d.value ();
}

static bool equal2QHostInfo_HostInfoError_Enum (const QHostInfo_HostInfoError_Enum *e, unsigned int i)
{
  return (unsigned int) e->value () == i;
}

static QHostInfo_HostInfoError_Enums oropQHostInfo_HostInfoError_Enums (const QHostInfo_HostInfoError_Enums *e, const QHostInfo_HostInfoError_Enums &d)
{
  return e->flags () | d.flags ();
}

static QHostInfo_HostInfoError_Enums andopQHostInfo_HostInfoError_Enums (const QHostInfo_HostInfoError_Enums *e, const QHostInfo_HostInfoError_Enums &d)
{
  return e->flags () & d.flags ();
}

static QHostInfo_HostInfoError_Enums xoropQHostInfo_HostInfoError_Enums (const QHostInfo_HostInfoError_Enums *e, const QHostInfo_HostInfoError_Enums &d)
{
  return e->flags () ^ d.flags ();
}

static std::string to_s_QHostInfo_HostInfoError_Enums (const QHostInfo_HostInfoError_Enums *e)
{
  std::string l;
  if (e->testFlag (QHostInfo::NoError)) { if (!l.empty ()) l += "|"; l += "NoError"; }
  if (e->testFlag (QHostInfo::HostNotFound)) { if (!l.empty ()) l += "|"; l += "HostNotFound"; }
  if (e->testFlag (QHostInfo::UnknownError)) { if (!l.empty ()) l += "|"; l += "UnknownError"; }
  return tl::sprintf ("%u (%s)", (unsigned int) (e->flags ()), l);
}

static int to_i_QHostInfo_HostInfoError_Enums (const QHostInfo_HostInfoError_Enums *e)
{
  return int (e->flags ());
}

static bool testFlag_QHostInfo_HostInfoError_Enums (const QHostInfo_HostInfoError_Enums *e, const QHostInfo_HostInfoError_Enum &d)
{
  return e->flags ().testFlag (d.value ());
}

}

namespace gsi
{

//  Declarations for QFlags<enum> wrapper class
gsi::Class<qt_gsi::QHostInfo_HostInfoError_Enums> decl_QHostInfo_HostInfoError_Enums ("QHostInfo_QFlags_HostInfoError",
  gsi::method_ext ("|", &qt_gsi::oropQHostInfo_HostInfoError_Enums, gsi::arg ("other"), "@brief 'or' operator between two flag sets") +
  gsi::method_ext ("&", &qt_gsi::andopQHostInfo_HostInfoError_Enums, gsi::arg ("other"), "@brief 'and' operator between two flag sets") +
  gsi::method_ext ("^", &qt_gsi::xoropQHostInfo_HostInfoError_Enums, gsi::arg ("other"), "@brief 'xor' operator between two flag sets") +
  gsi::method_ext ("to_s|inspect", &qt_gsi::to_s_QHostInfo_HostInfoError_Enums, "@brief Converts the flag set to a string") +
  gsi::method_ext ("to_i", &qt_gsi::to_i_QHostInfo_HostInfoError_Enums, "@brief Returns the integer value encoding the flag set") +
  gsi::method_ext ("testFlag", &qt_gsi::testFlag_QHostInfo_HostInfoError_Enums, gsi::arg ("flag"), "@brief Tests whether the flag is contained in the flag set"),
  "@qt\n@brief This class represents the QFlags<QHostInfo::HostInfoError> flag set");

//  Declarations for enum wrapper class
gsi::Class<qt_gsi::QHostInfo_HostInfoError_Enum> decl_QHostInfo_HostInfoError_Enum (decl_QHostInfo_HostInfoError_Enums, "QHostInfo_HostInfoError",
  qt_gsi::mkdefs_QHostInfo_HostInfoError () +
  gsi::method_ext ("to_s|inspect", &qt_gsi::to_s_QHostInfo_HostInfoError_Enum, "@brief Converts the enum class to a string") +
  gsi::method_ext ("to_i", &qt_gsi::to_i_QHostInfo_HostInfoError_Enum, "@brief Converts the enum class to an integer") +
  gsi::method_ext ("==", &qt_gsi::equalQHostInfo_HostInfoError_Enum, gsi::arg ("other"), "@brief Compares the enum class against an enum of it's own type") +
  gsi::method_ext ("==", &qt_gsi::equal2QHostInfo_HostInfoError_Enum, gsi::arg ("other"), "@brief Compares the enum class against an integer") +
  gsi::constructor ("new", &qt_gsi::from_i_QHostInfo_HostInfoError_Enum, gsi::arg ("value"), "@brief Creates the enum object from an integer"),
  "@qt\n@brief This class represents the QHostInfo::HostInfoError enum");

//  Inject the declarations into the parent
static gsi::ClassExt<QHostInfo> inject_QHostInfo_HostInfoError_Enum_in_parent (qt_gsi::mkdefs_QHostInfo_HostInfoError ());
static gsi::ClassExt<QHostInfo> decl_QHostInfo_HostInfoError_Enum_as_child (decl_QHostInfo_HostInfoError_Enum, "HostInfoError");

}

