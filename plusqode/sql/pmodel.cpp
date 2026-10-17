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






   #include "sql/pmodel.h"




   



   
   #include "app/modules/pmodules.h"




   



   
   



   
   
 
   #include "misc/ptelemetry.h"




   



   
   



   
   
 
   



   
   
 
   
 
 

int PModel   ::sysModelCounter = 0;
QList<PModel*> PModel   ::sysModelList;


PVariant PModel   ::autoComplete(const QString& modelName, QString fieldName, PVariant args) {

    return PSqlField::autoComplete(modelName, fieldName, args);

}

PVariant PModel   ::pAuto(PVariant args) {

    return PSqlField::pAuto(args);

}

PVariant PModel   ::pa(PVariant args) {

    return PSqlField::pa(args);

}

PVariant PModel   ::pText(PVariant args) {

    return PSqlField::pText(args);

}

PVariant PModel   ::pt(PVariant args) {

    return PSqlField::pt(args);

}


PVariant PModel   ::pInteger(PVariant args) {

    return PSqlField::pInteger(args);

}

PVariant PModel   ::pi(PVariant args) {

    return PSqlField::pi(args);

}

PVariant PModel   ::pFloat(PVariant args) {

    return PSqlField::pFloat(args);

}

PVariant PModel   ::pf(PVariant args) {

    return PSqlField::pf(args);

}

PVariant PModel   ::pDate(PVariant args) {

    return PSqlField::pDate(args);

}

PVariant PModel   ::pd(PVariant args) {

    return PSqlField::pd(args);

}

PVariant PModel   ::pTime(PVariant args) {

    return PSqlField::pTime(args);

}


PVariant PModel   ::pDateTime(PVariant args) {

    return PSqlField::pDateTime(args);

}

PVariant PModel   ::pdt(PVariant args) {

    return PSqlField::pdt(args);

}

PVariant PModel   ::pBool(PVariant args) {

    return PSqlField::pBool(args);

}

PVariant PModel   ::pb(PVariant args) {

    return PSqlField::pb(args);

}

PVariant PModel   :: pOneToOne(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pOneToOne:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");


    return PSqlField::pOneToOne(source_args);

}

PVariant PModel   :: po2o(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "po2o:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");


    return PSqlField::pOneToOne(source_args);

}

PVariant PModel   :: pOneToMany(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pOneToMany:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
QString referenceFieldName = source_args.value<PVariantMapPtr>()->include("referenceFieldName") ? source_args.value<PVariantMapPtr>()->operator[]("referenceFieldName").toString() : QVariant(nil).toString();args.removeByKey("referenceFieldName");


    return PSqlField::pOneToMany(source_args);

}

PVariant PModel   :: po2m(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "po2m:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
QString referenceFieldName = source_args.value<PVariantMapPtr>()->include("referenceFieldName") ? source_args.value<PVariantMapPtr>()->operator[]("referenceFieldName").toString() : QVariant(nil).toString();args.removeByKey("referenceFieldName");


    return PSqlField::pOneToMany(source_args);

}

PVariant PModel   :: pManyToOne(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pManyToOne:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");


    return PSqlField::pManyToOne(source_args);

}

PVariant PModel   :: pm2o(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pm2o:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");


    return PSqlField::pManyToOne(source_args);

}

PVariant PModel   :: pManyToMany(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pManyToMany:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
QString joinTable = source_args.value<PVariantMapPtr>()->include("joinTable") ? source_args.value<PVariantMapPtr>()->operator[]("joinTable").toString() : QVariant(nil).toString();args.removeByKey("joinTable");
QString referenceFieldName = source_args.value<PVariantMapPtr>()->include("referenceFieldName") ? source_args.value<PVariantMapPtr>()->operator[]("referenceFieldName").toString() : QVariant(nil).toString();args.removeByKey("referenceFieldName");
QString referenceFieldName2 = source_args.value<PVariantMapPtr>()->include("referenceFieldName2") ? source_args.value<PVariantMapPtr>()->operator[]("referenceFieldName2").toString() : QVariant(nil).toString();args.removeByKey("referenceFieldName2");


    return PSqlField::pManyToMany(source_args);

}

PVariant PModel   :: pm2m(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pm2m:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
QString joinTable = source_args.value<PVariantMapPtr>()->include("joinTable") ? source_args.value<PVariantMapPtr>()->operator[]("joinTable").toString() : QVariant(nil).toString();args.removeByKey("joinTable");
QString referenceFieldName = source_args.value<PVariantMapPtr>()->include("referenceFieldName") ? source_args.value<PVariantMapPtr>()->operator[]("referenceFieldName").toString() : QVariant(nil).toString();args.removeByKey("referenceFieldName");
QString referenceFieldName2 = source_args.value<PVariantMapPtr>()->include("referenceFieldName2") ? source_args.value<PVariantMapPtr>()->operator[]("referenceFieldName2").toString() : QVariant(nil).toString();args.removeByKey("referenceFieldName2");


    return PSqlField::pManyToMany(source_args);

}

PVariant PModel   :: pVirtual(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pVirtual:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString functionName = source_args.value<PVariantMapPtr>()->include("functionName") ? source_args.value<PVariantMapPtr>()->operator[]("functionName").toString() : QVariant(nil).toString();args.removeByKey("functionName");


    return PSqlField::pVirtual(source_args);

}


PVariant PModel   ::pv(PVariant args) {

    return PSqlField::pv(args);

}

PVariant PModel   ::pv(PFunc f) {

    PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    args["function"] = QVariant::fromValue(f);
    args["function_type"] = "PFunc";
    args["type"] = "virtual";
    return args;

}

PVariant PModel   ::pv(PVariant args, PFunc f) {

    args["function"] = QVariant::fromValue(f);
    args["function_type"] = "PFunc";
    args["type"] = "virtual";
    return args;

}

PVariant PModel   ::pv(PVariant args, PFuncPVariant f) {

    args["function"] = QVariant::fromValue(f);
    args["function_type"] = "PFuncPVariant";
    args["type"] = "virtual";
    return args;

}

PVariant PModel   ::pv(PVariant args, PFuncQStringPVariant f) {

    args["function"] = QVariant::fromValue(f);
    args["function_type"] = "PFuncQStringPVariant";
    args["type"] = "virtual";
    return args;

}

PVariant PModel   :: pWidget(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pWidget:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString functionName = source_args.value<PVariantMapPtr>()->include("functionName") ? source_args.value<PVariantMapPtr>()->operator[]("functionName").toString() : QVariant(nil).toString();args.removeByKey("functionName");


    return PSqlField::pWidget(source_args);

}


PVariant PModel   ::pw(PVariant args) {

    return PSqlField::pw(args);

}

PVariant PModel   ::primaryKey(PVariant args) {

    return PSqlField::primaryKey(args);

}

PVariant PModel   ::serial(PVariant args, QString tableName) {

    return PSqlField::serial(args, tableName);

} PModel   :: PModel   () {

} PModel   ::~ PModel   () { PModel   ::sysModelCounter--;

    if( PModel   ::sysModelList.contains(this)) { PModel   ::sysModelList.removeOne(this);
        
        delete this->psql;
    }
    else {
        PTelemetry* telemetry = PSinglTelemetry::instance();
        telemetry->add(PString(QString("memory_leak/totals")), 1);
        telemetry->add(PString(QString("memory_leak/%1").arg(modelName)), 1);
        qDebug() << PString(QString(" -  - - - - - > PModel::~PModel() ... %1 - %2").arg(modelName).arg(sysModelCounter)) << this << PModel   ::sysModelList.count() << " ........ error";
    }

    if( PModel   ::sysModelList.count() == 0)
        qDebug() << PString(QString("- - - > ~PModel ... ok"));

}


