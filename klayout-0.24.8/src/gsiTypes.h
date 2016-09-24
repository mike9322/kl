
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


#ifndef _HDR_gsiTypes
#define _HDR_gsiTypes

#include <string>
#include <vector>
#include <stdexcept>

#include "tlInternational.h"
#include "tlException.h"

#include <QtCore/QString>

//  For a comprehensive documentation see gsi.h

namespace tl
{
  class Variant;
}

namespace gsi
{

// ---------------------------------------------------------------------------------
//  Type system of GSI

class SerialArgs;
class ClassBase;
template <class X> class Class;
template <class X> struct ClassTag;
template <class I, class R, class V> class IterAdaptor;
template <class R, class V> class IterPtrAdaptor;
template <class R, class V> class ConstIterPtrAdaptor;
template <class I, class R, class V> class FreeIterAdaptor;
template <class X> const ClassBase *cls_decl ();

/**
 *  @brief Determine the size for one item in the serialization buffer
 */
template<class X>
unsigned int item_size () 
{
  return (sizeof (X) + (sizeof (void *) - 1)) & ~(sizeof (void *) - 1); 
}

template<class X>
struct type_tag
{
  // .. intentionally left blank ..
};

/**
 *   @brief Basic GSI type constants
 */
enum BasicType
{
  T_void = 0,
  T_bool = 1,
  T_char = 2,
  T_schar = 3,
  T_uchar = 4,
  T_short = 5,
  T_ushort = 6,
  T_int = 7,
  T_uint = 8,
  T_long = 9,
  T_ulong = 10,
  T_longlong = 11,
  T_ulonglong = 12,
#if defined(HAVE_64BIT_COORD)
  T_int128 = 100,
#endif
  T_double = 13,
  T_float = 14,
  T_var = 15,
  T_string = 16,
  T_qstring = 17,
  T_string_ccptr = 18,
  T_void_ptr = 19,
  T_qbytearray = 23,
  T_object = 20,
  T_vector = 21,
  T_map = 22
};

/**
 *  @brief Type tags
 *
 *  "pod" are the POD types (bool, char, short, int, long, long long, double, float, unsigned variants)
 *  "npod" types are strings, vectors and variants
 *  "obj" types are objects
 *
 *  The basic tags are:
 *    - pod_direct_tag:     (POD)           serialized as (POD)
 *    - pod_cref_tag:       (const POD &)   serialized as (POD)
 *    - pod_ref_tag:        (POD &)         serialized as (POD *) with pointer != 0
 *    - pod_cptr_tag:       (const POD *)   serialized as (true, POD) or (false)
 *    - pod_ptr_tag:        (POD *)         serialized as (POD *)
 *    - npod_direct_tag:    (NPOD)          serialized as (NPOD)
 *    - npod_cref_tag:      (const NPOD &)  serialized as (NPOD *)
 *                                          (Reason for the latter decision: deserializing is that 
 *                                          way possible without having to call the destructor after
 *                                          the value has been used)
 *    - npod_ref_tag:       (NPOD &)        serialized as (NPOD *) with pointer != 0
 *    - npod_cptr_tag:      (const NPOD *)  serialized as (NPOD *)
 *                                          (Reason for the latter decision: deserializing is that 
 *                                          way possible without having to call the destructor after
 *                                          the value has been used)
 *    - npod_ptr_tag:       (NPOD *)        serialized as (NPOD *)
 *    - x_tag:              (OBJ)           serialized as (OBJ)
 *    - x_cref_tag:         (const OBJ &)   serialized as (OBJ *) with pointer != 0
 *    - x_ref_tag:          (OBJ &)         serialized as (OBJ *) with pointer != 0, object must not be const
 *    - x_cptr_tag:         (const OBJ *)   serialized as (OBJ *)
 *    - x_ptr_tag:          (OBJ *)         serialized as (OBJ *), object must not be const
 */

struct type_tag_base
{ 
  typedef tl::false_tag is_pod;
  typedef tl::false_tag is_npod;
  typedef tl::false_tag is_ref;
  typedef tl::false_tag is_cref;
  typedef tl::false_tag is_ptr;
  typedef tl::false_tag is_cptr;
};

struct basic_type_tag       : public type_tag_base { };
struct void_tag             : public type_tag_base { };
struct ccptr_tag            : public type_tag_base { };
struct vptr_tag             : public type_tag_base { };

struct direct_tag           : public basic_type_tag { };
struct pod_direct_tag       : public direct_tag { typedef tl::true_tag is_pod; };
struct npod_direct_tag      : public direct_tag { typedef tl::true_tag is_npod; };
struct cref_tag             : public basic_type_tag { typedef tl::true_tag is_cref; };
struct pod_cref_tag         : public cref_tag { typedef tl::true_tag is_pod; };
struct npod_cref_tag        : public cref_tag { typedef tl::true_tag is_npod; };
struct ref_tag              : public basic_type_tag { typedef tl::true_tag is_ref; };
struct pod_ref_tag          : public ref_tag { typedef tl::true_tag is_pod; };
struct npod_ref_tag         : public ref_tag { typedef tl::true_tag is_npod; };
struct cptr_tag             : public basic_type_tag { typedef tl::true_tag is_cptr; };
struct pod_cptr_tag         : public cptr_tag { typedef tl::true_tag is_pod; };
struct npod_cptr_tag        : public cptr_tag { typedef tl::true_tag is_npod; };
struct ptr_tag              : public basic_type_tag { typedef tl::true_tag is_ptr; };
struct pod_ptr_tag          : public ptr_tag { typedef tl::true_tag is_pod; };
struct npod_ptr_tag         : public ptr_tag { typedef tl::true_tag is_npod; };

struct bool_tag             : public pod_direct_tag { };
struct char_tag             : public pod_direct_tag { };
struct uchar_tag            : public pod_direct_tag { };
struct schar_tag            : public pod_direct_tag { };
struct short_tag            : public pod_direct_tag { };
struct ushort_tag           : public pod_direct_tag { };
struct int_tag              : public pod_direct_tag { };
struct uint_tag             : public pod_direct_tag { };
struct long_tag             : public pod_direct_tag { };
struct ulong_tag            : public pod_direct_tag { };
struct longlong_tag         : public pod_direct_tag { };
struct ulonglong_tag        : public pod_direct_tag { };
#if defined(HAVE_64BIT_COORD)
struct int128_tag           : public pod_direct_tag { };
#endif
struct double_tag           : public pod_direct_tag { };
struct float_tag            : public pod_direct_tag { };

struct vector_tag           : public npod_direct_tag { }; 
struct map_tag              : public npod_direct_tag { }; 
struct string_tag           : public npod_direct_tag { };
struct qstring_tag          : public npod_direct_tag { };
struct qbytearray_tag       : public npod_direct_tag { };
struct var_tag              : public npod_direct_tag { };

struct bool_cref_tag        : public pod_cref_tag { };
struct char_cref_tag        : public pod_cref_tag { };
struct uchar_cref_tag       : public pod_cref_tag { };
struct schar_cref_tag       : public pod_cref_tag { };
struct short_cref_tag       : public pod_cref_tag { };
struct ushort_cref_tag      : public pod_cref_tag { };
struct int_cref_tag         : public pod_cref_tag { };
struct uint_cref_tag        : public pod_cref_tag { };
struct long_cref_tag        : public pod_cref_tag { };
struct ulong_cref_tag       : public pod_cref_tag { };
struct longlong_cref_tag    : public pod_cref_tag { };
struct ulonglong_cref_tag   : public pod_cref_tag { };
#if defined(HAVE_64BIT_COORD)
struct int128_cref_tag      : public pod_cref_tag { };
#endif
struct double_cref_tag      : public pod_cref_tag { };
struct float_cref_tag       : public pod_cref_tag { };

struct vector_cref_tag      : public npod_cref_tag { };
struct map_cref_tag         : public npod_cref_tag { };
struct string_cref_tag      : public npod_cref_tag { };
struct qstring_cref_tag     : public npod_cref_tag { };
struct qbytearray_cref_tag  : public npod_cref_tag { };
struct var_cref_tag         : public npod_cref_tag { };

struct bool_ref_tag         : public pod_ref_tag { };
struct char_ref_tag         : public pod_ref_tag { };
struct uchar_ref_tag        : public pod_ref_tag { };
struct schar_ref_tag        : public pod_ref_tag { };
struct short_ref_tag        : public pod_ref_tag { };
struct ushort_ref_tag       : public pod_ref_tag { };
struct int_ref_tag          : public pod_ref_tag { };
struct uint_ref_tag         : public pod_ref_tag { };
struct long_ref_tag         : public pod_ref_tag { };
struct ulong_ref_tag        : public pod_ref_tag { };
struct longlong_ref_tag     : public pod_ref_tag { };
struct ulonglong_ref_tag    : public pod_ref_tag { };
#if defined(HAVE_64BIT_COORD)
struct int128_ref_tag       : public pod_ref_tag { };
#endif
struct double_ref_tag       : public pod_ref_tag { };
struct float_ref_tag        : public pod_ref_tag { };

struct vector_ref_tag       : public npod_ref_tag { };
struct map_ref_tag          : public npod_ref_tag { };
struct string_ref_tag       : public npod_ref_tag { };
struct qstring_ref_tag      : public npod_ref_tag { };
struct qbytearray_ref_tag   : public npod_ref_tag { };
struct var_ref_tag          : public npod_ref_tag { };

struct bool_cptr_tag        : public pod_cptr_tag { };
struct char_cptr_tag        : public pod_cptr_tag { };
struct uchar_cptr_tag       : public pod_cptr_tag { };
struct schar_cptr_tag       : public pod_cptr_tag { };
struct short_cptr_tag       : public pod_cptr_tag { };
struct ushort_cptr_tag      : public pod_cptr_tag { };
struct int_cptr_tag         : public pod_cptr_tag { };
struct uint_cptr_tag        : public pod_cptr_tag { };
struct long_cptr_tag        : public pod_cptr_tag { };
struct ulong_cptr_tag       : public pod_cptr_tag { };
struct longlong_cptr_tag    : public pod_cptr_tag { };
struct ulonglong_cptr_tag   : public pod_cptr_tag { };
#if defined(HAVE_64BIT_COORD)
struct int128_cptr_tag      : public pod_cptr_tag { };
#endif
struct double_cptr_tag      : public pod_cptr_tag { };
struct float_cptr_tag       : public pod_cptr_tag { };

struct vector_cptr_tag      : public npod_cptr_tag { };
struct map_cptr_tag         : public npod_cptr_tag { };
struct string_cptr_tag      : public npod_cptr_tag { };
struct qstring_cptr_tag     : public npod_cptr_tag { };
struct qbytearray_cptr_tag  : public npod_cptr_tag { };
struct var_cptr_tag         : public npod_cptr_tag { };

struct bool_ptr_tag         : public pod_ptr_tag { };
struct char_ptr_tag         : public pod_ptr_tag { };
struct uchar_ptr_tag        : public pod_ptr_tag { };
struct schar_ptr_tag        : public pod_ptr_tag { };
struct short_ptr_tag        : public pod_ptr_tag { };
struct ushort_ptr_tag       : public pod_ptr_tag { };
struct int_ptr_tag          : public pod_ptr_tag { };
struct uint_ptr_tag         : public pod_ptr_tag { };
struct long_ptr_tag         : public pod_ptr_tag { };
struct ulong_ptr_tag        : public pod_ptr_tag { };
struct longlong_ptr_tag     : public pod_ptr_tag { };
struct ulonglong_ptr_tag    : public pod_ptr_tag { };
#if defined(HAVE_64BIT_COORD)
struct int128_ptr_tag       : public pod_ptr_tag { };
#endif
struct double_ptr_tag       : public pod_ptr_tag { };
struct float_ptr_tag        : public pod_ptr_tag { };

struct vector_ptr_tag       : public npod_ptr_tag { };
struct map_ptr_tag          : public npod_ptr_tag { };
struct string_ptr_tag       : public npod_ptr_tag { };
struct qstring_ptr_tag      : public npod_ptr_tag { };
struct qbytearray_ptr_tag   : public npod_ptr_tag { };
struct var_ptr_tag          : public npod_ptr_tag { };

struct x_tag                : public npod_direct_tag { };
struct x_cref_tag           : public npod_cref_tag { };
struct x_cptr_tag           : public npod_cptr_tag { };
struct x_cptr_cref_tag      : public x_cptr_tag { };
struct x_cptr_ref_tag       : public x_cptr_tag { };
struct x_ref_tag            : public npod_ref_tag { };
struct x_ptr_tag            : public npod_ptr_tag { };
struct x_ptr_cref_tag       : public x_ptr_tag { };
struct x_ptr_ref_tag        : public x_ptr_tag { };


/**
 *  @brief Type traits that map a C++ type to a certain tag
 */
template <class X> struct type_traits;

template <>
struct type_traits<void>
{
  typedef void_tag tag;
  typedef void value_type;
  typedef void inner_type;
  typedef void inner_k_type;

