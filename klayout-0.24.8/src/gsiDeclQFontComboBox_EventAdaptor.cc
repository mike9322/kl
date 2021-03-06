
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
*  @file generated/gsiDeclQFontComboBox_EventAdaptor.cc
*  @brief Event adaptor implementations for QFontComboBox
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtGui.h"
#include "gsiDeclQFontComboBox_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QFontComboBox_EventAdaptor

QFontComboBox_EventAdaptor::QFontComboBox_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(activated(int)), this, SLOT(activated(int)));
  connect (host, SIGNAL(activated(const QString &)), this, SLOT(activated(const QString &)));
  connect (host, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(currentFontChanged(const QFont &)));
  connect (host, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
  connect (host, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(currentIndexChanged(const QString &)));
  connect (host, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(customContextMenuRequested(const QPoint &)));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(editTextChanged(const QString &)), this, SLOT(editTextChanged(const QString &)));
  connect (host, SIGNAL(highlighted(int)), this, SLOT(highlighted(int)));
  connect (host, SIGNAL(highlighted(const QString &)), this, SLOT(highlighted(const QString &)));
}

//  Event QFontComboBox::activated(int index)
void QFontComboBox_EventAdaptor::activated(int index) {
BEGIN_PROTECTED
  activated_e_767(index);
END_PROTECTED
}

//  Event QFontComboBox::activated(const QString &arg1)
void QFontComboBox_EventAdaptor::activated(const QString &arg1) {
BEGIN_PROTECTED
  activated_e_2025(arg1);
END_PROTECTED
}

//  Event QFontComboBox::currentFontChanged(const QFont &f)
void QFontComboBox_EventAdaptor::currentFontChanged(const QFont &f) {
BEGIN_PROTECTED
  currentFontChanged_e_1801(f);
END_PROTECTED
}

//  Event QFontComboBox::currentIndexChanged(int index)
void QFontComboBox_EventAdaptor::currentIndexChanged(int index) {
BEGIN_PROTECTED
  currentIndexChanged_e_767(index);
END_PROTECTED
}

//  Event QFontComboBox::currentIndexChanged(const QString &arg1)
void QFontComboBox_EventAdaptor::currentIndexChanged(const QString &arg1) {
BEGIN_PROTECTED
  currentIndexChanged_e_2025(arg1);
END_PROTECTED
}

//  Event QFontComboBox::customContextMenuRequested(const QPoint &pos)
void QFontComboBox_EventAdaptor::customContextMenuRequested(const QPoint &pos) {
BEGIN_PROTECTED
  customContextMenuRequested_e_1916(pos);
END_PROTECTED
}

//  Event QFontComboBox::destroyed(QObject *arg1)
void QFontComboBox_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QFontComboBox::editTextChanged(const QString &arg1)
void QFontComboBox_EventAdaptor::editTextChanged(const QString &arg1) {
BEGIN_PROTECTED
  editTextChanged_e_2025(arg1);
END_PROTECTED
}

//  Event QFontComboBox::highlighted(int index)
void QFontComboBox_EventAdaptor::highlighted(int index) {
BEGIN_PROTECTED
  highlighted_e_767(index);
END_PROTECTED
}

//  Event QFontComboBox::highlighted(const QString &arg1)
void QFontComboBox_EventAdaptor::highlighted(const QString &arg1) {
BEGIN_PROTECTED
  highlighted_e_2025(arg1);
END_PROTECTED
}
