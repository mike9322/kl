
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
*  @file gsiDeclQWidgetAction.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQWidgetAction_EventAdaptor.h"
#include "gsiDeclQWidgetAction_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QWidgetAction

//  get static meta object

static void _init_smo (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<const QMetaObject &> ();
}

static void _call_smo (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const QMetaObject &> (QWidgetAction::staticMetaObject);
}

static qt_gsi::GenericStaticMethod *_create_smo ()
{
  return new qt_gsi::GenericStaticMethod ("staticMetaObject", "@brief Obtains the static MetaObject for this class.", &_init_smo, &_call_smo);
}

// QWidget *QWidgetAction::defaultWidget()


static void _init_f_defaultWidget_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QWidget * > ();
}

static void _call_f_defaultWidget_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QWidget * > ((QWidget *)((QWidgetAction *)cls)->defaultWidget ());
}

static qt_gsi::GenericMethod *_create_f_defaultWidget_c0 ()
{
  return new qt_gsi::GenericMethod (":defaultWidget", "@brief Method QWidget *QWidgetAction::defaultWidget()\n", true, &_init_f_defaultWidget_c0, &_call_f_defaultWidget_c0);
}

// void QWidgetAction::releaseWidget(QWidget *widget)


static void _init_f_releaseWidget_1315 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("widget");
  decl->add_arg<QWidget * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_releaseWidget_1315 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QWidget *arg1 = args.read<QWidget * > ();
  ((QWidgetAction *)cls)->releaseWidget (arg1);
}

static qt_gsi::GenericMethod *_create_f_releaseWidget_1315 ()
{
  return new qt_gsi::GenericMethod ("releaseWidget", "@brief Method void QWidgetAction::releaseWidget(QWidget *widget)\n", false, &_init_f_releaseWidget_1315, &_call_f_releaseWidget_1315);
}

// QWidget *QWidgetAction::requestWidget(QWidget *parent)


static void _init_f_requestWidget_1315 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent");
  decl->add_arg<QWidget * > (argspec_0);
  decl->set_return<QWidget * > ();
}

static void _call_f_requestWidget_1315 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QWidget *arg1 = args.read<QWidget * > ();
  ret.write<QWidget * > ((QWidget *)((QWidgetAction *)cls)->requestWidget (arg1));
}

static qt_gsi::GenericMethod *_create_f_requestWidget_1315 ()
{
  return new qt_gsi::GenericMethod ("requestWidget", "@brief Method QWidget *QWidgetAction::requestWidget(QWidget *parent)\n", false, &_init_f_requestWidget_1315, &_call_f_requestWidget_1315);
}

// void QWidgetAction::setDefaultWidget(QWidget *w)


static void _init_f_setDefaultWidget_1315 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("w");
  decl->add_arg<QWidget * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setDefaultWidget_1315 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QWidget *arg1 = args.read<QWidget * > ();
  ((QWidgetAction *)cls)->setDefaultWidget (arg1);
}

static qt_gsi::GenericMethod *_create_f_setDefaultWidget_1315 ()
{
  return new qt_gsi::GenericMethod ("setDefaultWidget|defaultWidget=", "@brief Method void QWidgetAction::setDefaultWidget(QWidget *w)\n", false, &_init_f_setDefaultWidget_1315, &_call_f_setDefaultWidget_1315);
}

