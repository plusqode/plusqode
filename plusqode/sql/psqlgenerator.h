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

#ifndef PSQLGENERATOR_H
#define PSQLGENERATOR_H

   #include <QtCore/QString>

   #include "sql/psql.h"
   #include "sql/pmodel.h"
   #include "misc/pdir.h"
   #include "variant/pvariant.h"
   #include "core/plogger.h"
   #include "core/pshareddata.h"
   #include "sql/psqldataloader.h"
   #include "misc/psystem.h"
   #include "misc/pcalculator.h"
   #include "app/modules/core/pmmessage_box/pmmessage_box.h"

class PSqlGenerator : public QObject {

    Q_OBJECT
public:
    void init(PVariant);
    void initModule();
    PVariant modelsOfModule(const QString&  moduleName);
    void initDataLoader();
    void dataLoader(const QString& moduleName, const QString& modelName, const QString& tableName);
    void dropFields(const QString& tableName, PVariant dbFields);
    void columnCopy(const QString& tableName, const QString& fieldName, const QString& oldFieldName, const QString& type);
    PVariant fieldMask(PVariant attrs);
    PVariant tableMask(PVariant fields);
    void attributeMigration(PVariant dbFields, PVariant hfields, PVariant definitions, const QString& tableName);
    void dynamicMigrations(PVariant pTables);
    void init_pTables();
    void createScaffoldTable(const QString& tableName);
    static PSqlGenerator* initDatabase();

    virtual void before(const QString& tableName) = 0;
    virtual void after(const QString& tableName) = 0;
    virtual void dropTable(const QString& tableName) = 0;
    virtual void createTable(const QString& tableName) = 0;
    void _addField(PVariant dbFields,
                   const QString& tableName,
                   const QString&fieldName,
                   PVariant fieldAttrs, bool force = false);
    virtual void addSystemFields(const QString& tableName) = 0;
    virtual void dropField(PVariant dbFields, const QString& tableName, const QString& fieldName, bool force = false) = 0;
    virtual void addField(QString tableName,
                  QString fieldName,
                  QString type,
                  QString constraint = QString(),
                  QString defaultValue = QString(),
                  QString reference = QString(),
                  QString onDelete = QString(),
                  QString onUpdate = QString()) = 0;
    virtual void disableTrigger() = 0;
    virtual void enableTrigger() = 0;
    virtual void finalize() {};
    virtual void disableTrigger(const QString& tableName) = 0;
    virtual void enableTrigger(const QString& tableName) = 0;
    virtual QString renameFieldName(PVariant dbFields, const QString& tableName, const QString& fieldName) = 0;
    virtual QString toType(const QString& type) = 0;
    virtual PVariant db_databases() = 0;
    virtual PVariant db_tables() = 0;
    virtual PVariant db_fields(const QString& tableName) = 0;
    virtual bool create_db(const QString name) = 0;
    virtual bool drop_db(const QString name) = 0;
    virtual QString dump(const QString& filename) { return QString(); }
    virtual QString restore(const QString& filename) { return QString(); }


public slots:
    void dump();

public:
    QMap<QString, bool> generatedTables;
    PVariant modules;

    QString connectionName;
    bool dropTables;

    PVariant pTables; 
    PVariant databases;
    PVariant dbTables;

};


class PSinglSqlGenerator {

public:
    static PSinglSqlGenerator& instance() {
        static PSinglSqlGenerator instance;
        return instance;
    }

    PSqlGenerator* sqlGenerator;

private:

    PSinglSqlGenerator() {

        sqlGenerator = PSqlGenerator::initDatabase();

    }

    ~PSinglSqlGenerator() {

        delete sqlGenerator;

    }

    Q_DISABLE_COPY(PSinglSqlGenerator);

};


#endif 



