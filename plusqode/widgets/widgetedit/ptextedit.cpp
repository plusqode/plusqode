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




   #include "widgets/widgetedit/ptextedit.h"


   

   

PTextEdit::PTextEdit(QWidget *parent) :
    PFieldWidget(parent) {

    textEdit = new QTextEdit(this);
    
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onEditingFinished()));


    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(textEdit, 0, 0);

}

QWidget* PTextEdit::mainWidget() {

    return textEdit;

}

PVariant PTextEdit::data() {

    return textEdit->toHtml();

}

void PTextEdit::setData(PVariant data) {

    textEdit->setText(data.toString());

}

void PTextEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    textEdit->setPalette(pal);

}

void PTextEdit::setReadOnly(bool value) {

    textEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());

}

void PTextEdit::textChanged() {

    emit dataChanged(fieldName, data());

}

bool PTextEdit::isEmpty() {

    return textEdit->toPlainText().isEmpty();

}


void PTextEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
