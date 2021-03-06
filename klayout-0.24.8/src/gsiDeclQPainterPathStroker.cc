
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
*  @file gsiDeclQPainterPathStroker.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQPainterPathStroker_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QPainterPathStroker

//  Constructor QPainterPathStroker::QPainterPathStroker()


static void _init_ctor_QPainterPathStroker_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QPainterPathStroker *> ();
}

static void _call_ctor_QPainterPathStroker_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QPainterPathStroker *> (new QPainterPathStroker ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QPainterPathStroker_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QPainterPathStroker::QPainterPathStroker()\nThis method creates an object of class QPainterPathStroker.", &_init_ctor_QPainterPathStroker_0, &_call_ctor_QPainterPathStroker_0);
}

// Qt::PenCapStyle QPainterPathStroker::capStyle()


static void _init_f_capStyle_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<Qt::PenCapStyle>::target_type > ();
}

static void _call_f_capStyle_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<Qt::PenCapStyle>::target_type > ((qt_gsi::Converter<Qt::PenCapStyle>::target_type)qt_gsi::CppToQtAdaptor<Qt::PenCapStyle>(((QPainterPathStroker *)cls)->capStyle ()));
}

static qt_gsi::GenericMethod *_create_f_capStyle_c0 ()
{
  return new qt_gsi::GenericMethod (":capStyle", "@brief Method Qt::PenCapStyle QPainterPathStroker::capStyle()\n", true, &_init_f_capStyle_c0, &_call_f_capStyle_c0);
}

// QPainterPath QPainterPathStroker::createStroke(const QPainterPath &path)


static void _init_f_createStroke_c2514 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("path");
  decl->add_arg<const QPainterPath & > (argspec_0);
  decl->set_return<QPainterPath > ();
}

static void _call_f_createStroke_c2514 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QPainterPath &arg1 = args.read<const QPainterPath & > ();
  ret.write<QPainterPath > ((QPainterPath)((QPainterPathStroker *)cls)->createStroke (arg1));
}

static qt_gsi::GenericMethod *_create_f_createStroke_c2514 ()
{
  return new qt_gsi::GenericMethod ("createStroke", "@brief Method QPainterPath QPainterPathStroker::createStroke(const QPainterPath &path)\n", true, &_init_f_createStroke_c2514, &_call_f_createStroke_c2514);
}

// double QPainterPathStroker::curveThreshold()


static void _init_f_curveThreshold_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<double > ();
}

static void _call_f_curveThreshold_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<double > ((double)((QPainterPathStroker *)cls)->curveThreshold ());
}

static qt_gsi::GenericMethod *_create_f_curveThreshold_c0 ()
{
  return new qt_gsi::GenericMethod (":curveThreshold", "@brief Method double QPainterPathStroker::curveThreshold()\n", true, &_init_f_curveThreshold_c0, &_call_f_curveThreshold_c0);
}

// double QPainterPathStroker::dashOffset()


static void _init_f_dashOffset_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<double > ();
}

static void _call_f_dashOffset_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<double > ((double)((QPainterPathStroker *)cls)->dashOffset ());
}

static qt_gsi::GenericMethod *_create_f_dashOffset_c0 ()
{
  return new qt_gsi::GenericMethod (":dashOffset", "@brief Method double QPainterPathStroker::dashOffset()\n", true, &_init_f_dashOffset_c0, &_call_f_dashOffset_c0);
}

// QVector<double> QPainterPathStroker::dashPattern()


static void _init_f_dashPattern_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QVector<double> >::target_type > ();
}

static void _call_f_dashPattern_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QVector<double> >::target_type > ((qt_gsi::Converter<QVector<double> >::target_type)qt_gsi::CppToQtAdaptor<QVector<double> >(((QPainterPathStroker *)cls)->dashPattern ()));
}

static qt_gsi::GenericMethod *_create_f_dashPattern_c0 ()
{
  return new qt_gsi::GenericMethod ("dashPattern", "@brief Method QVector<double> QPainterPathStroker::dashPattern()\n", true, &_init_f_dashPattern_c0, &_call_f_dashPattern_c0);
}

// Qt::PenJoinStyle QPainterPathStroker::joinStyle()


static void _init_f_joinStyle_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<Qt::PenJoinStyle>::target_type > ();
}

static void _call_f_joinStyle_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<Qt::PenJoinStyle>::target_type > ((qt_gsi::Converter<Qt::PenJoinStyle>::target_type)qt_gsi::CppToQtAdaptor<Qt::PenJoinStyle>(((QPainterPathStroker *)cls)->joinStyle ()));
}

