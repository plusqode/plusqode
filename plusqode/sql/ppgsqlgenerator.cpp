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




   #include "sql/ppgsqlgenerator.h"


   

   
   #include "app/modules/database_manager/pmdatabase_authentication/pmdatabase_authentication.h"


   

   
   

   
   
 


void PPgSqlGenerator::dropTable(const QString& tableName) {

    if(!this->dbTables.include(tableName)) return;
    if(!this->dropTables) return;

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("DROP TABLE %1 CASCADE").arg(tableName)));
    this->dbTables.removeByValue(tableName);

}


void PPgSqlGenerator::createTable(const QString& tableName) {

    if(this->dbTables.include(tableName)) return;

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("CREATE TABLE %1 ()").arg(tableName)));

    dbTables << tableName;

}

void PPgSqlGenerator::addSystemFields(const QString& tableName) {

    this->addField(tableName, "id", "SERIAL", "PRIMARY KEY");

}


void PPgSqlGenerator::before(const QString& tableName) {


}

void PPgSqlGenerator::after(const QString& tableName) {


}

void PPgSqlGenerator::finalize() {

    QString userName = PConf().value(PString(QString("%1.user").arg(connectionName))).toString();
     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER ROLE %1 CREATEDB").arg(userName)));
    

}


void PPgSqlGenerator::disableTrigger() {

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute("SET session_replication_role = replica");

}

void PPgSqlGenerator::enableTrigger() {

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute("SET session_replication_role = DEFAULT");

}

void PPgSqlGenerator::disableTrigger(const QString& tableName) {

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 DISABLE TRIGGER ALL").arg(tableName)));

}

void PPgSqlGenerator::enableTrigger(const QString& tableName) {

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 ENABLE TRIGGER ALL").arg(tableName)));

}


void PPgSqlGenerator::dropField(PVariant dbFields, const QString& tableName, const QString& fieldName, bool force) {

    if(!dbFields.include(fieldName) && !force) return;

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 DROP COLUMN %2").arg(tableName).arg(fieldName)));

}

void PPgSqlGenerator::addField(QString tableName,
                                  QString fieldName,
                                  QString type,
                                  QString constraint,
                                  QString defaultValue,
                                  QString reference,
                                  QString onDelete,
                                  QString onUpdate) {



    if (!onDelete.isNull())
        onDelete = PString(QString(" ON DELETE %1").arg(onDelete));
    if (!onUpdate.isNull())
        onUpdate = PString(QString(" ON UPDATE %1").arg(onUpdate));
    if (!reference.isNull())
        reference = PString(QString(" REFERENCES %1(id)").arg(reference));
    
    

    if (!constraint.isNull())
        constraint = PString(QString(" %1").arg(constraint));

    if (!defaultValue.isNull())
        defaultValue = PString(QString(" DEFAULT %1").arg(PSql::quoteValue(defaultValue))); 

    if(!type.isNull())
         PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 ADD COLUMN %2 %3%4%5%6%7%8").arg(tableName).arg(fieldName).arg(type).arg(constraint).arg(reference).arg(onDelete).arg(onUpdate).arg(defaultValue)));

}


void PPgSqlGenerator::changeType(const QString& tableName, const QString& fieldName, const QString& newType) {

  QString type = this->toType(newType);
   PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 alter COLUMN %2 type %3 USING %4::%5").arg(tableName).arg(fieldName).arg(type).arg(fieldName).arg(type)));

}

void PPgSqlGenerator::changeDefaultValue(const QString& tableName, const QString& fieldName, const QString& newDefaultValue) {

   PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 alter COLUMN %2 SET DEFAULT %3").arg(tableName).arg(fieldName).arg(newDefaultValue)));

}


