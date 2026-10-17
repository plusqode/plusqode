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

#include "app/modules/core/pmtransaction/pmtransaction.h"

PMTransaction::$PMTransaction() {

    init(args);

}

PMTransaction& PMTransaction::init(PVariant args) {

    PModel::init(args);

    mainField = "amount";
    showField = $["amount", "date"];

    amount$ = $pf(mandatory: true);
    date$ = $pd(default: psql->current("date"));
    opcode$ = $pt();
    transaction_type$ = $pi();
    description$ = $pt();
    description2$ = $pt();
    description3$ = $pt();
    description4$ = $pt();
    reason$ = $pt();
    note$ = $pt();
    charges$ = $pf();
    cro$ = $pt();
    contact$ = $pt();
    check_number$ = $pt();
    hide$ = $pb();
    balance$ = $pf();
    payment_table$ = $pa();
    qm_transaction_id$ = $pi();

    return *this;

}


