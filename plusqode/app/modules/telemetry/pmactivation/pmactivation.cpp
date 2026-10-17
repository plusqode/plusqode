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

#include "app/modules/telemetry/pmactivation/pmactivation.h"
#include "app/modules/pmodules.h"

PMActivation::$PMActivation() {

    init(args);

}

PMActivation& PMActivation::init(PVariant args) {

    PModel::init(args);

    this->autoView = false; // false if you want to use pmactivation_view.xml

    // It's a just an example about different fields

    name$ = $pt(); // installation id
    version$ = $pt();
    activation_date$ = $pd();
    last_start_date$ = $pd();
    os_name$ = $pt();
    os_type$ = $pt();
    os_version$ = $pt();
    architecture$ = $pt();
    language$ = $pt();
    total_sessions$ = $pi();
    total_minutes$ = $pi();
    client_id$ = $pt();
    module_usages$ = $pt(fieldType: "plain_text_edit");

    return *this;

}


PVariant PMActivation::action(PVariant action) {

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


void PMActivation::onChangeField(QString fieldName, PVariant fieldValue) {

    qDebug() << fieldName << fieldValue.toString();

}


PVariant PMActivation::$handleRequest(QString command:, PVariant payload:) {

    qDebug() << "PModel::$handleRequest - > " << command << payload.toString();
    return ${available: true, message: 'Congratulation by PlusQode'};

}
