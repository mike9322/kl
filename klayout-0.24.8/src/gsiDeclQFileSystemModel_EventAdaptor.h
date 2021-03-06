
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
*  @file generated/gsiDeclQFileSystemModel_EventAdaptor.h
*  @brief Event adaptor implementations for QFileSystemModel
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#ifndef _HDR_gsiDeclQFileSystemModel_EventAdaptor
#define _HDR_gsiDeclQFileSystemModel_EventAdaptor

#include "gsiDecl.h"
#include "gsiQtEvents.h"
#include "gsiQtGui.h"
#include "gsiDeclQFileSystemModel_Enums.h"

#include "layExceptions.h"

#include <QtCore/QObject>

// -----------------------------------------------------------------------
// class QFileSystemModel_EventAdaptor

class QFileSystemModel_EventAdaptor
  : public QObject, public qt_gsi::EventAdaptorBase, public gsi::ObjectBase
{
Q_OBJECT

public:
  QFileSystemModel_EventAdaptor (QObject *host);

public slots:
  void dataChanged(const QModelIndex &, const QModelIndex &);
  void destroyed(QObject *);
  void fileRenamed(const QString &, const QString &, const QString &);
  void headerDataChanged(Qt::Orientation, int, int);
  void layoutAboutToBeChanged();
  void layoutChanged();
  void rootPathChanged(const QString &);

public:
  gsi::event<const QModelIndex &, const QModelIndex &> dataChanged_e_4682;
  gsi::event<QObject *> destroyed_e_1302;
  gsi::event<const QString &, const QString &, const QString &> fileRenamed_e_5859;
  gsi::event<const qt_gsi::Converter<Qt::Orientation>::target_type &, int, int> headerDataChanged_e_3231;
  gsi::event<> layoutAboutToBeChanged_e_0;
  gsi::event<> layoutChanged_e_0;
  gsi::event<const QString &> rootPathChanged_e_2025;
};

#endif
