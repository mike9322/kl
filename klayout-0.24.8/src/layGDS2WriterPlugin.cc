
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


#include "dbGDS2.h"
#include "dbGDS2Writer.h"
#include "dbSaveLayoutOptions.h"
#include "layMainWindow.h"
#include "layCellView.h"
#include "layGDS2WriterPlugin.h"
#include "GDS2WriterOptionPage.h"
#include "gsiDecl.h"

#include <QtGui/QFrame>

namespace lay
{

const std::string cfg_gds2_write_timestamps ("gds2-write-timestamps");
const std::string cfg_gds2_write_cell_properties ("gds2-write-cell-properties");
const std::string cfg_gds2_write_file_properties ("gds2-write-file-properties");
const std::string cfg_gds2_no_zero_length_paths ("gds2-no-zero-length-paths");
const std::string cfg_gds2_multi_xy_records ("gds2-multi-xy-records");
const std::string cfg_gds2_max_vertex_count ("gds2-max-vertex-count");
const std::string cfg_gds2_max_cellname_length ("gds2-max-cellname-length");
const std::string cfg_gds2_libname ("gds2-libname");

// ---------------------------------------------------------------
//  GDS2WriterOptionPage definition and implementation

GDS2WriterOptionPage::GDS2WriterOptionPage (QWidget *parent)
  : StreamWriterOptionsPage (parent)
{
  mp_ui = new Ui::GDS2WriterOptionPage ();
  mp_ui->setupUi (this);

  connect (mp_ui->multi_xy_cbx, SIGNAL (clicked ()), this, SLOT (multi_xy_clicked ()));
}

GDS2WriterOptionPage::~GDS2WriterOptionPage ()
{
  delete mp_ui;
  mp_ui = 0;
}

void 
GDS2WriterOptionPage::setup (const db::FormatSpecificWriterOptions *o)
{
  const db::GDS2WriterOptions *options = dynamic_cast<const db::GDS2WriterOptions *> (o);
  if (options) {
    mp_ui->write_timestamps->setChecked (options->write_timestamps);
    mp_ui->write_cell_properties->setChecked (options->write_cell_properties);
    mp_ui->write_file_properties->setChecked (options->write_file_properties);
    mp_ui->no_zero_length_paths->setChecked (options->no_zero_length_paths);
    mp_ui->multi_xy_cbx->setChecked (options->multi_xy_records);
    mp_ui->max_vertex_le->setEnabled (! options->multi_xy_records);
    mp_ui->max_vertex_le->setText (tl::to_qstring (tl::to_string (options->max_vertex_count)));
    mp_ui->cell_name_length_le->setText (tl::to_qstring (tl::to_string (options->max_cellname_length)));
    mp_ui->libname_le->setText (tl::to_qstring (tl::to_string (options->libname)));
  }
}

void 
GDS2WriterOptionPage::commit (db::FormatSpecificWriterOptions *o, bool gzip)
{
  db::GDS2WriterOptions *options = dynamic_cast<db::GDS2WriterOptions *> (o);
  if (options) {

    unsigned int n;
    options->multi_xy_records = mp_ui->multi_xy_cbx->isChecked ();
    options->write_timestamps = mp_ui->write_timestamps->isChecked ();
    options->write_cell_properties = mp_ui->write_cell_properties->isChecked ();
    options->write_file_properties = mp_ui->write_file_properties->isChecked ();
    options->no_zero_length_paths = mp_ui->no_zero_length_paths->isChecked ();

    tl::from_string (tl::to_string (mp_ui->max_vertex_le->text ()), n);
    if (! options->multi_xy_records) {
      if (n > 8191) {
        throw tl::Exception (tl::to_string (QObject::tr ("Maximum number of vertices must not exceed 8191")));
      }
      if (n < 4) {
        throw tl::Exception (tl::to_string (QObject::tr ("Maximum number of vertices must be 4 at least")));
      }
    }
    options->max_vertex_count = n;

    n = 32000;
    tl::from_string (tl::to_string (mp_ui->cell_name_length_le->text ()), n);
    if (n > 32000) {
      throw tl::Exception (tl::to_string (QObject::tr ("Maximum cell name length must not exceed 32000")));
    }
    if (n < 8) {
      throw tl::Exception (tl::to_string (QObject::tr ("Maximum cell name length must be 8 at least")));
    }
    options->max_cellname_length = n;

    options->libname = tl::to_string (mp_ui->libname_le->text ());

  }
}

void 
GDS2WriterOptionPage::multi_xy_clicked ()
{
  mp_ui->max_vertex_le->setEnabled (! mp_ui->multi_xy_cbx->isChecked ());
}

// ---------------------------------------------------------------
//  GDS2WriterPluginDeclaration definition and implementation

class GDS2WriterPluginDeclaration
  : public StreamWriterPluginDeclaration
{
public:
  GDS2WriterPluginDeclaration (const char *format_name) 
    : StreamWriterPluginDeclaration (format_name)
  {
    // .. nothing yet ..
  }

  StreamWriterOptionsPage *format_specific_options_page (QWidget *parent) const
  {
    return new GDS2WriterOptionPage (parent);
  }

  void get_options (std::vector < std::pair<std::string, std::string> > &options) const
  {
    db::GDS2WriterOptions m_options;
    options.push_back (std::make_pair (cfg_gds2_write_timestamps, tl::to_string (m_options.write_timestamps)));
    options.push_back (std::make_pair (cfg_gds2_write_cell_properties, tl::to_string (m_options.write_cell_properties)));
    options.push_back (std::make_pair (cfg_gds2_write_file_properties, tl::to_string (m_options.write_file_properties)));
    options.push_back (std::make_pair (cfg_gds2_no_zero_length_paths, tl::to_string (m_options.no_zero_length_paths)));
    options.push_back (std::make_pair (cfg_gds2_multi_xy_records, tl::to_string (m_options.multi_xy_records)));
    options.push_back (std::make_pair (cfg_gds2_max_vertex_count, tl::to_string (m_options.max_vertex_count)));
    options.push_back (std::make_pair (cfg_gds2_max_cellname_length, tl::to_string (m_options.max_cellname_length)));
    options.push_back (std::make_pair (cfg_gds2_libname, tl::to_string (m_options.libname)));
  }

  db::FormatSpecificWriterOptions *create_specific_options (lay::PluginRoot *config_root) const
  {
    db::GDS2WriterOptions *options = new db::GDS2WriterOptions ();

    //  no initialization if config_root is not set.
    if (config_root) {
      try {
        config_root->config_get (cfg_gds2_write_timestamps, options->write_timestamps);
        config_root->config_get (cfg_gds2_write_cell_properties, options->write_cell_properties);
        config_root->config_get (cfg_gds2_write_file_properties, options->write_file_properties);
        config_root->config_get (cfg_gds2_no_zero_length_paths, options->no_zero_length_paths);
        config_root->config_get (cfg_gds2_multi_xy_records, options->multi_xy_records);
        config_root->config_get (cfg_gds2_max_vertex_count, options->max_vertex_count);
        config_root->config_get (cfg_gds2_max_cellname_length, options->max_cellname_length);
        config_root->config_get (cfg_gds2_libname, options->libname);
      } catch (...) {
        delete options;
        throw;
      }
    }

    return options;
  }

  void commit_to_config (const db::FormatSpecificWriterOptions *o, lay::PluginRoot *config_root) const 
  {
    const db::GDS2WriterOptions *options = dynamic_cast<const db::GDS2WriterOptions *> (o);
    if (options) {
      config_root->config_set (cfg_gds2_write_timestamps, options->write_timestamps);
      config_root->config_set (cfg_gds2_write_cell_properties, options->write_cell_properties);
      config_root->config_set (cfg_gds2_write_file_properties, options->write_file_properties);
      config_root->config_set (cfg_gds2_no_zero_length_paths, options->no_zero_length_paths);
      config_root->config_set (cfg_gds2_multi_xy_records, options->multi_xy_records);
      config_root->config_set (cfg_gds2_max_vertex_count, options->max_vertex_count);
      config_root->config_set (cfg_gds2_max_cellname_length, options->max_cellname_length);
      config_root->config_set (cfg_gds2_libname, options->libname);
    }
  }

  void initialize_options_from_layout_handle (db::FormatSpecificWriterOptions *o, const lay::LayoutHandle &lh) const
  {
    //  Initialize the libname property from meta data with key "libname".
    db::GDS2WriterOptions *options = dynamic_cast<db::GDS2WriterOptions *> (o);
    if (options) {
      for (lay::LayoutHandle::meta_info_iterator meta = lh.begin_meta (); meta != lh.end_meta (); ++meta) {
        if (meta->name == "libname" && !meta->value.empty ()) {
          options->libname = meta->value;
        }
      }
    }
  }
};

//  register the same options and property pages to GDS2Text that for GDS2
//  (although the limitations do not exist for GDS2Text)
static tl::RegisteredClass<lay::PluginDeclaration> plugin_decl1 (new lay::GDS2WriterPluginDeclaration ("GDS2"), 10000, "GDS2Writer");
static tl::RegisteredClass<lay::PluginDeclaration> plugin_decl2 (new lay::GDS2WriterPluginDeclaration ("GDS2Text"), 10001, "GDS2TextWriter");

// ---------------------------------------------------------------
//  gsi Implementation of specific methods

static void get_gds2_options (const db::SaveLayoutOptions *options, db::GDS2WriterOptions &gds2_options)
{
  const db::GDS2WriterOptions *current_gds2_options = dynamic_cast <const db::GDS2WriterOptions *> (options->get_specific_options ());
  if (current_gds2_options) {
    gds2_options = *current_gds2_options;
  }
}

static void set_gds2_max_vertex_count (db::SaveLayoutOptions *options, unsigned int n)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  gds2_options.max_vertex_count = n;
  options->set_specific_options (gds2_options);
}

