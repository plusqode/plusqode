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

#ifndef PMDATABASEIMPORT_H
#define PMDATABASEIMPORT_H

#include "sql/pmodel.h"
#include "app/modules/database_manager/pmdatabase_import_table_map/pmdatabase_import_table_map.h"


class PMDatabaseImport : public PModel {

    Q_OBJECT

public:
    PMDatabaseImport(PVariant args);
    PMDatabaseImport& init(PVariant);
    PVariant action(PVariant action);

public slots:

    virtual bool onOkDialog();
    void import();

};

Q_DECLARE_METATYPE(PMDatabaseImport*)

#endif // PMDATABASEIMPORT_H
