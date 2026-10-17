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




   #include "misc/pusermanager.h"


   

   
   #include "widgets/ptabnavigation.h"


   

   
   

   
   
 
   #include "app/modules/core/pmprofile/pmprofile.h"


   

   
   

   
   
 
   

   
   
 
   
 
 
   #include "app/modules/core/pmprofile_model/pmprofile_model.h"


   

   
   

   
   
 
   

   
   
 
   
 
 
   

   
   
 
   
 
 
   
 
 
 
   #include "app/modules/core/pmprofile_module/pmprofile_module.h"


   

   
   

   
   
 
   

   
   
 
   
 
 
   

   
   
 
   
 
 
   
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   #include "app/modules/core/pmprofile_model_widget/pmprofile_model_widget.h"


   

   
   

   
   
 
   

   
   
 
   
 
 
   

   
   
 
   
 
 
   
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   
 
 
 
 
 
   #include "app/modules/core/pmuser_authentication/pmuser_authentication.h"


   

   
   

   
   
 
   

   
   
 
   
 
 
   

   
   
 
   
 
 
   
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   
 
 
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   
 
 
 
 
 
   
 
 
 
 
 
 
   #include "app/modules/core/module_manager/pmmodule_manager/pmmodule_manager.h"


   

   
   

   
   
 
   

   
   
 
   
 
 
   

   
   
 
   
 
 
   
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   
 
 
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   
 
 
 
 
 
   
 
 
 
 
 
 
   

   
   
 
   
 
 
   
 
 
 
   
 
 
 
 
   
 
 
 
 
 
   
 
 
 
 
 
 
   
 
 
 
 
 
 
 

PUserManager::PUserManager() {

    this->developerMode = false;

}

PModelPtr PUserManager::modelProfile(const QString& modelName) {

    if(userProfileId.isNull()) return PModelPtr();

    PMProfile profile(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    profile.undefined("findBy_id", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(userProfileId)))));

    if(profile.count() == 0) return PModelPtr();

    PModelPtr profileModel = profile.undefined("profile_model_table", nil).value<PModelPtr>().value<PMProfileModel*>()-> find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("model_name", modelName)))));

    if(profileModel->count() == 0) return PModelPtr();

    return profileModel;

}

PModelPtr PUserManager::moduleProfile(const QString& moduleName) {

    if(userProfileId.isNull()) return PModelPtr();

    PMProfile profile(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    profile.undefined("findBy_id", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(userProfileId)))));

    if(profile.count() == 0) return PModelPtr();

    PModelPtr profileModule = profile.undefined("profile_module_table", nil).value<PModelPtr>().value<PMProfileModule*>()-> find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", moduleName)))));

    if(profileModule->count() == 0) return PModelPtr();

    return profileModule;

}


void PUserManager::applyProfile(QWidget* parent, const QString& modelName) {

    PModelPtr modelProfile = this->modelProfile(modelName);

    if(modelProfile.isNull()) return;

    PModelPtr widgetProfile = modelProfile->undefined("profile_model_widget_table", nil).value<PModelPtr>().value<PMProfileModelWidget*>();



    if(!modelProfile->undefined("up_record", nil).toBool())
        widgetProfile->       create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", 0)->append("name", QString("UpButton"))->append("visible", true)->append("enabled", false)))));
    if(!modelProfile->undefined("down_record", nil).toBool())
        widgetProfile->       create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", 0)->append("name", QString("DownButton"))->append("visible", true)->append("enabled", false)))));
    if(!modelProfile->undefined("new_record", nil).toBool())
        widgetProfile->       create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", 0)->append("name", QString("NewButton"))->append("visible", true)->append("enabled", false)))));
    if(!modelProfile->undefined("edit_record", nil).toBool()) {
        widgetProfile->       create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", 0)->append("name", QString("EditButton"))->append("visible", true)->append("enabled", false)))));

        
        QList<QWidget*> tableViews = parent->findChildren<QWidget*>(PString(QString("%1SqlTableView").arg(modelName)));
        if(tableViews.count()) {
            PSqlTableView* tableView = dynamic_cast<PSqlTableView*>(tableViews[0]);
            tableView->tableWidget->disconnect(SIGNAL(cellDoubleClicked(int, int)));
        }

    }
    if(!modelProfile->undefined("delete_record", nil).toBool())
        widgetProfile->       create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", 0)->append("name", QString("DeleteButton"))->append("visible", true)->append("enabled", false)))));
    if(!modelProfile->undefined("print_record", nil).toBool())
        widgetProfile->       create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", 0)->append("name", QString("PrintButton"))->append("visible", true)->append("enabled", false)))));

     widgetProfile->forEachPVariant([&] (PVariant wp) mutable {
        QList<QWidget*> widgetList = parent->findChildren<QWidget*>(wp.undefined("name", nil).toString());
        
        for(int i = 0; i < widgetList.count(); i++) {
            QWidget* w = dynamic_cast<QWidget*>(widgetList[i]);
            w->setVisible(wp.undefined("visible", nil).toBool());
            w->setEnabled(wp.undefined("enabled", nil).toBool());
        }
    });

}

void PUserManager::addTab(PVariant module, QWidget* tab) {

    if(!module.undefined("attrs", nil).undefined("icon", nil).toString().isNull())
        this->tabNavigation->addTab(tab, QIcon(module.undefined("attrs", nil).undefined("icon", nil).toString()), PTranslator::tr(module.undefined("moduleLabel", nil).toString()));
    else
        this->tabNavigation->addTab(tab, PTranslator::tr(module.undefined("moduleLabel", nil).toString()));

}

void PUserManager::applyModuleProfile() {

    PMModuleManager moduleManager(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

    this->tabNavigation->disconnect();

    this->tabNavigation->clear();

     this->tabNavigation->moduleNames.forEachPVariant([&] (PVariant module) mutable {

        QString moduleName = module.undefined("moduleName", nil).toString();

        moduleManager. find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", moduleName)))));

        if(moduleManager.count() && moduleManager.first().undefined("enabled", nil).toBool()) {

        QWidget* tab = this->tabNavigation->modules[moduleName].undefined("tab", nil).value<QWidget*>();

        PModelPtr moduleProfile = PSinglUserManager::instance()->moduleProfile(moduleName);
        if(!moduleProfile.isNull()) {
            if(moduleProfile->undefined("visible", nil).toBool()) {
                addTab(module, tab);
                tab->setEnabled(moduleProfile->undefined("enabled", nil).toBool());
            }
        }
        else {
            addTab(module, tab);
            tab->setEnabled(true);
        }

        }

    });

    QObject::connect(this->tabNavigation, SIGNAL(currentChanged(int)), this->tabNavigation, SLOT(onChangeTab(int)));

}

void PUserManager::setObjectName(QWidget* widget, const QString& objectName) {

    widget->setObjectName(objectName);

    if(PSinglUserManager::instance()->developerMode)
        widget->setToolTip(objectName);


}

void PUserManager::authenticate() {

    tabNavigation->treeWidgetClean();

    PMUserAuthentication userAuthentication(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    userAuthentication.initDialog();

    userAuthentication.exec();

    applyModuleProfile();

}
