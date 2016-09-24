
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
*  @file generated/gsiDeclQSocketNotifier_EventAdaptor.cc
*  @brief Event adaptor implementations for QSocketNotifier
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtCore.h"
#include "gsiDeclQSocketNotifier_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QSocketNotifier_EventAdaptor

QSocketNotifier_EventAdaptor::QSocketNotifier_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(activated(int)), this, SLOT(activated(int)));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
}

//  Event QSocketNotifier::activated(int socket)
void QSocketNotifier_EventAdaptor::activated(int socket) {
BEGIN_PROTECTED
  activated_e_767(socket);
END_PROTECTED
}

//  Event QSocketNotifier::destroyed(QObject *arg1)
void QSocketNotifier_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}
