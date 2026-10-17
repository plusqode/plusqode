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



   #include "widgets/widgetedit/pdatetimeedit.h"

   
   

PDateTimeEdit::PDateTimeEdit(QWidget *parent)
    : PFieldWidget (parent)
{

    dateTimeEdit = new QDateTimeEdit(this);
    dateTimeEdit->setMinimumHeight(PGlobal::fieldMinimumHeight());
    connect(dateTimeEdit, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateTimeChanged(QDateTime)));
    connect(dateTimeEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(dateTimeEdit, 0, 0);

    dateTimeEdit->setCalendarPopup(true);


}

QWidget* PDateTimeEdit::mainWidget() {

    return dateTimeEdit;

}


PVariant PDateTimeEdit::data() {

    QVariant result = dateTimeEdit->dateTime();
    return result;

}

void PDateTimeEdit::setData(PVariant data) {

    dateTimeEdit->setDateTime(data.toDateTime());

}

void PDateTimeEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    dateTimeEdit->setPalette(pal);

}

void PDateTimeEdit::setReadOnly(bool value) {

    dateTimeEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());

}

void PDateTimeEdit::dateTimeChanged(QDateTime dateTime) {

    emit dataChanged(fieldName, data());

}

bool PDateTimeEdit::isEmpty() {

    return dateTimeEdit->text().isEmpty();

}

void PDateTimeEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
