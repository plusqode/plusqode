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



   #include "widgets/widgetedit/pcoloredit.h"

   
   

PColorEdit::PColorEdit(QWidget* parent) :
        PFieldWidget(parent) {

    lineEdit = new QLineEdit(this);
    lineEdit->setMinimumHeight(PGlobal::fieldMinimumHeight());
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

    toolButton = new QToolButton(this);
    toolButton->setText("...");
    connect(toolButton, SIGNAL(clicked()), this, SLOT(selectionColor()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);

    layout->addWidget(lineEdit, 0, 0);
    layout->addWidget(toolButton, 0, 1);

}

QWidget* PColorEdit::mainWidget() {

    return lineEdit;

}


PVariant PColorEdit::data() {

    return lineEdit->text();

}

void PColorEdit::setData(PVariant data) {

    lineEdit->setText(data.toString());
    if(!data.toString().isEmpty())
        setBackgroundColor(data.toString());

}

void PColorEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    lineEdit->setPalette(pal);

}

void PColorEdit::setReadOnly(bool value) {

    lineEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());
    toolButton->setHidden(value);

}


void PColorEdit::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PColorEdit::isEmpty() {

    return lineEdit->text().isEmpty();

}

void PColorEdit::selectionColor() {

    QColor color = QColorDialog::getColor(QColor(lineEdit->text()), this);
      if (color.isValid()) {
          lineEdit->setText(color.name());
          onEditingFinished();
          setBackgroundColor(color.name());
      }

}

void PColorEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
