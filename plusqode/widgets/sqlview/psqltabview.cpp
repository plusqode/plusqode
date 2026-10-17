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






   #include "widgets/sqlview/psqltabview.h"




   



   
   #include "app/modules/pmodules.h"




   



   
   



   
   
 

Q_DECLARE_METATYPE(QTabWidget*)
Q_DECLARE_METATYPE(PTabWidget*)

PSqlTabView::PSqlTabView(PVariant args) {

    this->init(args);

}

PSqlTabView::~PSqlTabView() {

}

void PSqlTabView:: init(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "init:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString moduleName = source_args.value<PVariantMapPtr>()->include("moduleName") ? source_args.value<PVariantMapPtr>()->operator[]("moduleName").toString() : QVariant(nil).toString();args.removeByKey("moduleName");
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
PVariant attrs = source_args.value<PVariantMapPtr>()->include("attrs") ? source_args.value<PVariantMapPtr>()->operator[]("attrs") : nil;args.removeByKey("attrs");
PVariant filter = source_args.value<PVariantMapPtr>()->include("filter") ? source_args.value<PVariantMapPtr>()->operator[]("filter") : nil;args.removeByKey("filter");
PVariant sortField = source_args.value<PVariantMapPtr>()->include("sortField") ? source_args.value<PVariantMapPtr>()->operator[]("sortField") : nil;args.removeByKey("sortField");
QString pageSize = source_args.value<PVariantMapPtr>()->include("pageSize") ? source_args.value<PVariantMapPtr>()->operator[]("pageSize").toString() : QVariant(QString("all")).toString();args.removeByKey("pageSize");
int page = source_args.value<PVariantMapPtr>()->include("page") ? source_args.value<PVariantMapPtr>()->operator[]("page").toInt() : QVariant(0).toInt();args.removeByKey("page");
PModelPtr model = source_args.value<PVariantMapPtr>()->operator[]("model").value<PModelPtr>();
args.removeByKey("model");
QString connectionName = source_args.value<PVariantMapPtr>()->include("connectionName") ? source_args.value<PVariantMapPtr>()->operator[]("connectionName").toString() : QVariant(QString("default")).toString();args.removeByKey("connectionName");
bool showControlPanel = source_args.value<PVariantMapPtr>()->include("showControlPanel") ? source_args.value<PVariantMapPtr>()->operator[]("showControlPanel").toBool() : QVariant(true).toBool();args.removeByKey("showControlPanel");
bool totalizerPanel = source_args.value<PVariantMapPtr>()->include("totalizerPanel") ? source_args.value<PVariantMapPtr>()->operator[]("totalizerPanel").toBool() : QVariant(false).toBool();args.removeByKey("totalizerPanel");
bool showFilterPanel = source_args.value<PVariantMapPtr>()->include("showFilterPanel") ? source_args.value<PVariantMapPtr>()->operator[]("showFilterPanel").toBool() : QVariant(true).toBool();args.removeByKey("showFilterPanel");
QWidget* parent = source_args.value<PVariantMapPtr>()->include("parent") ? source_args.value<PVariantMapPtr>()->operator[]("parent").value<QWidget*>() : 0;
args.removeByKey("parent");


    QWidget::setParent(parent);
    this->showControlPanel = showControlPanel;
    this->modelName = modelName;
    this->attrs = attrs;
    this->sortField = sortField;

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0,0,0,0);

    if(model.model == 0) {
        PVariant domain = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
        if(attrs != nil and attrs != nil and attrs. undefined("ref", nil)!= nil and attrs.undefined("ref", nil). undefined("domain", nil)!= nil)
            domain = attrs.undefined("ref", nil).undefined("domain", nil);
        model = PModules::   newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("domain", domain)))));
        model->setParent(this);
        model->find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    }

    if(this->sortField == nil) {
        QString s = model->sortField.toString();
        this->sortField = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( s, QString("asc")))));
    }

    this->model = model;

    if(attrs. undefined("subModelName", nil)!= nil)
        this->subModelName = attrs.undefined("subModelName", nil).toString();
    if(attrs. undefined("subViewType", nil)!= nil)
        this->subViewType = attrs.undefined("subViewType", nil).toString();

    if(attrs. undefined("subModelName", nil) ==  nil)
        initSubModelFromView();

    model->sqlView = this;

    tabWidget = new PTabWidget(this);
    gridLayout->addWidget(tabWidget, 3, 0);

    connect(tabWidget, SIGNAL(doubleClicked()), this, SLOT(onDoubleClicked()));

}


