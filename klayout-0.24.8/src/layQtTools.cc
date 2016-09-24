
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


#include "layQtTools.h"
#include "tlString.h"

#include <QtGui/QDialog>
#include <QtGui/QTreeView>
#include <QtGui/QListView>
#include <QtGui/QHeaderView>
#include <QtGui/QSplitter>

#include <stdio.h>

namespace lay
{

std::string 
save_dialog_state (QWidget *w)
{
  std::string s;

  if (dynamic_cast<QDialog *> (w)) {

    s += tl::to_string (w->objectName ());
    s += "=\"";
    s += w->saveGeometry ().toBase64 ().constData ();
    s += "\";";

  } else if (dynamic_cast<QSplitter *> (w)) {

    s += tl::to_string (w->objectName ());
    s += "=\"";
    s += (dynamic_cast<QSplitter *> (w))->saveState ().toBase64 ().constData ();
    s += "\";";

  } else if (dynamic_cast<QTreeView *> (w)) {

    s += tl::to_string (w->objectName ());
    s += "=\"";
#if QT_VERSION >= 0x040500
    s += (dynamic_cast<QTreeView *> (w))->header ()->saveState ().toBase64 ().constData ();
#endif
    s += "\";";

  }

  for (QList<QObject *>::const_iterator c = w->children ().begin (); c != w->children ().end (); ++c) {
    if (dynamic_cast <QWidget *> (*c)) {
      std::string cs = save_dialog_state (dynamic_cast <QWidget *> (*c));
      if (! cs.empty ()) {
        s += cs;
      }
    }
  }

  return s;
}

void 
restore_dialog_state (QWidget *dialog, const std::string &s)
{
  tl::Extractor ex (s.c_str ());

  while (! ex.at_end ()) {

    std::string name, value;
    ex.read_word (name);
    ex.test ("=");
    ex.read_word_or_quoted (value);
    ex.test (";");

    QList<QWidget *> widgets;
    if (dialog->objectName () == tl::to_qstring (name)) {
      widgets.push_back (dialog);
    } else {
      widgets = dialog->findChildren<QWidget *>(tl::to_qstring (name));
    }

    if (widgets.size () == 1) {

      if (dynamic_cast<QDialog *> (widgets.front ())) {

        widgets.front ()->restoreGeometry (QByteArray::fromBase64 (value.c_str ()));

      } else if (dynamic_cast<QSplitter *> (widgets.front ())) {

        (dynamic_cast<QSplitter *> (widgets.front ()))->restoreState (QByteArray::fromBase64 (value.c_str ()));

      } else if (dynamic_cast<QTreeView *> (widgets.front ())) {

#if QT_VERSION >= 0x040500
        (dynamic_cast<QTreeView *> (widgets.front ()))->header ()->restoreState (QByteArray::fromBase64 (value.c_str ()));
#endif

      }


    }

  }
}

}

