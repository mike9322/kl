
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

/**
*  @file gsiDeclQSqlQueryModel.cc 
*
*  DO NOT EDIT THIS FILE. 
*  This file has been created automatically
*/

#include "gsiQtSql.h"
#include "gsiDeclQtTypeTraits.h"
#include "gsiDeclQSqlQueryModel_EventAdaptor.h"
#include "gsiDeclQSqlQueryModel_Enums.h"
#include <memory>

// -----------------------------------------------------------------------
// class QSqlQueryModel

//  get static meta object

static void _init_smo (qt_gsi::GenericStaticMethod *decl)
{
  decl->set_return<const QMetaObject &> ();
}

static void _call_smo (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<const QMetaObject &> (QSqlQueryModel::staticMetaObject);
}

static qt_gsi::GenericStaticMethod *_create_smo ()
{
  return new qt_gsi::GenericStaticMethod ("staticMetaObject", "@brief Obtains the static MetaObject for this class.", &_init_smo, &_call_smo);
}

//  Constructor QSqlQueryModel::QSqlQueryModel(QObject *parent)


static void _init_ctor_QSqlQueryModel_1302 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent", true, "0");
  decl->add_arg<QObject * > (argspec_0);
  decl->set_return_new<QSqlQueryModel *> ();
}

static void _call_ctor_QSqlQueryModel_1302 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  QObject *arg1 = args ? args.read<QObject * > () : (QObject *)(0);
  ret.write<QSqlQueryModel *> (new QSqlQueryModel (arg1));
}

static qt_gsi::GenericStaticMethod *_create_ctor_QSqlQueryModel_1302 ()
{
  return new qt_gsi::GenericStaticMethod ("new", "@brief Constructor QSqlQueryModel::QSqlQueryModel(QObject *parent)\nThis method creates an object of class QSqlQueryModel.", &_init_ctor_QSqlQueryModel_1302, &_call_ctor_QSqlQueryModel_1302);
}

// bool QSqlQueryModel::canFetchMore(const QModelIndex &parent)


static void _init_f_canFetchMore_c2395 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent", true, "QModelIndex()");
  decl->add_arg<const QModelIndex & > (argspec_0);
  decl->set_return<bool > ();
}

static void _call_f_canFetchMore_c2395 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QModelIndex &arg1 = args ? args.read<const QModelIndex & > () : (const QModelIndex &)(QModelIndex());
  ret.write<bool > ((bool)((QSqlQueryModel *)cls)->canFetchMore (arg1));
}

static qt_gsi::GenericMethod *_create_f_canFetchMore_c2395 ()
{
  return new qt_gsi::GenericMethod ("canFetchMore", "@brief Method bool QSqlQueryModel::canFetchMore(const QModelIndex &parent)\nThis is a reimplementation of QAbstractItemModel::canFetchMore", true, &_init_f_canFetchMore_c2395, &_call_f_canFetchMore_c2395);
}

// void QSqlQueryModel::clear()


static void _init_f_clear_0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<void > ();
}

static void _call_f_clear_0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ((QSqlQueryModel *)cls)->clear ();
}

static qt_gsi::GenericMethod *_create_f_clear_0 ()
{
  return new qt_gsi::GenericMethod ("clear", "@brief Method void QSqlQueryModel::clear()\n", false, &_init_f_clear_0, &_call_f_clear_0);
}

// int QSqlQueryModel::columnCount(const QModelIndex &parent)


static void _init_f_columnCount_c2395 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent", true, "QModelIndex()");
  decl->add_arg<const QModelIndex & > (argspec_0);
  decl->set_return<int > ();
}

static void _call_f_columnCount_c2395 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QModelIndex &arg1 = args ? args.read<const QModelIndex & > () : (const QModelIndex &)(QModelIndex());
  ret.write<int > ((int)((QSqlQueryModel *)cls)->columnCount (arg1));
}

static qt_gsi::GenericMethod *_create_f_columnCount_c2395 ()
{
  return new qt_gsi::GenericMethod ("columnCount", "@brief Method int QSqlQueryModel::columnCount(const QModelIndex &parent)\nThis is a reimplementation of QAbstractItemModel::columnCount", true, &_init_f_columnCount_c2395, &_call_f_columnCount_c2395);
}

// QVariant QSqlQueryModel::data(const QModelIndex &item, int role)


static void _init_f_data_c3054 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("item");
  decl->add_arg<const QModelIndex & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("role", true, "Qt::DisplayRole");
  decl->add_arg<int > (argspec_1);
  decl->set_return<QVariant > ();
}

