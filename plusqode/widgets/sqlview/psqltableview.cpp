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




   #include "widgets/sqlview/psqltableview.h"


   

   
   #include "widgets/sqlview/psqltableviewdialog.h"


   

   
   

   
   
 

   #include "widgets/widgetedit/pprogressbar.h"


   

   
   

   
   
 

   

   
   
 

   
 

 
   #include "widgets/widgetedit/pprogressbarplus.h"


   

   
   

   
   
 

   

   
   
 

   
 

 
   

   
   
 

   
 

 
   
 

 
 

   #include "app/modules/pmodules.h"


   

   
   

   
   
 

   

   
   
 

   
 

 
   

   
   
 

   
 

 
   
 

 
 

   

   
   
 

   
 

 
   
 

 
 

   
 

 
 

 


PSqlTableView::PSqlTableView(PVariant args) {

    this->init(args);

}

PSqlTableView::~PSqlTableView() {

}


void PSqlTableView:: init(PVariant source_args) {
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
    this->moduleName = moduleName;
    this->modelName = modelName;
    this->attrs = attrs;
    this->filter = filter;
    this->sortField = sortField;
    this->showFilterPanel = showFilterPanel;

    this->setObjectName(PString(QString("%1SqlTableView").arg(modelName)));

    this->treeWidget = 0;
    this->sqlGroupPanel = 0;
    this->sqlPagination = 0;

    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0,0,0,0);

    if(model.model == 0) {
        PVariant domain = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
        if(attrs != nil and attrs != nil and attrs. undefined("ref", nil)!= nil and attrs.undefined("ref", nil). undefined("domain", nil)!= nil)
            domain = attrs.undefined("ref", nil).undefined("domain", nil);
        model = PModules::   newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("domain", domain)))));
        model->setParent(this);
        model->find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

    }

    if(this->attrs == nil) { 
        this->attrs = model-> getView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("table")))))).undefined("attrs", nil);
         PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "Load Default View -" << model->modelName << this->attrs.toString();
    }

    if(this->sortField == nil) {
        QString s = model->sortField.toString();
        this->sortField = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( s, QString("asc")))));
    }

    this->model = model;
    model->sqlView = this;

    this->fields = model->tableViewFields();

    initTotalizerFields();

    

    if(model->level == 0 and showFilterPanel and this->attrs. undefined("show_filter_panel", nil)!= "false") {

        filterPanel = new QWidget(this);
        QGridLayout* mainLayout = new QGridLayout(filterPanel); mainLayout->setContentsMargins(0,0,0,0);
        gridLayout->addWidget(filterPanel, 1, 0);
        QGridLayout* paginationLayout = new QGridLayout();
        paginationLayout->setContentsMargins(0,0,0,0);
        mainLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 1);
        mainLayout->addLayout(paginationLayout, 0, 2);

        sqlPagination = new  
                                              PSqlPagination(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelPtr",   QVariant::fromValue(model))->append("parent",   
                                              QVariant::fromValue(parent))))));
        paginationLayout->addWidget(sqlPagination, 1, 0);

        connect(sqlPagination, SIGNAL(currentPageChanged(int)), this, SLOT(reload()));
        connect(sqlPagination, SIGNAL(pageSizeChanged(QString)), this, SLOT(reload()));

        sqlFilterPanel = new  
                                      PSqlFilterPanel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", this->modelName)->append("parent",   
                                      QVariant::fromValue(parent))))));

        connect(sqlFilterPanel, SIGNAL(filterChanged(PVariant)), this, SLOT(reload()));

        mainLayout->addWidget(sqlFilterPanel, 0, 0);


        sqlGroupPanel = new  
                                      PSqlGroupPanel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", this->modelName)->append("parent",   
                                      QVariant::fromValue(parent))))));

        connect(sqlGroupPanel, SIGNAL(groupChanged(PVariant)), this, SLOT(reload()));

        mainLayout->addWidget(sqlGroupPanel, 1, 0);


        sqlMenuFilters = new  
                                      PSqlMenuFilters(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", this->modelName)->append("parent",   
                                      QVariant::fromValue(parent))))));
        connect(sqlMenuFilters, SIGNAL(changeFilter(PVariant)), this, SLOT(reload()));

        paginationLayout->addWidget(sqlMenuFilters, 0, 0);

        hideButton = new QToolButton(this);
        hideButton->setArrowType(Qt::LeftArrow);
        hideButton->setAutoRaise(true);
        hideButton->setFixedSize(18, 18);
        gridLayout->addWidget(hideButton, 1, 0, Qt::AlignTop | Qt::AlignRight);

        connect(hideButton, SIGNAL(clicked(bool)), this, SLOT(hideOrShowFilterPanel()));

    }

    tableWidget = new PTableWidget();
    
    gridLayout->addWidget(tableWidget, 3, 0);
    tableWidget->setColumnCount(fields.count());
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setAlternatingRowColors(true);
    tableWidget->setShowGrid(false);
    

    if(showControlPanel) {
        PVariant controlPanelSection = model-> getView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("controlpanel"))))));

        if(controlPanelSection == nil)
            controlPanelSection = PViewLoader().viewByPath("views.default_view")->
                                  partialByType("controlpanel")->toVariant();

        QWidget* controlPanelWidget = new QWidget();
        model->toWidget(controlPanelSection, controlPanelWidget, gridLayout, 0, "new");
        

        QWidget* cpw = model->controlPanelWidget();
        if(cpw and gridLayout->itemAtPosition(0,0)) {
            QGridLayout* controlPanelGridLayout = qobject_cast<QGridLayout*>(gridLayout->itemAtPosition(0,0)->widget()->layout());
            controlPanelGridLayout->addWidget(cpw, 0, controlPanelGridLayout->columnCount());
        }

    }

    connect(tableWidget, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
    connect(tableWidget, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(onDoubleClicked(int, int)));

    QHeaderView* header = tableWidget->horizontalHeader();
    connect(header, SIGNAL(sortIndicatorChanged (int, Qt::SortOrder)), this, SLOT(onSortIndicatorChanged(int, Qt::SortOrder)));

       fields.forEachWithIndexPVariant_int([&] (PVariant field,int i) mutable {
        PString label = field.undefined("label", nil).toString();
        
        label = PTranslator::tr(label);
        tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(label));
    });

    PSinglUserManager::instance()->applyProfile(this, modelName);

}