PModel* PModel   :: init(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "init:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(  getModelName()).toString();args.removeByKey("modelName");
PVariant parents = source_args.value<PVariantMapPtr>()->include("parents") ? source_args.value<PVariantMapPtr>()->operator[]("parents") : PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));args.removeByKey("parents");
QString connectionName = source_args.value<PVariantMapPtr>()->include("connectionName") ? source_args.value<PVariantMapPtr>()->operator[]("connectionName").toString() : QVariant(        defaultConnectionName()).toString();args.removeByKey("connectionName");
PVariant connectionParams = source_args.value<PVariantMapPtr>()->include("connectionParams") ? source_args.value<PVariantMapPtr>()->operator[]("connectionParams") : nil;args.removeByKey("connectionParams");
PVariant domain = source_args.value<PVariantMapPtr>()->include("domain") ? source_args.value<PVariantMapPtr>()->operator[]("domain") : PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));args.removeByKey("domain");
bool generate = source_args.value<PVariantMapPtr>()->include("generate") ? source_args.value<PVariantMapPtr>()->operator[]("generate").toBool() : QVariant(true).toBool();args.removeByKey("generate");


    

    

    

    this->generate = generate;
    this->mainField = "name";  
    
    
    this->showField = "name";
    this->sortField = "ordering"; 

    this->type = QString();
    this->source = 0;
    this->sourceFieldName = QString();
    this->domain = domain;
    this->modelName = modelName;
    this->moduleName = QString();
    this->className = getClassName();
    this->connectionName = connectionName;
    this->connectionParams = connectionParams;
    this->psql = new  PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));
    this->parents = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())))); 
    this->pFields = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    this->tableFields = nil;
    this->modelFields = nil;
    this->allParents = nil;

    this->toWrite = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    this->toChange = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    this->toDelete = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    this->vid = 1;

    this->cacheMode = false;
    cacheValues = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    lastChangedFields = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    colWidth = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    this->setSystemFields();

    this->sqlView = 0;
    this->sqlFormViewDialog = 0;
    this->level = 0;
    this->writeOnDialog = false;
    this->dataChangedConnection = false;

    this->showFullScreen = false;

    this->tabLayoutDirection = Qt::LeftToRight;

    this->tabOrderFromCpp = false;

    this->dialogMode = false;

    this->fieldWidgets = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    this->autoView = false; PModel   ::sysModelCounter++; PModel   ::sysModelList << this;

    

    return this;

}


QString PModel   ::defaultConnectionName() {

    return PSharedDataManager::instance()->value("defaultConnectionName").toString();

}

QString PModel   ::getModelName() {

    return "PModel";

}

QString PModel   ::getClassName() {

    return QString(this->metaObject()->className()).mid(2); 

}


QString PModel   ::toClassName(QString modelName) {

   if(modelName == "PModel")
    return modelName;

   return PString(modelName).capitalize();

}




QString PModel   ::toModelName(QString className) {

    if(className == "")
        className = this->getClassName();

    if(className == "PModel")
        return "pmodel";

    if(className.startsWith("PM"))
        return PString(className.mid(2)).uncapitalize();

    return PString(className).uncapitalize();

}

PSql* PModel   ::get_psql() {

    return this->psql;

}

PModelPtr PModel   ::toRecordPtr(QString type) {

    return toModelPtr(getTableCursor(), type);

}

PModelPtr PModel   ::toModelPtr(PVariant tableCursor, QString type) {

    PModelPtr result(this, tableCursor, type);

    return result;

}

PVariant PModel   ::getTableCursor() {

    return psql->tableCursor;

}

void PModel   ::setCacheMode(bool mode) {

  PLog().debug() << PString(QString("setCacheMode: %1 - %2").arg(modelName).arg(mode));
  this->cacheMode = mode;
  if(mode) {
      this->cacheValues = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
      this->lastChangedFields = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
  }

}



void PModel   ::addField(const QString& fieldName, PVariant args) {

    PVariant field = autoComplete(modelName, fieldName, args); 
    pFields[fieldName] = field;
    PLog().debug() << PString(QString("addField: %1 %2").arg(fieldName).arg(field.toString()));

}


void PModel   ::setSystemFields() {

    QString timestamp = "";

    PSql  sql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));

    if(sql.connectionState == "connected")
        timestamp = sql.current("timestamp");

    pFields["id"] = primaryKey(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    pFields["create_date"] =    pd(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("default", timestamp)->append("system", true)))));
    pFields["update_date"] =    pd(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("default", timestamp)->append("system", true)))));
    pFields["ordering"] = serial( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))), modelName);

}

PVariant PModel   ::undefined(PString methodName, PVariant args) {

    PString fieldName = methodName;

    if(pFields.include(fieldName) && pFields[fieldName].include("modelNameReference")) {
        QString modelName = pFields[fieldName]["modelNameReference"].toString();
        QString type = fieldAttr(fieldName)["type"].toString();

        if (type == "manyToOne") {
            return manyToOne(modelName, fieldName).toVariant();
        }

        QString referenceFieldName = pFields[fieldName]["referenceFieldName"].toString();

        if (type == "oneToMany") {
            
            return oneToMany(fieldName, modelName, referenceFieldName).toVariant();
        }

    }

    else if(fieldName.endsWith("_id") && pFields.include(fieldName)) {
        PModelPtr model = this->manyToOne(fieldName.fromTo(0, -3), fieldName);
        return model.toVariant();
    }


    else if(fieldName.endsWith("_table") && pFields.include(fieldName)) {
        PModelPtr model = this->oneToMany(fieldName, fieldName.fromTo(0, -6), PString(QString("%1_id").arg(modelName)));
        return model.toVariant();
    }

    else if(fieldName.endsWith("_ptr") && pFields.include(fieldName.fromTo(0, -4)))
        return pFields[fieldName.fromTo(0, -4)];

    else if(fieldName.endsWith("_attrs=") ) {
        QString _fieldName = fieldName.fromTo(0, -7);
        pFields[_fieldName] += args;
    }

    else if(args == nil)
        return fieldValue(fieldName);

    else if(methodName.endsWith("=")) {
        methodName.chop(1);
        
        if(args != nil && args.typeName() == "Hash" && args.toMap().include("type")) 
            addField(methodName, args);
        else
            setFieldValue(methodName, args);
    }

    else if(methodName.startsWith("findBy_") && methodName.include("_and_")) {
        methodName = methodName.mid(7);
        PVariant list = methodName.split("_and_");

        

        PVariant map = list.toMap(args);

         findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", map)))));

    }

    else if(methodName.startsWith("findBy_") && methodName.include("_or_")) {

        methodName = methodName.mid(7);
        PVariant values = methodName.split("_or_");
           values.forEachWithIndexQString_int([&] (QString value,int i) mutable {
            values[i] = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( value,    args[i]))));
        });
         findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", values)))));

    }

    else if(methodName.startsWith("findBy_") && args.typeName() == "Array") {

        methodName = methodName.mid(7);
           findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( methodName, args)))))))));

    } 


    return nil;

}

bool PModel   ::isModelPtr(QString fieldName) {

  return (fieldName.startsWith("_") and fieldName.endsWith("_id_"));

}

QString PModel   ::modelPtr(QString fieldName) {

  return PString(QString("_%1_").arg(fieldName));

}

PModelPtr PModel   ::newPModel(QString modelName, QString type, PVariant domain) {

    QString className = this->toClassName(modelName);
    


    PModel* model;
    if(PModules::models().include(modelName)) {
        model = PModules::     newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("connectionName", connectionName)->append("domain", domain)))));
    }
    else {
        model = new PModel   ();
        model->       init(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("connectionName", connectionName)->append("connectionParams", connectionParams)->append("domain", domain)))));
    }

    model->source = this;
    model->type = type;

    model->setParent(this);

    return PModelPtr(model);
}


PModelPtr PModel   :: newModel(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "newModel:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
QString connectionName = source_args.value<PVariantMapPtr>()->include("connectionName") ? source_args.value<PVariantMapPtr>()->operator[]("connectionName").toString() : QVariant(nil).toString();args.removeByKey("connectionName");
PVariant connectionParams = source_args.value<PVariantMapPtr>()->include("connectionParams") ? source_args.value<PVariantMapPtr>()->operator[]("connectionParams") : nil;args.removeByKey("connectionParams");
PVariant domain = source_args.value<PVariantMapPtr>()->include("domain") ? source_args.value<PVariantMapPtr>()->operator[]("domain") : PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));args.removeByKey("domain");


    if(connectionName.isNull())
        connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    QString className = toClassName(modelName);
    PLog().info() << PString(QString("PModel::$newModel: %1 - connectionName: %2").arg(className).arg(connectionName));

    PModel* m = PModules::     newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("connectionName", connectionName)->append("domain", domain)))));

    return PModelPtr(m);

}

