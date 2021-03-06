
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
*  @file gsiDeclQButtonGroup.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQButtonGroup_EventAdaptor.h"
#include "gsiDeclQButtonGroup_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QButtonGroup

//  get static meta object

static void _init_smo (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<const QMetaObject &> ();
}

static void _call_smo (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const QMetaObject &> (QButtonGroup::staticMetaObject);
}

static qt_gsi::GenericStaticMethod *_create_smo ()
{
  return new qt_gsi::GenericStaticMethod ("staticMetaObject", "@brief Obtains the static MetaObject for this class.", &_init_smo, &_call_smo);
}

// void QButtonGroup::addButton(QAbstractButton *)


static void _init_f_addButton_2159 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QAbstractButton * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_addButton_2159 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QAbstractButton *arg1 = args.read<QAbstractButton * > ();
  ((QButtonGroup *)cls)->addButton (arg1);
}

static qt_gsi::GenericMethod *_create_f_addButton_2159 ()
{
  return new qt_gsi::GenericMethod ("addButton", "@brief Method void QButtonGroup::addButton(QAbstractButton *)\n", false, &_init_f_addButton_2159, &_call_f_addButton_2159);
}

// void QButtonGroup::addButton(QAbstractButton *, int id)


static void _init_f_addButton_2818 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QAbstractButton * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("id");
  decl->add_arg<int > (argspec_1);
  decl->set_return<void > ();
}

static void _call_f_addButton_2818 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QAbstractButton *arg1 = args.read<QAbstractButton * > ();
  int arg2 = args.read<int > ();
  ((QButtonGroup *)cls)->addButton (arg1, arg2);
}

static qt_gsi::GenericMethod *_create_f_addButton_2818 ()
{
  return new qt_gsi::GenericMethod ("addButton", "@brief Method void QButtonGroup::addButton(QAbstractButton *, int id)\n", false, &_init_f_addButton_2818, &_call_f_addButton_2818);
}

// QAbstractButton *QButtonGroup::button(int id)


static void _init_f_button_c767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("id");
  decl->add_arg<int > (argspec_0);
  decl->set_return<QAbstractButton * > ();
}

static void _call_f_button_c767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ret.write<QAbstractButton * > ((QAbstractButton *)((QButtonGroup *)cls)->button (arg1));
}

static qt_gsi::GenericMethod *_create_f_button_c767 ()
{
  return new qt_gsi::GenericMethod ("button", "@brief Method QAbstractButton *QButtonGroup::button(int id)\n", true, &_init_f_button_c767, &_call_f_button_c767);
}

// QList<QAbstractButton *> QButtonGroup::buttons()


static void _init_f_buttons_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QAbstractButton *> >::target_type > ();
}

static void _call_f_buttons_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QAbstractButton *> >::target_type > ((qt_gsi::Converter<QList<QAbstractButton *> >::target_type)qt_gsi::CppToQtAdaptor<QList<QAbstractButton *> >(((QButtonGroup *)cls)->buttons ()));
}

static qt_gsi::GenericMethod *_create_f_buttons_c0 ()
{
  return new qt_gsi::GenericMethod ("buttons", "@brief Method QList<QAbstractButton *> QButtonGroup::buttons()\n", true, &_init_f_buttons_c0, &_call_f_buttons_c0);
}

// QAbstractButton *QButtonGroup::checkedButton()


static void _init_f_checkedButton_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QAbstractButton * > ();
}

static void _call_f_checkedButton_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QAbstractButton * > ((QAbstractButton *)((QButtonGroup *)cls)->checkedButton ());
}

static qt_gsi::GenericMethod *_create_f_checkedButton_c0 ()
{
  return new qt_gsi::GenericMethod ("checkedButton", "@brief Method QAbstractButton *QButtonGroup::checkedButton()\n", true, &_init_f_checkedButton_c0, &_call_f_checkedButton_c0);
}

// int QButtonGroup::checkedId()


static void _init_f_checkedId_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<int > ();
}

