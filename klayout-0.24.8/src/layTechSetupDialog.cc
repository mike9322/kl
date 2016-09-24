
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


#include "layTechSetupDialog.h"
#include "layTechnology.h"
#include "layExceptions.h"
#include "layFileDialog.h"
#include "layTipDialog.h"
#include "layMainWindow.h"
#include "layApplication.h"
#include "layMacroEditorTree.h"
#include "layMacro.h"
#include "tlAssert.h"
#include "tlStream.h"

#include <QtGui/QInputDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QHeaderView>
#include <QtGui/QFileDialog>

#include <stdio.h>
#include <fstream>

namespace lay
{

// ----------------------------------------------------------------
//  TechBaseEditorPage implementation

TechBaseEditorPage::TechBaseEditorPage (QWidget *parent)
  : TechnologyComponentEditor (parent)
{
  Ui::TechBaseEditorPage::setupUi (this);

  // .. nothing yet ..
}

void 
TechBaseEditorPage::setup ()
{
  name_le->setText (tl::to_qstring (tech ()->name ()));
  desc_le->setText (tl::to_qstring (tech ()->description ()));
  desc_le->setEnabled (! tech ()->name ().empty ());
  base_path_le->setText (tl::to_qstring (tech ()->explicit_base_path ()));
#if QT_VERSION >= 0x040700
  base_path_le->setPlaceholderText (tl::to_qstring (tech ()->default_base_path ()));
#endif

  connect (browse_pb, SIGNAL (clicked ()), this, SLOT (browse_clicked ()));
}

void 
TechBaseEditorPage::commit ()
{
  tech ()->set_description (tl::to_string (desc_le->text ()));
  tech ()->set_explicit_base_path (tl::to_string (base_path_le->text ()));
}

void 
TechBaseEditorPage::browse_clicked ()
{
  QString p = QFileDialog::getExistingDirectory (this, QObject::tr ("Choose Base Path"), 
                                                       base_path_le->text ());
  if (! p.isNull ()) {
    base_path_le->setText (p);
  }
}

// ----------------------------------------------------------------
//  TechLayerMappingEditorPage implementation

TechLayerMappingEditorPage::TechLayerMappingEditorPage (QWidget *parent)
  : TechnologyComponentEditor (parent)
{
  Ui::TechLayerMappingEditorPage::setupUi (this);

  connect (browse_pb, SIGNAL (clicked ()), this, SLOT (browse_clicked ()));
}

void 
TechLayerMappingEditorPage::setup ()
{
  const db::LayerMap &lm = tech ()->layer_map ();
  layer_mapping_grp->setChecked (! lm.is_empty ());
  layer_map->set_layer_map (lm);
  read_all_cbx->setChecked (tech ()->create_other_layers ());
  
  const std::string &lyp = tech ()->layer_properties_file ();
  lyp_grp->setChecked (! lyp.empty ());
  lyp_le->setText (tl::to_qstring (lyp));
  add_other_layers_cbx->setChecked (tech ()->add_other_layers ());
}

void 
TechLayerMappingEditorPage::commit ()
{
  if (! layer_mapping_grp->isChecked ()) {
    tech ()->set_layer_map (db::LayerMap ());
    tech ()->set_create_other_layers (true);
  } else {
    tech ()->set_layer_map (layer_map->get_layer_map ());
    tech ()->set_create_other_layers (read_all_cbx->isChecked ());
  }

  if (! lyp_grp->isChecked ()) {
    tech ()->set_layer_properties_file (std::string ());
    tech ()->set_add_other_layers (true);
  } else {
    tech ()->set_layer_properties_file (tl::to_string (lyp_le->text ()));
    tech ()->set_add_other_layers (add_other_layers_cbx->isChecked ());
  }
}

void 
TechLayerMappingEditorPage::browse_clicked ()
{
  lay::FileDialog open_dialog (this, 
                               tl::to_string (QObject::tr ("Browse Layer Properties File")), 
                               tl::to_string (QObject::tr ("Layer properties files (*.lyp);;Text files (*.txt);;All files (*)")));

  // std::string lyp = tl::to_string (lyp_le->text ()); @@@
  std::string lyp = tech ()->base_path ();
  if (open_dialog.get_open (lyp)) {
    lyp_le->setText (tl::to_qstring (tech ()->correct_path (lyp)));
  }
}

// ----------------------------------------------------------------
//  TechMacrosPage implementation

TechMacrosPage::TechMacrosPage (QWidget *parent, const std::string &cat, const std::string &cat_desc)
  : TechnologyComponentEditor (parent), m_cat (cat), m_cat_desc (cat_desc)
{
  Ui::TechMacrosPage::setupUi (this);

  m_original_labels.push_back (std::make_pair (title_label, title_label->text ()));
  m_original_labels.push_back (std::make_pair (note_label, note_label->text ()));
  m_original_labels.push_back (std::make_pair (empty_label1, empty_label1->text ()));
  m_original_labels.push_back (std::make_pair (empty_label2, empty_label2->text ()));
  m_original_labels.push_back (std::make_pair (empty_label3, empty_label3->text ()));

  folder_tree->header ()->hide ();
  connect (folder_tree, SIGNAL (clicked (const QModelIndex &)), this, SLOT (macro_selected (const QModelIndex &)));

  QFont f = macro_text->font ();
  f.setFixedPitch (true);
  f.setFamily (tl::to_qstring ("Monospace"));
  macro_text->setFont (f);

  connect (create_folder_button, SIGNAL (clicked ()), this, SLOT (create_folder_clicked ()));
}

TechMacrosPage::~TechMacrosPage ()
{
  //  do this before the collection gets deleted.
  delete folder_tree->model ();
}

void 
TechMacrosPage::setup ()
{
  title_label->show ();
  macro_frame->show ();
  note_label->show ();
  empty_label1->hide ();
  empty_label3->hide ();
  empty_label2_frame->hide ();

  QDir base_dir (tl::to_qstring (tech ()->base_path ()));
  QDir macro_dir (base_dir.filePath (tl::to_qstring (m_cat)));
  QString cp = macro_dir.canonicalPath ();

  //  if a macro collection already exists, show a readonly copy of this one
  const lay::MacroCollection *original = 0;
  const lay::MacroCollection *root = &lay::MacroCollection::root ();
  for (lay::MacroCollection::const_child_iterator m = root->begin_children (); m != root->end_children () && ! original; ++m) {
    if (m->second->virtual_mode () == lay::MacroCollection::TechFolder && m->second->category () == m_cat && QDir (tl::to_qstring (m->second->path ())).canonicalPath () == cp) {
      original = m->second;
    }
  }

  const lay::MacroCollection *alt = 0;
  for (lay::MacroCollection::const_child_iterator m = root->begin_children (); m != root->end_children () && ! alt; ++m) {
    if (m->second->virtual_mode () != lay::MacroCollection::TechFolder && QDir (tl::to_qstring (m->second->path ())).canonicalPath () == cp) {
      alt = m->second;
    }
  }

  //  adjust labels
  for (std::vector<std::pair<QLabel *, QString> >::const_iterator ol = m_original_labels.begin (); ol != m_original_labels.end (); ++ol) {
    QString l = ol->second;
    l.replace (QString::fromUtf8 ("%CAT%"), tl::to_qstring (m_cat));
    l.replace (QString::fromUtf8 ("%CAT_DESC%"), tl::to_qstring (m_cat_desc));
    l.replace (QString::fromUtf8 ("%BASE_PATH%"), tl::to_qstring (tech ()->base_path ()));
    if (alt) {
      l.replace (QString::fromUtf8 ("%ALT_DESC%"), tl::to_qstring (alt->description ()));
    } else {
      l.replace (QString::fromUtf8 ("%ALT_DESC%"), QString::fromUtf8 ("*unknown*"));
    }
    ol->first->setText (l);
  }

  if (tech ()->base_path ().empty ()) {

    //  no base path set
    title_label->hide ();
    empty_label1->show ();
    macro_frame->hide ();
    note_label->hide ();

  } else {
    
    if (! macro_dir.exists ()) {

      //  macro folder not found
      title_label->hide ();
      empty_label2_frame->show ();
      macro_frame->hide ();
      note_label->hide ();

    } else {
      
      //  valid macros to show
      std::string mp = tl::to_string (macro_dir.path ());
      if (mp_collection.get () && m_current_path == mp) {
        //  .. nothing to do ..
      } else {

        if (! original && alt) {

          //  this can happen, if the macro collection is already there in a different context.
          //  Show a message indicating that
          title_label->hide ();
          empty_label3->show ();
          macro_frame->hide ();
          note_label->hide ();

        } else {

          std::string desc;
          if (original) {
            desc = original->description ();
          } else {
            desc = tl::to_string (QObject::tr ("Technology")) + " - " + tech ()->name ();
          }

          lay::MacroCollection *mc = new lay::MacroCollection ();
          mp_collection.reset (mc);
          mc->add_folder (desc, mp, m_cat, true);
          m_current_path = mp;

          delete folder_tree->model ();
          folder_tree->setModel (new lay::MacroTreeModel (this, mc, m_cat));
          folder_tree->expandAll ();
          macro_text->hide ();

        }

      }

    }

  }
}

void
TechMacrosPage::create_folder_clicked ()
{
BEGIN_PROTECTED
  QString macro_dir = QDir (tl::to_qstring (tech ()->base_path ())).absoluteFilePath (tl::to_qstring (m_cat));
  if (! QDir::root ().mkpath (macro_dir)) {
    throw tl::Exception (tl::to_string (QObject::tr ("Failed to create folder: ")) + tl::to_string (macro_dir));
  }
  setup ();
END_PROTECTED
}

void
TechMacrosPage::macro_selected (const QModelIndex &index)
{
  const lay::Macro *m = 0;
  lay::MacroTreeModel *model = dynamic_cast<lay::MacroTreeModel *> (folder_tree->model ());
  if (model && model->is_valid_pointer (index.internalPointer ())) {
    m = dynamic_cast <lay::Macro *> ((QObject *) index.internalPointer ());
  }

  if (! m) {
    macro_text->hide ();
  } else {
    macro_text->show ();
    macro_text->setPlainText (tl::to_qstring (m->text ()));
  }
}

void 
TechMacrosPage::commit ()
{
  // .. noting yet ..
}

// ----------------------------------------------------------------
//  TechSetupDialog implementation

static bool s_first_show = true;

TechSetupDialog::TechSetupDialog (QWidget *parent)
  : QDialog (parent), mp_current_tech (0), mp_current_editor (0), mp_current_tech_component (0)
{
  setObjectName (QString::fromAscii ("tech_setup_dialog"));

  Ui::TechSetupDialog::setupUi (this);

  QAction *add_action = new QAction (QObject::tr ("Add Technology"), this);
  connect (add_action, SIGNAL (triggered ()), this, SLOT (add_clicked ()));
  QAction *delete_action = new QAction (QObject::tr ("Delete Technology"), this);
  connect (delete_action, SIGNAL (triggered ()), this, SLOT (delete_clicked ()));
  QAction *rename_action = new QAction (QObject::tr ("Rename Technology"), this);
  connect (rename_action, SIGNAL (triggered ()), this, SLOT (rename_clicked ()));
  QAction *import_action = new QAction (QObject::tr ("Import Technology"), this);
  connect (import_action, SIGNAL (triggered ()), this, SLOT (import_clicked ()));
  QAction *export_action = new QAction (QObject::tr ("Export Technology"), this);
  connect (export_action, SIGNAL (triggered ()), this, SLOT (export_clicked ()));

  tech_tree->addAction (add_action);
  tech_tree->addAction (delete_action);
  tech_tree->addAction (rename_action);
  QAction *separator = new QAction (this);
  separator->setSeparator (true);
  tech_tree->addAction (separator);
  tech_tree->addAction (import_action);
  tech_tree->addAction (export_action);

  tech_tree->header ()->hide ();
  connect (tech_tree, SIGNAL (currentItemChanged (QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT (current_tech_changed (QTreeWidgetItem *, QTreeWidgetItem *)));
  connect (add_pb, SIGNAL (clicked ()), this, SLOT (add_clicked ()));
  connect (delete_pb, SIGNAL (clicked ()), this, SLOT (delete_clicked ()));
  connect (rename_pb, SIGNAL (clicked ()), this, SLOT (rename_clicked ()));

  if (s_first_show) {
    TipDialog td (this, lay::MainWindow::instance (), 
                  tl::to_string (QObject::tr ("<html><body>To get started with the technology manager, read the documentation provided: <a href=\"int:/about/technology_manager.xml\">About Technology Management</a>.</body></html>")), 
                  "tech-manager-basic-tips");
    td.exec_dialog ();
    s_first_show = false;
  }
}

TechSetupDialog::~TechSetupDialog ()
{
  clear_components ();
}

void
TechSetupDialog::clear_components ()
{
  for (std::map <std::string, lay::TechnologyComponent *>::iterator tc = m_technology_components.begin (); tc != m_technology_components.end (); ++tc) {
    delete tc->second;
  }
  m_technology_components.clear ();

  for (std::map <std::string, lay::TechnologyComponentEditor *>::iterator tce = m_component_editors.begin (); tce != m_component_editors.end (); ++tce) {
    tc_stack->removeWidget (tce->second);
    delete tce->second;
  }
  m_component_editors.clear ();

  mp_current_editor = 0;
  mp_current_tech_component = 0;
}

int
TechSetupDialog::exec ()
{
  m_technologies = *lay::Technologies ().instance ();
  update_tech_tree ();
  tech_tree->setCurrentItem (tech_tree->topLevelItem (0));
  update_tech (selected_tech ());
  tc_stack->setMinimumSize (tc_stack->sizeHint ());

  int ret = QDialog::exec ();
  if (ret) {
    *lay::Technologies ().instance () = m_technologies;
  }

  //  clean up
  update_tech (0);
  clear_components ();
  m_technologies = lay::Technologies ();
  update_tech_tree ();

  return ret;
}

void 
TechSetupDialog::add_clicked ()
{
BEGIN_PROTECTED

  commit_tech_component ();

  lay::Technology *t = selected_tech ();
  if (! t) {
    t = m_technologies.technology_by_name (std::string ());
    tl_assert (t != 0);
  }

  std::string d = t->name ();
  if (! d.empty () && ! t->description ().empty ()) {
    d += " - ";
  }
  d += t->description ();

  bool ok = false;
  QString tn = QInputDialog::getText (this, QObject::tr ("Add Technology"), 
                                      tl::to_qstring (tl::sprintf (tl::to_string (QObject::tr ("This will create a new technology based on the selected technology '%s'.\nChoose a name for the new technology.")), d)), 
                                      QLineEdit::Normal,
                                      QString (), 
                                      &ok);
  if (ok && !tn.isEmpty()) {

    tn = tn.simplified ();

    if (m_technologies.has_technology (tl::to_string (tn))) {
      throw tl::Exception (tl::to_string (QObject::tr ("A technology with this name already exists")));
    }

    lay::Technology *nt = new lay::Technology (*t);
    nt->set_name (tl::to_string (tn));
    nt->set_description (std::string ());
    m_technologies.add (nt);

    update_tech_tree ();
    select_tech (*m_technologies.technology_by_name (tl::to_string (tn)));

  }

END_PROTECTED
}

void 
TechSetupDialog::delete_clicked ()
{
BEGIN_PROTECTED

  lay::Technology *t = selected_tech ();
  if (! t) {
    throw tl::Exception (tl::to_string (QObject::tr ("No technology selected")));
  }

  if (t->name ().empty ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("The default technology cannot be deleted")));
  }

  if (! t->is_persisted ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("Auto-imported technologies cannot be deleted")));
  }

  if (QMessageBox::question (this, QObject::tr ("Deleting Technology"),
                                   QObject::tr ("Are you sure to delete this technology?\nThis operation cannot be undone, except by cancelling the technology manager."),
                                   QMessageBox::No | QMessageBox::Yes) == QMessageBox::Yes) {

    for (lay::Technologies::const_iterator i = m_technologies.begin (); i != m_technologies.end (); ++i) {

      if (i->name () == t->name ()) {

        m_technologies.remove (i->name ());
        update_tech_tree ();
        select_tech (*m_technologies.technology_by_name (std::string ()));

        break;

      }
    }

  }

