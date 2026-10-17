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











   #include "sql/psql.h"









   








  






 
   #include "sql/pmodel.h"









   








  






 
   








  






 
  






 
 

QString PSql::defaultConnectionName = "plusqode_pgsql";


PVariant PSql::simplify(PVariant root) {

    PVariant elem;

    if(root.typeName() == "Hash") {
        elem = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
           root.forEachQString_PVariant([&] (QString key,PVariant value) mutable {
            if(value.typeName() == "Hash" or value.typeName() == "Array")
                elem[key] = simplify(value);
            else
                elem[key] = value;
        });
    }
    else if(root.typeName() == "Array") {
        elem = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
         root.forEachPVariant([&] (PVariant value) mutable {
            if(value.typeName() == "Hash" or value.typeName() == "Array")
                elem << simplify(value);
            else if(!value.toString().isEmpty())
                elem << value;
        });
    }

    return elem;

}


QString PSql::quoteValue(QVariant _value) {

  if (_value.isNull())
    return "NULL";

  if(QString(_value.typeName()) == "int")
      return _value.toString();

  QString value = _value.toString();

  if(value.isEmpty()) return "''";

  if (value[0] == '@') 
    return value.mid(1);
  value = value.replace("'", "''");
  if(value.startsWith("$") and value.endsWith("_id$")) value = "$default"; 
  return (value[0] != '$') ? PString(QString("'%1'").arg(value)) : value.mid(1);

}


PVariant PSql::quote(PVariant args) {

    if(args.isNull())
        return PVariant("NULL");
    if(primitiveType(args))
        return PVariant(quoteValue(args));

    if(args.typeName() == "Hash") {
        PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
        foreach(QString key, args.toMap().keys()) {
            PVariant value = args[key];
            if (value.typeName() == "Array")
                result[key] = PVariant(quote(value));
            else
                result[key] = PVariant(quoteValue(value));
        }
        return result;
    }

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    if(args.typeName() == "Array") {
        PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
        for(int i = 0; i < args.count(); i++) {
            PVariant value = args[i];
            result << PVariant(quote(value));
        }
        return result;
    }

    return args;

}


QString PSql:: fieldNameIdToSql(PVariant source_args) {
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


    if(model != nil)
        return model.value<PModel*>()->fieldNameIdToSql(source_args);

    PVariant tables = PString(fieldName).split(".");
    QString fieldNameId;
    QString subTableName;
    if(tables.count() > 1) {
        fieldNameId = tables[0].toString(); 
        subTableName = fieldNameId; 
        subTableName.chop(3); 
    }
    else {
        if(quoteValue) fieldValue = PSql::quoteValue(fieldValue);

        QStringList tables = fieldName.split(".");
        if(fieldValue.typeName() == "Array")
            return      opOnArrayToSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("op", op)->append("array", fieldValue)))));

        return PString(QString("%1 %2 %3").arg(fieldName).arg(op).arg(fieldValue.toString()));
    }

    fieldName = tables.mid(1).join(".");
    QString subTableSql =          fieldNameIdToSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("fieldValue", fieldValue)->append("op", op)->append("quoteValue", quoteValue)->append("model", model)))));
    return PString(QString("%1 in (select id from %2 where %3)").arg(fieldNameId).arg(subTableName).arg(subTableSql));

}




QString PSql:: opOnArrayToSql(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "opOnArrayToSql:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString fieldName = source_args.value<PVariantMapPtr>()->include("fieldName") ? source_args.value<PVariantMapPtr>()->operator[]("fieldName").toString() : QVariant(nil).toString();args.removeByKey("fieldName");
QString op = source_args.value<PVariantMapPtr>()->include("op") ? source_args.value<PVariantMapPtr>()->operator[]("op").toString() : QVariant(QString("=")).toString();args.removeByKey("op");
PVariant array = source_args.value<PVariantMapPtr>()->include("array") ? source_args.value<PVariantMapPtr>()->operator[]("array") : nil;args.removeByKey("array");
QString arrayOp = source_args.value<PVariantMapPtr>()->include("arrayOp") ? source_args.value<PVariantMapPtr>()->operator[]("arrayOp").toString() : QVariant(QString("or")).toString();args.removeByKey("arrayOp");
PVariant model = source_args.value<PVariantMapPtr>()->include("model") ? source_args.value<PVariantMapPtr>()->operator[]("model") : nil;args.removeByKey("model");


    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
     array.forEachPVariant([&] (PVariant fieldValue) mutable {
        if(fieldValue.typeName() == "Array")
            result <<        opOnArrayToSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("op", op)->append("array", fieldValue)->append("model", model)))));
        if(fieldValue.typeName() == "Hash")
            result <<    whereByHash(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("hash", fieldValue)->append("model", model)))));
        else
            result << PString(QString("%1 %2 %3").arg(fieldName).arg(op).arg(PSql::quoteValue(fieldValue)));
    });

    result = result.join(PString(QString(" %1 ").arg(arrayOp)));

    return PString(QString("(%1)").arg(result.toString()));

}