static void _call_f_checkedId_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<int > ((int)((QButtonGroup *)cls)->checkedId ());
}

static qt_gsi::GenericMethod *_create_f_checkedId_c0 ()
{
  return new qt_gsi::GenericMethod ("checkedId", "@brief Method int QButtonGroup::checkedId()\n", true, &_init_f_checkedId_c0, &_call_f_checkedId_c0);
}

// bool QButtonGroup::exclusive()


static void _init_f_exclusive_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_exclusive_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QButtonGroup *)cls)->exclusive ());
}

static qt_gsi::GenericMethod *_create_f_exclusive_c0 ()
{
  return new qt_gsi::GenericMethod (":exclusive", "@brief Method bool QButtonGroup::exclusive()\n", true, &_init_f_exclusive_c0, &_call_f_exclusive_c0);
}

// int QButtonGroup::id(QAbstractButton *button)


static void _init_f_id_c2159 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("button");
  decl->add_arg<QAbstractButton * > (argspec_0);
  decl->set_return<int > ();
}

static void _call_f_id_c2159 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QAbstractButton *arg1 = args.read<QAbstractButton * > ();
  ret.write<int > ((int)((QButtonGroup *)cls)->id (arg1));
}

static qt_gsi::GenericMethod *_create_f_id_c2159 ()
{
  return new qt_gsi::GenericMethod ("id", "@brief Method int QButtonGroup::id(QAbstractButton *button)\n", true, &_init_f_id_c2159, &_call_f_id_c2159);
}

// void QButtonGroup::removeButton(QAbstractButton *)


static void _init_f_removeButton_2159 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QAbstractButton * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_removeButton_2159 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QAbstractButton *arg1 = args.read<QAbstractButton * > ();
  ((QButtonGroup *)cls)->removeButton (arg1);
}

static qt_gsi::GenericMethod *_create_f_removeButton_2159 ()
{
  return new qt_gsi::GenericMethod ("removeButton", "@brief Method void QButtonGroup::removeButton(QAbstractButton *)\n", false, &_init_f_removeButton_2159, &_call_f_removeButton_2159);
}

// void QButtonGroup::setExclusive(bool)


static void _init_f_setExclusive_864 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<bool > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setExclusive_864 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  bool arg1 = args.read<bool > ();
  ((QButtonGroup *)cls)->setExclusive (arg1);
}

static qt_gsi::GenericMethod *_create_f_setExclusive_864 ()
{
  return new qt_gsi::GenericMethod ("setExclusive|exclusive=", "@brief Method void QButtonGroup::setExclusive(bool)\n", false, &_init_f_setExclusive_864, &_call_f_setExclusive_864);
}

// void QButtonGroup::setId(QAbstractButton *button, int id)


static void _init_f_setId_2818 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("button");
  decl->add_arg<QAbstractButton * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("id");
  decl->add_arg<int > (argspec_1);
  decl->set_return<void > ();
}

static void _call_f_setId_2818 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QAbstractButton *arg1 = args.read<QAbstractButton * > ();
  int arg2 = args.read<int > ();
  ((QButtonGroup *)cls)->setId (arg1, arg2);
}

static qt_gsi::GenericMethod *_create_f_setId_2818 ()
{
  return new qt_gsi::GenericMethod ("setId", "@brief Method void QButtonGroup::setId(QAbstractButton *button, int id)\n", false, &_init_f_setId_2818, &_call_f_setId_2818);
}

// static QString QButtonGroup::tr(const char *s, const char *c)


static void _init_f_tr_3354 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<QString > ();
}

static void _call_f_tr_3354 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  const char *arg2 = args ? args.read<const char * > () : (const char *)(0);
  ret.write<QString > ((QString)QButtonGroup::tr (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_f_tr_3354 ()
{
  return new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QButtonGroup::tr(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_tr_3354, &_call_f_tr_3354);
}

// static QString QButtonGroup::tr(const char *s, const char *c, int n)


static void _init_f_tr_4013 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c");
  decl->add_arg<const char * > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("n");
  decl->add_arg<int > (argspec_2);
  decl->set_return<QString > ();
}

static void _call_f_tr_4013 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  const char *arg2 = args.read<const char * > ();
  int arg3 = args.read<int > ();
  ret.write<QString > ((QString)QButtonGroup::tr (arg1, arg2, arg3));
}

