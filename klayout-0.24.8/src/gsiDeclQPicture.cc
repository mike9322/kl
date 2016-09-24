
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
*  @file gsiDeclQPicture.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQPicture_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QPicture

// QRect QPicture::boundingRect()


static void _init_f_boundingRect_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QRect > ();
}

static void _call_f_boundingRect_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QRect > ((QRect)((QPicture *)cls)->boundingRect ());
}

static qt_gsi::GenericMethod *_create_f_boundingRect_c0 ()
{
  return new qt_gsi::GenericMethod (":boundingRect", "@brief Method QRect QPicture::boundingRect()\n", true, &_init_f_boundingRect_c0, &_call_f_boundingRect_c0);
}

// const char *QPicture::data()


static void _init_f_data_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<const char * > ();
}

static void _call_f_data_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const char * > ((const char *)((QPicture *)cls)->data ());
}

static qt_gsi::GenericMethod *_create_f_data_c0 ()
{
  return new qt_gsi::GenericMethod ("data", "@brief Method const char *QPicture::data()\n", true, &_init_f_data_c0, &_call_f_data_c0);
}

// void QPicture::detach()


static void _init_f_detach_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<void > ();
}

static void _call_f_detach_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ((QPicture *)cls)->detach ();
}

static qt_gsi::GenericMethod *_create_f_detach_0 ()
{
  return new qt_gsi::GenericMethod ("detach", "@brief Method void QPicture::detach()\n", false, &_init_f_detach_0, &_call_f_detach_0);
}

// bool QPicture::isDetached()


static void _init_f_isDetached_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isDetached_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QPicture *)cls)->isDetached ());
}

static qt_gsi::GenericMethod *_create_f_isDetached_c0 ()
{
  return new qt_gsi::GenericMethod ("isDetached?", "@brief Method bool QPicture::isDetached()\n", true, &_init_f_isDetached_c0, &_call_f_isDetached_c0);
}

// bool QPicture::isNull()


static void _init_f_isNull_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isNull_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QPicture *)cls)->isNull ());
}

static qt_gsi::GenericMethod *_create_f_isNull_c0 ()
{
  return new qt_gsi::GenericMethod ("isNull?", "@brief Method bool QPicture::isNull()\n", true, &_init_f_isNull_c0, &_call_f_isNull_c0);
}

// bool QPicture::load(QIODevice *dev, const char *format)


static void _init_f_load_3070 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("dev");
  decl->add_arg<QIODevice * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("format", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<bool > ();
}

static void _call_f_load_3070 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QIODevice *arg1 = args.read<QIODevice * > ();
  const char *arg2 = args ? args.read<const char * > () : (const char *)(0);
  ret.write<bool > ((bool)((QPicture *)cls)->load (arg1, arg2));
}

static qt_gsi::GenericMethod *_create_f_load_3070 ()
{
  return new qt_gsi::GenericMethod ("load", "@brief Method bool QPicture::load(QIODevice *dev, const char *format)\n", false, &_init_f_load_3070, &_call_f_load_3070);
}

// bool QPicture::load(const QString &fileName, const char *format)


static void _init_f_load_3648 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("fileName");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("format", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<bool > ();
}

static void _call_f_load_3648 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  const char *arg2 = args ? args.read<const char * > () : (const char *)(0);
  ret.write<bool > ((bool)((QPicture *)cls)->load (arg1, arg2));
}

static qt_gsi::GenericMethod *_create_f_load_3648 ()
{
  return new qt_gsi::GenericMethod ("load", "@brief Method bool QPicture::load(const QString &fileName, const char *format)\n", false, &_init_f_load_3648, &_call_f_load_3648);
}

// QPicture &QPicture::operator=(const QPicture &p)


static void _init_f_operator_eq__2126 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("p");
  decl->add_arg<const QPicture & > (argspec_0);
  decl->set_return<QPicture & > ();
}

static void _call_f_operator_eq__2126 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QPicture &arg1 = args.read<const QPicture & > ();
  ret.write<QPicture & > ((QPicture &)((QPicture *)cls)->operator= (arg1));
}

static qt_gsi::GenericMethod *_create_f_operator_eq__2126 ()
{
  return new qt_gsi::GenericMethod ("assign", "@brief Method QPicture &QPicture::operator=(const QPicture &p)\n", false, &_init_f_operator_eq__2126, &_call_f_operator_eq__2126);
}

// QPaintEngine *QPicture::paintEngine()


static void _init_f_paintEngine_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QPaintEngine * > ();
}

