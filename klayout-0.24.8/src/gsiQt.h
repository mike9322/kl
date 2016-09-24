
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


#ifndef _HDR_gsiQt
#define _HDR_gsiQt

#include "gsiDecl.h"
#include "tlString.h"
#include "tlException.h"
#include "tlTypeTraits.h"
#include "tlHeap.h"

#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QObject>
#include <QtCore/QProcess>

class QGraphicsItem;
class QGraphicsObject;

namespace qt_gsi
{

/**
 *   @brief A generic way to implement a method binding
 *
 *   Using that way saves compile time and memory
 */
class GenericMethod : public gsi::MethodBase 
{
public:
  GenericMethod (const char *name, const char *doc, bool is_const, void (*init_func)(GenericMethod *), void (*call_func)(const GenericMethod *, void *, gsi::SerialArgs &args, gsi::SerialArgs &ret))
    : gsi::MethodBase (name, doc, is_const, false), mp_init_func (init_func), mp_call_func (call_func), mp_set_callback_func (0)
  {
  }

  GenericMethod (const char *name, const char *doc, bool is_const, void (*init_func)(GenericMethod *), void (*call_func)(const GenericMethod *, void *, gsi::SerialArgs &args, gsi::SerialArgs &ret), void (*set_callback_func) (void *v, const gsi::Callback &cb))
    : gsi::MethodBase (name, doc, is_const, false), mp_init_func (init_func), mp_call_func (call_func), mp_set_callback_func (set_callback_func)
  {
  }
  
  virtual void initialize ()
  {
    clear ();
    (*mp_init_func) (this);
  }

  virtual gsi::MethodBase *clone () const
  {
    return new GenericMethod (*this);
  }

  virtual void call (void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) const 
  {
    (*mp_call_func) (this, cls, args, ret);
  }

  virtual bool is_callback () const
  {
    return mp_set_callback_func != 0;
  }

  virtual void set_callback (void *v, const gsi::Callback &cb) const
  {
    if (mp_set_callback_func) {
      (*mp_set_callback_func) (v, cb);
    }
  }

private:
  void (*mp_init_func) (GenericMethod *self);
  void (*mp_call_func) (const GenericMethod *self, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret);
  void (*mp_set_callback_func) (void *cls, const gsi::Callback &cb);
};

/**
 *   @brief A generic way to implement a static method binding
 *
 *   Using that way saves compile time and memory
 */
class GenericStaticMethod : public gsi::StaticMethodBase
{
public:
  GenericStaticMethod (const char *name, const char *doc, void (*init_func)(GenericStaticMethod *), void (*call_func)(const GenericStaticMethod *self, gsi::SerialArgs &args, gsi::SerialArgs &ret))
    : gsi::StaticMethodBase (name, doc), mp_init_func (init_func), mp_call_func (call_func)
  {
  }

  virtual void initialize ()
  {
    clear ();
    (*mp_init_func) (this);
  }

  virtual gsi::MethodBase *clone () const
  {
    return new GenericStaticMethod (*this);
  }

  virtual void call (void *, gsi::SerialArgs &args, gsi::SerialArgs &ret) const 
  {
    (*mp_call_func) (this, args, ret);
  }

private:
  void (*mp_init_func) (GenericStaticMethod *self);
  void (*mp_call_func) (const GenericStaticMethod *self, gsi::SerialArgs &args, gsi::SerialArgs &ret);
};

template <class QT> struct Converter;

template <class QT>
class QtToCppAdaptor
{
public:
  typedef Converter<QT> converter_type;
  typedef typename converter_type::target_type target_type;
  typedef typename converter_type::source_type source_type;

  QtToCppAdaptor ()
    : mp_ref (0)
  {
    //  .. nothing yet ..
  }

  QtToCppAdaptor (const QtToCppAdaptor<QT> &d)
    : m_qt (d.m_qt), mp_ref (d.mp_ref)
  {
    //  .. nothing yet ..
  }

