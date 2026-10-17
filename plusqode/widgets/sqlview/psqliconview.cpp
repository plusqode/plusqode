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




   #include "widgets/sqlview/psqliconview.h"


   

   
   #include "app/modules/pmodules.h"


   

   
   

   
   
 

PSqlIconView:: PSqlIconView(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PSqlIconView:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString moduleName = source_args.value<PVariantMapPtr>()->include("moduleName") ? source_args.value<PVariantMapPtr>()->operator[]("moduleName").toString() : QVariant(nil).toString();args.removeByKey("moduleName");
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
PVariant attrs = source_args.value<PVariantMapPtr>()->include("attrs") ? source_args.value<PVariantMapPtr>()->operator[]("attrs") : nil;args.removeByKey("attrs");
QString filter = source_args.value<PVariantMapPtr>()->include("filter") ? source_args.value<PVariantMapPtr>()->operator[]("filter").toString() : QVariant(QString("true")).toString();args.removeByKey("filter");
PVariant sortField = source_args.value<PVariantMapPtr>()->include("sortField") ? source_args.value<PVariantMapPtr>()->operator[]("sortField") : PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", QString("asc")))));args.removeByKey("sortField");
QString pageSize = source_args.value<PVariantMapPtr>()->include("pageSize") ? source_args.value<PVariantMapPtr>()->operator[]("pageSize").toString() : QVariant(QString("all")).toString();args.removeByKey("pageSize");
int page = source_args.value<PVariantMapPtr>()->include("page") ? source_args.value<PVariantMapPtr>()->operator[]("page").toInt() : QVariant(0).toInt();args.removeByKey("page");
PModelPtr model = source_args.value<PVariantMapPtr>()->operator[]("model").value<PModelPtr>();
args.removeByKey("model");
QString connectionName = source_args.value<PVariantMapPtr>()->include("connectionName") ? source_args.value<PVariantMapPtr>()->operator[]("connectionName").toString() : QVariant(QString("default")).toString();args.removeByKey("connectionName");
bool showControlPanel = source_args.value<PVariantMapPtr>()->include("showControlPanel") ? source_args.value<PVariantMapPtr>()->operator[]("showControlPanel").toBool() : QVariant(true).toBool();args.removeByKey("showControlPanel");
bool totalizerPanel = source_args.value<PVariantMapPtr>()->include("totalizerPanel") ? source_args.value<PVariantMapPtr>()->operator[]("totalizerPanel").toBool() : QVariant(false).toBool();args.removeByKey("totalizerPanel");
QWidget* parent = source_args.value<PVariantMapPtr>()->include("parent") ? source_args.value<PVariantMapPtr>()->operator[]("parent").value<QWidget*>() : 0;
args.removeByKey("parent");


    QWidget::setParent(parent);

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

    if(this->attrs == nil) {
        this->attrs = model-> getView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("icon")))))).undefined("attrs", nil);
         PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "Load Default View -" << model->modelName << this->attrs.toString();
    }

    this->model = model;
    model->sqlView = this;

    PVariant fields = model->tableViewFields();

    listWidget = new QListWidget(this);

    listWidget->setGridSize(QSize(120, 150)); 
    listWidget->setWordWrap(true);
    if(this->attrs. undefined("gridSize", nil)!= nil) {
        PVariant size = PVariant::fromString(this->attrs.undefined("gridSize", nil).toString());
        listWidget->setGridSize(QSize(size.undefined("0", nil).toInt(), size.undefined("1", nil).toInt()));
    }

    listWidget->setIconSize(QSize(128, 128));
    listWidget->setMovement(QListView::Static);
    listWidget->setResizeMode(QListView::Adjust);
    
    gridLayout->addWidget(listWidget, 3, 0);


    if(showControlPanel) {
        PVariant controlPanelSection = model-> getView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("controlpanel"))))));

        if(controlPanelSection == nil)
            controlPanelSection = PViewLoader().viewByPath("views.default_view")->
                                  partialByType("controlpanel")->toVariant();
        QWidget* controlPanelWidget = new QWidget(this);
        model->toWidget(controlPanelSection, controlPanelWidget, gridLayout, 0, "new");
        gridLayout->addWidget(controlPanelWidget, 2, 0);

        QWidget* cpw = model->controlPanelWidget();
        if(cpw and gridLayout->itemAtPosition(0,0)) {
            QGridLayout* controlPanelGridLayout = qobject_cast<QGridLayout*>(gridLayout->itemAtPosition(0,0)->widget()->layout());
            controlPanelGridLayout->addWidget(cpw, 0, controlPanelGridLayout->columnCount());
        }

    }


    listWidget->setViewMode(QListView::IconMode);

    connect(listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChanged()));
    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onDoubleClicked(QListWidgetItem*)));

    reload();

}

PSqlIconView::~PSqlIconView() {

}


PVariant PSqlIconView::data() {

    return nil;

}

void PSqlIconView::setData(PVariant data) {

    reload();

}

void PSqlIconView::setBackgroundColor(QString color) {

}


bool PSqlIconView::isEmpty() {

    return model->count() == 0;

}


void PSqlIconView::onEditingFinished() {

    this->reload();

    emit editingFinished(fieldName, QVariant::fromValue(model));

}


