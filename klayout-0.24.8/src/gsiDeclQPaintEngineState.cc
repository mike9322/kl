
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
*  @file gsiDeclQPaintEngineState.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQPaintEngineState_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QPaintEngineState

//  Constructor QPaintEngineState::QPaintEngineState()


static void _init_ctor_QPaintEngineState_0 (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return_new<QPaintEngineState *> ();
}

static void _call_ctor_QPaintEngineState_0 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QPaintEngineState *> (new QPaintEngineState ());
}

static qt_gsi::GenericStaticMethod *_create_ctor_QPaintEngineState_0 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QPaintEngineState::QPaintEngineState()\nThis method creates an object of class QPaintEngineState.", &_init_ctor_QPaintEngineState_0, &_call_ctor_QPaintEngineState_0);
}

// QBrush QPaintEngineState::backgroundBrush()


static void _init_f_backgroundBrush_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QBrush > ();
}

static void _call_f_backgroundBrush_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QBrush > ((QBrush)((QPaintEngineState *)cls)->backgroundBrush ());
}

static qt_gsi::GenericMethod *_create_f_backgroundBrush_c0 ()
{
  return new qt_gsi::GenericMethod ("backgroundBrush", "@brief Method QBrush QPaintEngineState::backgroundBrush()\n", true, &_init_f_backgroundBrush_c0, &_call_f_backgroundBrush_c0);
}

// Qt::BGMode QPaintEngineState::backgroundMode()


static void _init_f_backgroundMode_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<Qt::BGMode>::target_type > ();
}

static void _call_f_backgroundMode_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<Qt::BGMode>::target_type > ((qt_gsi::Converter<Qt::BGMode>::target_type)qt_gsi::CppToQtAdaptor<Qt::BGMode>(((QPaintEngineState *)cls)->backgroundMode ()));
}

static qt_gsi::GenericMethod *_create_f_backgroundMode_c0 ()
{
  return new qt_gsi::GenericMethod ("backgroundMode", "@brief Method Qt::BGMode QPaintEngineState::backgroundMode()\n", true, &_init_f_backgroundMode_c0, &_call_f_backgroundMode_c0);
}

// QBrush QPaintEngineState::brush()


static void _init_f_brush_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QBrush > ();
}

static void _call_f_brush_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QBrush > ((QBrush)((QPaintEngineState *)cls)->brush ());
}

static qt_gsi::GenericMethod *_create_f_brush_c0 ()
{
  return new qt_gsi::GenericMethod ("brush", "@brief Method QBrush QPaintEngineState::brush()\n", true, &_init_f_brush_c0, &_call_f_brush_c0);
}

// bool QPaintEngineState::brushNeedsResolving()


static void _init_f_brushNeedsResolving_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_brushNeedsResolving_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QPaintEngineState *)cls)->brushNeedsResolving ());
}

static qt_gsi::GenericMethod *_create_f_brushNeedsResolving_c0 ()
{
  return new qt_gsi::GenericMethod ("brushNeedsResolving", "@brief Method bool QPaintEngineState::brushNeedsResolving()\n", true, &_init_f_brushNeedsResolving_c0, &_call_f_brushNeedsResolving_c0);
}

// QPointF QPaintEngineState::brushOrigin()


static void _init_f_brushOrigin_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QPointF > ();
}

static void _call_f_brushOrigin_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QPointF > ((QPointF)((QPaintEngineState *)cls)->brushOrigin ());
}

static qt_gsi::GenericMethod *_create_f_brushOrigin_c0 ()
{
  return new qt_gsi::GenericMethod ("brushOrigin", "@brief Method QPointF QPaintEngineState::brushOrigin()\n", true, &_init_f_brushOrigin_c0, &_call_f_brushOrigin_c0);
}

// Qt::ClipOperation QPaintEngineState::clipOperation()


static void _init_f_clipOperation_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<Qt::ClipOperation>::target_type > ();
}

static void _call_f_clipOperation_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<Qt::ClipOperation>::target_type > ((qt_gsi::Converter<Qt::ClipOperation>::target_type)qt_gsi::CppToQtAdaptor<Qt::ClipOperation>(((QPaintEngineState *)cls)->clipOperation ()));
}

static qt_gsi::GenericMethod *_create_f_clipOperation_c0 ()
{
  return new qt_gsi::GenericMethod ("clipOperation", "@brief Method Qt::ClipOperation QPaintEngineState::clipOperation()\n", true, &_init_f_clipOperation_c0, &_call_f_clipOperation_c0);
}

// QPainterPath QPaintEngineState::clipPath()


