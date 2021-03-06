
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
*  @file generated/gsiDeclQGraphicsTextItem_EventAdaptor.cc
*  @brief Event adaptor implementations for QGraphicsTextItem
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQGraphicsTextItem_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QGraphicsTextItem_EventAdaptor

QGraphicsTextItem_EventAdaptor::QGraphicsTextItem_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(enabledChanged()), this, SLOT(enabledChanged()));
  connect (host, SIGNAL(linkActivated(const QString &)), this, SLOT(linkActivated(const QString &)));
  connect (host, SIGNAL(linkHovered(const QString &)), this, SLOT(linkHovered(const QString &)));
  connect (host, SIGNAL(opacityChanged()), this, SLOT(opacityChanged()));
  connect (host, SIGNAL(parentChanged()), this, SLOT(parentChanged()));
  connect (host, SIGNAL(rotationChanged()), this, SLOT(rotationChanged()));
  connect (host, SIGNAL(scaleChanged()), this, SLOT(scaleChanged()));
  connect (host, SIGNAL(visibleChanged()), this, SLOT(visibleChanged()));
  connect (host, SIGNAL(xChanged()), this, SLOT(xChanged()));
  connect (host, SIGNAL(yChanged()), this, SLOT(yChanged()));
  connect (host, SIGNAL(zChanged()), this, SLOT(zChanged()));
}

//  Event QGraphicsTextItem::destroyed(QObject *arg1)
void QGraphicsTextItem_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QGraphicsTextItem::enabledChanged()
void QGraphicsTextItem_EventAdaptor::enabledChanged() {
BEGIN_PROTECTED
  enabledChanged_e_0();
END_PROTECTED
}

//  Event QGraphicsTextItem::linkActivated(const QString &arg1)
void QGraphicsTextItem_EventAdaptor::linkActivated(const QString &arg1) {
BEGIN_PROTECTED
  linkActivated_e_2025(arg1);
END_PROTECTED
}

//  Event QGraphicsTextItem::linkHovered(const QString &arg1)
void QGraphicsTextItem_EventAdaptor::linkHovered(const QString &arg1) {
BEGIN_PROTECTED
  linkHovered_e_2025(arg1);
END_PROTECTED
}

//  Event QGraphicsTextItem::opacityChanged()
void QGraphicsTextItem_EventAdaptor::opacityChanged() {
BEGIN_PROTECTED
  opacityChanged_e_0();
END_PROTECTED
}

//  Event QGraphicsTextItem::parentChanged()
void QGraphicsTextItem_EventAdaptor::parentChanged() {
BEGIN_PROTECTED
  parentChanged_e_0();
END_PROTECTED
}

//  Event QGraphicsTextItem::rotationChanged()
void QGraphicsTextItem_EventAdaptor::rotationChanged() {
BEGIN_PROTECTED
  rotationChanged_e_0();
END_PROTECTED
}

//  Event QGraphicsTextItem::scaleChanged()
void QGraphicsTextItem_EventAdaptor::scaleChanged() {
BEGIN_PROTECTED
  scaleChanged_e_0();
END_PROTECTED
}

//  Event QGraphicsTextItem::visibleChanged()
void QGraphicsTextItem_EventAdaptor::visibleChanged() {
BEGIN_PROTECTED
  visibleChanged_e_0();
END_PROTECTED
}

//  Event QGraphicsTextItem::xChanged()
void QGraphicsTextItem_EventAdaptor::xChanged() {
BEGIN_PROTECTED
  xChanged_e_0();
END_PROTECTED
}

//  Event QGraphicsTextItem::yChanged()
void QGraphicsTextItem_EventAdaptor::yChanged() {
BEGIN_PROTECTED
  yChanged_e_0();
END_PROTECTED
}

//  Event QGraphicsTextItem::zChanged()
void QGraphicsTextItem_EventAdaptor::zChanged() {
BEGIN_PROTECTED
  zChanged_e_0();
END_PROTECTED
}