static unsigned int get_gds2_max_vertex_count (const db::SaveLayoutOptions *options)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  return gds2_options.max_vertex_count;
}

static void set_gds2_max_cellname_length (db::SaveLayoutOptions *options, unsigned int n)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  gds2_options.max_cellname_length = n;
  options->set_specific_options (gds2_options);
}

static unsigned int get_gds2_max_cellname_length (const db::SaveLayoutOptions *options)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  return gds2_options.max_cellname_length;
}

static void set_gds2_multi_xy_records (db::SaveLayoutOptions *options, bool n)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  gds2_options.multi_xy_records = n;
  options->set_specific_options (gds2_options);
}

static bool get_gds2_multi_xy_records (const db::SaveLayoutOptions *options)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  return gds2_options.multi_xy_records;
}

static void set_gds2_write_file_properties (db::SaveLayoutOptions *options, bool n)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  gds2_options.write_file_properties = n;
  options->set_specific_options (gds2_options);
}

static bool get_gds2_write_file_properties (const db::SaveLayoutOptions *options)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  return gds2_options.write_file_properties;
}

static void set_gds2_write_cell_properties (db::SaveLayoutOptions *options, bool n)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  gds2_options.write_cell_properties = n;
  options->set_specific_options (gds2_options);
}

static bool get_gds2_write_cell_properties (const db::SaveLayoutOptions *options)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  return gds2_options.write_cell_properties;
}