static void _init_f_clipPath_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QPainterPath > ();
}

static void _call_f_clipPath_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QPainterPath > ((QPainterPath)((QPaintEngineState *)cls)->clipPath ());
}

static qt_gsi::GenericMethod *_create_f_clipPath_c0 ()
{
  return new qt_gsi::GenericMethod ("clipPath", "@brief Method QPainterPath QPaintEngineState::clipPath()\n", true, &_init_f_clipPath_c0, &_call_f_clipPath_c0);
}

// QRegion QPaintEngineState::clipRegion()


static void _init_f_clipRegion_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QRegion > ();
}

static void _call_f_clipRegion_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QRegion > ((QRegion)((QPaintEngineState *)cls)->clipRegion ());
}

static qt_gsi::GenericMethod *_create_f_clipRegion_c0 ()
{
  return new qt_gsi::GenericMethod ("clipRegion", "@brief Method QRegion QPaintEngineState::clipRegion()\n", true, &_init_f_clipRegion_c0, &_call_f_clipRegion_c0);
}

// QPainter::CompositionMode QPaintEngineState::compositionMode()


static void _init_f_compositionMode_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QPainter::CompositionMode>::target_type > ();
}

static void _call_f_compositionMode_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QPainter::CompositionMode>::target_type > ((qt_gsi::Converter<QPainter::CompositionMode>::target_type)qt_gsi::CppToQtAdaptor<QPainter::CompositionMode>(((QPaintEngineState *)cls)->compositionMode ()));
}

static qt_gsi::GenericMethod *_create_f_compositionMode_c0 ()
{
  return new qt_gsi::GenericMethod ("compositionMode", "@brief Method QPainter::CompositionMode QPaintEngineState::compositionMode()\n", true, &_init_f_compositionMode_c0, &_call_f_compositionMode_c0);
}

// QFont QPaintEngineState::font()


static void _init_f_font_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QFont > ();
}

static void _call_f_font_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QFont > ((QFont)((QPaintEngineState *)cls)->font ());
}

static qt_gsi::GenericMethod *_create_f_font_c0 ()
{
  return new qt_gsi::GenericMethod ("font", "@brief Method QFont QPaintEngineState::font()\n", true, &_init_f_font_c0, &_call_f_font_c0);
}

// bool QPaintEngineState::isClipEnabled()


static void _init_f_isClipEnabled_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_isClipEnabled_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QPaintEngineState *)cls)->isClipEnabled ());
}

static qt_gsi::GenericMethod *_create_f_isClipEnabled_c0 ()
{
  return new qt_gsi::GenericMethod ("isClipEnabled?", "@brief Method bool QPaintEngineState::isClipEnabled()\n", true, &_init_f_isClipEnabled_c0, &_call_f_isClipEnabled_c0);
}

// QMatrix QPaintEngineState::matrix()


static void _init_f_matrix_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QMatrix > ();
}

static void _call_f_matrix_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QMatrix > ((QMatrix)((QPaintEngineState *)cls)->matrix ());
}

static qt_gsi::GenericMethod *_create_f_matrix_c0 ()
{
  return new qt_gsi::GenericMethod ("matrix", "@brief Method QMatrix QPaintEngineState::matrix()\n", true, &_init_f_matrix_c0, &_call_f_matrix_c0);
}

// double QPaintEngineState::opacity()


static void _init_f_opacity_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<double > ();
}

static void _call_f_opacity_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<double > ((double)((QPaintEngineState *)cls)->opacity ());
}

static qt_gsi::GenericMethod *_create_f_opacity_c0 ()
{
  return new qt_gsi::GenericMethod ("opacity", "@brief Method double QPaintEngineState::opacity()\n", true, &_init_f_opacity_c0, &_call_f_opacity_c0);
}

// QPainter *QPaintEngineState::painter()


static void _init_f_painter_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QPainter * > ();
}

static void _call_f_painter_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QPainter * > ((QPainter *)((QPaintEngineState *)cls)->painter ());
}

static qt_gsi::GenericMethod *_create_f_painter_c0 ()
{
  return new qt_gsi::GenericMethod ("painter", "@brief Method QPainter *QPaintEngineState::painter()\n", true, &_init_f_painter_c0, &_call_f_painter_c0);
}

// QPen QPaintEngineState::pen()


static void _init_f_pen_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QPen > ();
}

static void _call_f_pen_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QPen > ((QPen)((QPaintEngineState *)cls)->pen ());
}

