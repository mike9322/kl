
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


#include "layPlugin.h"
#include "layMainWindow.h"
#include "layAbstractMenu.h"
#include "layConverters.h"
#include "layConfigurationDialog.h"
#include "antConfigPage.h"
#include "antConfig.h"
#include "antPlugin.h"

namespace ant
{

PluginDeclaration::PluginDeclaration ()
  : m_current_template (0), mp_main_window (0),
    m_current_template_updated (true), m_templates_updated (true)
{
  // .. nothing yet ..
}

PluginDeclaration::~PluginDeclaration ()
{
  // .. nothing yet ..
}

void 
PluginDeclaration::get_options (std::vector < std::pair<std::string, std::string> > &options) const
{
  options.push_back (std::pair<std::string, std::string> (cfg_max_number_of_rulers, "-1"));
  options.push_back (std::pair<std::string, std::string> (cfg_ruler_snap_range, "8"));
  options.push_back (std::pair<std::string, std::string> (cfg_ruler_color, lay::ColorConverter ().to_string (QColor ())));
  options.push_back (std::pair<std::string, std::string> (cfg_ruler_halo, "true"));
  options.push_back (std::pair<std::string, std::string> (cfg_ruler_snap_mode, ACConverter ().to_string (lay::AC_Any)));
  options.push_back (std::pair<std::string, std::string> (cfg_ruler_obj_snap, tl::to_string (true)));
  options.push_back (std::pair<std::string, std::string> (cfg_ruler_grid_snap, tl::to_string (false)));
  options.push_back (std::pair<std::string, std::string> (cfg_ruler_templates, ""));
  options.push_back (std::pair<std::string, std::string> (cfg_current_ruler_template, "0"));
  //  grid-micron is not configured here since some other entity is supposed to do this.
}

std::vector<std::pair <std::string, lay::ConfigPage *> > 
PluginDeclaration::config_pages (QWidget *parent) const 
{
  std::vector<std::pair <std::string, lay::ConfigPage *> > pages;
  pages.push_back (std::make_pair (tl::to_string (QObject::tr ("Rulers And Annotations|Snapping")), new ant::ConfigPage (parent)));
  pages.push_back (std::make_pair (tl::to_string (QObject::tr ("Rulers And Annotations|Appearance")), new ant::ConfigPage2 (parent)));
  pages.push_back (std::make_pair (tl::to_string (QObject::tr ("Rulers And Annotations|Angle")), new ant::ConfigPage3 (parent)));
  pages.push_back (std::make_pair (tl::to_string (QObject::tr ("Rulers And Annotations|Templates")), new ant::ConfigPage4 (parent)));
  return pages;
}

void 
PluginDeclaration::get_menu_entries (std::vector<lay::MenuEntry> &menu_entries) const
{
  lay::PluginDeclaration::get_menu_entries (menu_entries);
  menu_entries.push_back (lay::MenuEntry ("rulers_group", "edit_menu.end"));
  menu_entries.push_back (lay::MenuEntry ("ant::clear_all_rulers", "clear_all_rulers:edit", "edit_menu.end", tl::to_string (QObject::tr ("Clear All Rulers And Annotations(Ctrl+K)"))));
  menu_entries.push_back (lay::MenuEntry ("ant::configure", "configure_rulers", "edit_menu.end", tl::to_string (QObject::tr ("Ruler And Annotation Setup"))));
}

lay::Plugin *
PluginDeclaration::create_plugin (db::Manager *manager, lay::MainWindow *, lay::LayoutView *view) const
{
  return new ant::Service (manager, view);
}

bool 
PluginDeclaration::menu_activated (const std::string &symbol) const
{
  if (symbol == "ant::configure") {

    lay::ConfigurationDialog config_dialog (lay::MainWindow::instance (), lay::MainWindow::instance (), "ant::Plugin");
    config_dialog.exec ();
    
    return true;

  } else {
    return lay::PluginDeclaration::menu_activated (symbol);
  }
}

bool 
PluginDeclaration::implements_editable (std::string &title) const
{
  title = tl::to_string (QObject::tr ("Rulers And Annotations"));
  return true;
}

bool 
PluginDeclaration::implements_mouse_mode (std::string &title) const
{
  title = "ruler:ruler_mode_group:ruler_templates_group\t" + tl::to_string (QObject::tr ("Ruler{Add rulers and annotations}")) + "<:ruler.png>";
  return true;
}

bool 
PluginDeclaration::configure (const std::string &name, const std::string &value)
{
  if (name == cfg_ruler_templates) {

    m_templates = ant::Template::from_string (value);
    m_templates_updated = true;
    
  } else if (name == cfg_current_ruler_template) {
    
    int n = 0;
    tl::from_string (value, n);
    
    if (n != m_current_template) {
      m_current_template = n;
      m_current_template_updated = true;
    }
    
  }
  return false;
}

void 
PluginDeclaration::config_finalize ()
{
  if (mp_main_window) {

    if (m_templates_updated) {

      update_menu (mp_main_window);
      m_templates_updated = false;
      m_current_template_updated = false;

    } else if (m_current_template_updated) {

      update_current_template (mp_main_window);
      m_current_template_updated = false;

    }

  }
}

void 
PluginDeclaration::initialize (lay::MainWindow *mw)
{
  mp_main_window = mw;
}

void 
PluginDeclaration::uninitialize (lay::MainWindow *)
{
  for (std::vector<lay::Action *>::iterator a = m_actions.begin (); a != m_actions.end (); ++a) {
    delete *a;
  }
  m_actions.clear ();

  mp_main_window = 0;
}

void 
PluginDeclaration::update_current_template (lay::MainWindow *mw)
{
  if (m_current_template >= 0 && m_current_template < int (m_templates.size ())) {

    std::vector<std::string> menu_entries = mw->menu ().group ("ruler_mode_group");
    for (std::vector<std::string>::const_iterator m = menu_entries.begin (); m != menu_entries.end (); ++m) {
      lay::Action action = mw->menu ().action (*m);
      action.set_title (m_templates [m_current_template].title ());
    }
    
    if (m_templates.size () > 1) {
      int it = 0;
      for (std::vector<Template>::const_iterator tt = m_templates.begin (); tt != m_templates.end () && it < int (m_actions.size ()); ++tt, ++it) {
        m_actions[it]->set_checked (it == m_current_template);
      }
    }

  }
}

void 
PluginDeclaration::update_menu (lay::MainWindow *mw)
{
  if (m_templates.empty ()) {
    m_templates.push_back (Template ());
  }

  if (m_current_template < 0 || m_current_template >= int (m_templates.size ())) {
    m_current_template = 0;
  }
    
  std::vector<std::string> menu_entries = mw->menu ().group ("ruler_mode_group");
  for (std::vector<std::string>::const_iterator m = menu_entries.begin (); m != menu_entries.end (); ++m) {
    lay::Action action = mw->menu ().action (*m);
    action.set_title (m_templates [m_current_template].title ());
  }
  
  std::vector<std::string> tmpl_group = mw->menu ().group ("ruler_templates_group");
  for (std::vector<std::string>::const_iterator t = tmpl_group.begin (); t != tmpl_group.end (); ++t) {
    std::vector<std::string> items = mw->menu ().items (*t);        
    for (std::vector<std::string>::const_iterator i = items.begin (); i != items.end (); ++i) {
      mw->menu ().delete_item (*i);
    }
  }
    
  for (std::vector<lay::Action *>::iterator a = m_actions.begin (); a != m_actions.end (); ++a) {
    delete *a;
  }
  m_actions.clear ();

  if (m_templates.size () > 1) {
    int it = 0;
    for (std::vector<Template>::const_iterator tt = m_templates.begin (); tt != m_templates.end (); ++tt, ++it) {
      m_actions.push_back (mp_main_window->create_config_action (tt->title (), cfg_current_ruler_template, tl::to_string (it)));
      m_actions.back ()->set_checkable (true);
      m_actions.back ()->set_checked (it == m_current_template);
      for (std::vector<std::string>::const_iterator t = tmpl_group.begin (); t != tmpl_group.end (); ++t) {
        mw->menu ().insert_item (*t + ".end", "ruler_template_" + tl::to_string (it), *m_actions.back ());
      }
    }
  }
    
}

static tl::RegisteredClass<lay::PluginDeclaration> config_decl (new ant::PluginDeclaration (), 3000, "ant::Plugin");

}