static void _call_f_data_c3054 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QModelIndex &arg1 = args.read<const QModelIndex & > ();
  int arg2 = args ? args.read<int > () : (int)(Qt::DisplayRole);
  ret.write<QVariant > ((QVariant)((QSqlQueryModel *)cls)->data (arg1, arg2));
}

static qt_gsi::GenericMethod *_create_f_data_c3054 ()
{
  return new qt_gsi::GenericMethod ("data", "@brief Method QVariant QSqlQueryModel::data(const QModelIndex &item, int role)\nThis is a reimplementation of QAbstractItemModel::data", true, &_init_f_data_c3054, &_call_f_data_c3054);
}

// void QSqlQueryModel::fetchMore(const QModelIndex &parent)


static void _init_f_fetchMore_2395 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent", true, "QModelIndex()");
  decl->add_arg<const QModelIndex & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_fetchMore_2395 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QModelIndex &arg1 = args ? args.read<const QModelIndex & > () : (const QModelIndex &)(QModelIndex());
  ((QSqlQueryModel *)cls)->fetchMore (arg1);
}

static qt_gsi::GenericMethod *_create_f_fetchMore_2395 ()
{
  return new qt_gsi::GenericMethod ("fetchMore", "@brief Method void QSqlQueryModel::fetchMore(const QModelIndex &parent)\nThis is a reimplementation of QAbstractItemModel::fetchMore", false, &_init_f_fetchMore_2395, &_call_f_fetchMore_2395);
}

// QVariant QSqlQueryModel::headerData(int section, Qt::Orientation orientation, int role)


static void _init_f_headerData_c3231 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("section");
  decl->add_arg<int > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("orientation");
  decl->add_arg<const qt_gsi::Converter<Qt::Orientation>::target_type & > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("role", true, "Qt::DisplayRole");
  decl->add_arg<int > (argspec_2);
  decl->set_return<QVariant > ();
}

static void _call_f_headerData_c3231 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  const qt_gsi::Converter<Qt::Orientation>::target_type & arg2 = args.read<const qt_gsi::Converter<Qt::Orientation>::target_type & > ();
  int arg3 = args ? args.read<int > () : (int)(Qt::DisplayRole);
  ret.write<QVariant > ((QVariant)((QSqlQueryModel *)cls)->headerData (arg1, qt_gsi::QtToCppAdaptor<Qt::Orientation>(arg2).cref(), arg3));
}

static qt_gsi::GenericMethod *_create_f_headerData_c3231 ()
{
  return new qt_gsi::GenericMethod ("headerData", "@brief Method QVariant QSqlQueryModel::headerData(int section, Qt::Orientation orientation, int role)\nThis is a reimplementation of QAbstractItemModel::headerData", true, &_init_f_headerData_c3231, &_call_f_headerData_c3231);
}

// bool QSqlQueryModel::insertColumns(int column, int count, const QModelIndex &parent)


static void _init_f_insertColumns_3713 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("column");
  decl->add_arg<int > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("count");
  decl->add_arg<int > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("parent", true, "QModelIndex()");
  decl->add_arg<const QModelIndex & > (argspec_2);
  decl->set_return<bool > ();
}

static void _call_f_insertColumns_3713 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  int arg2 = args.read<int > ();
  const QModelIndex &arg3 = args ? args.read<const QModelIndex & > () : (const QModelIndex &)(QModelIndex());
  ret.write<bool > ((bool)((QSqlQueryModel *)cls)->insertColumns (arg1, arg2, arg3));
}

static qt_gsi::GenericMethod *_create_f_insertColumns_3713 ()
{
  return new qt_gsi::GenericMethod ("insertColumns", "@brief Method bool QSqlQueryModel::insertColumns(int column, int count, const QModelIndex &parent)\nThis is a reimplementation of QAbstractItemModel::insertColumns", false, &_init_f_insertColumns_3713, &_call_f_insertColumns_3713);
}

// QSqlError QSqlQueryModel::lastError()


static void _init_f_lastError_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QSqlError > ();
}

static void _call_f_lastError_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSqlError > ((QSqlError)((QSqlQueryModel *)cls)->lastError ());
}

static qt_gsi::GenericMethod *_create_f_lastError_c0 ()
{
  return new qt_gsi::GenericMethod ("lastError", "@brief Method QSqlError QSqlQueryModel::lastError()\n", true, &_init_f_lastError_c0, &_call_f_lastError_c0);
}

// QSqlQuery QSqlQueryModel::query()


static void _init_f_query_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QSqlQuery > ();
}

static void _call_f_query_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSqlQuery > ((QSqlQuery)((QSqlQueryModel *)cls)->query ());
}

