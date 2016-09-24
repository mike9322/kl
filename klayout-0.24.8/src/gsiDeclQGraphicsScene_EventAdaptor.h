
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
*  @file generated/gsiDeclQGraphicsScene_EventAdaptor.h
*  @brief Event adaptor implementations for QGraphicsScene
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQGraphicsScene_EventAdaptor
#define _HDR_gsiDeclQGraphicsScene_EventAdaptor

#include "gsiDecl.h"
#include "gsiQtEvents.h"
#include "gsiQtGui.h"
#include "gsiDeclQGraphicsScene_Enums.h"

#include "layExceptions.h"

#include <QtCore/QObject>

// -----------------------------------------------------------------------
// class QGraphicsScene_EventAdaptor

class QGraphicsScene_EventAdaptor
  : public QObject, public qt_gsi::EventAdaptorBase, public gsi::ObjectBase
{
Q_OBJECT

public:
  QGraphicsScene_EventAdaptor (QObject *host);

public slots:
  void changed(const QList<QRectF> &);
  void destroyed(QObject *);
  void sceneRectChanged(const QRectF &);
  void selectionChanged();

public:
  gsi::event<const qt_gsi::Converter<QList<QRectF> >::target_type &> changed_e_2477;
  gsi::event<QObject *> destroyed_e_1302;
  gsi::event<const QRectF &> sceneRectChanged_e_1862;
  gsi::event<> selectionChanged_e_0;
};

#endif