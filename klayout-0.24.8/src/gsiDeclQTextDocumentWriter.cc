
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
*  @file gsiDeclQTextDocumentWriter.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQTextDocumentWriter_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QTextDocumentWriter

//  Constructor QTextDocumentWriter::QTextDocumentWriter()


static void _init_ctor_QTextDocumentWriter_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QTextDocumentWriter *> ();
}

static void _call_ctor_QTextDocumentWriter_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QTextDocumentWriter *> (new QTextDocumentWriter ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextDocumentWriter_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextDocumentWriter::QTextDocumentWriter()\nThis method creates an object of class QTextDocumentWriter.", &_init_ctor_QTextDocumentWriter_0, &_call_ctor_QTextDocumentWriter_0);
}

//  Constructor QTextDocumentWriter::QTextDocumentWriter(QIODevice *device, const QByteArray &format)


static void _init_ctor_QTextDocumentWriter_3648 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("device");
  decl->add_arg<QIODevice * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("format");
  decl->add_arg<const QByteArray & > (argspec_1);
  decl->set_return_new<QTextDocumentWriter *> ();
}

static void _call_ctor_QTextDocumentWriter_3648 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QIODevice *arg1 = args.read<QIODevice * > ();
  const QByteArray &arg2 = args.read<const QByteArray & > ();
  ret.write<QTextDocumentWriter *> (new QTextDocumentWriter (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextDocumentWriter_3648 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextDocumentWriter::QTextDocumentWriter(QIODevice *device, const QByteArray &format)\nThis method creates an object of class QTextDocumentWriter.", &_init_ctor_QTextDocumentWriter_3648, &_call_ctor_QTextDocumentWriter_3648);
}

//  Constructor QTextDocumentWriter::QTextDocumentWriter(const QString &fileName, const QByteArray &format)


static void _init_ctor_QTextDocumentWriter_4226 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("fileName");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("format", true, "QByteArray()");
  decl->add_arg<const QByteArray & > (argspec_1);
  decl->set_return_new<QTextDocumentWriter *> ();
}

static void _call_ctor_QTextDocumentWriter_4226 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  const QByteArray &arg2 = args ? args.read<const QByteArray & > () : (const QByteArray &)(QByteArray());
  ret.write<QTextDocumentWriter *> (new QTextDocumentWriter (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QTextDocumentWriter_4226 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QTextDocumentWriter::QTextDocumentWriter(const QString &fileName, const QByteArray &format)\nThis method creates an object of class QTextDocumentWriter.", &_init_ctor_QTextDocumentWriter_4226, &_call_ctor_QTextDocumentWriter_4226);
}

// QTextCodec *QTextDocumentWriter::codec()


static void _init_f_codec_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QTextCodec * > ();
}

static void _call_f_codec_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QTextCodec * > ((QTextCodec *)((QTextDocumentWriter *)cls)->codec ());
}

static qt_gsi::GenericMethod *_create_f_codec_c0 ()
{
  return new qt_gsi::GenericMethod (":codec", "@brief Method QTextCodec *QTextDocumentWriter::codec()\n", true, &_init_f_codec_c0, &_call_f_codec_c0);
}

// QIODevice *QTextDocumentWriter::device()


static void _init_f_device_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QIODevice * > ();
}

static void _call_f_device_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QIODevice * > ((QIODevice *)((QTextDocumentWriter *)cls)->device ());
}

static qt_gsi::GenericMethod *_create_f_device_c0 ()
{
  return new qt_gsi::GenericMethod (":device", "@brief Method QIODevice *QTextDocumentWriter::device()\n", true, &_init_f_device_c0, &_call_f_device_c0);
}

// QString QTextDocumentWriter::fileName()


static void _init_f_fileName_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QString > ();
}

static void _call_f_fileName_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QString > ((QString)((QTextDocumentWriter *)cls)->fileName ());
}

static qt_gsi::GenericMethod *_create_f_fileName_c0 ()
{
  return new qt_gsi::GenericMethod (":fileName", "@brief Method QString QTextDocumentWriter::fileName()\n", true, &_init_f_fileName_c0, &_call_f_fileName_c0);
}

// QByteArray QTextDocumentWriter::format()


static void _init_f_format_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QByteArray > ();
}

static void _call_f_format_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QByteArray > ((QByteArray)((QTextDocumentWriter *)cls)->format ());
}

static qt_gsi::GenericMethod *_create_f_format_c0 ()
{
  return new qt_gsi::GenericMethod (":format", "@brief Method QByteArray QTextDocumentWriter::format()\n", true, &_init_f_format_c0, &_call_f_format_c0);
}

// void QTextDocumentWriter::setCodec(QTextCodec *codec)


static void _init_f_setCodec_1602 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("codec");
  decl->add_arg<QTextCodec * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setCodec_1602 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QTextCodec *arg1 = args.read<QTextCodec * > ();
  ((QTextDocumentWriter *)cls)->setCodec (arg1);
}

static qt_gsi::GenericMethod *_create_f_setCodec_1602 ()
{
  return new qt_gsi::GenericMethod ("setCodec|codec=", "@brief Method void QTextDocumentWriter::setCodec(QTextCodec *codec)\n", false, &_init_f_setCodec_1602, &_call_f_setCodec_1602);
}

