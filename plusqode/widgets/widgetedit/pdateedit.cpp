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



   #include "widgets/widgetedit/pdateedit.h"

   
   

PDateEdit::PDateEdit(QWidget *parent)
    : PFieldWidget(parent) {

    dateEdit = new QDateEdit(this);
    dateEdit->setMinimumHeight(PGlobal::fieldMinimumHeight());
    connect(dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(dateChanged(QDate)));
    connect(dateEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));


    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(dateEdit, 0, 0);

    dateEdit->setCalendarPopup(true);

}

QWidget* PDateEdit::mainWidget() {

    return dateEdit;

}

PVariant PDateEdit::data() {

    QVariant result = dateEdit->date();
    return result;

}

void PDateEdit::setData(PVariant data) {

    dateEdit->setDate(data.toDate());

}

void PDateEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    dateEdit->setPalette(pal);

}


void PDateEdit::setReadOnly(bool value) {

    dateEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());

}

void PDateEdit::dateChanged(QDate date) {

    emit dataChanged(fieldName, data());

}

bool PDateEdit::isEmpty() {

    return dateEdit->text().isEmpty();

}

void PDateEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
