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

#include "app/modules/purchase/pmpurchase_quotation/pmpurchase_quotation.h"
#include "widgets/sqlview/psqlformviewdialog.h"


PMPurchaseQuotation::$PMPurchaseQuotation() {

    init(args);

}

PMPurchaseQuotation& PMPurchaseQuotation::init(PVariant args) {

    args.domain$ += ${document_type_id.name: 'Purchase Quotation'};
    
    PMDocument::init(args);

    QString purchaseQuotationId = $PMDocumentType().$find(name: "Purchase Quotation")->id$s;
    
    document_type_id_attrs$ = ${default: purchaseQuotationId};
    
    states.clear();

    states.draft$ =      ${arcs: ['confirmed'],                      label: 'Draft',   hue: 1};
    states.confirmed$ =  ${arcs: ['sent', 'new_order', 'cancelled'], label: 'Confirm', hue: 1};
    states.sent$ =       ${arcs: ['new_order', 'cancelled'],         label: 'Send',    hue: 140};
    states.new_order$ =  ${arcs: ['cancelled'],                      label: 'Generate Order',  hue: 140};
    states.cancelled$ =  ${arcs: [],                                 label: 'Cancel',  hue: 1};
    //states.buttons$ =    ${arcs: ['alina', 'herbert']};

    return *this;

}

PVariant PMPurchaseQuotation::action(PVariant button) {
  
    PLog().debug() << "purchase quotation ==>" << button.toString();

    if(button.toString() == "sent") {
        return true;
    }

    if(button.toString() == "new_order") {
        newDocument("Purchase Order");
        return true;

    }

    return PMDocument::action(button);

}

void PMPurchaseQuotation::onAfterWidget() {
    
    date$w->setDisabled(state$s != "draft");
    mainWidget = $<QWidget*>("mainWidget");
    mainWidget->setDisabled(state$s == "sent");

}

