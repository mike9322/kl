
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
*  @file gsiDeclQFileSystemWatcher.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtCore.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQFileSystemWatcher_EventAdaptor.h"
#include "gsiDeclQFileSystemWatcher_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QFileSystemWatcher

//  get static meta object

static void _init_smo (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<const QMetaObject &> ();
}

static void _call_smo (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const QMetaObject &> (QFileSystemWatcher::staticMetaObject);
}

static qt_gsi::GenericStaticMethod *_create_smo ()
{
  return new qt_gsi::GenericStaticMethod ("staticMetaObject", "@brief Obtains the static MetaObject for this class.", &_init_smo, &_call_smo);
}

// void QFileSystemWatcher::addPath(const QString &file)


static void _init_f_addPath_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("file");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_addPath_2025 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ((QFileSystemWatcher *)cls)->addPath (arg1);
}

static qt_gsi::GenericMethod *_create_f_addPath_2025 ()
{
  return new qt_gsi::GenericMethod ("addPath", "@brief Method void QFileSystemWatcher::addPath(const QString &file)\n", false, &_init_f_addPath_2025, &_call_f_addPath_2025);
}

// void QFileSystemWatcher::addPaths(const QStringList &files)


static void _init_f_addPaths_2437 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("files");
  decl->add_arg<const qt_gsi::Converter<QStringList>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_addPaths_2437 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QStringList>::target_type & arg1 = args.read<const qt_gsi::Converter<QStringList>::target_type & > ();
  ((QFileSystemWatcher *)cls)->addPaths (qt_gsi::QtToCppAdaptor<QStringList>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_addPaths_2437 ()
{
  return new qt_gsi::GenericMethod ("addPaths", "@brief Method void QFileSystemWatcher::addPaths(const QStringList &files)\n", false, &_init_f_addPaths_2437, &_call_f_addPaths_2437);
}

// QStringList QFileSystemWatcher::directories()


static void _init_f_directories_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QStringList>::target_type > ();
}

static void _call_f_directories_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QStringList>::target_type > ((qt_gsi::Converter<QStringList>::target_type)qt_gsi::CppToQtAdaptor<QStringList>(((QFileSystemWatcher *)cls)->directories ()));
}

static qt_gsi::GenericMethod *_create_f_directories_c0 ()
{
  return new qt_gsi::GenericMethod ("directories", "@brief Method QStringList QFileSystemWatcher::directories()\n", true, &_init_f_directories_c0, &_call_f_directories_c0);
}

// QStringList QFileSystemWatcher::files()


static void _init_f_files_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QStringList>::target_type > ();
}

static void _call_f_files_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QStringList>::target_type > ((qt_gsi::Converter<QStringList>::target_type)qt_gsi::CppToQtAdaptor<QStringList>(((QFileSystemWatcher *)cls)->files ()));
}

static qt_gsi::GenericMethod *_create_f_files_c0 ()
{
  return new qt_gsi::GenericMethod ("files", "@brief Method QStringList QFileSystemWatcher::files()\n", true, &_init_f_files_c0, &_call_f_files_c0);
}

// void QFileSystemWatcher::removePath(const QString &file)


static void _init_f_removePath_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("file");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_removePath_2025 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ((QFileSystemWatcher *)cls)->removePath (arg1);
}

static qt_gsi::GenericMethod *_create_f_removePath_2025 ()
{
  return new qt_gsi::GenericMethod ("removePath", "@brief Method void QFileSystemWatcher::removePath(const QString &file)\n", false, &_init_f_removePath_2025, &_call_f_removePath_2025);
}

// void QFileSystemWatcher::removePaths(const QStringList &files)