PModelPtr PModel   ::model(QString modelName, QString connectionName, PVariant connectionParams, PVariant domain) {

    return PModel   ::       newModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("connectionName", connectionName)->append("connectionParams", connectionParams)->append("domain", domain)))));

}

PModelPtr PModel   ::manyToOne(QString modelName, QString referenceFieldName, QString type) {

    QString modelPtr = this->modelPtr(referenceFieldName);

    
    if(getTableCursor().include(modelPtr) and getTableCursor()[modelPtr].typeName() == "PModelPtr") {
        visited << getTableCursor()[modelPtr].toModelPtr().model; 
        return getTableCursor()[modelPtr].toModelPtr();
    }

    
    if(this->source && modelName == source->modelName && referenceFieldName == this->sourceFieldName) {
        PLog() << PString(QString("PModel::manyToOne: parent model %1 ... ok").arg(modelName));
        return source;
    }

    PVariant id = this->fieldValue(referenceFieldName);
    if(id.toInt() == 0 || id == nil || id.toString() == "NULL") 
        return PModelPtr();

    PModelPtr model = newPModel(modelName, type);

    getTableCursor()[modelPtr] = model.toVariant();

    if(visited.indexOf(model.model) == -1)
        visited << model.model;

    PLog().debug() << PString(QString("PModel::manyToOne: modelName: %1 referenceFieldName: %2").arg(modelName).arg(referenceFieldName));

    

    
    

    model->undefined("findBy_id", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(id)))));

    

    return model;

}




PModelPtr PModel   ::oneToMany(QString fieldName, QString modelName, QString referenceFieldName, bool automaticReference) {

    if(undefined("id", nil).toString() == "")
        return PModelPtr();

    if(getTableCursor() != nil && getTableCursor().include(fieldName) && getTableCursor()[fieldName] != nil) {
            visited << getTableCursor()[fieldName].toModelPtr().model; 
            return getTableCursor()[fieldName].toModelPtr();
    }

    PVariant domain = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( referenceFieldName, nil))));

    QString _id = undefined("id", nil).toString();

    if(_id[0] != '$')
        domain[referenceFieldName] = undefined("id", nil).toString();

    if(automaticReference)
        domain += this->domain;  

    PModelPtr model = newPModel(modelName, "oneToMany", domain);
    model->level = this->level + 1;
    model->sourceFieldName = referenceFieldName;

    
    
    model->findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

    getTableCursor()[fieldName] = model.toVariant();


    if(visited.indexOf(model.model) == -1)
        visited << model.model;

    return model;

}



PVariant PModel   ::sqlQueryByFieldName(PString fieldName) {

    if(fieldName.include(",") and !fieldName.include("date_part")) { 
        PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
        PVariant fields = fieldName.split(",");
         fields.forEachQString([&] (QString field_name) mutable {
          result << sqlQueryByFieldName(field_name.simplified());
        });
        return result;

    }


    PVariant fieldNameAs = fieldName.split(" as ");

    fieldName = fieldNameAs.undefined("0", nil).toString();
    QString as = (fieldNameAs.count() > 1) ? fieldNameAs.undefined("1", nil).toString() : "";

    if(!as.isEmpty()) as = PString(QString(" as %1").arg(as));

    PVariant models = fieldName.split(".");

    QString subModelName;
    if(fieldName.include("."))
        subModelName = fieldAttr(models.undefined("0", nil).toString()).undefined("modelNameReference", nil).toString();

    if(!fieldName.include(".") or subModelName.isEmpty())
        return PString(QString("%1%2").arg(fieldName).arg(as));

    fieldName = models.value<PVariantListPtr>()->mid(1, -1).join(".");

    PModelPtr subOdb = PModules:: newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)))));

    return PString(QString("(select %1 from %2 where %3 = id)%4").arg(subOdb->sqlQueryByFieldName(fieldName).toString()).arg(subModelName).arg(models.undefined("0", nil).toString()).arg(as));

}


QString PModel   :: fieldNameIdToSql(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "fieldNameIdToSql:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString fieldName = source_args.value<PVariantMapPtr>()->include("fieldName") ? source_args.value<PVariantMapPtr>()->operator[]("fieldName").toString() : QVariant(nil).toString();args.removeByKey("fieldName");
QString op = source_args.value<PVariantMapPtr>()->include("op") ? source_args.value<PVariantMapPtr>()->operator[]("op").toString() : QVariant(QString("=")).toString();args.removeByKey("op");
PVariant fieldValue = source_args.value<PVariantMapPtr>()->include("fieldValue") ? source_args.value<PVariantMapPtr>()->operator[]("fieldValue") : nil;args.removeByKey("fieldValue");
bool quoteValue = source_args.value<PVariantMapPtr>()->include("quoteValue") ? source_args.value<PVariantMapPtr>()->operator[]("quoteValue").toBool() : QVariant(true).toBool();args.removeByKey("quoteValue");
PVariant model = source_args.value<PVariantMapPtr>()->include("model") ? source_args.value<PVariantMapPtr>()->operator[]("model") : nil;args.removeByKey("model");


    PVariant models = PString(fieldName).split(".");
    QString fieldNameId;
    QString subModelName;

    if(models.count() > 1) {
        fieldNameId = models[0].toString(); 
        subModelName = this->fieldAttr(fieldNameId).undefined("modelNameReference", nil).toString(); 
    }
    else {
        if(quoteValue) fieldValue = PSql::quoteValue(fieldValue);

        QStringList models = fieldName.split(".");
        if(fieldValue.typeName() == "Array")
            return psql->       opOnArrayToSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("op", op)->append("array", fieldValue)->append("model", model)))));

        return PString(QString("%1 %2 %3").arg(fieldName).arg(op).arg(fieldValue.toString()));

    }

    fieldName = models.mid(1).join(".");
    QString subModelSql =          fieldNameIdToSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("fieldValue", fieldValue)->append("op", op)->append("quoteValue", quoteValue)->append("model", model)))));
    return PString(QString("%1 in (select id from %2 where %3)").arg(fieldNameId).arg(subModelName).arg(subModelSql));

}

PModelPtr PModel   ::find(PVariant sql) {

    return  findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", sql)))));

}

PModelPtr PModel   :: findBy(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "findBy:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant select = source_args.value<PVariantMapPtr>()->include("select") ? source_args.value<PVariantMapPtr>()->operator[]("select") : PString(QString("%1.*").arg(modelName));args.removeByKey("select");
PVariant sql = source_args.value<PVariantMapPtr>()->include("sql") ? source_args.value<PVariantMapPtr>()->operator[]("sql") : nil;args.removeByKey("sql");
PVariant orderBy = source_args.value<PVariantMapPtr>()->include("orderBy") ? source_args.value<PVariantMapPtr>()->operator[]("orderBy") : sortField;args.removeByKey("orderBy");
QString pageSize = source_args.value<PVariantMapPtr>()->include("pageSize") ? source_args.value<PVariantMapPtr>()->operator[]("pageSize").toString() : QVariant(QString("all")).toString();args.removeByKey("pageSize");
int page = source_args.value<PVariantMapPtr>()->include("page") ? source_args.value<PVariantMapPtr>()->operator[]("page").toInt() : QVariant(0).toInt();args.removeByKey("page");
QString op = source_args.value<PVariantMapPtr>()->include("op") ? source_args.value<PVariantMapPtr>()->operator[]("op").toString() : QVariant(QString("auto")).toString();args.removeByKey("op");


    psql->select(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(select)))))->from(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(modelName)))))->where(sql, op, QVariant::fromValue(this));
    psql->where(domain);
    psql->orderBy(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(orderBy)))));

    psql->   execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("pageSize", pageSize)->append("page", page)))));

    tableFields = psql->fieldNameList().fromListToMap();

    this->next();

    return this->toRecordPtr("manyToOne");

}

void PModel   ::findBy() {

    this->findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

}

