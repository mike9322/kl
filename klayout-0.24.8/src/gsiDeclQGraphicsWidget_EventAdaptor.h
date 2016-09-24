
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
*  @file generated/gsiDeclQGraphicsWidget_EventAdaptor.h
*  @brief Event adaptor implementations for QGraphicsWidget
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQGraphicsWidget_EventAdaptor
#define _HDR_gsiDeclQGraphicsWidget_EventAdaptor

#include "gsiDecl.h"
#include "gsiQtEvents.h"
#include "gsiQtGui.h"
#include "gsiDeclQGraphicsWidget_Enums.h"

#include "layExceptions.h"

#include <QtCore/QObject>

// -----------------------------------------------------------------------
// class QGraphicsWidget_EventAdaptor

class QGraphicsWidget_EventAdaptor
  : public QObject, public qt_gsi::EventAdaptorBase, public gsi::ObjectBase
{
Q_OBJECT

public:
  QGraphicsWidget_EventAdaptor (QObject *host);

public slots:
  void destroyed(QObject *);
  void enabledChanged();
  void opacityChanged();
  void parentChanged();
  void rotationChanged();
  void scaleChanged();
  void visibleChanged();
  void xChanged();
  void yChanged();
  void zChanged();

public:
  gsi::event<QObject *> destroyed_e_1302;
  gsi::event<> enabledChanged_e_0;
  gsi::event<> opacityChanged_e_0;
  gsi::event<> parentChanged_e_0;
  gsi::event<> rotationChanged_e_0;
  gsi::event<> scaleChanged_e_0;
  gsi::event<> visibleChanged_e_0;
  gsi::event<> xChanged_e_0;
  gsi::event<> yChanged_e_0;
  gsi::event<> zChanged_e_0;
};

#endif
