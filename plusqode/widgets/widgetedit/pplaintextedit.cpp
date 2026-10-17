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



   #include "widgets/widgetedit/pplaintextedit.h"

   
   

PPlainTextEdit::PPlainTextEdit(QWidget *parent) :
    PFieldWidget(parent) {

    textEdit = new QTextEdit(this);
    
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(onEditingFinished()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(textEdit, 0, 0);

}

QWidget* PPlainTextEdit::mainWidget() {

    return textEdit;

}

PVariant PPlainTextEdit::data() {

    return textEdit->toPlainText();

}

void PPlainTextEdit::setData(PVariant data) {

    textEdit->setPlainText(data.toString());

}

void PPlainTextEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    textEdit->setPalette(pal);

}

void PPlainTextEdit::setReadOnly(bool value) {

    textEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());

}

void PPlainTextEdit::textChanged() {

    emit dataChanged(fieldName, data());

}

bool PPlainTextEdit::isEmpty() {

    return textEdit->toPlainText().isEmpty();

}

void PPlainTextEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
