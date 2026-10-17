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

#include "app/modules/database_manager/pmdatabase_connection_table_field/pmdatabase_connection_table_field.h"

PMDatabaseConnectionTableField::$PMDatabaseConnectionTableField() {

    init(args);

}

PMDatabaseConnectionTableField& PMDatabaseConnectionTableField::init(PVariant args) {

    PModel::init(args);

    name$ = $pt();
    database_connection_table_id$ = $pa(onDelete: "cascade");
    type$ = $pt();
    default_value$ = $pt();
    precision$ = $pt();
    length$ = $pt();
    required$ = $pt();
    is_read_only$ = $pb();
    is_null$ = $pb();
    is_auto_value$ = $pb();
    is_valid$ = $pb();
    is_generated$ = $pb();

    return *this;

}