static void _init_f_removePaths_2437 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("files");
  decl->add_arg<const qt_gsi::Converter<QStringList>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_removePaths_2437 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QStringList>::target_type & arg1 = args.read<const qt_gsi::Converter<QStringList>::target_type & > ();
  ((QFileSystemWatcher *)cls)->removePaths (qt_gsi::QtToCppAdaptor<QStringList>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_removePaths_2437 ()
{
  return new qt_gsi::GenericMethod ("removePaths", "@brief Method void QFileSystemWatcher::removePaths(const QStringList &files)\n", false, &_init_f_removePaths_2437, &_call_f_removePaths_2437);
}

// static QString QFileSystemWatcher::tr(const char *s, const char *c)


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
  ret.write<QString > ((QString)QFileSystemWatcher::tr (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_f_tr_3354 ()
{
  return new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QFileSystemWatcher::tr(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_tr_3354, &_call_f_tr_3354);
}

// static QString QFileSystemWatcher::tr(const char *s, const char *c, int n)


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
  ret.write<QString > ((QString)QFileSystemWatcher::tr (arg1, arg2, arg3));
}

static qt_gsi::GenericStaticMethod *_create_f_tr_4013 ()
{
  return new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QFileSystemWatcher::tr(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_tr_4013, &_call_f_tr_4013);
}

// static QString QFileSystemWatcher::trUtf8(const char *s, const char *c)


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
  ret.write<QString > ((QString)QFileSystemWatcher::trUtf8 (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_f_trUtf8_3354 ()
{
  return new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QFileSystemWatcher::trUtf8(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_3354, &_call_f_trUtf8_3354);
}

// static QString QFileSystemWatcher::trUtf8(const char *s, const char *c, int n)


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
  ret.write<QString > ((QString)QFileSystemWatcher::trUtf8 (arg1, arg2, arg3));
}

static qt_gsi::GenericStaticMethod *_create_f_trUtf8_4013 ()
{
  return new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QFileSystemWatcher::trUtf8(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_4013, &_call_f_trUtf8_4013);
}

static qt_gsi::QObjectConnector<QFileSystemWatcher, QFileSystemWatcher_EventAdaptor> ea_QFileSystemWatcher;

namespace gsi
{
extern gsi::Class<QObject> decl_QObject;

gsi::Class<QFileSystemWatcher> decl_QFileSystemWatcher (ea_QFileSystemWatcher, decl_QObject, "QFileSystemWatcher_Native",
  gsi::Methods(_create_smo ()) +
  gsi::Methods(_create_f_addPath_2025 ()) +
  gsi::Methods(_create_f_addPaths_2437 ()) +
  gsi::Methods(_create_f_directories_c0 ()) +
  gsi::Methods(_create_f_files_c0 ()) +
  gsi::Methods(_create_f_removePath_2025 ()) +
  gsi::Methods(_create_f_removePaths_2437 ()) +
  qt_gsi::qt_signal<QFileSystemWatcher, QFileSystemWatcher_EventAdaptor, QObject *> ("destroyed", &QFileSystemWatcher_EventAdaptor::destroyed_e_1302, gsi::arg("arg1"), "@brief Signal declaration for QFileSystemWatcher::destroyed(QObject *)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QFileSystemWatcher, QFileSystemWatcher_EventAdaptor, const QString &> ("directoryChanged", &QFileSystemWatcher_EventAdaptor::directoryChanged_e_2025, gsi::arg("path"), "@brief Signal declaration for QFileSystemWatcher::directoryChanged(const QString &path)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QFileSystemWatcher, QFileSystemWatcher_EventAdaptor, const QString &> ("fileChanged", &QFileSystemWatcher_EventAdaptor::fileChanged_e_2025, gsi::arg("path"), "@brief Signal declaration for QFileSystemWatcher::fileChanged(const QString &path)\nYou can bind a procedure to this signal.") +
  gsi::Methods(_create_f_tr_3354 ()) +
  gsi::Methods(_create_f_tr_4013 ()) +
  gsi::Methods(_create_f_trUtf8_3354 ()) +
  gsi::Methods(_create_f_trUtf8_4013 ()),
  "@hide\n@alias QFileSystemWatcher");
}


class QFileSystemWatcher_Adaptor : public QFileSystemWatcher, public qt_gsi::QtObjectBase
{
public:

  virtual ~QFileSystemWatcher_Adaptor();

  //  [adaptor ctor] QFileSystemWatcher::QFileSystemWatcher(QObject *parent)
  QFileSystemWatcher_Adaptor() : QFileSystemWatcher()
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QFileSystemWatcher::QFileSystemWatcher(QObject *parent)
  QFileSystemWatcher_Adaptor(QObject *parent) : QFileSystemWatcher(parent)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QFileSystemWatcher::QFileSystemWatcher(const QStringList &paths, QObject *parent)
  QFileSystemWatcher_Adaptor(const QStringList &paths) : QFileSystemWatcher(paths)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QFileSystemWatcher::QFileSystemWatcher(const QStringList &paths, QObject *parent)
  QFileSystemWatcher_Adaptor(const QStringList &paths, QObject *parent) : QFileSystemWatcher(paths, parent)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  int QFileSystemWatcher::receivers(const char *signal)
  int fp_QFileSystemWatcher_receivers_c1731 (const char *signal) const {
    return QFileSystemWatcher::receivers(signal);
  }

  //  QObject *QFileSystemWatcher::sender()
  QObject * fp_QFileSystemWatcher_sender_c0 () const {
    return QFileSystemWatcher::sender();
  }

  //  [adaptor impl] bool QFileSystemWatcher::event(QEvent *)
  bool cbs_event_1217_0(QEvent *arg1)
  {
    return QFileSystemWatcher::event(arg1);
  }

  virtual bool event(QEvent *arg1)
  {
    if (cb_event_1217_0.can_issue()) {
      return cb_event_1217_0.issue<QFileSystemWatcher_Adaptor, bool, QEvent *>(&QFileSystemWatcher_Adaptor::cbs_event_1217_0, arg1);
    } else {
      return QFileSystemWatcher::event(arg1);
    }
  }

  //  [adaptor impl] bool QFileSystemWatcher::eventFilter(QObject *, QEvent *)
  bool cbs_eventFilter_2411_0(QObject *arg1, QEvent *arg2)
  {
    return QFileSystemWatcher::eventFilter(arg1, arg2);
  }

  virtual bool eventFilter(QObject *arg1, QEvent *arg2)
  {
    if (cb_eventFilter_2411_0.can_issue()) {
      return cb_eventFilter_2411_0.issue<QFileSystemWatcher_Adaptor, bool, QObject *, QEvent *>(&QFileSystemWatcher_Adaptor::cbs_eventFilter_2411_0, arg1, arg2);
    } else {
      return QFileSystemWatcher::eventFilter(arg1, arg2);
    }
  }

  //  [adaptor impl] void QFileSystemWatcher::childEvent(QChildEvent *)
  void cbs_childEvent_1701_0(QChildEvent *arg1)
  {
    QFileSystemWatcher::childEvent(arg1);
  }

  virtual void childEvent(QChildEvent *arg1)
  {
    if (cb_childEvent_1701_0.can_issue()) {
      cb_childEvent_1701_0.issue<QFileSystemWatcher_Adaptor, QChildEvent *>(&QFileSystemWatcher_Adaptor::cbs_childEvent_1701_0, arg1);
    } else {
      QFileSystemWatcher::childEvent(arg1);
    }
  }

  //  [adaptor impl] void QFileSystemWatcher::customEvent(QEvent *)
  void cbs_customEvent_1217_0(QEvent *arg1)
  {
    QFileSystemWatcher::customEvent(arg1);
  }

  virtual void customEvent(QEvent *arg1)
  {
    if (cb_customEvent_1217_0.can_issue()) {
      cb_customEvent_1217_0.issue<QFileSystemWatcher_Adaptor, QEvent *>(&QFileSystemWatcher_Adaptor::cbs_customEvent_1217_0, arg1);
    } else {
      QFileSystemWatcher::customEvent(arg1);
    }
  }

  //  [adaptor impl] void QFileSystemWatcher::disconnectNotify(const char *signal)
  void cbs_disconnectNotify_1731_0(const char *signal)
  {
    QFileSystemWatcher::disconnectNotify(signal);
  }

  virtual void disconnectNotify(const char *signal)
  {
    if (cb_disconnectNotify_1731_0.can_issue()) {
      cb_disconnectNotify_1731_0.issue<QFileSystemWatcher_Adaptor, const char *>(&QFileSystemWatcher_Adaptor::cbs_disconnectNotify_1731_0, signal);
    } else {
      QFileSystemWatcher::disconnectNotify(signal);
    }
  }

  //  [adaptor impl] void QFileSystemWatcher::timerEvent(QTimerEvent *)
  void cbs_timerEvent_1730_0(QTimerEvent *arg1)
  {
    QFileSystemWatcher::timerEvent(arg1);
  }

  virtual void timerEvent(QTimerEvent *arg1)
  {
    if (cb_timerEvent_1730_0.can_issue()) {
      cb_timerEvent_1730_0.issue<QFileSystemWatcher_Adaptor, QTimerEvent *>(&QFileSystemWatcher_Adaptor::cbs_timerEvent_1730_0, arg1);
    } else {
      QFileSystemWatcher::timerEvent(arg1);
    }
  }

  gsi::Callback cb_event_1217_0;
  gsi::Callback cb_eventFilter_2411_0;
  gsi::Callback cb_childEvent_1701_0;
  gsi::Callback cb_customEvent_1217_0;
  gsi::Callback cb_disconnectNotify_1731_0;
  gsi::Callback cb_timerEvent_1730_0;
};

QFileSystemWatcher_Adaptor::~QFileSystemWatcher_Adaptor() { }

//  Constructor QFileSystemWatcher::QFileSystemWatcher(QObject *parent) (adaptor class)

static void _init_ctor_QFileSystemWatcher_Adaptor_1302 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent", true, "0");
  decl->add_arg<QObject * > (argspec_0);
  decl->set_return_new<QFileSystemWatcher_Adaptor *> ();
}

static void _call_ctor_QFileSystemWatcher_Adaptor_1302 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QObject *arg1 = args ? args.read<QObject * > () : (QObject *)(0);
  ret.write<QFileSystemWatcher_Adaptor *> (new QFileSystemWatcher_Adaptor (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QFileSystemWatcher_Adaptor_1302 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QFileSystemWatcher::QFileSystemWatcher(QObject *parent)\nThis method creates an object of class QFileSystemWatcher.", &_init_ctor_QFileSystemWatcher_Adaptor_1302, &_call_ctor_QFileSystemWatcher_Adaptor_1302);
}

//  Constructor QFileSystemWatcher::QFileSystemWatcher(const QStringList &paths, QObject *parent) (adaptor class)

static void _init_ctor_QFileSystemWatcher_Adaptor_3631 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("paths");
  decl->add_arg<const qt_gsi::Converter<QStringList>::target_type & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("parent", true, "0");
  decl->add_arg<QObject * > (argspec_1);
  decl->set_return_new<QFileSystemWatcher_Adaptor *> ();
}

static void _call_ctor_QFileSystemWatcher_Adaptor_3631 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QStringList>::target_type & arg1 = args.read<const qt_gsi::Converter<QStringList>::target_type & > ();
  QObject *arg2 = args ? args.read<QObject * > () : (QObject *)(0);
  ret.write<QFileSystemWatcher_Adaptor *> (new QFileSystemWatcher_Adaptor (qt_gsi::QtToCppAdaptor<QStringList>(arg1).cref(), arg2));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QFileSystemWatcher_Adaptor_3631 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QFileSystemWatcher::QFileSystemWatcher(const QStringList &paths, QObject *parent)\nThis method creates an object of class QFileSystemWatcher.", &_init_ctor_QFileSystemWatcher_Adaptor_3631, &_call_ctor_QFileSystemWatcher_Adaptor_3631);
}

// int QFileSystemWatcher::receivers(const char *signal)

static void _init_fp_receivers_c1731 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("signal");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<int > ();
}

static void _call_fp_receivers_c1731 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  ret.write<int > ((int)((QFileSystemWatcher_Adaptor *)cls)->fp_QFileSystemWatcher_receivers_c1731 (arg1));
}

