
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


#include "layTechnology.h"
#include "layPlugin.h"

#include <stdio.h>

#include <QtCore/QFileInfo>
#include <QtCore/QDir>

namespace lay
{

// -----------------------------------------------------------------------------

Technologies::Technologies ()
{
  m_technologies.push_back (new Technology (std::string (""), "(Default)"));
}

Technologies::Technologies (const Technologies &other)
{
  operator= (other);
}

Technologies::~Technologies ()
{
  // .. nothing yet ..
}

Technologies &
Technologies::operator= (const Technologies &other)
{
  if (&other != this) {
    m_technologies = other.m_technologies;
    for (tl::stable_vector<Technology>::iterator t = m_technologies.begin (); t != m_technologies.end (); ++t) {
      t->add_technology_changed_observer (*this);
    }
    m_technologies_changed_observer.signal_observers ();
  }

  return *this;
}

lay::Technologies *
Technologies::instance ()
{
  static lay::Technologies s_technologies;
  return &s_technologies;
}

static tl::XMLElementList xml_elements () 
{
  return make_element ((Technologies::const_iterator (Technologies::*) () const) &Technologies::begin, (Technologies::const_iterator (Technologies::*) () const) &Technologies::end, &Technologies::add, "technology",
    Technology::xml_elements ()
  );
}

std::string 
Technologies::to_xml () const
{
  //  create a copy to filter out the ones which are not persisted
  lay::Technologies copy;
  for (const_iterator t = begin (); t != end (); ++t) {
    if (t->is_persisted ()) {
      copy.add (new Technology (*t));
    }
  }

  tl::OutputStringStream os;
  tl::XMLStruct<lay::Technologies> xml_struct ("technologies", xml_elements ());
  tl::OutputStream oss (os);
  xml_struct.write (oss, copy);
  return os.string ();
}

void 
Technologies::load_from_xml (const std::string &s)
{
  tl::XMLStringSource source (s);
  tl::XMLStruct<lay::Technologies> xml_struct ("technologies", xml_elements ());
  xml_struct.parse (source, *this);
}

void 
Technologies::add (Technology *technology)
{
  for (tl::stable_vector<Technology>::iterator t = m_technologies.begin (); technology && t != m_technologies.end (); ++t) {
    if (t->name () == technology->name ()) {
      *t = *technology;
      t->add_technology_changed_observer (*this);
      delete technology;
      technology = 0;
    }
  }

  if (technology) {
    m_technologies.push_back (technology);
    technology->add_technology_changed_observer (*this);
  }

  m_technologies_changed_observer.signal_observers ();
}

void 
Technologies::remove (const std::string &name)
{
  for (tl::stable_vector<Technology>::iterator t = m_technologies.begin (); t != m_technologies.end (); ++t) {
    if (t->name () == name) {
      m_technologies.erase (t);
      m_technologies_changed_observer.signal_observers ();
      break;
    }
  }
}

bool 
Technologies::has_technology (const std::string &name) const
{
  for (tl::stable_vector<Technology>::const_iterator t = m_technologies.begin (); t != m_technologies.end (); ++t) {
    if (t->name () == name) {
      return true;
    }
  }

  return false;
}

Technology *
Technologies::technology_by_name (const std::string &name) 
{
  for (tl::stable_vector<Technology>::iterator t = m_technologies.begin (); t != m_technologies.end (); ++t) {
    if (t->name () == name) {
      return &*t;
    }
  }

  return &*m_technologies.begin ();
}

// -----------------------------------------------------------------------------
//  Technology implementation

Technology::Technology ()
  : m_name (), m_description (), m_persisted (true)
{
  init ();
}

Technology::Technology (const std::string &name, const std::string &description)
  : m_name (name), m_description (description), m_persisted (true)
{
  init ();
}

void 
Technology::init ()
{
  m_add_other_layers = true;
  m_create_other_layers = true;

  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    if (cls->technology_component_provider () != 0) {
      m_components.push_back (cls->technology_component_provider ()->create_component ());
    }
  }
}

Technology::~Technology ()
{
  for (std::vector <TechnologyComponent *>::const_iterator c = m_components.begin (); c != m_components.end (); ++c) {
    delete *c;
  }
  m_components.clear ();
}

Technology::Technology (const Technology &d)
  : m_name (d.m_name), m_description (d.m_description), m_explicit_base_path (d.m_explicit_base_path), m_default_base_path (d.m_default_base_path), 
    m_layer_map (d.m_layer_map), m_create_other_layers (d.m_create_other_layers), 
    m_lyp_path (d.m_lyp_path), m_add_other_layers (d.m_add_other_layers), m_persisted (d.m_persisted)
{
  for (std::vector <TechnologyComponent *>::const_iterator c = d.m_components.begin (); c != d.m_components.end (); ++c) {
    m_components.push_back ((*c)->clone ());
  }
}