static void _call_f_paintEngine_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QPaintEngine * > ((QPaintEngine *)((QPicture *)cls)->paintEngine ());
}

static qt_gsi::GenericMethod *_create_f_paintEngine_c0 ()
{
  return new qt_gsi::GenericMethod ("paintEngine", "@brief Method QPaintEngine *QPicture::paintEngine()\nThis is a reimplementation of QPaintDevice::paintEngine", true, &_init_f_paintEngine_c0, &_call_f_paintEngine_c0);
}

// bool QPicture::play(QPainter *p)


static void _init_f_play_1426 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("p");
  decl->add_arg<QPainter * > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_play_1426 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QPainter *arg1 = args.read<QPainter * > ();
  ret.write<bool > ((bool)((QPicture *)cls)->play (arg1));
}

static qt_gsi::GenericMethod *_create_f_play_1426 ()
{
  return new qt_gsi::GenericMethod ("play", "@brief Method bool QPicture::play(QPainter *p)\n", false, &_init_f_play_1426, &_call_f_play_1426);
}

// bool QPicture::save(QIODevice *dev, const char *format)


static void _init_f_save_3070 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("dev");
  decl->add_arg<QIODevice * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("format", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<bool > ();
}

static void _call_f_save_3070 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QIODevice *arg1 = args.read<QIODevice * > ();
  const char *arg2 = args ? args.read<const char * > () : (const char *)(0);
  ret.write<bool > ((bool)((QPicture *)cls)->save (arg1, arg2));
}

static qt_gsi::GenericMethod *_create_f_save_3070 ()
{
  return new qt_gsi::GenericMethod ("save", "@brief Method bool QPicture::save(QIODevice *dev, const char *format)\n", false, &_init_f_save_3070, &_call_f_save_3070);
}

// bool QPicture::save(const QString &fileName, const char *format)


static void _init_f_save_3648 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("fileName");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("format", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<bool > ();
}

static void _call_f_save_3648 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  const char *arg2 = args ? args.read<const char * > () : (const char *)(0);
  ret.write<bool > ((bool)((QPicture *)cls)->save (arg1, arg2));
}

static qt_gsi::GenericMethod *_create_f_save_3648 ()
{
  return new qt_gsi::GenericMethod ("save", "@brief Method bool QPicture::save(const QString &fileName, const char *format)\n", false, &_init_f_save_3648, &_call_f_save_3648);
}

// void QPicture::setBoundingRect(const QRect &r)


static void _init_f_setBoundingRect_1792 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("r");
  decl->add_arg<const QRect & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setBoundingRect_1792 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QRect &arg1 = args.read<const QRect & > ();
  ((QPicture *)cls)->setBoundingRect (arg1);
}

static qt_gsi::GenericMethod *_create_f_setBoundingRect_1792 ()
{
  return new qt_gsi::GenericMethod ("setBoundingRect|boundingRect=", "@brief Method void QPicture::setBoundingRect(const QRect &r)\n", false, &_init_f_setBoundingRect_1792, &_call_f_setBoundingRect_1792);
}

// void QPicture::setData(const char *data, unsigned int size)


static void _init_f_setData_3395 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("data");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("size");
  decl->add_arg<unsigned int > (argspec_1);
  decl->set_return<void > ();
}

static void _call_f_setData_3395 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  unsigned int arg2 = args.read<unsigned int > ();
  ((QPicture *)cls)->setData (arg1, arg2);
}

static qt_gsi::GenericMethod *_create_f_setData_3395 ()
{
  return new qt_gsi::GenericMethod ("setData", "@brief Method void QPicture::setData(const char *data, unsigned int size)\n", false, &_init_f_setData_3395, &_call_f_setData_3395);
}

// unsigned int QPicture::size()


static void _init_f_size_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<unsigned int > ();
}

static void _call_f_size_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<unsigned int > ((unsigned int)((QPicture *)cls)->size ());
}

static qt_gsi::GenericMethod *_create_f_size_c0 ()
{
  return new qt_gsi::GenericMethod ("size", "@brief Method unsigned int QPicture::size()\n", true, &_init_f_size_c0, &_call_f_size_c0);
}

// static QStringList QPicture::inputFormatList()


static void _init_f_inputFormatList_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QStringList>::target_type > ();
}

static void _call_f_inputFormatList_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QStringList>::target_type > ((qt_gsi::Converter<QStringList>::target_type)qt_gsi::CppToQtAdaptor<QStringList>(QPicture::inputFormatList ()));
}

