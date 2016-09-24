
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


#ifndef HDR_tlGlobPattern
#define HDR_tlGlobPattern

#include <string>
#include <vector>

#include "config.h"

namespace tl
{

/** 
 *  @brief A class representing a glob pattern 
 */

class KLAYOUT_DLL GlobPattern
{
public:
  /**
   *  @brief The default constructor
   */
  GlobPattern ();

  /**
   *  @brief The constructor
   *
   *  Creates a glob pattern form the given string
   */
  GlobPattern (const std::string &p);

  /**
   *  @brief Assignment of a string
   */
  GlobPattern &operator= (const std::string &p)
  {
    m_p = p;
    return *this;
  }

  /**
   *  @brief Get the pattern string
   */
  const std::string &pattern () const
  {
    return m_p;
  }

  /**
   *  @brief Match the given string 
   *
   *  Returns true, if the given subject string matches the glob pattern 
   */
  bool match (const std::string &s) const;

  /**
   *  @brief Match the given string and extract the bracket expressions into the vector of substrings
   */
  bool match (const std::string &s, std::vector<std::string> &e) const;

  /**
   *  @brief Match the given string 
   *
   *  Returns true, if the given subject string matches the glob pattern 
   */
  bool match (const char *s) const;

  /**
   *  @brief Match the given string and extract the bracket expressions into the vector of substrings
   */
  bool match (const char *s, std::vector<std::string> &e) const;

private:
  std::string m_p;
};

} // namespace tl

#endif

