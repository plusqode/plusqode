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

#include "app/modules/core/pmprofile/pmprofile.h"

PMProfile::$PMProfile() {

    init(args);

}

PMProfile& PMProfile::init(PVariant args) {

    PModel::init(args);

    name$ = $pt(mandatory: true);
    
    profile_module_table$ = $pa();

    profile_model_table$ = $pa();

    return *this;

}



PVariant PMProfile::action(PVariant button) {

    if(button.action$s == "setDeveloperMode") {
        PSinglUserManager::instance()->developerMode = true;
        return ${type: "message_box", description: "Developer Mode Activated !!!", icon: "picons/core/actions-128/settings.png"};
    }

    return nil;

}
