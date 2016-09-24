
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


#include "tlTimer.h"
#include "tlLog.h"
#include "tlString.h"

#ifndef _WIN32
#  include <sys/times.h>
#endif

#include <stdio.h>
#include <time.h>

#ifndef _MSC_VER // not available on MS VC++
#  include <unistd.h>
#endif

namespace tl
{

// -------------------------------------------------------------
//  Implementation of timer

Timer::Timer ()
    : m_user_ms (0), m_sys_ms (0),
      m_user_ms_res (0), m_sys_ms_res (0)
{
  // ..
}

void
Timer::start ()
{
#ifdef _WIN32
  long clks_ms = (long) ((double) clock () * (1000.0 / CLOCKS_PER_SEC) + 0.5);
  m_user_ms += clks_ms;
  //  no system time available ..
#else
  struct tms clks;
  times (&clks);
  const double clk2msec = 1000.0 / sysconf (_SC_CLK_TCK);

  m_user_ms += (long) ((clks.tms_utime + clks.tms_cutime) * clk2msec + 0.5);
  m_sys_ms += (long) ((clks.tms_stime + clks.tms_cstime) * clk2msec + 0.5);
#endif
}

void
Timer::stop ()
{
  m_user_ms = -m_user_ms;
  m_sys_ms = -m_sys_ms;
  start ();

  m_user_ms_res = m_user_ms;
  m_sys_ms_res = m_sys_ms;
  m_user_ms = 0;
  m_sys_ms = 0;
}

void
SelfTimer::report () const
{
#ifdef _WIN32
  tl::info << m_desc << ": (user) " << sec_user () << " (sys) " << sec_sys ();
#else

  unsigned long memsize = 0;
  FILE *procfile = fopen ("/proc/self/stat", "r");
  if (procfile != NULL) {
    fscanf (procfile, "%*d " // pid
                      "%*s " // comm
                      "%*c " // state
                      "%*d " // ppid
                      "%*d " // pgrp
                      "%*d " // session
                      "%*d " // tty_nr
                      "%*d " // tpgid
                      "%*u " // flags
                      "%*u " // minflt
                      "%*u " // cminflt
                      "%*u " // majflt
                      "%*u " // cmajflt
                      "%*u " // utime
                      "%*u " // stime
                      "%*d " // cutime
                      "%*d " // cstime
                      "%*d " // priority
                      "%*d " // nice
                      "%*d " // 0
                      "%*d " // itrealvalue
                      "%*u " // starttime
                      "%lu " // vsize
                      "%*d " // rss
                      "%*u " // rlim
                      "%*u " // startcode
                      "%*u " // endcode
                      "%*u " // startstack
                      "%*u " // kstkesp
                      "%*u " // kstkeip
                      "%*u " // signal
                      "%*u " // blocked
                      "%*u " // sigignore
                      "%*u " // sigcatch
                      "%*u " // wchan
                      "%*u " // nswap
                      "%*u " // cnswap
                      "%*d " // exit_signal
                      "%*d " // processor
                      "%*u " // rt_priority
                      "%*u" // policy
                      , &memsize);
    fclose (procfile);
  }

  tl::info << m_desc << ": (user) " << sec_user () 
           << " (sys) " << sec_sys () 
           << " (mem) " << tl::sprintf ("%.2fM", double (memsize) / (1024.0 * 1024.0)) 
           ;
#endif
}

// -------------------------------------------------------------
//  Implementation of timer

Clock::Clock (double s)
{
  m_clock = clock_value (s * double (CLOCKS_PER_SEC));
}

double 
Clock::seconds () const
{
  return double (m_clock) / double (CLOCKS_PER_SEC);
}

Clock
Clock::current ()
{
  Clock c;
  c.m_clock = clock ();
  return c;
}

}

