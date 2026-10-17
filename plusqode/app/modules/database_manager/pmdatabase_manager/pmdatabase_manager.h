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

#ifndef PMDATABASEMANAGER_H
#define PMDATABASEMANAGER_H

#include "sql/pmodel.h"
#include "misc/psystem.h"

class PMDatabaseManager : public PModel {

    Q_OBJECT

public:
    PMDatabaseManager(PVariant args);
    PMDatabaseManager& init(PVariant);

public slots:
    void onChangeField(QString fieldName, PVariant data);
    PVariant action(PVariant button);
    QString create_db();
    QString remove_db();
    QString rename_db();
    QString backup_db();
    QString restore_db();
    QString duplicate_db();

};

Q_DECLARE_METATYPE(PMDatabaseManager*)

#endif // PMDATABASEMANAGER_H
