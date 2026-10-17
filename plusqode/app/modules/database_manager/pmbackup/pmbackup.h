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

#ifndef PMBACKUP_H
#define PMBACKUP_H

#include <QtWidgets/QFileDialog>

#include "sql/pmodel.h"
#include "sql/psqlgenerator.h"
#include "misc/psystem.h"

class PMBackup : public PModel
{
    Q_OBJECT
public:
    PMBackup(PVariant args);
    PMBackup& init(PVariant);
    PVariant fileDialogBackup(); 
    PVariant fileDialogRestore(); 

public slots:    

    PVariant action(PVariant action);

};

Q_DECLARE_METATYPE(PMBackup*)

#endif // PMBACKUP_H
