
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



#ifndef HDR_dbGDS2Reader
#define HDR_dbGDS2Reader

#include "tlException.h"
#include "tlInternational.h"
#include "tlProgress.h"
#include "tlString.h"

#include "dbLayout.h"
#include "dbGDS2ReaderBase.h"
#include "tlStream.h"
#include "dbStreamLayers.h"


namespace db
{

/**
 *  @brief Structure that holds the GDS2 specific options for the reader
 */
class KLAYOUT_DLL GDS2ReaderOptions
  : public FormatSpecificReaderOptions
{
public:
  /**
   *  @brief The constructor
   */
  GDS2ReaderOptions ()
    : box_mode (1),
      allow_big_records (true),
      allow_multi_xy_records (true)
  {
    //  .. nothing yet ..
  }

  /**
   *  @brief How to treat BOX records
   *
   *  This property specifies how to treat BOX records. 
   *  Allowed values are 0 (ignore), 1 (treat as rectangles), 2 (treat as boundaries) or 3 (treat as errors).
   */
  unsigned int box_mode; 

  /**
   *  @brief Allow multiple big records
   *
   *  Setting this property to true allows to use up to 65535 bytes (instead of 32767) per record
   *  by treating the record length as unsigned short rather than signed short.
   *  This allows bigger polygons (up to ~8000 points) without having to use multiple XY records.
   */
  bool allow_big_records;

  /**
   *  @brief Allow multiple XY records in BOUNDARY elements for unlimited large polygons
   *
   *  Setting this property to true allows to unlimited polygons 
   *  by using multiple XY records. 
   */
  bool allow_multi_xy_records;

  /** 
   *  @brief Implementation of FormatSpecificReaderOptions
   */
  virtual FormatSpecificReaderOptions *clone () const
  {
    return new GDS2ReaderOptions (*this);
  }
};

/**
 *  @brief Generic base class of GDS2 reader exceptions
 */
class KLAYOUT_DLL GDS2ReaderException
  : public ReaderException 
{
public:
  GDS2ReaderException (const std::string &msg, size_t p, size_t n, const std::string &cell)
    : ReaderException (tl::sprintf (tl::to_string (QObject::tr ("%s (position=%ld, record number=%ld, cell=%s)")), msg, p, n, cell))
  { }
};

/**
 *  @brief The GDS2 format stream reader
 */
class KLAYOUT_DLL GDS2Reader
  : public GDS2ReaderBase
{
public: 
  /**
   *  @brief Construct a stream reader object
   *
   *  @param s The stream delegate from which to read stream data from
   */
  GDS2Reader (tl::InputStream &s);

  /**  
   *  @brief Destructor
   */
  ~GDS2Reader ();

  /** 
   *  @brief The basic read method 
   *
   *  This method will read the stream data and translate this to
   *  insert calls into the layout object. This will not do much
   *  on the layout object beside inserting the objects.
   *  It can be given a couple of options specified with the
   *  LoadLayoutOptions object.
   *  The returned map will contain all layers, the passed
   *  ones and the newly created ones.
   *
   *  @param layout The layout object to write to
   *  @param options The generic reader options
   *  @return The LayerMap object that tells where which layer was loaded
   */
  virtual const LayerMap &read (db::Layout &layout, const LoadLayoutOptions &options);

  /** 
   *  @brief The basic read method (without mapping)
   *
   *  This method will read the stream data and translate this to
   *  insert calls into the layout object. This will not do much
   *  on the layout object beside inserting the objects.
   *  This version will read all input layers and return a map
   *  which tells which GDS2 layer has been read into which logical
   *  layer.
   *
   *  @param layout The layout object to write to
   *  @return The LayerMap object
   */
  virtual const LayerMap &read (db::Layout &layout);

  /**
   *  @brief Format
   */
  virtual const char *format () const { return "GDS2"; }

private:
  tl::InputStream &m_stream;
  size_t m_recnum;
  size_t m_reclen;
  size_t m_recptr;
  unsigned char *mp_rec_buf;
  tl::string m_string_buf;
  short m_stored_rec;
  db::GDS2ReaderOptions m_options;
  tl::AbsoluteProgress m_progress;

  virtual void error (const std::string &txt);
  virtual void warn (const std::string &txt);

  virtual const char *get_string ();
  virtual void get_string (tl::string &s) const;
  virtual int get_int ();
  virtual short get_short ();
  virtual unsigned short get_ushort ();
  virtual double get_double ();
  virtual short get_record ();
  virtual void unget_record (short rec_id);
  virtual void get_time (unsigned int *mod_time, unsigned int *access_time);
  virtual GDS2XY *get_xy_data (unsigned int &length);
  virtual void progress_checkpoint ();
};

}

#endif

