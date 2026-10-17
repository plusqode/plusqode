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

#include "app/modules/pos/pmpos_printer/pmpos_printer.h"

PMPosPrinter::$PMPosPrinter() {

    init(args);

}

PMPosPrinter& PMPosPrinter::init(PVariant args) {

    PModel::init(args);

    name$ = $pt(mandatory: true, main: true);
    document_type_id$ = $pa(mandatory: true, newButton: false);
    ip_address$ = $pt(mandatory: true);
    port$ = $pt(mandatory: true);
    pos_printer_driver_id$ = $pa(mandatory: true, editButton: false, newButton: false);

    return *this;

}


void PMPosPrinter::onAfterWidget() {
   
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QRegExp ipRegex ("^" + ipRange
            + "(\\." + ipRange + ")"
            + "(\\." + ipRange + ")"
            + "(\\." + ipRange + ")$");
    QValidator *ipValidator = new QRegExpValidator(ipRegex, this);
#else
    QRegularExpression ipRegex ("^" + ipRange
                                + "(\\." + ipRange + ")"
                                + "(\\." + ipRange + ")"
                                + "(\\." + ipRange + ")$");
    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(ipRegex, this);
#endif


    QLineEdit* lineEdit = dynamic_cast<PLineEdit*>(ip_address$w)->lineEdit;
    lineEdit->setValidator(ipValidator);
    //lineEdit->setInputMask("000.000.000.000");

}  