  QtToCppAdaptor (const target_type &t)
    : m_qt (converter_type::toq (t)), mp_ref (0)
  {
    //  .. nothing yet ..
  }

  QtToCppAdaptor (const target_type *t)
    : m_qt (converter_type::toq (*t)), mp_ref (0)
  {
    //  .. nothing yet ..
  }

  QtToCppAdaptor (target_type &t)
    : m_qt (converter_type::toq (t)), mp_ref (&t)
  {
    //  .. nothing yet ..
  }

  QtToCppAdaptor (target_type *t)
    : m_qt (converter_type::toq (*t)), mp_ref (t)
  {
    //  .. nothing yet ..
  }

  ~QtToCppAdaptor ()
  {
    if (mp_ref) {
      *mp_ref = converter_type::toc (m_qt);
    }
  }

  source_type *ptr ()
  {
    return &m_qt;
  }

  source_type &ref ()
  {
    return m_qt;
  }

  const source_type *cptr () const
  {
    return &m_qt;
  }

  const source_type &cref () const
  {
    return m_qt;
  }

private:
  source_type m_qt;
  target_type *mp_ref;
};

template <class QT>
class CppToQtReadAdaptor
{
public:
  typedef Converter<QT> converter_type;
  typedef typename converter_type::target_type target_type;
  typedef typename converter_type::source_type source_type;

  CppToQtReadAdaptor ()
    : mp_ref (0)
  {
    //  .. nothing yet ..
  }

  CppToQtReadAdaptor (tl::Heap &heap, const source_type &qt)
  {
    mp_ref = new target_type (converter_type::toc (qt));
    heap.push (mp_ref);
  }

  operator const target_type *() const
  {
    return mp_ref;
  }

  operator const target_type &() const
  {
    return *mp_ref;
  }

private:
  const target_type *mp_ref;

  CppToQtReadAdaptor (const CppToQtReadAdaptor<QT> &d);
  CppToQtReadAdaptor &operator= (const CppToQtReadAdaptor<QT> &d);
};

template <class QT>
class CppToQtAdaptor
{
public:
  typedef Converter<QT> converter_type;
  typedef typename converter_type::target_type target_type;
  typedef typename converter_type::source_type source_type;

  CppToQtAdaptor ()
    : mp_ref (0)
  {
    //  .. nothing yet ..
  }

  CppToQtAdaptor (const CppToQtAdaptor<QT> &d)
    : m_t (d.m_t), mp_ref (d.mp_ref)
  {
    //  .. nothing yet ..
  }

  CppToQtAdaptor (const source_type &qt)
    : m_t (converter_type::toc (qt)), mp_ref (0)
  {
    //  .. nothing yet ..
  }

  CppToQtAdaptor (source_type &qt)
    : m_t (converter_type::toc (qt)), mp_ref (&qt)
  {
    //  .. nothing yet ..
  }

  ~CppToQtAdaptor ()
  {
    if (mp_ref) {
      *mp_ref = converter_type::toq (m_t);
    }
  }

  operator target_type *() 
  {
    return &m_t;
  }

  operator target_type &() 
  {
    return m_t;
  }

  operator const target_type *() const
  {
    return &m_t;
  }