QString PSql:: whereByHash(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "whereByHash:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant hash = source_args.value<PVariantMapPtr>()->include("hash") ? source_args.value<PVariantMapPtr>()->operator[]("hash") : nil;args.removeByKey("hash");
QString hashOp = source_args.value<PVariantMapPtr>()->include("hashOp") ? source_args.value<PVariantMapPtr>()->operator[]("hashOp").toString() : QVariant(QString("and")).toString();args.removeByKey("hashOp");
PVariant model = source_args.value<PVariantMapPtr>()->include("model") ? source_args.value<PVariantMapPtr>()->operator[]("model") : nil;args.removeByKey("model");


    if(hash.isEmpty()) return "";
    if(hash.count() == 1 and hash. undefined("op", nil)!= nil) return "";
    if(hash.count() == 1 and hash. undefined("and", nil)!= nil and hash.undefined("and", nil).isEmpty()) return ""; 

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    QString op = (hash. undefined("op", nil)!= nil) ? hash.undefined("op", nil).toString() : "=";
       hash.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        fieldName = toPeriod(fieldName); 
        if(fieldName == "op");
        else if(fieldValue.typeName() == "Hash")
            result <<      whereByHash(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("hash", fieldValue)->append("hashOp", fieldName)->append("model", model)))));
        else if(fieldName.toLower() == "and" and fieldValue.typeName() == "Array") 
            result <<      whereByArray(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("array", fieldValue)->append("arrayOp", QString("and"))->append("model", model)))));
        else if(fieldValue.typeName() == "Array") {
            QStringList tables = fieldName.split(".");
            if(tables.count() > 1) result <<          fieldNameIdToSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("op", op)->append("fieldValue", fieldValue)->append("quoteValue", false)->append("model", model)))));
            else result <<        opOnArrayToSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("op", op)->append("array", fieldValue)->append("model", model)))));
        }
        else {
            QStringList tables = fieldName.split(".");
            if(tables.count() > 1) result <<        fieldNameIdToSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("op", op)->append("fieldValue", fieldValue)->append("model", model)))));
            else result << PString(QString("%1 %2 %3").arg(fieldName).arg(op).arg(PSql::quoteValue(fieldValue)));
        }
    });

    result = result.join(PString(QString(" %1 ").arg(hashOp)));

    return PString(QString("(%1)").arg(result.toString()));


}

QString PSql:: whereByArray(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "whereByArray:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant array = source_args.value<PVariantMapPtr>()->include("array") ? source_args.value<PVariantMapPtr>()->operator[]("array") : nil;args.removeByKey("array");
QString arrayOp = source_args.value<PVariantMapPtr>()->include("arrayOp") ? source_args.value<PVariantMapPtr>()->operator[]("arrayOp").toString() : QVariant(QString("or")).toString();args.removeByKey("arrayOp");
PVariant model = source_args.value<PVariantMapPtr>()->include("model") ? source_args.value<PVariantMapPtr>()->operator[]("model") : nil;args.removeByKey("model");


    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

     array.forEachPVariant([&] (PVariant fieldValue) mutable {
        PVariant condition;
        if(fieldValue.toString().isEmpty());
        else if(fieldValue.typeName() == "Array")
            condition =    whereByArray(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("array", fieldValue)->append("model", model)))));
        else if(fieldValue.typeName() == "Hash")
            condition =    whereByHash(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("hash", fieldValue)->append("model", model)))));
        else
            condition = PSql::quoteValue(fieldValue);

        if(!condition.toString().isEmpty()) result << condition;

    });

    if(result.isEmpty()) return "";

    result = result.join(PString(QString(" %1 ").arg(arrayOp)));

    return PString(QString("(%1)").arg(result.toString()));

}

QString PSql::toSql(PVariant arrayOrHash, PVariant model) {

    if(arrayOrHash.typeName() == "Array")
        return    whereByArray(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("array", arrayOrHash)->append("model", model)))));
    else if(arrayOrHash.typeName() == "Hash")
        return    whereByHash(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("hash", arrayOrHash)->append("model", model)))));
    else
        return arrayOrHash.toString();

}


