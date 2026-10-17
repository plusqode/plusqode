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




   #include "widgets/sqlview/psqlgrouptableview.h"


   

   

PSqlGroupTableView::~PSqlGroupTableView() {

    delete treeWidget;

}


PSqlGroupTableView::PSqlGroupTableView(PVariant args) {

    init(args);

    initTreeWidget();

    PSqlTableView::reload();

    model->onAfterTable();


}

void PSqlGroupTableView::resizeColumnsToContents() {

    for(int i = 0; i < treeWidget->columnCount(); i++)
        treeWidget->resizeColumnToContents(i);

}


void PSqlGroupTableView::onGroupChanged(PVariant groupBy) {


}

QList<QTreeWidgetItem*> PSqlGroupTableView::sqlTotalizerFields(PVariant groupBy, PVariant filter) {

    PVariant groupBy1 = groupBy;
    if(groupBy.count() > 0)
        groupBy1 = groupBy[0];

    PVariant groupByFieldName = groupBy1.split(".")[0];

    PVariant groupByLeft = groupBy1.split("->")[0]; 

    PVariant _sqlTotalizerFields = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(groupByFieldName)->append(QString("count(*) as count"))->append(PString(QString("%1 as \"%2\"").arg(groupBy1.toString()).arg(groupByLeft.toString()))))));


    PVariant tots = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

     totalizerFields.forEachQString([&] (QString fieldName) mutable {
        if(fieldName == "id")
            tots << PString(QString("%1 as id").arg(groupByFieldName.toString()));
        else
            tots << PString(QString("sum(%1) as %2").arg(fieldName).arg(fieldName));
    });

    _sqlTotalizerFields += tots;

    PSql  query(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", model->connectionName)))));

    query.select(_sqlTotalizerFields, QVariant::fromValue(model.model))->
          from(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(model->modelName)))))->
          where(filter)->
          groupBy(groupByFieldName)->
          orderBy( PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(groupBy1)))), QVariant::fromValue(model.model))->
          
          execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))))->show();


    QList<QTreeWidgetItem*> items;


    PVariant queryFields = query.fieldNameList();


       queryFields.forEachWithIndexQString_int([&] (QString fieldName,int i) mutable {
        PString label = fieldName;
        if(label.include(".")) label = label.split(".")[-1].toString().capitalize(); 
        treeWidget->headerItem()->setText(i, label);
    });

    

       query.forEachWithIndexPVariant_int([&] (PVariant row,int r) mutable {
        
        QTreeWidgetItem* widgetItem = new QTreeWidgetItem(QStringList(row.values().toStringList()));
        PString key = _sqlTotalizerFields.undefined("0", nil).toString();
        PVariant subFilter = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( key,    row[key]))));

        if(key.include("->")) { 
            QString k = key.split("->")[0].toString();
            subFilter = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( key,    row[k]))));
        }

        PVariant f = PSql::simplify( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("and", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(filter)->append(subFilter)))))))));

        

        widgetItem->setData(0, Qt::UserRole, f.toString());
        widgetItem->setSizeHint(0, QSize(0, 30));
        items << widgetItem;
    });

    PVariant rightGroup = groupBy.value<PVariantListPtr>()->mid(1, -1);
    if(groupBy.count() > 1)    query.forEachWithIndexPVariant_int([&] (PVariant row,int i) mutable {
        QTreeWidgetItem* item = items[i];
        PVariant filter = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
        filter[groupByFieldName.toString()] = row[groupByFieldName.toString()];
        item->addChildren( sqlTotalizerFields(rightGroup, filter) );
    });

    return items;

}


PVariant PSqlGroupTableView:: groupByFieldName(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "groupByFieldName:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant groupBy = source_args.value<PVariantMapPtr>()->include("groupBy") ? source_args.value<PVariantMapPtr>()->operator[]("groupBy") : nil;args.removeByKey("groupBy");
PVariant filter = source_args.value<PVariantMapPtr>()->include("filter") ? source_args.value<PVariantMapPtr>()->operator[]("filter") : nil;args.removeByKey("filter");
QString totalizer = source_args.value<PVariantMapPtr>()->include("totalizer") ? source_args.value<PVariantMapPtr>()->operator[]("totalizer").toString() : QVariant(QString("count")).toString();args.removeByKey("totalizer");



    PVariant groupByCopy = groupBy;

    groupBy = groupBy[0];

    PVariant groupByFieldName = groupBy.split(".")[0];

    groupBy = groupBy.split("->")[0]; 

    QString totalizerField = totalizer == "count" ? "count(*) as count" : PString(QString("sum(%1) as \"%2\"").arg(totalizer).arg(totalizer));

    PVariant sqlTotalizerFields = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(totalizerField)->append(PString(QString("%1 as \"%2\"").arg(groupByCopy.undefined("0", nil).toString()).arg(groupBy.toString()))))));

    return sqlTotalizerFields;

}


void PSqlGroupTableView::reload() {

    if(!sqlGroupPanel) return;

    if(sqlGroupPanel->group.isNull() || sqlGroupPanel->group.count() == 0) {
        PSqlTableView::reload();
        return;
    }

    hideOrShow();

    treeWidget->clear();

    PVariant sql = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("and", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(sqlFilterPanel->globalFilter)->append(   sqlMenuFilters->getFilter())->append(this->filter))))))));

    treeWidget->addTopLevelItems(sqlTotalizerFields(sqlGroupPanel->group, sql));

    resizeColumnsToContents();

}
