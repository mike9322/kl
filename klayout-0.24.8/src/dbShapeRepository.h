
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


#ifndef HDR_dbShapeRepository
#define HDR_dbShapeRepository

#include "config.h"

#include "dbObjectTag.h"
#include "dbTrans.h"
#include "dbBox.h"
#include "dbMemStatistics.h"

#include <set>

namespace db {

template <class C> class polygon;
template <class C> class simple_polygon;
template <class C> class path;
template <class C> class edge;
template <class C> class text;
template <class C> class user_object;

/**
 *  @brief A repository for a certain shape type
 *
 *  The repository is basically a set of shapes that
 *  can be used to store duplicates of shapes in an
 *  efficient way.
 */

template <class Sh>
class repository
{
public:
  typedef typename Sh::coord_type coord_type;
  typedef std::set<Sh> set_type;
  typedef typename set_type::const_iterator iterator;

  /** 
   *  @brief The standard constructor
   */
  repository ()
    : m_set ()
  {
    //  .. nothing yet ..
  }

  /** 
   *  @brief The copy constructor
   */
  repository (const repository<Sh> &d)
    : m_set (d.m_set)
  {
    //  .. nothing yet ..
  }

  /**
   *  @brief Insert a shape into the repository
   *
   *  Inserts a shape into the repository.
   *
   *  @return A pointer to the instance of the identical shape
   */
  const Sh *insert (const Sh &shape)
  {
    typename std::set<Sh>::iterator f = m_set.insert (shape).first;
    return &(*f);
  }

  /**
   *  @brief Report the number of shapes in this repository
   */
  size_t size () const
  {
    return m_set.size ();
  }

  /**
   *  @brief begin iterator of the repository
   */
  iterator begin () const
  {
    return m_set.begin ();
  }

  /**
   *  @brief end iterator of the repository
   */
  iterator end () const
  {
    return m_set.end ();
  }

  size_t mem_used () const
  {
    return db::mem_used (m_set);
  }

  size_t mem_reqd () const
  {
    return db::mem_reqd (m_set);
  }

private:
  set_type m_set;
};

template <class Sh>
size_t mem_used (const repository<Sh> &s)
{
  return s.mem_used (); 
}

template <class Sh>
size_t mem_reqd (const repository<Sh> &s)
{
  return s.mem_reqd (); 
}


/**
 *  @brief A repository for many shape types
 *
 *  This generic repository is providing a repository for several
 *  shape types, even if these repositories are never used. 
 */

template <class C>
class generic_repository
{
public:
  typedef C coord_type;

  /**
   *  @brief Return the repository by tag 
   */
  db::repository< db::polygon<C> > &repository (db::object_tag< db::polygon<C> > tag)
  {
    return m_polygon_repository;
  }

  /**
   *  @brief Return the repository by tag 
   */
  db::repository< db::simple_polygon<C> > &repository (db::object_tag< db::simple_polygon<C> > tag)
  {
    return m_simple_polygon_repository;
  }

  /**
   *  @brief Return the repository by tag 
   */
  db::repository< db::path<C> > &repository (db::object_tag< db::path<C> > tag)
  {
    return m_path_repository;
  }

  /**
   *  @brief Return the repository by tag 
   */
  db::repository< db::text<C> > &repository (db::object_tag< db::text<C> > tag)
  {
    return m_text_repository;
  }

  size_t mem_used () const
  {
    return db::mem_used (m_polygon_repository) + 
           db::mem_used (m_simple_polygon_repository) + 
           db::mem_used (m_path_repository) + 
           db::mem_used (m_text_repository);
  }

  size_t mem_reqd () const
  {
    return db::mem_reqd (m_polygon_repository) + 
           db::mem_reqd (m_simple_polygon_repository) + 
           db::mem_reqd (m_path_repository) + 
           db::mem_reqd (m_text_repository);
  }

private:
  db::repository< db::polygon<C> > m_polygon_repository;
  db::repository< db::simple_polygon<C> > m_simple_polygon_repository;
  db::repository< db::path<C> > m_path_repository;
  db::repository< db::text<C> > m_text_repository;
};

template <class C>
size_t mem_used (const generic_repository<C> &s)
{
  return s.mem_used (); 
}

template <class C>
size_t mem_reqd (const generic_repository<C> &s)
{
  return s.mem_reqd (); 
}


/**
 *  @brief Standard repository typedef
 */
typedef db::generic_repository<db::Coord> GenericRepository;

/** 
 *  @brief A generic shape reference
 *
 *  A shape reference is basically a proxy to an actual shape  and
 *  is used to implement shape references with a repository.
 */

template <class Sh, class Trans>
struct shape_ref
{
  typedef Sh shape_type;
  typedef typename Sh::coord_type coord_type;
  typedef Trans trans_type;
  typedef db::generic_repository<coord_type> repository_type;
  typedef db::object_tag<shape_ref<Sh, Trans> > tag;

  /**
   *  @brief The default constructor.
   *  
   *  The default constructor creates a invalid polygon reference
   */
  shape_ref ()
    : m_ptr (0)
  {
    // .. nothing yet ..
  }

  /**
   *  @brief The constructor taking a shape pointer and a transformation.
   *  
   *  It is assumed that the shape is stored in a proper repository already
   */
  shape_ref (const Sh *ptr, const Trans &trans)
    : m_ptr (ptr), m_trans (trans)
  {
    // .. nothing yet ..
  }