// static QString QWidgetAction::tr(const char *s, const char *c)


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
  ret.write<QString > ((QString)QWidgetAction::tr (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_f_tr_3354 ()
{
  return new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QWidgetAction::tr(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_tr_3354, &_call_f_tr_3354);
}

// static QString QWidgetAction::tr(const char *s, const char *c, int n)


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
  ret.write<QString > ((QString)QWidgetAction::tr (arg1, arg2, arg3));
}

static qt_gsi::GenericStaticMethod *_create_f_tr_4013 ()
{
  return new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QWidgetAction::tr(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_tr_4013, &_call_f_tr_4013);
}

// static QString QWidgetAction::trUtf8(const char *s, const char *c)


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
  ret.write<QString > ((QString)QWidgetAction::trUtf8 (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_f_trUtf8_3354 ()
{
  return new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QWidgetAction::trUtf8(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_3354, &_call_f_trUtf8_3354);
}

// static QString QWidgetAction::trUtf8(const char *s, const char *c, int n)


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
  ret.write<QString > ((QString)QWidgetAction::trUtf8 (arg1, arg2, arg3));
}

static qt_gsi::GenericStaticMethod *_create_f_trUtf8_4013 ()
{
  return new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QWidgetAction::trUtf8(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_4013, &_call_f_trUtf8_4013);
}

static qt_gsi::QObjectConnector<QWidgetAction, QWidgetAction_EventAdaptor> ea_QWidgetAction;

namespace gsi
{
extern gsi::Class<QAction> decl_QAction;

gsi::Class<QWidgetAction> decl_QWidgetAction (ea_QWidgetAction, decl_QAction, "QWidgetAction_Native",
  gsi::Methods(_create_smo ()) +
  gsi::Methods(_create_f_defaultWidget_c0 ()) +
  gsi::Methods(_create_f_releaseWidget_1315 ()) +
  gsi::Methods(_create_f_requestWidget_1315 ()) +
  gsi::Methods(_create_f_setDefaultWidget_1315 ()) +
  qt_gsi::qt_signal<QWidgetAction, QWidgetAction_EventAdaptor> ("changed", &QWidgetAction_EventAdaptor::changed_e_0, "@brief Signal declaration for QWidgetAction::changed()\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QWidgetAction, QWidgetAction_EventAdaptor, QObject *> ("destroyed", &QWidgetAction_EventAdaptor::destroyed_e_1302, gsi::arg("arg1"), "@brief Signal declaration for QWidgetAction::destroyed(QObject *)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QWidgetAction, QWidgetAction_EventAdaptor> ("hovered", &QWidgetAction_EventAdaptor::hovered_e_0, "@brief Signal declaration for QWidgetAction::hovered()\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QWidgetAction, QWidgetAction_EventAdaptor, bool> ("toggled", &QWidgetAction_EventAdaptor::toggled_e_864, gsi::arg("arg1"), "@brief Signal declaration for QWidgetAction::toggled(bool)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QWidgetAction, QWidgetAction_EventAdaptor, bool> ("triggered", &QWidgetAction_EventAdaptor::triggered_e_864, gsi::arg("checked"), "@brief Signal declaration for QWidgetAction::triggered(bool checked)\nYou can bind a procedure to this signal.") +
  gsi::Methods(_create_f_tr_3354 ()) +
  gsi::Methods(_create_f_tr_4013 ()) +
  gsi::Methods(_create_f_trUtf8_3354 ()) +
  gsi::Methods(_create_f_trUtf8_4013 ()),
  "@hide\n@alias QWidgetAction");
}


class QWidgetAction_Adaptor : public QWidgetAction, public qt_gsi::QtObjectBase
{
public:

  virtual ~QWidgetAction_Adaptor();

  //  [adaptor ctor] QWidgetAction::QWidgetAction(QObject *parent)
  QWidgetAction_Adaptor(QObject *parent) : QWidgetAction(parent)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  QList<QWidget *> QWidgetAction::createdWidgets()
  qt_gsi::Converter<QList<QWidget *> >::target_type fp_QWidgetAction_createdWidgets_c0 () const {
    return qt_gsi::CppToQtAdaptor<QList<QWidget *> >(QWidgetAction::createdWidgets());
  }

  //  int QWidgetAction::receivers(const char *signal)
  int fp_QWidgetAction_receivers_c1731 (const char *signal) const {
    return QWidgetAction::receivers(signal);
  }

  //  QObject *QWidgetAction::sender()
  QObject * fp_QWidgetAction_sender_c0 () const {
    return QWidgetAction::sender();
  }

  //  [adaptor impl] void QWidgetAction::childEvent(QChildEvent *)
  void cbs_childEvent_1701_0(QChildEvent *arg1)
  {
    QWidgetAction::childEvent(arg1);
  }

  virtual void childEvent(QChildEvent *arg1)
  {
    if (cb_childEvent_1701_0.can_issue()) {
      cb_childEvent_1701_0.issue<QWidgetAction_Adaptor, QChildEvent *>(&QWidgetAction_Adaptor::cbs_childEvent_1701_0, arg1);
    } else {
      QWidgetAction::childEvent(arg1);
    }
  }

  //  [adaptor impl] QWidget *QWidgetAction::createWidget(QWidget *parent)
  QWidget * cbs_createWidget_1315_0(QWidget *parent)
  {
    return QWidgetAction::createWidget(parent);
  }

  virtual QWidget * createWidget(QWidget *parent)
  {
    if (cb_createWidget_1315_0.can_issue()) {
      return cb_createWidget_1315_0.issue<QWidgetAction_Adaptor, QWidget *, QWidget *>(&QWidgetAction_Adaptor::cbs_createWidget_1315_0, parent);
    } else {
      return QWidgetAction::createWidget(parent);
    }
  }

  //  [adaptor impl] void QWidgetAction::customEvent(QEvent *)
  void cbs_customEvent_1217_0(QEvent *arg1)
  {
    QWidgetAction::customEvent(arg1);
  }

  virtual void customEvent(QEvent *arg1)
  {
    if (cb_customEvent_1217_0.can_issue()) {
      cb_customEvent_1217_0.issue<QWidgetAction_Adaptor, QEvent *>(&QWidgetAction_Adaptor::cbs_customEvent_1217_0, arg1);
    } else {
      QWidgetAction::customEvent(arg1);
    }
  }

  //  [adaptor impl] void QWidgetAction::deleteWidget(QWidget *widget)
  void cbs_deleteWidget_1315_0(QWidget *widget)
  {
    QWidgetAction::deleteWidget(widget);
  }

  virtual void deleteWidget(QWidget *widget)
  {
    if (cb_deleteWidget_1315_0.can_issue()) {
      cb_deleteWidget_1315_0.issue<QWidgetAction_Adaptor, QWidget *>(&QWidgetAction_Adaptor::cbs_deleteWidget_1315_0, widget);
    } else {
      QWidgetAction::deleteWidget(widget);
    }
  }

  //  [adaptor impl] void QWidgetAction::disconnectNotify(const char *signal)
  void cbs_disconnectNotify_1731_0(const char *signal)
  {
    QWidgetAction::disconnectNotify(signal);
  }

  virtual void disconnectNotify(const char *signal)
  {
    if (cb_disconnectNotify_1731_0.can_issue()) {
      cb_disconnectNotify_1731_0.issue<QWidgetAction_Adaptor, const char *>(&QWidgetAction_Adaptor::cbs_disconnectNotify_1731_0, signal);
    } else {
      QWidgetAction::disconnectNotify(signal);
    }
  }

  //  [adaptor impl] bool QWidgetAction::event(QEvent *)
  bool cbs_event_1217_0(QEvent *arg1)
  {
    return QWidgetAction::event(arg1);
  }

  virtual bool event(QEvent *arg1)
  {
    if (cb_event_1217_0.can_issue()) {
      return cb_event_1217_0.issue<QWidgetAction_Adaptor, bool, QEvent *>(&QWidgetAction_Adaptor::cbs_event_1217_0, arg1);
    } else {
      return QWidgetAction::event(arg1);
    }
  }

  //  [adaptor impl] bool QWidgetAction::eventFilter(QObject *, QEvent *)
  bool cbs_eventFilter_2411_0(QObject *arg1, QEvent *arg2)
  {
    return QWidgetAction::eventFilter(arg1, arg2);
  }

  virtual bool eventFilter(QObject *arg1, QEvent *arg2)
  {
    if (cb_eventFilter_2411_0.can_issue()) {
      return cb_eventFilter_2411_0.issue<QWidgetAction_Adaptor, bool, QObject *, QEvent *>(&QWidgetAction_Adaptor::cbs_eventFilter_2411_0, arg1, arg2);
    } else {
      return QWidgetAction::eventFilter(arg1, arg2);
    }
  }

  //  [adaptor impl] void QWidgetAction::timerEvent(QTimerEvent *)
  void cbs_timerEvent_1730_0(QTimerEvent *arg1)
  {
    QWidgetAction::timerEvent(arg1);
  }

  virtual void timerEvent(QTimerEvent *arg1)
  {
    if (cb_timerEvent_1730_0.can_issue()) {
      cb_timerEvent_1730_0.issue<QWidgetAction_Adaptor, QTimerEvent *>(&QWidgetAction_Adaptor::cbs_timerEvent_1730_0, arg1);
    } else {
      QWidgetAction::timerEvent(arg1);
    }
  }

  gsi::Callback cb_childEvent_1701_0;
  gsi::Callback cb_createWidget_1315_0;
  gsi::Callback cb_customEvent_1217_0;
  gsi::Callback cb_deleteWidget_1315_0;
  gsi::Callback cb_disconnectNotify_1731_0;
  gsi::Callback cb_event_1217_0;
  gsi::Callback cb_eventFilter_2411_0;
  gsi::Callback cb_timerEvent_1730_0;
};

QWidgetAction_Adaptor::~QWidgetAction_Adaptor() { }

//  Constructor QWidgetAction::QWidgetAction(QObject *parent) (adaptor class)

static void _init_ctor_QWidgetAction_Adaptor_1302 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent");
  decl->add_arg<QObject * > (argspec_0);
  decl->set_return_new<QWidgetAction_Adaptor *> ();
}

static void _call_ctor_QWidgetAction_Adaptor_1302 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QObject *arg1 = args.read<QObject * > ();
  ret.write<QWidgetAction_Adaptor *> (new QWidgetAction_Adaptor (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QWidgetAction_Adaptor_1302 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QWidgetAction::QWidgetAction(QObject *parent)\nThis method creates an object of class QWidgetAction.", &_init_ctor_QWidgetAction_Adaptor_1302, &_call_ctor_QWidgetAction_Adaptor_1302);
}

// QList<QWidget *> QWidgetAction::createdWidgets()

static void _init_fp_createdWidgets_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QWidget *> >::target_type > ();
}

static void _call_fp_createdWidgets_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QWidget *> >::target_type > ((qt_gsi::Converter<QList<QWidget *> >::target_type)((QWidgetAction_Adaptor *)cls)->fp_QWidgetAction_createdWidgets_c0 ());
}

static qt_gsi::GenericMethod*_create_fp_createdWidgets_c0 ()
{
  return new qt_gsi::GenericMethod("*createdWidgets", "@brief Method QList<QWidget *> QWidgetAction::createdWidgets()\nThis method is protected and can only be called from inside a derived class.", true, &_init_fp_createdWidgets_c0, &_call_fp_createdWidgets_c0);
}


// int QWidgetAction::receivers(const char *signal)

static void _init_fp_receivers_c1731 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("signal");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<int > ();
}

static void _call_fp_receivers_c1731 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  ret.write<int > ((int)((QWidgetAction_Adaptor *)cls)->fp_QWidgetAction_receivers_c1731 (arg1));
}

