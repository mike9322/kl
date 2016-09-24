
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


#include "dbCIF.h"
#include "dbCIFReader.h"
#include "dbCIFWriter.h"
#include "dbStream.h"

#include "tlClassRegistry.h"

namespace db
{

// ---------------------------------------------------------------
//  CIFDiagnostics implementation

CIFDiagnostics::~CIFDiagnostics ()
{
  //  .. nothing yet ..
}

// ---------------------------------------------------------------
//  CIF format declaration

class CIFFormatDeclaration
  : public db::StreamFormatDeclaration
{
public:
  CIFFormatDeclaration ()
  {
    //  .. nothing yet ..
  }

  virtual std::string format_name () const { return "CIF"; }
  virtual std::string format_desc () const { return "CIF stream format"; }
  virtual std::string file_format () const { return "CIF files (*.CIF *.cif *.cif.gz *.CIF.gz)"; }

  virtual bool detect (tl::InputStream &s) const 
  {
    try {

      //  analyze the first 4000 characters - this is within the initial block read
      //  by the stream and won't trigger a reset of the stream which is not available
      //  on some sources.
      std::string head = s.read_all (4000);
      int n = 0;

      tl::Extractor ex (head.c_str ());
      while (! ex.at_end ()) {

        if (ex.test ("(")) {

          //  read over comments
          int bl = 0;
          while (! ex.at_end () && (*ex != ')' || bl > 0)) {
            //  check for nested comments (bl is the nesting level)
            if (*ex == '(') {
              ++bl;
            } else if (*ex == ')') {
              --bl;
            }
            ++ex;
          }
          if (! ex.at_end ()) {
            ++ex;
          }

        } else if (ex.test (";")) {

          //  ignore ;

        } else if ((ex.test ("DS ") && ex.try_read (n)) || ex.test ("L ")) {

          //  first command must be "DS num", "L"
          return true;

        } else if (ex.test ("9")) {

          //  read over 9...; commands
          while (! ex.at_end () && *ex != ';') {
            ++ex;
          }
          if (! ex.at_end ()) {
            ++ex;
          }

        } else {
          break;
        }

      }

    } catch (...) {
      //  ignore errors
    }

    return false;
  }

  virtual ReaderBase *create_reader (tl::InputStream &s) const 
  {
    return new db::CIFReader (s);
  }

  virtual WriterBase *create_writer () const
  {
    return new db::CIFWriter ();
  }

  virtual bool can_read () const
  {
    return true;
  }

  virtual bool can_write () const
  {
    return true;
  }
};

static tl::RegisteredClass<db::StreamFormatDeclaration> reader_decl (new CIFFormatDeclaration (), 100, "CIF");

//  provide a symbol to force linking against
int force_link_CIF = 0;

}