QString PPgSqlGenerator::renameFieldName(PVariant dbFields, const QString& tableName, const QString& fieldName) {

  if(!dbFields.include(fieldName)) return QString();
  QString counter =  PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("select nextval('%1_id_seq')").arg(tableName)))->data(0, 0).toString();
   PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 rename COLUMN %2 to %3_%4").arg(tableName).arg(fieldName).arg(fieldName).arg(counter)));
  return PString(QString("%1_%2").arg(fieldName).arg(counter));

}

QString PPgSqlGenerator::toType(const QString& type) {

    PVariant toPgTypes = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("boolean", QString("bool"))->append("integer", QString("int4"))->append("float", QString("real"))->append("text", QString("text"))->append("html", QString("text"))->append("date", QString("date"))->append("time", QString("time"))->append("datetime", QString("timestamp"))->append("binary", QString("bytea"))->append("oneToOne", QString("int4"))->append("manyToOne", QString("int4"))->append("oneToMany", QString("int4"))->append("manyToMany", QString("int4"))->append("serialized", QString("text"))->append("virtual", nil))));

   return toPgTypes.include(type) ? toPgTypes[type].toString() : type;

}


PVariant PPgSqlGenerator::db_databases() {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));
    result.select(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("datname"))))))->from(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("pg_database"))))))-> where(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("datistemplate", QString("false"))))))->execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    return result.column("datname");

}


PVariant PPgSqlGenerator::db_tables() {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));
    return result.tables();

}

PVariant PPgSqlGenerator::db_fields(const QString& tableName) {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));
    return result.fields(tableName).keys();

}


bool PPgSqlGenerator::create_db(const QString name) {

    QString stmn = PString(QString("createdb -U %1 %2").arg(connectionName).arg(name));
    PSystem(stmn.toUtf8());
    PLog().debug() << stmn;
    return true;

}

bool PPgSqlGenerator::drop_db(const QString name) {

    return true;

}

bool PPgSqlGenerator::create_db(const QString& dbname, const QString& username, const QString& password) {

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("postgres")))))).execute(PString(QString("CREATE USER %1 WITH PASSWORD '%2' SUPERUSER").arg(username).arg(password)));
     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("postgres")))))).execute(PString(QString("CREATE DATABASE %1 OWNER %2").arg(dbname).arg(username)));

    return true;

}

bool PPgSqlGenerator::drop_db(const QString& dbname, const QString& username) {

    PDir::remove(PString(QString("%1/.db").arg(PGlobal::basePath())));

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("postgres")))))).execute(PString(QString("DROP DATABASE %1").arg(dbname)));
     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("postgres")))))).execute(PString(QString("DROP USER %1").arg(dbname)));

    return true;

}



