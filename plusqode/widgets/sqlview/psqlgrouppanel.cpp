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



   #include "widgets/sqlview/psqlgrouppanel.h"

   
   

PSqlGroupPanel:: PSqlGroupPanel(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PSqlGroupPanel:  invalid type";
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

    groups = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    group = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    PVariant fields = modelPtr->pFields.keys();

     fields.forEachQString([&] (QString fieldName) mutable {
        PVariant group = modelPtr->fieldAttr(fieldName).undefined("groups", nil);
        if(group != nil) groups << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fieldName", fieldName)->append("groups", group))));
    });

    groupWidget();

}


PVariant PSqlGroupPanel::getGroup() {

    PVariant andConditions = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

     groups.forEachPVariant([&] (PVariant row) mutable {
         row.
        undefined("groups", nil).forEachPVariant([&] (PVariant fil) mutable {
            if(fil("selected") == true)
                andConditions << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("value", fil.  undefined("value", nil))->append("position", fil.    undefined("position", nil)))));
        });

    });

    andConditions =    andConditions.sortPVariant_PVariant([&] (PVariant a,PVariant b) mutable { return a.undefined("position", nil).toInt() < b.undefined("position", nil).toInt(); });;

    return  andConditions.mapPVariant([&] (PVariant value) mutable { return value.undefined("value", nil); });

}



void PSqlGroupPanel::onChangeState(PCheckBox* checkBox)  {

    static int position = 0;

    checkBox->data["selected"] = checkBox->isChecked();
    checkBox->data["position"] = position++;

    this->group = this->getGroup();

    emit groupChanged(group);

}



void PSqlGroupPanel::groupWidget() {


       groups.forEachWithIndexPVariant_int([&] (PVariant row,int i) mutable {

        QWidget* widget = new QWidget(this);
        QGridLayout* layout = new QGridLayout(widget);
        layout->setContentsMargins(0,0,0,0);
        gridLayout->addWidget(new QLabel(PTranslator::tr(PString(QString("%1 - Group by").arg(row.undefined("fieldName", nil).toString())))), i, 0);
        gridLayout->addWidget(widget, i, 1);

           row.

        undefined("groups", nil).forEachWithIndexPVariant_int([&] (PVariant group,int j) mutable {
            PCheckBox* checkBox = new PCheckBox(this);
            checkBox->setKey(PString(QString("%1-%2").arg(i).arg(j)));
            checkBox->setText(PTranslator::tr(group.undefined("label", nil).toString()));
            checkBox->data = group;
            connect(checkBox, SIGNAL(changeState(PCheckBox*)), this, SLOT(onChangeState(PCheckBox*)));
            layout->addWidget(checkBox, 0, j);
        });

    });

}