PModelPtr PModel   ::all() {

    return this->findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

}

bool PModel   ::include(PVariant record) {PVariant _keys_0_ = record.keys();
for(int _i_0_ = 0; _i_0_ < _keys_0_.count(); _i_0_++) {
PString fieldName = _keys_0_[_i_0_].toString();
PVariant fieldValue = record.operator[](fieldName);
        if(fieldName[0] == fieldName[-1] && fieldName[-1] == '_') continue;
        if(this->fieldAttr(fieldName).undefined("type", nil).toString() == "virtual") continue;
        if(this->fieldAttr(fieldName).undefined("type", nil).toString() == "widget") continue;
        if(fieldValue.typeName() == "Array") {
            if(!fieldValue.include(this->fieldValue(fieldName).toString())) return false;
        }
        else
            if(this->fieldValue(fieldName).toString() != fieldValue.toString()) return false;

    }

    return true;

}


PVariant PModel   ::findByOffLine(PVariant record) {

    PVariant ptrRecords = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

     this->forEachPVariant([&] (PVariant rec) mutable {
        if(this->include(record))
            ptrRecords << QVariant::fromValue(this->toRecordPtr("manyToOne"));
    });

    return ptrRecords;

}


PVariant PModel   ::defaultVariantValue(const QString& fieldType) {

    if(fieldType == "text")
        return "";
    else if(fieldType == "bool")
        return psql->db_false();
    else if(fieldType == "float")
        return 0.0;
    else if(fieldType == "integer")
        return 0;
    else if(fieldType == "time") {
        QVariant time = QTime::currentTime();
        return time;
    }
    else if(fieldType == "date") {
        QVariant date = QDate::currentDate();
        return date;
    }
    else if(fieldType == "datetime") {
        QVariant dateTime = QDateTime::currentDateTime();
        return dateTime;
    }

    return nil;

}


PVariant PModel   ::defaultValue(const QString& fieldName) {

    if(fieldName == "ordering")
        return psql->orderingDefaultValue();

    PVariant field = pFields[fieldName];
    if(field == nil)
        return nil;

    if(pFields[fieldName].undefined("type", nil).toString() == "virtual")
        return fieldValue(fieldName);

    PVariant defaultValue = field["default"];

    if(!defaultValue.isNull())
        return defaultValue;

    PVariant result = this->defaultVariantValue(field.undefined("type", nil).toString());

    return (result == nil) ? defaultValue : result;

}




PVariant PModel   ::defaultRecord(PVariant record) {

    PVariant dr = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    getTableFields();
    
    
    PVariant fields = pFields + tableFields;
       fields.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        dr[fieldName] = defaultValue(fieldName);
    });

    
    dr["id"] = PString(QString("$%1_id$").arg(this->vid++));

       record.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        if(dr.include(fieldName))
            dr[fieldName] = fieldValue;
    });

    return dr;

}


PModelPtr PModel   ::create(PVariant record) {

    if(this->psql->table == nil)
        this->psql->table = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    PVariant dr = defaultRecord(record);
    dr += domain;
    toWrite << dr;
    this->psql->table << dr;
    this->last();
    this->onCreate();

    return toRecordPtr("parent");

}


PModel* PModel   ::createOnDb(PVariant record) {

    this->create(record);
    this->writeRecord(record);

    return this;

}



PModel* PModel   ::writeRecord(PVariant values) {

    PVariant tableCursor = this->getTableCursor();

    
    if(!this->toWrite.include(tableCursor ))
        return this;

    if(values == nil)
        return this;


       tableCursor.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        if(tableCursor [fieldName] == nil)
            tableCursor.removeByKey(fieldName);
    });



    tableCursor += values;

    
    

       tableCursor.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        if(fieldValue.typeName() == "PModelPtr") {
            PModelPtr m = fieldValue.toModelPtr();
            if(m->type == "manyToOne" || m->type == "oneToOne")
                     psql->tableCursor[fieldName] = m->writeRecord()->undefined("id", nil);
        }
    });

    tableCursor["id"] =  PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).insert(modelName, tableCursor & tableFields);

       tableCursor.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        if(fieldValue.toModelPtr().model) {
            PModelPtr m = fieldValue.toModelPtr();
            if(m->type == "oneToMany" || m->type == "manyToMany" || m->type == "rightTable") {
                QString referenceFieldName = m->domain.keys()[0].toString();
                PVariant _domain = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( referenceFieldName,    psql->tableCursor["id"]))));
                m->writeAllRecords(_domain);
                m->domain += _domain;
            }
        }
    });

    toWrite.removeByValue(getTableCursor());

    return this;

}



PModel* PModel   ::writeAllRecords(PVariant values) {

    

    PVariant toDeleteCopy = toDelete.dup();
     toDeleteCopy.forEachPVariant([&] (PVariant record) mutable {
        QString id = record.undefined("id", nil).toString();
        this->  removeOnDB(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("where", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", id)))))))));
    });

    PVariant toWriteCopy = toWrite.dup();
     toWriteCopy.forEachPVariant([&] (PVariant record) mutable {
        
         setTableCursorBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", 
        
         record["id"])))));
        writeRecord(values);
    });

    return this;

}

PModel* PModel   ::save(PVariant values, PVariant record) {

    if(record == nil)
        record = getTableCursor();

    if (record.typeName() == "PModelPtr") {
        PModelPtr recordPtr = record.value<PModelPtr>();
        this->setTableCursor(recordPtr.tableCursor);
        this->setRecord(values);
    }
    else if(record.toModelPtr().model)
        this->save(values, record.toModelPtr()->getTableCursor());
    else if(record.typeName() == "Hash") {
        PVariant result = findByOffLine(record);
         result.forEachPVariant([&] (PVariant toRecordPtr) mutable { this->save(values, toRecordPtr); });
    }
    else if(record.typeName() == "Array")
         record.forEachPVariant([&] (PVariant rec) mutable { this->save(values, rec); });

    return this;

}



PModel* PModel   ::saveRecord(PVariant values) {

    PLog().debug() << PString(QString("PModel::saveRecord(%1) - %2").arg(values.toString()).arg(modelName));
    if(values.any()) getTableCursor() += values;

    

       psql->tableCursor.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        if(fieldValue.typeName() == "PModelPtr" or fieldValue.toModelPtr().model) { 
            QString t = fieldValue.toModelPtr()->type;
            if(t == "manyToOne" or t == "oneToOne") {
                PLog().debug() << PString(QString("PModel::saveRecord.saveAllRecords: %1 - #{fieldValue.domain}").arg(fieldName));
                if(!this->isModelPtr(fieldName)) 
                    getTableCursor()[fieldName] = fieldValue.toModelPtr()->saveAllRecords()->undefined("id", nil);
            }
        }
    });

    
     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).update(modelName, getTableCursor() & tableFields, PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id",   psql->tableCursor["id"])))));

       psql->tableCursor.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable { 
        if(fieldValue.typeName() == "PModelPtr" or fieldValue.toModelPtr().model) {
            QString t = fieldValue.toModelPtr()->type;
            if(t == "oneToMany" || t == "manyToMany" || t == "rightTable") {
                PLog().debug() << PString(QString("PModel::saveRecord.saveAllRecords: %1 - %2").arg(fieldName).arg(fieldValue.toString()));
                fieldValue.toModelPtr()->saveAllRecords();
            }
        }

    });

    toChange.removeByValue(getTableCursor());
    return this;

}



PModel* PModel   ::saveAllRecords(PVariant values) {

    PLog().debug() << PString(QString("PModel::saveAllRecords(%1) - %2").arg(values.toString()).arg(modelName));

    PVariant toChangeCopy = toChange.dup();
     toChangeCopy.forEachPVariant([&] (PVariant record) mutable {
         setTableCursorBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", 
         record["id"])))));
        saveRecord(values);
    });

    return this;

}



PModel* PModel   :: saveOnDB(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "saveOnDB:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant set = source_args.value<PVariantMapPtr>()->include("set") ? source_args.value<PVariantMapPtr>()->operator[]("set") : PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));args.removeByKey("set");
PVariant where = source_args.value<PVariantMapPtr>()->include("where") ? source_args.value<PVariantMapPtr>()->operator[]("where") : nil;args.removeByKey("where");


  args += set;
  if(where != nil)
      this->find(where);

  PVariant ptrRecord = findByOffLine();
  this->save(ptrRecord, args);

  return this->saveAllRecords();

}