void PPgSqlGenerator::initDatabase() {

    PSql testConnection(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    if(testConnection.connectionState == "connected")
        return;

    if(QFile::exists("plusqode.lock")) {
        PLog().error() << "Warinng:" <<
                "System locked: if you want to reset remove plusqode.lock -->" <<
                "All db data will be erased";
        exit(0);
    }

    PMDatabaseAuthentication databaseAuthentication(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    databaseAuthentication.initDialog();
    databaseAuthentication.getFieldLabel("password")->setText("Insert: plusqode or Postgres root password");
    databaseAuthentication.sqlFormViewDialog->findChild<QLabel*>("logoLabel")->setPixmap(QPixmap("app/modules/database_manager/pmdatabase_authentication/postgresql.png"));

    databaseAuthentication.exec();

    QString pwd = databaseAuthentication.undefined("password", nil).toString();

    PSql              test(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("host", QString("localhost"))->append("port", 5432)->append("dbname", QString("template1"))->append("user", QString("postgres"))->append("password", pwd)->append("connectionName", QString("postgres"))->append("driver", QString("QPSQL"))))));

    if(test.connectionState != "connected") {
        qDebug() << "Wrong Password !!!" << "\n";
        qDebug() << "Run this script to change postgres password -> ./utils/chpwd_postgres.sh" << "\n";
        exit(0);
    }

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    PPgSqlGenerator dbGenerator;
    dbGenerator.connectionName = "postgres";

    QString dbname = PConf().value(PString(QString("%1.dbname").arg(connectionName))).toString();
    QString username = PConf().value(PString(QString("%1.user").arg(connectionName))).toString();
    QString password = PConf().value(PString(QString("%1.password").arg(connectionName))).toString();

    QString dbpwd =  PCalculator::randStr(12);
    if(password != "plusqode-pgsql-pwd")
        dbpwd = password;

    PSql::closeAllConnections();

    if(PMMessageBox:: 
                                  
                                       messageBox(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("text", QString("A new Database will be created, do You Want to continue ?"))->append("icon", QString("picons/core/actions-128/stop.png"))->append("ok", true)->append("cancel", true)))))== QDialog::Accepted) {
                     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("host", QString("localhost"))->append("port", 5432)->append("dbname", QString("template1"))->append("user", QString("postgres"))->append("password", pwd)->append("connectionName", QString("postgres"))->append("driver", QString("QPSQL"))))));
        QByteArray plusqode_cfg = PDir::fileContent("plusqode.cfg");
        plusqode_cfg.replace("plusqode-pgsql-pwd", dbpwd.toUtf8());
        PDir::fileWrite("plusqode.cfg", plusqode_cfg);
        drop_db(dbname, username);
        create_db(dbname, username, dbpwd);

        PMMessageBox:: 
                                   
                                       messageBox(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("text", QString("Database creatation successfully\n\n - To reset remove plusqode.cfg"))->append("icon", QString("picons/core/actions-128/ok.png"))->append("ok", true)->append("cancel", false)))));

    }

    exit(0);

}


QString PPgSqlGenerator::dump(const QString& filename) {

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();
    QString dbname = PConf().value(PString(QString("%1.dbname").arg(connectionName))).toString();
    QString username = PConf().value(PString(QString("%1.user").arg(connectionName))).toString();

    return PPgSqlGenerator::pg_dump(dbname, username, filename);

}


QString PPgSqlGenerator::restore(const QString& filename) {

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();
    QString dbname = PConf().value(PString(QString("%1.dbname").arg(connectionName))).toString();
    QString username = PConf().value(PString(QString("%1.user").arg(connectionName))).toString();

    return PPgSqlGenerator::pg_restore(dbname, username, filename);

}


QString PPgSqlGenerator::pg_dump(const QString& dbname, const QString& username, const QString& filename) {

    QString pg_dump = PString(QString("pg_dump -U %1 -C -F t -f %2 %3").arg(username).arg(filename).arg(dbname));
    PSystem(pg_dump.toUtf8());
    qDebug() << pg_dump;

    QString plain_pg_dump = PString(QString("pg_dump -U %1 -C -F p -f %2.plain %3").arg(username).arg(filename).arg(dbname));
    PSystem(plain_pg_dump.toUtf8());
    qDebug() << plain_pg_dump;

    return pg_dump;

}



QString PPgSqlGenerator::pg_restore(const QString& dbname, const QString& username, const QString& filename) {

    QString pg_restore1 = PString(QString("pg_restore -U %1 -C -O -d postgres %2").arg(username).arg(filename));
    QString pg_restore2 = PString(QString("pg_restore -U %1 --disable-triggers -v -d %2 %3").arg(username).arg(dbname).arg(filename));
    QString pg_restore3 = PString(QString("psql -U %1 %2 < %3 - (remember to use plain file)").arg(username).arg(dbname).arg(filename));

    qDebug() << "\n\nYou must run this command: ==>";
    qDebug() << " 1 - Standard - " << pg_restore1 << "\n";
    qDebug() << " 2 - No Triggers - " << pg_restore2 << "\n";
    qDebug() << " 3 - Plain - " << pg_restore3 << "\n\n";

    qDebug() << PString(QString(" NOTE: dropdb %1 and createdb %2 for 2 and 3 option\n").arg(dbname).arg(dbname));

    return pg_restore1;

}
