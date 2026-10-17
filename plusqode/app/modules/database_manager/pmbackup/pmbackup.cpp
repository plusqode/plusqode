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

#include "app/modules/database_manager/pmbackup/pmbackup.h"

PMBackup::$PMBackup() {

    init(args);

}

PMBackup& PMBackup::init(PVariant args) {

    PModel::init(args);
    
    name$ = $pt();
    
    QString backupButton =     
    "<menusection name='Backup'>"
       "<menuitem action='Backup' icon=\"{name: 'picons/core/actions-128/db-backup.png', width: 200, height: 100}\"/>"
    "</menusection>";

    backup_button$ = $pw(xml: backupButton);
    
    QString restoreButton =     
    "<menusection name='Restore'>"
       "<menuitem action='Restore' icon=\"{name: 'picons/core/actions-128/db-restore.png', width: 200, height: 100}\"/>"
    "</menusection>";

    restore_button$ = $pw(xml: restoreButton);

    return *this;

}


PVariant PMBackup::fileDialogBackup() {
        
    QFileDialog fileDialog;
    fileDialog.setDirectory("backup");
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setNameFilter("Backup (*.bck)");
    fileDialog.selectFile(QDate::currentDate().toString("yyyy-MM-dd"));
    if(fileDialog.exec() == QDialog::Accepted) 
        return fileDialog.selectedFiles()[0];

    return nil;

}


PVariant PMBackup::fileDialogRestore() {

    QFileDialog fileDialog;
    fileDialog.setDirectory("backup");
    fileDialog.setNameFilter("Backup (*.bck)");
    if(fileDialog.exec() == QDialog::Accepted) 
        return fileDialog.selectedFiles()[0];

    return nil;

}



PVariant PMBackup::action(PVariant action) {
        

    if(action.action$s == "Backup") {

        PVariant fileName = this->fileDialogBackup();
        if(fileName == nil)
            return ${type: "message_box", description: "No Action", icon: "picons/core/actions-128/stop.png"};

        PSinglSqlGenerator::instance().sqlGenerator->dump($"${fileName.toString()}.bck");

        return ${type: "message_box",
                description: $"Backup successfully in ${fileName.toString()}.bck",
                icon: "picons/core/actions-128/ok.png"};

    }

    else if(action.action$s == "Restore") {

        PVariant fileName = this->fileDialogRestore();
        if(fileName == nil)
            return ${type: "message_box", description: "No Action", icon: "picons/core/actions-128/stop.png"};

        QString restoreCommand = PSinglSqlGenerator::instance().sqlGenerator->restore(fileName.toString());

        return ${type: "message_box",
                 description: restoreCommand,
                 icon: "picons/core/actions-128/ok.png"};
    }

    return true;

}