  static bool is_pod () { return false; }
  static bool is_npod () { return false; }
  static bool is_cref () { return false; }
  static bool is_ref () { return false; }
  static bool is_cptr () { return false; }
  static bool is_ptr () { return false; }
  static BasicType code () { return T_void; }
  static const ClassBase *cls_decl () { return 0; }
  static bool is_iter () { return false; }
  static size_t serial_size () { return 0; }
};

//  see serialization notes above
template <class T>
inline size_t compute_size (const void_tag &)         { return 0; }
template <class T>
inline size_t compute_size (const basic_type_tag &)   { return item_size<T> (); }
template <class T>
inline size_t compute_size (const pod_direct_tag &)   { return item_size<T> (); }
template <class T>
inline size_t compute_size (const pod_cref_tag &)     { return item_size<T> (); }
template <class T>
inline size_t compute_size (const pod_ref_tag &)      { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const pod_cptr_tag &)     { return item_size<bool> () + item_size<T> (); }
template <class T>
inline size_t compute_size (const pod_ptr_tag &)      { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const ccptr_tag &)        { return item_size<const char *> (); }
template <class T>
inline size_t compute_size (const vptr_tag &)         { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const npod_direct_tag &)  { return item_size<T> (); }
template <class T>
inline size_t compute_size (const npod_cref_tag &)    { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const npod_ref_tag &)     { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const npod_cptr_tag &)    { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const npod_ptr_tag &)     { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const x_tag &)            { return item_size<T> (); }
template <class T>
inline size_t compute_size (const x_cref_tag &)       { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const x_ref_tag &)        { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const x_cptr_tag &)       { return item_size<void *> (); }
template <class T>
inline size_t compute_size (const x_ptr_tag &)        { return item_size<void *> (); }

//  Note: derived, "real" traits must not overwrite tag or value_type since these
//  are used by the predicates and serial_size attribute.
template <class T, class V, enum BasicType TC> 
struct generic_type_traits 
{
  typedef T tag;
  typedef V value_type;
  typedef void inner_type;
  typedef void inner_k_type;

