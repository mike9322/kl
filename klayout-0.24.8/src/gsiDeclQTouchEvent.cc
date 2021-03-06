
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
*  @file gsiDeclQTouchEvent.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQTouchEvent_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QTouchEvent

// QTouchEvent::DeviceType QTouchEvent::deviceType()


static void _init_f_deviceType_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QTouchEvent::DeviceType>::target_type > ();
}

static void _call_f_deviceType_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QTouchEvent::DeviceType>::target_type > ((qt_gsi::Converter<QTouchEvent::DeviceType>::target_type)qt_gsi::CppToQtAdaptor<QTouchEvent::DeviceType>(((QTouchEvent *)cls)->deviceType ()));
}

static qt_gsi::GenericMethod *_create_f_deviceType_c0 ()
{
  return new qt_gsi::GenericMethod (":deviceType", "@brief Method QTouchEvent::DeviceType QTouchEvent::deviceType()\n", true, &_init_f_deviceType_c0, &_call_f_deviceType_c0);
}

// void QTouchEvent::setDeviceType(QTouchEvent::DeviceType adeviceType)


static void _init_f_setDeviceType_2672 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("adeviceType");
  decl->add_arg<const qt_gsi::Converter<QTouchEvent::DeviceType>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setDeviceType_2672 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QTouchEvent::DeviceType>::target_type & arg1 = args.read<const qt_gsi::Converter<QTouchEvent::DeviceType>::target_type & > ();
  ((QTouchEvent *)cls)->setDeviceType (qt_gsi::QtToCppAdaptor<QTouchEvent::DeviceType>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setDeviceType_2672 ()
{
  return new qt_gsi::GenericMethod ("setDeviceType|deviceType=", "@brief Method void QTouchEvent::setDeviceType(QTouchEvent::DeviceType adeviceType)\n", false, &_init_f_setDeviceType_2672, &_call_f_setDeviceType_2672);
}

// void QTouchEvent::setTouchPointStates(QFlags<Qt::TouchPointState> aTouchPointStates)


static void _init_f_setTouchPointStates_2995 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("aTouchPointStates");
  decl->add_arg<const qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setTouchPointStates_2995 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type & arg1 = args.read<const qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type & > ();
  ((QTouchEvent *)cls)->setTouchPointStates (qt_gsi::QtToCppAdaptor<QFlags<Qt::TouchPointState> >(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setTouchPointStates_2995 ()
{
  return new qt_gsi::GenericMethod ("setTouchPointStates|touchPointStates=", "@brief Method void QTouchEvent::setTouchPointStates(QFlags<Qt::TouchPointState> aTouchPointStates)\n", false, &_init_f_setTouchPointStates_2995, &_call_f_setTouchPointStates_2995);
}

// void QTouchEvent::setTouchPoints(const QList<QTouchEvent::TouchPoint> &atouchPoints)


static void _init_f_setTouchPoints_4191 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("atouchPoints");
  decl->add_arg<const qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setTouchPoints_4191 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type & arg1 = args.read<const qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type & > ();
  ((QTouchEvent *)cls)->setTouchPoints (qt_gsi::QtToCppAdaptor<QList<QTouchEvent::TouchPoint> >(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setTouchPoints_4191 ()
{
  return new qt_gsi::GenericMethod ("setTouchPoints|touchPoints=", "@brief Method void QTouchEvent::setTouchPoints(const QList<QTouchEvent::TouchPoint> &atouchPoints)\n", false, &_init_f_setTouchPoints_4191, &_call_f_setTouchPoints_4191);
}

// void QTouchEvent::setWidget(QWidget *awidget)


static void _init_f_setWidget_1315 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("awidget");
  decl->add_arg<QWidget * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setWidget_1315 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QWidget *arg1 = args.read<QWidget * > ();
  ((QTouchEvent *)cls)->setWidget (arg1);
}

static qt_gsi::GenericMethod *_create_f_setWidget_1315 ()
{
  return new qt_gsi::GenericMethod ("setWidget|widget=", "@brief Method void QTouchEvent::setWidget(QWidget *awidget)\n", false, &_init_f_setWidget_1315, &_call_f_setWidget_1315);
}

// QFlags<Qt::TouchPointState> QTouchEvent::touchPointStates()


static void _init_f_touchPointStates_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type > ();
}

static void _call_f_touchPointStates_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type > ((qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type)qt_gsi::CppToQtAdaptor<QFlags<Qt::TouchPointState> >(((QTouchEvent *)cls)->touchPointStates ()));
}

static qt_gsi::GenericMethod *_create_f_touchPointStates_c0 ()
{
  return new qt_gsi::GenericMethod (":touchPointStates", "@brief Method QFlags<Qt::TouchPointState> QTouchEvent::touchPointStates()\n", true, &_init_f_touchPointStates_c0, &_call_f_touchPointStates_c0);
}

// const QList<QTouchEvent::TouchPoint> &QTouchEvent::touchPoints()


static void _init_f_touchPoints_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type > ();
}

static void _call_f_touchPoints_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type > ((qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type)qt_gsi::CppToQtAdaptor<QList<QTouchEvent::TouchPoint> >(((QTouchEvent *)cls)->touchPoints ()));
}