void PSqlTabView::initSubModelFromView() {

    PVariant viewVariant = model-> getView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("tab"))))));

    this->subModelName = viewVariant.undefined("attrs", nil).undefined("subModelName", nil).toString();
    if(this->subModelName.isNull()) {
        PLog().error() << "PSqlTabView::$init(): missed subModelName";
        PLog().error() << attrs.toString();
        exit(0);
    }

    this->subViewType = viewVariant.undefined("attrs", nil).undefined("subViewType", nil).toString();
    if(this->subViewType.isNull()) {
        PLog().error() << "PSqlTabView::$init(): missed subViewType";
        exit(0);
    }

}


PVariant PSqlTabView::data() {

    return nil;

}

void PSqlTabView::setData(PVariant data) {

    reload();

}

void PSqlTabView::setBackgroundColor(QString color) {

}


bool PSqlTabView::isEmpty() {

    return model->count() == 0;

}


void PSqlTabView::onEditingFinished() {

    this->reload();

    emit editingFinished(fieldName, QVariant::fromValue(model));

}


void PSqlTabView::onDoubleClicked() {

    model->onClick( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("action", QString("edit"))))));

    PLog().error() << " - - - - - - >";

}


void PSqlTabView::reload() {

    while(tabWidget->count() > 0) {
        QWidget* tw = tabWidget->widget(0);
        tabWidget->removeTab(0);
        if(tw) tw->deleteLater();
    }




    if(model->level == 0) {
        
        model-> findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("orderBy", this->sortField)))));
        
    }

    QVariant newId = model->undefined("id", nil);

    if(newId == nil) return;

    int newRow = -1;

       model->forEachPModelPtr_int([&] (PModelPtr rec,int r) mutable {

        QVariant id = rec->undefined("id", nil);
        PVariant showField = model->showField;
        QString name = model->fieldValue(showField.toString()).toString();

        if(showField.typeName() == "Array") {
            PVariant item = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
             showField.forEachQString([&] (QString fieldName) mutable { item << model->fieldValue(fieldName).toString(); });
            name = item.join(" - ");
        }

        QString icon = rec->undefined("icon", nil).toString();

        PModelPtr subModelPtr = model->undefined(this->subModelName, nil).value<PModelPtr>();
        PModelPtr subPtr = PModel   ::model(this->subModelName.split("_table")[0]);
        subPtr->setParent(this);
        if(subModelPtr != nil) subPtr->domain = subModelPtr->domain;
        subPtr->find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

        PSqlView* sqlView = 0;

        if(this->subViewType == "icon") {
            
            
            sqlView = new  
                                        
                              
                                        PSqlIconView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("model",   subPtr.toVariant())->append("showControlPanel", showControlPanel)->append("parent",   
                                        
                              
                                        QVariant::fromValue(tabWidget))))));
        }
        else if(this->subViewType == "table") {
            
            
            sqlView = new  
                                              
                                    
                                    PSqlGroupTableView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("model",   subModelPtr.toVariant())->append("showControlPanel", showControlPanel)->append("parent",   
                                              
                                    
                                    QVariant::fromValue(tabWidget))))));
        }

        if(icon.isEmpty())
            tabWidget->addTab(sqlView, PTranslator::tr(name));
        else
            tabWidget->addTab(sqlView, QIcon(icon), PTranslator::tr(name));

    });

}


PVariant PSqlTabView::idSelectionList() {

    return nil;
}


PVariant PSqlTabView::selectedRows() {

    return nil;
}


void PSqlTabView::selectItem(int row) {



}

void PSqlTabView::selectLastItem() {



}


int PSqlTabView::count() {


    return 0;

}

void PSqlTabView::itemSelectionChanged() {

}
