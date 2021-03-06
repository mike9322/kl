
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
*  @file generated/gsiDeclQMenuBar_EventAdaptor.cc
*  @brief Event adaptor implementations for QMenuBar
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQMenuBar_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QMenuBar_EventAdaptor

QMenuBar_EventAdaptor::QMenuBar_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(customContextMenuRequested(const QPoint &)));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(hovered(QAction *)), this, SLOT(hovered(QAction *)));
  connect (host, SIGNAL(triggered(QAction *)), this, SLOT(triggered(QAction *)));
}

//  Event QMenuBar::customContextMenuRequested(const QPoint &pos)
void QMenuBar_EventAdaptor::customContextMenuRequested(const QPoint &pos) {
BEGIN_PROTECTED
  customContextMenuRequested_e_1916(pos);
END_PROTECTED
}

//  Event QMenuBar::destroyed(QObject *arg1)
void QMenuBar_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QMenuBar::hovered(QAction *action)
void QMenuBar_EventAdaptor::hovered(QAction *action) {
BEGIN_PROTECTED
  hovered_e_1309(action);
END_PROTECTED
}

//  Event QMenuBar::triggered(QAction *action)
void QMenuBar_EventAdaptor::triggered(QAction *action) {
BEGIN_PROTECTED
  triggered_e_1309(action);
END_PROTECTED
}