  static bool is_pod () { return tl::value_of (typename T::is_pod ()); }
  static bool is_npod () { return tl::value_of (typename T::is_npod ()); }
  static bool is_cref () { return tl::value_of (typename T::is_cref ()); }
  static bool is_ref () { return tl::value_of (typename T::is_ref ()); }
  static bool is_cptr () { return tl::value_of (typename T::is_cptr ()); }
  static bool is_ptr () { return tl::value_of (typename T::is_ptr ()); }
  static size_t serial_size () { return compute_size<V> (T ()); }

  static BasicType code () { return TC; }
  static const ClassBase *cls_decl () { return 0; }
  static bool is_iter () { return false; }
};

template <> struct type_traits<bool>                        : generic_type_traits<bool_tag, bool, T_bool> { };
template <> struct type_traits<char>                        : generic_type_traits<char_tag, char, T_char> { };
template <> struct type_traits<signed char>                 : generic_type_traits<schar_tag, signed char, T_schar> { };
template <> struct type_traits<unsigned char>               : generic_type_traits<uchar_tag, unsigned char, T_uchar> { };
template <> struct type_traits<short>                       : generic_type_traits<short_tag, short, T_short> { };
template <> struct type_traits<unsigned short>              : generic_type_traits<ushort_tag, unsigned short, T_ushort> { };
template <> struct type_traits<int>                         : generic_type_traits<int_tag, int, T_int> { };
template <> struct type_traits<unsigned int>                : generic_type_traits<uint_tag, unsigned int, T_uint> { };
template <> struct type_traits<long>                        : generic_type_traits<long_tag, long, T_long> { };
template <> struct type_traits<unsigned long>               : generic_type_traits<ulong_tag, unsigned long, T_ulong> { };
template <> struct type_traits<long long>                   : generic_type_traits<longlong_tag, long long, T_longlong> { };
template <> struct type_traits<unsigned long long>          : generic_type_traits<ulonglong_tag, unsigned long long, T_ulonglong> { };
#if defined(HAVE_64BIT_COORD)
template <> struct type_traits<__int128>                    : generic_type_traits<int128_tag, __int128, T_int128> { };
#endif
template <> struct type_traits<double>                      : generic_type_traits<double_tag, double, T_double> { };
template <> struct type_traits<float>                       : generic_type_traits<float_tag, float, T_float> { };
template <> struct type_traits<std::string>                 : generic_type_traits<string_tag, std::string, T_string> { };
template <> struct type_traits<QString>                     : generic_type_traits<qstring_tag, QString, T_qstring> { };
template <> struct type_traits<QByteArray>                  : generic_type_traits<qbytearray_tag, QByteArray, T_qbytearray> { };
template <> struct type_traits<tl::Variant>                 : generic_type_traits<var_tag, tl::Variant, T_var> { };

template <> struct type_traits<void *>                      : generic_type_traits<vptr_tag, void *, T_void_ptr> { };
template <> struct type_traits<const void *>                : generic_type_traits<vptr_tag, void *, T_void_ptr> { };
template <> struct type_traits<const char *>                : generic_type_traits<ccptr_tag, const char *, T_string_ccptr> { };
template <> struct type_traits<const unsigned char *>       : generic_type_traits<ccptr_tag, const char *, T_string_ccptr> { };
template <> struct type_traits<const signed char *>         : generic_type_traits<ccptr_tag, const char *, T_string_ccptr> { };

template <> struct type_traits<const bool &>                : generic_type_traits<bool_cref_tag, bool, T_bool> { };
template <> struct type_traits<const char &>                : generic_type_traits<char_cref_tag, char, T_char> { };
template <> struct type_traits<const signed char &>         : generic_type_traits<schar_cref_tag, signed char, T_schar> { };
template <> struct type_traits<const unsigned char &>       : generic_type_traits<uchar_cref_tag, unsigned char, T_uchar> { };
template <> struct type_traits<const short &>               : generic_type_traits<short_cref_tag, short, T_short> { };
template <> struct type_traits<const unsigned short &>      : generic_type_traits<ushort_cref_tag, unsigned short, T_ushort> { };
template <> struct type_traits<const int &>                 : generic_type_traits<int_cref_tag, int, T_int> { };
template <> struct type_traits<const unsigned int &>        : generic_type_traits<uint_cref_tag, unsigned int, T_uint> { };
template <> struct type_traits<const long &>                : generic_type_traits<long_cref_tag, long, T_long> { };
template <> struct type_traits<const unsigned long &>       : generic_type_traits<ulong_cref_tag, unsigned long, T_ulong> { };
template <> struct type_traits<const long long &>           : generic_type_traits<longlong_cref_tag, long long, T_longlong> { };
template <> struct type_traits<const unsigned long long &>  : generic_type_traits<ulonglong_cref_tag, unsigned long long, T_ulonglong> { };
#if defined(HAVE_64BIT_COORD)
template <> struct type_traits<const __int128 &>            : generic_type_traits<int128_cref_tag, __int128, T_int128> { };
#endif
template <> struct type_traits<const double &>              : generic_type_traits<double_cref_tag, double, T_double> { };
template <> struct type_traits<const float &>               : generic_type_traits<float_cref_tag, float, T_float> { };
template <> struct type_traits<const std::string &>         : generic_type_traits<string_cref_tag, std::string, T_string> { };
template <> struct type_traits<const QString &>             : generic_type_traits<qstring_cref_tag, QString, T_qstring> { };
template <> struct type_traits<const QByteArray &>          : generic_type_traits<qbytearray_cref_tag, QByteArray, T_qbytearray> { };
template <> struct type_traits<const tl::Variant &>         : generic_type_traits<var_cref_tag, tl::Variant, T_var> { };

template <> struct type_traits<bool &>                      : generic_type_traits<bool_ref_tag, bool, T_bool> { };
template <> struct type_traits<char &>                      : generic_type_traits<char_ref_tag, char, T_char> { };
template <> struct type_traits<signed char &>               : generic_type_traits<schar_ref_tag, signed char, T_schar> { };
template <> struct type_traits<unsigned char &>             : generic_type_traits<uchar_ref_tag, unsigned char, T_uchar> { };
template <> struct type_traits<short &>                     : generic_type_traits<short_ref_tag, short, T_short> { };
template <> struct type_traits<unsigned short &>            : generic_type_traits<ushort_ref_tag, unsigned short, T_ushort> { };
template <> struct type_traits<int &>                       : generic_type_traits<int_ref_tag, int, T_int> { };
template <> struct type_traits<unsigned int &>              : generic_type_traits<uint_ref_tag, unsigned int, T_uint> { };
template <> struct type_traits<long &>                      : generic_type_traits<long_ref_tag, long, T_long> { };
template <> struct type_traits<unsigned long &>             : generic_type_traits<ulong_ref_tag, unsigned long, T_ulong> { };
template <> struct type_traits<long long &>                 : generic_type_traits<longlong_ref_tag, long long, T_longlong> { };
template <> struct type_traits<unsigned long long &>        : generic_type_traits<ulonglong_ref_tag, unsigned long long, T_ulonglong> { };
#if defined(HAVE_64BIT_COORD)
template <> struct type_traits<__int128 &>                  : generic_type_traits<int128_ref_tag, __int128, T_int128> { };
#endif
template <> struct type_traits<double &>                    : generic_type_traits<double_ref_tag, double, T_double> { };
template <> struct type_traits<float &>                     : generic_type_traits<float_ref_tag, float, T_float> { };
template <> struct type_traits<std::string &>               : generic_type_traits<string_ref_tag, std::string, T_string> { };
template <> struct type_traits<QString &>                   : generic_type_traits<qstring_ref_tag, QString, T_qstring> { };
template <> struct type_traits<QByteArray &>                : generic_type_traits<qbytearray_ref_tag, QByteArray, T_qbytearray> { };
template <> struct type_traits<tl::Variant &>               : generic_type_traits<var_ref_tag, tl::Variant, T_var> { };

template <> struct type_traits<const bool *>                : generic_type_traits<bool_cptr_tag, bool, T_bool> { };
// that is bound to a string, not a single char
// template <> struct type_traits<const char *>             : generic_type_traits<char_cptr_tag, char, T_char> { };
// template <> struct type_traits<const unsigned char *>       : generic_type_traits<uchar_cptr_tag, unsigned char, T_uchar> { };
// template <> struct type_traits<const signed char *>         : generic_type_traits<schar_cptr_tag, signed char, T_schar> { };
template <> struct type_traits<const short *>               : generic_type_traits<short_cptr_tag, short, T_short> { };
template <> struct type_traits<const unsigned short *>      : generic_type_traits<ushort_cptr_tag, unsigned short, T_ushort> { };
template <> struct type_traits<const int *>                 : generic_type_traits<int_cptr_tag, int, T_int> { };
template <> struct type_traits<const unsigned int *>        : generic_type_traits<uint_cptr_tag, unsigned int, T_uint> { };
template <> struct type_traits<const long *>                : generic_type_traits<long_cptr_tag, long, T_long> { };
template <> struct type_traits<const unsigned long *>       : generic_type_traits<ulong_cptr_tag, unsigned long, T_ulong> { };
template <> struct type_traits<const long long *>           : generic_type_traits<longlong_cptr_tag, long long, T_longlong> { };
template <> struct type_traits<const unsigned long long *>  : generic_type_traits<ulonglong_cptr_tag, unsigned long long, T_ulonglong> { };
#if defined(HAVE_64BIT_COORD)
template <> struct type_traits<const __int128 *>            : generic_type_traits<int128_cptr_tag, __int128, T_int128> { };
#endif
template <> struct type_traits<const double *>              : generic_type_traits<double_cptr_tag, double, T_double> { };
template <> struct type_traits<const float *>               : generic_type_traits<float_cptr_tag, float, T_float> { };
template <> struct type_traits<const std::string *>         : generic_type_traits<string_cptr_tag, std::string, T_string> { };
template <> struct type_traits<const QString *>             : generic_type_traits<qstring_cptr_tag, QString, T_qstring> { };
template <> struct type_traits<const QByteArray *>          : generic_type_traits<qbytearray_cptr_tag, QByteArray, T_qbytearray> { };
template <> struct type_traits<const tl::Variant *>         : generic_type_traits<var_cptr_tag, tl::Variant, T_var> { };

template <> struct type_traits<bool *>                      : generic_type_traits<bool_ptr_tag, bool, T_bool> { };
// that is not bound to avoid interpretation problems between string and char *
// template <> struct type_traits<char *>                   : generic_type_traits<char_ptr_tag, char, T_char> { };
// template <> struct type_traits<signed char *>               : generic_type_traits<schar_ptr_tag, signed char, T_schar> { };
// template <> struct type_traits<unsigned char *>             : generic_type_traits<uchar_ptr_tag, unsigned char, T_uchar> { };
template <> struct type_traits<short *>                     : generic_type_traits<short_ptr_tag, short, T_short> { };
template <> struct type_traits<unsigned short *>            : generic_type_traits<ushort_ptr_tag, unsigned short, T_ushort> { };
template <> struct type_traits<int *>                       : generic_type_traits<int_ptr_tag, int, T_int> { };
template <> struct type_traits<unsigned int *>              : generic_type_traits<uint_ptr_tag, unsigned int, T_uint> { };
template <> struct type_traits<long *>                      : generic_type_traits<long_ptr_tag, long, T_long> { };
template <> struct type_traits<unsigned long *>             : generic_type_traits<ulong_ptr_tag, unsigned long, T_ulong> { };
template <> struct type_traits<long long *>                 : generic_type_traits<longlong_ptr_tag, long long, T_longlong> { };
template <> struct type_traits<unsigned long long *>        : generic_type_traits<ulonglong_ptr_tag, unsigned long long, T_ulonglong> { };
#if defined(HAVE_64BIT_COORD)
template <> struct type_traits<__int128 *>                  : generic_type_traits<int128_ptr_tag, __int128, T_int128> { };
#endif
template <> struct type_traits<double *>                    : generic_type_traits<double_ptr_tag, double, T_double> { };
template <> struct type_traits<float *>                     : generic_type_traits<float_ptr_tag, float, T_float> { };
template <> struct type_traits<std::string *>               : generic_type_traits<string_ptr_tag, std::string, T_string> { };
template <> struct type_traits<QString *>                   : generic_type_traits<qstring_ptr_tag, QString, T_qstring> { };
template <> struct type_traits<QByteArray *>                : generic_type_traits<qbytearray_ptr_tag, QByteArray, T_qbytearray> { };
template <> struct type_traits<tl::Variant *>               : generic_type_traits<var_ptr_tag, tl::Variant, T_var> { };

template <class X>
struct type_traits<const X>
  : generic_type_traits<typename type_traits<X>::tag, typename type_traits<X>::value_type, T_void>
{
  static BasicType code () { return type_traits<X>::code (); }
  static const ClassBase *cls_decl () { return type_traits<X>::cls_decl (); }
};

template <class X>
struct type_traits
  : generic_type_traits<x_tag, X, T_object>
{
  static const ClassBase *cls_decl () { return gsi::cls_decl<X> (); }
};

template <class X>
struct type_traits<const X &>
  : generic_type_traits<x_cref_tag, X, T_object>
{
  static const ClassBase *cls_decl () { return gsi::cls_decl<X> (); }
};

template <class X>
struct type_traits<const X *>
  : generic_type_traits<x_cptr_tag, X, T_object>
{
  static const ClassBase *cls_decl () { return gsi::cls_decl<X> (); }
};

template <class X>
struct type_traits<const X * const &>
  : generic_type_traits<x_cptr_cref_tag, X, T_object>
{
  static const ClassBase *cls_decl () { return gsi::cls_decl<X> (); }
};

template <class X>
struct type_traits<const X * &>
  : generic_type_traits<x_cptr_ref_tag, X, T_object>
{
  static const ClassBase *cls_decl () { return gsi::cls_decl<X> (); }
};

template <class X>
struct type_traits<X &>
  : generic_type_traits<x_ref_tag, X, T_object>
{
  static const ClassBase *cls_decl () { return gsi::cls_decl<X> (); }
};

template <class X>
struct type_traits<X *>
  : generic_type_traits<x_ptr_tag, X, T_object>
{
  static const ClassBase *cls_decl () { return gsi::cls_decl<X> (); }
};

template <class X>
struct type_traits<X * const &>
  : generic_type_traits<x_ptr_cref_tag, X, T_object>
{
  static const ClassBase *cls_decl () { return gsi::cls_decl<X> (); }
};

template <class X>
struct type_traits<X * &>
  : generic_type_traits<x_ptr_ref_tag, X, T_object>
{
  static const ClassBase *cls_decl () { return gsi::cls_decl<X> (); }
};

template <class X>
struct type_traits< std::vector<X> >
  : generic_type_traits<vector_tag, std::vector<X>, T_vector>
{
  typedef X inner_type;
};

template <class X>
struct type_traits< const std::vector<X> & >
  : generic_type_traits<vector_cref_tag, std::vector<X>, T_vector>
{
  typedef X inner_type;
};

template <class X>
struct type_traits< std::vector<X> & >
  : generic_type_traits<vector_ref_tag, std::vector<X>, T_vector>
{
  typedef X inner_type;
};

template <class X>
struct type_traits< const std::vector<X> * >
  : generic_type_traits<vector_cptr_tag, std::vector<X>, T_vector>
{
  typedef X inner_type;
};

template <class X>
struct type_traits< std::vector<X> * >
  : generic_type_traits<vector_ptr_tag, std::vector<X>, T_vector>
{
  typedef X inner_type;
};

template <class X, class Y>
struct type_traits< std::map<X, Y> >
  : generic_type_traits<map_tag, std::map<X, Y>, T_map>
{
  typedef X inner_k_type;
  typedef Y inner_type;
};

template <class X, class Y>
struct type_traits< const std::map<X, Y> & >
  : generic_type_traits<map_cref_tag, std::map<X, Y>, T_map>
{
  typedef X inner_k_type;
  typedef Y inner_type;
};

template <class X, class Y>
struct type_traits< std::map<X, Y> & >
  : generic_type_traits<map_ref_tag, std::map<X, Y>, T_map>
{
  typedef X inner_k_type;
  typedef Y inner_type;
};

template <class X, class Y>
struct type_traits< const std::map<X, Y> * >
  : generic_type_traits<map_cptr_tag, std::map<X, Y>, T_map>
{
  typedef X inner_k_type;
  typedef Y inner_type;
};

template <class X, class Y>
struct type_traits< std::map<X, Y> * >
  : generic_type_traits<map_ptr_tag, std::map<X, Y>, T_map>
{
  typedef X inner_k_type;
  typedef Y inner_type;
};

template <class I, class R, class V>
struct type_traits< IterAdaptor<I, R, V> >
  : generic_type_traits<typename type_traits<R>::tag, typename type_traits<R>::value_type, T_void>
{
  static BasicType code () { return type_traits<R>::code (); }
  static const ClassBase *cls_decl () { return type_traits<R>::cls_decl (); }
  static bool is_iter () { return true; }
};

template <class R, class V>
struct type_traits< IterPtrAdaptor<R, V> >
  : generic_type_traits<typename type_traits<R>::tag, typename type_traits<R>::value_type, T_void>
{
  static BasicType code () { return type_traits<R>::code (); }
  static const ClassBase *cls_decl () { return type_traits<R>::cls_decl (); }
  static bool is_iter () { return true; }
};

template <class R, class V>
struct type_traits< ConstIterPtrAdaptor<R, V> >
  : generic_type_traits<typename type_traits<R>::tag, typename type_traits<R>::value_type, T_void>
{
  static BasicType code () { return type_traits<R>::code (); }
  static const ClassBase *cls_decl () { return type_traits<R>::cls_decl (); }
  static bool is_iter () { return true; }
};

template <class I, class R, class V>
struct type_traits< FreeIterAdaptor<I, R, V> >
  : generic_type_traits<typename type_traits<R>::tag, typename type_traits<R>::value_type, T_void>
{
  static BasicType code () { return type_traits<R>::code (); }
  static const ClassBase *cls_decl () { return type_traits<R>::cls_decl (); }
  static bool is_iter () { return true; }
};

template <class X> class ArgSpec;

/**
 *  @brief A generic argument specification class
 *
 *  This class provides an optional argument name and initialization.
 *  The base class provides the interface, specializations the actual code
 */
class KLAYOUT_DLL ArgSpecBase
{
public:
  ArgSpecBase ()
    : m_name (), m_has_default (false) 
  { }

