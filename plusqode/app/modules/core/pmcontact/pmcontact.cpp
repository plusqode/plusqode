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

#include "app/modules/core/pmcontact/pmcontact.h"
#include "app/modules/core/pmcontact_address/pmcontact_address.h"
#include "widgets/widgetedit/psqlcombobox.h"

PMContact::$PMContact() {

    init(args);

}

PMContact& PMContact::init(PVariant args) {

    PModel::init(args);

    showField = $["contact_surname", "contact_name"];

    this->tabOrderFromCpp = true;

    name$ = $pt(mandatory: true);
    
    contact_type$ = $pt(itemsAndValues: {customer: "Customer",
                                         supplier: "Supplier",
                                         company: "Company"}, default: 'customer', fieldType: "combobox");

    contact_type_id$ = $pa(filters: [{label: "Supplier", filter: {contact_type_id.name: "Supplier"}}],
                               groups: [{label: "Name", value: "contact_type_id.name"},
                                        {label: "Id", value: "contact_type_id.id"}]
                              );

    contact_name$ = $pt(filters: [{label: "Mario", value: "Mario"},
                                    {label: "Valerio", value: "Valerio"},
                                    {label: "Tutti", filter: "@id > 0"}
                                    ],
                         groups: [{label: "Contact Name", value: "contact_name"}]
                                    );

    contact_surname$ = $pt(filters: [{label: "Rossi", value: "Rossi"},
                                       {label: "Bianchi", value: "Bianchi"}]);

    contact_nickname$ = $pt();
    phone$ = $pt();
    mobile$ = $pt();
    email$ = $pt();
    pec$ = $pt();
    vat_number$ = $pt();
    fiscal_code$ = $pt();
    description$ = $pt(fieldType: "text_edit");

    credit$ = $pf(totalizable: true);
    
    billing_address_id$ = $pm2o(modelName: "contact_address", onDelete: true, newButton: false);
    delivery_address_id$ = $pm2o(modelName: "contact_address", onDelete: true, newButton: false) ;

    contact_address_table$ = $pa();

    return *this;

}

void PMContact::onChangeField(QString fieldName, PVariant data) {
   
   if(fieldName == "contact_address_table") {
       QString ba_id = this->undefined("billing_address_id", nil).value<PModelPtr>()->id$s;
       QString da_id = this->undefined("delivery_address_id", nil).value<PModelPtr>()->id$s;

       dynamic_cast<PSqlComboBox*>(this->billing_address_id$w)->populateList();
       dynamic_cast<PSqlComboBox*>(this->delivery_address_id$w)->populateList();

       this->billing_address_id$ = ba_id; 
       this->delivery_address_id$ = da_id; 
   }


}

void PMContact::setFilter() {

    billing_address_id_attrs$ = ${filter: {contact_id: fieldValue("id")}};
    delivery_address_id_attrs$ = ${filter: {contact_id: fieldValue("id")}};

}

void PMContact::onNewBeforeWidget() {

    this->contact_address_table$->writeOnDialog = true; // It performes the db writing pushing ok button also with level > 0
    this->setFilter();

}


void PMContact::onEditBeforeWidget() {

    this->contact_address_table$->writeOnDialog = true; // It performes the db writing pushing ok button also with level > 0
    this->setFilter();

}