static qt_gsi::GenericMethod *_create_f_touchPoints_c0 ()
{
  return new qt_gsi::GenericMethod (":touchPoints", "@brief Method const QList<QTouchEvent::TouchPoint> &QTouchEvent::touchPoints()\n", true, &_init_f_touchPoints_c0, &_call_f_touchPoints_c0);
}

// QWidget *QTouchEvent::widget()


static void _init_f_widget_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QWidget * > ();
}

static void _call_f_widget_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QWidget * > ((QWidget *)((QTouchEvent *)cls)->widget ());
}

static qt_gsi::GenericMethod *_create_f_widget_c0 ()
{
  return new qt_gsi::GenericMethod (":widget", "@brief Method QWidget *QTouchEvent::widget()\n", true, &_init_f_widget_c0, &_call_f_widget_c0);
}

namespace gsi
{
extern gsi::Class<QInputEvent> decl_QInputEvent;

gsi::Class<QTouchEvent> decl_QTouchEvent (decl_QInputEvent, "QTouchEvent_Native",
  gsi::Methods(_create_f_deviceType_c0 ()) +
  gsi::Methods(_create_f_setDeviceType_2672 ()) +
  gsi::Methods(_create_f_setTouchPointStates_2995 ()) +
  gsi::Methods(_create_f_setTouchPoints_4191 ()) +
  gsi::Methods(_create_f_setWidget_1315 ()) +
  gsi::Methods(_create_f_touchPointStates_c0 ()) +
  gsi::Methods(_create_f_touchPoints_c0 ()) +
  gsi::Methods(_create_f_widget_c0 ()),
  "@hide\n@alias QTouchEvent");
}


class QTouchEvent_Adaptor : public QTouchEvent, public qt_gsi::QtObjectBase
{
public:

  virtual ~QTouchEvent_Adaptor();

  //  [adaptor ctor] QTouchEvent::QTouchEvent(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers, QFlags<Qt::TouchPointState> touchPointStates, const QList<QTouchEvent::TouchPoint> &touchPoints)
  QTouchEvent_Adaptor(QEvent::Type eventType) : QTouchEvent(eventType)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QTouchEvent::QTouchEvent(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers, QFlags<Qt::TouchPointState> touchPointStates, const QList<QTouchEvent::TouchPoint> &touchPoints)
  QTouchEvent_Adaptor(QEvent::Type eventType, QTouchEvent::DeviceType deviceType) : QTouchEvent(eventType, deviceType)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QTouchEvent::QTouchEvent(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers, QFlags<Qt::TouchPointState> touchPointStates, const QList<QTouchEvent::TouchPoint> &touchPoints)
  QTouchEvent_Adaptor(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers) : QTouchEvent(eventType, deviceType, modifiers)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QTouchEvent::QTouchEvent(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers, QFlags<Qt::TouchPointState> touchPointStates, const QList<QTouchEvent::TouchPoint> &touchPoints)
  QTouchEvent_Adaptor(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers, QFlags<Qt::TouchPointState> touchPointStates) : QTouchEvent(eventType, deviceType, modifiers, touchPointStates)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QTouchEvent::QTouchEvent(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers, QFlags<Qt::TouchPointState> touchPointStates, const QList<QTouchEvent::TouchPoint> &touchPoints)
  QTouchEvent_Adaptor(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers, QFlags<Qt::TouchPointState> touchPointStates, const QList<QTouchEvent::TouchPoint> &touchPoints) : QTouchEvent(eventType, deviceType, modifiers, touchPointStates, touchPoints)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  
};

