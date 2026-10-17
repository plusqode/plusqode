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



   #include "widgets/sqlview/psqlviewtabwidget.h"

   
   
   #include "app/modules/pmodules.h"

   
   
   
   
   
 

PSqlViewTabWidget::PSqlViewTabWidget(const QString& modelName, PVariant views,  QWidget* parent) :
    QTabWidget(parent) {

    PVariant viewList = PVariant::fromString(views.undefined("views", nil).undefined("value", nil).toString());

    if(viewList == nil) viewList = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("table")))));

    this->setTabPosition(QTabWidget::East);
    
    

       viewList.forEachWithIndexQString_int([&] (QString viewType,int i) mutable {
        PSqlView* sqlView = 0;
        QWidget* subTab = new QWidget(this);
        PWidgetAttrs::setBackgroundColor(subTab, PGlobal::windowColor());

        
        this->addTab(subTab, "");
        QGridLayout* subGridLayout = new QGridLayout(subTab);
        if(viewType == "table") {
            this->setTabIcon(i, QIcon(":/picons/core/views/table-view.png"));
            PSqlGroupTableView* sqlTableView = new   
                                                                          PSqlGroupTableView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("controlPanel", views.   
                                                                        undefined("table", nil).   
                                                                        undefined("showControlPanel", nil))->append("parent",    
                                                                          QVariant::fromValue(subTab))))));
            
            sqlView = sqlTableView;
            subGridLayout->addWidget(sqlTableView, 0, 0);
        }
        else if(viewType == "icon") {
            this->setTabIcon(i, QIcon(":/picons/core/views/icon-view.png"));
            PSqlIconView* sqlIconView = new   
                                                             PSqlIconView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("showControlPanel", views.   
                                                           undefined("icon", nil).   
                                                           undefined("showControlPanel", nil))->append("parent",    
                                                             QVariant::fromValue(subTab))))));
            sqlView = sqlIconView;
            subGridLayout->addWidget(sqlIconView, 0, 0);
        }
        else if(viewType == "tab") {
            this->setTabIcon(i, QIcon(":/picons/core/views/icon-view.png"));
            PSqlTabView* sqlTabView = new   
                                                          PSqlTabView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("showControlPanel", views.   
                                                        undefined("tab", nil).   
                                                        undefined("showControlPanel", nil))->append("parent",    
                                                          QVariant::fromValue(subTab))))));
            sqlView = sqlTabView;
            subGridLayout->addWidget(sqlTabView, 0, 0);
            sqlView->reload();
        }
        else if(viewType == "form") {
            this->setTabIcon(i, QIcon(":/picons/core/views/form-view.png"));
            PModelPtr modelPtr = PModules:: newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)))));
            modelPtr->setParent(this);
            modelPtr->find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

            PMandatoryField* mandatoryField = new PMandatoryField(this);

            PSqlFormView* sqlFormView = new PSqlFormView(modelPtr, "edit", mandatoryField, views.undefined("form", nil));
            sqlView = sqlFormView;
            modelPtr->sqlView = sqlFormView;

            subGridLayout->addWidget(sqlFormView, 2, 0);

            PVariant viewVariant = modelPtr-> getView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("form"))))));

            if(viewVariant.undefined("attrs", nil). undefined("pagination", nil) ==  nil) {
                PSqlPagination* sqlPagination = new  
                                                                     
                                                                     
                                                                     PSqlPagination(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelPtr",   QVariant::fromValue(modelPtr))->append("rowsForPage", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(1)))))->append("defaultIndex", 0)->append("parent",   
                                                                     
                                                                     
                                                                     QVariant::fromValue(parent))))));
                subGridLayout->addWidget(sqlPagination, 1, 0);

                connect(sqlPagination, SIGNAL(currentPageChanged(int)), sqlFormView, SLOT(onChangeRecord(int)));
            }

        }

        connect(this, SIGNAL(currentChanged(int)), sqlView, SLOT(reload()));

        PSinglUserManager::instance()->applyProfile(subTab, modelName);

    });

}
