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

#include "app/modules/core/pmsetting/pmsetting.h"

PMSetting::$PMSetting() {

    init(args);

}

PMSetting& PMSetting::init(PVariant args) {

    PModel::init(args);

    language$ = $pt(default: "en", mandatory: true);
    
    decimal_precision$ = $pt(default: "2", fieldType: "spinbox", mandatory: true);

    tax_inclusive_mode$ = $pb(default: true);
    
    form_font$ = $pt(default: "arial", mandatory: true); 

    form_font_size$ = $pi(default: 10, fieldType: "spinbox", mandatory: true); 
    
    form_main_font$ = $pt(default: "arial", mandatory: true); 
    
    form_main_font_size$ = $pi(default: 10, fieldType: "spinbox", mandatory: true);

    form_field_minimum_height$ = $pi(default: 25, fieldType: "spinbox", mandatory: true);

    read_only_field_color$ = $pt(default: "#EEEEEE", mandatory: true); 
    
    mandatory_field_color$ = $pt(default: "yellow", mandatory: true); 
    
    window_color$ = $pt(default: "white", mandatory: true); 
    
    ip_address$ = $pt(default: "192.168.0.2", mandatory: true); 

    telemetry$ = $pt(default: "telemetry.plusqode.com:9089/api/telemetry");

    browser_command_line$ = $pt(default: "firefox");

    return *this;

}