bool PModel   :: _deleteOnDB(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "_deleteOnDB:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant ids = source_args.value<PVariantMapPtr>()->include("ids") ? source_args.value<PVariantMapPtr>()->operator[]("ids") : nil;args.removeByKey("ids");
PVariant references = source_args.value<PVariantMapPtr>()->include("references") ? source_args.value<PVariantMapPtr>()->operator[]("references") : nil;args.removeByKey("references");
bool check = source_args.value<PVariantMapPtr>()->include("check") ? source_args.value<PVariantMapPtr>()->operator[]("check").toBool() : QVariant(false).toBool();args.removeByKey("check");


    PVariant ref = references[modelName];
    if(references[modelName].toBool())for(int _i_1_ = 0; _i_1_ < ref.count(); _i_1_++) {
PVariant reference = ref.operator[](_i_1_);
        QString tableName = reference["tableName"].toString();
        QString referenceFieldName = reference["fieldName"].toString();
        PVariant values = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( referenceFieldName, nil))));
        PVariant where = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( referenceFieldName, ids))));

        if(reference["onDelete"].toString().toUpper() == "SET NULL") {
            if(!check) {
                 PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).update(tableName, values, where);
            }
            continue;
        }
        PModelPtr subTable = PModules:: 
                                                 
                                                 newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("connectionName", connectionName)->append("connectionParams", connectionParams)))));
        subTable->find(where);
        if(subTable->count() == 0) continue;

        if(reference["onDelete"].toString().toUpper() == "CASCADE") {
            where["check"] = check;
            if(!subTable->deleteOnDB(where))
                return false;
        }
        else 
          pDebug() << PString(QString("DELETE on table %1 violates foreign key constraint on table %2").arg(modelName).arg(tableName));
          pDebug() << PString(QString("ids: %1 are still referenced from table %2").arg(ids.toString()).arg(tableName));
          return false;
    }


    return true;

}




void PModel   ::onReloadView() {

}


void PModel   ::onCreate() {

}

void PModel   ::onSave() {
}

void PModel   ::onRemove(PVariant record) {
}



void PModel   ::onNewBeforeWidget() {
}

void PModel   ::onNewAfterWidget() {
}


void PModel   ::onEditBeforeWidget() {
}

void PModel   ::onEditAfterWidget() {
}

void PModel   ::onBeforeWidget() {

}

void PModel   ::onAfterWidget() {

}



void PModel   ::onAfterTable() {

}



bool PModel   ::onWrite() {

    if(this->dialogMode)
        return false;

    return true;

}


void PModel   ::onDelete(PVariant ids) {
}




bool PModel   ::onOkDialog() {

    return true;

}



void PModel   ::onAfterOkDialog() {

}



bool PModel   ::onCancelDialog() {

    return true;

}

PModel* PModel   ::setRecord(PVariant values) {

    PVariant tableCursor = getTableCursor();

    if(values.isEmpty())
        return this;

    pDebug() << "PModel::setRecord";

    if(!toChange.include(tableCursor)) toChange << tableCursor;

       values.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        if(!tableFields.include(fieldName))
            pDebug() << PString(QString("PModel::setRecord: %1 not found").arg(fieldName)), "ERROR";
        else
            this->setFieldValue(fieldName, fieldValue);
    });
    this->onSave();

    return this;

}



bool PModel   :: deleteOnDB(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "deleteOnDB:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant where = source_args.value<PVariantMapPtr>()->include("where") ? source_args.value<PVariantMapPtr>()->operator[]("where") : nil;args.removeByKey("where");
PVariant hash = source_args.value<PVariantMapPtr>()->include("hash") ? source_args.value<PVariantMapPtr>()->operator[]("hash") : nil;args.removeByKey("hash");
bool check = source_args.value<PVariantMapPtr>()->include("check") ? source_args.value<PVariantMapPtr>()->operator[]("check").toBool() : QVariant(false).toBool();args.removeByKey("check");


    if(hash != nil) where << hash;

    PModelPtr model = PModules:: 
                                             
                                             newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("connectionName", connectionName)->append("connectionParams", connectionParams)))));

    model-> findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", where)))));

    if(model->count() == 0) {
        
        return true;
    }

    PVariant ids = model->psql->column("id");


    PConfiguration config(PString(QString("%1/references.json").arg(PGlobal::jsonDbPath())));

    PVariant references = config.cfg();

    pDebug() << PString(QString("PModel::$eraseOnDb: %1 - %2").arg(modelName).arg(references[modelName].toString()));

    bool result = this->     _deleteOnDB(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("ids", ids)->append("references", references)->append("check", true)))));

    if(check || result == false) {
        
        return result;
    }

    this->   _deleteOnDB(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("ids", ids)->append("references", references)))));

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).erase(modelName, PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", ids)))));

    return true;

}


PModel* PModel   ::_removeRecord(PVariant record) {

    if(record == nil)
        record = this->getTableCursor();

  
  
    this->onRemove(record);
    QString _id = record["id"].toString();
    if(_id.startsWith("$")) {
        toWrite.removeByValue(record);
        toChange.removeByValue(record);
    }
    else
        toDelete << record;

    psql->table.removeByValue(record);

    return this;

}



PModelPtr PModel   :: removeOnDB(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "removeOnDB:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant where = source_args.value<PVariantMapPtr>()->include("where") ? source_args.value<PVariantMapPtr>()->operator[]("where") : nil;args.removeByKey("where");
PVariant hash = source_args.value<PVariantMapPtr>()->include("hash") ? source_args.value<PVariantMapPtr>()->operator[]("hash") : nil;args.removeByKey("hash");


    if(psql->table == nil)
        this->findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));


    if(hash.include("id")) hash[modelName + ".id"] = hash.removeByKey("id");
    if(hash != nil) where << hash;
    pDebug() << PString(QString("PModel::findBy: %1").arg(where.toString()));

    PSql  tmp_db(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName)))));
    tmp_db.  select(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(modelName+".*")))))->from(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(modelName)))))->where(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(where)))));

    tmp_db.execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

    if(tmp_db.count() == 0) {
      
      return this;
    }

    PVariant ids = tmp_db.column("id");

    
    if(false) { 
      psql->pushState();
      this->deleteOnDB(where);
      psql->popState();
    }
    else
         PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", connectionName))))).erase(modelName, PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", ids)))));for(int _i_2_ = 0; _i_2_ < ids.count(); _i_2_++) {
QString id = ids.operator[](_i_2_).toString();for(int i = 0; i < psql->table.count(); i++) {
PVariant record = psql->table.operator[](i);
            if(record["id"] == id) {
                psql->table.removeByIndex(i);
                break;
            }
        }for(int i = 0; i < toDelete.count(); i++) {
PVariant record = toDelete.operator[](i);
            if(record["id"] == id) {
                toDelete.removeByIndex(i);
                break;
            }
        }for(int i = 0; i < toChange.count(); i++) {
PVariant record = toChange.operator[](i);
            if(record["id"] == id) {
                toChange.removeByIndex(i);
                break;
            }
        }

    }

    return this->toRecordPtr("manyToOne");

}










PModel* PModel   ::remove(PVariant record) {

    if(record == nil) record = getTableCursor();

    if(record.typeName() == "PModelPtr") {
        PModelPtr recordPtr = record.value<PModelPtr>();
        this->_removeRecord(recordPtr.tableCursor);
    }
    else if(record.toModelPtr().model)
        this->_removeRecord(record.toModelPtr()->getTableCursor());
    else if(record.typeName() == "Hash") {
        PVariant result = findByOffLine(record);
         result.forEachPVariant([&] (PVariant recordPtr) mutable { this->remove(recordPtr); });
    }
    else if(record.typeName() == "Array")
         record.forEachPVariant([&] (PVariant recordPtr) mutable { this->remove(recordPtr); });
    else if(record == "all") {
        PVariant tr = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())))); 
         this->forEachPVariant([&] (PVariant rec) mutable { tr << rec.undefined("id", nil).toString(); });
        this-> remove(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", tr)))));
    }

    return this;

}








