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



   #include "sql/psqlgenerator.h"

   
   
   #include "app/modules/pmodules.h"

   
   
   
   
   
 

void PSqlGenerator:: init(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "init:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
bool dropTables = source_args.value<PVariantMapPtr>()->include("dropTables") ? source_args.value<PVariantMapPtr>()->operator[]("dropTables").toBool() : QVariant(false).toBool();args.removeByKey("dropTables");
QString connectionName = source_args.value<PVariantMapPtr>()->include("connectionName") ? source_args.value<PVariantMapPtr>()->operator[]("connectionName").toString() : QVariant(nil).toString();args.removeByKey("connectionName");


    if(connectionName.isNull())
        connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    pTables = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    this->dropTables = dropTables;
    this->connectionName = connectionName;

    this->modules = PVariant::fromQStringList(PDir(PString(QString("%1").arg(PGlobal::modulePath()))).   onlyDirectories(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("recursive", false)->append("onlyFileName", true))))));

    this->initModule();
    this->initDataLoader();

}


void PSqlGenerator::init_pTables() {

    databases = db_databases();
    dbTables = db_tables();

    pTables = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))); 
    PVariant pt = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))); 

     modules.forEachQString([&] (QString moduleName) mutable {
        PVariant tom = modelsOfModule(moduleName);
         tom.forEachQString([&] (QString tableName) mutable {
            pt[tableName] = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("moduleName", moduleName))));
            createScaffoldTable(tableName); 
        });
    });

       pt.forEachQString_PVariant([&] (QString modelName,PVariant tableInfo) mutable {
        PModelPtr model = PModules::   newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("connectionName", connectionName)))));
        model->setParent(this);
        QString tableName = model->modelName;

        if(!pTables.include(tableName)) pTables[tableName] = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fields", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))))->append("model",     model.toVariant()))));

        pTables[tableName]["fields"] += model->pFields;

    });

}


void PSqlGenerator::initModule() {

    init_pTables();

    if(QDir().exists(PString(QString("%1/definitions.json").arg(PGlobal::jsonDbPath()))))
        this->dynamicMigrations(this->pTables);
    else {PVariant _keys_0_ = pTables.keys();
for(int _i_0_ = 0; _i_0_ < _keys_0_.count(); _i_0_++) {
PString tableName = _keys_0_[_i_0_].toString();
PVariant tableInfo = pTables.operator[](tableName);
            if(this->dropTables) {
                PLog().sql() << "drop table" << tableName;
                this->dropTable(tableName);
            }
            PLog().sql() << "create table" << tableName;
            this->createScaffoldTable(tableName);
        }PVariant _keys_1_ = pTables.keys();
for(int _i_1_ = 0; _i_1_ < _keys_1_.count(); _i_1_++) {
PString tableName = _keys_1_[_i_1_].toString();
PVariant tableInfo = pTables.operator[](tableName);
            PVariant modelVariant = tableInfo["model"];
            PModelPtr model = modelVariant.toModelPtr();
            tableName = model->modelName;
            PVariant dbFields = db_fields(tableName);
            PVariant pFields = tableInfo.undefined("fields", nil);

            PVariant fieldsToDrop = dbFields - pFields.keys() - model->systemFields().keys();

            this->dropFields(tableName, fieldsToDrop);

            this->before(tableName);PVariant _keys_2_ = pFields.keys();
for(int _i_2_ = 0; _i_2_ < _keys_2_.count(); _i_2_++) {
PString fieldName = _keys_2_[_i_2_].toString();
PVariant fieldAttrs = pFields.operator[](fieldName);
                this->_addField(dbFields, tableName, fieldName, fieldAttrs);
            }

            this->after(tableName);
        }
    }


    PVariant definitions = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    PVariant references = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));PVariant _keys_3_ = pTables.keys();