static qt_gsi::GenericStaticMethod *_create_f_inputFormatList_0 ()
{
  return new qt_gsi::GenericStaticMethod ("inputFormatList", "@brief Static method QStringList QPicture::inputFormatList()\nThis method is static and can be called without an instance.", &_init_f_inputFormatList_0, &_call_f_inputFormatList_0);
}

// static QList<QByteArray> QPicture::inputFormats()


static void _init_f_inputFormats_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QByteArray> >::target_type > ();
}

static void _call_f_inputFormats_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QByteArray> >::target_type > ((qt_gsi::Converter<QList<QByteArray> >::target_type)qt_gsi::CppToQtAdaptor<QList<QByteArray> >(QPicture::inputFormats ()));
}

static qt_gsi::GenericStaticMethod *_create_f_inputFormats_0 ()
{
  return new qt_gsi::GenericStaticMethod ("inputFormats", "@brief Static method QList<QByteArray> QPicture::inputFormats()\nThis method is static and can be called without an instance.", &_init_f_inputFormats_0, &_call_f_inputFormats_0);
}

// static QStringList QPicture::outputFormatList()


static void _init_f_outputFormatList_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QStringList>::target_type > ();
}

static void _call_f_outputFormatList_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QStringList>::target_type > ((qt_gsi::Converter<QStringList>::target_type)qt_gsi::CppToQtAdaptor<QStringList>(QPicture::outputFormatList ()));
}

static qt_gsi::GenericStaticMethod *_create_f_outputFormatList_0 ()
{
  return new qt_gsi::GenericStaticMethod ("outputFormatList", "@brief Static method QStringList QPicture::outputFormatList()\nThis method is static and can be called without an instance.", &_init_f_outputFormatList_0, &_call_f_outputFormatList_0);
}

// static QList<QByteArray> QPicture::outputFormats()


static void _init_f_outputFormats_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QByteArray> >::target_type > ();
}

static void _call_f_outputFormats_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QByteArray> >::target_type > ((qt_gsi::Converter<QList<QByteArray> >::target_type)qt_gsi::CppToQtAdaptor<QList<QByteArray> >(QPicture::outputFormats ()));
}

static qt_gsi::GenericStaticMethod *_create_f_outputFormats_0 ()
{
  return new qt_gsi::GenericStaticMethod ("outputFormats", "@brief Static method QList<QByteArray> QPicture::outputFormats()\nThis method is static and can be called without an instance.", &_init_f_outputFormats_0, &_call_f_outputFormats_0);
}

// static const char *QPicture::pictureFormat(const QString &fileName)


static void _init_f_pictureFormat_2025 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("fileName");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<const char * > ();
}

static void _call_f_pictureFormat_2025 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ret.write<const char * > ((const char *)QPicture::pictureFormat (arg1));
}

static qt_gsi::GenericStaticMethod *_create_f_pictureFormat_2025 ()
{
  return new qt_gsi::GenericStaticMethod ("pictureFormat", "@brief Static method const char *QPicture::pictureFormat(const QString &fileName)\nThis method is static and can be called without an instance.", &_init_f_pictureFormat_2025, &_call_f_pictureFormat_2025);
}

namespace gsi
{
extern gsi::Class<QPaintDevice> decl_QPaintDevice;

gsi::Class<QPicture> decl_QPicture (decl_QPaintDevice, "QPicture_Native",
  gsi::Methods(_create_f_boundingRect_c0 ()) +
  gsi::Methods(_create_f_data_c0 ()) +
  gsi::Methods(_create_f_detach_0 ()) +
  gsi::Methods(_create_f_isDetached_c0 ()) +
  gsi::Methods(_create_f_isNull_c0 ()) +
  gsi::Methods(_create_f_load_3070 ()) +
  gsi::Methods(_create_f_load_3648 ()) +
  gsi::Methods(_create_f_operator_eq__2126 ()) +
  gsi::Methods(_create_f_paintEngine_c0 ()) +
  gsi::Methods(_create_f_play_1426 ()) +
  gsi::Methods(_create_f_save_3070 ()) +
  gsi::Methods(_create_f_save_3648 ()) +
  gsi::Methods(_create_f_setBoundingRect_1792 ()) +
  gsi::Methods(_create_f_setData_3395 ()) +
  gsi::Methods(_create_f_size_c0 ()) +
  gsi::Methods(_create_f_inputFormatList_0 ()) +
  gsi::Methods(_create_f_inputFormats_0 ()) +
  gsi::Methods(_create_f_outputFormatList_0 ()) +
  gsi::Methods(_create_f_outputFormats_0 ()) +
  gsi::Methods(_create_f_pictureFormat_2025 ()),
  "@hide\n@alias QPicture");
}


