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



   #include "widgets/widgetedit/pbooledit.h"

   
   

PBoolEdit::PBoolEdit(QWidget *parent) :
    PFieldWidget(parent) {

    checkBox = new QCheckBox(this);
    checkBox->setMinimumHeight(PGlobal::fieldMinimumHeight());
    connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(onEditingFinished()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(checkBox, 0, 0);

}

QWidget* PBoolEdit::mainWidget() {

    return checkBox;

}


PVariant PBoolEdit::data() {

    return checkBox->checkState() == Qt::Checked;

}

void PBoolEdit::setData(PVariant data) {

    checkBox->setChecked(data.toBool());

}

void PBoolEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    checkBox->setPalette(pal);

}

void PBoolEdit::setReadOnly(bool value) {

    setDisabled(true);
    setStyleSheet(PString(QString("QCheckBox {color: black}"))); 

}

void PBoolEdit::stateChanged(int state) {

    emit dataChanged(fieldName, data());

}

bool PBoolEdit::isEmpty() {

    return false;

}

void PBoolEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
