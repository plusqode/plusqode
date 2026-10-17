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




   #include "widgets/sqlview/psqlmenufilter.h"


   

   

PSqlMenuFilter:: PSqlMenuFilter(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PSqlMenuFilter:  invalid type";
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

    PModelPtr modelPtr = PModel   ::model(modelName);
    modelPtr->setParent(this);

    filters = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    PVariant fields = modelPtr->pFields;

    PVariant items = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

       fields.forEachQString_PVariant([&] (QString fieldName,PVariant fieldAttrs) mutable {
        PVariant item = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", fieldName)->append("value", fieldName))));
        items << item;
        if(fieldAttrs.undefined("type", nil).toString() == "manyToOne" || fieldAttrs.undefined("type", nil).toString() == "oneToOne") {
            PModelPtr model = modelPtr->newPModel(fieldAttrs.undefined("modelNameReference", nil).toString());
            PVariant subItems = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
            item.  undefined("menu=", subItems);
               model->pFields.forEachQString_PVariant([&] (QString subFieldName,PVariant fieldAttrs) mutable {
                subItems << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", subFieldName)->append("value", PString(QString("%1.%2").arg(fieldName).arg(subFieldName))))));
            });
        }

    });

    actionButton = new PActionButton( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString(""))->append("menu", items)))));
    actionButton->setMinimumWidth(200);
    connect(actionButton, SIGNAL(click(PVariant)), this, SLOT(onClick(PVariant)));
    gridLayout->addWidget(actionButton, 0, 0);


    comboBox = new QComboBox(this);
    comboBox->addItem("more or less");
    comboBox->addItem("!=");
    comboBox->addItem("~");
    comboBox->addItem("=");
    comboBox->addItem(">");
    comboBox->addItem(">=");
    comboBox->addItem("<");
    comboBox->addItem("<=");
    int i = 0;
    comboBox->setItemData(i++, "ilike", Qt::UserRole);
    comboBox->setItemData(i++, "!=", Qt::UserRole);
    comboBox->setItemData(i++, "~", Qt::UserRole);
    comboBox->setItemData(i++, "=", Qt::UserRole);
    comboBox->setItemData(i++, ">", Qt::UserRole);
    comboBox->setItemData(i++, ">=", Qt::UserRole);
    comboBox->setItemData(i++, "<", Qt::UserRole);
    comboBox->setItemData(i++, "<=", Qt::UserRole);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onEditingFinished()));
    gridLayout->addWidget(comboBox, 0, 1);


    lineEdit = new QLineEdit(this);
    gridLayout->addWidget(lineEdit, 0, 2);
    connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));


    PActionButton* newButton = new PActionButton( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("icon", QString(":/picons/core/actions/new.png"))))), this);
    connect(newButton, SIGNAL(click(PVariant)), this, SLOT(onClickNewButton()));
    gridLayout->addWidget(newButton, 0, 3);
    PActionButton* deleteButton = new PActionButton( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("icon", QString(":/picons/core/actions/delete.png"))))));
    connect(deleteButton, SIGNAL(click(PVariant)), this, SLOT(onClickDeleteButton()));
    gridLayout->addWidget(deleteButton, 0, 4);

}


void PSqlMenuFilter::onClick(PVariant actionItem) {

    lastActionItem = actionItem;

    actionButton->setText(actionItem.undefined("value", nil).toString());

    onEditingFinished();

}

void PSqlMenuFilter::onEditingFinished() {

    fieldName = lastActionItem.undefined("value", nil).toString();
    op = comboBox->itemData(comboBox->currentIndex(), Qt::UserRole).toString();
    fieldValue = lineEdit->text();
    if(op == "ilike")
        fieldValue = PString(QString("%%1%").arg(fieldValue));


    emit changeFilter(this);

}

void PSqlMenuFilter::clear() {

    actionButton->setText("");
    comboBox->setCurrentIndex(0);
    lineEdit->setText("");

    onEditingFinished();

    emit changeFilter(this);

}

void PSqlMenuFilter::onClickNewButton() {


    emit(clickNewButton());


}

void PSqlMenuFilter::onClickDeleteButton() {


    emit(clickDeleteButton(this));


}
