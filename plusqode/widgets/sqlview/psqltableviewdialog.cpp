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



   #include "widgets/sqlview/psqltableviewdialog.h"

   
   

PSqlTableViewDialog::PSqlTableViewDialog(PVariant args) {

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    sqlTableView = new PSqlGroupTableView(args);

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->addWidget(sqlTableView, 0, 0);
    gridLayout->addWidget(buttonBox, 1, 0);

}


void PSqlTableViewDialog::accept() {

    QDialog::accept();

}



void PSqlTableViewDialog::reject() {

    QDialog::reject();

}