static qt_gsi::GenericStaticMethod *_create_f_tr_4013 ()
{
  return new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QButtonGroup::tr(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_tr_4013, &_call_f_tr_4013);
}

// static QString QButtonGroup::trUtf8(const char *s, const char *c)


static void _init_f_trUtf8_3354 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<QString > ();
}

static void _call_f_trUtf8_3354 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  const char *arg2 = args ? args.read<const char * > () : (const char *)(0);
  ret.write<QString > ((QString)QButtonGroup::trUtf8 (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_f_trUtf8_3354 ()
{
  return new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QButtonGroup::trUtf8(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_3354, &_call_f_trUtf8_3354);
}

// static QString QButtonGroup::trUtf8(const char *s, const char *c, int n)


static void _init_f_trUtf8_4013 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c");
  decl->add_arg<const char * > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("n");
  decl->add_arg<int > (argspec_2);
  decl->set_return<QString > ();
}

static void _call_f_trUtf8_4013 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  const char *arg2 = args.read<const char * > ();
  int arg3 = args.read<int > ();
  ret.write<QString > ((QString)QButtonGroup::trUtf8 (arg1, arg2, arg3));
}

static qt_gsi::GenericStaticMethod *_create_f_trUtf8_4013 ()
{
  return new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QButtonGroup::trUtf8(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_4013, &_call_f_trUtf8_4013);
}

static qt_gsi::QObjectConnector<QButtonGroup, QButtonGroup_EventAdaptor> ea_QButtonGroup;

