
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
*  @file gsiDeclQFactoryInterface.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtCore.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQFactoryInterface_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QFactoryInterface

// QStringList QFactoryInterface::keys()


static void _init_f_keys_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QStringList>::target_type > ();
}

static void _call_f_keys_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QStringList>::target_type > ((qt_gsi::Converter<QStringList>::target_type)qt_gsi::CppToQtAdaptor<QStringList>(((QFactoryInterface *)cls)->keys ()));
}

static qt_gsi::GenericMethod *_create_f_keys_c0 ()
{
  return new qt_gsi::GenericMethod ("keys", "@brief Method QStringList QFactoryInterface::keys()\n", true, &_init_f_keys_c0, &_call_f_keys_c0);
}

namespace gsi
{
gsi::Class<QFactoryInterface> decl_QFactoryInterface ("QFactoryInterface_Native",
  gsi::Methods(_create_f_keys_c0 ()),
  "@hide\n@alias QFactoryInterface");
}


class QFactoryInterface_Adaptor : public QFactoryInterface, public qt_gsi::QtObjectBase
{
public:

  virtual ~QFactoryInterface_Adaptor();

  //  [adaptor ctor] QFactoryInterface::QFactoryInterface()
  QFactoryInterface_Adaptor() : QFactoryInterface()
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor impl] QStringList QFactoryInterface::keys()
  qt_gsi::Converter<QStringList>::target_type cbs_keys_c0_0() const
  {
    throw qt_gsi::AbstractMethodCalledException("keys");
  }

  virtual QStringList keys() const
  {
    if (cb_keys_c0_0.can_issue()) {
      return qt_gsi::QtToCppAdaptor<QStringList>(cb_keys_c0_0.issue<QFactoryInterface_Adaptor, qt_gsi::Converter<QStringList>::target_type>(&QFactoryInterface_Adaptor::cbs_keys_c0_0)).cref();
    } else {
      throw qt_gsi::AbstractMethodCalledException("keys");
    }
  }

  gsi::Callback cb_keys_c0_0;
};

QFactoryInterface_Adaptor::~QFactoryInterface_Adaptor() { }

//  Constructor QFactoryInterface::QFactoryInterface() (adaptor class)

static void _init_ctor_QFactoryInterface_Adaptor_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QFactoryInterface_Adaptor *> ();
}

static void _call_ctor_QFactoryInterface_Adaptor_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QFactoryInterface_Adaptor *> (new QFactoryInterface_Adaptor ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QFactoryInterface_Adaptor_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QFactoryInterface::QFactoryInterface()\nThis method creates an object of class QFactoryInterface.", &_init_ctor_QFactoryInterface_Adaptor_0, &_call_ctor_QFactoryInterface_Adaptor_0);
}

// QStringList QFactoryInterface::keys()

static void _init_cbs_keys_c0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QStringList>::target_type > ();
}

static void _call_cbs_keys_c0_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QStringList>::target_type > ((qt_gsi::Converter<QStringList>::target_type)((QFactoryInterface_Adaptor *)cls)->cbs_keys_c0_0 ());
}

static void _set_callback_cbs_keys_c0_0 (void *cls, const gsi::Callback &cb)
{
  ((QFactoryInterface_Adaptor *)cls)->cb_keys_c0_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_keys_c0_0 ()
{
  return new qt_gsi::GenericMethod ("keys", "@hide", true, &_init_cbs_keys_c0_0, &_call_cbs_keys_c0_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_keys_c0_0 ()
{
  return new qt_gsi::GenericMethod ("keys", "@brief Virtual method QStringList QFactoryInterface::keys()\nThis method can be reimplemented in a derived class.", true, &_init_cbs_keys_c0_0, &_call_cbs_keys_c0_0, &_set_callback_cbs_keys_c0_0);
}


namespace gsi
{

extern gsi::Class<QFactoryInterface> decl_QFactoryInterface;

gsi::Class<QFactoryInterface_Adaptor> decl_QFactoryInterface_Adaptor (decl_QFactoryInterface, "QFactoryInterface",
  gsi::Methods(_create_cbs_keys_c0_0 ()) +
  gsi::Methods(_create_callback_cbs_keys_c0_0 ()) +
  gsi::Methods(_create_ctor_QFactoryInterface_Adaptor_0 ()),
  "@qt\n@brief Binding of QFactoryInterface");

}