END_PROTECTED
}

void 
TechSetupDialog::rename_clicked ()
{
BEGIN_PROTECTED

  commit_tech_component ();

  lay::Technology *t = selected_tech ();
  if (! t) {
    throw tl::Exception (tl::to_string (QObject::tr ("No technology selected")));
  }

  if (t->name ().empty ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("The default technology cannot be renamed")));
  }

  if (! t->is_persisted ()) {
    throw tl::Exception (tl::to_string (QObject::tr ("Auto-imported technologies cannot be renamed")));
  }

  bool ok = false;
  QString tn = QInputDialog::getText (this, QObject::tr ("Rename Technology"), 
                                      QObject::tr ("Choose a name for the technology"), 
                                      QLineEdit::Normal,
                                      tl::to_qstring (t->name ()), 
                                      &ok);
  if (ok && !tn.isEmpty()) {

    tn = tn.simplified ();

    if (m_technologies.has_technology (tl::to_string (tn))) {
      throw tl::Exception (tl::to_string (QObject::tr ("A technology with this name already exists")));
    }

    t->set_name (tl::to_string (tn));

    update_tech_tree ();
    select_tech (*t);

  }

END_PROTECTED
}

void 
TechSetupDialog::import_clicked ()
{
BEGIN_PROTECTED

  lay::FileDialog open_dialog (this, tl::to_string (QObject::tr ("Import Technology")), tl::to_string (QObject::tr ("KLayout technology files (*.lyt);;All files (*)")));

  std::string fn;
  if (open_dialog.get_open (fn)) {

    lay::Technology t;
    t.load (fn);

    if (m_technologies.has_technology (t.name ())) {
      *m_technologies.technology_by_name (t.name ()) = t;
    } else {
      m_technologies.add (new lay::Technology (t));
    }

    update_tech_tree ();
    select_tech (*m_technologies.technology_by_name (t.name ()));

  }

END_PROTECTED
}

