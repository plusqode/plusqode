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





   #include "widgets/pnumberpad.h"



   


   

PNumberPad::PNumberPad(QWidget* parent) {

    QWidget::setParent(parent);

    buttonGridLayout = new QGridLayout(this);
    buttonGridLayout->setContentsMargins(0,0,0,0);
    buttonGridLayout->setSpacing(0);

    display = new QLabel(this);
    display->setFont(QFont("Helvetica", 18, QFont::Bold));
    display->setAlignment(Qt::AlignRight);
    setValue("0");
    buttonGridLayout->addWidget(display, 0, 0);

    actionButtons = new PActionButtons(this);
    PVariant buttons = actionButtons->numberPad3();
    PActionButtons::setButtonSize(buttons, 80, 60);
    actionButtons->initByVariant(buttons);
    connect(actionButtons, SIGNAL(click(PVariant)), this, SLOT(numberPad_onClick(PVariant)));
    buttonGridLayout->addWidget(actionButtons, 1, 0);

}

PNumberPad::~PNumberPad() {

}

void PNumberPad::setValue(QString value) {

    this->value = value;
    display->setText(value);

}

double PNumberPad::getValue() {

    return value.replace(",", ".").toDouble();

}

void PNumberPad::numberPad_onClick(PVariant button) {

    if(button. undefined("name", nil) ==  "Cancel") {
        QDialog::reject();
        return;
    }

    if(button. undefined("name", nil) ==  "Ok") {
        QDialog::accept();
        return;
    }

    if(button. undefined("name", nil) ==  "C") {
        setValue("0");
        return;
    }

    if(button. undefined("name", nil) ==  "," && value.indexOf(",") != -1)
        return;

    if(button. undefined("name", nil) ==  "," && value == "0") {
        setValue(value + button.undefined("name", nil).toString());
        return;
    }

    if(display->text() == "0")
        setValue("");

    setValue(value + button.undefined("name", nil).toString());

}