bool PSql::primitiveType(PVariant value) {

    return (value.typeName() == "QString" ||
    value.typeName() == "Int" ||
    value.typeName() == "Bool");

}


void PSql::closeAllConnections() {

     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("high_cyan")))))).sql() << "closeAllConnections ->";

    foreach(QString connectionName, QSqlDatabase::connectionNames()) {
         PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("high_cyan")))))).sql() << " - " << connectionName << "closed";
        QSqlDatabase::database(connectionName).close();
        
    }

}


void PSql::initDriverByConnectionName() {

    if(this->connectionName.isNull())
        return;

    if(!this->driver.isNull())
        return;

    if(this->connectionName.toLower().contains("pgsql") or this->connectionName.toLower() == "postgres")
        this->driver = "QPSQL";
    else if(this->connectionName.toLower().contains("mysql"))
        this->driver = "QMYSQL";
    else if(this->connectionName.toLower().contains("sqlite"))
        this->driver = "QSQLITE";
    else {
        PLog().error() << PString(QString("PSql::initDriverByConnectionName: connectionName %1 can't identify the right driver").arg(connectionName));
        exit(0);
    }

}


PSql:: PSql(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PSql:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString host = source_args.value<PVariantMapPtr>()->include("host") ? source_args.value<PVariantMapPtr>()->operator[]("host").toString() : QVariant(nil).toString();args.removeByKey("host");
int port = source_args.value<PVariantMapPtr>()->include("port") ? source_args.value<PVariantMapPtr>()->operator[]("port").toInt() : QVariant(5432).toInt();args.removeByKey("port");
QString dbname = source_args.value<PVariantMapPtr>()->include("dbname") ? source_args.value<PVariantMapPtr>()->operator[]("dbname").toString() : QVariant(nil).toString();args.removeByKey("dbname");
QString user = source_args.value<PVariantMapPtr>()->include("user") ? source_args.value<PVariantMapPtr>()->operator[]("user").toString() : QVariant(nil).toString();args.removeByKey("user");
QString password = source_args.value<PVariantMapPtr>()->include("password") ? source_args.value<PVariantMapPtr>()->operator[]("password").toString() : QVariant(nil).toString();args.removeByKey("password");
QString timezone = source_args.value<PVariantMapPtr>()->include("timezone") ? source_args.value<PVariantMapPtr>()->operator[]("timezone").toString() : QVariant(QString("posix/Europe/Rome")).toString();args.removeByKey("timezone");
QString connectionName = source_args.value<PVariantMapPtr>()->include("connectionName") ? source_args.value<PVariantMapPtr>()->operator[]("connectionName").toString() : QVariant(nil).toString();args.removeByKey("connectionName");
QString driver = source_args.value<PVariantMapPtr>()->include("driver") ? source_args.value<PVariantMapPtr>()->operator[]("driver").toString() : QVariant(nil).toString();args.removeByKey("driver");


    if(connectionName.isNull()) {
        this->connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();
        this->initParams(this->connectionName);
    }
    else {
        this->connectionName = connectionName;
        this->driver = driver;
        this->initDriverByConnectionName();
        this->host = host;
        this->port = port;
        this->dbname = dbname;
        this->user = user;
        this->password = password;
        this->timezone = timezone;
    }

    this->cursorStack = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    this->stateHistory = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    this->init();

    if(QSqlDatabase::connectionNames().indexOf(this->connectionName) == -1) {
       connection = QSqlDatabase::addDatabase(this->driver, this->connectionName);
       this->openConnection();
    }
    else
        connection = QSqlDatabase::database(this->connectionName);


}

void PSql::init() {

    table = PVariant();
    tableIndex = -1;
    tableCursor = PVariant();
    id = QString();

    _select = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    _from = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    _where = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    _orderBy = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    _limit = -1;
    _offset = -1;
    _groupBy = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    _pageSize = "all";
    _page = 0;

    colWidth = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

}

void PSql::resetCursor() {

    tableCursor = nil;
    tableIndex = -1;
    id = QString();

}

PSql* PSql::reset() {

  if(!this->table.isNull())
    this->init();

  return this;

}

void PSql::pushCursor() {

    cursorStack << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tableIndex", tableIndex)->append("tableCursor", tableCursor)->append("id", id))));

}