namespace gsi
{
extern gsi::Class<QObject> decl_QObject;

gsi::Class<QButtonGroup> decl_QButtonGroup (ea_QButtonGroup, decl_QObject, "QButtonGroup_Native",
  gsi::Methods(_create_smo ()) +
  gsi::Methods(_create_f_addButton_2159 ()) +
  gsi::Methods(_create_f_addButton_2818 ()) +
  gsi::Methods(_create_f_button_c767 ()) +
  gsi::Methods(_create_f_buttons_c0 ()) +
  gsi::Methods(_create_f_checkedButton_c0 ()) +
  gsi::Methods(_create_f_checkedId_c0 ()) +
  gsi::Methods(_create_f_exclusive_c0 ()) +
  gsi::Methods(_create_f_id_c2159 ()) +
  gsi::Methods(_create_f_removeButton_2159 ()) +
  gsi::Methods(_create_f_setExclusive_864 ()) +
  gsi::Methods(_create_f_setId_2818 ()) +
  qt_gsi::qt_signal<QButtonGroup, QButtonGroup_EventAdaptor, QAbstractButton *> ("buttonClicked_qab", &QButtonGroup_EventAdaptor::buttonClicked_e_2159, gsi::arg("arg1"), "@brief Signal declaration for QButtonGroup::buttonClicked(QAbstractButton *)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QButtonGroup, QButtonGroup_EventAdaptor, int> ("buttonClicked", &QButtonGroup_EventAdaptor::buttonClicked_e_767, gsi::arg("arg1"), "@brief Signal declaration for QButtonGroup::buttonClicked(int)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QButtonGroup, QButtonGroup_EventAdaptor, QAbstractButton *> ("buttonPressed_qab", &QButtonGroup_EventAdaptor::buttonPressed_e_2159, gsi::arg("arg1"), "@brief Signal declaration for QButtonGroup::buttonPressed(QAbstractButton *)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QButtonGroup, QButtonGroup_EventAdaptor, int> ("buttonPressed", &QButtonGroup_EventAdaptor::buttonPressed_e_767, gsi::arg("arg1"), "@brief Signal declaration for QButtonGroup::buttonPressed(int)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QButtonGroup, QButtonGroup_EventAdaptor, QAbstractButton *> ("buttonReleased_qab", &QButtonGroup_EventAdaptor::buttonReleased_e_2159, gsi::arg("arg1"), "@brief Signal declaration for QButtonGroup::buttonReleased(QAbstractButton *)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QButtonGroup, QButtonGroup_EventAdaptor, int> ("buttonReleased", &QButtonGroup_EventAdaptor::buttonReleased_e_767, gsi::arg("arg1"), "@brief Signal declaration for QButtonGroup::buttonReleased(int)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QButtonGroup, QButtonGroup_EventAdaptor, QObject *> ("destroyed", &QButtonGroup_EventAdaptor::destroyed_e_1302, gsi::arg("arg1"), "@brief Signal declaration for QButtonGroup::destroyed(QObject *)\nYou can bind a procedure to this signal.") +
  gsi::Methods(_create_f_tr_3354 ()) +
  gsi::Methods(_create_f_tr_4013 ()) +
  gsi::Methods(_create_f_trUtf8_3354 ()) +
  gsi::Methods(_create_f_trUtf8_4013 ()),
  "@hide\n@alias QButtonGroup");
}


class QButtonGroup_Adaptor : public QButtonGroup, public qt_gsi::QtObjectBase
{
public:

  virtual ~QButtonGroup_Adaptor();

  //  [adaptor ctor] QButtonGroup::QButtonGroup(QObject *parent)
  QButtonGroup_Adaptor() : QButtonGroup()
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QButtonGroup::QButtonGroup(QObject *parent)
  QButtonGroup_Adaptor(QObject *parent) : QButtonGroup(parent)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  int QButtonGroup::receivers(const char *signal)
  int fp_QButtonGroup_receivers_c1731 (const char *signal) const {
    return QButtonGroup::receivers(signal);
  }

  //  QObject *QButtonGroup::sender()
  QObject * fp_QButtonGroup_sender_c0 () const {
    return QButtonGroup::sender();
  }

  //  [adaptor impl] bool QButtonGroup::event(QEvent *)
  bool cbs_event_1217_0(QEvent *arg1)
  {
    return QButtonGroup::event(arg1);
  }

  virtual bool event(QEvent *arg1)
  {
    if (cb_event_1217_0.can_issue()) {
      return cb_event_1217_0.issue<QButtonGroup_Adaptor, bool, QEvent *>(&QButtonGroup_Adaptor::cbs_event_1217_0, arg1);
    } else {
      return QButtonGroup::event(arg1);
    }
  }

  //  [adaptor impl] bool QButtonGroup::eventFilter(QObject *, QEvent *)
  bool cbs_eventFilter_2411_0(QObject *arg1, QEvent *arg2)
  {
    return QButtonGroup::eventFilter(arg1, arg2);
  }

  virtual bool eventFilter(QObject *arg1, QEvent *arg2)
  {
    if (cb_eventFilter_2411_0.can_issue()) {
      return cb_eventFilter_2411_0.issue<QButtonGroup_Adaptor, bool, QObject *, QEvent *>(&QButtonGroup_Adaptor::cbs_eventFilter_2411_0, arg1, arg2);
    } else {
      return QButtonGroup::eventFilter(arg1, arg2);
    }
  }

  //  [adaptor impl] void QButtonGroup::childEvent(QChildEvent *)
  void cbs_childEvent_1701_0(QChildEvent *arg1)
  {
    QButtonGroup::childEvent(arg1);
  }

  virtual void childEvent(QChildEvent *arg1)
  {
    if (cb_childEvent_1701_0.can_issue()) {
      cb_childEvent_1701_0.issue<QButtonGroup_Adaptor, QChildEvent *>(&QButtonGroup_Adaptor::cbs_childEvent_1701_0, arg1);
    } else {
      QButtonGroup::childEvent(arg1);
    }
  }

  //  [adaptor impl] void QButtonGroup::customEvent(QEvent *)
  void cbs_customEvent_1217_0(QEvent *arg1)
  {
    QButtonGroup::customEvent(arg1);
  }

  virtual void customEvent(QEvent *arg1)
  {
    if (cb_customEvent_1217_0.can_issue()) {
      cb_customEvent_1217_0.issue<QButtonGroup_Adaptor, QEvent *>(&QButtonGroup_Adaptor::cbs_customEvent_1217_0, arg1);
    } else {
      QButtonGroup::customEvent(arg1);
    }
  }

  //  [adaptor impl] void QButtonGroup::disconnectNotify(const char *signal)
  void cbs_disconnectNotify_1731_0(const char *signal)
  {
    QButtonGroup::disconnectNotify(signal);
  }

  virtual void disconnectNotify(const char *signal)
  {
    if (cb_disconnectNotify_1731_0.can_issue()) {
      cb_disconnectNotify_1731_0.issue<QButtonGroup_Adaptor, const char *>(&QButtonGroup_Adaptor::cbs_disconnectNotify_1731_0, signal);
    } else {
      QButtonGroup::disconnectNotify(signal);
    }
  }

  //  [adaptor impl] void QButtonGroup::timerEvent(QTimerEvent *)
  void cbs_timerEvent_1730_0(QTimerEvent *arg1)
  {
    QButtonGroup::timerEvent(arg1);
  }

  virtual void timerEvent(QTimerEvent *arg1)
  {
    if (cb_timerEvent_1730_0.can_issue()) {
      cb_timerEvent_1730_0.issue<QButtonGroup_Adaptor, QTimerEvent *>(&QButtonGroup_Adaptor::cbs_timerEvent_1730_0, arg1);
    } else {
      QButtonGroup::timerEvent(arg1);
    }
  }

  gsi::Callback cb_event_1217_0;
  gsi::Callback cb_eventFilter_2411_0;
  gsi::Callback cb_childEvent_1701_0;
  gsi::Callback cb_customEvent_1217_0;
  gsi::Callback cb_disconnectNotify_1731_0;
  gsi::Callback cb_timerEvent_1730_0;
};

QButtonGroup_Adaptor::~QButtonGroup_Adaptor() { }

//  Constructor QButtonGroup::QButtonGroup(QObject *parent) (adaptor class)

static void _init_ctor_QButtonGroup_Adaptor_1302 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent", true, "0");
  decl->add_arg<QObject * > (argspec_0);
  decl->set_return_new<QButtonGroup_Adaptor *> ();
}

static void _call_ctor_QButtonGroup_Adaptor_1302 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QObject *arg1 = args ? args.read<QObject * > () : (QObject *)(0);
  ret.write<QButtonGroup_Adaptor *> (new QButtonGroup_Adaptor (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QButtonGroup_Adaptor_1302 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QButtonGroup::QButtonGroup(QObject *parent)\nThis method creates an object of class QButtonGroup.", &_init_ctor_QButtonGroup_Adaptor_1302, &_call_ctor_QButtonGroup_Adaptor_1302);
}

// int QButtonGroup::receivers(const char *signal)

static void _init_fp_receivers_c1731 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("signal");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<int > ();
}

static void _call_fp_receivers_c1731 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  ret.write<int > ((int)((QButtonGroup_Adaptor *)cls)->fp_QButtonGroup_receivers_c1731 (arg1));
}

static qt_gsi::GenericMethod*_create_fp_receivers_c1731 ()
{
  return new qt_gsi::GenericMethod("*receivers", "@brief Method int QButtonGroup::receivers(const char *signal)\nThis method is protected and can only be called from inside a derived class.", true, &_init_fp_receivers_c1731, &_call_fp_receivers_c1731);
}


// QObject *QButtonGroup::sender()

static void _init_fp_sender_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QObject * > ();
}