class QPicture_Adaptor : public QPicture, public qt_gsi::QtObjectBase
{
public:

  virtual ~QPicture_Adaptor();

  //  [adaptor ctor] QPicture::QPicture(int formatVersion)
  QPicture_Adaptor() : QPicture()
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QPicture::QPicture(int formatVersion)
  QPicture_Adaptor(int formatVersion) : QPicture(formatVersion)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor ctor] QPicture::QPicture(const QPicture &)
  QPicture_Adaptor(const QPicture &arg1) : QPicture(arg1)
  {
    qt_gsi::QtObjectBase::init (this);
  }

  //  [adaptor impl] QPaintEngine *QPicture::paintEngine()
  QPaintEngine * cbs_paintEngine_c0_0() const
  {
    return QPicture::paintEngine();
  }

  virtual QPaintEngine * paintEngine() const
  {
    if (cb_paintEngine_c0_0.can_issue()) {
      return cb_paintEngine_c0_0.issue<QPicture_Adaptor, QPaintEngine *>(&QPicture_Adaptor::cbs_paintEngine_c0_0);
    } else {
      return QPicture::paintEngine();
    }
  }

  //  [adaptor impl] void QPicture::setData(const char *data, unsigned int size)
  void cbs_setData_3395_0(const char *data, unsigned int size)
  {
    QPicture::setData(data, size);
  }

  virtual void setData(const char *data, unsigned int size)
  {
    if (cb_setData_3395_0.can_issue()) {
      cb_setData_3395_0.issue<QPicture_Adaptor, const char *, unsigned int>(&QPicture_Adaptor::cbs_setData_3395_0, data, size);
    } else {
      QPicture::setData(data, size);
    }
  }

  //  [adaptor impl] int QPicture::metric(QPaintDevice::PaintDeviceMetric m)
  int cbs_metric_c3445_0(const qt_gsi::Converter<QPaintDevice::PaintDeviceMetric>::target_type & m) const
  {
    return QPicture::metric(qt_gsi::QtToCppAdaptor<QPaintDevice::PaintDeviceMetric>(m).cref());
  }

  virtual int metric(QPaintDevice::PaintDeviceMetric m) const
  {
    if (cb_metric_c3445_0.can_issue()) {
      return cb_metric_c3445_0.issue<QPicture_Adaptor, int, const qt_gsi::Converter<QPaintDevice::PaintDeviceMetric>::target_type &>(&QPicture_Adaptor::cbs_metric_c3445_0, qt_gsi::CppToQtAdaptor<QPaintDevice::PaintDeviceMetric>(m));
    } else {
      return QPicture::metric(m);
    }
  }

  gsi::Callback cb_paintEngine_c0_0;
  gsi::Callback cb_setData_3395_0;
  gsi::Callback cb_metric_c3445_0;
};

QPicture_Adaptor::~QPicture_Adaptor() { }

//  Constructor QPicture::QPicture(int formatVersion) (adaptor class)

static void _init_ctor_QPicture_Adaptor_767 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("formatVersion", true, "-1");
  decl->add_arg<int > (argspec_0);
  decl->set_return_new<QPicture_Adaptor *> ();
}

static void _call_ctor_QPicture_Adaptor_767 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args ? args.read<int > () : (int)(-1);
  ret.write<QPicture_Adaptor *> (new QPicture_Adaptor (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QPicture_Adaptor_767 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QPicture::QPicture(int formatVersion)\nThis method creates an object of class QPicture.", &_init_ctor_QPicture_Adaptor_767, &_call_ctor_QPicture_Adaptor_767);
}

//  Constructor QPicture::QPicture(const QPicture &) (adaptor class)

static void _init_ctor_QPicture_Adaptor_2126 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<const QPicture & > (argspec_0);
  decl->set_return_new<QPicture_Adaptor *> ();
}

static void _call_ctor_QPicture_Adaptor_2126 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QPicture &arg1 = args.read<const QPicture & > ();
  ret.write<QPicture_Adaptor *> (new QPicture_Adaptor (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QPicture_Adaptor_2126 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QPicture::QPicture(const QPicture &)\nThis method creates an object of class QPicture.", &_init_ctor_QPicture_Adaptor_2126, &_call_ctor_QPicture_Adaptor_2126);
}

// QPaintEngine *QPicture::paintEngine()

static void _init_cbs_paintEngine_c0_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QPaintEngine * > ();
}

