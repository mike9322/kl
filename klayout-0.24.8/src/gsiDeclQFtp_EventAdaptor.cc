
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
*  @file generated/gsiDeclQFtp_EventAdaptor.cc
*  @brief Event adaptor implementations for QFtp
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtNetwork.h"
#include "gsiDeclQFtp_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QFtp_EventAdaptor

QFtp_EventAdaptor::QFtp_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(commandFinished(int, bool)), this, SLOT(commandFinished(int, bool)));
  connect (host, SIGNAL(commandStarted(int)), this, SLOT(commandStarted(int)));
  connect (host, SIGNAL(dataTransferProgress(qint64, qint64)), this, SLOT(dataTransferProgress(qint64, qint64)));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(done(bool)), this, SLOT(done(bool)));
  connect (host, SIGNAL(listInfo(const QUrlInfo &)), this, SLOT(listInfo(const QUrlInfo &)));
  connect (host, SIGNAL(rawCommandReply(int, const QString &)), this, SLOT(rawCommandReply(int, const QString &)));
  connect (host, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect (host, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
}

//  Event QFtp::commandFinished(int arg1, bool arg2)
void QFtp_EventAdaptor::commandFinished(int arg1, bool arg2) {
BEGIN_PROTECTED
  commandFinished_e_1523(arg1, arg2);
END_PROTECTED
}

//  Event QFtp::commandStarted(int arg1)
void QFtp_EventAdaptor::commandStarted(int arg1) {
BEGIN_PROTECTED
  commandStarted_e_767(arg1);
END_PROTECTED
}

//  Event QFtp::dataTransferProgress(qint64 arg1, qint64 arg2)
void QFtp_EventAdaptor::dataTransferProgress(qint64 arg1, qint64 arg2) {
BEGIN_PROTECTED
  dataTransferProgress_e_1864(arg1, arg2);
END_PROTECTED
}

//  Event QFtp::destroyed(QObject *arg1)
void QFtp_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QFtp::done(bool arg1)
void QFtp_EventAdaptor::done(bool arg1) {
BEGIN_PROTECTED
  done_e_864(arg1);
END_PROTECTED
}

//  Event QFtp::listInfo(const QUrlInfo &arg1)
void QFtp_EventAdaptor::listInfo(const QUrlInfo &arg1) {
BEGIN_PROTECTED
  listInfo_e_2097(arg1);
END_PROTECTED
}

//  Event QFtp::rawCommandReply(int arg1, const QString &arg2)
void QFtp_EventAdaptor::rawCommandReply(int arg1, const QString &arg2) {
BEGIN_PROTECTED
  rawCommandReply_e_2684(arg1, arg2);
END_PROTECTED
}

//  Event QFtp::readyRead()
void QFtp_EventAdaptor::readyRead() {
BEGIN_PROTECTED
  readyRead_e_0();
END_PROTECTED
}

//  Event QFtp::stateChanged(int arg1)
void QFtp_EventAdaptor::stateChanged(int arg1) {
BEGIN_PROTECTED
  stateChanged_e_767(arg1);
END_PROTECTED
}