for(int _i_3_ = 0; _i_3_ < _keys_3_.count(); _i_3_++) {
PString tableName = _keys_3_[_i_3_].toString();
PVariant tableInfo = pTables.operator[](tableName);
        PVariant modelVariant = tableInfo["model"];
        PModelPtr model = modelVariant.toModelPtr();
        PVariant pFields = tableInfo.undefined("fields", nil);
        if(definitions[tableName] == nil) definitions[tableName] = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
        definitions[tableName] += this->tableMask(pFields);PVariant _keys_4_ = pFields.keys();
for(int _i_4_ = 0; _i_4_ < _keys_4_.count(); _i_4_++) {
PString fieldName = _keys_4_[_i_4_].toString();
PVariant field = pFields.operator[](fieldName);
            if(field["type"] == "oneToOne" || field["type"] == "manyToOne") {
                QString modelNameReference = field["modelNameReference"].toString();
                QString onDelete = field["onDelete"].toString();
                QString onUpdate = field["onUpdate"].toString();
                if(references[modelNameReference] == nil) references[modelNameReference] = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
                references[modelNameReference] << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tableName", tableName)->append("fieldName", fieldName)->append("onDelete", onDelete)->append("onUpdate", onUpdate))));
            }

            else if(field["type"] == "manyToMany") {
               QString modelNameReference = field["modelNameReference"].toString();
               QString joinTable = field["joinTable"].toString();
               QString referenceFieldName = field["referenceFieldName"].toString();
               QString referenceFieldName2 = field["referenceFieldName2"].toString();
               QString onDelete = field["onDelete"].toString();
               QString onUpdate = field["onUpdate"].toString();
               
               
               
               if(references[tableName] == nil) references[tableName] = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
               references[tableName] << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tableName", joinTable)->append("fieldName", referenceFieldName)->append("onDelete", onDelete)->append("onUpdate", onUpdate))));
               if(references[modelNameReference] == nil) references[modelNameReference] = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
               references[modelNameReference] << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tableName", joinTable)->append("fieldName", referenceFieldName2)->append("onDelete", onDelete)->append("onUpdate", onUpdate))));
           }


        }

    }

    QDir().mkpath(PGlobal::jsonDbPath());

    PDir::fileWrite(PString(QString("%1/definitions.json").arg(PGlobal::jsonDbPath())), definitions.toString().toUtf8());
    PDir::fileWrite(PString(QString("%1/references.json").arg(PGlobal::jsonDbPath())), references.toString().toUtf8());

}

PVariant PSqlGenerator::modelsOfModule(const QString& moduleName) {

    PVariant tables = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    QStringList files = PDir(PString(QString("%1/%2").arg(PGlobal::modulePath()).arg(moduleName))).onlyFiles(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("PM*.h"))))));for(int _i_5_ = 0; _i_5_ < files.count(); _i_5_++) {
PString fileName = files.operator[](_i_5_);
        if(fileName.contains("_controller.h")) continue;
        QString tableName = fileName;
        tableName.chop(2); 
        tables << tableName.mid(2);
    }

    return tables;

}


void PSqlGenerator::initDataLoader() {

    
     dbTables.forEachQString([&] (QString tableName) mutable { this->disableTrigger(tableName); });

    PLog().sql() << "Init Data Loader";for(int _i_6_ = 0; _i_6_ < modules.count(); _i_6_++) {
QString moduleName = modules.operator[](_i_6_).toString();
        PVariant models = modelsOfModule(moduleName);for(int _i_7_ = 0; _i_7_ < models.count(); _i_7_++) {
QString modelName = models.operator[](_i_7_).toString();
            PModelPtr model = PModules::   newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("connectionName", connectionName)))));
            model->setParent(this);
            QString tableName = model->modelName;
            if(this->generatedTables[tableName]) {
                this->dataLoader(moduleName, modelName, tableName);
                
                 PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("high_cyan")))))).sql() << PString(QString("... %1 data loading ... ok").arg(modelName));
            }

        }

    }

    
     dbTables.forEachQString([&] (QString tableName) mutable { this->enableTrigger(tableName); });
    this->finalize();

}

void PSqlGenerator::dataLoader(const QString& moduleName, const QString& modelName, const QString& tableName) {

    PVariant files = PVariant::fromQStringList(PDir(PString(QString("%1/%2/pm%3").arg(PGlobal::modulePath()).arg(moduleName).arg(modelName))).onlyFullFiles(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("*.yml")))))));

    files = files.quicksort();

     files.forEachQString([&] (QString fileName) mutable {
        PSqlDataLoader loader(fileName, connectionName);
        loader.load();
    });

}

