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



   #include "dom/pdomtable.h"

   
   

PDomTable::PDomTable(PVariant table, PVariant fieldNameList) : PDom("table", "") {

    this->table = table;
    this->fieldNameList = fieldNameList;

    if(fieldNameList == nil)
        this->fieldNameList = table.undefined("", nil).keys();

}

PDom* PDomTable::tr_th(PVariant record) {

    PDom* tr = new  PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("tr"))))));

     fieldNameList.forEachPVariant([&] (PVariant field) mutable {
        QString fieldLabel = field.typeName() == "Hash" ? field.undefined("fieldLabel", nil).toString() : field.toString();
        *tr << new    PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("th"))->append("innerHTML", fieldLabel)))));
    });

    return tr;

}

PDom* PDomTable::tr_td(PVariant record) {

    PDom* tr = new  PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("tr"))))));

     fieldNameList.forEachPVariant([&] (PVariant field) mutable {
        QString fieldName = field.typeName() == "Hash" ? field.undefined("fieldName", nil).toString() : field.toString();
        *tr << new    PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("td"))->append("innerHTML",     record[fieldName])))));
    });

    return tr;

}


QString PDomTable::toHtml() {

    if(table.count() == 0)
        return "";

    (*this) << this->tr_th(table.undefined("", nil));

     table.forEachPVariant([&] (PVariant record) mutable {
        (*this) << this->tr_td(record);
    });

    return PDom::toHtml();

}
