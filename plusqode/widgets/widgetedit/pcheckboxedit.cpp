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



   #include "widgets/widgetedit/pcheckboxedit.h"

   
   

PCheckBoxEdit::PCheckBoxEdit(PVariant itemsAndValues, QWidget *parent) :
        PFieldWidget(parent) {

    this->currentData = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    this->itemsAndValues = itemsAndValues;
    this->mandatoryFields = 0;
    this->alignment = "vertical";
    this->readOnly = false;

    layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
}

void PCheckBoxEdit::setMandatory(int mandatoryFields) {

    this->mandatoryFields = mandatoryFields;

}


PVariant PCheckBoxEdit::data() {

    return currentData.toString();

}

void PCheckBoxEdit::setData(PVariant data) {

    if(!data.toString().startsWith("{"))
        data = "{}";

    currentData = PVariant::fromString(data.toString());

    populateList();

}

void PCheckBoxEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    setPalette(pal);

}

void PCheckBoxEdit::setReadOnly(bool value) {

    readOnly = value;

}

void PCheckBoxEdit::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PCheckBoxEdit::isEmpty() {

    int counter = 0;
         itemsAndValues.forEachWithIndexQString_QString_int([&] (QString key,QString value,int i) mutable {
        if(checkBoxMap[key]->checkState() != 0) counter++;
    });

    return counter < this->mandatoryFields;

}

void PCheckBoxEdit::onEditingFinished(QString) {

    emit editingFinished(fieldName, data());

}

void PCheckBoxEdit::onChangeState(PCheckBox* checkBox) {

    this->currentData[checkBox->key] = checkBox->checkState();
    emit editingFinished(fieldName, data());
    emit changeState(fieldName, checkBox);

}


void PCheckBoxEdit::populateList() {

         itemsAndValues.forEachWithIndexQString_QString_int([&] (QString key,QString value,int i) mutable {
        PCheckBox* checkBox = new PCheckBox(this);
        checkBoxMap[key] = checkBox;
        connect(checkBox, SIGNAL(changeState(PCheckBox*)), this, SLOT(onChangeState(PCheckBox*)));
        checkBox->setReadOnly(readOnly);
        checkBox->setKey(key);
        checkBox->setText(value);
        checkBox->setCheckState((Qt::CheckState)currentData[key].toInt());
        if(this->alignment == "vertical")
            layout->addWidget(checkBox, i, 0);
        else
            layout->addWidget(checkBox, 0, i);
    });

}
