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

#include "app/modules/core/pmdocument_attrs/pmdocument_attrs.h"

PMDocumentAttrs::$PMDocumentAttrs() {

    init(args);

}

PMDocumentAttrs& PMDocumentAttrs::init(PVariant args) {

    PModel::init(args);

    name$ = $pt(mandatory: true);
    row$ = $pi(default: -1);
    col$ = $pi(default: -1);

    print_type$ = $pt(itemsAndValues: {partial: "Partial",
                                       full: "Full",
                                       full2: "Full2"}, fieldType: "combobox", default: "Partial");

    char_size$ = $pi(default: 1, fieldType: "spinbox");
    copy_number$ = $pi(default: 1);
    style$ = $pt(default: "qd");
    top_margin$ = $pi(default: 0);
    quantity_field_width$ = $pi(default: 5);
    price_field_width$ = $pi(default: 7);
    total_price_field_width$ = $pi(default: 8);     
    paper_width$ = $pi(default: 0);       
    paper_rows$ = $pi(default: 50);

    header$ = $pt(default: PTranslator::tr("HEADER"));
    footer$ = $pt(default: PTranslator::tr("FOOTER"));

    print_geometry$ = $pb(default: false, color: "random");
    print_header$ = $pb(default: false, color: "random");
    print_footer$ = $pb(default: false, color: "random");
    print_logo$ = $pb(default: false, color: "random");
    print_company$ = $pb(default: false, color: "random");
    print_date$ = $pb(default: false, color: "random");
    print_time$ = $pb(default: true, color: "random");     
    print_serial$ = $pb(default: true, color: "random");
    print_user$ = $pb(default: false, color: "random");

    print_customer$ = $pb(default: false, color: "random");
    print_name$ = $pb(default: false, color: "random");
    print_contact_surname$ = $pb(default: false, color: "random");
    print_contact_name$ = $pb(default: false, color: "random");
    print_billing_address$ = $pb(default: false, color: "random");
    print_delivery_address$ = $pb(default: false, color: "random");
    print_phone$ = $pb(default: false, color: "random");
    print_mobile$ = $pb(default: false, color: "random");
    print_vat_number$ = $pb(default: false, color: "random");
    print_fiscal_code$ = $pb(default: false, color: "random");
    print_pec$ = $pb(default: false, color: "random");

    print_note$ = $pb(default: true, color: "random");

    open_cash_drawer$ = $pb(default: false, color: "random");

    return *this;

}