  operator const target_type &() const
  {
    return m_t;
  }

private:
  target_type m_t;
  source_type *mp_ref;
};

template <class T>
struct Converter
{
  typedef T source_type;
  typedef T target_type;
  static const T &toq (const T &v) { return v; }
  static const T &toc (const T &v) { return v; }
};

template <>
struct Converter<Qt::HANDLE>
{
public:
  typedef Qt::HANDLE source_type;
  typedef size_t target_type;
  static source_type toq (target_type c) { return source_type (c); }
  static target_type toc (source_type qc) { return target_type (qc); }
};

template <>
struct Converter<Q_PID>
{
public:
  typedef Q_PID source_type;
  typedef size_t target_type;
  static source_type toq (target_type c) { return source_type (c); }
  static target_type toc (source_type qc) { return target_type (qc); }
};

template <>
struct Converter<QChar>
{
public:
  typedef QChar source_type;
  typedef unsigned int target_type;
  static QChar toq (unsigned int c) { return QChar (c); }
  static unsigned int toc (QChar qc) { return qc.unicode (); }
};

template <>
struct Converter<QBool>
{
public:
  typedef QBool source_type;
  typedef bool target_type;
  static QBool toq (bool b) { return QBool (b); }
  static bool toc (QBool qb) { return qb; }
};

std::vector<std::string> to_string_vector (const QStringList &sl);
QStringList to_string_list (const std::vector<std::string> &sv);

template <>
struct Converter<QStringList>
{
public:
  typedef QStringList source_type;
  typedef std::vector<std::string> target_type;
  static QStringList toq (const std::vector<std::string> &sl) { return to_string_list (sl); }
  static std::vector<std::string> toc (const QStringList &qsl) { return to_string_vector (qsl); }
};

template <class QT> 
struct Converter< QVector<QT> >
{
public:
  typedef Converter<QT> inner_converter_type;
  typedef typename inner_converter_type::target_type inner_target_type;
  typedef QVector<QT> source_type;
  typedef std::vector<inner_target_type> target_type;

  static QVector<QT> toq (const std::vector<inner_target_type> &v) 
  { 
    QVector<QT> ql;
    for (typename std::vector<inner_target_type>::const_iterator c = v.begin (); c != v.end (); ++c) {
      ql.push_back (inner_converter_type::toq (*c));
    }
    return ql;
  }

  static std::vector<inner_target_type> toc (const QVector<QT> &ql) 
  { 
    std::vector<inner_target_type> v;
    v.reserve (ql.size ());
    for (typename QVector<QT>::const_iterator q = ql.begin (); q != ql.end (); ++q) {
      v.push_back (inner_converter_type::toc (*q));
    }
    return v;
  }
};

template <class QT> 
struct Converter< QList<QT> >
{
public:
  typedef Converter<QT> inner_converter_type;
  typedef typename inner_converter_type::target_type inner_target_type;
  typedef QList<QT> source_type;
  typedef std::vector<inner_target_type> target_type;

  static QList<QT> toq (const std::vector<inner_target_type> &v) 
  { 
    QList<QT> ql;
    for (typename std::vector<inner_target_type>::const_iterator c = v.begin (); c != v.end (); ++c) {
      ql.push_back (inner_converter_type::toq (*c));
    }
    return ql;
  }

  static std::vector<inner_target_type> toc (const QList<QT> &ql) 
  { 
    std::vector<inner_target_type> v;
    v.reserve (ql.size ());
    for (typename QList<QT>::const_iterator q = ql.begin (); q != ql.end (); ++q) {
      v.push_back (inner_converter_type::toc (*q));
    }
    return v;
  }
};

class AbstractMethodCalledException
  : public tl::Exception
{
public:
  AbstractMethodCalledException (const char *method_name);
};

class QtObjectBase
  : public gsi::ObjectBase
{
public:
  void init (void *x) 
  {
    //  fallback case: no particular initialization 
  }

  void init (QObject *object);
  void init (QGraphicsItem *object);
  void init (QGraphicsObject *object);
};

/**
 *  @brief An implementation helper for the "keep arg" feature
 *  This helper will call keep on the object or objects, hence passing
 *  ownership to the callee.
 */
template <class T>
inline void qt_keep (T *obj)
{
  QtObjectBase *qt_obj = dynamic_cast<QtObjectBase *>(obj);
  if (qt_obj) {
    qt_obj->keep ();
  }
}

template <class T>
inline void qt_keep (const QList<T *> &list)
{
  for (typename QList<T *>::const_iterator l = list.begin (); l != list.end (); ++l) {
    qt_keep (*l);
  }
}

template <class T>
inline void qt_keep (const std::vector<T *> &list)
{
  for (typename std::vector<T *>::const_iterator l = list.begin (); l != list.end (); ++l) {
    qt_keep (*l);
  }
}

}
  
#endif