  ArgSpecBase (const std::string &name)
    : m_name (name), m_has_default (false) 
  { }

  ArgSpecBase (const std::string &name, bool has_default, const std::string &init_doc = std::string ()) 
    : m_name (name), m_init_doc (init_doc), m_has_default (has_default) 
  { }
  
  virtual ~ArgSpecBase () { }
  
  const std::string &name () const 
  { 
    return m_name; 
  }

  const std::string &init_doc () const 
  { 
    return m_init_doc; 
  }

  bool has_default () const
  {
    return m_has_default;
  }

  virtual tl::Variant default_value () const 
  {
    return tl::Variant ();
  }

  virtual ArgSpecBase *clone () const
  {
    return new ArgSpecBase (*this);
  }

private:
  std::string m_name, m_init_doc;
  bool m_has_default;
};

/**
 *  @brief A specialization for void
 */
template <>
class ArgSpec<void>
  : public ArgSpecBase
{
public:
  typedef void init_type;

  ArgSpec () 
    : ArgSpecBase (std::string (), false)
  { }

  ArgSpec (const ArgSpec<void> &other)
    : ArgSpecBase (other)
  { }

  template <class Q>
  ArgSpec (const ArgSpec<Q> &other)
    : ArgSpecBase (other)
  { }

  ArgSpec (const std::string &name)
    : ArgSpecBase (name, false)
  { }

  virtual ArgSpecBase *clone () const
  {
    return new ArgSpec<void> (*this);
  }

  void init () const
  {
    //  TODO: throw exception
    tl_assert (false);
  }

  tl::Variant default_value () const
  {
    return tl::Variant ();
  }
};

/**
 *  @brief An implementation helper that provides a switch between classes having and having no copy ctor 
 */
template <class T, class CC>
class ArgSpecImpl 
  : public ArgSpecBase
{
public:
  typedef const T &init_type;

  ArgSpecImpl () 
    : ArgSpecBase (std::string (), false)
  { }

  ArgSpecImpl (const ArgSpec<void> &other)
    : ArgSpecBase (other)
  { }

  template <class Q>
  ArgSpecImpl (const ArgSpec<Q> &other)
    : ArgSpecBase (other)
  { }

  ArgSpecImpl (const std::string &name)
    : ArgSpecBase (name, false)
  { }

  virtual ArgSpecBase *clone () const
  {
    return new ArgSpecImpl (*this);
  }

  const T &init () const
  {
    //  should never happen
    tl_assert (false);
  }

  tl::Variant default_value () const
  {
    return tl::Variant ();
  }
};

/**
 *  @brief A specialization for classes with default and copy ctor
 */
template <class T>
class ArgSpecImpl<T, tl::true_tag>
  : public ArgSpecBase
{
public:
  typedef const T &init_type;

  ArgSpecImpl () 
    : ArgSpecBase (std::string (), false), mp_init (0)
  { }

  ArgSpecImpl (const ArgSpec<void> &other)
    : ArgSpecBase (other), mp_init (0)
  { }

  template <class Q>
  ArgSpecImpl (const ArgSpec<Q> &other)
    : ArgSpecBase (other), mp_init (0)
  { 
    if (other.has_init ()) {
      mp_init = new T (other.init ());
    } 
  }

  ArgSpecImpl (const ArgSpecImpl &other) 
    : ArgSpecBase (other), mp_init (0)
  {
    if (other.has_init ()) {
      mp_init = new T (other.init ());
    } 
  }

  ArgSpecImpl &operator= (const ArgSpecImpl &other) 
  {
    if (this != &other) {
      ArgSpecBase::operator= (other);
      if (mp_init) {
        delete mp_init;
        mp_init = 0;
      }
      if (other.has_init ()) {
        mp_init = new T (other.init ());
      } 
    }
    return *this;
  }

  ArgSpecImpl (const std::string &name)
    : ArgSpecBase (name, false), mp_init (0)
  { }

  ArgSpecImpl (const std::string &name, const T &init)
    : ArgSpecBase (name, true), mp_init (new T (init))
  { }

  ArgSpecImpl (const std::string &name, const T &init, const std::string &init_doc)
    : ArgSpecBase (name, true, init_doc), mp_init (new T (init))
  { }

  ~ArgSpecImpl ()
  {
    if (mp_init) {
      delete mp_init;
      mp_init = 0;
    }
  }

  virtual ArgSpecBase *clone () const
  {
    return new ArgSpecImpl (*this);
  }
  
  bool has_init () const
  {
    return mp_init != 0;
  }

  const T &init () const
  {
    tl_assert (mp_init != 0);
    return *mp_init;
  }

  tl::Variant default_value () const
  {
    if (mp_init) {
      return tl::Variant (*mp_init);
    } else {
      return tl::Variant ();
    }
  }

private:
  T *mp_init;
};

/**
 *  @brief The generic implementation
 */
template <class T>
class ArgSpec
  : public ArgSpecImpl<T, typename tl::type_traits<T>::has_copy_constructor>
{
public:
  typedef typename tl::type_traits<T>::has_copy_constructor cc_type;

  ArgSpec () 
    : ArgSpecImpl<T, cc_type> ()
  { }

  ArgSpec (const ArgSpec<void> &other)
    : ArgSpecImpl<T, cc_type> (other)
  { }

  template <class Q>
  ArgSpec (const ArgSpec<Q> &other)
    : ArgSpecImpl<T, cc_type> (other)
  { }

  ArgSpec (const std::string &name)
    : ArgSpecImpl<T, cc_type> (name)
  { }

  ArgSpec (const std::string &name, const T &init, const std::string &init_doc = std::string ())
    : ArgSpecImpl<T, cc_type> (name, init, init_doc)
  { }

  virtual ArgSpecBase *clone () const
  {
    return new ArgSpec (*this);
  }
};

/**
 *  @brief The generic implementation for const references
 */
template <class T>
class ArgSpec<const T &>
  : public ArgSpecImpl<T, typename tl::type_traits<T>::has_copy_constructor>
{
public:
  typedef typename tl::type_traits<T>::has_copy_constructor cc_type;

  ArgSpec () 
    : ArgSpecImpl<T, cc_type> ()
  { }

  ArgSpec (const ArgSpec<void> &other)
    : ArgSpecImpl<T, cc_type> (other)
  { }

  template <class Q>
  ArgSpec (const ArgSpec<Q> &other)
    : ArgSpecImpl<T, cc_type> (other)
  { }

  ArgSpec (const std::string &name)
    : ArgSpecImpl<T, cc_type> (name)
  { }

  ArgSpec (const std::string &name, const T &init, const std::string &init_doc = std::string ())
    : ArgSpecImpl<T, cc_type> (name, init, init_doc)
  { }

  virtual ArgSpecBase *clone () const
  {
    return new ArgSpec (*this);
  }
};

/**
 *  @brief The generic implementation for references
 */
template <class T>
class ArgSpec<T &>
  : public ArgSpecImpl<T, typename tl::type_traits<T>::has_copy_constructor>
{
public:
  typedef T &init_type;
  typedef typename tl::type_traits<T>::has_copy_constructor cc_type;

  ArgSpec () 
    : ArgSpecImpl<T, cc_type> ()
  { }

  ArgSpec (const ArgSpec<void> &other)
    : ArgSpecImpl<T, cc_type> (other)
  { }

  template <class Q>
  ArgSpec (const ArgSpec<Q> &other)
    : ArgSpecImpl<T, cc_type> (other)
  { }

  ArgSpec (const std::string &name)
    : ArgSpecImpl<T, cc_type> (name)
  { }

  ArgSpec (const std::string &name, const T &init, const std::string &init_doc = std::string ())
    : ArgSpecImpl<T, cc_type> (name, init, init_doc)
  { }

  T &init () const
  {
    //  this simplifies the implementation, but it's not really clean since the caller may modify the default.
    return const_cast<T &> (ArgSpecImpl<T, cc_type>::init ());
  }

  virtual ArgSpecBase *clone () const
  {
    return new ArgSpec (*this);
  }
};

/**
 *  @brief Generic argument type declaration
 *
 *  The type declaration carries the basic type code and flags, if the argument 
 *  is an iterator delivering the given types of a vector of the given types and
 *  adds class informations if the type is "T_object", "T_object_ref", "T_object_cref". 
 */
struct KLAYOUT_DLL ArgType
{
  /**
   *  @brief Default constructor
   *
   *  Creates a void type
   */
  ArgType ();

