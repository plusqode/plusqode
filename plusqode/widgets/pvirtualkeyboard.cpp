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



   #include "widgets/pvirtualkeyboard.h"

   
   

PVirtualKeyboard::PVirtualKeyboard(QWidget* parent) :
        QDialog(parent) {

    this->setWindowTitle("Virtual Keyboard");

    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    buttonBox->setObjectName("dialogButtonBox");

    okButton = buttonBox->addButton("Ok", QDialogButtonBox::AcceptRole);
    okButton->setMinimumHeight(40);
    okButton->setIcon(QIcon(":/picons/core/actions/ok.png"));

    cancelButton = buttonBox->addButton("Cancel", QDialogButtonBox::AcceptRole);
    cancelButton->setMinimumHeight(40);
    cancelButton->setIcon(QIcon(":/picons/core/actions/delete.png"));

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    
    buttonBox->setCenterButtons(true);

    lineEdit = new QLineEdit(this);
    lineEdit->setFont(PGlobal::mainFieldFont());
    lineEdit->setFont(QFont("Courier 10 Pitch", 18));
    lineEdit->setAlignment(Qt::AlignRight);
    QDoubleValidator* doubleValidator = new QDoubleValidator(lineEdit);
    doubleValidator->setDecimals(PGlobal::decimalPrecision());
    lineEdit->setValidator(doubleValidator);

    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(lineEdit, 0, 0);
    gridLayout->addWidget(buttonBox, 2, 0);

}


void PVirtualKeyboard::accept() {

    okButton->setFocus();

    QDialog::accept();

}

void PVirtualKeyboard::reject() {

    QDialog::reject();

}

void PVirtualKeyboard::keyboardOnClick(PVariant button) {

    QString text = lineEdit->text();

    if(button.undefined("name", nil).toString() == "C") {
        text.chop(1);
        lineEdit->setText(text);
        return;
    }
    else if(button.undefined("name", nil).toString() == ",")
        text += ".";
    else
        text += button.undefined("name", nil).toString();

    int pos;
    if(lineEdit->validator()->validate(text, pos) == QValidator::Acceptable)
        lineEdit->setText(text);


}

void PVirtualKeyboard::init() {

    PActionButtons* actionButtons = new PActionButtons(this);
    PVariant buttons = actionButtons->numberPad4();
    PActionButtons::setButtonSize(buttons, 30, 40);
    actionButtons->initByVariant(buttons);
    connect(actionButtons, SIGNAL(click(PVariant)), this, SLOT(keyboardOnClick(PVariant)));
    gridLayout->addWidget(actionButtons, 1, 0);

}