void PModel   ::apply() {

    PLog().debug() << PString(QString("PModel::apply - %1").arg(modelName));
    this->writeAllRecords();
    for(int i = 0; i < visited.count(); i++) {
        PModel* model = visited[i];
        PLog().debug() << PString(QString("PModel::apply - %1 -> PModel::apply - %2").arg(modelName).arg(model->modelName));
        model->apply();
    }
    this->saveAllRecords();
    visited.clear();


}


PVariant PModel   ::action(PVariant action) {

    PLog().debug() << "PModel::action " << action.toString();

    return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("message_box"))->append("result", QString("")))));

}



PVariant PModel   ::fieldAttr(PString fieldName) {

    if(fieldName.include("."))  
        fieldName = fieldName.split(".")[0].toString();

    if(!pFields.include(fieldName) or pFields[fieldName] == nil) 
        return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("text")))));

    return pFields[fieldName].dup(); 

}

PVariant PModel   ::fieldValue(PString fieldName) {

    if(fieldName.include(".")) { 
        PVariant fields = fieldName.split(".");
        PModelPtr modelPtr = undefined(fields[0].toString(), nil).value<PModelPtr>();
        if(modelPtr != nil) return modelPtr->fieldValue(fields.mid(1).join("."));
        return nil;
    }

    if(this->getTableCursor() == nil) return nil;

    if(this->cacheMode and this->cacheValues.include(fieldName))
        return this->cacheValues[fieldName];

    PVariant value = this->getTableCursor()[fieldName];

    PVariant attr = fieldAttr(fieldName);

    QString fieldType = attr["type"].toString();

    if(fieldType == "virtual" && attr.include("functionName")) {
        PVariant result;
        QMetaObject::invokeMethod(this, fieldName.toUtf8(), Qt::DirectConnection, Q_RETURN_ARG(PVariant, result));
        return result;
    }

    
    
    
    
    if(attr.include("virtual") and attr["virtual"].toBool()) {
        PVariant result;
        QMetaObject::invokeMethod(this, fieldName.toUtf8(), Qt::DirectConnection, Q_RETURN_ARG(PVariant, result));
        this->getTableCursor()[fieldName] = result;
        this->saveRecord();
        return result;
    }

    if(fieldType == "virtual" && attr.include("function")) {

        QString functionType = attr["function_type"].toString();

        if(functionType == "PFunc") {
            PFunc func = attr.undefined("function", nil).value<PFunc>();
            return func();
        }

        if(functionType == "PFuncPVariant") {
            PFuncPVariant funcVariant = attr.undefined("function", nil).value<PFuncPVariant>();
            return funcVariant(this->getTableCursor());
        }

        if(functionType == "PFuncQStringPVariant") {
            PFuncQStringPVariant funcVariant = attr.undefined("function", nil).value<PFuncQStringPVariant>();
            return funcVariant(this->undefined("id", nil).toString(), this->getTableCursor());
        }

    }

    return value;

}









void PModel   ::resetIfModelNameReference(QString fieldName) {

    QString modelPtr = this->modelPtr(fieldName);
    if(fieldAttr(fieldName).include("modelNameReference"))
        getTableCursor().removeByKey(modelPtr);

}



bool PModel   ::setFieldValue(QString fieldName, PVariant fieldValue) {

    

    if(this->cacheMode) {
      this->cacheValues[fieldName] = fieldValue;
      this->lastChangedFields[fieldName] = fieldValue;
      this->resetIfModelNameReference(fieldName);
      this->reloadFieldWidget(fieldName);
      return true;
    }


    if(this->getTableCursor() == nil)
        this->first();
    if(this->getTableCursor() == nil)
        return false;

    if(psql->fieldNameList().include(fieldName)) {
        getTableCursor()[fieldName] = fieldValue;
        if(!this->toChange.include(getTableCursor())) {
            this->toChange << getTableCursor();
        }

        this->resetIfModelNameReference(fieldName);
        this->reloadFieldWidget(fieldName);
        return true;
    }

    return false;

}


PVariant PModel   ::getTableFields() {

    if(this->tableFields != nil)
        return this->tableFields;

    
    this-> findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", QString("1 = 0"))))));
    

    return tableFields;

}

PVariant PModel   ::systemFields() {

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));PVariant _keys_6_ = pFields.keys();
for(int _i_6_ = 0; _i_6_ < _keys_6_.count(); _i_6_++) {
PString fieldName = _keys_6_[_i_6_].toString();
PVariant field = pFields.operator[](fieldName);
        if(field. undefined("system", nil)!= nil)
            result[fieldName] = field;
    }

    return result;
}


PVariant PModel   ::operator[](int row) {

    if(row >= this->count()) {
        PLog().debug() << PString(QString("PModel::operator[%1]: limit overbound").arg(row));
        return nil;
    }

    if(this->psql->table == nil)
        findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

    if(this->getTableCursor() == nil) {
        resetCursor();
        next();
    }

    psql->setTableCursor(row);

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));PVariant _keys_7_ = pFields.keys();
for(int _i_7_ = 0; _i_7_ < _keys_7_.count(); _i_7_++) {
PString fieldName = _keys_7_[_i_7_].toString();
QString fieldAttrs = pFields.operator[](fieldName).toString();
        result[fieldName] = fieldValue(fieldName);
    }

    return result;

}

PVariant PModel   ::operator()(int row) {

    if(row >= this->count()) {
        PLog().debug() << PString(QString("PModel::operator(%1): limit overbound").arg(row));
        return nil;
    }

    if(this->psql->table == nil)
        findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

    if(this->getTableCursor() == nil) {
        resetCursor();
        next();
    }

    return this->psql->record(row);

}

PVariant PModel   ::operator[](QString fieldName) {

    return this->fieldValue(fieldName);

}

int PModel   ::count() {

    return this->psql->table.count();

}

PVariant PModel   ::keys() {

    return pFields.keys();

}

PModel* PModel   ::setTableCursor(PVariant tableCursor) {

    if(tableCursor == nil) {
        tableCursor = getTableCursor();
        resetCursor();
        return this;
    }

    int index = psql->table.indexOf(tableCursor);

    if(index == -1) {
        resetCursor();
        return this;
    }

    psql->setTableCursor(index);

    return this;

}


PModel* PModel   ::setTableCursorBy(PVariant values) {

    resetCursor();
    while(this->next() != nil)
        if(this->include(values))
                return this;

    PLog().error() << PString(QString("PModel::setTableCursorBy(%1): Impossibile impostare il cursore").arg(values.toString()));
    return this;

}


void PModel   ::resetCursor() {

    this->psql->resetCursor();

}

PVariant PModel   ::current() {

    return this->getTableCursor();

}

PVariant PModel   ::first() {

    this->psql->first();
    return this->getTableCursor();

}

PVariant PModel   ::last() {

    this->psql->last();
    return this->getTableCursor();

}

PVariant PModel   ::prev() {

    this->psql->prev();
    return this->getTableCursor();

}

PVariant PModel   ::next() {

    this->psql->next();
    return this->getTableCursor();

}






