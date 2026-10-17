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

#ifndef PSQLITEGENERATOR_H
#define PSQLITEGENERATOR_H

   #include <QtCore/QString>

   #include "configuration/pconfigurationmanager.h"
   #include "sql/psql.h"
   #include "sql/psqlgenerator.h"

class PSqliteGenerator : public PSqlGenerator
{
public:
    virtual void dropTable(const QString& tableName);
    virtual void createTable(const QString& tableName);
    virtual void addSystemFields(const QString& tableName);
    virtual void before(const QString& tableName);
    virtual void after(const QString& tableName);
    virtual void disableTrigger();
    virtual void enableTrigger();
    virtual void disableTrigger(const QString& tableName);
    virtual void enableTrigger(const QString& tableName);
    virtual void dropField(PVariant dbFields, const QString& tableName, const QString& fieldName, bool force = false);
    virtual void addField(QString tableName,
                  QString fieldName,
                  QString type,
                  QString constraint = QString(),
                  QString defaultValue = QString(),
                  QString reference = QString(),
                  QString onDelete = QString(),
                  QString onUpdate = QString());
    virtual void changeType(const QString& tableName, const QString& fieldName, const QString& newType);
    virtual void changeDefaultValue(const QString& tableName, const QString& fieldName, const QString& newDefaultValue);
    virtual QString renameFieldName(PVariant dbFields, const QString& tableName, const QString& fieldName);
    virtual QString toType(const QString& type);
    virtual PVariant db_databases();
    virtual PVariant db_tables();
    virtual PVariant db_fields(const QString& tableName);
    virtual bool create_db(const QString name);
    virtual bool drop_db(const QString name);

    static PVariant mysql_databases();
    static bool create_db(const QString& dbname, const QString& username, const QString& password);
    static bool drop_db(const QString& dbname, const QString& username);

    static void initDatabase();

};

#endif 