static qt_gsi::GenericMethod*_create_fp_receivers_c1731 ()
{
  return new qt_gsi::GenericMethod("*receivers", "@brief Method int QFileSystemWatcher::receivers(const char *signal)\nThis method is protected and can only be called from inside a derived class.", true, &_init_fp_receivers_c1731, &_call_fp_receivers_c1731);
}


// QObject *QFileSystemWatcher::sender()

static void _init_fp_sender_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QObject * > ();
}

static void _call_fp_sender_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QObject * > ((QObject *)((QFileSystemWatcher_Adaptor *)cls)->fp_QFileSystemWatcher_sender_c0 ());
}

static qt_gsi::GenericMethod*_create_fp_sender_c0 ()
{
  return new qt_gsi::GenericMethod("*sender", "@brief Method QObject *QFileSystemWatcher::sender()\nThis method is protected and can only be called from inside a derived class.", true, &_init_fp_sender_c0, &_call_fp_sender_c0);
}


// bool QFileSystemWatcher::event(QEvent *)

static void _init_cbs_event_1217_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_cbs_event_1217_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QEvent *arg1 = args.read<QEvent * > ();
  ret.write<bool > ((bool)((QFileSystemWatcher_Adaptor *)cls)->cbs_event_1217_0 (arg1));
}