  /**
   *  @brief Copy ctor
   */
  ArgType (const ArgType &other);

  /**
   *  @brief Destructor
   */
  ~ArgType ();

  /**
   *  @brief Assignment
   */
  ArgType &operator= (const ArgType &other);

  /**
   *  @brief Initializes with an external specification
   *
   *  This method will initialize the type object referring to an external
   *  spec object. The spec object will specify name and default
   *  value for arguments
   */
  template <class X>
  void init (const ArgSpecBase &spec)
  {
    init<X> ();
    mp_spec = &spec;
    m_owns_spec = false;
  }

  /**
   *  @brief Initializes with a specification
   *
   *  This method will initialize the type object with a specification.
   *  The ownership over the specification object will be transferred to
   *  the type object.
   */
  template <class X>
  void init (ArgSpecBase *spec)
  {
    init<X> ();
    mp_spec = spec;
    m_owns_spec = true;
  }

  /**
   *  @brief Initialize the type from a given type X
   *  If "pass_obj" is true, the receiver of an object will always
   *  take over the ownership over the passed object. This applies
   *  to the case of object pointers mainly.
   */
  template <class X>
  void init (bool pass_obj = false) 
  { 
    release_spec ();

    m_type        = type_traits<X>::code ();
    m_is_iter     = type_traits<X>::is_iter ();
    mp_cls        = type_traits<X>::cls_decl ();

    m_pass_obj    = pass_obj;
    m_is_ref      = type_traits<X>::is_ref ();
    m_is_ptr      = type_traits<X>::is_ptr ();
    m_is_cref     = type_traits<X>::is_cref ();
    m_is_cptr     = type_traits<X>::is_cptr ();
    m_size        = type_traits<X>::serial_size ();

    if (mp_inner) {
      delete mp_inner;
      mp_inner = 0;
    }

    if (mp_inner_k) {
      delete mp_inner_k;
      mp_inner_k = 0;
    }

    if (type_traits<typename type_traits<X>::inner_type>::code () != T_void) {
      mp_inner = new ArgType;
      mp_inner->init<typename type_traits<X>::inner_type> ();
    }

    if (type_traits<typename type_traits<X>::inner_k_type>::code () != T_void) {
      mp_inner_k = new ArgType;
      mp_inner_k->init<typename type_traits<X>::inner_k_type> ();
    }
  }

