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

#include "app/modules/purchase/pmpurchase_credit_note/pmpurchase_credit_note.h"

PMPurchaseCreditNote::$PMPurchaseCreditNote() {

    init(args);

}

PMPurchaseCreditNote& PMPurchaseCreditNote::init(PVariant args) {

    args.domain$ += ${document_type_id.name: 'Purchase Credit Note'};
    
    PMDocument::init(args);
    
    QString purchaseCreditNoteId = $PMDocumentType().$find(name: "Purchase Credit Note")->id$s;
    
    document_type_id_attrs$ = ${default: purchaseCreditNoteId};
    
    return *this;

}