static void _call_cbs_paintEngine_c0_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QPaintEngine * > ((QPaintEngine *)((QPicture_Adaptor *)cls)->cbs_paintEngine_c0_0 ());
}

static void _set_callback_cbs_paintEngine_c0_0 (void *cls, const gsi::Callback &cb)
{
  ((QPicture_Adaptor *)cls)->cb_paintEngine_c0_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_paintEngine_c0_0 ()
{
  return new qt_gsi::GenericMethod ("paintEngine", "@hide", true, &_init_cbs_paintEngine_c0_0, &_call_cbs_paintEngine_c0_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_paintEngine_c0_0 ()
{
  return new qt_gsi::GenericMethod ("paintEngine", "@brief Virtual method QPaintEngine *QPicture::paintEngine()\nThis method can be reimplemented in a derived class.", true, &_init_cbs_paintEngine_c0_0, &_call_cbs_paintEngine_c0_0, &_set_callback_cbs_paintEngine_c0_0);
}


// void QPicture::setData(const char *data, unsigned int size)

static void _init_cbs_setData_3395_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("data");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("size");
  decl->add_arg<unsigned int > (argspec_1);
  decl->set_return<void > ();
}

static void _call_cbs_setData_3395_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  unsigned int arg2 = args.read<unsigned int > ();
  ((QPicture_Adaptor *)cls)->cbs_setData_3395_0 (arg1, arg2);
}

static void _set_callback_cbs_setData_3395_0 (void *cls, const gsi::Callback &cb)
{
  ((QPicture_Adaptor *)cls)->cb_setData_3395_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_setData_3395_0 ()
{
  return new qt_gsi::GenericMethod ("setData", "@hide", false, &_init_cbs_setData_3395_0, &_call_cbs_setData_3395_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_setData_3395_0 ()
{
  return new qt_gsi::GenericMethod ("setData", "@brief Virtual method void QPicture::setData(const char *data, unsigned int size)\nThis method can be reimplemented in a derived class.", false, &_init_cbs_setData_3395_0, &_call_cbs_setData_3395_0, &_set_callback_cbs_setData_3395_0);
}


// int QPicture::metric(QPaintDevice::PaintDeviceMetric m)

static void _init_cbs_metric_c3445_0 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("m");
  decl->add_arg<const qt_gsi::Converter<QPaintDevice::PaintDeviceMetric>::target_type & > (argspec_0);
  decl->set_return<int > ();
}

static void _call_cbs_metric_c3445_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QPaintDevice::PaintDeviceMetric>::target_type & arg1 = args.read<const qt_gsi::Converter<QPaintDevice::PaintDeviceMetric>::target_type & > ();
  ret.write<int > ((int)((QPicture_Adaptor *)cls)->cbs_metric_c3445_0 (arg1));
}

static void _set_callback_cbs_metric_c3445_0 (void *cls, const gsi::Callback &cb)
{
  ((QPicture_Adaptor *)cls)->cb_metric_c3445_0 = cb;
}

static qt_gsi::GenericMethod *_create_cbs_metric_c3445_0 ()
{
  return new qt_gsi::GenericMethod ("*metric", "@hide", true, &_init_cbs_metric_c3445_0, &_call_cbs_metric_c3445_0);
}

static qt_gsi::GenericMethod *_create_callback_cbs_metric_c3445_0 ()
{
  return new qt_gsi::GenericMethod ("*metric", "@brief Virtual method int QPicture::metric(QPaintDevice::PaintDeviceMetric m)\nThis method can be reimplemented in a derived class.", true, &_init_cbs_metric_c3445_0, &_call_cbs_metric_c3445_0, &_set_callback_cbs_metric_c3445_0);
}


namespace gsi
{

extern gsi::Class<QPicture> decl_QPicture;

gsi::Class<QPicture_Adaptor> decl_QPicture_Adaptor (decl_QPicture, "QPicture",
  gsi::Methods(_create_cbs_paintEngine_c0_0 ()) +
  gsi::Methods(_create_callback_cbs_paintEngine_c0_0 ()) +
  gsi::Methods(_create_cbs_setData_3395_0 ()) +
  gsi::Methods(_create_callback_cbs_setData_3395_0 ()) +
  gsi::Methods(_create_cbs_metric_c3445_0 ()) +
  gsi::Methods(_create_callback_cbs_metric_c3445_0 ()) +
  gsi::Methods(_create_ctor_QPicture_Adaptor_767 ()) +
  gsi::Methods(_create_ctor_QPicture_Adaptor_2126 ()),
  "@qt\n@brief Binding of QPicture");

}
