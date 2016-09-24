
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


#include "tlHttpStream.h"
#include "tlStaticObjects.h"

#include "PasswordDialog.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QAuthenticator>
#include <QtCore/QCoreApplication>
#include <QtCore/QDateTime>
#include <QtCore/QFileInfo>
#include <QtGui/QDialog>

namespace tl
{

// ---------------------------------------------------------------
//  PasswordDialog definition and implementation

class PasswordDialog
  : public QDialog, private Ui::PasswordDialog
{
public:
  PasswordDialog (QWidget *parent)
    : QDialog (parent)
  {
    setupUi (this);
  }
  
  bool exec (bool proxy, const QString &where, QAuthenticator *auth)
  {
    realm_label->setText (QString::fromAscii ("<b>Realm:</b> ") + auth->realm ());
    if (proxy) {
      where_label->setText (QString::fromAscii ("<b>Proxy:</b> ") + where);
    } else {
      where_label->setText (QString::fromAscii ("<b>URL:</b> ") + where);
    }

    if (QDialog::exec ()) {
      auth->setPassword (password_le->text ());
      auth->setUser (user_le->text ());
      return true;
    } else {
      return false;
    }

  }
};

// ---------------------------------------------------------------
//  InputHttpFile implementation

static QNetworkAccessManager *s_network_manager (0);

InputHttpStream::InputHttpStream (const std::string &url)
  : m_url (url)
{
  if (! s_network_manager) {
    s_network_manager = new QNetworkAccessManager(0);
    tl::StaticObjects::reg (&s_network_manager);
  }
  connect (s_network_manager, SIGNAL (finished (QNetworkReply *)), this, SLOT (finished (QNetworkReply *)));
  connect (s_network_manager, SIGNAL (authenticationRequired (QNetworkReply *, QAuthenticator *)), this, SLOT (authenticationRequired (QNetworkReply *, QAuthenticator *)));
  connect (s_network_manager, SIGNAL (proxyAuthenticationRequired (const QNetworkProxy &, QAuthenticator *)), this, SLOT (proxyAuthenticationRequired (const QNetworkProxy &, QAuthenticator *)));
  s_network_manager->get (QNetworkRequest (QUrl (tl::to_qstring (url))));
  mp_reply = 0;
}

InputHttpStream::~InputHttpStream ()
{
  delete mp_reply;
  mp_reply = 0;
}

void 
InputHttpStream::authenticationRequired (QNetworkReply *reply, QAuthenticator *auth)
{
  PasswordDialog pw_dialog (0 /*no parent*/);
  pw_dialog.exec (false, reply->url ().toString (), auth);
}

void 
InputHttpStream::proxyAuthenticationRequired (const QNetworkProxy &proxy, QAuthenticator *auth)
{
  PasswordDialog pw_dialog (0 /*no parent*/);
  pw_dialog.exec (true, proxy.hostName (), auth);
}

void 
InputHttpStream::finished (QNetworkReply *reply)
{
  QVariant redirect_target = reply->attribute (QNetworkRequest::RedirectionTargetAttribute);
  if (reply->error () == QNetworkReply::NoError && ! redirect_target.isNull ()) {
    m_url = tl::to_string (redirect_target.toString ());
    s_network_manager->get (QNetworkRequest (QUrl (redirect_target.toString ())));
    delete reply;
  } else {
    mp_reply = reply;
  }
}

size_t 
InputHttpStream::read (char *b, size_t n)
{
  while (mp_reply == 0) {
    QCoreApplication::processEvents (QEventLoop::ExcludeUserInputEvents | QEventLoop::WaitForMoreEvents);
  }

  if (mp_reply->error () != QNetworkReply::NoError) {
    //  throw an error 
    std::string em = tl::to_string (mp_reply->attribute (QNetworkRequest::HttpReasonPhraseAttribute).toString ());
    int ec = mp_reply->attribute (QNetworkRequest::HttpStatusCodeAttribute).toInt ();
    if (ec == 0) {
      ec = int (mp_reply->error ());
      em = tl::to_string (QObject::tr ("Network API error"));
    }
    throw HttpErrorException (em, ec, m_url);
  }

  QByteArray data = mp_reply->read (n);
  memcpy (b, data.constData (), data.size ());
  return data.size ();
}

void 
InputHttpStream::reset ()
{
  throw tl::Exception (tl::to_string (QObject::tr ("'reset' is not supported on HTTP input streams")));
}

std::string 
InputHttpStream::filename () const
{
  return tl::to_string (QFileInfo (QUrl (tl::to_qstring (m_url)).path ()).fileName ());
}

}

