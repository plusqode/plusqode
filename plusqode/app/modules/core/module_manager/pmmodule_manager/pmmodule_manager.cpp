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

#include "app/modules/core/module_manager/pmmodule_manager/pmmodule_manager.h"
#include "widgets/sqlview/psqlformviewdialog.h"
#include "misc/pprofilemanager.h"

PMModuleManager::$PMModuleManager() {

    init(args);

}

PMModuleManager& PMModuleManager::init(PVariant args) {

    PModel::init(args);

    name$ = $pt(main: true, mandatory: true);

    icon$ = $pt();
    
    enabled$ = $pb(default: psql->db_false(), fieldType: "switch_edit");

    QString uninstallButton =
    "<menusection name='Uninstall'>"
       "<menuitem action='Uninstall' icon=\"{name: 'picons/core/actions/delete.png', width:48, height: 48}\"/>"
    "</menusection>";

    uninstall_button$ = $pw(xml: uninstallButton);
    
    author$ = $pt(fieldType: "plain_text_edit", readOnly: true);

    description$ = $pt(fieldType: "plain_text_edit", readOnly: true);

    web_site$ = $pt(default: "www.plusqode.com", fieldType: "label", link: true);

    tutorial$ = $pt(default: "<a href='youtu.be/zxvQA1izmVo?si=u3v11QsItechrseS'>click</a>",
                    fieldType: "label",
                    link: true);

    manual$ = $pt(fieldType: "label", pdf: true);

    return *this;

}


void PMModuleManager::onAfterWidget() {

    PImage image(icon$s);
    image = image.scaled(QSize(100, 100), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    $<QLabel*>("logo1Label")->setPixmap(image.toPixmap());
    $<QLabel*>("logo2Label")->setPixmap(image.toPixmap());
    $<QLabel*>("logo3Label")->setPixmap(image.toPixmap());

}


void PMModuleManager::uninstall() {

    QStringList hh = PDir($"${PGlobal::modulePath()}/${this->name$s}").$onlyFullFiles("PM*.h");
    PVariant h = $[];
    $$hh.foreach(PString fileName) {
        fileName.remove($"${PGlobal::basePath()}/");
        h << fileName;
    }

    QStringList cc = PDir($"${PGlobal::modulePath()}/${this->name$s}").$onlyFullFiles("PM*.cpp");
    PVariant c = $[];
    $$cc.foreach(PString fileName) {
        fileName.remove($"${PGlobal::basePath()}/");
        c << fileName;
    }

    PProFileManager headerManger("HEADERS");
    $h.forEach(QString fileName) {
        headerManger.remove(fileName);
    }
    headerManger.save();

    PProFileManager sourceManager("SOURCES");
    $c.forEach(QString fileName) {
        sourceManager.remove(fileName);
    }
    sourceManager.save();

    PDir::remove($"${PGlobal::modulePath()}/${this->name$s}");

    PMModuleManager $mm();
    mm.$removeOnDB(where: {name: name$s});

}


PVariant PMModuleManager::action(PVariant action) {

    qDebug() << action.toString() << "\n";

    if(action.action$s == "Uninstall") {
        this->uninstall();
        return ${type: "message_box", 
                 icon: "picons/core/actions-128/ok.png",
                 description: $"${this->name$s} removed"};
    }

    if(action.action$s == "disableAllModules") {
        $PSql().update("module_manager", ${enabled: false}, ${});
        $PSql().update("module_manager", ${enabled: true},  ${name: ["module_manager", "quit"]});
        return ${type: "message_box",
                 icon: "picons/core/actions-128/ok.png",
                 description: $"${this->name$s} removed"};
    }

    return false;

}
