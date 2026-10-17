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

   
   
   #include "app/modules/pmodules.h"

   
   
   
   
   
 

PTabNavigation::PTabNavigation(QWidget *parent) : QTabWidget(parent) {

    leftMenuWidth = 200;

    this->setStyleSheet(PString(QString("QTabBar::tab {height: 40px; background-color: '%1'}").arg(PGlobal::windowColor())));

    this->setIconSize(QSize(32, 32));

    this->modules = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    this->moduleNameMap = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    this->moduleNames = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    PVariant names = PGlobal::menus();

    

    PMModuleManager moduleManager(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    moduleManager.findBy();
    PVariant mods = moduleManager.psql->column("name");

    

    PLog().debug() << names.toString();for(int pos = 0; pos < names.count(); pos++) {
PVariant module = names.operator[](pos);

        QString moduleName = module.undefined("moduleName", nil).toString();
        QString viewFileName = module.undefined("viewFileName", nil).toString();

        PView view;
        view.initByFileName(viewFileName);
        PVariant menu = view.toVariant();
        modules[moduleName] = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("menu", menu))));

        QString modulePosition = QVariant(pos).toString();
        QString moduleLabel = moduleName;
        QString moduleIcon;
        QString moduleAuthor;
        QString moduleDescription;
        PVariant moduleTag = view.  findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("module"))))))))));
        PVariant attrs = moduleTag.undefined("", nil).undefined("attrs", nil);
        if(moduleTag.count()) {
            moduleLabel = attrs.undefined("name", nil).toString();
            modulePosition = attrs.undefined("position", nil).toString();
            moduleIcon = attrs.undefined("icon", nil).toString();
            PVariant author = PVariant::fromString(attrs.undefined("author", nil).toString());
            moduleAuthor = PString(QString("%1\n%2").arg(author.undefined("name", nil).toString()).arg(author.undefined("address", nil).toString()));
            moduleDescription = attrs.undefined("description", nil).toString();
        }
        else
            PLog().debug() << "module tag in menu_view.xml not found !!!";

        moduleNameMap[PTranslator::tr(moduleLabel)] = moduleName;

        this->moduleNames << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("moduleName", moduleName)->append("moduleLabel", moduleLabel)->append("position", modulePosition)->append("attrs", attrs))));

        if(!mods.include(moduleName))
            moduleManager. 
                                       
                                       
                                       
                                       
                                       
                                       
                                       createOnDb(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", moduleName)->append("icon", moduleIcon)->append("description", moduleDescription)->append("author", moduleAuthor)->append("web_site", attrs. 
                                       
                                       
                                       
                                       undefined("website", nil))->append("tutorial", attrs. 
                                       
                                       
                                       
                                       
                                       undefined("tutorial", nil))->append("manual", attrs. 
                                       
                                       
                                       
                                       
                                       
                                       undefined("manual", nil))->append("enabled",  
                                       
                                       
                                       
                                       
                                       
                                       
                                       moduleManager.psql->db_true())))));

    }

    moduleNames =    moduleNames.sortPVariant_PVariant([&] (PVariant a,PVariant b) mutable { return a.undefined("position", nil).toInt() < b.undefined("position", nil).toInt(); });

     moduleNames.forEachPVariant([&] (PVariant module) mutable {

        QString moduleName = module.undefined("moduleName", nil).toString();
        QString moduleLabel = module.undefined("moduleLabel", nil).toString();

        QWidget* tab = new PWidget(this);

        if(!module.undefined("moduleIcon", nil).toString().isNull())
            addTab(tab, QIcon(module.undefined("moduleIcon", nil).toString()), PTranslator::tr(moduleLabel));
        else
            addTab(tab, PTranslator::tr(moduleLabel));

        QGridLayout* mainLayout = new QGridLayout(tab);
        mainLayout->setContentsMargins(0,0,0,0);
        tab->setObjectName(moduleName + "Tab");
        connect(tab, SIGNAL(doubleClicked()), this, SLOT(onWidgetDoubleClicked()));

        PSinglUserManager::instance()->tabNavigation = this;

        QGridLayout* gridLayout = new QGridLayout();
        mainLayout->addLayout(gridLayout, 0, 1);

        modules[moduleName].  undefined("label=", moduleLabel);
        modules[moduleName].  undefined("tab=", QVariant::fromValue(tab));
        modules[moduleName].  undefined("gridLayout=", QVariant::fromValue(gridLayout));
        modules[moduleName].  undefined("mainLayout=", QVariant::fromValue(mainLayout));

        PMainView* mainView = new PMainView(module);
        mainLayout->addWidget(mainView, 0, 1);

    });

    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onChangeTab(int)));

}

PTabNavigation::~PTabNavigation() {

    PLog().debug() << "PTabNavigation::~PTabNavigation";

}


QString PTabNavigation::currentModuleName() {

    QString moduleName = tabText(currentIndex());
    return moduleNameMap[moduleName].toString();

}

QTreeWidget* PTabNavigation::treeWidget(const QString& moduleName) {

    PVariant menu = modules[moduleName].undefined("menu", nil);

    QTreeWidget* treeWidget = new QTreeWidget();
    treeWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));

    connect(treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(onClickLeftMenu()));
    treeWidget->headerItem()->setText(0, "PlusQode");
    treeWidget->setAlternatingRowColors(true);

    treeWidget->insertTopLevelItems(0, this->leftMenu(menu));
    treeWidget->setMaximumWidth(this->leftMenuWidth);

    return treeWidget;

}


