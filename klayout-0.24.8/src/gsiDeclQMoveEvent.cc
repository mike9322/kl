
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
*  @file gsiDeclQMoveEvent.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQMoveEvent_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QMoveEvent

// const QPoint &QMoveEvent::oldPos()


static void _init_f_oldPos_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<const QPoint & > ();
}

static void _call_f_oldPos_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const QPoint & > ((const QPoint &)((QMoveEvent *)cls)->oldPos ());
}

static qt_gsi::GenericMethod *_create_f_oldPos_c0 ()
{
  return new qt_gsi::GenericMethod ("oldPos", "@brief Method const QPoint &QMoveEvent::oldPos()\n", true, &_init_f_oldPos_c0, &_call_f_oldPos_c0);
}

// const QPoint &QMoveEvent::pos()


static void _init_f_pos_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<const QPoint & > ();
}

static void _call_f_pos_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const QPoint & > ((const QPoint &)((QMoveEvent *)cls)->pos ());
}

static qt_gsi::GenericMethod *_create_f_pos_c0 ()
{
  return new qt_gsi::GenericMethod ("pos", "@brief Method const QPoint &QMoveEvent::pos()\n", true, &_init_f_pos_c0, &_call_f_pos_c0);
}

namespace gsi
{
extern gsi::Class<QEvent> decl_QEvent;

gsi::Class<QMoveEvent> decl_QMoveEvent (decl_QEvent, "QMoveEvent_Native",
  gsi::Methods(_create_f_oldPos_c0 ()) +
  gsi::Methods(_create_f_pos_c0 ()),
  "@hide\n@alias QMoveEvent");
}


class QMoveEvent_Adaptor : public QMoveEvent, public qt_gsi::QtObjectBase
{
public:

  virtual ~QMoveEvent_Adaptor();

  //  [adaptor ctor] QMoveEvent::QMoveEvent(const QPoint &pos, const QPoint &oldPos)
  QMoveEvent_Adaptor(const QPoint &pos, const QPoint &oldPos) : QMoveEvent(pos, oldPos)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  
};

QMoveEvent_Adaptor::~QMoveEvent_Adaptor() { }

//  Constructor QMoveEvent::QMoveEvent(const QPoint &pos, const QPoint &oldPos) (adaptor class)

static void _init_ctor_QMoveEvent_Adaptor_3724 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("pos");
  decl->add_arg<const QPoint & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("oldPos");
  decl->add_arg<const QPoint & > (argspec_1);
  decl->set_return_new<QMoveEvent_Adaptor *> ();
}

static void _call_ctor_QMoveEvent_Adaptor_3724 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QPoint &arg1 = args.read<const QPoint & > ();
  const QPoint &arg2 = args.read<const QPoint & > ();
  ret.write<QMoveEvent_Adaptor *> (new QMoveEvent_Adaptor (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QMoveEvent_Adaptor_3724 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QMoveEvent::QMoveEvent(const QPoint &pos, const QPoint &oldPos)\nThis method creates an object of class QMoveEvent.", &_init_ctor_QMoveEvent_Adaptor_3724, &_call_ctor_QMoveEvent_Adaptor_3724);
}

namespace gsi
{

extern gsi::Class<QMoveEvent> decl_QMoveEvent;

gsi::Class<QMoveEvent_Adaptor> decl_QMoveEvent_Adaptor (decl_QMoveEvent, "QMoveEvent",
  gsi::Methods(_create_ctor_QMoveEvent_Adaptor_3724 ()),
  "@qt\n@brief Binding of QMoveEvent");

}

