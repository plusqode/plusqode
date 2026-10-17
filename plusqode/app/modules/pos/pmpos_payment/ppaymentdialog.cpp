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

#include "app/modules/pos/pmpos_payment/ppaymentdialog.h"

PPaymentDialog::PPaymentDialog(QWidget *parent) :
    QDialog(parent) {

    this->setMinimumSize(600, 240);
    //this->setMaximumSize(480, 300);

    QGridLayout* gridLayout = new QGridLayout(this);

    gridLayout->addWidget(summaryWidget(), 0, 0);

    restLineEdit = new PKLineEdit(this);
    restLineEdit->setFont(PGlobal::mainFieldFont());
    restLineEdit->setFont(QFont("Courier 10 Pitch", 18));
    restLineEdit->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum));
    restLineEdit->setMaximumWidth(150);
    QDoubleValidator* doubleValidator = new QDoubleValidator(restLineEdit);
    doubleValidator->setDecimals(PGlobal::decimalPrecision());
    restLineEdit->setValidator(doubleValidator);
    restLineEdit->setAlignment(Qt::AlignRight);
    restLineEdit->setText("Rest");
    gridLayout->addWidget(restLineEdit, 0, 1);
    connect(restLineEdit, SIGNAL(accepted(PKLineEdit*)), this, SLOT(rest()));


    QPushButton* okButton = new QPushButton(this);
    okButton->setMinimumSize(150, 80);
    okButton->setIcon(QIcon("picons/core/actions-128/ok.png"));
    okButton->setIconSize(QSize(48, 48));
    connect(okButton, SIGNAL(pressed()), this, SLOT(accept()));
    gridLayout->addWidget(okButton, 0, 2);

    PMPaymentMode $paymentMode();
    paymentMode.$find();

    $paymentMode.forEach(PVariant pm, int i) {
        PActionButton* paymentModeButton = new PActionButton(${name: pm.name$, mode: pm.name$}, this);
        paymentModeButton->setTextAlignment("center");
        paymentModeButton->textLabel->setWordWrap(true);
        paymentModeButton->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        paymentModeButton->setMinimumSize(150, 40);
        connect(paymentModeButton, SIGNAL(click(PVariant)), this, SLOT(onClickButton(PVariant)));
        gridLayout->addWidget(paymentModeButton, i + 1, 0);
    }


    $paymentMode.forEach(PVariant pm, int i) {
        ids[i] = pm.id$s;
        PKLineEdit* lineEdit = new PKLineEdit(this);
        lineEdits[pm.name$s] = lineEdit;
        lineEdit->setFont(PGlobal::mainFieldFont());
        lineEdit->setFont(QFont("Courier 10 Pitch", 18));
        lineEdit->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum));
        lineEdit->setMaximumWidth(150);
        lineEdit->setText("0");
        QDoubleValidator* doubleValidator = new QDoubleValidator(lineEdit);
        doubleValidator->setDecimals(PGlobal::decimalPrecision());
        lineEdit->setValidator(doubleValidator);
        lineEdit->setAlignment(Qt::AlignRight);
        gridLayout->addWidget(lineEdit, i + 1, 1);
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(updateTotalPanel()));
    }

}


QWidget* PPaymentDialog::summaryWidget() {

    QWidget* widget = new QWidget(this);
    QGridLayout* gridLayout = new QGridLayout(widget);

    totalLabel = new QLabel("TOTAL", widget);
    totalLabel->setFont(QFont("Courier 10 Pitch", 30));
    gridLayout->addWidget(totalLabel, 0, 0);

    toPayLabel = new QLabel("TOTAL", widget);
    toPayLabel->setFont(QFont("Courier 10 Pitch", 30));
    gridLayout->addWidget(toPayLabel, 1, 0);

    return widget;

}


void PPaymentDialog::setTotal(QVariant tot) {

    this->total = this->toPay = tot.toDouble();

    QString totalStr = QString::number(this->total, 'f', PGlobal::decimalPrecision());

    totalLabel->setText($"TOTAL:${totalStr}");
    toPayLabel->setText($"ToPay:${totalStr}");

}


void PPaymentDialog::updateTotalPanel() {

    this->toPay = this->total - this->totalPayment();

    QString toPayStr = QString::number(this->toPay, 'f', PGlobal::decimalPrecision());

    toPayLabel->setText($"ToPay:${toPayStr}");

    QPalette pal(toPayLabel->palette());
    if(toPay)
        pal.setColor(QPalette::WindowText, "red");
    else
        pal.setColor(QPalette::WindowText, "green");

    toPayLabel->setPalette(pal);

}


void PPaymentDialog::onClickButton(PVariant button) {

    PLog().error() << "- - - - - >" << button.toString() << this->toPay;

    if(this->toPay and lineEdits[button.mode$s]->text().toDouble() == 0) {
        lineEdits[button.mode$s]->setText(QVariant(this->toPay).toString());
        updateTotalPanel();
    }

}


double PPaymentDialog::totalPayment() {

    QList<QLineEdit*> values = lineEdits.values();

    double total = 0;
    for(int i = 0; i < values.count(); i++)
        total += values[i]->text().toDouble();

    return total;

}


void PPaymentDialog::resetLineEdits() {

    QList<QLineEdit*> values = lineEdits.values();

    int total = 0;
    for(int i = 0; i < values.count(); i++)
        values[i]->setText("0");

}


void PPaymentDialog::accept() {

    if(this->toPay == 0)
        QDialog::accept();
    else
        PMMessageBox::$messageBox(text: "Sum Payment Failed !!!", icon: "picons/core/actions-128/ko.png");

}


void PPaymentDialog::rest() {

    if(restLineEdit->text().toDouble() == 0)
        return;

    double result = restLineEdit->text().toDouble() - this->total;

    restLineEdit->setText(PVariant(result).toString());

}


PVariant PPaymentDialog::payments() {

    PVariant result = $[];

    PMPaymentMode $paymentMode();
    paymentMode.$find();

    $paymentMode.forEach(PVariant pm) {
        QLineEdit* lineEdit = lineEdits[pm.name$s];
        PVariant rec = ${amount: lineEdit->text(), payment_mode_id: pm.id$, name: pm.name$, tender: pm.tender$};
        if(lineEdits[pm.name$s]->text().toDouble()) result << rec;

    }

    return result;

}
