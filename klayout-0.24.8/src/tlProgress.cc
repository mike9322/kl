
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


#include <math.h>
#include <stdio.h>

#include "tlProgress.h"
#include "tlString.h"
#include "tlAssert.h"

#include <QtCore/QThreadStorage>
#include <QtCore/QThread>

namespace tl
{

// ---------------------------------------------------------------------------------------------
//  ProgressAdaptor implementation

ProgressAdaptor::ProgressAdaptor ()
{
  tl::Progress::register_adaptor (this);
}

ProgressAdaptor::~ProgressAdaptor ()
{
  tl::Progress::register_adaptor (0);
}

// ---------------------------------------------------------------------------------------------
//  Progress implementation

//  Hint: we don't want the QThreadStorage take ownership over the object. Hence we don't
//  store a pointer but a pointer to a pointer.
static QThreadStorage<ProgressAdaptor **> s_thread_data;

Progress::Progress (const std::string &desc, size_t yield_interval)
  : m_desc (desc), m_title (desc),
    m_interval_count (0), 
    m_yield_interval (yield_interval), 
    m_last_value (-1.0),
    m_can_cancel (true),
    m_cancelled (false)
{
  ProgressAdaptor *a = adaptor ();
  if (a) {
    a->register_object (this);
  }
}

Progress::~Progress ()
{
  ProgressAdaptor *a = adaptor ();
  if (a) {
    a->unregister_object (this);
  }
}

void 
Progress::register_adaptor (ProgressAdaptor *pa)
{
  tl_assert (adaptor () == 0 || pa == 0);
  s_thread_data.setLocalData (new (ProgressAdaptor *) (pa));
}

ProgressAdaptor *
Progress::adaptor () 
{
  if (! s_thread_data.hasLocalData ()) {
    return 0;
  } else {
    return *s_thread_data.localData ();
  }
}

void 
Progress::signal_break ()
{
  m_cancelled = true;
}

void
Progress::set_desc (const std::string &d)
{
  ProgressAdaptor *a = adaptor ();
  if (a && d != m_desc) {

    m_desc = d;
    a->trigger (this);
    a->yield (this);

    if (m_cancelled) {
      m_cancelled = false;
      throw tl::BreakException ();
    }

  }

}

void
Progress::test (bool force_yield)
{
  if (++m_interval_count >= m_yield_interval || force_yield) {

    ProgressAdaptor *a = adaptor ();

    bool needs_trigger = false;
    double v = value ();
    if (fabs (v - m_last_value) > 1e-6) {
      m_last_value = v;
      needs_trigger = true;
    }

    m_interval_count = 0;

    if (a) {
      tl::Clock now = tl::Clock::current ();
      if ((now - m_last_yield).seconds () > 0.1) {
        m_last_yield = now;
        if (needs_trigger) {
          a->trigger (this);
        }
        a->yield (this);
      }
    }

    if (m_cancelled) {
      m_cancelled = false;
      throw tl::BreakException ();
    }

  }
}

// ---------------------------------------------------------------------------------------------
//  Progress implementation

RelativeProgress::RelativeProgress (const std::string &desc, size_t max_count, size_t yield_interval)
  : Progress (desc, yield_interval)
{
  m_format = "%.0f%%";
  m_unit = double (max_count) / 100.0;
  m_count = 0;
}

double
RelativeProgress::value () const
{
  return double (m_count) / m_unit;
}

std::string 
RelativeProgress::formatted_value () const
{
  double v = double (m_count) / m_unit; 
  return tl::sprintf (m_format, v);
}

RelativeProgress &
RelativeProgress::set (size_t count, bool force_yield)
{
  m_count = count;
  test (force_yield);
  return *this;
}

// ---------------------------------------------------------------------------------------------
//  Progress implementation

AbsoluteProgress::AbsoluteProgress (const std::string &desc, size_t yield_interval)
  : Progress (desc, yield_interval)
{
  m_format = "%.0f";
  m_res = 1.0;
  m_unit = 1.0;
  m_format_unit = 0.0;
  m_count = 0;
}

double
AbsoluteProgress::value () const
{
  return double (m_count) / m_unit;
}

std::string 
AbsoluteProgress::formatted_value () const
{
  double v = double (m_count) / (m_format_unit > 0 ? m_format_unit : m_unit); 
  return tl::sprintf (m_format, v);
}

AbsoluteProgress &
AbsoluteProgress::set (size_t count, bool force_yield)
{
  m_count = count;
  test ();
  return *this;
}

} // namespace tl


