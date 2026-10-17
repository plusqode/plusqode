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





   #include "sql/psqldataloader.h"



   


   

PSqlDataLoader::PSqlDataLoader(const QString& fileName, const QString& connectionName) :
        fileName(fileName),
        connectionName(connectionName)
{

    lastId = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

}

   #include "app/modules/pmodules.h"


void PSqlDataLoader::load(PVariant data) {

       data.forEachQString_PVariant([&] (QString modelName,PVariant records) mutable {
         PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("yellow")))))).sql() << modelName << records.toString();

        PModelPtr model = PModel   ::   newModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("connectionName", connectionName)))));

        if(records.typeName() == "Array") {
             records.forEachPVariant([&] (PVariant record) mutable {

                   record.forEachQString_PVariant([&] (QString key,PVariant value) mutable {
                    if(value.toString().startsWith("lastId_")) {
                        QString tableName = value.toString().remove("lastId_");
                        record[key] = lastId[tableName];
                    }
                });

                lastId[modelName] = model->psql->insert(modelName, record);
            });
        }

        else if(records.typeName() == "Hash") {
            PLog().error() << "PSqlDataLoader::load(): Hash instead than Array in " << modelName;
            exit(0);
        }

        delete model.model;

    });

}


void PSqlDataLoader::load() {

    PLog().sql() << "PSqlDataLoader::load():" << fileName;

    if(!QDir().exists(fileName)) return;
    PConfiguration config(fileName);

    PVariant data = config.cfg();

    if(data == nil) {
        PLog().error() << "Syntax Error";
        exit(0);
    }

    if(data.typeName() == "Hash")
        load(data);
    else if(data.typeName() == "Array")
         data.forEachPVariant([&] (PVariant data) mutable {
            load(data);
        });


}