static qt_gsi::GenericMethod *_create_f_joinStyle_c0 ()
{
  return new qt_gsi::GenericMethod (":joinStyle", "@brief Method Qt::PenJoinStyle QPainterPathStroker::joinStyle()\n", true, &_init_f_joinStyle_c0, &_call_f_joinStyle_c0);
}

// double QPainterPathStroker::miterLimit()


static void _init_f_miterLimit_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<double > ();
}

static void _call_f_miterLimit_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<double > ((double)((QPainterPathStroker *)cls)->miterLimit ());
}

static qt_gsi::GenericMethod *_create_f_miterLimit_c0 ()
{
  return new qt_gsi::GenericMethod (":miterLimit", "@brief Method double QPainterPathStroker::miterLimit()\n", true, &_init_f_miterLimit_c0, &_call_f_miterLimit_c0);
}

// void QPainterPathStroker::setCapStyle(Qt::PenCapStyle style)


static void _init_f_setCapStyle_1845 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("style");
  decl->add_arg<const qt_gsi::Converter<Qt::PenCapStyle>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setCapStyle_1845 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<Qt::PenCapStyle>::target_type & arg1 = args.read<const qt_gsi::Converter<Qt::PenCapStyle>::target_type & > ();
  ((QPainterPathStroker *)cls)->setCapStyle (qt_gsi::QtToCppAdaptor<Qt::PenCapStyle>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setCapStyle_1845 ()
{
  return new qt_gsi::GenericMethod ("setCapStyle|capStyle=", "@brief Method void QPainterPathStroker::setCapStyle(Qt::PenCapStyle style)\n", false, &_init_f_setCapStyle_1845, &_call_f_setCapStyle_1845);
}

// void QPainterPathStroker::setCurveThreshold(double threshold)


static void _init_f_setCurveThreshold_1071 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("threshold");
  decl->add_arg<double > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setCurveThreshold_1071 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  double arg1 = args.read<double > ();
  ((QPainterPathStroker *)cls)->setCurveThreshold (arg1);
}

static qt_gsi::GenericMethod *_create_f_setCurveThreshold_1071 ()
{
  return new qt_gsi::GenericMethod ("setCurveThreshold|curveThreshold=", "@brief Method void QPainterPathStroker::setCurveThreshold(double threshold)\n", false, &_init_f_setCurveThreshold_1071, &_call_f_setCurveThreshold_1071);
}

// void QPainterPathStroker::setDashOffset(double offset)


static void _init_f_setDashOffset_1071 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("offset");
  decl->add_arg<double > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setDashOffset_1071 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  double arg1 = args.read<double > ();
  ((QPainterPathStroker *)cls)->setDashOffset (arg1);
}

static qt_gsi::GenericMethod *_create_f_setDashOffset_1071 ()
{
  return new qt_gsi::GenericMethod ("setDashOffset|dashOffset=", "@brief Method void QPainterPathStroker::setDashOffset(double offset)\n", false, &_init_f_setDashOffset_1071, &_call_f_setDashOffset_1071);
}

// void QPainterPathStroker::setDashPattern(Qt::PenStyle)


