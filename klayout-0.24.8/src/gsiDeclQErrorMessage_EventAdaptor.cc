
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
*  @file generated/gsiDeclQErrorMessage_EventAdaptor.cc
*  @brief Event adaptor implementations for QErrorMessage
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQErrorMessage_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QErrorMessage_EventAdaptor

QErrorMessage_EventAdaptor::QErrorMessage_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(accepted()), this, SLOT(accepted()));
  connect (host, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(customContextMenuRequested(const QPoint &)));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(finished(int)), this, SLOT(finished(int)));
  connect (host, SIGNAL(rejected()), this, SLOT(rejected()));
}

//  Event QErrorMessage::accepted()
void QErrorMessage_EventAdaptor::accepted() {
BEGIN_PROTECTED
  accepted_e_0();
END_PROTECTED
}

//  Event QErrorMessage::customContextMenuRequested(const QPoint &pos)
void QErrorMessage_EventAdaptor::customContextMenuRequested(const QPoint &pos) {
BEGIN_PROTECTED
  customContextMenuRequested_e_1916(pos);
END_PROTECTED
}

//  Event QErrorMessage::destroyed(QObject *arg1)
void QErrorMessage_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QErrorMessage::finished(int result)
void QErrorMessage_EventAdaptor::finished(int result) {
BEGIN_PROTECTED
  finished_e_767(result);
END_PROTECTED
}

//  Event QErrorMessage::rejected()
void QErrorMessage_EventAdaptor::rejected() {
BEGIN_PROTECTED
  rejected_e_0();
END_PROTECTED
}
