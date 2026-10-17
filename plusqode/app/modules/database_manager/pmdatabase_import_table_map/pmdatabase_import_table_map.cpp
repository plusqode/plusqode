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

#include "app/modules/database_manager/pmdatabase_import_table_map/pmdatabase_import_table_map.h"
#include "app/modules/pmodules.h"
    
PVariant PMDatabaseImportTableMap::tableMap = ${};

PMDatabaseImportTableMap::$PMDatabaseImportTableMap() {

    init(args);

}

PMDatabaseImportTableMap& PMDatabaseImportTableMap::init(PVariant args) {

    models = nil;


    PModel::init(args);

    name$ = $pt();
    source_table_id$ = $pm2o(modelName: "database_connection_table", onDelete: "cascade", filter: ${id: 0}, sortField: 'name', newButton: false, editButton: false); // filter is used in the ComboBox
    dest_table_id$ = $pm2o(modelName: "database_connection_table", onDelete: "cascade", filter: ${id: 0}, sortField: 'name', newButton: false, editButton: false);
    to_clean_before$ = $pb(fieldType: "switch_edit", default: true);
    database_import_field_map_table$ = $pa();
    database_import_id$ = $pa(onDelete: "cascade");

    source_pre_sql$ = $pt(fieldType: "plain_text_edit");
    source_post_sql$ = $pt(fieldType: "plain_text_edit");

    dest_pre_sql$ = $pt(fieldType: "plain_text_edit");
    dest_post_sql$ = $pt(fieldType: "plain_text_edit");

    return *this;

}

void PMDatabaseImportTableMap::setFilter() {

    source_table_id_attrs$ = ${filter: {database_connection_id: database_import_id$->source_database_connection_id$b->id$s}};
    dest_table_id_attrs$ = ${filter: {database_connection_id: database_import_id$->dest_database_connection_id$b->id$s}};


}

void PMDatabaseImportTableMap::onNewBeforeWidget() {
    
    setFilter();

}  

void PMDatabaseImportTableMap::onNewAfterWidget() {
    
    name$w->setDisabled(true);

}  

void PMDatabaseImportTableMap::onEditBeforeWidget() {

    source_table_id_attrs$ = ${filter: {id: source_table_id$b->id$s}};
    dest_table_id_attrs$ = ${filter: {id: dest_table_id$b->id$s}};

}

void PMDatabaseImportTableMap::onEditAfterWidget() {

    name$w->setEnabled(true);

}

bool PMDatabaseImportTableMap::onOkDialog() {

    if(name$s.isEmpty())
        name$ = $"${source_table_id$b->name$s} => ${dest_table_id$b->name$s}";

    return true;

}

bool PMDatabaseImportTableMap::toSkip() {

    return (source_table_id$b == nil || dest_table_id$b == nil);

}

void PMDatabaseImportTableMap::import() {

    if(toSkip()) return;

    QProgressDialog progress($"Migration from ${source_table_id$b->name$s} => ${dest_table_id$b->name$s}",
                             "Abort Copy", 0, 100);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();

    $PLog(color: "high_cyan", levelStr: "INFO").debug() << "Import Table";

    sourceSqlPtr =      database_import_id$->source_database_connection_id$b.value<PMDatabaseConnection*>()->getSql();
    PSqlPtr sourcedb = database_import_id$->source_database_connection_id$b.value<PMDatabaseConnection*>()->getSql();
    destSqlPtr =      database_import_id$->dest_database_connection_id$b.value<PMDatabaseConnection*>()->getSql();
    PSqlPtr destdb = database_import_id$->dest_database_connection_id$b.value<PMDatabaseConnection*>()->getSql();

    PModelPtr fieldMap = database_import_field_map_table$;

    $PLog(color: "high_cyan", levelStr: "INFO").debug() << "===================================================";
    $PLog(color: "high_cyan", levelStr: "INFO").debug() << $"=== MIGRATION from ${source_table_id$b->name$s} => ${dest_table_id$b->name$s}";
    $PLog(color: "high_cyan", levelStr: "INFO").debug() << "===================================================";

    PVariant tm = ${}; // table map
    tableMap[:dest_table_id$b->name$s] = tm;
    destSqlPtr->execute($"ALTER TABLE ${dest_table_id$b->name$s} DISABLE TRIGGER ALL");
    if(to_clean_before$b) destSqlPtr->erase(dest_table_id$b->name$s, true);
    if(source_pre_sql$s != "") sourceSqlPtr->execute(source_pre_sql$s);
    if(dest_pre_sql$s != "") destSqlPtr->execute(dest_pre_sql$s);

    int i = 0;
    sourceSqlPtr->select()->$from(source_table_id$b->name$s)->$orderBy(id: "asc")->$execute();
    progress.setRange(0, sourceSqlPtr->count());
    $sourceSqlPtr->forEach(PVariant record) {
        progress.setValue(i++);
        PVariant newRecord = ${};
        $fieldMap->forEach(PModelPtr mapModelPtr) {
            PVariant value = 0;
            if(mapModelPtr->source_field_id$b->id$i)
                value = record[mapModelPtr->source_field_id$b->name$s];
            // value = eval(map.converter_function) if map.converter_function.strip != ""
            newRecord[mapModelPtr->dest_field_id$b->name$s] = value;
        }
        tm[record.id$s] = destSqlPtr->insert(dest_table_id$b->name$s, newRecord);
    }
    
    progress.close();

}