PModelPtr PModel   ::dup() {

    PVariant fields = pFields.keys();

    PModelPtr currentRecord = this->toRecordPtr();

    PModelPtr newRecord = PModel   ::model(modelName);
    newRecord->setParent(this);
    newRecord = newRecord->create();

     fields.forEachQString([&] (QString fieldName) mutable {
        PVariant attrs = fieldAttr(fieldName);
        QString modelNameReference = attrs.undefined("modelNameReference", nil).toString();
        if(fieldName == "id")
            newRecord->setFieldValue("id", "$default");
        
        else if(attrs.undefined("type", nil).toString() == "manyToOne" and attrs. undefined("dup", nil)!= nil and attrs.undefined("dup", nil).toBool() == true) {
            PModelPtr subModelSource = currentRecord->manyToOne(modelNameReference, fieldName);
            if(subModelSource != nil) {
                PModelPtr subModelDest = PModel   ::model(modelNameReference);
                subModelDest->setParent(this);
                subModelDest->createOnDb(subModelSource->dup()->getTableCursor());
                newRecord->setFieldValue(fieldName, subModelDest->undefined("id", nil).toString());
            }
        }
        else if(attrs.undefined("type", nil).toString() != "oneToMany") { 
            
            newRecord->setFieldValue(fieldName, currentRecord->fieldValue(fieldName));
        }
        else if(attrs. undefined("dup", nil) ==  nil or attrs.undefined("dup", nil).toBool() == true) { 
            PModelPtr subModelSource = currentRecord->oneToMany(fieldName, modelNameReference, attrs.undefined("referenceFieldName", nil).toString());
            PModelPtr subModelDest = newRecord->oneToMany(fieldName, modelNameReference, attrs.undefined("referenceFieldName", nil).toString());
             subModelSource->forEachPModelPtr([&] (PModelPtr record) mutable {
                subModelDest->create(record->dup()->getTableCursor());
            });
        }
    });

    return newRecord;

}







PModelPtr PModel   ::copy(const QString& suffixModelName) {

    QString destModelName = PString(QString("%1_%2").arg(this->modelName).arg(suffixModelName));

    PVariant fields = pFields.keys();

    PModelPtr currentRecord = this->toRecordPtr();

    PModelPtr newRecord = PModel   ::model(destModelName);
    newRecord->setParent(this);
    newRecord = newRecord->create();

     fields.forEachQString([&] (QString fieldName) mutable {
        PVariant attrs = fieldAttr(fieldName);
        QString modelNameReference = attrs.undefined("modelNameReference", nil).toString();
        if(fieldName == "id")
            newRecord->setFieldValue("id", "$default");
        
        else if(attrs.undefined("type", nil).toString() == "manyToOne" and attrs. undefined("dup", nil)!= nil and attrs.undefined("dup", nil).toBool() == true) {
            PModelPtr subModelSource = currentRecord->manyToOne(modelNameReference, fieldName);
            if(subModelSource != nil) {
                PModelPtr subModelDest = PModel   ::model(modelNameReference);
                subModelDest->setParent(this);
                subModelDest->createOnDb(subModelSource->dup()->getTableCursor());
                newRecord->setFieldValue(fieldName, subModelDest->undefined("id", nil).toString());
            }
        }
        else if(attrs.undefined("type", nil).toString() != "oneToMany") { 
            
            newRecord->setFieldValue(fieldName, currentRecord->fieldValue(fieldName));
        }
        else if(attrs. undefined("dup", nil) ==  nil or attrs.undefined("dup", nil).toBool() == true) { 
            QString destFieldName = fieldName;

            if(fieldName == PString(QString("%1_table").arg(modelNameReference)))
                destFieldName = PString(QString("%1_%2_table").arg(modelNameReference).arg(suffixModelName));

            PVariant destAttrs = newRecord->fieldAttr(destFieldName);

            PModelPtr subModelSource = currentRecord->oneToMany(fieldName, modelNameReference, attrs.undefined("referenceFieldName", nil).toString());
            PModelPtr subModelDest = newRecord->oneToMany(destFieldName, destAttrs.undefined("modelNameReference", nil).toString(), destAttrs.undefined("referenceFieldName", nil).toString());

             subModelSource->forEachPModelPtr([&] (PModelPtr record) mutable {
                subModelDest->create(record->dup()->getTableCursor());
            });
        }
    });

    return newRecord;

}



int PModel   ::columnWidth(QString fieldName) {

    if(colWidth(fieldName) != nil)
        return colWidth[fieldName].toUInt();

    PVariant vals = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append( fieldName.length()))));

     this->forEachPVariant([&] (PVariant rec) mutable { vals << fieldValue(fieldName).toString().length(); });

    colWidth[fieldName] = vals.max();

    return colWidth[fieldName].toInt();


}


void PModel   :: showValue(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "showValue:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString fieldName = source_args.value<PVariantMapPtr>()->include("fieldName") ? source_args.value<PVariantMapPtr>()->operator[]("fieldName").toString() : QVariant(nil).toString();args.removeByKey("fieldName");
QString fieldValue = source_args.value<PVariantMapPtr>()->include("fieldValue") ? source_args.value<PVariantMapPtr>()->operator[]("fieldValue").toString() : QVariant(nil).toString();args.removeByKey("fieldValue");
QString color = source_args.value<PVariantMapPtr>()->include("color") ? source_args.value<PVariantMapPtr>()->operator[]("color").toString() : QVariant(nil).toString();args.removeByKey("color");
QString separator = source_args.value<PVariantMapPtr>()->include("separator") ? source_args.value<PVariantMapPtr>()->operator[]("separator").toString() : QVariant(QString("|")).toString();args.removeByKey("separator");
QString justify = source_args.value<PVariantMapPtr>()->include("justify") ? source_args.value<PVariantMapPtr>()->operator[]("justify").toString() : QVariant(QString("left")).toString();args.removeByKey("justify");
QString std_out = source_args.value<PVariantMapPtr>()->include("std_out") ? source_args.value<PVariantMapPtr>()->operator[]("std_out").toString() : QVariant(QString("window")).toString();args.removeByKey("std_out");


    
    if(fieldValue.isNull())
      fieldValue = "NULL";

    int cw = columnWidth(fieldName);
    PString value = QString("| %1").arg(PString::justify(fieldValue, cw,
                                    (fieldAttr(fieldName).type() == QVariant::Double) ? "right" : "left"
                                    ));
    if(!color.isNull())value = value.color(color);

  

    pDebug().noEndl() << value;


}

void PModel   :: showSeparator(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "showSeparator:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant fields = source_args.value<PVariantMapPtr>()->include("fields") ? source_args.value<PVariantMapPtr>()->operator[]("fields") : pFields;args.removeByKey("fields");
QString color = source_args.value<PVariantMapPtr>()->include("color") ? source_args.value<PVariantMapPtr>()->operator[]("color").toString() : QVariant(nil).toString();args.removeByKey("color");


     fields.forEachQString([&] (QString fieldName) mutable {
        PString separator = QString("+%1").arg("-", -(columnWidth(fieldName) + 2), '-');
        if(!color.isNull())separator = separator.color(color);
        pDebug("%s").noEndl() << separator;
    });
    pDebug() << "";

}


void PModel   :: show(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "show:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant fields = source_args.value<PVariantMapPtr>()->include("fields") ? source_args.value<PVariantMapPtr>()->operator[]("fields") :   pFields.keys();args.removeByKey("fields");
QString color = source_args.value<PVariantMapPtr>()->include("color") ? source_args.value<PVariantMapPtr>()->operator[]("color").toString() : QVariant(nil).toString();args.removeByKey("color");
QString justify = source_args.value<PVariantMapPtr>()->include("justify") ? source_args.value<PVariantMapPtr>()->operator[]("justify").toString() : QVariant(QString("center")).toString();args.removeByKey("justify");


    if(this->psql->table == nil)
        findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

       showSeparator(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fields", fields)->append("color", color)))));

     fields.forEachQString([&] (QString fieldName) mutable {
        PString str = PString::justify(fieldName, columnWidth(fieldName), "center");
        str = PString(QString("| %1").arg(str));
        if(!color.isNull())str = str.color(color);
        pDebug().noEndl() << str;
    });
    pDebug() << "";

       showSeparator(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fields", fields)->append("color", color)))));

     this->forEachPVariant([&] (PVariant row) mutable {
         fields.forEachQString([&] (QString fieldName) mutable {
                   showValue(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("fieldValue", 
               fieldValue(fieldName))->append("color", color)->append("justify", justify)))));
        });
        pDebug() << "";
    });

       showSeparator(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fields", fields)->append("color", color)))));

     PString rows = PString(QString("(%1 rows)").arg(this->count()));
     if(!color.isNull())rows = rows.color(color);

     pDebug() << rows;

}