  /**
   *  @brief The constructor creating a reference from an actual shape
   */
  shape_ref (const shape_type &p, repository_type &rep)
    : m_ptr (0)
  {
    shape_type p_red (p);
    p_red.reduce (m_trans);
    m_ptr = rep.repository (typename Sh::tag ()).insert (p_red);
  }

  /**
   *  @brief The translation constructor.
   *  
   *  This constructor allows to copy a shape reference from one
   *  repository to another
   */
  shape_ref (const shape_ref<Sh, Trans> &ref, repository_type &rep)
    : m_ptr (0)
  {
    if (! ref.is_null ()) {
      m_trans = ref.trans ();
      m_ptr = rep.repository (typename Sh::tag ()).insert (ref.obj ());
    }
  }

  /**
   *  @brief The translation operator.
   *  
   *  This assignment allows to assign a reference in one repository
   *  to a reference in another repository
   */
  void translate (const shape_ref<Sh, Trans> &ref, repository_type &rep, db::ArrayRepository &)
  {
    if (! ref.is_null ()) {
      m_trans = ref.trans ();
      m_ptr = rep.repository (typename Sh::tag ()).insert (ref.obj ());
    } else {
      m_ptr = 0;
    }
  }

  /**
   *  @brief The translation operator with transformation.
   *  
   *  This assignment allows to assign a reference in one repository
   *  to a reference in another repository
   */
  template <class T>
  void translate (const shape_ref<Sh, Trans> &ref, const T &t, repository_type &rep, db::ArrayRepository &)
  {
    if (! ref.is_null ()) {

      m_trans = Trans ();
      shape_type p_red (ref.instantiate ().transformed (t));
      p_red.reduce (m_trans);
      m_ptr = rep.repository (typename Sh::tag ()).insert (p_red);

    } else {
      m_ptr = 0;
    }
  }

  /**
   *  @brief The translation operator.
   *  
   *  This operator allows to change a reference to another repository.
   */
  void translate (repository_type &rep)
  {
    if (! is_null ()) {
      m_ptr = rep.repository (typename Sh::tag ()).insert (obj ());
    } else {
      m_ptr = 0;
    }
  }

  /** 
   *  @brief Equality test
   *
   *  This test assumes that the source and target are from the same
   *  repository so it is sufficient to compare transformations and pointers.
   */
  bool operator== (const shape_ref<Sh, Trans> &b) const
  {
    return m_trans == b.m_trans && m_ptr == b.m_ptr;
  }

  /** 
   *  @brief Inequality test
   */
  bool operator!= (const shape_ref<Sh, Trans> &b) const
  {
    return !operator== (b);
  }

  /**
   *  @brief Transform the shape reference.
   *
   *  Transforms the shape with the given transformation.
   *  Modifies the shape with the transformed shape.
   *  
   *  @param t The transformation to apply.
   *
   *  @return The transformed shape reference.
   */
  shape_ref<Sh, Trans> &transform (const trans_type &t)
  {
    m_trans = t * m_trans;
    return *this;
  }

  /**
   *  @brief Returns the bounding box of the shape
   */
  db::box<coord_type> box () const
  {
    tl_assert (m_ptr != 0);
    return m_trans * m_ptr->box ();
  }

  /**
   *  @brief Tell if the shape reference is an invalid reference
   */
  bool is_null () const
  {
    return m_ptr == 0;
  }

  /**
   *  @brief Return the reference the referenced shape
   */
  const shape_type &obj () const
  {
    tl_assert (m_ptr != 0);
    return *m_ptr;
  }

  /**
   *  @brief Return the Pointer the referenced shape
   *
   *  In contrast to obj(), this pointer can be 0 as well.
   */
  const shape_type *ptr () const
  {
    return m_ptr;
  }

  /**
   *  @brief Return the transformation to apply
   */
  const trans_type &trans () const
  {
    return m_trans;
  }

  /**
   *  @brief Instantiate the shape 
   */
  Sh instantiate () const
  {
    Sh shape = obj ();
    shape.transform (trans ());
    return shape;
  }

  /**
   *  @brief Instantiate the shape (other, faster version)
   */
  void instantiate (Sh &shape) const
  {
    shape = obj ();
    shape.transform (trans ());
  }

  /**
   *  @brief Some sorting criterion (geometrically)
   */
  bool operator< (const shape_ref &b) const
  {
    if (m_ptr == b.m_ptr || *m_ptr == *b.m_ptr) {
      return m_trans < b.m_trans;
    } else {
      return *m_ptr < *b.m_ptr;
    }
  }

  /**
   *  @brief The string conversion function
   */
  std::string to_string () const
  {
    return obj ().to_string () + "->" + m_trans.to_string ();
  }

  size_t mem_used () const
  {
    return sizeof (shape_ref) + (m_ptr ? db::mem_used (*m_ptr) : 0);
  }

  size_t mem_reqd () const
  {
    return sizeof (shape_ref) + (m_ptr ? db::mem_reqd (*m_ptr) : 0);
  }

private:
  const shape_type *m_ptr;
  trans_type m_trans;
};

template <class Sh, class Tr>
size_t mem_used (const shape_ref<Sh, Tr> &s)
{
  return s.mem_used (); 
}

template <class Sh, class Tr>
size_t mem_reqd (const shape_ref<Sh, Tr> &s)
{
  return s.mem_reqd (); 
}

/**
 *  @brief Output stream insertion operator
 */
template <class Sh, class Tr>
inline std::ostream &
operator<< (std::ostream &os, const shape_ref<Sh, Tr> &p)
{
  return (os << p.to_string ());
}

} // namespace db

#endif