void PTabNavigation::onWidgetDoubleClicked() {

    QString moduleName = currentModuleName();

    QTreeWidget* treeWidget = modules[moduleName]["treeWidget"].value<QTreeWidget*>();

    if(treeWidget == 0)
        return;

    if(treeWidget->maximumWidth() == 0)
        treeWidget->setMaximumWidth(this->leftMenuWidth);
    else
        treeWidget->setMaximumWidth(0);

}



QList<QTreeWidgetItem*> PTabNavigation::leftMenu(PVariant& menu) {

    QList<QTreeWidgetItem*> items;

    if(menu == nil)
        return items;

    QString label = PTranslator::tr(menu.undefined("attrs", nil).undefined("name", nil).toString());

    if(menu.typeName() == "Hash" && menu. undefined("name", nil) ==  "menuitem") {
        PVariant ref = PVariant::fromString(menu.undefined("attrs", nil).undefined("ref", nil).toString());
        PModelPtr modelProfile = PSinglUserManager::instance()->modelProfile(ref.undefined("modelName", nil).toString());
        if(!modelProfile.isNull() and modelProfile->undefined("menu", nil).toBool() == false) return items;

        QTreeWidgetItem* widgetItem = new QTreeWidgetItem(QStringList(label));
        if(menu.undefined("attrs", nil).undefined("icon", nil).toString() != nil) widgetItem->setIcon(0, QIcon(menu.undefined("attrs", nil).undefined("icon", nil).toString()));
        widgetItem->setData(0, Qt::UserRole, menu.undefined("attrs", nil).undefined("ref", nil));
        widgetItem->setSizeHint(0, QSize(0, 30));
        items.append(widgetItem);
    }
    else if(menu.typeName() == "Hash" && menu. undefined("name", nil) ==  "menusection") {
        QTreeWidgetItem* widgetItem = new QTreeWidgetItem(QStringList(label));
        if(menu.undefined("attrs", nil).undefined("icon", nil).toString() != nil) widgetItem->setIcon(0, QIcon(menu.undefined("attrs", nil).undefined("icon", nil).toString()));
        widgetItem->setData(0, Qt::UserRole, menu.undefined("attrs", nil).undefined("ref", nil));
        widgetItem->setSizeHint(0, QSize(0, 30));
        items.append(widgetItem);
        widgetItem->addChildren(leftMenu(menu["children"]));
    }

    else if(menu.typeName() == "Array") {
         menu.forEachPVariant([&] (PVariant item) mutable {
            items.append(leftMenu(item));
        });
    }

    return items;

}




void PTabNavigation::onClickLeftMenu() {

    QTreeWidgetItem* item = modules[currentModuleName()]["treeWidget"].value<QTreeWidget*>()->selectedItems()[0];
    QString refStr = item->data(0, Qt::UserRole).toString();

    if(refStr == "") return;
    PVariant ref = PVariant::fromString(refStr);

    if(ref.include("modelName")) {
        showSqlView(ref);
    }


}


PVariant PTabNavigation::viewList(PVariant ref) {

    QString modelName = ref.undefined("modelName", nil).toString();

    PViewLoader viewLoader;

    PModel* model = PModules:: newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)))));

    PView* view = viewLoader.view(model->getModuleName(), modelName);

    if(!view) return nil;

    PVariant viewVariant = view->toVariant();

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

     viewVariant.forEachPVariant([&] (PVariant v) mutable {
        v.undefined("attrs", nil).  undefined("ref=", ref);
        if(v.undefined("name", nil).toString() == "view")
            result[v.undefined("attrs", nil).undefined("type", nil).toString()] = v.undefined("attrs", nil);

    });

    delete model;

    return result;

}


void PTabNavigation::showSqlView(PVariant ref) {

    QString modelName = ref.undefined("modelName", nil).toString();

    
    if(modules[currentModuleName()]. undefined("subTabWidget", nil)!= nil)
        delete modules[currentModuleName()]["subTabWidget"].value<PSqlViewTabWidget*>();

    PVariant views = viewList(ref);

    QWidget* tab = modules[currentModuleName()]["tab"].value<QWidget*>();
    PSqlViewTabWidget* subTabWidget = new PSqlViewTabWidget(modelName, views, tab);

    modules[currentModuleName()]["subTabWidget"] = QVariant::fromValue(subTabWidget);
    modules[currentModuleName()]["gridLayout"].value<QGridLayout*>()->addWidget(subTabWidget, 0, 0);

}

void PTabNavigation::treeWidgetClean() {

       modules.forEachQString_PVariant([&] (QString moduleName,PVariant var) mutable {
        delete var.undefined("treeWidget", nil).value<QTreeWidget*>();
        delete var.undefined("subTabWidget", nil).value<PSqlViewTabWidget*>();
        var.  undefined("treeWidget=", nil);
        var.  undefined("subTabWidget=", nil);
    });

}

void PTabNavigation::onChangeTab(int tabIndex) {

    QString moduleName = currentModuleName();

    PSinglTelemetry::instance()->onChangeModule(moduleName);

    QGridLayout* mainLayout = modules[moduleName]["mainLayout"].value<QGridLayout*>();

    if(modules[moduleName]. undefined("treeWidget", nil)!= nil) return;
    

    QTreeWidget* tw = treeWidget(moduleName);
    modules[moduleName].  undefined("treeWidget=", QVariant::fromValue(tw));
    tw->setMaximumWidth(this->leftMenuWidth);

    mainLayout->addWidget(tw, 0, 0);

}


void PTabNavigation::paintEvent(QPaintEvent*) {

    setGeometry(0, 0, parentWidget()->width(), parentWidget()->height());
    QString moduleName = currentModuleName();

}
