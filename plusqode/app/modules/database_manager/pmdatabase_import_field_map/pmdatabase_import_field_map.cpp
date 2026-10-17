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

#include "app/modules/database_manager/pmdatabase_import_field_map/pmdatabase_import_field_map.h"
#include "app/modules/pmodules.h"

PMDatabaseImportFieldMap::$PMDatabaseImportFieldMap() {

    init(args);

}

PMDatabaseImportFieldMap& PMDatabaseImportFieldMap::init(PVariant args) {

    PModel::init(args);

    name$ = $pa();
    source_field_id$ = $pm2o(modelName: "database_connection_table_field", onDelete: "cascade", sortField: 'name', filter: ${id: 0});
    dest_field_id$ = $pm2o(modelName: "database_connection_table_field", onDelete: "cascade", sortField: 'name', filter: ${id: 0});
    update_reference$ = $pb(fieldType: "switch_edit", default: false);
    converter_function$ = $pt(fieldType: "plain_text_edit");
    database_import_table_map_id$ = $pa(onDelete: "cascade");

    return *this;

}

void PMDatabaseImportFieldMap::setFilter() {

    source_field_id_attrs$ = ${filter: {database_connection_table_id: database_import_table_map_id$->source_table_id$b->id$s}};
    dest_field_id_attrs$ = ${filter: {database_connection_table_id: database_import_table_map_id$->dest_table_id$b->id$s}};

}

void PMDatabaseImportFieldMap::onNewBeforeWidget() {

    setFilter();

}  

void PMDatabaseImportFieldMap::onNewAfterWidget() {

    name$w->setDisabled(true);

}  


void PMDatabaseImportFieldMap::onEditBeforeWidget() {

    if(source_field_id$b != nil) source_field_id_attrs$ = ${filter: {id: source_field_id$b->id$s}};
    dest_field_id_attrs$ = ${filter: {id: dest_field_id$b->id$s}};

}

void PMDatabaseImportFieldMap::onEditAfterWidget() {

    name$w->setEnabled(true);

}

bool PMDatabaseImportFieldMap::onOkDialog() {
    
    if(name$s.isEmpty())
        name$ = $"${source_field_id$b->name$s} => ${dest_field_id$b->name$s}";

    return true;

}