static void _set_callback_cbs_event_1217_0 (void *cls, const gsi::Callback &cb)
{
  ((QFileSystemWatcher_Adaptor *)cls)->cb_event_1217_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_event_1217_0 ()
{
  return new qt_gsi::GenericMethod ("event", "@hide", false, &_init_cbs_event_1217_0, &_call_cbs_event_1217_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_event_1217_0 ()
{
  return new qt_gsi::GenericMethod ("event", "@brief Virtual method bool QFileSystemWatcher::event(QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_event_1217_0, &_call_cbs_event_1217_0, &_set_callback_cbs_event_1217_0);
}


// bool QFileSystemWatcher::eventFilter(QObject *, QEvent *)

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
  ret.write<bool > ((bool)((QFileSystemWatcher_Adaptor *)cls)->cbs_eventFilter_2411_0 (arg1, arg2));
}

static void _set_callback_cbs_eventFilter_2411_0 (void *cls, const gsi::Callback &cb)
{
  ((QFileSystemWatcher_Adaptor *)cls)->cb_eventFilter_2411_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_eventFilter_2411_0 ()
{
  return new qt_gsi::GenericMethod ("eventFilter", "@hide", false, &_init_cbs_eventFilter_2411_0, &_call_cbs_eventFilter_2411_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_eventFilter_2411_0 ()
{
  return new qt_gsi::GenericMethod ("eventFilter", "@brief Virtual method bool QFileSystemWatcher::eventFilter(QObject *, QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_eventFilter_2411_0, &_call_cbs_eventFilter_2411_0, &_set_callback_cbs_eventFilter_2411_0);
}


// void QFileSystemWatcher::childEvent(QChildEvent *)

static void _init_cbs_childEvent_1701_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QChildEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_childEvent_1701_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QChildEvent *arg1 = args.read<QChildEvent * > ();
  ((QFileSystemWatcher_Adaptor *)cls)->cbs_childEvent_1701_0 (arg1);
}

static void _set_callback_cbs_childEvent_1701_0 (void *cls, const gsi::Callback &cb)
{
  ((QFileSystemWatcher_Adaptor *)cls)->cb_childEvent_1701_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_childEvent_1701_0 ()
{
  return new qt_gsi::GenericMethod ("*childEvent", "@hide", false, &_init_cbs_childEvent_1701_0, &_call_cbs_childEvent_1701_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_childEvent_1701_0 ()
{
  return new qt_gsi::GenericMethod ("*childEvent", "@brief Virtual method void QFileSystemWatcher::childEvent(QChildEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_childEvent_1701_0, &_call_cbs_childEvent_1701_0, &_set_callback_cbs_childEvent_1701_0);
}


// void QFileSystemWatcher::customEvent(QEvent *)

static void _init_cbs_customEvent_1217_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_customEvent_1217_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QEvent *arg1 = args.read<QEvent * > ();
  ((QFileSystemWatcher_Adaptor *)cls)->cbs_customEvent_1217_0 (arg1);
}

static void _set_callback_cbs_customEvent_1217_0 (void *cls, const gsi::Callback &cb)
{
  ((QFileSystemWatcher_Adaptor *)cls)->cb_customEvent_1217_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_customEvent_1217_0 ()
{
  return new qt_gsi::GenericMethod ("*customEvent", "@hide", false, &_init_cbs_customEvent_1217_0, &_call_cbs_customEvent_1217_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_customEvent_1217_0 ()
{
  return new qt_gsi::GenericMethod ("*customEvent", "@brief Virtual method void QFileSystemWatcher::customEvent(QEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_customEvent_1217_0, &_call_cbs_customEvent_1217_0, &_set_callback_cbs_customEvent_1217_0);
}


// void QFileSystemWatcher::disconnectNotify(const char *signal)

static void _init_cbs_disconnectNotify_1731_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("signal");
  decl->add_arg<const char * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_disconnectNotify_1731_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  ((QFileSystemWatcher_Adaptor *)cls)->cbs_disconnectNotify_1731_0 (arg1);
}

static void _set_callback_cbs_disconnectNotify_1731_0 (void *cls, const gsi::Callback &cb)
{
  ((QFileSystemWatcher_Adaptor *)cls)->cb_disconnectNotify_1731_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_disconnectNotify_1731_0 ()
{
  return new qt_gsi::GenericMethod ("*disconnectNotify", "@hide", false, &_init_cbs_disconnectNotify_1731_0, &_call_cbs_disconnectNotify_1731_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_disconnectNotify_1731_0 ()
{
  return new qt_gsi::GenericMethod ("*disconnectNotify", "@brief Virtual method void QFileSystemWatcher::disconnectNotify(const char *signal)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_disconnectNotify_1731_0, &_call_cbs_disconnectNotify_1731_0, &_set_callback_cbs_disconnectNotify_1731_0);
}


// void QFileSystemWatcher::timerEvent(QTimerEvent *)

static void _init_cbs_timerEvent_1730_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<QTimerEvent * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_cbs_timerEvent_1730_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QTimerEvent *arg1 = args.read<QTimerEvent * > ();
  ((QFileSystemWatcher_Adaptor *)cls)->cbs_timerEvent_1730_0 (arg1);
}

static void _set_callback_cbs_timerEvent_1730_0 (void *cls, const gsi::Callback &cb)
{
  ((QFileSystemWatcher_Adaptor *)cls)->cb_timerEvent_1730_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_timerEvent_1730_0 ()
{
  return new qt_gsi::GenericMethod ("*timerEvent", "@hide", false, &_init_cbs_timerEvent_1730_0, &_call_cbs_timerEvent_1730_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_timerEvent_1730_0 ()
{
  return new qt_gsi::GenericMethod ("*timerEvent", "@brief Virtual method void QFileSystemWatcher::timerEvent(QTimerEvent *)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_timerEvent_1730_0, &_call_cbs_timerEvent_1730_0, &_set_callback_cbs_timerEvent_1730_0);
}


namespace gsi
{

extern gsi::Class<QFileSystemWatcher> decl_QFileSystemWatcher;

gsi::Class<QFileSystemWatcher_Adaptor> decl_QFileSystemWatcher_Adaptor (decl_QFileSystemWatcher, "QFileSystemWatcher",
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
  gsi::Methods(_create_ctor_QFileSystemWatcher_Adaptor_1302 ()) +
  gsi::Methods(_create_ctor_QFileSystemWatcher_Adaptor_3631 ()),
  "@qt\n@brief Binding of QFileSystemWatcher");

}
