
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
*  @file gsiDeclQIconDragEvent.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQIconDragEvent_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QIconDragEvent

namespace gsi
{
extern gsi::Class<QEvent> decl_QEvent;

gsi::Class<QIconDragEvent> decl_QIconDragEvent (decl_QEvent, "QIconDragEvent_Native",
  gsi::Methods(),
  "@hide\n@alias QIconDragEvent");
}


class QIconDragEvent_Adaptor : public QIconDragEvent, public qt_gsi::QtObjectBase
{
public:

  virtual ~QIconDragEvent_Adaptor();

  //  [adaptor ctor] QIconDragEvent::QIconDragEvent()
  QIconDragEvent_Adaptor() : QIconDragEvent()
  {
    qt_gsi::QtObjectBase::init (this);
  }

  
};

QIconDragEvent_Adaptor::~QIconDragEvent_Adaptor() { }

//  Constructor QIconDragEvent::QIconDragEvent() (adaptor class)

static void _init_ctor_QIconDragEvent_Adaptor_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QIconDragEvent_Adaptor *> ();
}

static void _call_ctor_QIconDragEvent_Adaptor_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QIconDragEvent_Adaptor *> (new QIconDragEvent_Adaptor ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QIconDragEvent_Adaptor_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QIconDragEvent::QIconDragEvent()\nThis method creates an object of class QIconDragEvent.", &_init_ctor_QIconDragEvent_Adaptor_0, &_call_ctor_QIconDragEvent_Adaptor_0);
}

namespace gsi
{

extern gsi::Class<QIconDragEvent> decl_QIconDragEvent;

gsi::Class<QIconDragEvent_Adaptor> decl_QIconDragEvent_Adaptor (decl_QIconDragEvent, "QIconDragEvent",
  gsi::Methods(_create_ctor_QIconDragEvent_Adaptor_0 ()),
  "@qt\n@brief Binding of QIconDragEvent");

}