static qt_gsi::GenericMethod *_create_f_query_c0 ()
{
  return new qt_gsi::GenericMethod (":query", "@brief Method QSqlQuery QSqlQueryModel::query()\n", true, &_init_f_query_c0, &_call_f_query_c0);
}

// QSqlRecord QSqlQueryModel::record(int row)


static void _init_f_record_c767 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("row");
  decl->add_arg<int > (argspec_0);
  decl->set_return<QSqlRecord > ();
}

static void _call_f_record_c767 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  ret.write<QSqlRecord > ((QSqlRecord)((QSqlQueryModel *)cls)->record (arg1));
}

static qt_gsi::GenericMethod *_create_f_record_c767 ()
{
  return new qt_gsi::GenericMethod ("record", "@brief Method QSqlRecord QSqlQueryModel::record(int row)\n", true, &_init_f_record_c767, &_call_f_record_c767);
}

// QSqlRecord QSqlQueryModel::record()


static void _init_f_record_c0 (qt_gsi::GenericMethod *decl)
{
  decl->set_return<QSqlRecord > ();
}

static void _call_f_record_c0 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  ret.write<QSqlRecord > ((QSqlRecord)((QSqlQueryModel *)cls)->record ());
}

static qt_gsi::GenericMethod *_create_f_record_c0 ()
{
  return new qt_gsi::GenericMethod ("record", "@brief Method QSqlRecord QSqlQueryModel::record()\n", true, &_init_f_record_c0, &_call_f_record_c0);
}

// bool QSqlQueryModel::removeColumns(int column, int count, const QModelIndex &parent)


static void _init_f_removeColumns_3713 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("column");
  decl->add_arg<int > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("count");
  decl->add_arg<int > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("parent", true, "QModelIndex()");
  decl->add_arg<const QModelIndex & > (argspec_2);
  decl->set_return<bool > ();
}

static void _call_f_removeColumns_3713 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  int arg2 = args.read<int > ();
  const QModelIndex &arg3 = args ? args.read<const QModelIndex & > () : (const QModelIndex &)(QModelIndex());
  ret.write<bool > ((bool)((QSqlQueryModel *)cls)->removeColumns (arg1, arg2, arg3));
}

static qt_gsi::GenericMethod *_create_f_removeColumns_3713 ()
{
  return new qt_gsi::GenericMethod ("removeColumns", "@brief Method bool QSqlQueryModel::removeColumns(int column, int count, const QModelIndex &parent)\nThis is a reimplementation of QAbstractItemModel::removeColumns", false, &_init_f_removeColumns_3713, &_call_f_removeColumns_3713);
}

// int QSqlQueryModel::rowCount(const QModelIndex &parent)


static void _init_f_rowCount_c2395 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("parent", true, "QModelIndex()");
  decl->add_arg<const QModelIndex & > (argspec_0);
  decl->set_return<int > ();
}

static void _call_f_rowCount_c2395 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QModelIndex &arg1 = args ? args.read<const QModelIndex & > () : (const QModelIndex &)(QModelIndex());
  ret.write<int > ((int)((QSqlQueryModel *)cls)->rowCount (arg1));
}

static qt_gsi::GenericMethod *_create_f_rowCount_c2395 ()
{
  return new qt_gsi::GenericMethod ("rowCount", "@brief Method int QSqlQueryModel::rowCount(const QModelIndex &parent)\nThis is a reimplementation of QAbstractItemModel::rowCount", true, &_init_f_rowCount_c2395, &_call_f_rowCount_c2395);
}

// bool QSqlQueryModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)


static void _init_f_setHeaderData_5242 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("section");
  decl->add_arg<int > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("orientation");
  decl->add_arg<const qt_gsi::Converter<Qt::Orientation>::target_type & > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("value");
  decl->add_arg<const QVariant & > (argspec_2);
  static gsi::ArgSpecBase argspec_3 ("role", true, "Qt::EditRole");
  decl->add_arg<int > (argspec_3);
  decl->set_return<bool > ();
}

static void _call_f_setHeaderData_5242 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  int arg1 = args.read<int > ();
  const qt_gsi::Converter<Qt::Orientation>::target_type & arg2 = args.read<const qt_gsi::Converter<Qt::Orientation>::target_type & > ();
  const QVariant &arg3 = args.read<const QVariant & > ();
  int arg4 = args ? args.read<int > () : (int)(Qt::EditRole);
  ret.write<bool > ((bool)((QSqlQueryModel *)cls)->setHeaderData (arg1, qt_gsi::QtToCppAdaptor<Qt::Orientation>(arg2).cref(), arg3, arg4));
}

