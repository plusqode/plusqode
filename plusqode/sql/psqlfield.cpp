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




   #include "sql/psqlfield.h"


   

   

PSqlField::PSqlField()
{
}

PVariant& PSqlField::operator=(QVariant var) {

    return PVariant::operator =(var);

}

PVariant PSqlField::autoComplete(const QString& modelName, QString fieldName, PVariant args) {

    if(args["type"] != "auto")
        return args;

    if(fieldName.endsWith("_id")) {
        fieldName.chop(3);
        args.  undefined("modelName=", fieldName);
        return pManyToOne(args);
    }
    else if(fieldName.endsWith("_table")) {
        fieldName.chop(6);
        args.  undefined("modelName=", fieldName);
        args.  undefined("referenceFieldName=", PString(QString("%1_id").arg(modelName)));
        return pOneToMany(args);
    }

    return pText(args);

}


PVariant PSqlField::pAuto(PVariant args) {

    args["type"] = "auto";
    return args;

}

PVariant PSqlField::pa(PVariant args) {

    return pAuto(args);

}

PVariant PSqlField::pText(PVariant args) {

    args["type"] = "text";
    return args;

}

PVariant PSqlField::pt(PVariant args) {

    return pText(args);

}


PVariant PSqlField::pInteger(PVariant args) {

    args["type"] = "integer";
    return args;

}

PVariant PSqlField::pi(PVariant args) {

    return pInteger(args);

}

PVariant PSqlField::pFloat(PVariant args) {

    args["type"] = "float";
    return args;

}

PVariant PSqlField::pf(PVariant args) {

    return pFloat(args);

}

PVariant PSqlField::pDate(PVariant args) {

    args["type"] = "date";
    return args;

}

PVariant PSqlField::pd(PVariant args) {

    return pDate(args);

}

PVariant PSqlField::pTime(PVariant args) {

    args["type"] = "time";
    return args;

}


PVariant PSqlField::pDateTime(PVariant args) {

    args["type"] = "datetime";
    return args;

}

PVariant PSqlField::pdt(PVariant args) {

    return pDateTime(args);

}

PVariant PSqlField::pBool(PVariant args) {

    args["type"] = "bool";
    return args;

}

PVariant PSqlField::pb(PVariant args) {

    return pBool(args);

}

PVariant PSqlField:: pOneToOne(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pOneToOne:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");


    args["modelNameReference"] = modelName;
    if(args.include("onDelete")) args["onDelete"] = "CASCADE";
    if(args.include("onUpdate")) args["onUpdate"] = "CASCADE";
    
    args["type"] = "oneToOne";

    return args;

}

PVariant PSqlField:: pOneToMany(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pOneToMany:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
QString referenceFieldName = source_args.value<PVariantMapPtr>()->include("referenceFieldName") ? source_args.value<PVariantMapPtr>()->operator[]("referenceFieldName").toString() : QVariant(nil).toString();args.removeByKey("referenceFieldName");


    args["modelNameReference"] = modelName;
    args["referenceFieldName"] = referenceFieldName;
    args["type"] = "oneToMany";
    return args;

}

PVariant PSqlField:: pManyToOne(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pManyToOne:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");


    args["modelNameReference"] = modelName;
    if(args.include("onDelete")) args["onDelete"] = "CASCADE";
    if(args.include("onUpdate")) args["onUpdate"] = "CASCADE";
    
    args["type"] = "manyToOne";

    return args;

}


PVariant PSqlField:: pManyToMany(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pManyToMany:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
QString joinTable = source_args.value<PVariantMapPtr>()->include("joinTable") ? source_args.value<PVariantMapPtr>()->operator[]("joinTable").toString() : QVariant(nil).toString();args.removeByKey("joinTable");
QString referenceFieldName = source_args.value<PVariantMapPtr>()->include("referenceFieldName") ? source_args.value<PVariantMapPtr>()->operator[]("referenceFieldName").toString() : QVariant(nil).toString();args.removeByKey("referenceFieldName");
QString referenceFieldName2 = source_args.value<PVariantMapPtr>()->include("referenceFieldName2") ? source_args.value<PVariantMapPtr>()->operator[]("referenceFieldName2").toString() : QVariant(nil).toString();args.removeByKey("referenceFieldName2");


    args["modelNameReference"] = modelName;
    args["joinTable"] = joinTable;
    args["referenceFieldName"] = referenceFieldName;
    args["referenceFieldName2"] = referenceFieldName2;
    
    
    if(args.include("onDelete")) args["onDelete"] = "CASCADE";
    if(args.include("onUpdate")) args["onUpdate"] = "CASCADE";
    

    args["type"] = "manyToMany";

    return args;

}


PVariant PSqlField:: pVirtual(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pVirtual:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString functionName = source_args.value<PVariantMapPtr>()->include("functionName") ? source_args.value<PVariantMapPtr>()->operator[]("functionName").toString() : QVariant(nil).toString();args.removeByKey("functionName");


    args["functionName"] = functionName;
    args["type"] = "virtual";
    return args;

}


PVariant PSqlField::pv(PVariant args) {

    return pVirtual(args);

}

PVariant PSqlField:: pWidget(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "pWidget:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString functionName = source_args.value<PVariantMapPtr>()->include("functionName") ? source_args.value<PVariantMapPtr>()->operator[]("functionName").toString() : QVariant(nil).toString();args.removeByKey("functionName");


    args["functionName"] = functionName;
    args["type"] = "widget";
    if(args. undefined("xml", nil) ==  nil) args.  undefined("xml=", "<layout/>");
    return args;

}


PVariant PSqlField::pw(PVariant args) {

    return pWidget(args);

}


PVariant PSqlField::primaryKey(PVariant args) {

    args["type"] = "integer";
    args["system"] = true;
    args["constraint"] = "SERIAL PRIMARY KEY";

    return args;

}

   #include "sql/psql.h"

PVariant PSqlField::serial(PVariant args, QString tableName) {

    args["type"] = "integer";
    args["system"] = true;
    args["constraint"] = PSql::serialConstraint(tableName);

    return args;

}
