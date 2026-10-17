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




   #include "sql/pmysqlgenerator.h"


   

   
   #include "app/modules/pmodules.h"


   

   
   

   
   
 


void PMySqlGenerator::dropTable(const QString& tableName) {

    if(!this->dbTables.include(tableName)) return;
    if(!this->dropTables) return;

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("DROP TABLE %1 CASCADE").arg(tableName)));
    this->dbTables.removeByValue(tableName);

}


void PMySqlGenerator::createTable(const QString& tableName) {

    if(this->dbTables.include(tableName)) return;

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("CREATE TABLE IF NOT EXISTS %1 (id INT NOT NULL AUTO_INCREMENT PRIMARY KEY)").arg(tableName)));

    dbTables << tableName;

}

void PMySqlGenerator::addSystemFields(const QString& tableName) {

    this->addField(tableName, "id", "SERIAL", "PRIMARY KEY");

}


void PMySqlGenerator::before(const QString& tableName) {


}

void PMySqlGenerator::after(const QString& tableName) {


}

void PMySqlGenerator::disableTrigger() {

}

void PMySqlGenerator::enableTrigger() {

}


void PMySqlGenerator::disableTrigger(const QString& tableName) {

}

void PMySqlGenerator::enableTrigger(const QString& tableName) {

}


void PMySqlGenerator::dropField(PVariant dbFields, const QString& tableName, const QString& fieldName, bool force) {

    if(!dbFields.include(fieldName) && !force) return;

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 DROP COLUMN %2").arg(tableName).arg(fieldName)));

}

void PMySqlGenerator::addField(QString tableName,
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

    if(!reference.isNull())
        defaultValue = "";

    if(!type.isNull())
         PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 ADD COLUMN %2 %3%4%5%6%7%8").arg(tableName).arg(fieldName).arg(type).arg(constraint).arg(reference).arg(onDelete).arg(onUpdate).arg(defaultValue)));

}


void PMySqlGenerator::changeType(const QString& tableName, const QString& fieldName, const QString& newType) {

  QString type = this->toType(newType);
   PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 alter COLUMN %2 type %3 USING %4::%5").arg(tableName).arg(fieldName).arg(type).arg(fieldName).arg(type)));

}

void PMySqlGenerator::changeDefaultValue(const QString& tableName, const QString& fieldName, const QString& newDefaultValue) {

   PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 alter COLUMN %2 SET DEFAULT %3").arg(tableName).arg(fieldName).arg(newDefaultValue)));

}


QString PMySqlGenerator::renameFieldName(PVariant dbFields, const QString& tableName, const QString& fieldName) {

  if(!dbFields.include(fieldName)) return QString();
  QString counter =  PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("select nextval('%1_id_seq')").arg(tableName)))->data(0, 0).toString();
   PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("ALTER TABLE %1 CHANGE %2 %3_%4 text").arg(tableName).arg(fieldName).arg(fieldName).arg(counter)));
  return PString(QString("%1_%2").arg(fieldName).arg(counter));

}

QString PMySqlGenerator::toType(const QString& type) {

    PVariant toPgTypes = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("boolean", QString("bool"))->append("integer", QString("int4"))->append("float", QString("real"))->append("text", QString("varchar(1024)"))->append("html", QString("varchar(1024)"))->append("date", QString("date"))->append("time", QString("time"))->append("datetime", QString("timestamp"))->append("binary", QString("bytea"))->append("oneToOne", QString("int4"))->append("manyToOne", QString("int4"))->append("oneToMany", QString("int4"))->append("manyToMany", QString("int4"))->append("serialized", QString("varchar(1024)"))->append("virtual", nil))));

   return toPgTypes.include(type) ? toPgTypes[type].toString() : type;

}


PVariant PMySqlGenerator::db_databases() {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("mysql"))))));
    result.execute("show databases");
    return result.column("Database");

}