static void _call_fp_sender_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QObject * > ((QObject *)((QButtonGroup_Adaptor *)cls)->fp_QButtonGroup_sender_c0 ());
}

static qt_gsi::GenericMethod*_create_fp_sender_c0 ()
{
  return new qt_gsi::GenericMethod("*sender", "@brief Method QObject *QButtonGroup::sender()\nThis method is protected and can only be called from inside a derived class.", true, &_init_fp_sender_c0, &_call_fp_sender_c0);
}


// bool QButtonGroup::event(QEvent *)

static void _init_cbs_event_1217_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_cbs_event_1217_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QEvent *arg1 = args.read<QEvent * > ();
  ret.write<bool > ((bool)((QButtonGroup_Adaptor *)cls)->cbs_event_1217_0 (arg1));
}

static void _set_callback_cbs_event_1217_0 (void *cls, const gsi::Callback &cb)
{
  ((QButtonGroup_Adaptor *)cls)->cb_event_1217_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_event_1217_0 ()
{
  return new qt_gsi::GenericMethod ("event", "@hide", false, &_init_cbs_event_1217_0, &_call_cbs_event_1217_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_event_1217_0 ()
{
  return new qt_gsi::GenericMethod ("event", "@brief Virtual method bool QButtonGroup::event(QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_event_1217_0, &_call_cbs_event_1217_0, &_set_callback_cbs_event_1217_0);
}


// bool QButtonGroup::eventFilter(QObject *, QEvent *)

static void _init_cbs_eventFilter_2411_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QObject * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("arg2");
  decl->add_arg<QEvent * > (argspec_1);
  decl->set_return<bool > ();
}

static void _call_cbs_eventFilter_2411_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QObject *arg1 = args.read<QObject * > ();
  QEvent *arg2 = args.read<QEvent * > ();
  ret.write<bool > ((bool)((QButtonGroup_Adaptor *)cls)->cbs_eventFilter_2411_0 (arg1, arg2));
}

static void _set_callback_cbs_eventFilter_2411_0 (void *cls, const gsi::Callback &cb)
{
  ((QButtonGroup_Adaptor *)cls)->cb_eventFilter_2411_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_eventFilter_2411_0 ()
{
  return new qt_gsi::GenericMethod ("eventFilter", "@hide", false, &_init_cbs_eventFilter_2411_0, &_call_cbs_eventFilter_2411_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_eventFilter_2411_0 ()
{
  return new qt_gsi::GenericMethod ("eventFilter", "@brief Virtual method bool QButtonGroup::eventFilter(QObject *, QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_eventFilter_2411_0, &_call_cbs_eventFilter_2411_0, &_set_callback_cbs_eventFilter_2411_0);
}


// void QButtonGroup::childEvent(QChildEvent *)

static void _init_cbs_childEvent_1701_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QChildEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_childEvent_1701_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QChildEvent *arg1 = args.read<QChildEvent * > ();
  ((QButtonGroup_Adaptor *)cls)->cbs_childEvent_1701_0 (arg1);
}

static void _set_callback_cbs_childEvent_1701_0 (void *cls, const gsi::Callback &cb)
{
  ((QButtonGroup_Adaptor *)cls)->cb_childEvent_1701_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_childEvent_1701_0 ()
{
  return new qt_gsi::GenericMethod ("*childEvent", "@hide", false, &_init_cbs_childEvent_1701_0, &_call_cbs_childEvent_1701_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_childEvent_1701_0 ()
{
  return new qt_gsi::GenericMethod ("*childEvent", "@brief Virtual method void QButtonGroup::childEvent(QChildEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_childEvent_1701_0, &_call_cbs_childEvent_1701_0, &_set_callback_cbs_childEvent_1701_0);
}


// void QButtonGroup::customEvent(QEvent *)

static void _init_cbs_customEvent_1217_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_customEvent_1217_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QEvent *arg1 = args.read<QEvent * > ();
  ((QButtonGroup_Adaptor *)cls)->cbs_customEvent_1217_0 (arg1);
}

static void _set_callback_cbs_customEvent_1217_0 (void *cls, const gsi::Callback &cb)
{
  ((QButtonGroup_Adaptor *)cls)->cb_customEvent_1217_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_customEvent_1217_0 ()
{
  return new qt_gsi::GenericMethod ("*customEvent", "@hide", false, &_init_cbs_customEvent_1217_0, &_call_cbs_customEvent_1217_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_customEvent_1217_0 ()
{
  return new qt_gsi::GenericMethod ("*customEvent", "@brief Virtual method void QButtonGroup::customEvent(QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_customEvent_1217_0, &_call_cbs_customEvent_1217_0, &_set_callback_cbs_customEvent_1217_0);
}


// void QButtonGroup::disconnectNotify(const char *signal)

static void _init_cbs_disconnectNotify_1731_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("signal");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_disconnectNotify_1731_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  ((QButtonGroup_Adaptor *)cls)->cbs_disconnectNotify_1731_0 (arg1);
}

static void _set_callback_cbs_disconnectNotify_1731_0 (void *cls, const gsi::Callback &cb)
{
  ((QButtonGroup_Adaptor *)cls)->cb_disconnectNotify_1731_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_disconnectNotify_1731_0 ()
{
  return new qt_gsi::GenericMethod ("*disconnectNotify", "@hide", false, &_init_cbs_disconnectNotify_1731_0, &_call_cbs_disconnectNotify_1731_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_disconnectNotify_1731_0 ()
{
  return new qt_gsi::GenericMethod ("*disconnectNotify", "@brief Virtual method void QButtonGroup::disconnectNotify(const char *signal)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_disconnectNotify_1731_0, &_call_cbs_disconnectNotify_1731_0, &_set_callback_cbs_disconnectNotify_1731_0);
}


// void QButtonGroup::timerEvent(QTimerEvent *)

static void _init_cbs_timerEvent_1730_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QTimerEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_timerEvent_1730_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QTimerEvent *arg1 = args.read<QTimerEvent * > ();
  ((QButtonGroup_Adaptor *)cls)->cbs_timerEvent_1730_0 (arg1);
}

static void _set_callback_cbs_timerEvent_1730_0 (void *cls, const gsi::Callback &cb)
{
  ((QButtonGroup_Adaptor *)cls)->cb_timerEvent_1730_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_timerEvent_1730_0 ()
{
  return new qt_gsi::GenericMethod ("*timerEvent", "@hide", false, &_init_cbs_timerEvent_1730_0, &_call_cbs_timerEvent_1730_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_timerEvent_1730_0 ()
{
  return new qt_gsi::GenericMethod ("*timerEvent", "@brief Virtual method void QButtonGroup::timerEvent(QTimerEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_timerEvent_1730_0, &_call_cbs_timerEvent_1730_0, &_set_callback_cbs_timerEvent_1730_0);
}


namespace gsi
{

extern gsi::Class<QButtonGroup> decl_QButtonGroup;

gsi::Class<QButtonGroup_Adaptor> decl_QButtonGroup_Adaptor (decl_QButtonGroup, "QButtonGroup",
  gsi::Methods(_create_fp_receivers_c1731 ()) +
  gsi::Methods(_create_fp_sender_c0 ()) +
  gsi::Methods(_create_cbs_event_1217_0 ()) +
  gsi::Methods(_create_callback_cbs_event_1217_0 ()) +
  gsi::Methods(_create_cbs_eventFilter_2411_0 ()) +
  gsi::Methods(_create_callback_cbs_eventFilter_2411_0 ()) +
  gsi::Methods(_create_cbs_childEvent_1701_0 ()) +
  gsi::Methods(_create_callback_cbs_childEvent_1701_0 ()) +
  gsi::Methods(_create_cbs_customEvent_1217_0 ()) +
  gsi::Methods(_create_callback_cbs_customEvent_1217_0 ()) +
  gsi::Methods(_create_cbs_disconnectNotify_1731_0 ()) +
  gsi::Methods(_create_callback_cbs_disconnectNotify_1731_0 ()) +
  gsi::Methods(_create_cbs_timerEvent_1730_0 ()) +
  gsi::Methods(_create_callback_cbs_timerEvent_1730_0 ()) +
  gsi::Methods(_create_ctor_QButtonGroup_Adaptor_1302 ()),
  "@qt\n@brief Binding of QButtonGroup");

}