void PSql::popCursor() {

    PVariant cursor = cursorStack.removeByIndex(0);

    tableIndex = cursor.undefined("tableIndex", nil).toInt();
    tableCursor = cursor.undefined("tableCursor", nil);
    id = cursor.undefined("id", nil).toString();

}

PSql::~PSql() {

    if(!table.isNull()) {
        table = PVariant();
    }

}

void PSql::openConnection() {

       PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red"))->append("levelStr", QString("SQL")))))).debug() << PString(QString("connectionName: %1").arg(connectionName));
       PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red"))->append("levelStr", QString("SQL")))))).debug() << PString(QString("driver: %1").arg(driver));
       PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red"))->append("levelStr", QString("SQL")))))).debug() << PString(QString("host: %1").arg(host));
       PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red"))->append("levelStr", QString("SQL")))))).debug() << PString(QString("port: %1").arg(port));
       PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red"))->append("levelStr", QString("SQL")))))).debug() << PString(QString("db: %1").arg(dbname));
       PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red"))->append("levelStr", QString("SQL")))))).debug() << PString(QString("user: %1").arg(user));
       PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red"))->append("levelStr", QString("SQL")))))).debug() << PString(QString("password: %1").arg(password));
       PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red"))->append("levelStr", QString("SQL")))))).debug() << PString(QString("timezone: %1").arg(timezone));

    connection.setDatabaseName(dbname);
    connection.setUserName(user);
    connection.setPassword(password);
    connection.setHostName(host);
    connection.setPort(port);
    if (!connection.open()) {
        this->connectionState = connection.lastError().driverText();
        PLog().error() << "Failed to open database:" << connection.lastError().driverText();
        PLog().error() << connection.lastError().databaseText();
    }
    else {
           PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("white"))->append("levelStr", QString("SQL")))))).debug() << PString(QString("Connection With %1 DB established").arg(dbname));
        this->connectionState = "connected";
    }

}



QString PSql::toPeriod(QString value) {

  if(!value.contains("->"))
    return value;

  QStringList values = value.split("->");
  value = values[0];
  QString right = values[1];
  values = right.split(" ");
  QString period = values[0];
  right = (values.count() > 1) ? " " + ((QStringList)values.mid(1)).join(" ") : "";
  value = PString(QString("date_part('%1', %2)%3").arg(period).arg(value).arg(right));

  return value;

}

PSql* PSql::reselect(PVariant select, PVariant model) {

    if(select == nil) select = "*";

    if(select.typeName() != "Array") select = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(select))));

    table = nil;
     select.forEachPVariant([&] (PVariant value) mutable {
        if(value.typeName() == "Array")
            this->select(value, model);
        else {
            if(model != nil) value = model.value<PModel*>()->sqlQueryByFieldName(value.toString());
            value = this->toPeriod(value.toString());  
            if(!_select.include(value))  _select << value;
        }
    });

    return this;

}


PSql* PSql::select(PVariant select, PVariant model) {

    this->reset();
    return this->reselect(select, model);

}


PSql* PSql::from(PVariant from) {

    if(from.typeName() != "Array")
        from = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(from))));

    for(int i = 0; i < from.count(); i++) {
        PVariant value = from[i];
        if(value.typeName() == "Array")
            this->from(value);
        else
            if(!_from.include(value)) _from << value;

    }

    return this;

}

PSql* PSql::groupBy(PVariant fields) {

    if(fields.typeName() != "Array")
        fields = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(fields))));

    for(int i = 0; i < fields.count(); i++) {
        PVariant value = fields[i];
        if(value.typeName() == "Array")
            this->groupBy(value);
        else {
            value = toPeriod(value.toString());
            if(!_groupBy.include(value)) _groupBy << value;
        }

    }

    return this;

}



QString PSql::orderByFieldNameIdToSql(QString fieldName, PVariant model) {

    PVariant models = PString(fieldName).split(".");
    QString fieldNameId;
    QString subModelName;

    if(models.count() == 1)
        return fieldName;

    fieldNameId = models[0].toString(); 
    subModelName = fieldNameId;
    if(model != nil)
        subModelName = model.value<PModel*>()->fieldAttr(fieldNameId).undefined("modelNameReference", nil).toString(); 
    else
        subModelName.chop(3); 

    fieldName = models.mid(1).join(".");

    QString subModelSql = this->orderByFieldNameIdToSql(fieldName, model);

    return PString(QString("(select (%1) from %2 where id = %3)").arg(subModelSql).arg(subModelName).arg(fieldNameId));

}