void 
TechSetupDialog::export_clicked ()
{
BEGIN_PROTECTED

  lay::Technology *t = selected_tech ();
  if (! t) {
    throw tl::Exception (tl::to_string (QObject::tr ("No technology selected")));
  }

  lay::FileDialog save_dialog (this, tl::to_string (QObject::tr ("Export Technology")), tl::to_string (QObject::tr ("KLayout technology files (*.lyt);;All files (*)")));

  std::string fn;
  if (save_dialog.get_save (fn)) {
    t->save (fn);
  }

END_PROTECTED
}

void
TechSetupDialog::update_tech_tree ()
{
  tech_tree->clear ();

  std::map <std::string, const lay::Technology *> tech_by_name;
  for (lay::Technologies::const_iterator t = m_technologies.begin (); t != m_technologies.end (); ++t) {
    tech_by_name.insert (std::make_pair (t->name (), &*t));
  }

  for (std::map <std::string, const lay::Technology *>::const_iterator t = tech_by_name.begin (); t != tech_by_name.end (); ++t) {
    
    QFont f (tech_tree->font ());
    f.setItalic (! t->second->is_persisted ());

    std::string d;
    d += t->first;
    if (! d.empty () && ! t->second->description ().empty ()) {
      d += " - ";
    }
    d += t->second->description ();

    QTreeWidgetItem *ti = new QTreeWidgetItem (tech_tree);
    ti->setData (0, Qt::DisplayRole, QVariant (tl::to_qstring (d)));
    ti->setData (0, Qt::UserRole, QVariant (tl::to_qstring (t->first)));
    ti->setData (0, Qt::FontRole, QVariant (f));
    
    std::vector <std::string> tc_names = t->second->component_names ();
    std::map <std::string, const lay::TechnologyComponent *> tc_by_name;
    for (std::vector <std::string>::const_iterator n = tc_names.begin (); n != tc_names.end (); ++n) {
      tc_by_name.insert (std::make_pair (*n, t->second->component_by_name (*n)));
    }

    QTreeWidgetItem *tci = new QTreeWidgetItem (ti);
    tci->setData (0, Qt::DisplayRole, QVariant (QObject::tr ("General")));
    tci->setData (0, Qt::UserRole + 1, QVariant (tl::to_qstring ("_general")));
    tci->setData (0, Qt::FontRole, QVariant (f));

    const std::vector<std::pair<std::string, std::string> > &mc = lay::Application::instance ()->macro_categories ();
    for (std::vector<std::pair<std::string, std::string> >::const_iterator c = mc.begin (); c != mc.end (); ++c) {
      tci = new QTreeWidgetItem (ti);
      tci->setData (0, Qt::DisplayRole, QVariant (tl::to_qstring (c->second)));
      tci->setData (0, Qt::UserRole + 1, QVariant (tl::to_qstring (std::string ("_macros_") + c->first)));
      tci->setData (0, Qt::FontRole, QVariant (f));
    }

    tci = new QTreeWidgetItem (ti);
    tci->setData (0, Qt::DisplayRole, QVariant (QObject::tr ("Layers")));
    tci->setData (0, Qt::UserRole + 1, QVariant (tl::to_qstring ("_layer_mapping")));
    tci->setData (0, Qt::FontRole, QVariant (f));

    for (std::map <std::string, const lay::TechnologyComponent *>::const_iterator c = tc_by_name.begin (); c != tc_by_name.end (); ++c) {
      tci = new QTreeWidgetItem (ti);
      tci->setData (0, Qt::DisplayRole, QVariant (tl::to_qstring (c->second->description ())));
      tci->setData (0, Qt::UserRole + 1, QVariant (tl::to_qstring (c->first)));
      tci->setData (0, Qt::FontRole, QVariant (f));
    }

  }

}

