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



   #include "widgets/pfieldselector.h"

   
   

PFieldSelector::PFieldSelector(QWidget* parent) : QDialog(parent) {

    this->setWindowTitle("Field Selector");

    gridLayout = new QGridLayout(this);
    label = new QLabel(this);
    label->setPixmap(QPixmap("picons/core/actions-128/db-restore.png"));
    label->setAlignment(Qt::AlignHCenter);
    gridLayout->addWidget(label, 0, 0);

    QDialogButtonBox::ButtonRole buttonRole = QDialogButtonBox::AcceptRole;

    
    

    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    buttonBox->setObjectName("dialogButtonBox");

    okButton = buttonBox->addButton("Ok", buttonRole);
    okButton->setMinimumHeight(40);
    okButton->setIcon(QIcon(":/picons/core/actions/ok.png"));

    cancelButton = buttonBox->addButton("Cancel", buttonRole);
    cancelButton->setMinimumHeight(40);
    cancelButton->setIcon(QIcon(":/picons/core/actions/delete.png"));


    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    
    buttonBox->setCenterButtons(true);

    gridLayout->addWidget(buttonBox, 3, 0);

}

void PFieldSelector::initListWidget(PModel* model) {

    listWidget = new QListWidget(this);
    listWidget->setDragDropMode(QAbstractItemView::InternalMove);
    gridLayout->addWidget(listWidget, 2, 0);

    PVariant fields = model->pFields;

    PVariant items = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

       fields.forEachQString_PVariant([&] (QString fieldName,PVariant fieldAttrs) mutable {
        PVariant item = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", fieldName)->append("value", fieldName))));
        items << item;
        if(fieldAttrs.undefined("type", nil).toString() == "manyToOne" || fieldAttrs.undefined("type", nil).toString() == "oneToOne") {
            PModelPtr modelPtr = model->newPModel(fieldAttrs.undefined("modelNameReference", nil).toString());
            PVariant subItems = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
            item.  undefined("menu=", subItems);
               modelPtr->pFields.forEachQString_PVariant([&] (QString subFieldName,PVariant fieldAttrs) mutable {
                subItems << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", subFieldName)->append("value", PString(QString("%1.%2").arg(fieldName).arg(subFieldName))))));
            });
        }

    });

    actionButton = new PActionButton( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString(""))->append("menu", items)))));
    actionButton->setMinimumWidth(200);
    connect(actionButton, SIGNAL(click(PVariant)), this, SLOT(onClick(PVariant)));
    gridLayout->addWidget(actionButton, 1, 0);

}


PVariant PFieldSelector::selectedFields() {

    PVariant sf = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));  

    for(int i = 0; i < listWidget->count(); i++) {
        QListWidgetItem* item = listWidget->item(i);
        if(item->checkState() == Qt::Checked)
            sf << item->text();
    }

    return sf;

}


void PFieldSelector::onClick(PVariant fieldName) {

    QListWidgetItem* item = new QListWidgetItem(fieldName.undefined("value", nil).toString());
    item->setCheckState(Qt::Checked);
    listWidget->addItem(item);

}
