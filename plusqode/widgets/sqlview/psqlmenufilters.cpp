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



   #include "widgets/sqlview/psqlmenufilters.h"

   
   

PSqlMenuFilters:: PSqlMenuFilters(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PSqlMenuFilters:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
QWidget* parent = source_args.value<PVariantMapPtr>()->include("parent") ? source_args.value<PVariantMapPtr>()->operator[]("parent").value<QWidget*>() : 0;
args.removeByKey("parent");


    QWidget::setParent(parent);
    this->modelName = modelName;

    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(0);

    conditionLabel = new QLabel("condition", this);
    conditionLabel->setFont(QFont("Arial", 8));

    gridLayout->addWidget(conditionLabel, 0, 0);

    onClickNewButton();

}


void PSqlMenuFilters::removeSqlFilter(PSqlMenuFilter* sqlMenuFilter) {

    gridLayout->removeWidget(sqlMenuFilter);
    sqlMenuFilters.removeAll(sqlMenuFilter);
    sqlMenuFilter->hide();
    sqlMenuFilter->deleteLater();

}


void PSqlMenuFilters::setConditionLabel(PVariant filter) {

    

}

PVariant PSqlMenuFilters::getFilter() {

    if(sqlMenuFilters.count() == 1 and sqlMenuFilters[0]->fieldValue == "")
        return PSql::db_true();

    PVariant filter = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    for(int i = 0; i < sqlMenuFilters.count(); i++) {
        PSqlMenuFilter* sqlMenuFilter = sqlMenuFilters[i];
        QString fieldName = sqlMenuFilter->fieldName;
        QString op = sqlMenuFilter->op;
        QString fieldValue = sqlMenuFilter->fieldValue;

        if(filter[op] == nil) filter[op] = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
        if(filter[op][fieldName] == nil) filter[op][fieldName] = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
        filter[op][fieldName] << fieldValue;

    }

    PVariant filter2 = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

       filter.forEachQString_PVariant([&] (QString op,PVariant filter) mutable {
        filter.  undefined("op=", op);
        filter2 << filter;
    });

    PLog().sql() << filter2.toString();

    filter2 = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("and", filter2))));

    return filter2;

}

void PSqlMenuFilters::onChangeFilter(PSqlMenuFilter* sqlMenuFilter) {

    emit changeFilter(getFilter());

}

void PSqlMenuFilters::setAllOperators(QString op) {

    for(int i = 0; i < sqlMenuFilters.count(); i++) {
        PSqlMenuFilter* sqlMenuFilter = sqlMenuFilters[i];
        sqlMenuFilter->comboBox->setCurrentIndex(sqlMenuFilter->comboBox->findData(op, Qt::UserRole));
    }

}


void PSqlMenuFilters::onClickNewButton() {

    PSqlMenuFilter* sqlMenuFilter = new  PSqlMenuFilter(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)))));

    connect(sqlMenuFilter, SIGNAL(clickNewButton()), this, SLOT(onClickNewButton()));
    connect(sqlMenuFilter, SIGNAL(clickDeleteButton(PSqlMenuFilter*)), this, SLOT(onClickDeleteButton(PSqlMenuFilter*)));
    connect(sqlMenuFilter, SIGNAL(changeFilter(PSqlMenuFilter*)), this, SLOT(onChangeFilter(PSqlMenuFilter*)));
    gridLayout->addWidget(sqlMenuFilter, gridLayout->count(), 0);
    sqlMenuFilters << sqlMenuFilter;

    emit changeFilter(getFilter());

}

void PSqlMenuFilters::onClickDeleteButton(PSqlMenuFilter* sqlMenuFilter) {

    


    if(sqlMenuFilters.count() > 1) {
        removeSqlFilter(sqlMenuFilter);
        emit changeFilter(getFilter());
    }
    else
        sqlMenuFilter->clear();


}