static void set_gds2_no_zero_length_paths (db::SaveLayoutOptions *options, bool n)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  gds2_options.no_zero_length_paths = n;
  options->set_specific_options (gds2_options);
}

static bool get_gds2_no_zero_length_paths (const db::SaveLayoutOptions *options)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  return gds2_options.no_zero_length_paths;
}

static void set_gds2_write_timestamps (db::SaveLayoutOptions *options, bool n)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  gds2_options.write_timestamps = n;
  options->set_specific_options (gds2_options);
}

static bool get_gds2_write_timestamps (const db::SaveLayoutOptions *options)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  return gds2_options.write_timestamps;
}

static void set_gds2_libname (db::SaveLayoutOptions *options, const std::string &n)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  gds2_options.libname = n;
  options->set_specific_options (gds2_options);
}

static std::string get_gds2_libname (const db::SaveLayoutOptions *options)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  return gds2_options.libname;
}

static void set_gds2_user_units (db::SaveLayoutOptions *options, double n)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  gds2_options.user_units = n;
  options->set_specific_options (gds2_options);
}

static double get_gds2_user_units (const db::SaveLayoutOptions *options)
{
  db::GDS2WriterOptions gds2_options;
  get_gds2_options (options, gds2_options);
  return gds2_options.user_units;
}