// void QTextDocumentWriter::setDevice(QIODevice *device)


static void _init_f_setDevice_1447 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("device");
  decl->add_arg<QIODevice * > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setDevice_1447 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QIODevice *arg1 = args.read<QIODevice * > ();
  ((QTextDocumentWriter *)cls)->setDevice (arg1);
}

static qt_gsi::GenericMethod *_create_f_setDevice_1447 ()
{
  return new qt_gsi::GenericMethod ("setDevice|device=", "@brief Method void QTextDocumentWriter::setDevice(QIODevice *device)\n", false, &_init_f_setDevice_1447, &_call_f_setDevice_1447);
}

// void QTextDocumentWriter::setFileName(const QString &fileName)


static void _init_f_setFileName_2025 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("fileName");
  decl->add_arg<const QString & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setFileName_2025 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  ((QTextDocumentWriter *)cls)->setFileName (arg1);
}

static qt_gsi::GenericMethod *_create_f_setFileName_2025 ()
{
  return new qt_gsi::GenericMethod ("setFileName|fileName=", "@brief Method void QTextDocumentWriter::setFileName(const QString &fileName)\n", false, &_init_f_setFileName_2025, &_call_f_setFileName_2025);
}

// void QTextDocumentWriter::setFormat(const QByteArray &format)


static void _init_f_setFormat_2309 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("format");
  decl->add_arg<const QByteArray & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setFormat_2309 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QByteArray &arg1 = args.read<const QByteArray & > ();
  ((QTextDocumentWriter *)cls)->setFormat (arg1);
}

static qt_gsi::GenericMethod *_create_f_setFormat_2309 ()
{
  return new qt_gsi::GenericMethod ("setFormat|format=", "@brief Method void QTextDocumentWriter::setFormat(const QByteArray &format)\n", false, &_init_f_setFormat_2309, &_call_f_setFormat_2309);
}

// bool QTextDocumentWriter::write(const QTextDocument *document)


static void _init_f_write_2650 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("document");
  decl->add_arg<const QTextDocument * > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_write_2650 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextDocument *arg1 = args.read<const QTextDocument * > ();
  ret.write<bool > ((bool)((QTextDocumentWriter *)cls)->write (arg1));
}

static qt_gsi::GenericMethod *_create_f_write_2650 ()
{
  return new qt_gsi::GenericMethod ("write", "@brief Method bool QTextDocumentWriter::write(const QTextDocument *document)\n", false, &_init_f_write_2650, &_call_f_write_2650);
}

// bool QTextDocumentWriter::write(const QTextDocumentFragment &fragment)


static void _init_f_write_3466 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("fragment");
  decl->add_arg<const QTextDocumentFragment & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_write_3466 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QTextDocumentFragment &arg1 = args.read<const QTextDocumentFragment & > ();
  ret.write<bool > ((bool)((QTextDocumentWriter *)cls)->write (arg1));
}

static qt_gsi::GenericMethod *_create_f_write_3466 ()
{
  return new qt_gsi::GenericMethod ("write", "@brief Method bool QTextDocumentWriter::write(const QTextDocumentFragment &fragment)\n", false, &_init_f_write_3466, &_call_f_write_3466);
}

// static QList<QByteArray> QTextDocumentWriter::supportedDocumentFormats()


static void _init_f_supportedDocumentFormats_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QList<QByteArray> >::target_type > ();
}

static void _call_f_supportedDocumentFormats_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QList<QByteArray> >::target_type > ((qt_gsi::Converter<QList<QByteArray> >::target_type)qt_gsi::CppToQtAdaptor<QList<QByteArray> >(QTextDocumentWriter::supportedDocumentFormats ()));
}

static qt_gsi::GenericStaticMethod *_create_f_supportedDocumentFormats_0 ()
{
  return new qt_gsi::GenericStaticMethod ("supportedDocumentFormats", "@brief Static method QList<QByteArray> QTextDocumentWriter::supportedDocumentFormats()\nThis method is static and can be called without an instance.", &_init_f_supportedDocumentFormats_0, &_call_f_supportedDocumentFormats_0);
}


namespace gsi
{
gsi::Class<QTextDocumentWriter> decl_QTextDocumentWriter ("QTextDocumentWriter",
  gsi::Methods(_create_ctor_QTextDocumentWriter_0 ()) +
  gsi::Methods(_create_ctor_QTextDocumentWriter_3648 ()) +
  gsi::Methods(_create_ctor_QTextDocumentWriter_4226 ()) +
  gsi::Methods(_create_f_codec_c0 ()) +
  gsi::Methods(_create_f_device_c0 ()) +
  gsi::Methods(_create_f_fileName_c0 ()) +
  gsi::Methods(_create_f_format_c0 ()) +
  gsi::Methods(_create_f_setCodec_1602 ()) +
  gsi::Methods(_create_f_setDevice_1447 ()) +
  gsi::Methods(_create_f_setFileName_2025 ()) +
  gsi::Methods(_create_f_setFormat_2309 ()) +
  gsi::Methods(_create_f_write_2650 ()) +
  gsi::Methods(_create_f_write_3466 ()) +
  gsi::Methods(_create_f_supportedDocumentFormats_0 ()),
  "@qt\n@brief Binding of QTextDocumentWriter");

}
