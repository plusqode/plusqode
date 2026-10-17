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



   #include "widgets/widgetedit/pcomboboxplus.h"

   
   

PComboBoxPlus::PComboBoxPlus(PVariant itemsAndValues, QWidget *parent) :
        PFieldWidget(parent) {

    this->linearItemsAndValues = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    this->itemsAndValues = this->convert(itemsAndValues);

    actionButton = new PActionButton( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString(""))->append("menu", this->itemsAndValues)))), parent);
    
    actionButton->setMinimumHeight(PGlobal::fieldMinimumHeight());

    actionButton->setFont(PGlobal::widgetFont());

    connect(actionButton, SIGNAL(click(PVariant)), this, SLOT(onEditingFinished(PVariant)));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(actionButton, 0, 0);

    populateList();

}


PVariant PComboBoxPlus::convert(PVariant itemsAndValues) {

    PVariant items = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

       itemsAndValues.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        PVariant item = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", fieldValue)->append("value", fieldName))));
        if(fieldValue.typeName() == "Hash") {
            item = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", fieldName)->append("value", fieldName))));
            item.  undefined("menu=", this->convert(fieldValue));
        }
        else
            linearItemsAndValues[fieldName] = fieldValue;

        items << item;
    });

    return items;

}




QWidget* PComboBoxPlus::mainWidget() {

    return actionButton;

}


QString PComboBoxPlus::currentText() {

    return linearItemsAndValues[this->currentData].toString();

}


PVariant PComboBoxPlus::data() {

    return this->currentData;

}


void PComboBoxPlus::setData(PVariant data) {

    this->currentData = data.toString();

    actionButton->setText(linearItemsAndValues[this->currentData].toString());

}

void PComboBoxPlus::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    actionButton->setPalette(pal);



}

void PComboBoxPlus::setReadOnly(bool value) {

    actionButton->setEnabled(!value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());
    actionButton->setStyleSheet(PString(QString("QComboBox {color: black}")));

}


void PComboBoxPlus::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PComboBoxPlus::isEmpty() {

    return this->currentText().isEmpty();

}

void PComboBoxPlus::onEditingFinished(PVariant data) {

    emit editingFinished(fieldName, data.undefined("value", nil).toString());

}

void PComboBoxPlus::populateList() {

    actionButton->initMenu(this->itemsAndValues);

}