QTouchEvent_Adaptor::~QTouchEvent_Adaptor() { }

//  Constructor QTouchEvent::QTouchEvent(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers, QFlags<Qt::TouchPointState> touchPointStates, const QList<QTouchEvent::TouchPoint> &touchPoints) (adaptor class)

static void _init_ctor_QTouchEvent_Adaptor_14068 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("eventType");
  decl->add_arg<const qt_gsi::Converter<QEvent::Type>::target_type & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("deviceType", true, "QTouchEvent::TouchScreen");
  decl->add_arg<const qt_gsi::Converter<QTouchEvent::DeviceType>::target_type & > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("modifiers", true, "Qt::NoModifier");
  decl->add_arg<const qt_gsi::Converter<QFlags<Qt::KeyboardModifier> >::target_type & > (argspec_2);
  static gsi::ArgSpecBase argspec_3 ("touchPointStates", true, "0");
  decl->add_arg<const qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type & > (argspec_3);
  static gsi::ArgSpecBase argspec_4 ("touchPoints", true, "QList<QTouchEvent::TouchPoint>()");
  decl->add_arg<const qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type & > (argspec_4);
  decl->set_return_new<QTouchEvent_Adaptor *> ();
}

static void _call_ctor_QTouchEvent_Adaptor_14068 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QEvent::Type>::target_type & arg1 = args.read<const qt_gsi::Converter<QEvent::Type>::target_type & > ();
  tl::Heap heap;
  const qt_gsi::Converter<QTouchEvent::DeviceType>::target_type & arg2 = args ? args.read<const qt_gsi::Converter<QTouchEvent::DeviceType>::target_type & > () : (const qt_gsi::Converter<QTouchEvent::DeviceType>::target_type &)(qt_gsi::CppToQtReadAdaptor<QTouchEvent::DeviceType>(heap, QTouchEvent::TouchScreen));
  const qt_gsi::Converter<QFlags<Qt::KeyboardModifier> >::target_type & arg3 = args ? args.read<const qt_gsi::Converter<QFlags<Qt::KeyboardModifier> >::target_type & > () : (const qt_gsi::Converter<QFlags<Qt::KeyboardModifier> >::target_type &)(qt_gsi::CppToQtReadAdaptor<QFlags<Qt::KeyboardModifier> >(heap, Qt::NoModifier));
  const qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type & arg4 = args ? args.read<const qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type & > () : (const qt_gsi::Converter<QFlags<Qt::TouchPointState> >::target_type &)(qt_gsi::CppToQtReadAdaptor<QFlags<Qt::TouchPointState> >(heap, 0));
  const qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type & arg5 = args ? args.read<const qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type & > () : (const qt_gsi::Converter<QList<QTouchEvent::TouchPoint> >::target_type &)(qt_gsi::CppToQtReadAdaptor<QList<QTouchEvent::TouchPoint> >(heap, QList<QTouchEvent::TouchPoint>()));
  ret.write<QTouchEvent_Adaptor *> (new QTouchEvent_Adaptor (qt_gsi::QtToCppAdaptor<QEvent::Type>(arg1).cref(), qt_gsi::QtToCppAdaptor<QTouchEvent::DeviceType>(arg2).cref(), qt_gsi::QtToCppAdaptor<QFlags<Qt::KeyboardModifier> >(arg3).cref(), qt_gsi::QtToCppAdaptor<QFlags<Qt::TouchPointState> >(arg4).cref(), qt_gsi::QtToCppAdaptor<QList<QTouchEvent::TouchPoint> >(arg5).cref()));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTouchEvent_Adaptor_14068 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTouchEvent::QTouchEvent(QEvent::Type eventType, QTouchEvent::DeviceType deviceType, QFlags<Qt::KeyboardModifier> modifiers, QFlags<Qt::TouchPointState> touchPointStates, const QList<QTouchEvent::TouchPoint> &touchPoints)\nThis method creates an object of class QTouchEvent.", &_init_ctor_QTouchEvent_Adaptor_14068, &_call_ctor_QTouchEvent_Adaptor_14068);
}