void 
TechSetupDialog::update_tech (lay::Technology *t)
{
  if (t == mp_current_tech) {
    return;
  }

  mp_current_tech = t;

  clear_components ();

  if (t) {

    lay::TechnologyComponentEditor *tce_widget = new TechBaseEditorPage (this);
    tce_widget->setEnabled (t->is_persisted ());
    tce_widget->set_technology (t, 0);
    tc_stack->addWidget (tce_widget);
    m_component_editors.insert (std::make_pair (std::string ("_general"), tce_widget));

    const std::vector<std::pair<std::string, std::string> > &mc = lay::Application::instance ()->macro_categories ();
    for (std::vector<std::pair<std::string, std::string> >::const_iterator c = mc.begin (); c != mc.end (); ++c) {
      tce_widget = new TechMacrosPage (this, c->first, c->second);
      tce_widget->setEnabled (t->is_persisted ());
      tce_widget->set_technology (t, 0);
      tc_stack->addWidget (tce_widget);
      m_component_editors.insert (std::make_pair (std::string ("_macros_") + c->first, tce_widget));
    }

    tce_widget = new TechLayerMappingEditorPage (this);
    tce_widget->setEnabled (t->is_persisted ());
    tce_widget->set_technology (t, 0);
    tc_stack->addWidget (tce_widget);
    m_component_editors.insert (std::make_pair (std::string ("_layer_mapping"), tce_widget));

    std::vector <std::string> tc_names = t->component_names ();
    for (std::vector <std::string>::const_iterator n = tc_names.begin (); n != tc_names.end (); ++n) {

      TechnologyComponent *tc = t->component_by_name (*n)->clone ();
      m_technology_components.insert (std::make_pair (*n, tc));

      tce_widget = tc->create_editor (this);
      if (tce_widget) {
        tce_widget->setEnabled (t->is_persisted ());
        tce_widget->set_technology (t, tc);
        tc_stack->addWidget (tce_widget);
        m_component_editors.insert (std::make_pair (tc->name (), tce_widget));
      }

    }

  }
}