Technology &Technology::operator= (const Technology &d)
{
  if (this != &d) {

    m_name = d.m_name;
    m_description = d.m_description;
    m_default_base_path = d.m_default_base_path;
    m_explicit_base_path = d.m_explicit_base_path;
    m_layer_map = d.m_layer_map;
    m_create_other_layers = d.m_create_other_layers;
    m_lyp_path = d.m_lyp_path;
    m_add_other_layers = d.m_add_other_layers;
    m_persisted = d.m_persisted;

    for (std::vector <TechnologyComponent *>::const_iterator c = m_components.begin (); c != m_components.end (); ++c) {
      delete *c;
    }
    m_components.clear ();

    for (std::vector <TechnologyComponent *>::const_iterator c = d.m_components.begin (); c != d.m_components.end (); ++c) {
      m_components.push_back ((*c)->clone ());
    }

    m_technology_changed_observer.signal_observers ();
    m_technology_changed_observer.signal_observers ((void *) this);

  }

  return *this;
}

struct LayerMapStringConverter
{
  std::string to_string (const db::LayerMap &lm) const
  { 
    return lm.to_string ();
  }

  void from_string (const std::string &s, db::LayerMap &lm) const
  {
    lm = db::LayerMap::from_string (s);
  }
};

tl::XMLElementList 
Technology::xml_elements () 
{
  tl::XMLElementList elements = 
         tl::make_member (&Technology::name, &Technology::set_name, "name") + 
         tl::make_member (&Technology::description, &Technology::set_description, "description") + 
         tl::make_member (&Technology::explicit_base_path, &Technology::set_explicit_base_path, "base-path") +
         tl::make_member (&Technology::default_base_path, &Technology::set_default_base_path, "original-base-path") +
         tl::make_member (&Technology::layer_properties_file, &Technology::set_layer_properties_file, "layer-properties_file") +
         tl::make_member (&Technology::add_other_layers, &Technology::set_add_other_layers, "add-other-layers") +
         tl::make_member (&Technology::layer_map, &Technology::set_layer_map, "layer-map", LayerMapStringConverter ()) +
         tl::make_member (&Technology::create_other_layers, &Technology::set_create_other_layers, "create-other-layers") 
         ;

  for (tl::Registrar<lay::PluginDeclaration>::iterator cls = tl::Registrar<lay::PluginDeclaration>::begin (); cls != tl::Registrar<lay::PluginDeclaration>::end (); ++cls) {
    if (cls->technology_component_provider () != 0) {
      elements.append (cls->technology_component_provider ()->xml_element ());
    }
  }

  // ignore all unknown elements
  elements.append (tl::make_member<Technology> ("*")); 

  return elements;
}

const TechnologyComponent *
Technology::component_by_name (const std::string &component_name) const
{
  for (std::vector <TechnologyComponent *>::const_iterator c = m_components.begin (); c != m_components.end (); ++c) {
    if ((*c)->name () == component_name) {
      return *c;
    }
  }

  return 0;
}

std::vector <std::string> 
Technology::component_names () const
{
  std::vector <std::string> names;
  for (std::vector <TechnologyComponent *>::const_iterator c = m_components.begin (); c != m_components.end (); ++c) {
    names.push_back ((*c)->name ());
  }
  return names;
}

void
Technology::set_component (TechnologyComponent *component)
{
  for (std::vector <TechnologyComponent *>::iterator c = m_components.begin (); c != m_components.end (); ++c) {
    if ((*c)->name () == component->name ()) {
      if (*c != component) {
        delete *c;
        *c = component;
        m_technology_changed_observer.signal_observers ((void *) this);
      }
      break;
    }
  }
}

std::string 
Technology::correct_path (const std::string &fp) const
{
  if (base_path ().empty ()) {
    return fp;
  }

  QString rfp = QDir (tl::to_qstring (base_path ())).relativeFilePath (tl::to_qstring (fp));
  if (rfp.startsWith (QString::fromUtf8 (".."))) {
    //  upwards or beside - don't correct:
    return fp;
  } else {
    return tl::to_string (rfp);
  }
}

void 
Technology::load (const std::string &fn)
{
  tl::XMLFileSource source (fn);
  tl::XMLStruct<lay::Technology> xml_struct ("technology", xml_elements ());
  xml_struct.parse (source, *this);

  //  use the tech file's path as the default base path
  set_default_base_path (tl::to_string (QFileInfo (tl::to_qstring (fn)).absoluteDir ().path ()));
}

void
Technology::save (const std::string &fn) const
{
  tl::XMLStruct<lay::Technology> xml_struct ("technology", xml_elements ());
  tl::OutputStream os (fn, tl::OutputStream::OM_Plain);
  xml_struct.write (os, *this);
}

std::string 
Technology::build_effective_path (const std::string &p) const
{
  if (p.empty () || base_path ().empty ()) {
    return p;
  }

  QFileInfo f (tl::to_qstring (p));
  if (f.isAbsolute ()) {
    return p;
  } else {
    return tl::to_string (QDir (tl::to_qstring (base_path ())).filePath (tl::to_qstring (p)));
  }
}

}