void PSqlTableView::hideOrShowFilterPanel() {

    filterPanel->setVisible(!filterPanel->isVisible());

}


void PSqlTableView::initTreeWidget() {

    treeWidget = new QTreeWidget();
    gridLayout->addWidget(treeWidget, 4, 0);
    treeWidget->setAlternatingRowColors(true);
    treeWidget->hide();

    connect(treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onDoubleClicled(QTreeWidgetItem*, int)));

}


PVariant PSqlTableView::data() {

    return true;

}

void PSqlTableView::setData(PVariant data) {

    
    reload();

}

void PSqlTableView::setBackgroundColor(QString color) {

}


bool PSqlTableView::isEmpty() {

    return model->count() == 0;

}


void PSqlTableView::onEditingFinished() {



    emit editingFinished(fieldName, QVariant::fromValue(model));

}


void PSqlTableView::onDoubleClicked(int row, int col) {

    model->onClick( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("action", QString("edit"))))));

}

void PSqlTableView::onDoubleClicled(QTreeWidgetItem* item, int column) {

    QDialog dialog;

    PVariant filter = PVariant::fromString(item->data(0, Qt::UserRole).toString());

    

    PSqlTableViewDialog  
                                          sqlTableView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", this->modelName)->append("filter", filter)->append("showControlPanel", false)))));

    sqlTableView.exec();



}


void PSqlTableView::onSortIndicatorChanged(int index, Qt::SortOrder order) {

    QString fieldName = this->fields[index].undefined("name", nil).toString();

    if(model->fieldAttr(fieldName).undefined("type", nil).toString() == "virtual")
        return;

    QString direction = order ? "asc" : "desc";

    this->sortField = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( fieldName, direction))));

    this->reload();

}


void PSqlTableView::initTotalizerFields() {

    this->totalizerFields = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    this->totalizers = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

     this->fields.forEachPVariant([&] (PVariant fieldAttr) mutable {
        QString fieldName = fieldAttr.undefined("name", nil).toString();
        totalizers[fieldName] = "";
        if(fieldAttr. undefined("totalizable", nil)!= nil) {
            this->totalizerFields << fieldName;
            totalizers[fieldName] = 0;
        }
    });

}

void PSqlTableView::hideOrShow() {

    if(!sqlGroupPanel) return;

    if(sqlGroupPanel->group.count() > 0) {
        tableWidget->hide();
        if(treeWidget) treeWidget->show();
    }

    else {
        tableWidget->show();
        if(treeWidget) treeWidget->hide();
    }

}

void PSqlTableView::setAlignmentTableWidgetItem(QTableWidgetItem* widgetItem, QString type, QString alignment) {

    if(alignment == "right" or PModel   ::isNumber(type)) widgetItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    else if(alignment == "center" or type == "date" or type == "time" or type == "datetime") widgetItem->setTextAlignment(Qt::AlignCenter);
    else widgetItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

}


