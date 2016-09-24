
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
*  @file generated/gsiDeclQAbstractProxyModel_EventAdaptor.cc
*  @brief Event adaptor implementations for QAbstractProxyModel
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQAbstractProxyModel_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QAbstractProxyModel_EventAdaptor

QAbstractProxyModel_EventAdaptor::QAbstractProxyModel_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(headerDataChanged(Qt::Orientation, int, int)), this, SLOT(headerDataChanged(Qt::Orientation, int, int)));
  connect (host, SIGNAL(layoutAboutToBeChanged()), this, SLOT(layoutAboutToBeChanged()));
  connect (host, SIGNAL(layoutChanged()), this, SLOT(layoutChanged()));
}

//  Event QAbstractProxyModel::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
void QAbstractProxyModel_EventAdaptor::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
BEGIN_PROTECTED
  dataChanged_e_4682(topLeft, bottomRight);
END_PROTECTED
}

//  Event QAbstractProxyModel::destroyed(QObject *arg1)
void QAbstractProxyModel_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QAbstractProxyModel::headerDataChanged(Qt::Orientation orientation, int first, int last)
void QAbstractProxyModel_EventAdaptor::headerDataChanged(Qt::Orientation orientation, int first, int last) {
BEGIN_PROTECTED
  headerDataChanged_e_3231(qt_gsi::CppToQtAdaptor<Qt::Orientation>(orientation), first, last);
END_PROTECTED
}

//  Event QAbstractProxyModel::layoutAboutToBeChanged()
void QAbstractProxyModel_EventAdaptor::layoutAboutToBeChanged() {
BEGIN_PROTECTED
  layoutAboutToBeChanged_e_0();
END_PROTECTED
}

//  Event QAbstractProxyModel::layoutChanged()
void QAbstractProxyModel_EventAdaptor::layoutChanged() {
BEGIN_PROTECTED
  layoutChanged_e_0();
END_PROTECTED
}