static qt_gsi::GenericMethod *_create_f_setHeaderData_5242 ()
{
  return new qt_gsi::GenericMethod ("setHeaderData", "@brief Method bool QSqlQueryModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)\nThis is a reimplementation of QAbstractItemModel::setHeaderData", false, &_init_f_setHeaderData_5242, &_call_f_setHeaderData_5242);
}

// void QSqlQueryModel::setQuery(const QSqlQuery &query)


static void _init_f_setQuery_2232 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("query");
  decl->add_arg<const QSqlQuery & > (argspec_0);
  decl->set_return<void > ();
}

static void _call_f_setQuery_2232 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QSqlQuery &arg1 = args.read<const QSqlQuery & > ();
  ((QSqlQueryModel *)cls)->setQuery (arg1);
}

static qt_gsi::GenericMethod *_create_f_setQuery_2232 ()
{
  return new qt_gsi::GenericMethod ("setQuery|query=", "@brief Method void QSqlQueryModel::setQuery(const QSqlQuery &query)\n", false, &_init_f_setQuery_2232, &_call_f_setQuery_2232);
}

// void QSqlQueryModel::setQuery(const QString &query, const QSqlDatabase &db)


static void _init_f_setQuery_4404 (qt_gsi::GenericMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("query");
  decl->add_arg<const QString & > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("db", true, "QSqlDatabase()");
  decl->add_arg<const QSqlDatabase & > (argspec_1);
  decl->set_return<void > ();
}

static void _call_f_setQuery_4404 (const qt_gsi::GenericMethod *decl, void *cls, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const QString &arg1 = args.read<const QString & > ();
  const QSqlDatabase &arg2 = args ? args.read<const QSqlDatabase & > () : (const QSqlDatabase &)(QSqlDatabase());
  ((QSqlQueryModel *)cls)->setQuery (arg1, arg2);
}

static qt_gsi::GenericMethod *_create_f_setQuery_4404 ()
{
  return new qt_gsi::GenericMethod ("setQuery", "@brief Method void QSqlQueryModel::setQuery(const QString &query, const QSqlDatabase &db)\n", false, &_init_f_setQuery_4404, &_call_f_setQuery_4404);
}

// static QString QSqlQueryModel::tr(const char *s, const char *c)


static void _init_f_tr_3354 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<QString > ();
}

static void _call_f_tr_3354 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  const char *arg2 = args ? args.read<const char * > () : (const char *)(0);
  ret.write<QString > ((QString)QSqlQueryModel::tr (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_f_tr_3354 ()
{
  return new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QSqlQueryModel::tr(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_tr_3354, &_call_f_tr_3354);
}

// static QString QSqlQueryModel::tr(const char *s, const char *c, int n)


static void _init_f_tr_4013 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c");
  decl->add_arg<const char * > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("n");
  decl->add_arg<int > (argspec_2);
  decl->set_return<QString > ();
}

static void _call_f_tr_4013 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  const char *arg2 = args.read<const char * > ();
  int arg3 = args.read<int > ();
  ret.write<QString > ((QString)QSqlQueryModel::tr (arg1, arg2, arg3));
}

static qt_gsi::GenericStaticMethod *_create_f_tr_4013 ()
{
  return new qt_gsi::GenericStaticMethod ("tr", "@brief Static method QString QSqlQueryModel::tr(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_tr_4013, &_call_f_tr_4013);
}

// static QString QSqlQueryModel::trUtf8(const char *s, const char *c)


static void _init_f_trUtf8_3354 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c", true, "0");
  decl->add_arg<const char * > (argspec_1);
  decl->set_return<QString > ();
}

static void _call_f_trUtf8_3354 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  const char *arg2 = args ? args.read<const char * > () : (const char *)(0);
  ret.write<QString > ((QString)QSqlQueryModel::trUtf8 (arg1, arg2));
}

static qt_gsi::GenericStaticMethod *_create_f_trUtf8_3354 ()
{
  return new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QSqlQueryModel::trUtf8(const char *s, const char *c)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_3354, &_call_f_trUtf8_3354);
}

// static QString QSqlQueryModel::trUtf8(const char *s, const char *c, int n)


static void _init_f_trUtf8_4013 (qt_gsi::GenericStaticMethod *decl)
{
  static gsi::ArgSpecBase argspec_0 ("s");
  decl->add_arg<const char * > (argspec_0);
  static gsi::ArgSpecBase argspec_1 ("c");
  decl->add_arg<const char * > (argspec_1);
  static gsi::ArgSpecBase argspec_2 ("n");
  decl->add_arg<int > (argspec_2);
  decl->set_return<QString > ();
}

