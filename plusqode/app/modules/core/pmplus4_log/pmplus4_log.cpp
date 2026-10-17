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

#include "app/modules/core/pmplus4_log/pmplus4_log.h"
#include "app/modules/pmodules.h"

PMPlus4Log::$PMPlus4Log() {

    init(args);

}

PMPlus4Log& PMPlus4Log::init(PVariant args) {

    PModel::init(args);

    this->mainField = "timestamp";

    this->autoView = false; // false if you want to use pmplus4_log_view.xml

    timestamp$ = $pdt(default: psql->current('timestamp'));
    user_name$ = $pt();
    action$ = $pt();
    model_name$ = $pt();
    id_value$ = $pt();

    return *this;

}


PVariant PMPlus4Log::action(PVariant action) {

    if(action.action$s == "print") {
       POpenUrl::writeHtml($"pos/generic", "xxx", this->html());
       return true;
    }
    else if(action.action$s == "action_name1")
        ;
    else if(action.action$s == "action_name2")
        ;
    return ${type: "message_box", description: "apply successfully", icon: "picons/core/actions-128/ok.png"};

}


void PMPlus4Log::onChangeField(QString fieldName, PVariant fieldValue) {

    qDebug() << fieldName << fieldValue.toString();

}
