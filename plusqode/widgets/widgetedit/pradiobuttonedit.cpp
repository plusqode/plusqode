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



   #include "widgets/widgetedit/pradiobuttonedit.h"

   
   

PRadioButtonEdit::PRadioButtonEdit(PVariant itemsAndValues, QWidget *parent) :
        PFieldWidget(parent) {

    this->currentData = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    this->itemsAndValues = itemsAndValues;
    this->mandatoryFields = 0;
    this->readOnly = false;

    layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
}


void PRadioButtonEdit::setMandatory(int mandatoryFields) {

    this->mandatoryFields = mandatoryFields;

}


PVariant PRadioButtonEdit::data() {

    return currentData.toString();

}

void PRadioButtonEdit::setData(PVariant data) {

    if(!data.toString().startsWith("{"))
        data = "{}";

    currentData = PVariant::fromString(data.toString());

    populateList();

}

void PRadioButtonEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    setPalette(pal);

}

void PRadioButtonEdit::setReadOnly(bool value) {

    readOnly = value;

}

void PRadioButtonEdit::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PRadioButtonEdit::isEmpty() {

    int counter = 0;
         itemsAndValues.forEachWithIndexQString_QString_int([&] (QString key,QString value,int i) mutable {
        if(radioButtonMap[key]->isChecked() != 0) counter++;
    });

    return counter < this->mandatoryFields;

}

void PRadioButtonEdit::onEditingFinished(QString) {

    emit editingFinished(fieldName, data());

}

void PRadioButtonEdit::onChangeState(PRadioButton* radioButton) {

    this->currentData = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( radioButton->key,    radioButton->isChecked()))));
    emit editingFinished(fieldName, data());

}


void PRadioButtonEdit::populateList() {

         itemsAndValues.forEachWithIndexQString_QString_int([&] (QString key,QString value,int i) mutable {
        PRadioButton* radioButton = new PRadioButton(this);
        radioButtonMap[key] = radioButton;
        connect(radioButton, SIGNAL(changeState(PRadioButton*)), this, SLOT(onChangeState(PRadioButton*)));
        if(readOnly) {
            radioButton->setDisabled(true);
            radioButton->setStyleSheet(PString(QString("QCheckBox:unchecked {color: black}"))); 
        }
        radioButton->setKey(key);
        radioButton->setText(value);
        radioButton->setChecked((Qt::CheckState)currentData[key].toInt());
        layout->addWidget(radioButton, i, 0);
    });

}