static void _call_f_trUtf8_4013 (const qt_gsi::GenericStaticMethod *decl, gsi::SerialArgs &args, gsi::SerialArgs &ret) 
{
  const char *arg1 = args.read<const char * > ();
  const char *arg2 = args.read<const char * > ();
  int arg3 = args.read<int > ();
  ret.write<QString > ((QString)QSqlQueryModel::trUtf8 (arg1, arg2, arg3));
}

static qt_gsi::GenericStaticMethod *_create_f_trUtf8_4013 ()
{
  return new qt_gsi::GenericStaticMethod ("trUtf8", "@brief Static method QString QSqlQueryModel::trUtf8(const char *s, const char *c, int n)\nThis method is static and can be called without an instance.", &_init_f_trUtf8_4013, &_call_f_trUtf8_4013);
}

static qt_gsi::QObjectConnector<QSqlQueryModel, QSqlQueryModel_EventAdaptor> ea_QSqlQueryModel;


namespace gsi
{
extern gsi::Class<QAbstractTableModel> decl_QAbstractTableModel;

gsi::Class<QSqlQueryModel> decl_QSqlQueryModel (ea_QSqlQueryModel, decl_QAbstractTableModel, "QSqlQueryModel",
  gsi::Methods(_create_ctor_QSqlQueryModel_1302 ()) +
  gsi::Methods(_create_smo ()) +
  gsi::Methods(_create_f_canFetchMore_c2395 ()) +
  gsi::Methods(_create_f_clear_0 ()) +
  gsi::Methods(_create_f_columnCount_c2395 ()) +
  gsi::Methods(_create_f_data_c3054 ()) +
  gsi::Methods(_create_f_fetchMore_2395 ()) +
  gsi::Methods(_create_f_headerData_c3231 ()) +
  gsi::Methods(_create_f_insertColumns_3713 ()) +
  gsi::Methods(_create_f_lastError_c0 ()) +
  gsi::Methods(_create_f_query_c0 ()) +
  gsi::Methods(_create_f_record_c767 ()) +
  gsi::Methods(_create_f_record_c0 ()) +
  gsi::Methods(_create_f_removeColumns_3713 ()) +
  gsi::Methods(_create_f_rowCount_c2395 ()) +
  gsi::Methods(_create_f_setHeaderData_5242 ()) +
  gsi::Methods(_create_f_setQuery_2232 ()) +
  gsi::Methods(_create_f_setQuery_4404 ()) +
  qt_gsi::qt_signal<QSqlQueryModel, QSqlQueryModel_EventAdaptor, const QModelIndex &, const QModelIndex &> ("dataChanged", &QSqlQueryModel_EventAdaptor::dataChanged_e_4682, gsi::arg("topLeft"), gsi::arg("bottomRight"), "@brief Signal declaration for QSqlQueryModel::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QSqlQueryModel, QSqlQueryModel_EventAdaptor, QObject *> ("destroyed", &QSqlQueryModel_EventAdaptor::destroyed_e_1302, gsi::arg("arg1"), "@brief Signal declaration for QSqlQueryModel::destroyed(QObject *)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QSqlQueryModel, QSqlQueryModel_EventAdaptor, const qt_gsi::Converter<Qt::Orientation>::target_type &, int, int> ("headerDataChanged", &QSqlQueryModel_EventAdaptor::headerDataChanged_e_3231, gsi::arg("orientation"), gsi::arg("first"), gsi::arg("last"), "@brief Signal declaration for QSqlQueryModel::headerDataChanged(Qt::Orientation orientation, int first, int last)\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QSqlQueryModel, QSqlQueryModel_EventAdaptor> ("layoutAboutToBeChanged", &QSqlQueryModel_EventAdaptor::layoutAboutToBeChanged_e_0, "@brief Signal declaration for QSqlQueryModel::layoutAboutToBeChanged()\nYou can bind a procedure to this signal.") +
  qt_gsi::qt_signal<QSqlQueryModel, QSqlQueryModel_EventAdaptor> ("layoutChanged", &QSqlQueryModel_EventAdaptor::layoutChanged_e_0, "@brief Signal declaration for QSqlQueryModel::layoutChanged()\nYou can bind a procedure to this signal.") +
  gsi::Methods(_create_f_tr_3354 ()) +
  gsi::Methods(_create_f_tr_4013 ()) +
  gsi::Methods(_create_f_trUtf8_3354 ()) +
  gsi::Methods(_create_f_trUtf8_4013 ()),
  "@qt\n@brief Binding of QSqlQueryModel");

}