void PSqlTableView::reload() {

    hideOrShow();

    if(sqlGroupPanel and sqlGroupPanel->group.count() > 0)
        return;


    model->onReloadView();

    this->totalizerFields = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    tableWidget->clearContents();

    PVariant sql;
    if(model->level == 0 and sqlPagination == 0)
        model->   findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", this->filter)->append("orderBy", this->sortField)))));
    else if(model->level == 0) {
        int currentPage = sqlPagination->currentPage - 1;
        QString pageSize = sqlPagination->pageSize;

        sql = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("and", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(sqlFilterPanel->globalFilter)->append(   sqlMenuFilters->getFilter())->append(this->filter))))))));

        model->       findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", sql)->append("orderBy", this->sortField)->append("page", currentPage)->append("pageSize", pageSize)))));
        
    }

    if(model->level == 0) tableWidget->setRowCount(model->count() + 1);
    else tableWidget->setRowCount(model->count());

    QVariant newId = model->undefined("id", nil);

    if(newId == nil) return;

    int newRow = -1;

       model->forEachPModelPtr_int([&] (PModelPtr modelPtr,int r) mutable {
        int col = 0;
        QVariant id = modelPtr->undefined("id", nil);
        if(id == newId) newRow = r;
         fields.forEachPVariant([&] (PVariant field) mutable {
            PVariant attrs = model->fieldAttr(field.undefined("name", nil).toString());
            QString type = attrs.undefined("type", nil).toString();
            if(field != nil) {
                QString fieldValue = modelPtr->fieldValue(field.undefined("name", nil).toString()).toString();
                if(attrs.undefined("toTranslate", nil).toBool())
                    fieldValue = PTranslator::tr(modelPtr->fieldValue(field.undefined("name", nil).toString()).toString());

                if(attrs.undefined("type", nil).toString() == "date") {
                    QDate fieldValueDate =  modelPtr->fieldValue(field.undefined("name", nil).toString()).toDate();
                    fieldValue = QLocale().toString(fieldValueDate, QLocale::ShortFormat);
                }

                if(attrs.undefined("fieldType", nil).toString() != "progress_bar_plus" &&
                   attrs.undefined("fieldType", nil).toString() != "dashboard") {
                    QTableWidgetItem* widgetItem = new QTableWidgetItem(fieldValue);
                    setAlignmentTableWidgetItem(widgetItem, type, field.undefined("alignment", nil).toString());
                    widgetItem->setData(Qt::UserRole, id);
                    tableWidget->setItem(r, col++, widgetItem);
                }
                else {
                    
                    PProgressBarPlus* progressBar = new PProgressBarPlus(this);
                    progressBar->setAttrs(attrs);
                    progressBar->setData(fieldValue);
                    tableWidget->setCellWidget(r, col++, progressBar);
                }
            }
        });
    });

    reloadTotalizers();

    tableWidget->selectRow(newRow);
    tableWidget->resizeColumnsToContents();
    
}


void PSqlTableView::reloadTotalizers() {

    quint64 ti = model->psql->tableIndex; 
    PVariant tc = model->psql->tableCursor;

    initTotalizerFields();

       model->forEachPModelPtr_int([&] (PModelPtr modelPtr,int r) mutable {
         fields.forEachPVariant([&] (PVariant field) mutable {
            QString fieldValue = modelPtr->fieldValue(field.undefined("name", nil).toString()).toString();
            if(field. undefined("totalizable", nil)!= nil) totalizers[field.undefined("name", nil).toString()] = totalizers[field.undefined("name", nil).toString()].toDouble() + fieldValue.toDouble();
        });
    });

    if(model->level == 0) {
             totalizers.forEachWithIndexQString_QString_int([&] (QString fieldName,QString fieldValue,int col) mutable {
            QTableWidgetItem* widgetItem = new QTableWidgetItem(fieldValue);
            setAlignmentTableWidgetItem(widgetItem, "number", "right");
            tableWidget->setItem(tableWidget->rowCount() - 1, col, widgetItem);
        });
        tableWidget->setNoSelectRow(tableWidget->rowCount() - 1);
        tableWidget->setBackgroundRow(tableWidget->rowCount() - 1);
    }

    model->psql->tableIndex = ti;
    model->psql->tableCursor = tc;

}


PVariant PSqlTableView::idSelectionList() {

    QList<QTableWidgetItem*> selectedItems = tableWidget->selectedItems();

    PVariant ids = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    for (int i = 0; i < selectedItems.count(); i += tableWidget->columnCount())
        ids << selectedItems[i]->data(Qt::UserRole);

    return ids;

}


PVariant PSqlTableView::selectedRows() {

    PVariant rows = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    QModelIndexList selectedRowsList = this->tableWidget->selectionModel()->selectedRows();

    if(selectedRowsList.count() == 0)
        return rows;

    for(int i = 0; i < selectedRowsList.count(); i++)
            rows << selectedRowsList[i].row();

    return rows;

}


