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

#include "app/modules/pbx/pmpbx_phone_number_join/pmpbx_phone_number_join.h"
#include "app/modules/pmodules.h"

PMPbxPhoneNumberJoin::$PMPbxPhoneNumberJoin() {

    init(args);

}

PMPbxPhoneNumberJoin& PMPbxPhoneNumberJoin::init(PVariant args) {

    PModel::init(args);

    this->autoView = false; // false if you want to use pmpbx_phone_number_join_view.xml

    pbx_phone_number_id$ = $pa();

    pbx_phone_number_ptr_id$ = $pm2o(modelName: "pbx_phone_number", onDelete: "cascade", mandatory: true, newButton: false, editButton: false, editable: true);

    ivr_key$ = $pt(toolTip: "leave blank if you don't need an IVR(Interactive Voice Response)");

    return *this;

}


PVariant PMPbxPhoneNumberJoin::action(PVariant action) {

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


void PMPbxPhoneNumberJoin::onChangeField(QString fieldName, PVariant fieldValue) {

    qDebug() << fieldName << fieldValue.toString();

}


PVariant PMPbxPhoneNumberJoin::$handleRequest(QString command:, PVariant payload:) {

    qDebug() << "PModel::$handleRequest - > " << command << payload.toString();
    return ${available: true, message: 'Congratulation by PlusQode'};

}
