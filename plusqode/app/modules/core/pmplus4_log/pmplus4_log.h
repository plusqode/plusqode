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

#ifndef PMPLUS4_LOG_H
#define PMPLUS4_LOG_H

#include "sql/pmodel.h"
#include "misc/popenurl.h"

class PMPlus4Log : public PModel {

    Q_OBJECT

public:
#include "dom/phtml_header.h"

    PMPlus4Log() {};
    PMPlus4Log(PVariant args);
    PMPlus4Log& init(PVariant);

public slots:
    PVariant action(PVariant action);
    void onChangeField(QString fieldName, PVariant fieldValue);

};

Q_DECLARE_METATYPE(PMPlus4Log*)


class Plus4LogManager {

public:
    static void $log(QString action:, QString model_name:, QString id_value:) {

        source_args["user_name"] = PSinglUserManager::instance()->userName;

        $PSql().insert("plus4_log", source_args);

    }

};


#endif // PMPLUS4_LOG_H