namespace gsi
{

extern gsi::Class<QTouchEvent> decl_QTouchEvent;

gsi::Class<QTouchEvent_Adaptor> decl_QTouchEvent_Adaptor (decl_QTouchEvent, "QTouchEvent",
  gsi::Methods(_create_ctor_QTouchEvent_Adaptor_14068 ()),
  "@qt\n@brief Binding of QTouchEvent");

}


//  Implementation of the enum wrapper class for QTouchEvent::DeviceType
namespace qt_gsi
{

static QTouchEvent_DeviceType_Enum *c_1_QTouchEvent_DeviceType_Enum () { return new QTouchEvent_DeviceType_Enum (QTouchEvent::TouchScreen); }
static QTouchEvent_DeviceType_Enum *c_2_QTouchEvent_DeviceType_Enum () { return new QTouchEvent_DeviceType_Enum (QTouchEvent::TouchPad); }

static gsi::Methods mkdefs_QTouchEvent_DeviceType () {
  return
    gsi::constant ("TouchScreen", &qt_gsi::c_1_QTouchEvent_DeviceType_Enum, "@brief Enum constant QTouchEvent::TouchScreen") +
    gsi::constant ("TouchPad", &qt_gsi::c_2_QTouchEvent_DeviceType_Enum, "@brief Enum constant QTouchEvent::TouchPad");
}

static std::string to_s_QTouchEvent_DeviceType_Enum (const QTouchEvent_DeviceType_Enum *e)
{
  if (e->value () == QTouchEvent::TouchScreen) { return tl::sprintf ("TouchScreen (%u)", (unsigned int) e->value ()); }
  if (e->value () == QTouchEvent::TouchPad) { return tl::sprintf ("TouchPad (%u)", (unsigned int) e->value ()); }
  return std::string ("(not a valid enum evalue)");
}

static unsigned int to_i_QTouchEvent_DeviceType_Enum (const QTouchEvent_DeviceType_Enum *e)
{
  return (unsigned int) e->value ();
}

static QTouchEvent_DeviceType_Enum *from_i_QTouchEvent_DeviceType_Enum (unsigned int i)
{
  return new QTouchEvent_DeviceType_Enum ((QTouchEvent::DeviceType) i);
}

static bool equalQTouchEvent_DeviceType_Enum (const QTouchEvent_DeviceType_Enum *e, QTouchEvent_DeviceType_Enum d)
{
  return e->value () == d.value ();
}

static bool equal2QTouchEvent_DeviceType_Enum (const QTouchEvent_DeviceType_Enum *e, unsigned int i)
{
  return (unsigned int) e->value () == i;
}

static QTouchEvent_DeviceType_Enums oropQTouchEvent_DeviceType_Enums (const QTouchEvent_DeviceType_Enums *e, const QTouchEvent_DeviceType_Enums &d)
{
  return e->flags () | d.flags ();
}

static QTouchEvent_DeviceType_Enums andopQTouchEvent_DeviceType_Enums (const QTouchEvent_DeviceType_Enums *e, const QTouchEvent_DeviceType_Enums &d)
{
  return e->flags () & d.flags ();
}

static QTouchEvent_DeviceType_Enums xoropQTouchEvent_DeviceType_Enums (const QTouchEvent_DeviceType_Enums *e, const QTouchEvent_DeviceType_Enums &d)
{
  return e->flags () ^ d.flags ();
}

static std::string to_s_QTouchEvent_DeviceType_Enums (const QTouchEvent_DeviceType_Enums *e)
{
  std::string l;
  if (e->testFlag (QTouchEvent::TouchScreen)) { if (!l.empty ()) l += "|"; l += "TouchScreen"; }
  if (e->testFlag (QTouchEvent::TouchPad)) { if (!l.empty ()) l += "|"; l += "TouchPad"; }
  return tl::sprintf ("%u (%s)", (unsigned int) (e->flags ()), l);
}

static int to_i_QTouchEvent_DeviceType_Enums (const QTouchEvent_DeviceType_Enums *e)
{
  return int (e->flags ());
}

static bool testFlag_QTouchEvent_DeviceType_Enums (const QTouchEvent_DeviceType_Enums *e, const QTouchEvent_DeviceType_Enum &d)
{
  return e->flags ().testFlag (d.value ());
}

}

