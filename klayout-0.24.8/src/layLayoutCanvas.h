
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


#ifndef HDR_layLayoutCanvas
#define HDR_layLayoutCanvas

#include <vector>
#include <map>
#include <set>
#include <utility>

#include <QtCore/QMutex>

#include "dbTrans.h"
#include "dbBox.h"
#include "layViewport.h"
#include "layViewOp.h"
#include "layViewObject.h"
#include "layBitmap.h"
#include "layDrawing.h"
#include "layDitherPattern.h"
#include "layRedrawThreadCanvas.h"
#include "layRedrawLayerInfo.h"
#include "tlDeferredExecution.h"
#include "tlObserver.h"


namespace lay
{

class LayoutView;
class RedrawThread;

/**
 *  @brief A class representing one entry in the image cache
 */

class ImageCacheEntry
{
public:
  /**
   *  @brief Constructor
   *  On creation, the entry is in "open" state and will be closed once the data has been 
   *  committed with "close".
   *  "Precious" entries will be preserved as far as possible.
   */
  ImageCacheEntry (const lay::Viewport &vp, const std::vector<lay::RedrawLayerInfo> &layers, bool precious);

  /**
   *  @brief Returns a value indicating whether the entry complies with the given viewport
   */
  bool equals (const lay::Viewport &vp, const std::vector<lay::RedrawLayerInfo> &layers) const;

  /**
   *  @brief Closes the entry and stores the given data
   */
  void close (const BitmapCanvasData &data);

  /**
   *  @brief Returns a value indicating whether the entry is opened
   */
  bool opened () const
  {
    return m_opened;
  }

  /**
   *  @brief Returns a value indicating whether the entry is precious
   */
  bool precious () const
  {
    return m_precious;
  }

  /**
   *  @brief Sets a value indicating whether the entry is precious
   */
  void set_precious (bool p)
  {
    m_precious = p;
  }

  /**
   *  @brief Gets the stored bitmap data
   */
  const BitmapCanvasData &data () const
  {
    return m_data;
  }

  /**
   *  @brief Swaps this entry with another one
   */
  void swap (ImageCacheEntry &other);