static qt_gsi::GenericMethod*_create_fp_receivers_c1731 ()
{
  return new qt_gsi::GenericMethod("*receivers", "@brief Method int QWidgetAction::receivers(const char *signal)\nThis method is protected and can only be called from inside a derived class.", true, &_init_fp_receivers_c1731, &_call_fp_receivers_c1731);
}


// QObject *QWidgetAction::sender()

static void _init_fp_sender_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QObject * > ();
}

static void _call_fp_sender_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QObject * > ((QObject *)((QWidgetAction_Adaptor *)cls)->fp_QWidgetAction_sender_c0 ());
}

static qt_gsi::GenericMethod*_create_fp_sender_c0 ()
{
  return new qt_gsi::GenericMethod("*sender", "@brief Method QObject *QWidgetAction::sender()\nThis method is protected and can only be called from inside a derived class.", true, &_init_fp_sender_c0, &_call_fp_sender_c0);
}


// void QWidgetAction::childEvent(QChildEvent *)

static void _init_cbs_childEvent_1701_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QChildEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_childEvent_1701_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QChildEvent *arg1 = args.read<QChildEvent * > ();
  ((QWidgetAction_Adaptor *)cls)->cbs_childEvent_1701_0 (arg1);
}

static void _set_callback_cbs_childEvent_1701_0 (void *cls, const gsi::Callback &cb)
{
  ((QWidgetAction_Adaptor *)cls)->cb_childEvent_1701_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_childEvent_1701_0 ()
{
  return new qt_gsi::GenericMethod ("*childEvent", "@hide", false, &_init_cbs_childEvent_1701_0, &_call_cbs_childEvent_1701_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_childEvent_1701_0 ()
{
  return new qt_gsi::GenericMethod ("*childEvent", "@brief Virtual method void QWidgetAction::childEvent(QChildEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_childEvent_1701_0, &_call_cbs_childEvent_1701_0, &_set_callback_cbs_childEvent_1701_0);
}


// QWidget *QWidgetAction::createWidget(QWidget *parent)

static void _init_cbs_createWidget_1315_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent");
  decl->add_arg<QWidget * > (argspec_0);
  decl->set_return<QWidget * > ();
}

static void _call_cbs_createWidget_1315_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QWidget *arg1 = args.read<QWidget * > ();
  ret.write<QWidget * > ((QWidget *)((QWidgetAction_Adaptor *)cls)->cbs_createWidget_1315_0 (arg1));
}

static void _set_callback_cbs_createWidget_1315_0 (void *cls, const gsi::Callback &cb)
{
  ((QWidgetAction_Adaptor *)cls)->cb_createWidget_1315_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_createWidget_1315_0 ()
{
  return new qt_gsi::GenericMethod ("*createWidget", "@hide", false, &_init_cbs_createWidget_1315_0, &_call_cbs_createWidget_1315_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_createWidget_1315_0 ()
{
  return new qt_gsi::GenericMethod ("*createWidget", "@brief Virtual method QWidget *QWidgetAction::createWidget(QWidget *parent)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_createWidget_1315_0, &_call_cbs_createWidget_1315_0, &_set_callback_cbs_createWidget_1315_0);
}


// void QWidgetAction::customEvent(QEvent *)

static void _init_cbs_customEvent_1217_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_customEvent_1217_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QEvent *arg1 = args.read<QEvent * > ();
  ((QWidgetAction_Adaptor *)cls)->cbs_customEvent_1217_0 (arg1);
}

static void _set_callback_cbs_customEvent_1217_0 (void *cls, const gsi::Callback &cb)
{
  ((QWidgetAction_Adaptor *)cls)->cb_customEvent_1217_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_customEvent_1217_0 ()
{
  return new qt_gsi::GenericMethod ("*customEvent", "@hide", false, &_init_cbs_customEvent_1217_0, &_call_cbs_customEvent_1217_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_customEvent_1217_0 ()
{
  return new qt_gsi::GenericMethod ("*customEvent", "@brief Virtual method void QWidgetAction::customEvent(QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_customEvent_1217_0, &_call_cbs_customEvent_1217_0, &_set_callback_cbs_customEvent_1217_0);
}


// void QWidgetAction::deleteWidget(QWidget *widget)

static void _init_cbs_deleteWidget_1315_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("widget");
  decl->add_arg<QWidget * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_deleteWidget_1315_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QWidget *arg1 = args.read<QWidget * > ();
  ((QWidgetAction_Adaptor *)cls)->cbs_deleteWidget_1315_0 (arg1);
}

static void _set_callback_cbs_deleteWidget_1315_0 (void *cls, const gsi::Callback &cb)
{
  ((QWidgetAction_Adaptor *)cls)->cb_deleteWidget_1315_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_deleteWidget_1315_0 ()
{
  return new qt_gsi::GenericMethod ("*deleteWidget", "@hide", false, &_init_cbs_deleteWidget_1315_0, &_call_cbs_deleteWidget_1315_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_deleteWidget_1315_0 ()
{
  return new qt_gsi::GenericMethod ("*deleteWidget", "@brief Virtual method void QWidgetAction::deleteWidget(QWidget *widget)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_deleteWidget_1315_0, &_call_cbs_deleteWidget_1315_0, &_set_callback_cbs_deleteWidget_1315_0);
}


// void QWidgetAction::disconnectNotify(const char *signal)

static void _init_cbs_disconnectNotify_1731_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("signal");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_disconnectNotify_1731_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  ((QWidgetAction_Adaptor *)cls)->cbs_disconnectNotify_1731_0 (arg1);
}

static void _set_callback_cbs_disconnectNotify_1731_0 (void *cls, const gsi::Callback &cb)
{
  ((QWidgetAction_Adaptor *)cls)->cb_disconnectNotify_1731_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_disconnectNotify_1731_0 ()
{
  return new qt_gsi::GenericMethod ("*disconnectNotify", "@hide", false, &_init_cbs_disconnectNotify_1731_0, &_call_cbs_disconnectNotify_1731_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_disconnectNotify_1731_0 ()
{
  return new qt_gsi::GenericMethod ("*disconnectNotify", "@brief Virtual method void QWidgetAction::disconnectNotify(const char *signal)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_disconnectNotify_1731_0, &_call_cbs_disconnectNotify_1731_0, &_set_callback_cbs_disconnectNotify_1731_0);
}


// bool QWidgetAction::event(QEvent *)

static void _init_cbs_event_1217_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_cbs_event_1217_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QEvent *arg1 = args.read<QEvent * > ();
  ret.write<bool > ((bool)((QWidgetAction_Adaptor *)cls)->cbs_event_1217_0 (arg1));
}

static void _set_callback_cbs_event_1217_0 (void *cls, const gsi::Callback &cb)
{
  ((QWidgetAction_Adaptor *)cls)->cb_event_1217_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_event_1217_0 ()
{
  return new qt_gsi::GenericMethod ("*event", "@hide", false, &_init_cbs_event_1217_0, &_call_cbs_event_1217_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_event_1217_0 ()
{
  return new qt_gsi::GenericMethod ("*event", "@brief Virtual method bool QWidgetAction::event(QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_event_1217_0, &_call_cbs_event_1217_0, &_set_callback_cbs_event_1217_0);
}


// bool QWidgetAction::eventFilter(QObject *, QEvent *)

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
  ret.write<bool > ((bool)((QWidgetAction_Adaptor *)cls)->cbs_eventFilter_2411_0 (arg1, arg2));
}

static void _set_callback_cbs_eventFilter_2411_0 (void *cls, const gsi::Callback &cb)
{
  ((QWidgetAction_Adaptor *)cls)->cb_eventFilter_2411_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_eventFilter_2411_0 ()
{
  return new qt_gsi::GenericMethod ("*eventFilter", "@hide", false, &_init_cbs_eventFilter_2411_0, &_call_cbs_eventFilter_2411_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_eventFilter_2411_0 ()
{
  return new qt_gsi::GenericMethod ("*eventFilter", "@brief Virtual method bool QWidgetAction::eventFilter(QObject *, QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_eventFilter_2411_0, &_call_cbs_eventFilter_2411_0, &_set_callback_cbs_eventFilter_2411_0);
}


// void QWidgetAction::timerEvent(QTimerEvent *)

static void _init_cbs_timerEvent_1730_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QTimerEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_timerEvent_1730_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QTimerEvent *arg1 = args.read<QTimerEvent * > ();
  ((QWidgetAction_Adaptor *)cls)->cbs_timerEvent_1730_0 (arg1);
}

static void _set_callback_cbs_timerEvent_1730_0 (void *cls, const gsi::Callback &cb)
{
  ((QWidgetAction_Adaptor *)cls)->cb_timerEvent_1730_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_timerEvent_1730_0 ()
{
  return new qt_gsi::GenericMethod ("*timerEvent", "@hide", false, &_init_cbs_timerEvent_1730_0, &_call_cbs_timerEvent_1730_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_timerEvent_1730_0 ()
{
  return new qt_gsi::GenericMethod ("*timerEvent", "@brief Virtual method void QWidgetAction::timerEvent(QTimerEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_timerEvent_1730_0, &_call_cbs_timerEvent_1730_0, &_set_callback_cbs_timerEvent_1730_0);
}


namespace gsi
{

extern gsi::Class<QWidgetAction> decl_QWidgetAction;

gsi::Class<QWidgetAction_Adaptor> decl_QWidgetAction_Adaptor (decl_QWidgetAction, "QWidgetAction",
  gsi::Methods(_create_fp_createdWidgets_c0 ()) +
  gsi::Methods(_create_fp_receivers_c1731 ()) +
  gsi::Methods(_create_fp_sender_c0 ()) +
  gsi::Methods(_create_cbs_childEvent_1701_0 ()) +
  gsi::Methods(_create_callback_cbs_childEvent_1701_0 ()) +
  gsi::Methods(_create_cbs_createWidget_1315_0 ()) +
  gsi::Methods(_create_callback_cbs_createWidget_1315_0 ()) +
  gsi::Methods(_create_cbs_customEvent_1217_0 ()) +
  gsi::Methods(_create_callback_cbs_customEvent_1217_0 ()) +
  gsi::Methods(_create_cbs_deleteWidget_1315_0 ()) +
  gsi::Methods(_create_callback_cbs_deleteWidget_1315_0 ()) +
  gsi::Methods(_create_cbs_disconnectNotify_1731_0 ()) +
  gsi::Methods(_create_callback_cbs_disconnectNotify_1731_0 ()) +
  gsi::Methods(_create_cbs_event_1217_0 ()) +
  gsi::Methods(_create_callback_cbs_event_1217_0 ()) +
  gsi::Methods(_create_cbs_eventFilter_2411_0 ()) +
  gsi::Methods(_create_callback_cbs_eventFilter_2411_0 ()) +
  gsi::Methods(_create_cbs_timerEvent_1730_0 ()) +
  gsi::Methods(_create_callback_cbs_timerEvent_1730_0 ()) +
  gsi::Methods(_create_ctor_QWidgetAction_Adaptor_1302 ()),
  "@qt\n@brief Binding of QWidgetAction");

}

