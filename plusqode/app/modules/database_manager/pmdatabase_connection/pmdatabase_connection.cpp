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

#include "app/modules/database_manager/pmdatabase_connection/pmdatabase_connection.h"
#include "app/modules/pmodules.h"

PMDatabaseConnection::$PMDatabaseConnection() {

    init(args);

}

PMDatabaseConnection& PMDatabaseConnection::init(PVariant args) {

    PModel::init(args);

    name$ = $pt();
    host$ = $pt(default: "127.0.0.1");
    port$ = $pt(default: "5432");
    database_name$ = $pt();
    username$ = $pt();
    password$ = $pt();
    timezone$ = $pt();

    database_connector$ = $pt(fieldType: "combobox", default: "QPSQL");
    database_connector_ptr$.itemsAndValues$ = ${
                                          QDB2: "IBM DB2",
                                          QIBASE: "Borland InterBase Driver",
                                          QMYSQL: "MySql",
                                          QOCI: "Oracle Call Interface Driver",
                                          QODBC: "ODBC Driver (includes Microsoft SQL Server)",
                                          QPSQL: "PostgreSQL",
                                          QSQLITE: "SQLite3",
                                          QSQLITE2: "SQLite2",
                                          QTDS: "Sybase Adaptive Server"};

    database_connection_table_table$ = $pa();

    return *this;

}

void PMDatabaseConnection::onChangeField(QString fieldName, PVariant data) {

    if(!name$s.isEmpty())
        return;

    if(fieldName == "database_connector") {
        if(database_connector$s == "QPSQL") {
            name$ = "plusqode";
            host$ = "127.0.0.1";
            port$ = "5432";
            database_name$ = "plusqode";
            username$ = "plusqode";
            password$ = "plusqode";
            timezone$ = "posix/Europe/Rome";
        }
        else if(database_connector$s == "QMYSQL") {
            port$ = "3306";
            timezone$ = "+02:00";
        }
        else if(database_connector$s == "QSQLITE") {
            port$ = "";
            timezone$ = "+02:00";
        }
        else if(database_connector$s == "QOCI") {
            port$ = "1521";
            timezone$ = "Europe/Rome";
        }
    }

}


PVariant PMDatabaseConnection::connectionParams() {

    return ${
        connectionName: name$,
        host: host$,
        port: port$,
        dbname: database_name$,
        user: username$,
        password: password$,
        timezone: timezone$,
        driver: database_connector$
    };

}


PSqlPtr PMDatabaseConnection::getSql() {

    PSqlPtr sqlPtr = new PSql(connectionParams());

    return sqlPtr;

}



PVariant PMDatabaseConnection::action(PVariant action) {


    PLog().debug() << connectionParams().toString();

    PModel::action(action);

    PVariant params = connectionParams();

    database_connection_table_table$->$remove(database_connection_id: id$);

    PSqlPtr sqlPtr = getSql();

    PVariant tables = sqlPtr->tables();

    $tables.forEach(QString tableName) {
       PModelPtr table = database_connection_table_table$->$create(name: tableName);
       
       PVariant fields = sqlPtr->fields(tableName);
       $fields.forEach(QString fieldName, PVariant attrs) {
           PLog().debug() << attrs.toString();
           table->database_connection_table_field_table$->create(attrs);
       }
    }

    // senza questa istruzione non viene aggiornata la tabella
    return ${type: "action", action: "reload"};

}
