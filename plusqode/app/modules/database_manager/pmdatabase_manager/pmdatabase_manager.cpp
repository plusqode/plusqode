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

#include "app/modules/database_manager/pmdatabase_manager/pmdatabase_manager.h"

PMDatabaseManager::$PMDatabaseManager() {

    init(args);

}

PMDatabaseManager& PMDatabaseManager::init(PVariant args) {

    PModel::init(args);

    action$ = $pt(fieldType: "combobox");
    action_ptr$.itemsAndValues$ = ${
                                    duplicate: "Duplicate",
                                    create:    "Create",
                                    rename:    "Rename",
                                    remove:    "Remove",
                                    backup:    "Backup",
                                    restore:   "Restore"
                                  };
    source_database$ = $pt();
    dest_database$ = $pt();

    return *this;

}

void PMDatabaseManager::onChangeField(QString fieldName, PVariant data) {

    if(data == nil) return;
    
    if(fieldName == "action") {

        QLabel* sourceDatabaseLabel = getFieldLabel("source_database");
        PFieldWidget* sourceDatabaseWidget = source_database$w;
        QLabel* destDatabaseLabel = getFieldLabel("dest_database");
        PFieldWidget* destDatabaseWidget = dest_database$w;


        if(action$s == "duplicate") {
            sourceDatabaseLabel->setVisible(true);
            sourceDatabaseLabel->setText("Source Database Name");
            sourceDatabaseWidget->setVisible(true);

            destDatabaseLabel->setVisible(true);
            destDatabaseLabel->setText("Destination Database Name");
            destDatabaseWidget->setVisible(true);
        }
        
        else if(action$s == "create") {
            sourceDatabaseLabel->setVisible(true);
            sourceDatabaseLabel->setText("New Database Name");
            sourceDatabaseWidget->setVisible(true);

            destDatabaseLabel->setVisible(false);
            destDatabaseWidget->setVisible(false);
        }
        
        else if(action$s == "rename") {
            sourceDatabaseLabel->setVisible(true);
            sourceDatabaseLabel->setText("Old Database Name");
            sourceDatabaseWidget->setVisible(true);

            destDatabaseLabel->setVisible(true);
            destDatabaseLabel->setText("New Database Name");
            destDatabaseWidget->setVisible(true);
        }

        else if(action$s == "remove") {
            sourceDatabaseLabel->setVisible(true);
            sourceDatabaseLabel->setText("Database Name");
            sourceDatabaseWidget->setVisible(true);

            destDatabaseLabel->setVisible(false);
            destDatabaseWidget->setVisible(false);
        }

        else if(action$s == "backup") {
            sourceDatabaseLabel->setVisible(true);
            sourceDatabaseLabel->setText("Database Name");
            sourceDatabaseWidget->setVisible(true);

            destDatabaseLabel->setVisible(false);
            destDatabaseWidget->setVisible(false);
        }
        
        else if(action$s == "restore") {
            sourceDatabaseLabel->setVisible(true);
            sourceDatabaseLabel->setText("Database Name");
            sourceDatabaseWidget->setVisible(true);

            destDatabaseLabel->setVisible(false);
            destDatabaseWidget->setVisible(false);
        }

    }

}


PVariant PMDatabaseManager::action(PVariant button) {

    QString result = "";

    if(action$s == "duplicate")
        result = duplicate_db();
    else if(action$s == "create")
        result = create_db();
    else if(action$s == "rename")
        result = rename_db();
    else if(action$s == "remove")
        result = remove_db();
    else if(action$s == "backup")
        result = backup_db();
    else if(action$s == "restore")
        result = restore_db();

    return ${type: "message_box", text: "Result", description: result};

}


QString PMDatabaseManager::create_db() {

    QString stmn = $"createdb -U postgres ${source_database$s}";
    PSystem(stmn.toUtf8());
    PLog().debug() << stmn;
    return "Database Created";

}

QString PMDatabaseManager::remove_db() {
    
    QString stmn = $"dropdb -U postgres ${source_database$s}";
    PSystem(stmn.toUtf8());
    PLog().debug() << stmn;
    return "Database Removed";

}


QString PMDatabaseManager::rename_db() {

    QString stmn = $"psql -U postgres template1 -c \"ALTER DATABASE ${source_database$s} RENAME TO ${dest_database$s}\"";
    system(stmn.toUtf8()); // PSystem doesn't work
    PLog().debug() << stmn;
    return "Database Renamed";

}


QString PMDatabaseManager::backup_db() {

    QString stmn = $"pg_dump -U postgres -Fc ${source_database$s} -f moc_plusqode/${source_database$s}-bck.dump";

    PSystem(stmn.toUtf8());
    PLog().debug() << stmn;
    return "Backup Successfully";

}

QString PMDatabaseManager::restore_db() {

    QString stmn1 = $"createdb -U postgres -T template0 ${source_database$s}";
    QString stmn2 = $"pg_restore -U postgres -d ${source_database$s} moc_plusqode/${source_database$s}-bck.dump";

    PSystem($"${stmn1};${stmn2}");
    PLog().debug() << $"${stmn1};${stmn2}";
    
    return "Restored Successfully";

}


QString PMDatabaseManager::duplicate_db() {
    
    QString stmn1 = $"pg_dump -U postgres -Fc ${source_database$s} -f moc_plusqode/${source_database$s}.dump";
    QString stmn2 = $"dropdb -U postgres ${dest_database$s}";
    QString stmn3 = $"createdb -U postgres -T template0 ${dest_database$s}";
    QString stmn4 = $"pg_restore -U postgres -d ${dest_database$s} moc_plusqode/${source_database$s}.dump";

    PSystem($"${stmn1};${stmn2};${stmn3};${stmn4}");
    qDebug() << $"${stmn1};${stmn2};${stmn3};${stmn4}" << "\n";

    return "Database Duplicated";

}

