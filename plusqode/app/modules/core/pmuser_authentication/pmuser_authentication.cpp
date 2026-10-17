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

#include "widgets/ptabnavigation.h"
#include "app/modules/core/pmuser_authentication/pmuser_authentication.h"
#include "app/modules/core/pmprofile/pmprofile.h"
#include "app/modules/core/pmuser_manager/pmuser_manager.h"
#include "app/modules/core/pmmessage_box/pmmessage_box.h"

PMUserAuthentication::$PMUserAuthentication() {

    init(args);

}

PMUserAuthentication& PMUserAuthentication::init(PVariant args) {

    PModel::init(args + ${generate: false});

    password$ = $pt(password: true, main: true);

    return *this;

}

void PMUserAuthentication::onAfterWidget() {

    sqlFormViewDialog->cancelButton->setHidden(true);

}


bool PMUserAuthentication::onOkDialog() {

    PUserManager* um = PSinglUserManager::instance();

    PMUserManager $userManager();
    userManager.findBy_password$(password$s);
    password$ = "";

    if(userManager.count() == 0) {
        PMMessageBox::$messageBox(text: "Wrong Password !!!", icon: "picons/core/actions-128/stop.png");
        return false;
    }

    QString username = userManager.username$s;

    um->userName = userManager.username$s;
    um->userProfileId = userManager.profile_id$->id$s;
    um->userId = userManager.id$s;

    QString welcome = $"Welcome ${username}";
    PMMessageBox::$messageBox(text: welcome, icon: "picons/core/actions-128/ok.png");

    PSinglUserManager::instance()->tabNavigation->setCurrentIndex(0);

    return true;

}


bool PMUserAuthentication::onCancelDialog() {

    // avoid to close the window
    return false;

}




