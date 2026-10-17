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

#include "app/modules/core/pmcontact_address/pmcontact_address.h"

PMContactAddress::$PMContactAddress() {

    init(args);

}


PMContactAddress& PMContactAddress::init(PVariant args) {

    PModel::init(args);

    contact_id$ = $pManyToOne(modelName: "contact");
    name$ = $pt();
    contact_name$ = $pt();
    contact_surname$ = $pt();
    street_name$ = $pt();
    street_number$ = $pt();
    address_note$ = $pt();
    postal_code$ = $pt();
    city$ = $pt();
    state_province$ = $pt();
    country$ = $pt();
    phone$ = $pt();
    mobile$ = $pt();
    email$ = $pt();

    account_holder$ = $pt();
    iban$ = $pt();
    bic_swift$ = $pt();

    return *this;

}
