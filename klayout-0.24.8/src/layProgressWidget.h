
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


#ifndef HDR_layProgressWidget
#define HDR_layProgressWidget

#include <QtGui/QFrame>
#include <QtGui/QToolButton>
#include <QtGui/QLabel>
#include <QtGui/QPainter>
#include <QtGui/QHBoxLayout>

#include "layProgress.h"

class QToolButton;
class QLabel;
class QToolButton;

namespace lay
{

class ProgressBarWidget;

class ProgressWidget
  : public QFrame
{
Q_OBJECT

public:
  ProgressWidget (ProgressReporter *pr, QWidget *parent, bool full_width = false);

  void set_text (const std::string &text);
  void set_value (double v, const std::string &value);
  void set_can_cancel (bool f);

  QSize sizeHint () const;

public slots:
  void signal_break ();

private:
  QLabel *mp_label;
  ProgressBarWidget *mp_progress_bar;
  QToolButton *mp_cancel_button;
  ProgressReporter *mp_pr;
};

}

#endif