  /**
   *  @brief Returns a string representing this entry
   */
  std::string to_string () const;

private:
  bool m_opened;
  db::CplxTrans m_trans;
  std::vector<lay::RedrawLayerInfo> m_layers;
  unsigned int m_width, m_height;
  bool m_precious;
  BitmapCanvasData m_data;
};
/** 
 *  @brief A "canvas" object to paint layouts on
 *
 *  The purpose of this object is to provide a canvas QWidget
 *  and to manage the auxiliary objects like rulers etc.
 */

class LayoutCanvas 
  : public lay::ViewObjectWidget,
    public lay::BitmapViewObjectCanvas,
    public lay::BitmapRedrawThreadCanvas,
    public lay::Drawings
{
Q_OBJECT

public:
  LayoutCanvas (QWidget *parent, lay::LayoutView *view, const char *name = "canvas");
  ~LayoutCanvas ();

  void set_colors (QColor background, QColor foreground, QColor active);

  /**
   *  @brief Set the view ops for the layers
   *
   *  The view_ops vector must correspond to the layers-vector from a separate 
   *  "redraw_new" call.
   *  For performance reasons it is swapped with the existing one.
   */
  void set_view_ops (std::vector <lay::ViewOp> &view_ops);

  /**
   *  @brief Get the view ops for the layers
   *
   *  This call delivers the view op vector from the layer set_view_ops call.
   */
  const std::vector <lay::ViewOp> &get_view_ops () const
  { 
    return m_view_ops; 
  }

  QImage screenshot ();
  QImage image (unsigned int width, unsigned int height);
  QImage image_with_options (unsigned int width, unsigned int height, int linewidth, int oversampling, double resolution, QColor background, QColor foreground, QColor active_color, const db::DBox &target_box, bool monochrome);

  void update_image ();

  virtual void paintEvent (QPaintEvent *);

  /**
   *  @brief Specifies the global transformation which is always applied first
   */
  void set_global_trans (const db::DCplxTrans &global_trans);

  /**
   *  @brief Place the viewport to the box specified.
   *
   *  The box gives the target box for the viewport. It may have a different aspect ratio
   *  than the viewport (in pixels) which is important if the size changes.
   *  Then, the original target box will be used which may result in a better fit.
   *  If the "precious" flag is set, the zoom box will be regarded "precious" and kept
   *  in the cache for longer.
   */
  void zoom_box (const db::DBox &box, bool precious = false);

  /**
   *  @brief Set the transformation directly
   *
   *  This sets the transformation of the viewport directly. Thus, an arbitrary transformation
   *  may be specified.
   */
  void zoom_trans (const db::DCplxTrans &trans);

  /**
   *  @brief Free internal resources, in particular pixmaps
   */
  void free_resources (); 

  /**
   *  @brief Stop the redraw thread
   */
  void stop_redraw ();

  /**
   *  @brief Issue a new redraw request
   *
   *  The layers vector gets swapped with the current one for performance reasons.
   */
  void redraw_new (std::vector<lay::RedrawLayerInfo> &layers);

  /**
   *  @brief Get the redraw layer info
   *
   *  This method delivers the redraw layer info vector as set by the last redraw_new call.
   */
  const std::vector<lay::RedrawLayerInfo> &get_redraw_layers () const
  {
    return m_layers;
  }

  /**
   *  @brief Issue a full redraw request
   */
  void redraw_all ();

  /**
   *  @brief Issue a redraw request on selected layers
   *
   *  The index must correspond to lay::RedrawLayerInfo objects from former redraw_new 
   *  calls.
   */
  void redraw_selected (const std::vector<int> &layers);

  /**
   *  @brief Set the oversampling factor
   *
   *  An oversampling of 2 means that 2 pixels are combined into one.
   */
  void set_oversampling (unsigned int os);

  /**
   *  @brief Sets the depth of the image cache
   */
  void set_image_cache_size (size_t len);

  /**
   *  @brief Change the visibility
   *
   *  The vector must correspond to the  lay::RedrawLayerInfo objects from former redraw_new
   */
  void change_visibility (const std::vector <bool> &visible);

  /**
   *  @brief Set the dither pattern object
   */
  void set_dither_pattern (const lay::DitherPattern &p);

  /**
   *  @brief Get the dither pattern object
   */
  const lay::DitherPattern &dither_pattern () const
  {
    return m_dither_pattern;
  }

  /**
   *  @brief Reimplementation of ViewObjectCanvas: Background color 
   */
  QColor background_color () const
  { 
    return QColor (m_background); 
  }

  /**
   *  @brief Reimplementation of ViewObjectCanvas: Foreground color 
   */
  QColor foreground_color () const
  { 
    return QColor (m_foreground); 
  }

  /**
   *  @brief Reimplementation of ViewObjectCanvas: Active color 
   */
  QColor active_color () const
  { 
    return QColor (m_active); 
  }

  /**
   *  @brief Reimplementation of ViewObjectCanvas: background image
   */
  QImage &bg_image ()
  {
    return *mp_image;
  }

  /** 
   *  @brief Reimplementation of RedrawThreadCanvas: signal end of drawing
   */
  void signal_end_of_drawing ();

  /** 
   *  @brief Reimplementation of RedrawThreadCanvas: signal transfer
   */
  void signal_transfer_done ();

  /**
   *  @brief Access to the viewport object
   */
  const lay::Viewport &viewport () const
  {
    return m_viewport;
  }

  /**
   *  @brief Add a viewport changed observer
   *  
   *  If the viewport (the rectangle that is shown) changes, this observer
   *  is triggered.
   */
  void add_viewport_changed_observer (tl::Observer &observer)
  {
    m_viewport_changed_observers.add_observer (observer);
  }

  /**
   *  @brief Remove a viewport changed observer
   */
  void remove_viewport_changed_observer (tl::Observer &observer)
  {
    m_viewport_changed_observers.remove_observer (observer);
  }

signals:
  void left_arrow_key_pressed ();
  void up_arrow_key_pressed ();
  void right_arrow_key_pressed ();
  void down_arrow_key_pressed ();

private:
  lay::LayoutView *mp_view;
  QImage *mp_image;
  QImage *mp_image_bg;
  QPixmap *mp_pixmap;
  db::DBox m_precious_box;
  lay::Viewport m_viewport, m_viewport_l;
  lay::color_t m_background;
  lay::color_t m_foreground;
  lay::color_t m_active;
  std::vector <lay::ViewOp> m_view_ops;
  lay::DitherPattern m_dither_pattern;
  unsigned int m_oversampling;

  bool m_need_redraw;
  bool m_redraw_clearing;
  bool m_redraw_force_update;
  bool m_update_image;
  std::vector<int> m_need_redraw_layer;
  std::vector<lay::RedrawLayerInfo> m_layers;

  lay::RedrawThread *mp_redraw_thread;
  tl::DeferredMethod<LayoutCanvas> m_do_update_image_dm;
  tl::DeferredMethod<LayoutCanvas> m_do_end_of_drawing_dm;

  std::vector<ImageCacheEntry> m_image_cache;
  size_t m_image_cache_size;

  tl::Observed m_viewport_changed_observers;

  QMutex m_mutex;

  virtual void resizeEvent (QResizeEvent *);
  virtual bool event (QEvent *e);
  virtual void key_event (unsigned int key, unsigned int buttons);

  //  implementation of the lay::Drawings interface
  void update_drawings ();

  //  must be called after updating m_viewport
  void update_viewport ();

  void do_update_image ();
  void do_end_of_drawing ();
  void do_redraw_all (bool force_redraw = true);

  void prepare_drawing ();
};

} //  namespace lay

#endif

