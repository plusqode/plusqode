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

#include "app/modules/database_manager/pmdatabase_import/pmdatabase_import.h"

PMDatabaseImport::$PMDatabaseImport() {

    init(args);

}

PMDatabaseImport& PMDatabaseImport::init(PVariant args) {

    PModel::init(args);

    name$ = $pt();
    source_database_connection_id$ = $pm2o(modelName: "database_connection");
    dest_database_connection_id$ = $pm2o(modelName: "database_connection");
    database_import_table_map_table$ = $pa();

    /*
    QString importButton =     
    "<menusection name='Import'>"
       "<menuitem action='Import' icon=\"{name: 'picons/core/actions-128/db-import.png', width:48, height: 48}\"/>"
    "</menusection>";

    import_button$ = $pw(xml: importButton);
    */

    return *this;

}

bool PMDatabaseImport::onOkDialog() {

    if(name$s.isEmpty())
        name$ = $"${source_database_connection_id$b->name$s} => ${dest_database_connection_id$b->name$s}";

    return true;

}


void PMDatabaseImport::import() {

    PModelPtr table_map = database_import_table_map_table$;
    $table_map->forEach(PModelPtr model) {
        model.value<PMDatabaseImportTableMap*>()->import();
    }

    $table_map->forEach(PModelPtr model) {
        model.value<PMDatabaseImportTableMap*>()->updateReferences();
    }

}


PVariant PMDatabaseImport::action(PVariant action) {

    if(action.action$s == "import") {
        import();

    return ${type: "message_box",
      description: "import successfully",
             icon: "picons/core/actions-128/ok.png"};
    }

}
