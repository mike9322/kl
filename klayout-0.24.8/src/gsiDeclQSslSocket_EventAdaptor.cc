
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
*  @file generated/gsiDeclQSslSocket_EventAdaptor.cc
*  @brief Event adaptor implementations for QSslSocket
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtNetwork.h"
#include "gsiDeclQSslSocket_EventAdaptor.h"

// -----------------------------------------------------------------------
// class QSslSocket_EventAdaptor

QSslSocket_EventAdaptor::QSslSocket_EventAdaptor (QObject *host)
  : QObject ()
{
  connect (host, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
  connect (host, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
  connect (host, SIGNAL(connected()), this, SLOT(connected()));
  connect (host, SIGNAL(destroyed(QObject *)), this, SLOT(destroyed(QObject *)));
  connect (host, SIGNAL(disconnected()), this, SLOT(disconnected()));
  connect (host, SIGNAL(encrypted()), this, SLOT(encrypted()));
  connect (host, SIGNAL(encryptedBytesWritten(qint64)), this, SLOT(encryptedBytesWritten(qint64)));
  connect (host, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
  connect (host, SIGNAL(hostFound()), this, SLOT(hostFound()));
  connect (host, SIGNAL(modeChanged(QSslSocket::SslMode)), this, SLOT(modeChanged(QSslSocket::SslMode)));
  connect (host, SIGNAL(peerVerifyError(const QSslError &)), this, SLOT(peerVerifyError(const QSslError &)));
  connect (host, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)), this, SLOT(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)));
  connect (host, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinished()));
  connect (host, SIGNAL(readyRead()), this, SLOT(readyRead()));
  connect (host, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(sslErrors(const QList<QSslError> &)));
  connect (host, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
}

//  Event QSslSocket::aboutToClose()
void QSslSocket_EventAdaptor::aboutToClose() {
BEGIN_PROTECTED
  aboutToClose_e_0();
END_PROTECTED
}

//  Event QSslSocket::bytesWritten(qint64 bytes)
void QSslSocket_EventAdaptor::bytesWritten(qint64 bytes) {
BEGIN_PROTECTED
  bytesWritten_e_986(bytes);
END_PROTECTED
}

//  Event QSslSocket::connected()
void QSslSocket_EventAdaptor::connected() {
BEGIN_PROTECTED
  connected_e_0();
END_PROTECTED
}

//  Event QSslSocket::destroyed(QObject *arg1)
void QSslSocket_EventAdaptor::destroyed(QObject *arg1) {
BEGIN_PROTECTED
  destroyed_e_1302(arg1);
END_PROTECTED
}

//  Event QSslSocket::disconnected()
void QSslSocket_EventAdaptor::disconnected() {
BEGIN_PROTECTED
  disconnected_e_0();
END_PROTECTED
}

//  Event QSslSocket::encrypted()
void QSslSocket_EventAdaptor::encrypted() {
BEGIN_PROTECTED
  encrypted_e_0();
END_PROTECTED
}

//  Event QSslSocket::encryptedBytesWritten(qint64 totalBytes)
void QSslSocket_EventAdaptor::encryptedBytesWritten(qint64 totalBytes) {
BEGIN_PROTECTED
  encryptedBytesWritten_e_986(totalBytes);
END_PROTECTED
}

//  Event QSslSocket::error(QAbstractSocket::SocketError arg1)
void QSslSocket_EventAdaptor::error(QAbstractSocket::SocketError arg1) {
BEGIN_PROTECTED
  error_e_3209(qt_gsi::CppToQtAdaptor<QAbstractSocket::SocketError>(arg1));
END_PROTECTED
}

//  Event QSslSocket::hostFound()
void QSslSocket_EventAdaptor::hostFound() {
BEGIN_PROTECTED
  hostFound_e_0();
END_PROTECTED
}

//  Event QSslSocket::modeChanged(QSslSocket::SslMode newMode)
void QSslSocket_EventAdaptor::modeChanged(QSslSocket::SslMode newMode) {
BEGIN_PROTECTED
  modeChanged_e_2251(qt_gsi::CppToQtAdaptor<QSslSocket::SslMode>(newMode));
END_PROTECTED
}

//  Event QSslSocket::peerVerifyError(const QSslError &error)
void QSslSocket_EventAdaptor::peerVerifyError(const QSslError &error) {
BEGIN_PROTECTED
  peerVerifyError_e_2222(error);
END_PROTECTED
}

//  Event QSslSocket::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
void QSslSocket_EventAdaptor::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator) {
BEGIN_PROTECTED
  proxyAuthenticationRequired_e_4652(proxy, authenticator);
END_PROTECTED
}

//  Event QSslSocket::readChannelFinished()
void QSslSocket_EventAdaptor::readChannelFinished() {
BEGIN_PROTECTED
  readChannelFinished_e_0();
END_PROTECTED
}

//  Event QSslSocket::readyRead()
void QSslSocket_EventAdaptor::readyRead() {
BEGIN_PROTECTED
  readyRead_e_0();
END_PROTECTED
}

//  Event QSslSocket::sslErrors(const QList<QSslError> &errors)
void QSslSocket_EventAdaptor::sslErrors(const QList<QSslError> &errors) {
BEGIN_PROTECTED
  sslErrors_e_2837(qt_gsi::CppToQtAdaptor<QList<QSslError> >(errors));
END_PROTECTED
}

//  Event QSslSocket::stateChanged(QAbstractSocket::SocketState arg1)
void QSslSocket_EventAdaptor::stateChanged(QAbstractSocket::SocketState arg1) {
BEGIN_PROTECTED
  stateChanged_e_3200(qt_gsi::CppToQtAdaptor<QAbstractSocket::SocketState>(arg1));
END_PROTECTED
}
