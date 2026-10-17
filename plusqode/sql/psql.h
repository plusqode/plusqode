/*
 * Copyright (C) 2026 - PlusQode - www.plusqode.com - plusqode@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PSQL_H
#define PSQL_H

   #include <QtSql/QSqlDatabase>
   #include <QtSql/QSqlQueryModel>
   #include <QtSql/QSqlTableModel>
   #include <QtSql/QSqlRecord>
   #include <QtSql/QSqlField>
   #include <QtSql/QSqlQuery>
   #include <QtSql/QSqlError>
   #include <QtCore/QString>
   #include <QtCore/QElapsedTimer>
   #include <QtCore/QSharedData>

   #include "configuration/pconfigurationmanager.h"
   #include "variant/pvariant.h"
   #include "misc/pdebug.h"
   #include "core/plogger.h"
   #include "core/pshareddata.h"

class PSql : public QSharedData {

public:

    static PVariant simplify(PVariant root);
    static QString quoteValue(QVariant value);
    static PVariant quote(PVariant args);
    QString fieldNameIdToSql(PVariant);
    QString opOnArrayToSql(PVariant);
    QString whereByHash(PVariant);
    QString whereByArray(PVariant);
    QString toSql(PVariant arrayOrHash, PVariant model = nil);

    static bool primitiveType(PVariant value);

    static void closeAllConnections();

    void initDriverByConnectionName();

    PSql(PVariant);

    void init();
    void resetCursor();
    PSql* reset();
    void pushCursor();
    void popCursor();

    virtual ~PSql();

    void openConnection();
    QString toPeriod(QString value);
    PSql* reselect(PVariant select = nil, PVariant model = nil);
    PSql* select(PVariant select = nil, PVariant model = nil);
    PSql* from(PVariant from);
    PSql* groupBy(PVariant fields);

    PSql* where(PVariant where, QString oprt = "auto", PVariant model = nil);

    QString orderByFieldNameIdToSql(QString fieldName, PVariant model = nil);
    QString order_by(PVariant value, PVariant model = nil);
    PSql* orderByHash(PVariant args);
    PSql* orderByArray(PVariant args, PVariant model = nil);
    PSql* orderBy(PVariant args, PVariant model = nil);
    PSql* limit(qint64 limit);
    PSql* offset(qint64 offset);
    PSql* pageSize(QString pageSize);
    PSql* page(qint64 page);

    QString sqlQuery();

    PSql* execute(PVariant);
    PSql* execute(QString sql);
    PSql* execute(const char* sql);

    QString insertValues(PVariant args);
    QString insert(QString tableName, PVariant values);
    QString pgSqlInsert(QString tableName, PVariant values);
    QString mySqlInsert(QString tableName, PVariant values);
    QString sqliteInsert(QString tableName, PVariant values);

    static QString db_false();
    static QString db_true();
    QString db_true_or_false(bool value);
    QString orderingDefaultValue();
    static QString serialConstraint(const QString& tableName);

    QString updateValues(PVariant args);
    int update(QString tableName, PVariant values, PVariant where);
    int erase(QString tableName, PVariant where);

    PVariant fieldNameList();

    int rowCount();
    int columnCount();

    PVariant setTableCursor(int row);
    PVariant record(int row);

    PVariant data(int row, PVariant idOrFieldName);
    PVariant column(PVariant idOrFieldName);

    int count();

    PVariant first();
    PVariant last();
    PVariant prev();
    PVariant next();
    PVariant& operator[](int index);
    PVariant operator()(int index);

      template <typename F>
void forEachPVariant(F f) {

        for(int i = 0; i < this->count(); i++)
                f(this->operator[](i));
    }

      template <typename F>
void forEachQString(F f) {

        for(int i = 0; i < this->count(); i++)
                f(this->operator[](i).toString());
    }


       template <typename F>
void forEachWithIndexPVariant_int(F f) {

        for(int i = 0; i < this->count(); i++)
                f(this->operator[](i), i);
    }

       template <typename F>
void forEachWithIndexQString_int(F f) {

        for(int i = 0; i < this->count(); i++)
                f(this->operator[](i).toString(), i);
    }

    int columnWidth(QString fieldName);
    QSqlField fieldAttrs(QString fieldName);
    void showSeparator(PVariant fields);
    void show(PVariant fields = nil);
    static QString db_current(const QString& what);
    QString current(const QString& what);
    void pushState();
    PSql* popState();

    PVariant tables(QSql::TableType type = QSql::Tables) const;
    PVariant fields(const QString& tableName) const;

    void initParams(const QString& connectionName);

    static void initByConnectionName(const QString& connectionName);
    static void demo();

    static QString defaultConnectionName;

    QString host;
    int port;
    QString dbname;
    QString user;
    QString password;
    QString timezone;
    QString connectionName;
    QString driver;

    QSqlDatabase connection;
    QSqlQuery qsqlQuery;

    QString query;

    PVariant table;

    quint64 tableIndex;
    PVariant tableCursor;
    QString id;

    PVariant _select;
    PVariant _from;
    PVariant _where;
    PVariant _orderBy;
    qint64 _limit;
    qint64 _offset;
    PVariant _groupBy;
    QString _pageSize;
    quint64 _page;

    PVariant colWidth;

    PVariant cursorStack;

    PVariant stateHistory;

    QString connectionState;

};






class PSqlPtr : public QExplicitlySharedDataPointer<PSql> {

public:

    PSqlPtr() : QExplicitlySharedDataPointer<PSql>(0) {

    }

    PSqlPtr(PSql* sql) : QExplicitlySharedDataPointer<PSql>(sql) {

    }

};

Q_DECLARE_METATYPE(PSqlPtr)

#endif 



