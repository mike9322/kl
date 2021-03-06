
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
*  @file generated/gsiDeclQGraphicsScene_EventAdaptor.cc
*  @brief Event adaptor implementations for QGraphicsScene
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQGraphicsScene_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QGraphicsScene_EventAdaptor

QGraphicsScene_EventAdaptor::QGraphicsScene_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(changed(const QList<QRectF> &)), this, SLOT(changed(const QList<QRectF> &)));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(sceneRectChanged(const QRectF &)), this, SLOT(sceneRectChanged(const QRectF &)));
  connect (host, SIGNAL(selectionChanged()), this, SLOT(selectionChanged()));
}

//  Event QGraphicsScene::changed(const QList<QRectF> &region)
void QGraphicsScene_EventAdaptor::changed(const QList<QRectF> &region) {
BEGIN_PROTECTED
  changed_e_2477(qt_gsi::CppToQtAdaptor<QList<QRectF> >(region));
END_PROTECTED
}

//  Event QGraphicsScene::destroyed(QObject *arg1)
void QGraphicsScene_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QGraphicsScene::sceneRectChanged(const QRectF &rect)
void QGraphicsScene_EventAdaptor::sceneRectChanged(const QRectF &rect) {
BEGIN_PROTECTED
  sceneRectChanged_e_1862(rect);
END_PROTECTED
}

//  Event QGraphicsScene::selectionChanged()
void QGraphicsScene_EventAdaptor::selectionChanged() {
BEGIN_PROTECTED
  selectionChanged_e_0();
END_PROTECTED
}
