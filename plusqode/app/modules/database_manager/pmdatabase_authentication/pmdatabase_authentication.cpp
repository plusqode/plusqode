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
#include "app/modules/database_manager/pmdatabase_authentication/pmdatabase_authentication.h"
#include "app/modules/core/pmmessage_box/pmmessage_box.h"

PMDatabaseAuthentication::$PMDatabaseAuthentication() {

    init(args);

}

PMDatabaseAuthentication& PMDatabaseAuthentication::init(PVariant args) {

    PModel::init(args + ${generate: false});

    password$ = $pt(password: true, main: true);

    return *this;

}

void PMDatabaseAuthentication::onAfterWidget() {

    sqlFormViewDialog->cancelButton->setHidden(true);

}


bool PMDatabaseAuthentication::onOkDialog() {

/*
    PDatabaseManager* um = PSinglDatabaseManager::instance();

    PMMessageBox $messageBox();
    messageBox.initDialog();
        
    PMDatabaseManager $userManager();
    userManager.findBy_password$(password$s);
    password$ = "";

    if(userManager.count() == 0) {
        messageBox.setText("Wrong Password !!!");
        messageBox.setPixmap("picons/core/actions-128/stop.png");
        messageBox.exec();
        return false;
    }

    QString username = userManager.username$s;

    um->userName = userManager.username$s;
    um->userProfileId = userManager.profile_id$->id$s;
    um->userId = userManager.id$s;

    messageBox.setText($"Welcome ${username}");
    messageBox.setPixmap("picons/core/actions-128/ok.png");
    messageBox.exec();

    PSinglDatabaseManager::instance()->tabNavigation->setCurrentIndex(0);
*/
    return true;
}

bool PMDatabaseAuthentication::onCancelDialog() {

    // avoid to close the window
    return false;

}




