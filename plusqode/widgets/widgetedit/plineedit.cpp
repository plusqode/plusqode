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




   #include "widgets/widgetedit/plineedit.h"


   

   

PLineEdit::PLineEdit(QWidget *parent) :
    PFieldWidget(parent) {

    lineEdit = new QLineEdit(this);
    lineEdit->setMinimumHeight(PGlobal::fieldMinimumHeight());
    lineEdit->setFont(PGlobal::widgetFont());

    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

    layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(lineEdit, 0, 0);

}

void PLineEdit::setAttrs(PVariant fieldAttrs) {

    PFieldWidget::setAttrs(fieldAttrs);

    if(fieldAttrs. undefined("password", nil)!= nil)
        lineEdit->setEchoMode(QLineEdit::Password);

}


QWidget* PLineEdit::mainWidget() {

    return lineEdit;

}

PVariant PLineEdit::data() {

    return lineEdit->text();

}

void PLineEdit::setData(PVariant data) {

    lineEdit->setText(data.toString());

}

void PLineEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    lineEdit->setPalette(pal);

}

void PLineEdit::setReadOnly(bool value) {

    lineEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());

}

void PLineEdit::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PLineEdit::isEmpty() {

    return lineEdit->text().isEmpty();

}


void PLineEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
