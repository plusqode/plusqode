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

#include "app/modules/warehouse/pmbarcode_printer/pmbarcode_printer.h"

PMBarcodePrinter::$PMBarcodePrinter() {

    init(args);

}


PMBarcodePrinter& PMBarcodePrinter::init(PVariant args) {

    PModel::init(args);
    
    ip_address$ = $pt(default: "192.168.0.192");
    port$ = $pt(default: "9100");

    barcode_type$ = $pt(itemsAndValues: {
                                         "68": "EAN8",
                                         "67": "EAN13",
                                         "65": "UPC-A",
                                         "66": "UPC-E",
                                         "69": "CODE39",
                                         "72": "CODE93",
                                         "73": "CODE128",
                                         "71": "CODEBAR",
                                         "70": "ITF"},
                                         default: "67",
                                         fieldType: "combobox");
    
    alignment$ = $pt(itemsAndValues: {
                                         "0": "Left",
                                         "1": "Center",
                                         "2": "Right"},
                                         default: "1",
                                         fieldType: "combobox");

    font$ = $pi(default: 1, fieldType: "spinbox");
    font_size$ = $pi(default: 2, fieldType: "spinbox", minimum: 1, maximum: 8);

    print_name$ = $pb(default: true);
    print_price$ = $pb(default: true);
    print_barcode$ = $pb(default: true);
    print_hri$ = $pb(default: true);

    prefix$ = $pt(default: "=> ");
    suffix$ = $pt(default: " Euro <=");

    barcode_width$ = $pi(default: 50);
    barcode_height$ = $pi(default: 60);

    scan_and_print$ = $pb(default: false, toolTip: "Enable automatic Scan and Print on barcode manager");


    return *this;

}
