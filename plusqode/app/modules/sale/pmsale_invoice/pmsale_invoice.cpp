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

#include "app/modules/sale/pmsale_invoice/pmsale_invoice.h"

PMSaleInvoice::$PMSaleInvoice() {

    init(args);

}

PMSaleInvoice& PMSaleInvoice::init(PVariant args) {

    args.domain$ += ${document_type_id.name: 'Sale Invoice'};
    
    PMDocument::init(args);
    
    QString saleInvoiceId = $PMDocumentType().$find(name: "Sale Invoice")->id$s;
    
    document_type_id_attrs$ = ${default: saleInvoiceId};
    
    return *this;

}

