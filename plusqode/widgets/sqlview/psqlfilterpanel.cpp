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



   #include "widgets/sqlview/psqlfilterpanel.h"

   
   

PSqlFilterPanel:: PSqlFilterPanel(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PSqlFilterPanel:  invalid type";
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

    PModelPtr modelPtr = PModel   ::model(modelName);
    modelPtr->setParent(this);

    filters = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    PVariant fields = modelPtr->pFields.keys();

     fields.forEachQString([&] (QString fieldName) mutable {
        PVariant filter = modelPtr->fieldAttr(fieldName).undefined("filters", nil);
        if(filter != nil) filters << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("filters", filter))));
    });

    

    filterWidget();

}


PVariant PSqlFilterPanel::getFilter() {

    PVariant andConditions = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

     filters.forEachPVariant([&] (PVariant row) mutable {
        QString fieldName = row.undefined("fieldName", nil).toString();
        PVariant orConditions = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
        PVariant filter = row.undefined("filters", nil);
         filter.forEachPVariant([&] (PVariant fil) mutable {
            if(fil("op") == nil) fil["op"] = "=";
            if(fil("selected") == true) {
                if(fil("filter") != nil)
                    orConditions << fil.undefined("filter", nil);
                else {
                    QString fv = fil.undefined("value", nil).toString();
                    QString oprt = fil.undefined("op", nil).toString();
                    orConditions << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( fieldName, fv)->append("op", oprt))));
                }
            }
        });
        if(orConditions.any())
            andConditions << orConditions;

    });

    return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("and", andConditions))));

}


void PSqlFilterPanel::onChangeState(PCheckBox* checkBox)  {

    globalFilter = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    checkBox->data["selected"] = checkBox->isChecked();

    PVariant filter = this->getFilter();

    if(!filter.isEmpty()) globalFilter << filter;

    

    

    

    emit filterChanged(globalFilter);

}



void PSqlFilterPanel::filterWidget() {

       filters.forEachWithIndexPVariant_int([&] (PVariant row,int i) mutable {

        QWidget* widget = new QWidget(this);
        QGridLayout* layout = new QGridLayout(widget);
        layout->setContentsMargins(0,0,0,0);
        gridLayout->addWidget(new QLabel(PTranslator::tr(PString(row.undefined("fieldName", nil).toString()).capitalize())), i, 0);
        gridLayout->addWidget(widget, i, 1);

           row.

        undefined("filters", nil).forEachWithIndexPVariant_int([&] (PVariant filter,int j) mutable {
            PCheckBox* checkBox = new PCheckBox(this);
            checkBox->setKey(PString(QString("%1-%2").arg(i).arg(j)));
            checkBox->setText(PTranslator::tr(filter.undefined("label", nil).toString()));
            checkBox->data = filter;
            connect(checkBox, SIGNAL(changeState(PCheckBox*)), this, SLOT(onChangeState(PCheckBox*)));
            layout->addWidget(checkBox, 0, j);
        });

    });

}