namespace gsi
{

//  Declarations for QFlags<enum> wrapper class
gsi::Class<qt_gsi::QTouchEvent_DeviceType_Enums> decl_QTouchEvent_DeviceType_Enums ("QTouchEvent_QFlags_DeviceType",
  gsi::method_ext ("|", &qt_gsi::oropQTouchEvent_DeviceType_Enums, gsi::arg ("other"), "@brief 'or' operator between two flag sets") +
  gsi::method_ext ("&", &qt_gsi::andopQTouchEvent_DeviceType_Enums, gsi::arg ("other"), "@brief 'and' operator between two flag sets") +
  gsi::method_ext ("^", &qt_gsi::xoropQTouchEvent_DeviceType_Enums, gsi::arg ("other"), "@brief 'xor' operator between two flag sets") +
  gsi::method_ext ("to_s|inspect", &qt_gsi::to_s_QTouchEvent_DeviceType_Enums, "@brief Converts the flag set to a string") +
  gsi::method_ext ("to_i", &qt_gsi::to_i_QTouchEvent_DeviceType_Enums, "@brief Returns the integer value encoding the flag set") +
  gsi::method_ext ("testFlag", &qt_gsi::testFlag_QTouchEvent_DeviceType_Enums, gsi::arg ("flag"), "@brief Tests whether the flag is contained in the flag set"),
  "@qt\n@brief This class represents the QFlags<QTouchEvent::DeviceType> flag set");

//  Declarations for enum wrapper class
gsi::Class<qt_gsi::QTouchEvent_DeviceType_Enum> decl_QTouchEvent_DeviceType_Enum (decl_QTouchEvent_DeviceType_Enums, "QTouchEvent_DeviceType",
  qt_gsi::mkdefs_QTouchEvent_DeviceType () +
  gsi::method_ext ("to_s|inspect", &qt_gsi::to_s_QTouchEvent_DeviceType_Enum, "@brief Converts the enum class to a string") +
  gsi::method_ext ("to_i", &qt_gsi::to_i_QTouchEvent_DeviceType_Enum, "@brief Converts the enum class to an integer") +
  gsi::method_ext ("==", &qt_gsi::equalQTouchEvent_DeviceType_Enum, gsi::arg ("other"), "@brief Compares the enum class against an enum of it's own type") +
  gsi::method_ext ("==", &qt_gsi::equal2QTouchEvent_DeviceType_Enum, gsi::arg ("other"), "@brief Compares the enum class against an integer") +
  gsi::constructor ("new", &qt_gsi::from_i_QTouchEvent_DeviceType_Enum, gsi::arg ("value"), "@brief Creates the enum object from an integer"),
  "@qt\n@brief This class represents the QTouchEvent::DeviceType enum");

//  Inject the declarations into the parent
static gsi::ClassExt<QTouchEvent> inject_QTouchEvent_DeviceType_Enum_in_parent (qt_gsi::mkdefs_QTouchEvent_DeviceType ());
static gsi::ClassExt<QTouchEvent> decl_QTouchEvent_DeviceType_Enum_as_child (decl_QTouchEvent_DeviceType_Enum, "DeviceType");

}