static qt_gsi::GenericMethod *_create_f_pen_c0 ()
{
  return new qt_gsi::GenericMethod ("pen", "@brief Method QPen QPaintEngineState::pen()\n", true, &_init_f_pen_c0, &_call_f_pen_c0);
}

// bool QPaintEngineState::penNeedsResolving()


static void _init_f_penNeedsResolving_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<bool > ();
}

static void _call_f_penNeedsResolving_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<bool > ((bool)((QPaintEngineState *)cls)->penNeedsResolving ());
}

static qt_gsi::GenericMethod *_create_f_penNeedsResolving_c0 ()
{
  return new qt_gsi::GenericMethod ("penNeedsResolving", "@brief Method bool QPaintEngineState::penNeedsResolving()\n", true, &_init_f_penNeedsResolving_c0, &_call_f_penNeedsResolving_c0);
}

// QFlags<QPainter::RenderHint> QPaintEngineState::renderHints()


static void _init_f_renderHints_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QFlags<QPainter::RenderHint> >::target_type > ();
}

static void _call_f_renderHints_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QFlags<QPainter::RenderHint> >::target_type > ((qt_gsi::Converter<QFlags<QPainter::RenderHint> >::target_type)qt_gsi::CppToQtAdaptor<QFlags<QPainter::RenderHint> >(((QPaintEngineState *)cls)->renderHints ()));
}

static qt_gsi::GenericMethod *_create_f_renderHints_c0 ()
{
  return new qt_gsi::GenericMethod ("renderHints", "@brief Method QFlags<QPainter::RenderHint> QPaintEngineState::renderHints()\n", true, &_init_f_renderHints_c0, &_call_f_renderHints_c0);
}

// QFlags<QPaintEngine::DirtyFlag> QPaintEngineState::state()


static void _init_f_state_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<qt_gsi::Converter<QFlags<QPaintEngine::DirtyFlag> >::target_type > ();
}

static void _call_f_state_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<qt_gsi::Converter<QFlags<QPaintEngine::DirtyFlag> >::target_type > ((qt_gsi::Converter<QFlags<QPaintEngine::DirtyFlag> >::target_type)qt_gsi::CppToQtAdaptor<QFlags<QPaintEngine::DirtyFlag> >(((QPaintEngineState *)cls)->state ()));
}

static qt_gsi::GenericMethod *_create_f_state_c0 ()
{
  return new qt_gsi::GenericMethod ("state", "@brief Method QFlags<QPaintEngine::DirtyFlag> QPaintEngineState::state()\n", true, &_init_f_state_c0, &_call_f_state_c0);
}

// QTransform QPaintEngineState::transform()


static void _init_f_transform_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QTransform > ();
}

static void _call_f_transform_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QTransform > ((QTransform)((QPaintEngineState *)cls)->transform ());
}

static qt_gsi::GenericMethod *_create_f_transform_c0 ()
{
  return new qt_gsi::GenericMethod ("transform", "@brief Method QTransform QPaintEngineState::transform()\n", true, &_init_f_transform_c0, &_call_f_transform_c0);
}


namespace gsi
{
gsi::Class<QPaintEngineState> decl_QPaintEngineState ("QPaintEngineState",
  gsi::Methods(_create_ctor_QPaintEngineState_0 ()) +
  gsi::Methods(_create_f_backgroundBrush_c0 ()) +
  gsi::Methods(_create_f_backgroundMode_c0 ()) +
  gsi::Methods(_create_f_brush_c0 ()) +
  gsi::Methods(_create_f_brushNeedsResolving_c0 ()) +
  gsi::Methods(_create_f_brushOrigin_c0 ()) +
  gsi::Methods(_create_f_clipOperation_c0 ()) +
  gsi::Methods(_create_f_clipPath_c0 ()) +
  gsi::Methods(_create_f_clipRegion_c0 ()) +
  gsi::Methods(_create_f_compositionMode_c0 ()) +
  gsi::Methods(_create_f_font_c0 ()) +
  gsi::Methods(_create_f_isClipEnabled_c0 ()) +
  gsi::Methods(_create_f_matrix_c0 ()) +
  gsi::Methods(_create_f_opacity_c0 ()) +
  gsi::Methods(_create_f_painter_c0 ()) +
  gsi::Methods(_create_f_pen_c0 ()) +
  gsi::Methods(_create_f_penNeedsResolving_c0 ()) +
  gsi::Methods(_create_f_renderHints_c0 ()) +
  gsi::Methods(_create_f_state_c0 ()) +
  gsi::Methods(_create_f_transform_c0 ()),
  "@qt\n@brief Binding of QPaintEngineState");

}

