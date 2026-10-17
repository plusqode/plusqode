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

#ifndef PPAYMENTDIALOG_H
#define PPAYMENTDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QMap>

#include "core/plogger.h"
#include "widgets/pklineedit.h"
#include "widgets/pactionbuttons.h"
#include "widgets/pvirtualkeyboard.h"
#include "widgets/widgetedit/plineedit.h"
#include "app/modules/core/pmpayment_mode/pmpayment_mode.h"
#include "app/modules/core/pmmessage_box/pmmessage_box.h"
#include "widgets/pnumberpad.h"

class PPaymentDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PPaymentDialog(QWidget *parent = 0);
    QWidget* summaryWidget();
    void setTotal(QVariant total);
    double totalPayment();
    PVariant payments();

signals:

public slots:
    void onClickButton(PVariant);
    void updateTotalPanel();
    void resetLineEdits();
    void accept();
    void rest();

public:
    QMap<QString, QLineEdit*> lineEdits;
    QMap<int, QString> ids;

    double total;
    double toPay;

    QLabel* totalLabel;
    QLabel* toPayLabel;

    QLineEdit* restLineEdit;

};

#endif // PPAYMENTDIALOG_H