void PModel   ::showBy(PVariant fields) {

     show(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fields", fields)))));

}





QString PModel   ::dump() {

    PString fileName = currentFileName();

    QString path = fileName.split("/").value<PVariantListPtr>()->mid2(1, -1).join("/");

    fileName = PString(QString("%1/default_data.yml").arg(path));

    PVariant recordList = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    PModelPtr m = PModel   ::model(modelName);
    m->findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
     m->forEachPVariant([&] (PVariant record) mutable {
        recordList << (record & this->getTableFields()).toString();
    });

    QString result = PString(QString("{%1:[\n%2\n]}").arg(modelName).arg(recordList.join(",\n")));

    PDir::fileWrite(fileName, result.toUtf8());

     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("high_cyan")))))).debug() << fileName << "written successfully !!!";

    return fileName;

}


QString PModel   :: exportCSV(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "exportCSV:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString fileName = source_args.value<PVariantMapPtr>()->include("fileName") ? source_args.value<PVariantMapPtr>()->operator[]("fileName").toString() : QVariant(nil).toString();args.removeByKey("fileName");
PVariant fields = source_args.value<PVariantMapPtr>()->include("fields") ? source_args.value<PVariantMapPtr>()->operator[]("fields") : nil;args.removeByKey("fields");
QString separator = source_args.value<PVariantMapPtr>()->include("separator") ? source_args.value<PVariantMapPtr>()->operator[]("separator").toString() : QVariant(QString(";")).toString();args.removeByKey("separator");


    if(fileName.isEmpty())
        fileName = PString(QString("%1.csv").arg(modelName));

    PVariant recordList = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    recordList << fields.toString(separator).fromTo(1, -1);

     this->forEachPVariant([&] (PVariant record) mutable {
        PVariant row = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
         fields.forEachQString([&] (QString fieldName) mutable {
            row << fieldValue(fieldName);
        });
        recordList << row.toString(separator).fromTo(1, -1);
    });

    QString result = recordList.join("\n");

    PDir::fileWrite(fileName, result.toUtf8());

     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("high_cyan")))))).debug() << fileName << "written successfully !!!";

    return fileName;

}


PVariant PModel   ::mainHandleRequest(PVariant request) {

    qDebug() << " - >" << request.toString();

    QString command = request.undefined("command", nil).toString();

    QString modelName = command.split(".")[0];

    request["command"] = command.split(".")[1];

    PModelPtr model = PModules:: newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)))));

    PVariant result = model->handleRequest(request);

    delete model.model;

    return result;

}


QString PModel   ::apiSpec() {QStringList lines;
lines << "";
lines << "";
lines << "# RUOLO";
lines << "Traduci le richieste vocali dell'utente in chiamate API JSON e rispondi in modo parlato.";
lines << "";
lines << "# FORMATO COMANDI API";
lines << "Genera oggetti JSON con sintassi: `{ 'command': '<MODELLO>.<AZIONE>', 'payload': { ... } }`";
lines << "";
lines << "### Modello ed Azioni";
lines << "- `<MODELLO>`: L'entità target in minuscolo (es. `contact`, `supplier`, `article`, `invoice`).";
lines << "- `<MODELLO>.find`: Ricerca standard con filtri nel payload.";
lines << "- `<MODELLO>.findByTableViewFields`: Ricerca avanzata per decodificare relazioni/chiavi esterne (es. nomi al posto di ID).";
lines << "- `<MODELLO>.create`: Inserimento di un nuovo record.";
lines << "- `<MODELLO>.update`: Aggiornamento di **tutti** i record che rispettano la condizione `{ 'where': {...}, 'values': {...} }`.";
lines << "- `<MODEL>.updateFirst`: Aggiornamento del **solo primo record** trovato (usa questo per modifiche a singoli elementi).";
lines << "- `<MODELLO>.delete`: Eliminazione di record con condizione `{ 'where': {...} }`.";
lines << "";
lines << "# REGOLE DI COMPORTAMENTO";
lines << "1. **Scelta Comando:** Usa sempre `updateFirst` per modifiche puntuali a un singolo elemento.";
lines << "2. **Stile Vocale:** Le tue risposte parlate devono essere brevissime (max 1-2 frasi), naturali e prive di gergo tecnico (non leggere mai JSON, ID o comandi).";
lines << "3. **Sicurezza:** Per le eliminazioni (`delete`), chiedi sempre prima conferma vocale all'utente.";
lines << "";
lines << "# CONVENZIONE NOMI CAMPI";
lines << "Utilizza **rigorosamente solo** i seguenti nomi di campo all'interno degli oggetti payload:";
lines << "";
lines << "";
return lines.join("\n");

}




PVariant PModel   ::findByTableViewFieldsCurrent(PVariant payload) {

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    

    PVariant tvf = this->tableViewFields();

     tvf.forEachPVariant([&] (PVariant field) mutable {
        PVariant attrs = this->fieldAttr(field.undefined("name", nil).toString());
        QString fieldValue = "";
        if(field != nil) {
            fieldValue = this->fieldValue(field.undefined("name", nil).toString()).toString();
            if(attrs.undefined("toTranslate", nil).toBool())
                fieldValue = PTranslator::tr(this->fieldValue(field.undefined("name", nil).toString()).toString());
            if(attrs.undefined("type", nil).toString() == "date") {
                QDate fieldValueDate =  this->fieldValue(field.undefined("name", nil).toString()).toDate();
                fieldValue = QLocale().toString(fieldValueDate, QLocale::ShortFormat);
            }
            result[field.undefined("name", nil).toString()] = fieldValue;
        }
    });

    return result;


}


PVariant PModel   :: handleRequest(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "handleRequest:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString command = source_args.value<PVariantMapPtr>()->include("command") ? source_args.value<PVariantMapPtr>()->operator[]("command").toString() : QVariant(nil).toString();args.removeByKey("command");
PVariant payload = source_args.value<PVariantMapPtr>()->include("payload") ? source_args.value<PVariantMapPtr>()->operator[]("payload") : nil;args.removeByKey("payload");


    qDebug() << "PModel::$handleRequest -> " << command << payload.toString();

    if(command == "create") {
        this->create(payload);
        this->writeRecord();
        
        return this->psql->tableCursor;
    }
    else if(command == "findFirst") {
        this->find(payload);

        if(this->count() == 0)
            return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("result", QString("empty")))));

        
        return this->psql->tableCursor;
    }

    else if(command == "find") {
        this->find(payload);

        if(this->count() == 0)
            return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("result", QString("empty")))));

        
        return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("result", this->psql->table))));
    }

    else if(command == "findByTableViewFieldsFirst") {

          this->find(payload);

          if(this->count() == 0)
              return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("result", QString("empty")))));

          return this->findByTableViewFieldsCurrent(payload);

    }

    else if(command == "findByTableViewFields") {

        PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

        this->find(payload);

        if(this->count() == 0)
            return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("result", QString("empty")))));

         this->forEachPVariant([&] (PVariant record) mutable {

            result << this->findByTableViewFieldsCurrent(payload);

        });

        return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("result", result))));

    }


    else if(command == "update") {

        this->find(payload.undefined("where", nil));

        if(this->count() == 0)
            return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("result", QString("nothing to update")))));

        PVariant ids = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
         this->forEachPVariant([&] (PVariant record) mutable {
            ids << this->undefined("id", nil);
            this->saveRecord(payload.undefined("values", nil));
        });

        return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("ids", ids))));

    }

    else if(command == "updateFirst") {

        this->find(payload.undefined("where", nil));

        if(this->count() == 0)
            return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("result", QString("nothing to update")))));

        this->saveRecord(payload.undefined("values", nil));
        return this->psql->tableCursor;

    }

    else if(command == "delete") {

        this->deleteOnDB(payload.undefined("where", nil));

    }

    else if(command == "call") {

        PMPbxPhoneNumber::   call(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("internal", payload. undefined("internal", nil))->append("phoneNumber", payload.   undefined("phoneNumber", nil))))));

    }

    else if(command == "api") {

        this-> find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("is_default", true)))));

        PModelPtr model = PModules:: newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName",  undefined("model_name", nil).toString())))));

        QString fields = model->pFields.keys().toString();

        QString description = PString(QString("%1 - %2: %3").arg(undefined("description", nil).toString()).arg(apiSpec()).arg(fields));

        return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("description", description))));

    }


    return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("available", true)->append("message", QString("Congratulation by PlusQode")))));

}
