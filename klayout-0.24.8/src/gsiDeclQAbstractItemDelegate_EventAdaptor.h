
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
*  @file generated/gsiDeclQAbstractItemDelegate_EventAdaptor.h
*  @brief Event adaptor implementations for QAbstractItemDelegate
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQAbstractItemDelegate_EventAdaptor
#define _HDR_gsiDeclQAbstractItemDelegate_EventAdaptor

#include "gsiDecl.h"
#include "gsiQtEvents.h"
#include "gsiQtGui.h"
#include "gsiDeclQAbstractItemDelegate_Enums.h"

#include "layExceptions.h"

#include <QtCore/QObject>

// -----------------------------------------------------------------------
// class QAbstractItemDelegate_EventAdaptor

class QAbstractItemDelegate_EventAdaptor
  : public QObject, public qt_gsi::EventAdaptorBase, public gsi::ObjectBase
{
Q_OBJECT

public:
  QAbstractItemDelegate_EventAdaptor (QObject *host);

public slots:
  void closeEditor(QWidget *, QAbstractItemDelegate::EndEditHint);
  void commitData(QWidget *);
  void destroyed(QObject *);
  void sizeHintChanged(const QModelIndex &);

public:
  gsi::event<QWidget *, const qt_gsi::Converter<QAbstractItemDelegate::EndEditHint>::target_type &> closeEditor_e_4926;
  gsi::event<QWidget *> commitData_e_1315;
  gsi::event<QObject *> destroyed_e_1302;
  gsi::event<const QModelIndex &> sizeHintChanged_e_2395;
};

#endif