QString PSql::order_by(PVariant value, PVariant model) {

  if(value == nil)
    return "";

  value = orderByFieldNameIdToSql(value.toString(), model); 

  QString strValue = toPeriod(value.toString());

  if(model == nil) return strValue;

  return model.value<PModel*>()->sqlQueryByFieldName(strValue).toString();

}


PSql* PSql:: orderByHash(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "orderByHash:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant model = source_args.value<PVariantMapPtr>()->include("model") ? source_args.value<PVariantMapPtr>()->operator[]("model") : nil;args.removeByKey("model");


    foreach(QString key, args.toMap().keys()) {
      PVariant value = args[key];
      key = this->orderByFieldNameIdToSql(key, model); 
      _orderBy << PString(QString("%1 %2").arg(key).arg(order_by(value, model)));
    }

    return this;
}


PSql* PSql::orderByArray(PVariant args, PVariant model) {

    for(int i = 0; i < args.count(); i++) {
        PVariant value = args[i];
        if(value.typeName() == "QString" || value.typeName() == "QByteArray")
            _orderBy << order_by(value, model);
        else
            orderBy(value, model);
    }

    return this;
}








PSql* PSql::orderBy(PVariant args, PVariant model) {

    if(args.typeName() == "QString" || args.typeName() == "QByteArray")
        order_by(args, model);
    else if(args.typeName() == "Hash")
        return orderByHash(args);
    else if(args.typeName() == "Array")
        return orderByArray(args, model);
    else
        pDebug() << "orderBy(): error type - " << args.typeName();

    return this;

}


PSql* PSql::limit(qint64 limit) {
  _limit = limit;
  return this;
}

PSql* PSql::offset(qint64 offset) {
  _offset = offset;
  return this;
}

PSql* PSql::pageSize(QString pageSize) {
  _pageSize = pageSize;
  return this;
}

PSql* PSql::page(qint64 page) {
  _page = page;
  return this;
}


PSql* PSql::where(PVariant args, QString oprt, PVariant model) {

    

    QString condition = toSql(args, model);

    if(condition != "()" and !condition.isEmpty())
        _where << condition;

    return this;

}


QString PSql::sqlQuery() {

    QString select, from, where, orderBy, groupBy, limit, offset;

    if(_select.any())
        select = PString(QString("SELECT %1 ").arg(_select.join(", ")));

    if(_from.any())
        from = PString(QString("FROM %1 ").arg(_from.join(", ")));

    if(_where.any())
        where = PString(QString("WHERE %1 ").arg(_where.join(" AND ")));

    if(_orderBy.any())
        orderBy  = PString(QString("ORDER BY %1 ").arg(_orderBy.join(", ")));

    if(_groupBy.any())
        groupBy = PString(QString("GROUP BY %1 ").arg(_groupBy.join(", ")));

    if(_limit >= 0)
        limit = PString(QString("LIMIT %1 ").arg(_limit));

    if(_offset >= 0)
        offset = PString(QString("OFFSET %1").arg(_offset));

    return PString(QString("%1%2%3%4%5%6%7").arg(select).arg(from).arg(where).arg(groupBy).arg(orderBy).arg(limit).arg(offset));

}


PSql* PSql:: execute(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "execute:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString sql = source_args.value<PVariantMapPtr>()->include("sql") ? source_args.value<PVariantMapPtr>()->operator[]("sql").toString() : QVariant(  sqlQuery()).toString();args.removeByKey("sql");
QString pageSize = source_args.value<PVariantMapPtr>()->include("pageSize") ? source_args.value<PVariantMapPtr>()->operator[]("pageSize").toString() : QVariant(_pageSize).toString();args.removeByKey("pageSize");
int page = source_args.value<PVariantMapPtr>()->include("page") ? source_args.value<PVariantMapPtr>()->operator[]("page").toInt() : QVariant(_page).toInt();args.removeByKey("page");


    QString limit = PString(QString("LIMIT %1").arg(pageSize));
    QString offset = PString(QString("OFFSET %1").arg(page * pageSize.toInt()));

    if(pageSize == "all")
        limit = offset = "";

    sql += PString(QString(" %1 %2").arg(limit).arg(offset));

    if(table.any())
        table = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    QElapsedTimer time;
    time.start();

    
    
    PLog().sql() << sql;

    qsqlQuery = QSqlQuery(sql, connection);
    QSqlRecord rec = qsqlQuery.record();
    while (qsqlQuery.next()) {
        PVariant record = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
        for(int i = 0; i < rec.count(); i++)
            record[rec.field(i).name()] = qsqlQuery.value(i);

        table << record;
    }

    this->query = sql;

    
    PLog().sql() << PString(QString("... msecs. %1").arg(time.elapsed()));

    return this;

}

