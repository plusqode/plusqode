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

#ifndef PMBARCODEMANAGER_H
#define PMBARCODEMANAGER_H

#include "app/modules/core/pmproduct/pmproduct.h"
#include "app/modules/core/pmmessage_box/pmmessage_box.h"
#include "app/modules/pos/pmpos_document/pmpos_document.h"
#include "pos/pepsontmt88.h"
#include "app/modules/warehouse/pmbarcode_printer/pmbarcode_printer.h"
#include "core/ptranslator.h"

class PMBarcodeManager : public PMProduct {

    Q_OBJECT
    
    $P_PARENT_VIEW

public:
    PMBarcodeManager(PVariant args);
    PMBarcodeManager& init(PVariant);
    PVariant action(PVariant button);
    
    virtual void onAfterTable();

public slots:
    void printBarcodeLabel(const QString& barcode = QString());
    void barcodeOnReturnPressed();


public:
    QLineEdit* barcodeLineEdit;

};

Q_DECLARE_METATYPE(PMBarcodeManager*)

#endif // PMBARCODEMANAGER_H
