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



   #include "widgets/pklineedit.h"

   
   

PKLineEdit::PKLineEdit(QWidget* parent) :
    QLineEdit(parent) {

    connect(this, SIGNAL(clicked(PKLineEdit*)), this, SLOT(virtualKeyboard(PKLineEdit*)));

}

void PKLineEdit::mousePressEvent(QMouseEvent* event) {

    QLineEdit::mousePressEvent(event);
    emit(clicked(this));

}


void PKLineEdit::virtualKeyboard(PKLineEdit* lineEdit) {

    PVirtualKeyboard virtualKeyboard;
    virtualKeyboard.init();
    if(virtualKeyboard.exec() == QDialog::Accepted) {
        QString value = virtualKeyboard.lineEdit->text();
        if(value.isEmpty()) value = "0";
        this->setText(value);
        this->editingFinished();
        emit(accepted(this));
    }

}