PSql* PSql::execute(QString sql) {

    return  execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", sql)))));

}

PSql* PSql::execute(const char* sql) {

    return  execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", sql)))));

}


QString PSql::insertValues(PVariant args) {

  if(args == nil)
      return PString(QString("(id) values(default)"));

  args = quote(args);

  return PString(QString("(%1) values(%2)").arg(args.keys().join(", ", "")).arg(args.values().join(", ")));

}


QString PSql::insert(QString tableName, PVariant values) {


    if(driver == "QPSQL")
        return this->pgSqlInsert(tableName, values);
    else if(driver == "QMYSQL")
        return this->mySqlInsert(tableName, values);
    else if(driver == "QSQLITE")
        return this->sqliteInsert(tableName, values);
    else
        PLog().error() << PString(QString("PSql::insert: driver %1 not supported").arg(driver));

    return QString();

}

QString PSql::mySqlInsert(QString tableName, PVariant values) {

    execute(PString(QString("INSERT INTO %1 %2").arg(tableName).arg(insertValues(values))));
    return qsqlQuery.lastInsertId().toString();

}

QString PSql::pgSqlInsert(QString tableName, PVariant values) {

    PVariant table = execute(PString(QString("INSERT INTO \"%1\" %2 RETURNING id").arg(tableName).arg(insertValues(values))))->table;
    if(table.count() == 0) {
        PLog().error() << "PSql::pgSqlInsert(...): failed";
        return "0";
    }

    return table[0]["id"].toString();

}

QString PSql::sqliteInsert(QString tableName, PVariant values) {

    values.removeByKey("id");
    execute(PString(QString("INSERT INTO %1 %2").arg(tableName).arg(insertValues(values))));
    return qsqlQuery.lastInsertId().toString();

}

QString PSql::db_false() {

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    QString driver = PConf().value(PString(QString("%1.driver").arg(connectionName))).toString();

    if(driver == "QPSQL")
        return "false";
    else if(driver == "QMYSQL")
        return "@false";
    else if(driver == "QSQLITE")
        return "@0";
    else
        PLog().error() << PString(QString("PSql::db_false: driver %1 not supported").arg(driver));

    return QString();

}

QString PSql::db_true() {

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    QString driver = PConf().value(PString(QString("%1.driver").arg(connectionName))).toString();

    if(driver == "QPSQL")
        return "true";
    else if(driver == "QMYSQL")
        return "@true";
    else if(driver == "QSQLITE")
        return "@1";
    else
        PLog().error() << PString(QString("PSql::db_true: driver %1 not supported").arg(driver));

    return QString();

}

QString PSql::db_true_or_false(bool value) {

    return value ? db_true() : db_false();

}


QString PSql::orderingDefaultValue() {

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    QString driver = PConf().value(PString(QString("%1.driver").arg(connectionName))).toString();

    if(driver == "QPSQL")
        return "$default";
    else if(driver == "QMYSQL")
        return "0";
    else if(driver == "QSQLITE")
        return "0";
    else
        PLog().error() << PString(QString("PSql::orderingDefaultValue(): driver %1 not supported").arg(driver));

    return QString();

}


QString PSql::serialConstraint(const QString& tableName) {

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    QString driver = PConf().value(PString(QString("%1.driver").arg(connectionName))).toString();

    if(driver == "QPSQL")
        return PString(QString("DEFAULT currval('%1_id_seq')").arg(tableName));
    else if(driver == "QMYSQL")
        return "DEFAULT  0";
    else if(driver == "QSQLITE")
        return "DEFAULT  0";
    else
        PLog().error() << PString(QString("PSql::serialConstraint(): driver %1 not supported").arg(driver));

    return QString();

}


QString PSql::updateValues(PVariant args) {

    if(args == nil)
        return "";

    args = quote(args);
    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    foreach(QString key, args.toMap().keys()) {
        PVariant value = args[key];
        result << PString(QString("%1 = %2").arg(key).arg(value.toString()));
    }
    return result.join(", ");

}


int PSql::update(QString tableName, PVariant values, PVariant where) {

    QString sqlWhere = toSql(where);
    if (sqlWhere.simplified() != "")
        sqlWhere = PString(QString(" WHERE %1").arg(sqlWhere));
    execute(PString(QString("UPDATE %1 SET %2%3").arg(tableName).arg(updateValues(values)).arg(sqlWhere)));
    return qsqlQuery.numRowsAffected();

}