void 
TechSetupDialog::update_tech_component ()
{
  std::string tc_name = selected_tech_component_name ();
  std::map <std::string, lay::TechnologyComponentEditor *>::const_iterator tce = m_component_editors.find (tc_name);
  if (tce != m_component_editors.end ()) {

    std::map <std::string, lay::TechnologyComponent *>::const_iterator tc = m_technology_components.find (tc_name);
    if (tc != m_technology_components.end ()) {
      mp_current_tech_component = tc->second;
    } else {
      mp_current_tech_component = 0;
    }

    tc_stack->setCurrentWidget (tce->second);
    mp_current_editor = tce->second;
    tce->second->setup ();

  } else {

    tc_stack->setCurrentIndex (0);
    mp_current_editor = 0;

  }
}

void
TechSetupDialog::select_tech (const lay::Technology &tech)
{
  //  unselect the previous technology
  update_tech (0); 

  //  find the item for the new technology
  QTreeWidgetItem *item = 0;
  for (int i = tech_tree->topLevelItemCount (); i > 0; --i) {
    item = tech_tree->topLevelItem (i - 1);
    if (item->data (0, Qt::UserRole).toString () == tl::to_qstring (tech.name ())) {
      break;
    }
  }

  tech_tree->setCurrentItem (item);
  
  update_tech (selected_tech ());
  update_tech_component ();
}

