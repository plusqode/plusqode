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



   #include "widgets/widgetedit/ptimeedit.h"

   
   

PTimeEdit::PTimeEdit(QWidget *parent)
    : PFieldWidget(parent) {

    timeEdit = new QTimeEdit(this);
    timeEdit->setMinimumHeight(PGlobal::fieldMinimumHeight());
    timeEdit->setDisplayFormat("HH:mm");
    connect(timeEdit, SIGNAL(timeChanged(QTime)), this, SLOT(timeChanged(QTime)));
    connect(timeEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(timeEdit, 0, 0);

    timeEdit->setCalendarPopup(true);

}


QWidget* PTimeEdit::mainWidget() {

    return timeEdit;

}


PVariant PTimeEdit::data() {

    QVariant result = timeEdit->time();
    return result;

}

void PTimeEdit::setData(PVariant data) {

    timeEdit->setTime(data.toTime());

}

void PTimeEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    timeEdit->setPalette(pal);

}

void PTimeEdit::setReadOnly(bool value) {

    timeEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());

}

void PTimeEdit::timeChanged(QTime time) {

    emit dataChanged(fieldName, data());

}

bool PTimeEdit::isEmpty() {

    return timeEdit->text().isEmpty();

}

void PTimeEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