  /**
   *  @brief Checks whether the type and the given type are equivalent
   */
  void check_type (const ArgType &a) const;

  /**
   *  @brief Equality of the types
   *
   *  The equality operator does not check the specification objects.
   */
  bool operator== (const ArgType &b) const;

  /**
   *  @brief Inequality
   */
  bool operator!= (const ArgType &b) const
  {
    return !operator== (b);
  }

  /**
   *  @brief Conversion to a string
   *
   *  This method will produce the C++ type notation from this type.
   */
  std::string to_string () const;

  /**
   *  @brief Gets the default value for the given type T
   *
   *  The type T must be the one with which the type object 
   *  was initialized.
   */
  template <class T> 
  typename ArgSpec<T>::init_type default_value () const
  {
    const ArgSpec<T> *arg_spec = dynamic_cast<const ArgSpec<T> *> (mp_spec);
    tl_assert (arg_spec != 0);
    return arg_spec->init ();
  }

  /**
   *  @brief Gets the type code
   */
  BasicType type () const
  {
    return m_type;
  }

  /**
   *  @brief Sets the type code
   */
  void set_type (BasicType t) 
  {
    m_type = t;
  }

  /**
   *  @brief Gets the specification object or 0 if there is none
   */
  const ArgSpecBase *spec () const
  {
    return mp_spec;
  }