void
TechSetupDialog::accept ()
{
BEGIN_PROTECTED
  commit_tech_component ();
  QDialog::accept ();
END_PROTECTED
}

void
TechSetupDialog::current_tech_changed (QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
BEGIN_PROTECTED
  try {
    if (current) {
      commit_tech_component ();
      update_tech (selected_tech ());
      update_tech_component ();
    }
  } catch (...) {
    disconnect (tech_tree, SIGNAL (currentItemChanged (QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT (current_tech_changed (QTreeWidgetItem *, QTreeWidgetItem *)));
    // TODO: this leaves current selected - any way to unselect it?
    tech_tree->setCurrentItem (previous);
    connect (tech_tree, SIGNAL (currentItemChanged (QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT (current_tech_changed (QTreeWidgetItem *, QTreeWidgetItem *)));
    throw;
  }
END_PROTECTED
}

void
TechSetupDialog::commit_tech_component ()
{
  if (mp_current_editor) {
    mp_current_editor->commit ();
  }

  if (mp_current_tech && mp_current_tech_component && mp_current_tech->is_persisted ()) {

    mp_current_tech->set_component (mp_current_tech_component->clone ());

    //  because commit may have changed the description text, update the technology titles
    for (int i = tech_tree->topLevelItemCount (); i > 0; --i) {

      QTreeWidgetItem *item = tech_tree->topLevelItem (i - 1);

      lay::Technology *t = m_technologies.technology_by_name (tl::to_string (item->data (0, Qt::UserRole).toString ()));
      std::string d = t->name ();
      if (! d.empty () && ! t->description ().empty ()) {
        d += " - ";
      }
      d += t->description ();

      item->setData (0, Qt::DisplayRole, QVariant (tl::to_qstring (d)));

    }

  }
}

std::string 
TechSetupDialog::selected_tech_component_name ()
{
  QTreeWidgetItem *item = tech_tree->currentItem ();
  if (item) {
    QVariant d = item->data (0, Qt::UserRole + 1);
    if (d != QVariant ()) {
      return tl::to_string (d.toString ());
    }
  }

  return std::string ();
}

lay::Technology *
TechSetupDialog::selected_tech ()
{
  QTreeWidgetItem *item = tech_tree->currentItem ();
  while (item) {

    QVariant d = item->data (0, Qt::UserRole);
    if (d != QVariant ()) {
      std::string tn = tl::to_string (d.toString ());
      if (m_technologies.has_technology (tn)) {
        return m_technologies.technology_by_name (tn);
      }
    }

    //  try parent node.
    item = item->parent ();

  }

  return 0;
}

// ----------------------------------------------------------------
//  TechComponentSetupDialog implementation

TechComponentSetupDialog::TechComponentSetupDialog (QWidget *parent, Technology *tech, const std::string &component_name)
  : QDialog (parent),
    mp_tech (tech), mp_component (0), mp_editor (0)
{
  setObjectName (QString::fromAscii ("tech_component_setup_dialog"));

  Ui::TechComponentSetupDialog::setupUi (this);

  if (tech->name ().empty ()) {
    setWindowTitle (tl::to_qstring (tl::to_string (QObject::tr ("Edit Technology")) + " - " + tl::to_string (QObject::tr ("(Default)"))));
  } else {
    setWindowTitle (tl::to_qstring (tl::to_string (QObject::tr ("Edit Technology")) + " - " + tech->name ()));
  }

  const TechnologyComponent *component = tech->component_by_name (component_name);
  if (component) {

    mp_component = component->clone ();

    mp_editor = mp_component->create_editor (content_frame);
    if (mp_editor) {

      QVBoxLayout *layout = new QVBoxLayout (content_frame);
      layout->addWidget (mp_editor);
      layout->setMargin (0);
      content_frame->setLayout (layout);

      mp_editor->set_technology (tech, mp_component);
      mp_editor->setup ();

    }
  }
}

TechComponentSetupDialog::~TechComponentSetupDialog ()
{
  delete mp_component;
  mp_component = 0;
}

void 
TechComponentSetupDialog::accept ()
{
BEGIN_PROTECTED
  if (mp_editor && mp_tech && mp_component) {
    mp_editor->commit ();
    mp_tech->set_component (mp_component);
    mp_component = 0;
  }

  QDialog::accept ();
END_PROTECTED
}

}