int PSql::erase(QString tableName, PVariant where) {

    QString sqlWhere = toSql(where);
    if (sqlWhere.simplified() != "")
        sqlWhere = PString(QString(" WHERE %1").arg(sqlWhere));
    execute(PString(QString("DELETE FROM %1%2").arg(tableName).arg(sqlWhere)));

    return qsqlQuery.numRowsAffected();

}

PVariant PSql::fieldNameList() {

    if(table.count() > 0)
        return table[0].keys();

    QSqlRecord record = qsqlQuery.record();
    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    for(int i = 0; i < record.count(); i++)
        result << record.field(i).name();

    return result;

}


int PSql::rowCount() {

  return qsqlQuery.numRowsAffected();

}


int PSql::columnCount() {

    return qsqlQuery.record().count();

}


PVariant PSql::setTableCursor(int row) {

  this->tableIndex = row;
  this->tableCursor = this->table[row];
  if(tableCursor != nil)
    id = tableCursor["id"].toString();

  return this->tableCursor;

}


PVariant PSql::record(int row) {

  if(table == nil)
    execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

  if(table == nil)
      return nil;

  if(row < 0 || row >= table.count()) {
    this->resetCursor();
    return nil;
  }

  return setTableCursor(row);

}

PVariant PSql::data(int row, PVariant idOrFieldName) {

  tableIndex = row;
  return (idOrFieldName.typeName() == "int") ? record(row)[idOrFieldName.toInt()] : record(row)[idOrFieldName.toString()];

}

PVariant PSql::column(PVariant idOrFieldName) {

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    for(int i = 0; i < table.count(); i++) {
        PVariant row = table[i];
        PVariant keys = fieldNameList();
        if(idOrFieldName.typeName() == "int")
            result << row[keys[idOrFieldName.toUInt()].toString()];
        else
            result << row[idOrFieldName.toString()];
    }

    return result;

}


int PSql::count() {

    return (table == nil) ? 0 : table.count();

}


PVariant PSql::first() {

  return record(0);

}

PVariant PSql::last() {

  return record(table.count() - 1);

}

PVariant PSql::prev() {

    return record(tableIndex - 1);

}

PVariant PSql::next() {

  return record(tableIndex + 1);

}

PVariant& PSql::operator[](int index) {


    return table[index];

}

PVariant PSql::operator()(int index) {


    return table[index];

}


int PSql::columnWidth(QString fieldName) {

    if(colWidth(fieldName) != nil)
        return colWidth[fieldName].toUInt();

    PVariant values = this->column(fieldName);

    PVariant vals = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append( fieldName.length()))));
     values.forEachQString([&] (QString value) mutable { vals << value.length(); });

    colWidth[fieldName] = vals.max();

    return colWidth[fieldName].toInt();


}


QSqlField PSql::fieldAttrs(QString fieldName) {

    QSqlRecord record = qsqlQuery.record();
    return record.field(fieldName);

}

void PSql::showSeparator(PVariant fields) {

     fields.forEachQString([&] (QString fieldName) mutable {
        pDebug("%s").noEndl() << QString("+%1").arg("-", -(columnWidth(fieldName) + 2), '-');
    });
    pDebug() << "";

}

void PSql::show(PVariant fields) {

    if(fields == nil)
        fields = fieldNameList();

    pDebug() << " ";

    showSeparator(fields);

     fields.forEachQString([&] (QString fieldName) mutable {
        QString str = PString::justify(fieldName, columnWidth(fieldName), "center");
        pDebug().noEndl() << QString("| %1").arg(str);
    });
    pDebug() << "";

    showSeparator(fields);

    for(int i = 0; i < count(); i++) {
        PVariant row = (*this)[i];
         fields.forEachQString([&] (QString fieldName) mutable {
            int cw = columnWidth(fieldName);
            QString value = row[fieldName].toString().left(cw);
            pDebug().noEndl() << QString("| %1").arg(PString::justify(value, cw,
                                                     (fieldAttrs(fieldName).type() == QVariant::Double) ? "right" : "left"
                                                     ));
        });

        pDebug() << "";

    }

    showSeparator(fields);

    pDebug() << PString(QString("(%1 rows)").arg(count()));

}



QString PSql::db_current(const QString& what) {

    if(what == "timestamp")
        return "$CURRENT_TIMESTAMP";
    if(what == "date")
        return "$CURRENT_DATE";
    if(what == "time")
        return "$CURRENT_TIME";
    else
        return "@date_part('${what}', current_date)";

}


