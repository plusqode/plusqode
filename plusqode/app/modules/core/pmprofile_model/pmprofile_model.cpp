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

#include "app/modules/core/pmprofile_model/pmprofile_model.h"
#include "app/modules/pmodules.h"

PMProfileModel::$PMProfileModel() {

    init(args);

}

PMProfileModel& PMProfileModel::init(PVariant args) {

    PModel::init(args);
    
    profile_id$ = $pa();
    
    model_name$ = $pa(main: true, editable: true, fieldType: "combobox", itemsAndValues: tables());
    
    menu$ = $pb(default: true, fieldType: "switch_edit", color: "random");
    
    up_record$ = $pb(default: true, fieldType: "switch_edit", color: "random");
    down_record$ = $pb(default: true, fieldType: "switch_edit", color: "random");

    new_record$ = $pb(default: true, fieldType: "switch_edit", color: "random");
    edit_record$ = $pb(default: true, fieldType: "switch_edit", color: "random");
    delete_record$ = $pb(default: true, fieldType: "switch_edit", color: "random");
    print_record$ = $pb(default: true, fieldType: "switch_edit", color: "random");
    
    profile_model_widget_table$ = $pa();

    return *this;

}


PVariant PMProfileModel::tables() {

    PVariant tables = $PSql().tables();

    tables = tables.quicksort();

    return PVariant::fromItemsAndValues(tables, tables);

}

