
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
*  @file generated/gsiDeclQListWidget_EventAdaptor.cc
*  @brief Event adaptor implementations for QListWidget
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQListWidget_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QListWidget_EventAdaptor

QListWidget_EventAdaptor::QListWidget_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(activated(const QModelIndex &)), this, SLOT(activated(const QModelIndex &)));
  connect (host, SIGNAL(clicked(const QModelIndex &)), this, SLOT(clicked(const QModelIndex &)));
  connect (host, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(currentItemChanged(QListWidgetItem *, QListWidgetItem *)));
  connect (host, SIGNAL(currentRowChanged(int)), this, SLOT(currentRowChanged(int)));
  connect (host, SIGNAL(currentTextChanged(const QString &)), this, SLOT(currentTextChanged(const QString &)));
  connect (host, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(customContextMenuRequested(const QPoint &)));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(doubleClicked(const QModelIndex &)));
  connect (host, SIGNAL(entered(const QModelIndex &)), this, SLOT(entered(const QModelIndex &)));
  connect (host, SIGNAL(indexesMoved(const QModelIndexList &)), this, SLOT(indexesMoved(const QModelIndexList &)));
  connect (host, SIGNAL(itemActivated(QListWidgetItem *)), this, SLOT(itemActivated(QListWidgetItem *)));
  connect (host, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(itemChanged(QListWidgetItem *)));
  connect (host, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClicked(QListWidgetItem *)));
  connect (host, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(itemDoubleClicked(QListWidgetItem *)));
  connect (host, SIGNAL(itemEntered(QListWidgetItem *)), this, SLOT(itemEntered(QListWidgetItem *)));
  connect (host, SIGNAL(itemPressed(QListWidgetItem *)), this, SLOT(itemPressed(QListWidgetItem *)));
  connect (host, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
  connect (host, SIGNAL(pressed(const QModelIndex &)), this, SLOT(pressed(const QModelIndex &)));
  connect (host, SIGNAL(viewportEntered()), this, SLOT(viewportEntered()));
}

//  Event QListWidget::activated(const QModelIndex &index)
void QListWidget_EventAdaptor::activated(const QModelIndex &index) {
BEGIN_PROTECTED
  activated_e_2395(index);
END_PROTECTED
}

//  Event QListWidget::clicked(const QModelIndex &index)
void QListWidget_EventAdaptor::clicked(const QModelIndex &index) {
BEGIN_PROTECTED
  clicked_e_2395(index);
END_PROTECTED
}

//  Event QListWidget::currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
void QListWidget_EventAdaptor::currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous) {
BEGIN_PROTECTED
  currentItemChanged_e_4144(current, previous);
END_PROTECTED
}

//  Event QListWidget::currentRowChanged(int currentRow)
void QListWidget_EventAdaptor::currentRowChanged(int currentRow) {
BEGIN_PROTECTED
  currentRowChanged_e_767(currentRow);
END_PROTECTED
}

//  Event QListWidget::currentTextChanged(const QString &currentText)
void QListWidget_EventAdaptor::currentTextChanged(const QString &currentText) {
BEGIN_PROTECTED
  currentTextChanged_e_2025(currentText);
END_PROTECTED
}

//  Event QListWidget::customContextMenuRequested(const QPoint &pos)
void QListWidget_EventAdaptor::customContextMenuRequested(const QPoint &pos) {
BEGIN_PROTECTED
  customContextMenuRequested_e_1916(pos);
END_PROTECTED
}

//  Event QListWidget::destroyed(QObject *arg1)
void QListWidget_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QListWidget::doubleClicked(const QModelIndex &index)
void QListWidget_EventAdaptor::doubleClicked(const QModelIndex &index) {
BEGIN_PROTECTED
  doubleClicked_e_2395(index);
END_PROTECTED
}

//  Event QListWidget::entered(const QModelIndex &index)
void QListWidget_EventAdaptor::entered(const QModelIndex &index) {
BEGIN_PROTECTED
  entered_e_2395(index);
END_PROTECTED
}

//  Event QListWidget::indexesMoved(const QList<QModelIndex> &indexes)
void QListWidget_EventAdaptor::indexesMoved(const QModelIndexList &indexes) {
BEGIN_PROTECTED
  indexesMoved_e_3010(qt_gsi::CppToQtAdaptor<QList<QModelIndex> >(indexes));
END_PROTECTED
}

//  Event QListWidget::itemActivated(QListWidgetItem *item)
void QListWidget_EventAdaptor::itemActivated(QListWidgetItem *item) {
BEGIN_PROTECTED
  itemActivated_e_2126(item);
END_PROTECTED
}

//  Event QListWidget::itemChanged(QListWidgetItem *item)
void QListWidget_EventAdaptor::itemChanged(QListWidgetItem *item) {
BEGIN_PROTECTED
  itemChanged_e_2126(item);
END_PROTECTED
}

//  Event QListWidget::itemClicked(QListWidgetItem *item)
void QListWidget_EventAdaptor::itemClicked(QListWidgetItem *item) {
BEGIN_PROTECTED
  itemClicked_e_2126(item);
END_PROTECTED
}

//  Event QListWidget::itemDoubleClicked(QListWidgetItem *item)
void QListWidget_EventAdaptor::itemDoubleClicked(QListWidgetItem *item) {
BEGIN_PROTECTED
  itemDoubleClicked_e_2126(item);
END_PROTECTED
}

//  Event QListWidget::itemEntered(QListWidgetItem *item)
void QListWidget_EventAdaptor::itemEntered(QListWidgetItem *item) {
BEGIN_PROTECTED
  itemEntered_e_2126(item);
END_PROTECTED
}

//  Event QListWidget::itemPressed(QListWidgetItem *item)
void QListWidget_EventAdaptor::itemPressed(QListWidgetItem *item) {
BEGIN_PROTECTED
  itemPressed_e_2126(item);
END_PROTECTED
}

//  Event QListWidget::itemSelectionChanged()
void QListWidget_EventAdaptor::itemSelectionChanged() {
BEGIN_PROTECTED
  itemSelectionChanged_e_0();
END_PROTECTED
}

//  Event QListWidget::pressed(const QModelIndex &index)
void QListWidget_EventAdaptor::pressed(const QModelIndex &index) {
BEGIN_PROTECTED
  pressed_e_2395(index);
END_PROTECTED
}

//  Event QListWidget::viewportEntered()
void QListWidget_EventAdaptor::viewportEntered() {
BEGIN_PROTECTED
  viewportEntered_e_0();
END_PROTECTED
}