void PSqlGenerator::dropFields(const QString& tableName, PVariant dbFields) {for(int _i_8_ = 0; _i_8_ < dbFields.count(); _i_8_++) {
PVariant field = dbFields.operator[](_i_8_);
        this->dropField(dbFields, tableName, field.toString());
    }

}

void PSqlGenerator::columnCopy(const QString& tableName, const QString& fieldName, const QString& oldFieldName, const QString& type) {

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).execute(PString(QString("update %1 set %2 = %3::%4").arg(tableName).arg(fieldName).arg(oldFieldName).arg(type)));

}

PVariant PSqlGenerator::fieldMask(PVariant attrs) {

    PVariant mask = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("system", nil)->append("type", nil)->append("default", nil)->append("onDelete", nil)->append("onUpdate", nil)->append("constraint", nil)->append("modelNameReference", nil)->append("referenceFieldName", nil)->append("referenceFieldName2", nil)->append("joinTable", nil))));

    PVariant result = attrs & mask;

    if( PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("date"))->append(QString("time"))->append(QString("datetime"))))).include(attrs["type"]))
        result["default"] = PSql::db_current(attrs["type"].toString());

    return result;

}


PVariant PSqlGenerator::tableMask(PVariant fields) {

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));PVariant _keys_9_ = fields.keys();
for(int _i_9_ = 0; _i_9_ < _keys_9_.count(); _i_9_++) {
PString fieldName = _keys_9_[_i_9_].toString();
PVariant attrs = fields.operator[](fieldName);
        result[fieldName] = this->fieldMask(attrs);
    }

    return result;

}

void PSqlGenerator::attributeMigration(PVariant dbFields, PVariant pFields, PVariant definitions, const QString& tableName) {PVariant _keys_10_ = pFields.keys();
for(int _i_10_ = 0; _i_10_ < _keys_10_.count(); _i_10_++) {
PString fieldName = _keys_10_[_i_10_].toString();
PVariant fieldAttrs = pFields.operator[](fieldName);
        if(fieldAttrs["type"] == "virtual") continue;
        if(fieldAttrs["type"] == "widget") continue;
        if(fieldAttrs["type"] == "oneToMany") continue;
        if(!definitions.include(tableName) || !definitions[tableName].include(fieldName)) continue;
        if(fieldMask(fieldAttrs) != fieldMask(definitions[tableName][fieldName])) {
             PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("high_purple")))))).sql() << fieldMask(fieldAttrs).toString();
             PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("high_cyan")))))).sql() << fieldMask(definitions[tableName][fieldName]).toString();
            QString oldFieldName = renameFieldName(dbFields, tableName, fieldName);
            _addField(dbFields, tableName, fieldName, fieldAttrs, true);
            QString type = toType(fieldAttrs["type"].toString());
            columnCopy(tableName, fieldName, oldFieldName, type);
            dropField(dbFields, tableName, oldFieldName, true);
        }
    }

}


