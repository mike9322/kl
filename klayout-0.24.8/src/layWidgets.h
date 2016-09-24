
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


#ifndef HDR_layWidgets
#define HDR_layWidgets

#include <QtGui/QPushButton>
#include <QtGui/QComboBox>

namespace db
{
  class Layout;
  class Library;
  struct LayerProperties;
}

namespace lay
{

class LayoutView;
struct LayerSelectionComboBoxPrivateData;
struct CellViewSelectionComboBoxPrivateData;

/**
 *  @brief A selection button for dither pattern
 */
class DitherPatternSelectionButton
  : public QPushButton
{
Q_OBJECT

public:
  /**
   *  @brief Constructor
   */
  DitherPatternSelectionButton (QWidget *parent);

  /**
   *  @brief Destructor
   */
  ~DitherPatternSelectionButton ();

  /**
   *  @brief Associate with a view 
   *
   *  This method is required to select the proper dither pattern
   */
  void set_view (lay::LayoutView *view);

  /**
   *  @brief Set the dither pattern index
   */
  void set_dither_pattern (int dp);

  /**
   *  @brief Get the dither pattern index
   */
  int dither_pattern () const;

  /**
   *  @brief Override setText 
   */
  void setText (const QString &) { }

  /**
   *  @brief Override setPixmap 
   */
  void setPixmap (const QPixmap &) { }

signals:
  void dither_pattern_changed (int);

private slots:
  void browse_selected ();
  void menu_selected ();
  void menu_about_to_show ();

private:
  lay::LayoutView *mp_view;
  int m_dither_pattern;

  void update_pattern ();
  void update_menu ();
};

/**
 *  @brief A library selection combo box
 *
 *  This combo box allows to select a library
 */
class LibrarySelectionComboBox
  : public QComboBox
{
Q_OBJECT

public:
  /**
   *  @brief Constructor
   */
  LibrarySelectionComboBox (QWidget *parent);

  /**
   *  @brief Destructor
   */
  ~LibrarySelectionComboBox ();

  /**
   *  @brief Set the current library
   *
   *  The current library is "none" (local definition) if the pointer is 0.
   */
  void set_current_library (db::Library *lib);

  /**
   *  @brief Get the current library
   *
   *  The pointer is 0 if "none" is selected.
   */
  db::Library *current_library () const;

  /**
   *  @brief Update the list of libraries
   */
  void update_list ();
};

/**
 *  @brief A layer selection combo box
 *
 *  This combo box allows to select a (physical) layer from a layout
 */
class LayerSelectionComboBox
  : public QComboBox
{
Q_OBJECT

public:
  /**
   *  @brief Constructor
   */
  LayerSelectionComboBox (QWidget *parent);

  /**
   *  @brief Destructor
   */
  ~LayerSelectionComboBox ();

  /**
   *  @brief Associate with a layout
   *
   *  Associates this widget with a certain layout object - this one is being
   *  scanned for layers that are presented in this combo box.
   */
  void set_layout (const db::Layout *layout);

  /**
   *  @brief Associate with a view and cellview index
   *
   *  This method can be used instead of set_layout. If this method is used, more
   *  functionality is available, i.e. the ability to create new layers.
   *  If all_layers is set to true, layers are shown which are in the layer list, but
   *  not created as layers yet.
   */
  void set_view (lay::LayoutView *view, int cv_index, bool all_layers = false);

  /**
   *  @brief Sets a flag indicating whether the "new layer" option is available
   */
  void set_new_layer_enabled (bool f);

  /**
   *  @brief Gets a flag indicating whether the "new layer" option is available
   */
  bool is_new_layer_enabled () const;

  /**
   *  @brief Sets a flag indicating whether "no layer" is available as selection
   */
  void set_no_layer_available (bool f);

  /**
   *  @brief Gets a flag indicating whether "no layer" is available as selection
   */
  bool is_no_layer_available () const;

  /**
   *  @brief Set the current layer (index)
   */
  void set_current_layer (const db::LayerProperties &lp);

  /**
   *  @brief Set the current layer (index)
   */
  void set_current_layer (int l);

  /**
   *  @brief Get the current layer (index)
   */
  int current_layer () const;

  /**
   *  @brief Get the current layer properties
   */
  db::LayerProperties current_layer_props () const;

protected slots:
  void item_selected (int index);

private:
  LayerSelectionComboBoxPrivateData *mp_private;

  void update_layer_list ();
};

/**
 *  @brief A cell view selection combo box
 *
 *  This combo box allows to select a cellview from a lay::LayoutView
 */
class CellViewSelectionComboBox
  : public QComboBox
{
Q_OBJECT

public:
  CellViewSelectionComboBox (QWidget *parent);
  ~CellViewSelectionComboBox ();

  void set_layout_view (const lay::LayoutView *view);
  const lay::LayoutView *layout_view () const;

  void set_current_cv_index (int l);
  int current_cv_index () const;

private:
  CellViewSelectionComboBoxPrivateData *mp_private;
};

/**
 *  @brief Simpl color chooser button
 *
 *  This class implements a special button that can replace a 
 *  usual push button and supplies a color chooser without the
 *  capability to switch to "auto" color mode.
 */
class SimpleColorButton 
  : public QPushButton 
{
Q_OBJECT

public:
  SimpleColorButton (QPushButton *&to_replace, const char *name = 0);
  SimpleColorButton (QWidget *parent, const char *name = 0);

  QColor get_color () const;

signals:
  void color_changed (QColor color);

public slots:
  void set_color (QColor color);

private:
  QColor m_color;

  void set_color_internal (QColor color);

private slots:
  virtual void selected ();
};

/**
 *  @brief Color chooser button
 *
 *  This class implements a special button that can replace a 
 *  usual push button and supplies a color chooser with the
 *  capability to switch to "auto" color mode.
 */
class ColorButton 
  : public QPushButton 
{
Q_OBJECT

public:
  ColorButton (QPushButton *&to_replace, const char *name = 0);
  ColorButton (QWidget *parent, const char *name = 0);

  QColor get_color () const;

signals:
  void color_changed (QColor color);

public slots:
  void set_color (QColor color);

private:
  QColor m_color;

  void set_color_internal (QColor color);
  void build_menu ();

protected slots:
  virtual void browse_selected ();
  virtual void menu_selected ();

private slots:
  void menu_about_to_show ();
};

} // namespace lay

#endif

