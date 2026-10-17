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

#include "app/modules/pos/pmpos_document_item/pmpos_document_item.h"
#include "app/modules/pmodules.h"

PMPosDocumentItem::$PMPosDocumentItem() {

    init(args);

}

PMPosDocumentItem& PMPosDocumentItem::init(PVariant args) {
    
    PMDocumentItem::init(args);

    this->autoView = false;

    pos_printer_id$ = $pa();

    to_print$ = $pb(default: true);
    
    return *this;

}


bool PMPosDocumentItem::isModifier() {

    if(product_id$ == 0)
        return false;

    PModelPtr productTypeId = product_id$->product_type_id$$;

    if(productTypeId == nil)
        return false;


    if(productTypeId != nil and productTypeId->name$s != "modifier")
        return false;

    return true;

}


void PMPosDocumentItem::setModifier(const QString& modifier) {

    if(!this->isModifier())
        return;

    QString name = name$s;

    if(name.startsWith(" - ") or name.startsWith(" + "))
        name.remove(0, 3);

    if(modifier == "-") {
        name$ = $" - ${name}";
        quantity$ = PVariant(0.00);
    }
    else if(modifier == "+")
        name$ = $" + ${name}";

    sqlView->reloadCurrentRecord();

}

void PMPosDocumentItem::changeQuantity(const QString& qty) {

    // questo controllo serve quando modifico in cascata una quantita' es. 5 margherita
    // per evitare che il - prenda la quantita' 5
    if(name$s.startsWith(" - "))
        return;

    quantity$ = qty;
    this->onChangeField("quantity", nil);

}

PVariant PMPosDocumentItem::action(PVariant button) {

    if(this->isModifier()) {
        PModel::onClick(${action: "delete"});
        return true;
    }

    if(button.action$s == "remove") {
        do {
            PModel::onClick(${action: "delete"});
        } while(this->count() and  this->isModifier());

        return true;
    }

    return PMDocumentItem::action(button);

}