  /**
   *  @brief Returns a value indicating that the ownership of a passed object is transfered to the receiver
   */
  bool pass_obj () const
  {
    return m_pass_obj;
  }

  /**
   *  @brief Sets a value indicating that the ownership of a passed object is transfered to the receiver
   */
  void set_pass_obj (bool b) 
  {
    m_pass_obj = b;
  }

  /**
   *  @brief Returns a value indicating whether the type is a reference
   */
  bool is_ref () const
  {
    return m_is_ref;
  }

  /**
   *  @brief Sets a value indicating whether the type is a reference
   */
  void set_is_ref (bool b) 
  {
    m_is_ref = b;
  }

  /**
   *  @brief Returns a value indicating whether the type is a pointer
   */
  bool is_ptr () const
  {
    return m_is_ptr;
  }

  /**
   *  @brief Sets a value indicating whether the type is a pointer
   */
  void set_is_ptr (bool b) 
  {
    m_is_ptr = b;
  }

  /**
   *  @brief Returns a value indicating whether the type is a const reference
   */
  bool is_cref () const
  {
    return m_is_cref;
  }

  /**
   *  @brief Sets a value indicating whether the type is a const reference
   */
  void set_is_cref (bool b) 
  {
    m_is_cref = b;
  }

  /**
   *  @brief Returns a value indicating whether the type is a const pointer
   */
  bool is_cptr () const
  {
    return m_is_cptr;
  }

  /**
   *  @brief Sets a value indicating whether the type is a const pointer
   */
  void set_is_cptr (bool b) 
  {
    m_is_cptr = b;
  }

  /**
   *  @brief Returns a value indicating whether the type is an iterator
   */
  bool is_iter () const
  {
    return m_is_iter;
  }

  /**
   *  @brief Sets a value indicating whether the type is an iterator
   */
  void set_is_iter (bool b) 
  {
    m_is_iter = b;
  }

  /**
   *  @brief Returns the size (in bytes) on the call stack
   */
  unsigned int size () const
  {
    return m_size;
  }

  /**
   *  @brief Returns the class descriptor if the type is an object
   */
  const ClassBase *cls () const
  {
    return mp_cls;
  }

  /**
   *  @brief Sets the class descriptor 
   */
  void set_cls (const ClassBase *cls) 
  {
    mp_cls = cls;
  }

  /**
   *  @brief Returns a pointer to the inner type (i.e. value type of an array) or 0 if there is no inner type
   */
  const ArgType *inner () const
  {
    return mp_inner;
  }

  /**
   *  @brief Returns a pointer to the inner key type (i.e. key type of an hash) or 0 if there is no inner type
   */
  const ArgType *inner_k () const
  {
    return mp_inner_k;
  }

private:
  BasicType m_type;
  const ArgSpecBase *mp_spec;
  ArgType *mp_inner, *mp_inner_k;
  bool m_is_ref : 1;
  bool m_is_ptr : 1;
  bool m_is_cref : 1;
  bool m_is_cptr : 1;
  bool m_is_iter : 1;
  bool m_owns_spec : 1;
  bool m_pass_obj : 1;
  mutable const ClassBase *mp_cls;
  unsigned int m_size;

