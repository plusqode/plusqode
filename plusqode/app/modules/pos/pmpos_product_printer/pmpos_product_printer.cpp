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

#include "app/modules/pos/pmpos_product_printer/pmpos_product_printer.h"

PMPosProductPrinter::$PMPosProductPrinter() {
 
    init(args);

}

PMPosProductPrinter& PMPosProductPrinter::init(PVariant args) {

    PModel::init(args);

    // Sarebbe un errore scrivere pos_product_id$ = $pa(); perche' pos_product deriva da product 
    // e sul db la tabella pos_product non esiste
    product_id$ = $pa(); 
    pos_printer_id$ = $pa();

    return *this;

}


