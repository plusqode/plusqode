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

#include "app/modules/core/pmdocument_type/pmdocument_type.h"
#include "app/modules/core/pmdocument_attrs/pmdocument_attrs.h"
#include "app/modules/core/pmsequence/pmsequence.h"
#include "app/modules/core/pmmessage_box/pmmessage_box.h"
#include "app/modules/core/pmicon/pmicon.h"

PMDocumentType::$PMDocumentType() {

    init(args);

}

PMDocumentType& PMDocumentType::init(PVariant args) {

    PModel::init(args);

    name$ = $pt(mandatory: true);
    
    sequence_id$ = $pa();

    document_attrs_id$ = $pa(default: 1);

    pos_printer_table$ = $pa();
    
    icon_id$ = $pa(default: 6);

    print_button$ = $pb(default: false, fieldType: "switch_edit");

    return *this;

}