void PSqlIconView::onDoubleClicked(QListWidgetItem*) {

    model->onClick( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("action", QString("edit"))))));

}


void PSqlIconView::setWidgetItem(QListWidgetItem* widgetItem) {

    PModelPtr rec = model->toModelPtr();

    QVariant id = rec->undefined("id", nil);
    PVariant showField = model->showField;
    QString name = model->fieldValue(showField.toString()).toString();

    if(showField.typeName() == "Array") {
        PVariant item = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
         showField.forEachQString([&] (QString fieldName) mutable { item << model->fieldValue(fieldName).toString(); });
        name = item.join(" - ");
    }

    QString icon;
    if(rec-> undefined("pos_id", nil).value<PModelPtr>().value<PMPos*>()&& !rec->undefined("pos_id", nil).value<PModelPtr>().value<PMPos*>()->undefined("icon", nil).toString().isEmpty()) icon = rec->undefined("pos_id", nil).value<PModelPtr>().value<PMPos*>()->undefined("icon", nil).toString();
    if(icon.isEmpty()) icon = rec->undefined("icon", nil).toString();
    if(icon.isEmpty()) icon = model->fieldAttr("icon").undefined("default", nil).toString();

    widgetItem->setText(name);
    widgetItem->setData(Qt::UserRole, id);

    if(!model->stateIdFieldName.isNull() and
       rec->undefined(model->stateIdFieldName, nil).value<PModelPtr>().model) {
        PModelPtr iconId = rec->undefined(model->stateIdFieldName, nil).value<PModelPtr>()->undefined("icon_id", nil).value<PModelPtr>().value<PMIcon*>();
        
        
        if(icon.isEmpty()) icon = iconId->undefined("icon", nil).toString();
        int hue = iconId->undefined("hue", nil).toInt();
        int saturation = iconId->undefined("saturation", nil).toInt();
        int scale = iconId->undefined("scale", nil).toInt();

        PImage image(icon);
        if(hue || saturation) image.setHS(hue, saturation);
        if(scale) image = image.scaled(image.width() * 100 / scale,
                                           image.height() * 100 / scale,
                                           Qt::KeepAspectRatio);
        widgetItem->setIcon(QPixmap::fromImage(image));
    }
    else {
        PImage image(icon);

        

        if(this->attrs. undefined("iconSize", nil)!= nil) {
            PVariant size = PVariant::fromString(this->attrs.undefined("iconSize", nil).toString());
            image = image.scaled(QSize(size.undefined("0", nil).toInt(), size.undefined("1", nil).toInt()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }

        widgetItem->setIcon(image.toPixmap());
    }

    
    listWidget->addItem(widgetItem);

}


void PSqlIconView::reload() {

    model->onReloadView();

    listWidget->clear();

    if(model->level == 0) {
        
        model-> findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("orderBy", this->sortField)))));
        
    }

    QVariant newId = model->undefined("id", nil);

    if(newId == nil) return;

    int newRow = -1;

       model->forEachPModelPtr_int([&] (PModelPtr rec,int r) mutable {
        this->setWidgetItem(new QListWidgetItem());
    });

    
    listWidget->setFocus();

}


void PSqlIconView::reloadCurrentRecord() {

    QListWidgetItem* widgetItem;

    for(int i = 0; i < listWidget->count(); i++) {
        widgetItem = listWidget->item(i);
        if(widgetItem->data(Qt::UserRole).toString() == model->undefined("id", nil).toString())
            break;
    }

    this->setWidgetItem(widgetItem);

}


PVariant PSqlIconView::idSelectionList() {

    QList<QListWidgetItem*> selectedItems = listWidget->selectedItems();

    PVariant ids = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    for (int i = 0; i < selectedItems.count(); i++)
        ids << selectedItems[i]->data(Qt::UserRole);

    return ids;

}


PVariant PSqlIconView::selectedRows() {

    PVariant rows = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    QList<QListWidgetItem*> selectedItems = this->listWidget->selectedItems();

    if(selectedItems.count() == 0)
        return rows;

    for(int i = 0; i < selectedItems.count(); i++)
        rows << this->listWidget->row(selectedItems[i]);

    return rows;

}


void PSqlIconView::selectItem(int row) {

    this->listWidget->setCurrentRow(row);

}

void PSqlIconView::selectItemById(QString id) {

    for(int i = 0; i < listWidget->count(); i++) {
        QListWidgetItem* widgetItem = listWidget->item(i);
        if(widgetItem->data(Qt::UserRole).toString() == id) {
            widgetItem->setSelected(true);
            model-> setTableCursorBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", id)))));
            return;
        }

    }

}


void PSqlIconView::selectLastItem() {

    this->listWidget->setCurrentRow(count() - 1);

}


int PSqlIconView::count() {

    return this->listWidget->count();

}


void PSqlIconView::itemSelectionChanged() {

    QList<QListWidgetItem*> selectedItems = listWidget->selectedItems();

    if(selectedItems.count() == 0)
        return;

    PVariant id = selectedItems[0]->data(Qt::UserRole);

    model-> setTableCursorBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", id)))));

    model->onCurrentRecordChanged(id.toString());

}