PVariant PMySqlGenerator::db_tables() {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));
    return result.tables();

}

PVariant PMySqlGenerator::db_fields(const QString& tableName) {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));
    return result.fields(tableName).keys();

}


bool PMySqlGenerator::create_db(const QString name) {

    return true;

}

bool PMySqlGenerator::drop_db(const QString name) {

    return true;

}

PVariant PMySqlGenerator::mysql_databases() {

    PSql  result(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("mysql"))))));
    result.execute("show databases");
    return result.column("Database");

}


bool PMySqlGenerator::create_db(const QString& dbname, const QString& username, const QString& password) {

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("mysql")))))).execute(PString(QString("CREATE USER %1@localhost").arg(username)));
     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("mysql")))))).execute(PString(QString("SET PASSWORD FOR %1@localhost = PASSWORD('%2')").arg(username).arg(password)));
     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("mysql")))))).execute(PString(QString("CREATE DATABASE %1").arg(dbname)));
     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("mysql")))))).execute(PString(QString("GRANT ALL ON %1.* TO %2@localhost").arg(dbname).arg(username)));

    return true;

}


bool PMySqlGenerator::drop_db(const QString& dbname, const QString& username) {

    PDir::remove(PString(QString("%1/.db").arg(PGlobal::basePath())));

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("mysql")))))).execute(PString(QString("DROP USER %1@localhost").arg(username)));
     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("mysql")))))).execute(PString(QString("DROP DATABASE IF EXISTS %1").arg(dbname)));

    return true;

}


void PMySqlGenerator::initDatabase() {

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
    databaseAuthentication.getFieldLabel("password")->setText("Mysql root password");
    databaseAuthentication.sqlFormViewDialog->findChild<QLabel*>("logoLabel")->setPixmap(QPixmap("app/modules/database_manager/pmdatabase_authentication/mysql.png"));

    databaseAuthentication.exec();

    QString pwd = databaseAuthentication.undefined("password", nil).toString();

    PSql              test(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("host", QString("localhost"))->append("port", 3306)->append("dbname", QString("information_schema"))->append("user", QString("root"))->append("password", pwd)->append("connectionName", QString("mysql"))->append("driver", QString("QMYSQL"))))));

    if(test.connectionState != "connected") {
        qDebug() << "Wrong Password !!!" << "\n";
        exit(0);
    }

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    QString dbname = PConf().value(PString(QString("%1.dbname").arg(connectionName))).toString();
    QString username = PConf().value(PString(QString("%1.user").arg(connectionName))).toString();
    QString password = PConf().value(PString(QString("%1.password").arg(connectionName))).toString();

    QString dbpwd =  PCalculator::randStr(12);
    if(password != "plusqode-mysql-pwd")
        dbpwd = password;

    PSql::closeAllConnections();

    if(PMMessageBox:: 
                                  
                                       messageBox(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("text", QString("A new Database will be created, do You Want to continue ?"))->append("icon", QString("picons/core/actions-128/stop.png"))->append("ok", true)->append("cancel", true)))))== QDialog::Accepted) {
                     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("host", QString("localhost"))->append("port", 3306)->append("dbname", QString("information_schema"))->append("user", QString("root"))->append("password", pwd)->append("connectionName", QString("mysql"))->append("driver", QString("QMYSQL"))))));
        QByteArray plusqode_cfg = PDir::fileContent("plusqode.cfg");
        plusqode_cfg.replace("plusqode-mysql-pwd", dbpwd.toUtf8());
        PDir::fileWrite("plusqode.cfg", plusqode_cfg);
        drop_db(dbname, username);
        create_db(dbname, username, dbpwd);

        PMMessageBox:: 
                                   
                                       messageBox(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("text", QString("Database creatation successfully\n\n - To reset remove plusqode.cfg"))->append("icon", QString("picons/core/actions-128/ok.png"))->append("ok", true)->append("cancel", false)))));

    }

    exit(0);

}