  void release_spec ();
};

struct KLAYOUT_DLL IncompatibleTypeException
  : public tl::Exception
{
  IncompatibleTypeException (const ArgType &got, const ArgType &want)
    : tl::Exception (tl::to_string (QObject::tr ("Incompatible types: got '")) + got.to_string () + tl::to_string (QObject::tr ("', want '")) + want.to_string () + "'")
  { }
};

inline void ArgType::check_type (const ArgType &a) const
{
  if (*this != a) {
    throw IncompatibleTypeException (a, *this);
  }
}

// ---------------------------------------------------------------------------------
//  Utility: determine non-case "base" of X (nc_x(const X) == X)

template <class X>
struct non_const_x {
  typedef X nc_x;
};

template <class X>
struct non_const_x<const X> {
  typedef X nc_x;
};

// ---------------------------------------------------------------------------------
//  Utility: determine, if X is const 

template <class X>
struct is_const_x {
  static bool value () { return false; }
};

template <class X>
struct is_const_x<const X> {
  static bool value () { return true; }
};

// ---------------------------------------------------------------------------------
//  Utility: type dispatcher (enum to C++ type)

template <class F, class A1, class A2, class A3, class A4>
struct call_variadic_function
{
  inline void operator() (const A1 *arg1, const A2 *arg2, const A3 *arg3, const A4 *arg4)
  {
    F() (*arg1, *arg2, *arg3, *arg4);
  }
};

template <class F, class A1, class A2, class A3>
struct call_variadic_function<F, A1, A2, A3, void> 
{
  inline void operator() (const A1 *arg1, const A2 *arg2, const A3 *arg3, const void *)
  {
    F() (*arg1, *arg2, *arg3);
  }
};

template <class F, class A1, class A2>
struct call_variadic_function<F, A1, A2, void, void> 
{
  inline void operator() (const A1 *arg1, const A2 *arg2, const void *, const void *)
  {
    F() (*arg1, *arg2);
  }
};

template <class F, class A1>
struct call_variadic_function<F, A1, void, void, void> 
{
  inline void operator() (const A1 *arg1, const void *, const void *, const void *)
  {
    F() (*arg1);
  }
};

template <class F>
struct call_variadic_function<F, void, void, void, void> 
{
  inline void operator() (const void *, const void *, const void *, const void *)
  {
    F() ();
  }
};

/**
 *  @brief Represents "T_object" as a C++ type
 */
struct ObjectType { };

/**
 *  @brief Represents "T_vector" as a C++ type
 */
struct VectorType { };

/**
 *  @brief Represents "T_map" as a C++ type
 */
struct MapType { };

/**
 *  @brief Represents "T_void" as a C++ type
 */
struct VoidType { };

template <template<class> class F, class A1, class A2, class A3, class A4>
void do_on_type_impl (gsi::BasicType type, const A1 *arg1, const A2 *arg2, const A3 *arg3, const A4 *arg4)
{
  switch (type) {
  case gsi::T_bool:     
    call_variadic_function<F<bool>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_char:      
    call_variadic_function<F<char>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_schar:     
    call_variadic_function<F<signed char>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_uchar:     
    call_variadic_function<F<unsigned char>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_short:      
    call_variadic_function<F<short>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_ushort:     
    call_variadic_function<F<unsigned short>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_int:      
    call_variadic_function<F<int>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_uint:     
    call_variadic_function<F<unsigned int>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_long:     
    call_variadic_function<F<long>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_ulong:    
    call_variadic_function<F<unsigned long>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_longlong:     
    call_variadic_function<F<long long>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_ulonglong:     
    call_variadic_function<F<unsigned long long>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
#if defined(HAVE_64BIT_COORD)
  case gsi::T_int128:     
    call_variadic_function<F<__int128>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
#endif
  case gsi::T_double:   
    call_variadic_function<F<double>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_float:   
    call_variadic_function<F<float>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_void_ptr:   
    call_variadic_function<F<void *>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_string_ccptr:   
    call_variadic_function<F<const char *>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_string:   
    call_variadic_function<F<std::string>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_qstring:   
    call_variadic_function<F<QString>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_qbytearray:   
    call_variadic_function<F<QByteArray>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_var:   
    call_variadic_function<F<tl::Variant>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_object:   
    call_variadic_function<F<ObjectType>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_vector:   
    call_variadic_function<F<VectorType>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_map:   
    call_variadic_function<F<MapType>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_void:   
    call_variadic_function<F<VoidType>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  }
}

template <class T1, template<class, class> class F, class A1, class A2, class A3, class A4>
void do_on_type_impl_second (gsi::BasicType type, const A1 *arg1, const A2 *arg2, const A3 *arg3, const A4 *arg4)
{
  switch (type) {
  default:
    break;
  case gsi::T_bool:     
    call_variadic_function<F<T1, bool>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_char:      
    call_variadic_function<F<T1, char>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_schar:     
    call_variadic_function<F<T1, signed char>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_uchar:     
    call_variadic_function<F<T1, unsigned char>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_short:      
    call_variadic_function<F<T1, short>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_ushort:     
    call_variadic_function<F<T1, unsigned short>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_int:      
    call_variadic_function<F<T1, int>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_uint:     
    call_variadic_function<F<T1, unsigned int>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_long:     
    call_variadic_function<F<T1, long>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_ulong:    
    call_variadic_function<F<T1, unsigned long>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_longlong:     
    call_variadic_function<F<T1, long long>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_ulonglong:     
    call_variadic_function<F<T1, unsigned long long>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
#if defined(HAVE_64BIT_COORD)
  case gsi::T_int128:     
    call_variadic_function<F<T1, __int128>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
#endif
  case gsi::T_double:   
    call_variadic_function<F<T1, double>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_float:   
    call_variadic_function<F<T1, float>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_void_ptr:   
    call_variadic_function<F<T1, void *>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_string_ccptr:   
    call_variadic_function<F<T1, const char *>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_string:   
    call_variadic_function<F<T1, std::string>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_qstring:   
    call_variadic_function<F<T1, QString>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_qbytearray:   
    call_variadic_function<F<T1, QByteArray>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_var:   
    call_variadic_function<F<T1, tl::Variant>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_object:   
    call_variadic_function<F<T1, ObjectType>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_vector:   
    call_variadic_function<F<T1, VectorType>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_map:   
    call_variadic_function<F<T1, MapType>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  case gsi::T_void:   
    call_variadic_function<F<T1, VoidType>, A1, A2, A3, A4> () (arg1, arg2, arg3, arg4);
    break;
  }
}

template <template<class, class> class F, class A1, class A2, class A3, class A4>
void do_on_type_impl2 (gsi::BasicType type1, gsi::BasicType type2, const A1 *arg1, const A2 *arg2, const A3 *arg3, const A4 *arg4)
{
  switch (type1) {
  default:
    break;
  case gsi::T_bool:     
    do_on_type_impl_second<bool, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_char:      
    do_on_type_impl_second<char, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_schar:     
    do_on_type_impl_second<signed char, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_uchar:     
    do_on_type_impl_second<unsigned char, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_short:      
    do_on_type_impl_second<short, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_ushort:     
    do_on_type_impl_second<unsigned short, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_int:      
    do_on_type_impl_second<int, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_uint:     
    do_on_type_impl_second<unsigned int, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_long:     
    do_on_type_impl_second<long, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_ulong:    
    do_on_type_impl_second<unsigned long, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_longlong:     
    do_on_type_impl_second<long long, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_ulonglong:     
    do_on_type_impl_second<unsigned long long, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
#if defined(HAVE_64BIT_COORD)
  case gsi::T_int128:     
    do_on_type_impl_second<__int128, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
#endif
  case gsi::T_double:   
    do_on_type_impl_second<double, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_float:   
    do_on_type_impl_second<float, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_void_ptr:   
    do_on_type_impl_second<void *, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_string_ccptr:   
    do_on_type_impl_second<const char *, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_string:   
    do_on_type_impl_second<std::string, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_qstring:   
    do_on_type_impl_second<QString, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_qbytearray:   
    do_on_type_impl_second<QByteArray, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_var:   
    do_on_type_impl_second<tl::Variant, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_object:   
    do_on_type_impl_second<ObjectType, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_vector:   
    do_on_type_impl_second<VectorType, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_map:   
    do_on_type_impl_second<MapType, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  case gsi::T_void:   
    do_on_type_impl_second<VoidType, F, A1, A2, A3, A4> (type2, arg1, arg2, arg3, arg4);
    break;
  }
}

/**
 *  @brief Another utility to map a type enum to a type
 *
 *  Is must be used this way:
 *
 *  template <class X>
 *  struct func {
 *    void operator() (int x, ...) { do_it_with_X; }  //  arguments can be any type
 *  };
 *
 *  if (! do_on_type<func>()(type, passed_as_arg1, ...)) {
 *    do_it_with_other_types(type);
 *  }
 */

template <template<class> class F>
struct do_on_type
{
  template <class A1>
  void operator() (gsi::BasicType type, const A1 &arg1)
  {
    do_on_type_impl<F, A1, void, void, void> (type, &arg1, 0, 0, 0);
  }

  template <class A1, class A2>
  void operator() (gsi::BasicType type, const A1 &arg1, const A2 &arg2)
  {
    do_on_type_impl<F, A1, A2, void, void> (type, &arg1, &arg2, 0, 0);
  }

  template <class A1, class A2, class A3>
  void operator() (gsi::BasicType type, const A1 &arg1, const A2 &arg2, const A3 &arg3)
  {
    do_on_type_impl<F, A1, A2, A3, void> (type, &arg1, &arg2, &arg3, 0);
  }

  template <class A1, class A2, class A3, class A4>
  void operator() (gsi::BasicType type, const A1 &arg1, const A2 &arg2, const A3 &arg3, const A4 &arg4)
  {
    do_on_type_impl<F, A1, A2, A3, A4> (type, &arg1, &arg2, &arg3, &arg4);
  }
};

/**
 *  @brief Another utility to map two type enums to two types (for maps for example)
 *
 *  Is must be used this way:
 *
 *  template <class X, class Y>
 *  struct func {
 *    void operator() (int x, ...) { do_it_with_X; }  //  arguments can be any type
 *  };
 *
 *  if (! do_on_type2<func>()(type1, type2, passed_as_arg1, ...)) {
 *    do_it_with_other_types(type);
 *  }
 */

template <template<class, class> class F2>
struct do_on_type2
{
  template <class A1>
  void operator() (gsi::BasicType type1, gsi::BasicType type2, const A1 &arg1)
  {
    do_on_type_impl2<F2, A1, void, void, void> (type1, type2, &arg1, 0, 0, 0);
  }

  template <class A1, class A2>
  void operator() (gsi::BasicType type1, gsi::BasicType type2, const A1 &arg1, const A2 &arg2)
  {
    do_on_type_impl2<F2, A1, A2, void, void> (type1, type2, &arg1, &arg2, 0, 0);
  }

  template <class A1, class A2, class A3>
  void operator() (gsi::BasicType type1, gsi::BasicType type2, const A1 &arg1, const A2 &arg2, const A3 &arg3)
  {
    do_on_type_impl2<F2, A1, A2, A3, void> (type1, type2, &arg1, &arg2, &arg3, 0);
  }

  template <class A1, class A2, class A3, class A4>
  void operator() (gsi::BasicType type1, gsi::BasicType type2, const A1 &arg1, const A2 &arg2, const A3 &arg3, const A4 &arg4)
  {
    do_on_type_impl2<F2, A1, A2, A3, A4> (type1, type2, &arg1, &arg2, &arg3, &arg4);
  }
};

}

#endif