PModelPtr PMDatabaseImportTableMap::getModelPtr(const QString& modelName) {

    if(models == nil) this->models = ${};
    
    if(models.include(modelName)) 
        return models[modelName].toModelPtr();

    models[modelName] = this->newPModel(modelName).toVariant();
    return models[modelName].toModelPtr();

}

void PMDatabaseImportTableMap::updateReferences() {

    if(toSkip()) return;

    QProgressDialog progress($"Update Reference from ${source_table_id$b->name$s} => ${dest_table_id$b->name$s}",
                             "Abort Copy", 0, 100);
    progress.setWindowModality(Qt::WindowModal);
    progress.show();


    $PLog(color: "high_cyan", levelStr: "INFO").debug() << $"===================================================";
    $PLog(color: "high_cyan", levelStr: "INFO").debug() << $"=== Update Reference from ${source_table_id$b->name$s} => ${dest_table_id$b->name$s}";
    $PLog(color: "high_cyan", levelStr: "INFO").debug() << $"===================================================";

    PModelPtr fieldMap = database_import_field_map_table$; 
    PSqlPtr dest2HDB = database_import_id$->dest_database_connection_id$b.value<PMDatabaseConnection*>()->getSql();

    destSqlPtr->select()->$from(dest_table_id$b->name$s)->$execute();

    int i = 0;
    progress.setRange(0, sourceSqlPtr->count());
    $destSqlPtr->forEach(PVariant record) {
        progress.setValue(i++);
        $fieldMap->forEach(PModelPtr mapModelPtr) {
            if(mapModelPtr->update_reference$b) {
                QString sourceTableReferenceName = getModelPtr(dest_table_id$b->name$s)->fieldAttr(mapModelPtr->dest_field_id$b->name$s)["modelNameReference"].toString();
                QString sourceId = record[mapModelPtr->dest_field_id$b->name$s].toString();
                QString mappedId = tableMap[sourceTableReferenceName][sourceId].toString();
                PVariant newRecord = ${};
                newRecord[mapModelPtr->dest_field_id$b->name$s] = mappedId;
                $PLog(color: "high_cyan", levelStr: "INFO").debug() << "- - - - - >" << sourceTableReferenceName;
                $PLog(color: "high_cyan", levelStr: "INFO").debug() << newRecord.toString();
                dest2HDB->update(dest_table_id$b->name$s, newRecord, ${id: record["id"]});
            }
        }
    }

    progress.close();

    destSqlPtr->execute($"ALTER TABLE ${dest_table_id$b->name$s} ENABLE TRIGGER ALL");

    PSqlPtr sourcedb = database_import_id$->source_database_connection_id$b.value<PMDatabaseConnection*>()->getSql();
    PSqlPtr destdb = database_import_id$->dest_database_connection_id$b.value<PMDatabaseConnection*>()->getSql();
    if(after$s != "") destdb->execute(after$s);
    if(source_post_sql$s != "") sourceSqlPtr->execute(source_post_sql$s);
    if(dest_post_sql$s != "") destSqlPtr->execute(dest_post_sql$s);

    //eval(self.after) if self.after
  
}