void PSqlGenerator::dynamicMigrations(PVariant pTables) {

    PConfiguration config(PString(QString("%1/definitions.json").arg(PGlobal::jsonDbPath())));

    PVariant definitions = config.cfg();

    if(definitions == nil) {
        PLog().error() << "PSqlGenerator::dynamicMigrations() error";
        PLog().error() << "It's possible to have in .cpp files something with ' like this";
        PLog().error() << "    name$ = $pt(main: true, default: \"caffe'\");";
        
    }

    

    PVariant toRemoveTables = definitions.keys() - pTables.keys();
    PVariant toAddTables = pTables.keys() - definitions.keys();

    PLog().sql() << PString(QString("Tabelle da rimuovere: %1").arg(toRemoveTables.toString()));
    PLog().sql() << PString(QString("Tabelle da aggiugere: %1").arg(toAddTables.toString()));PVariant _keys_11_ = pTables.keys();
for(int _i_11_ = 0; _i_11_ < _keys_11_.count(); _i_11_++) {
PString tableName = _keys_11_[_i_11_].toString();
PVariant tableInfo = pTables.operator[](tableName);
        PLog().sql() << PString(QString("Migrazione tabella: %1").arg(tableName));
        PVariant dbFields = db_fields(tableName);
        
        PVariant pFields = tableInfo.undefined("fields", nil);
        PVariant toAddFields = pFields.keys();
        PVariant toRemoveFields = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
        if(definitions.include(tableName)) {
            toAddFields = pFields.keys() - definitions[tableName].keys();
            toRemoveFields = definitions[tableName].keys() - pFields.keys();
        }
        if (toAddFields.any()) PLog().sql() << PString(QString("Campi da aggiungere: %1").arg(toAddFields.toString()));for(int _i_12_ = 0; _i_12_ < toAddFields.count(); _i_12_++) {
QString fieldName = toAddFields.operator[](_i_12_).toString();
            _addField(dbFields, tableName, fieldName, pFields[fieldName]);
        }
        if(toRemoveFields.any()) PLog().sql() << PString(QString("Campi da rimuovere: %1").arg(toRemoveFields.toString()));for(int _i_13_ = 0; _i_13_ < toRemoveFields.count(); _i_13_++) {
QString fieldName = toRemoveFields.operator[](_i_13_).toString();
            dropField(dbFields, tableName, fieldName);
        }
        attributeMigration(dbFields, pFields, definitions, tableName);
    }

}

void PSqlGenerator::_addField(PVariant dbFields,
                              const QString& tableName,
                              const QString& fieldName,
                              PVariant fieldAttrs, bool force) {


       PLog().sql() << PString(QString("%1.%2 %3").arg(tableName).arg(fieldName).arg(fieldAttrs.toString()));

       if(dbFields.include(fieldName) && force == false)
           return;


       if(fieldAttrs["type"] == "oneToMany" || fieldAttrs["type"] == "manyToMany")
           return;

       QString type = this->toType(fieldAttrs["type"].toString());
       this->addField(tableName, fieldName, type,
                      fieldAttrs("constraint").toString(),
                      fieldAttrs("default").toString(),
                      fieldAttrs("modelNameReference").toString(),
                      fieldAttrs("onDelete").toString(),
                      fieldAttrs("onUpdate").toString());

}

void PSqlGenerator::createScaffoldTable(const QString& tableName) {

    if(!dbTables.include(tableName)) {
        this->createTable(tableName);
        this->addSystemFields(tableName);
        generatedTables[tableName] = true;
    }


}

   #include "sql/ppgsqlgenerator.h"
   #include "sql/pmysqlgenerator.h"
   #include "sql/psqlitegenerator.h"

PSqlGenerator* PSqlGenerator::initDatabase() {

    
    


    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    QString driver = PConf().value(PString(QString("%1.driver").arg(connectionName))).toString();

    if(driver == "QPSQL") {
        PLog().sql() << "Database Driver:" << driver;
        PPgSqlGenerator::initDatabase();
        PSql::initByConnectionName(connectionName);
        
        PPgSqlGenerator* dbGenerator = new PPgSqlGenerator();
        dbGenerator-> init(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("dropTables", true)))));
        return dbGenerator;
    }

    else if(driver == "QMYSQL") {
        PLog().sql() << "Database Driver:" << driver;
        PMySqlGenerator::initDatabase();
        PSql::initByConnectionName(connectionName);
        PMySqlGenerator* dbGenerator = new PMySqlGenerator();
        dbGenerator-> init(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("dropTables", true)))));
        return dbGenerator;
    }

    else if(driver == "QSQLITE") {
        PLog().sql() << "Database Driver:" << driver;
        PSqliteGenerator::initDatabase();
        PSql::initByConnectionName(connectionName);
        PSqliteGenerator* dbGenerator = new PSqliteGenerator();
        dbGenerator-> init(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("dropTables", true)))));
        return dbGenerator;
    }

    else  {
        PLog().sql() << PString(QString("Driver %1not Supported").arg(driver ));
        exit(0);
    }

}


void PSqlGenerator::dump() {

    QString fileName = QDate::currentDate().toString("yyyy-MM-dd");
    fileName = PString(QString("%1/backup/%2.bck").arg(PGlobal::basePath()).arg(fileName));
     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "PSqlGenerator::dump() - - - >" << fileName;
    this->dump(fileName);

}
