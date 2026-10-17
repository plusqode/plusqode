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



   #include "widgets/widgetedit/pcombobox.h"

   
   

PComboBox::PComboBox(PVariant itemsAndValues, QWidget *parent) :
        PFieldWidget(parent) {

    this->itemsAndValues = itemsAndValues;
    comboBox = new QComboBox(this);
    comboBox->setEditable(true); 

    comboBox->setMinimumHeight(PGlobal::fieldMinimumHeight());
    comboBox->setFont(PGlobal::widgetFont());

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    connect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(textChanged(QString)));
    connect(comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onEditingFinished(QString)));
#else
    connect(comboBox, &QComboBox::currentTextChanged, this, [this]() {
        onEditingFinished(comboBox->currentText());
    });
    connect(comboBox->lineEdit(), &QLineEdit::editingFinished, this, [this]() {
        onEditingFinished(comboBox->currentText());
    });
#endif


    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(comboBox, 0, 0);

    populateList();

}

QWidget* PComboBox::mainWidget() {

    return comboBox;

}

PVariant PComboBox::data() {

    int index = comboBox->currentIndex();
    return comboBox->itemData(index);

}

void PComboBox::setData(PVariant data) {

    comboBox->setCurrentIndex(comboBox->findData(data.toString()));

}

void PComboBox::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    comboBox->setPalette(pal);



}

void PComboBox::setReadOnly(bool value) {

    comboBox->setEditable(value);
    comboBox->setEnabled(!value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());
    comboBox->setStyleSheet(PString(QString("QComboBox {color: black}")));

}

void PComboBox::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PComboBox::isEmpty() {

    return comboBox->currentText().isEmpty();

}

void PComboBox::onEditingFinished(QString) {

    emit editingFinished(fieldName, data());

}

void PComboBox::populateList() {

         itemsAndValues.forEachWithIndexQString_QString_int([&] (QString key,QString value,int i) mutable {
        comboBox->insertItem(i, value, key);
    });

    
    

}