static void _init_f_setDashPattern_1569 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("arg1");
  decl->add_arg<const qt_gsi::Converter<Qt::PenStyle>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setDashPattern_1569 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<Qt::PenStyle>::target_type & arg1 = args.read<const qt_gsi::Converter<Qt::PenStyle>::target_type & > ();
  ((QPainterPathStroker *)cls)->setDashPattern (qt_gsi::QtToCppAdaptor<Qt::PenStyle>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setDashPattern_1569 ()
{
  return new qt_gsi::GenericMethod ("setDashPattern", "@brief Method void QPainterPathStroker::setDashPattern(Qt::PenStyle)\n", false, &_init_f_setDashPattern_1569, &_call_f_setDashPattern_1569);
}

// void QPainterPathStroker::setDashPattern(const QVector<double> &dashPattern)


static void _init_f_setDashPattern_2778 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("dashPattern");
  decl->add_arg<const qt_gsi::Converter<QVector<double> >::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setDashPattern_2778 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<QVector<double> >::target_type & arg1 = args.read<const qt_gsi::Converter<QVector<double> >::target_type & > ();
  ((QPainterPathStroker *)cls)->setDashPattern (qt_gsi::QtToCppAdaptor<QVector<double> >(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setDashPattern_2778 ()
{
  return new qt_gsi::GenericMethod ("setDashPattern", "@brief Method void QPainterPathStroker::setDashPattern(const QVector<double> &dashPattern)\n", false, &_init_f_setDashPattern_2778, &_call_f_setDashPattern_2778);
}

// void QPainterPathStroker::setJoinStyle(Qt::PenJoinStyle style)


static void _init_f_setJoinStyle_1969 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("style");
  decl->add_arg<const qt_gsi::Converter<Qt::PenJoinStyle>::target_type & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setJoinStyle_1969 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const qt_gsi::Converter<Qt::PenJoinStyle>::target_type & arg1 = args.read<const qt_gsi::Converter<Qt::PenJoinStyle>::target_type & > ();
  ((QPainterPathStroker *)cls)->setJoinStyle (qt_gsi::QtToCppAdaptor<Qt::PenJoinStyle>(arg1).cref());
}

static qt_gsi::GenericMethod *_create_f_setJoinStyle_1969 ()
{
  return new qt_gsi::GenericMethod ("setJoinStyle|joinStyle=", "@brief Method void QPainterPathStroker::setJoinStyle(Qt::PenJoinStyle style)\n", false, &_init_f_setJoinStyle_1969, &_call_f_setJoinStyle_1969);
}

// void QPainterPathStroker::setMiterLimit(double length)


static void _init_f_setMiterLimit_1071 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("length");
  decl->add_arg<double > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setMiterLimit_1071 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  double arg1 = args.read<double > ();
  ((QPainterPathStroker *)cls)->setMiterLimit (arg1);
}

static qt_gsi::GenericMethod *_create_f_setMiterLimit_1071 ()
{
  return new qt_gsi::GenericMethod ("setMiterLimit|miterLimit=", "@brief Method void QPainterPathStroker::setMiterLimit(double length)\n", false, &_init_f_setMiterLimit_1071, &_call_f_setMiterLimit_1071);
}

// void QPainterPathStroker::setWidth(double width)


static void _init_f_setWidth_1071 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("width");
  decl->add_arg<double > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setWidth_1071 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  double arg1 = args.read<double > ();
  ((QPainterPathStroker *)cls)->setWidth (arg1);
}

static qt_gsi::GenericMethod *_create_f_setWidth_1071 ()
{
  return new qt_gsi::GenericMethod ("setWidth|width=", "@brief Method void QPainterPathStroker::setWidth(double width)\n", false, &_init_f_setWidth_1071, &_call_f_setWidth_1071);
}

// double QPainterPathStroker::width()


static void _init_f_width_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<double > ();
}

static void _call_f_width_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<double > ((double)((QPainterPathStroker *)cls)->width ());
}

static qt_gsi::GenericMethod *_create_f_width_c0 ()
{
  return new qt_gsi::GenericMethod (":width", "@brief Method double QPainterPathStroker::width()\n", true, &_init_f_width_c0, &_call_f_width_c0);
}


namespace gsi
{
gsi::Class<QPainterPathStroker> decl_QPainterPathStroker ("QPainterPathStroker",
  gsi::Methods(_create_ctor_QPainterPathStroker_0 ()) +
  gsi::Methods(_create_f_capStyle_c0 ()) +
  gsi::Methods(_create_f_createStroke_c2514 ()) +
  gsi::Methods(_create_f_curveThreshold_c0 ()) +
  gsi::Methods(_create_f_dashOffset_c0 ()) +
  gsi::Methods(_create_f_dashPattern_c0 ()) +
  gsi::Methods(_create_f_joinStyle_c0 ()) +
  gsi::Methods(_create_f_miterLimit_c0 ()) +
  gsi::Methods(_create_f_setCapStyle_1845 ()) +
  gsi::Methods(_create_f_setCurveThreshold_1071 ()) +
  gsi::Methods(_create_f_setDashOffset_1071 ()) +
  gsi::Methods(_create_f_setDashPattern_1569 ()) +
  gsi::Methods(_create_f_setDashPattern_2778 ()) +
  gsi::Methods(_create_f_setJoinStyle_1969 ()) +
  gsi::Methods(_create_f_setMiterLimit_1071 ()) +
  gsi::Methods(_create_f_setWidth_1071 ()) +
  gsi::Methods(_create_f_width_c0 ()),
  "@qt\n@brief Binding of QPainterPathStroker");

}

