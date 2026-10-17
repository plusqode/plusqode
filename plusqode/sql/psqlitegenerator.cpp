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




   #include "sql/psqlitegenerator.h"


   

   


void PSqliteGenerator::dropTable(const QString& tableName) {

    if(!this->dbTables.include(tableName)) return;
    if(!this->dropTables) return;

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("DROP TABLE %1").arg(tableName)));
    this->dbTables.removeByValue(tableName);

}


void PSqliteGenerator::createTable(const QString& tableName) {

    if(this->dbTables.include(tableName)) return;

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("CREATE TABLE %1 (id INTEGER NOT NULL PRIMARY KEY)").arg(tableName)));

    dbTables << tableName;

}

void PSqliteGenerator::addSystemFields(const QString& tableName) {

    this->addField(tableName, "id", "SERIAL", "PRIMARY KEY");

}


void PSqliteGenerator::before(const QString& tableName) {


}

void PSqliteGenerator::after(const QString& tableName) {


}

void PSqliteGenerator::disableTrigger() {

}

void PSqliteGenerator::enableTrigger() {

}


void PSqliteGenerator::disableTrigger(const QString& tableName) {

}

void PSqliteGenerator::enableTrigger(const QString& tableName) {

}


void PSqliteGenerator::dropField(PVariant dbFields, const QString& tableName, const QString& fieldName, bool force) {




    return;

}

void PSqliteGenerator::addField(QString tableName,
                                  QString fieldName,
                                  QString type,
                                  QString constraint,
                                  QString defaultValue,
                                  QString reference,
                                  QString onDelete,
                                  QString onUpdate) {


    if (fieldName == "id") return;

    if (!onDelete.isNull())
        onDelete = PString(QString(" "));
    if (!onUpdate.isNull())
        onUpdate = PString(QString(" "));
    if (!reference.isNull())
        reference = PString(QString(" "));
    
    

    if (!constraint.isNull())
        constraint = PString(QString(" "));

    if (!defaultValue.isNull())
        defaultValue = PString(QString(" "));

    if(!type.isNull())
         PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 ADD COLUMN %2 %3%4%5%6%7%8").arg(tableName).arg(fieldName).arg(type).arg(constraint).arg(reference).arg(onDelete).arg(onUpdate).arg(defaultValue)));

}


void PSqliteGenerator::changeType(const QString& tableName, const QString& fieldName, const QString& newType) {

  QString type = this->toType(newType);
   PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 alter COLUMN %2 type %3 USING %4::%5").arg(tableName).arg(fieldName).arg(type).arg(fieldName).arg(type)));

}

void PSqliteGenerator::changeDefaultValue(const QString& tableName, const QString& fieldName, const QString& newDefaultValue) {

   PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 alter COLUMN %2 SET DEFAULT %3").arg(tableName).arg(fieldName).arg(newDefaultValue)));

}


QString PSqliteGenerator::renameFieldName(PVariant dbFields, const QString& tableName, const QString& fieldName) {

    PLog().warning() << "PSqliteGenerator::renameFieldName: SQLite doesn't support dynamic migrations";
    PLog().warning() << "   You must rebuild the table removing definition.json";
    return "";

}

QString PSqliteGenerator::toType(const QString& type) {

    PVariant toPgTypes = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("boolean", QString("bool"))->append("integer", QString("int4"))->append("float", QString("real"))->append("text", QString("text"))->append("html", QString("text"))->append("date", QString("date"))->append("time", QString("time"))->append("datetime", QString("timestamp"))->append("binary", QString("bytea"))->append("oneToOne", QString("int4"))->append("manyToOne", QString("int4"))->append("oneToMany", QString("int4"))->append("manyToMany", QString("int4"))->append("serialized", QString("text"))->append("virtual", nil))));

   return toPgTypes.include(type) ? toPgTypes[type].toString() : type;

}


PVariant PSqliteGenerator::db_databases() {

    return PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

}


PVariant PSqliteGenerator::db_tables() {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));
    return result.tables();

}

PVariant PSqliteGenerator::db_fields(const QString& tableName) {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));

    result.execute(PString(QString("pragma table_info('%1')").arg(tableName)));

    return result.column("name");

}


bool PSqliteGenerator::create_db(const QString name) {

    return true;

}

bool PSqliteGenerator::drop_db(const QString name) {

    return true;

}

PVariant PSqliteGenerator::mysql_databases() {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("sqlite"))))));
    result.select(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("name"))))))->
            from(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("sqlite_master"))))))->
            where(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("type = 'table' and name not like 'sqlite_%'"))))))->
            orderBy(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("contact_name"))))))->
            execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

    return result.column("name");

}


bool PSqliteGenerator::create_db(const QString& dbname, const QString& username, const QString& password) {

    return true;

}


bool PSqliteGenerator::drop_db(const QString& dbname, const QString& username) {

    PDir::remove(PString(QString("%1/.db").arg(PGlobal::basePath())));

    return true;

}


void PSqliteGenerator::initDatabase() {


}
