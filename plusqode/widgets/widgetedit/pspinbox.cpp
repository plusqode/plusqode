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



   #include "widgets/widgetedit/pspinbox.h"

   
   

PSpinBox::PSpinBox(QWidget *parent) :
    PFieldWidget(parent) {

    spinBox = new QSpinBox(this);
    spinBox->setMinimumHeight(PGlobal::fieldMinimumHeight());
    spinBox->setMaximum(1000);
    connect(spinBox, SIGNAL(valueChanged(QString)), this, SLOT(textChanged(QString)));
    connect(spinBox, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(spinBox, 0, 0);

}

void PSpinBox::setAttrs(PVariant attrs) {

    this->attrs = attrs;
    if(attrs. undefined("minimum", nil)!= nil) spinBox->setMinimum(attrs.undefined("minimum", nil).toInt());
    if(attrs. undefined("maximum", nil)!= nil) spinBox->setMaximum(attrs.undefined("maximum", nil).toInt());
    if(attrs. undefined("singleStep", nil)!= nil) spinBox->setSingleStep(attrs.undefined("singleStep", nil).toInt());

}

QWidget* PSpinBox::mainWidget() {

    return spinBox;

}


PVariant PSpinBox::data() {

    return spinBox->text();

}

void PSpinBox::setData(PVariant data) {

    spinBox->setValue(data.toInt());

}

void PSpinBox::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    spinBox->setPalette(pal);

}


void PSpinBox::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PSpinBox::isEmpty() {

    return spinBox->text().isEmpty();

}


void PSpinBox::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
