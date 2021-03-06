
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
*  @file generated/gsiDeclQTcpSocket_EventAdaptor.cc
*  @brief Event adaptor implementations for QTcpSocket
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtNetwork.h"
#include "gsiDeclQTcpSocket_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QTcpSocket_EventAdaptor

QTcpSocket_EventAdaptor::QTcpSocket_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
  connect (host, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
  connect (host, SIGNAL(connected()), this, SLOT(connected()));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(disconnected()), this, SLOT(disconnected()));
  connect (host, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
  connect (host, SIGNAL(hostFound()), this, SLOT(hostFound()));
  connect (host, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)), this, SLOT(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)));
  connect (host, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));
  connect (host, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect (host, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
}

//  Event QTcpSocket::aboutToClose()
void QTcpSocket_EventAdaptor::aboutToClose() {
BEGIN_PROTECTED
  aboutToClose_e_0();
END_PROTECTED
}

//  Event QTcpSocket::bytesWritten(qint64 bytes)
void QTcpSocket_EventAdaptor::bytesWritten(qint64 bytes) {
BEGIN_PROTECTED
  bytesWritten_e_986(bytes);
END_PROTECTED
}

//  Event QTcpSocket::connected()
void QTcpSocket_EventAdaptor::connected() {
BEGIN_PROTECTED
  connected_e_0();
END_PROTECTED
}

//  Event QTcpSocket::destroyed(QObject *arg1)
void QTcpSocket_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QTcpSocket::disconnected()
void QTcpSocket_EventAdaptor::disconnected() {
BEGIN_PROTECTED
  disconnected_e_0();
END_PROTECTED
}

//  Event QTcpSocket::error(QAbstractSocket::SocketError arg1)
void QTcpSocket_EventAdaptor::error(QAbstractSocket::SocketError arg1) {
BEGIN_PROTECTED
  error_e_3209(qt_gsi::CppToQtAdaptor<QAbstractSocket::SocketError>(arg1));
END_PROTECTED
}

//  Event QTcpSocket::hostFound()
void QTcpSocket_EventAdaptor::hostFound() {
BEGIN_PROTECTED
  hostFound_e_0();
END_PROTECTED
}

//  Event QTcpSocket::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
void QTcpSocket_EventAdaptor::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator) {
BEGIN_PROTECTED
  proxyAuthenticationRequired_e_4652(proxy, authenticator);
END_PROTECTED
}

//  Event QTcpSocket::readChannelFinished()
void QTcpSocket_EventAdaptor::readChannelFinished() {
BEGIN_PROTECTED
  readChannelFinished_e_0();
END_PROTECTED
}

//  Event QTcpSocket::readyRead()
void QTcpSocket_EventAdaptor::readyRead() {
BEGIN_PROTECTED
  readyRead_e_0();
END_PROTECTED
}

//  Event QTcpSocket::stateChanged(QAbstractSocket::SocketState arg1)
void QTcpSocket_EventAdaptor::stateChanged(QAbstractSocket::SocketState arg1) {
BEGIN_PROTECTED
  stateChanged_e_3200(qt_gsi::CppToQtAdaptor<QAbstractSocket::SocketState>(arg1));
END_PROTECTED
}
