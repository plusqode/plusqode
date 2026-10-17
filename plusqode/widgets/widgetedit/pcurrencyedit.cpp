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



   #include "widgets/widgetedit/pcurrencyedit.h"

   
   

PCurrencyEdit::PCurrencyEdit(QWidget *parent, int decimals) :
        PFieldWidget(parent) {

    lineEdit = new QLineEdit(this);
    lineEdit->setMinimumHeight(PGlobal::fieldMinimumHeight());
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(lineEdit, 0, 0);

    QDoubleValidator* doubleValidator = new QDoubleValidator(this);

    doubleValidator->setDecimals(decimals);

    lineEdit->setValidator(doubleValidator);

    

    lineEdit->setAlignment(Qt::AlignRight);

}

QWidget* PCurrencyEdit::mainWidget() {

    return lineEdit;

}


PVariant PCurrencyEdit::data() {

    return lineEdit->text();

}

void PCurrencyEdit::setData(PVariant data) {

    lineEdit->setText(data.toString());

}

void PCurrencyEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    lineEdit->setPalette(pal);

}

void PCurrencyEdit::setReadOnly(bool value) {

    lineEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());

}


void PCurrencyEdit::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PCurrencyEdit::isEmpty() {

    return lineEdit->text().isEmpty();

}

void PCurrencyEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
