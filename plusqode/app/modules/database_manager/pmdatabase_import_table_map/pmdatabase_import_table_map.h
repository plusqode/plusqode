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

#ifndef PMDATABASEIMPORTTABLEMAP_H
#define PMDATABASEIMPORTTABLEMAP_H

#include <QtWidgets/QProgressDialog>

#include "sql/pmodel.h"
#include "app/modules/database_manager/pmdatabase_connection/pmdatabase_connection.h"
#include "app/modules/database_manager/pmdatabase_import_field_map/pmdatabase_import_field_map.h"

class PMDatabaseImportTableMap : public PModel {

    Q_OBJECT

public:
    PMDatabaseImportTableMap(PVariant args);
    PMDatabaseImportTableMap& init(PVariant);

public slots:

    void setFilter();
    void onNewBeforeWidget();
    void onNewAfterWidget();
    void onEditBeforeWidget();
    void onEditAfterWidget();
    virtual bool onOkDialog();
    bool toSkip();
    void import();
    PModelPtr getModelPtr(const QString& modelName);
    void updateReferences();

public:
    PVariant models;
    PSqlPtr sourceSqlPtr;
    PSqlPtr destSqlPtr;

    static PVariant tableMap;

};

Q_DECLARE_METATYPE(PMDatabaseImportTableMap*)

#endif // PMDATABASEIMPORTTABLEMAP_H