QString PSql::current(const QString& what) {

    QString result = db_current(what).mid(1);
    return select(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(result)))))->execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))))->data(0, 0).toString();

}


PVariant PSql::tables(QSql::TableType type) const {

    QStringList stringList = connection.tables(type);

    return PVariant::fromQStringList(stringList);

}

PVariant PSql::fields(const QString& tableName) const {

    QSqlRecord record = connection.record(tableName);

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    for(int i = 0; i < record.count(); i++) {
        QSqlField sqlField = record.field(i);
        QString required;
        switch(sqlField.requiredStatus()) {
            case 0: required = "Required"; break;
            case 1: required = "Optional"; break;
            default: required = "Unknown";
        }
        PVariant field = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name",   sqlField.name())->append("type",   
                             sqlField.type())->append("default_value",   
                             
                             PSql::quote(  
                             
                             sqlField.defaultValue()))->append("precision",   
                             
                             
                             sqlField.precision())->append("lenght",   
                             
                             
                             
                             sqlField.length())->append("required", required)->append("is_read_only",   
                             
                             
                             
                             
                             
                             sqlField.isReadOnly())->append("is_null",   
                             
                             
                             
                             
                             
                             
                             sqlField.isNull())->append("is_auto_value",   
                             
                             
                             
                             
                             
                             
                             
                             sqlField.isAutoValue())->append("is_valid",   
                             
                             
                             
                             
                             
                             
                             
                             
                             sqlField.isValid())->append("is_generated",   
                             
                             
                             
                             
                             
                             
                             
                             
                             
                             sqlField.isGenerated()))));

        result[sqlField.name()] = field;
    }

    return result;

}

void PSql::initParams(const QString& connectionName) {

    this->connectionName = connectionName;
    this->host = PConf().value(PString(QString("%1.host").arg(connectionName))).toString();
    this->port = PConf().value(PString(QString("%1.port").arg(connectionName))).toInt();
    this->dbname = PConf().value(PString(QString("%1.dbname").arg(connectionName))).toString();
    this->user = PConf().value(PString(QString("%1.user").arg(connectionName))).toString();
    this->password = PConf().value(PString(QString("%1.password").arg(connectionName))).toString();
    this->timezone = PConf().value(PString(QString("%1.timezone").arg(connectionName))).toString();
    this->driver = PConf().value(PString(QString("%1.driver").arg(connectionName))).toString();

}


void PSql::initByConnectionName(const QString& connectionName) {

    PVariant params = PSinglConfigurationManager::instance()->configMap["plusqode"]->value(connectionName);
    params.  undefined("connectionName=", connectionName);

    PSql psql(params);

}

void PSql::pushState() {

    PVariant state = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("table", table)->append("tableIndex", tableIndex)->append("tableCursor", tableCursor)->append("select", _select)->append("from", _from)->append("where", _where)->append("orderBy", _orderBy)->append("limit", _limit)->append("offset", _offset)->append("groupBy", _groupBy)->append("pageSize", _pageSize)->append("page", _page))));

    this->init();
    stateHistory << state;

}


PSql* PSql::popState() {

    PVariant state = stateHistory.removeByIndex(0);
    table = state["table"];
    tableIndex = state["tableIndex"].toUInt();
    tableCursor = state["tableCursor"];
    _select = state["select"].toString();
    _from = state["from"].toString();
    _where = state["where"].toString();
    _orderBy = state["orderBy"].toString();
    _limit = state["limit"].toUInt();
    _offset = state["offset"].toUInt();
    _groupBy = state["groupBy"].toString();
    _pageSize = state["pageSize"].toString();
    _page = state["page"].toUInt();

    return this;

}

void PSql::demo() {

               PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("host", QString("localhost"))->append("port", 5432)->append("dbname", QString("quickorderQuickOrder"))->append("user", QString("quickorder"))->append("password", QString("quickorder"))->append("connectionName", QString("quickorder"))))));
               PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("host", QString("localhost"))->append("port", 5432)->append("dbname", QString("quickmanager"))->append("user", QString("quickmanager"))->append("password", QString("quickmanager"))->append("connectionName", QString("quickmanager"))))));

     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("quickorder")))))).  select(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("name"))->append(QString("price"))->append(QString("id"))))))->from(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("cookbook"))))))->execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))))->show();
     PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", QString("quickmanager")))))).  select(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("date"))->append(QString("amount"))->append(QString("description"))))))->from(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("transactions"))))))->execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))))->show();

    PSql::closeAllConnections();

}
