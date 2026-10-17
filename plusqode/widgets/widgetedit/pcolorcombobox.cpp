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



   #include "widgets/widgetedit/pcolorcombobox.h"

   
   

PColorComboBox::PColorComboBox(QWidget *parent) :
        PFieldWidget(parent) {

    comboBox = new QComboBox(this);
    comboBox->setMinimumHeight(PGlobal::fieldMinimumHeight());
    comboBox->setEditable(true); 

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

QWidget* PColorComboBox::mainWidget() {

    return comboBox;

}


PVariant PColorComboBox::data() {

    return comboBox->currentText();

}

void PColorComboBox::setData(PVariant data) {

    comboBox->setCurrentIndex(comboBox->findText(data.toString()));

}

void PColorComboBox::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    comboBox->setPalette(pal);

}

void PColorComboBox::setReadOnly(bool value) {

    comboBox->setEditable(value);
    comboBox->setEnabled(!value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());
    comboBox->setStyleSheet(PString(QString("QComboBox {color: black}")));

}

void PColorComboBox::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PColorComboBox::isEmpty() {

    return comboBox->currentText().isEmpty();

}

void PColorComboBox::onEditingFinished(QString) {

    emit editingFinished(fieldName, data());

}

void PColorComboBox::populateList() {

    PVariant colorNames = PVariant::fromQStringList(QColor::colorNames());

       colorNames.forEachWithIndexQString_int([&] (QString colorName,int i) mutable {
        QColor color(colorName);
        comboBox->insertItem(i, colorName);
        comboBox->setItemData(i, color, Qt::DecorationRole);
    });
}
