
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
*  @file generated/gsiDeclQDrag_EventAdaptor.cc
*  @brief Event adaptor implementations for QDrag
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQDrag_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QDrag_EventAdaptor

QDrag_EventAdaptor::QDrag_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(actionChanged(Qt::DropAction)), this, SLOT(actionChanged(Qt::DropAction)));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(targetChanged(QWidget *)), this, SLOT(targetChanged(QWidget *)));
}

//  Event QDrag::actionChanged(Qt::DropAction action)
void QDrag_EventAdaptor::actionChanged(Qt::DropAction action) {
BEGIN_PROTECTED
  actionChanged_e_1760(qt_gsi::CppToQtAdaptor<Qt::DropAction>(action));
END_PROTECTED
}

//  Event QDrag::destroyed(QObject *arg1)
void QDrag_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QDrag::targetChanged(QWidget *newTarget)
void QDrag_EventAdaptor::targetChanged(QWidget *newTarget) {
BEGIN_PROTECTED
  targetChanged_e_1315(newTarget);
END_PROTECTED
}
