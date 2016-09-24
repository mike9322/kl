
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


#ifndef HDR_gsiInspector
#define HDR_gsiInspector

#include "config.h"

#include "tlVariant.h"

#include <string>

namespace gsi
{

/**
 *  @brief The inspector allows navigating the elements of a variable context
 *
 *  GSI interpreters will deliver an inspector to iterate the elements.
 *  It interfaces with the tree view of the macro editor.
 */
class KLAYOUT_DLL Inspector
{
public:
  /**
   *  @brief An enum describing the visiblity of items
   *
   *  The item's visibility controls under which circumstances an item will become visible 
   *  in the list of variables.
   */
  enum Visibility
  {
    /**
     *  @brief The entry is never visible
     */
    Never = 0,

    /**
     *  @brief The entry is visible only upon request
     */
    IfRequested = 1,

    /**
     *  @brief The item is always visible
     */
    Always = 2
  };

  /**
   *  @brief Constructor
   */
  Inspector ()
  {
    //  .. the base class implementation does nothing ..
  }

  /**
   *  @brief Destructor
   */
  virtual ~Inspector ()
  {
    //  .. the base class implementation does nothing ..
  }

  /**
   *  @brief Returns a text describing the namespace the inspector will deliver
   */
  virtual std::string description () const = 0;

  /**
   *  @brief Gets the key (name) of the element given by the index
   */
  virtual std::string key (size_t index) const = 0;
  
  /**
   *  @brief Gets the value indicating the type of the entry
   */
  virtual std::string type (size_t index) const = 0;

  /**
   *  @brief Gets the value indicating the visibility of the entry
   */
  virtual Visibility visibility (size_t index) const = 0;

  /**
   *  @brief Gets the value for the element given by the index
   *
   *  This method may throw an exception if the evaluation fails.
   */
  virtual tl::Variant value (size_t index) const = 0;

  /**
   *  @brief Returns the number of elements this inspector can deliver
   *
   *  The index values for the methods of the inspector must be between 0 and count-1.
   */
  virtual size_t count () const = 0;

  /**
   *  @brief Returns a value indicating whether the given element has children
   */
  virtual bool has_children (size_t index) const = 0;

  /**
   *  @brief Returns an inspector object for the children of the element given by index
   *
   *  The returned object must be deleted by the caller.
   */
  virtual Inspector *child_inspector (size_t index) const = 0;

  /**
   *  @brief Returns a value indicating whether the inspectors are equivalent
   *
   *  The system uses this information to determine whether to update the full variable
   *  list or just the changed information.
   */
  virtual bool equiv (const gsi::Inspector *other) const = 0;
};

}

#endif