bool PSqlTableView::removeItem(int row) {

    if(row == -1)
        row = this->tableWidget->selectionModel()->selectedRows()[0].row();

    this->tableWidget->removeRow(row);

    reloadTotalizers();

    return true;

}


void PSqlTableView::itemSelectionChanged() {

    QList<QTableWidgetItem*> selectedItems = tableWidget->selectedItems();

    if(selectedItems.count() == 0)
        return;
    

    PVariant id = selectedItems[0]->data(Qt::UserRole);

    model-> setTableCursorBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", id)))));

    model->onCurrentRecordChanged(id.toString());

}


void PSqlTableView::selectItem(int row) {


    this->tableWidget->selectRow(row);

}

void PSqlTableView::selectLastItem() {

    this->selectItem(this->count() - 1);

}

void PSqlTableView::selectItemById(QString id) {

    for(int i = 0; i < tableWidget->rowCount(); i++) {
        QTableWidgetItem* widgetItem = tableWidget->item(i, 0);
        if(widgetItem->data(Qt::UserRole).toString() == id) {
            tableWidget->selectRow(i);
            model-> setTableCursorBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", id)))));
            return;
        }

    }

}

void PSqlTableView::reloadCurrentRecord() {

    int row;

    for(row = 0; row < tableWidget->rowCount(); row++) {
        QTableWidgetItem* widgetItem = tableWidget->item(row, 0);
        if(widgetItem->data(Qt::UserRole).toString() == model->undefined("id", nil).toString())
            break;
    }

       fields.forEachWithIndexPVariant_int([&] (PVariant field,int col) mutable {
        if(field != nil) {
            PVariant attrs = model->fieldAttr(field.undefined("name", nil).toString());
            QString type = attrs.undefined("type", nil).toString();
            QString fieldValue = model->fieldValue(field.undefined("name", nil).toString()).toString();

            if(attrs.undefined("type", nil).toString() == "date") {
                QDate fieldValueDate =  model->fieldValue(field.undefined("name", nil).toString()).toDate();
                fieldValue = QLocale().toString(fieldValueDate, QLocale::ShortFormat);
            }

            if(type == "manyToOne" and fieldValue.isNull()) fieldValue = "0";
            if(attrs.undefined("fieldType", nil).toString() != "progress_bar_plus" &&
               attrs.undefined("fieldType", nil).toString() != "dashboard") {
                QTableWidgetItem* widgetItem = tableWidget->item(row, col);
                if(widgetItem)
                    widgetItem->setText(fieldValue);
            }
            else {
                PProgressBarPlus* progressBar = static_cast<PProgressBarPlus*>(tableWidget->cellWidget(row, col));
                progressBar->setAttrs(attrs);
                progressBar->setData(fieldValue);
            }

        }
    });

    reloadTotalizers();

}

void PSqlTableView::addCurrentRecord(int row) {

    if(row == -1) row = this->count(); 

    tableWidget->insertRow(row);

    PModelPtr newModel = PModel   ::model(model->modelName);
    newModel->setParent(this);
    newModel-> find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id",  model-> undefined("id", nil).toString())))));

       fields.forEachWithIndexPVariant_int([&] (PVariant field,int col) mutable {
        PVariant attrs = model->fieldAttr(field.undefined("name", nil).toString());
        QString type = attrs.undefined("type", nil).toString();
        if(field != nil) {
            QString fieldValue = newModel->fieldValue(field.undefined("name", nil).toString()).toString();

            if(attrs.undefined("type", nil).toString() == "date") {
                QDate fieldValueDate =  newModel->fieldValue(field.undefined("name", nil).toString()).toDate();
                fieldValue = QLocale().toString(fieldValueDate, QLocale::ShortFormat);
            }

            if(attrs.undefined("fieldType", nil).toString() != "progress_bar_plus" &&
               attrs.undefined("fieldType", nil).toString() != "dashboard") {
                QTableWidgetItem* widgetItem = new QTableWidgetItem(fieldValue);
                setAlignmentTableWidgetItem(widgetItem, type, field.undefined("alignment", nil).toString());
                widgetItem->setData(Qt::UserRole, model->undefined("id", nil));
                tableWidget->setItem(row, col, widgetItem);
            }
            else {
                
                PProgressBarPlus* progressBar = new PProgressBarPlus(this);
                progressBar->setAttrs(attrs);
                progressBar->setData(fieldValue);
                tableWidget->setCellWidget(row, col, progressBar);
            }

        }
    });

    delete newModel.model;

    reloadTotalizers();

}


void PSqlTableView::swapItems(int item1, int item2) {

    this->tableWidget->swapRows(item1, item2);

}


int PSqlTableView::count() {

    if(model->level == 0)
        return tableWidget->rowCount() - 1;

    return tableWidget->rowCount();

}
