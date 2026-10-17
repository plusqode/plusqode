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

#include "app/modules/core/module_manager/pmmodule_repository/pmmodule_repository.h"
#include "app/modules/pmodules.h"
#include "widgets/sqlview/psqlformviewdialog.h"
#include "misc/pprofilemanager.h"
#include "misc/pmakedialog.h"
#include "misc/pget.h"


PMModuleRepository::$PMModuleRepository() {

    init(args);

}

PMModuleRepository& PMModuleRepository::init(PVariant args) {

    PModel::init(args);

    name$ = $pt(main: true, mandatory: true);

    icon$ = $pt();
    
    author$ = $pt(fieldType: "plain_text_edit", readOnly: true);

    description$ = $pt(fieldType: "plain_text_edit", readOnly: true);

    web_site$  = $pt(default: "www.plusqode.com", fieldType: "label", link: true);

    tutorial$ = $pt(default: "<a href='youtu.be/zxvQA1izmVo?si=u3v11QsItechrseS'>click</a>",
                    fieldType: "label",
                    link: true);

    manual$ = $pt(fieldType: "label", pdf: true);


    QString installButton =     
    "<menusection name='Install'>"
       "<menuitem action='Install' icon=\"{name: 'picons/core/actions-128/db-import.png', width:48, height: 48}\"/>"
    "</menusection>";

    install_button$ = $pw(xml: installButton);

    return *this;

}


PVariant PMModuleRepository::menus() {

    QString repositoryPath = "app/repository";

    PVariant names = PVariant::fromQStringList(PDir($"${repositoryPath}").$onlyDirectories(recursive: false, onlyFileName: true));

    PVariant result = $[];

    $$names.foreachWithIndex(QString moduleName, int pos) {

        QString viewFileName = $"${repositoryPath}/${moduleName}/menu_view.xml";
        if(QDir().exists(viewFileName))
            result << ${moduleName: moduleName, viewFileName: viewFileName};

    }

    return $result.sort(PVariant a, PVariant b) { return a.moduleName$s < b.moduleName$s; }

}


void PMModuleRepository::onReloadView() {

    QString url("repository.plusqode.com/repository.zip");
    QString outputFileName = "app/repository.zip";

    PGet g("Downloading...", "Abort", 0, 100);
    g.get(url, outputFileName);

    PDir::remove("app/repository");

    PSystem("unzip app/repository.zip -d app");

    QFile::remove("app/repository.zip");

    this->$removeOnDB();

    PVariant modules = ${};

    PVariant names = this->menus();

    // Module Manager

    PMModuleManager $moduleManager();
    moduleManager.findBy();
    PVariant mods = moduleManager.psql->column("name");

    ////////////////////

    PLog().debug() << names.toString();
    
    $$names.foreachWithIndex(PVariant module, int pos) {

        QString moduleName = module.moduleName$s;
        QString viewFileName = module.viewFileName$s;

        PView view;
        view.initByFileName(viewFileName);
        PVariant menu = view.toVariant();
        modules[moduleName] = ${menu: menu};

        QString modulePosition = QVariant(pos).toString();
        QString moduleLabel = moduleName;
        QString moduleIcon;
        QString moduleAuthor;
        QString moduleDescription;
        PVariant moduleTag = view.$findBy(tag: ${name: "module"});
        PVariant attrs = moduleTag.0$.attrs$;
        if(moduleTag.count()) {
            moduleLabel = attrs.name$s;
            modulePosition = attrs.position$s;
            moduleIcon = attrs.icon$s.replace("app/modules", "app/repository");
            PVariant author = PVariant::fromString(attrs.author$s);
            moduleAuthor = $"${author.name$s}\n${author.address$s}";
            moduleDescription = attrs.description$s;
        }
        else
            PLog().debug() << "module tag in menu_view.xml not found !!!";

        //moduleNameMap[moduleLabel] = moduleName;

        //this->moduleNames << ${moduleName: moduleName, moduleLabel: moduleLabel, position: modulePosition, attrs: attrs};

        if(!mods.include(moduleName))
        this->$createOnDb(name: moduleName,
                          icon: moduleIcon,
                          description: moduleDescription,
                          author: moduleAuthor,
                          web_site: attrs.website$,
                          tutorial: attrs.tutorial$,
                          manual: attrs.manual$,
                          enabled: this->psql->db_true());
    }



}



void PMModuleRepository::onAfterWidget() {

    PImage image(icon$s);
    image = image.scaled(QSize(100, 100), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    $<QLabel*>("logo1Label")->setPixmap(image.toPixmap());
    $<QLabel*>("logo2Label")->setPixmap(image.toPixmap());
    $<QLabel*>("logo3Label")->setPixmap(image.toPixmap());

}



void PMModuleRepository::copy(const QString& moduleName) {

    PDir::copy($"app/repository/${moduleName}", $"${PGlobal::modulePath()}");

    PView view;
    QString fileName = $"${PGlobal::modulePath()}/${moduleName}/menu_view.xml";
    view.initByFileName(fileName);

    PVariant depends = view.$findBy(tag: {name: "depends"});
    if(depends.count()) {
        depends = depends.0$.attrs$.modules$;
        depends = depends.split(",");
    }

    qDebug() << "installation ==> " << moduleName;
    qDebug() << "- depends ==> " << depends.toString();

    QStringList hh = PDir($"${PGlobal::modulePath()}/${moduleName}").$onlyFullFiles("PM*.h");
    PVariant h = $[];
    $$hh.foreach(PString fileName) {
        fileName.remove($"${PGlobal::basePath()}/");
        h << fileName;
    }

    QStringList cc = PDir($"${PGlobal::modulePath()}/${moduleName}").$onlyFullFiles("PM*.cpp");
    PVariant c = $[];
    $$cc.foreach(PString fileName) {
        fileName.remove($"${PGlobal::basePath()}/");
        c << fileName;
    }

    PProFileManager headerManger("HEADERS");
    $h.forEach(QString fileName) {
        headerManger.add(fileName);
    }
    headerManger.save();

    PProFileManager sourceManager("SOURCES");
    $c.forEach(QString fileName) {
        sourceManager.add(fileName);
    }
    sourceManager.save();


    $depends.forEach(QString moduleName) {
        if(!moduleName.isEmpty())
            this->copy(moduleName.simplified());
    }

}




void PMModuleRepository::install() {
    
    this->copy(this->name$s);

    QString question = $"Do You Want to compile now or later ?";
    if(PMMessageBox::$messageBox(text: question,
                                 icon: "picons/core/actions-128/stop.png",
                                 ok: true, cancel: true) == QDialog::Accepted) {


        PMakeDialog d(this->sqlFormViewDialog);
        d.resize(600, 600);
        d.show();

        bool turbo = false;
        if(PMMessageBox::$messageBox(text: "Turbo ?",
                                     icon: "picons/core/actions-128/launch.png",
                                     ok: true, cancel: true) == QDialog::Accepted)
            d.startMake(true);
        else
            d.startMake();

        d.exec();
    }

}


PVariant PMModuleRepository::action(PVariant action) {
    
    qDebug() << action.toString() << "\n";

    if(action.action$s == "Install") {
        this->install();
        return ${type: "message_box",
                 icon: "picons/core/actions-128/ok.png",
                 description: $"installation ${this->name$s} successfully"};
    }

    return false;

}