//  extend lay::SaveLayoutOptions with the GDS2 options 
static
gsi::ClassExt<db::SaveLayoutOptions> gds2_writer_options (
  gsi::method_ext ("gds2_max_vertex_count=", &set_gds2_max_vertex_count,
    "@brief Set the maximum number of vertices for polygons to write\n"
    "@args count\n"
    "This property describes the maximum number of point for polygons in GDS2 files.\n"
    "Polygons with more points will be split.\n"
    "The minimum value for this property is 4. The maximum allowed value is about 4000 or 8000, depending on the\n"
    "GDS2 interpretation. If \\gds2_multi_xy_records is true, this\n"
    "property is not used. Instead, the number of points is unlimited.\n"
    "\nThis property has been added in version 0.18.\n"
  ) +
  gsi::method_ext ("gds2_max_vertex_count", &get_gds2_max_vertex_count,
    "@brief Get the maximum number of vertices for polygons to write\n"
    "See \\gds2_max_vertex_count= method for a description of the maximum vertex count."
    "\nThis property has been added in version 0.18.\n"
  ) +
  gsi::method_ext ("gds2_multi_xy_records=", &set_gds2_multi_xy_records,
    "@brief Use multiple XY records in BOUNDARY elements for unlimited large polygons\n"
    "@args flag\n"
    "\n"
    "Setting this property to true allows to produce unlimited polygons \n"
    "at the cost of incompatible formats. Setting it to true disables the \\gds2_max_vertex_count setting.\n"
    "\nThis property has been added in version 0.18.\n"
  ) +
  gsi::method_ext ("gds2_multi_xy_records?", &get_gds2_multi_xy_records,
    "@brief Get the property enabling multiple XY records for BOUNDARY elements\n"
    "See \\gds2_multi_xy_records= method for a description of this property."
    "\nThis property has been added in version 0.18.\n"
  ) +
  gsi::method_ext ("gds2_write_timestamps=", &set_gds2_write_timestamps,
    "@brief Write the current time into the GDS2 timestamps if set to true\n"
    "@args flag\n"
    "\n"
    "If this property is set to false, the time fields will all be zero. This somewhat simplifies compare and diff "
    "applications.\n"
    "\n"
    "\nThis property has been added in version 0.21.16.\n"
  ) +
  gsi::method_ext ("gds2_write_timestamps?", &get_gds2_write_timestamps,
    "@brief Gets a value indicating whether the current time is written into the GDS2 timestamp fields\n"
    "\nThis property has been added in version 0.21.16.\n"
  ) +
  gsi::method_ext ("gds2_no_zero_length_paths=", &set_gds2_no_zero_length_paths,
    "@brief Eliminates zero-length paths if true\n"
    "@args flag\n"
    "\n"
    "If this property is set to true, paths with zero length will be converted to BOUNDARY objects.\n"
    "\n"
    "\nThis property has been added in version 0.23.\n"
  ) +
  gsi::method_ext ("gds2_no_zero_length_paths?|#gds2_no_zero_length_paths", &get_gds2_no_zero_length_paths,
    "@brief Gets a value indicating whether zero-length paths are eliminated\n"
    "\nThis property has been added in version 0.23.\n"
  ) +
  gsi::method_ext ("gds2_write_cell_properties=", &set_gds2_write_cell_properties,
    "@brief Enables writing of cell properties if set to true\n"
    "@args flag\n"
    "\n"
    "If this property is set to true, cell properties will be written as PROPATTR/PROPVALUE records immediately "
    "following the BGNSTR records. This is a non-standard extension and is therefore disabled by default.\n"
    "\n"
    "\nThis property has been added in version 0.23.\n"
  ) +
  gsi::method_ext ("gds2_write_cell_properties?|#gds2_write_cell_properties", &get_gds2_write_cell_properties,
    "@brief Gets a value indicating whether cell properties are written\n"
    "\nThis property has been added in version 0.23.\n"
  ) +
  gsi::method_ext ("gds2_write_file_properties=", &set_gds2_write_file_properties,
    "@brief Enables writing of file properties if set to true\n"
    "@args flag\n"
    "\n"
    "If this property is set to true, layout properties will be written as PROPATTR/PROPVALUE records immediately "
    "following the BGNLIB records. This is a non-standard extension and is therefore disabled by default.\n"
    "\n"
    "\nThis property has been added in version 0.24.\n"
  ) +
  gsi::method_ext ("gds2_write_file_properties?|#gds2_write_file_properties", &get_gds2_write_file_properties,
    "@brief Gets a value indicating whether layout properties are written\n"
    "\nThis property has been added in version 0.24.\n"
  ) +
  gsi::method_ext ("gds2_max_cellname_length=", &set_gds2_max_cellname_length,
    "@brief Maximum length of cell names\n"
    "@args length\n"
    "\n"
    "This property describes the maximum number of characters for cell names. \n"
    "Longer cell names will be shortened.\n"
    "\nThis property has been added in version 0.18.\n"
  ) +
  gsi::method_ext ("gds2_max_cellname_length", &get_gds2_max_cellname_length,
    "@brief Get the maximum length of cell names\n"
    "See \\gds2_max_cellname_length= method for a description of the maximum cell name length."
    "\nThis property has been added in version 0.18.\n"
  ) +
  gsi::method_ext ("gds2_libname=", &set_gds2_libname,
    "@brief Set the library name\n"
    "@args libname\n"
    "\n"
    "The library name is the string written into the LIBNAME records of the GDS file.\n"
    "The library name should not be an empty string and is subject to certain limitations in the character choice.\n"
    "\nThis property has been added in version 0.18.\n"
  ) +
  gsi::method_ext ("gds2_libname", &get_gds2_libname,
    "@brief Get the library name\n"
    "See \\gds2_libname= method for a description of the library name."
    "\nThis property has been added in version 0.18.\n"
  ) +
  gsi::method_ext ("gds2_user_units=", &set_gds2_user_units,
    "@brief Set the users units to write into the GDS file\n"
    "@args uu\n"
    "\n"
    "The user units of a GDS file are rarely used and usually are set to 1 (micron).\n"
    "The intention of the user units is to specify the display units. KLayout ignores the user unit and uses microns as the display unit.\n"
    "The user unit must be larger than zero.\n"
    "\nThis property has been added in version 0.18.\n"
  ) +
  gsi::method_ext ("gds2_user_units", &get_gds2_user_units,
    "@brief Get the user units\n"
    "See \\gds2_user_units= method for a description of the user units."
    "\nThis property has been added in version 0.18.\n"
  ),
  ""
);

}


