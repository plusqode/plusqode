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

#include "app/modules/warehouse/pmbarcode_manager/pmbarcode_manager.h"
#include "app/modules/pmodules.h"


// attenzione se il barcode non e' valido la stampate stampa sempre lo stesso
// Es. di barcode validi: 8001234567897, 1234567890001


PMBarcodeManager::$PMBarcodeManager() {
 
    init(args);

}

PMBarcodeManager& PMBarcodeManager::init(PVariant args) {

    PMProduct::init(args);

    barcodeLineEdit = 0;

    return *this;

}

void PMBarcodeManager::onAfterTable() {
    
    PMBarcodePrinter $barcodePrinter();
    barcodePrinter.$find();
    if(barcodePrinter.count() == 0) 
        return;
    
    if(!barcodePrinter.scan_and_print$b)
        return;

    QWidget* controlPanelGridWidget = sqlView->findChild<QWidget*>("barcode-panelWidget");

    QGridLayout* controlPanelGridLayout = controlPanelGridWidget->findChild<QGridLayout*>("barcode-panelGridLayout");

    if(controlPanelGridLayout == 0) return;
    
    barcodeLineEdit = new QLineEdit(controlPanelGridWidget);
    controlPanelGridLayout->addWidget(barcodeLineEdit, 0, 2);
    connect(barcodeLineEdit, SIGNAL(returnPressed()), this, SLOT(barcodeOnReturnPressed()));

    QFont font = barcodeLineEdit->font();
    font.setPixelSize(20);
    barcodeLineEdit->setFont(font);


}


void PMBarcodeManager::printBarcodeLabel(const QString& barcode) {

    PMBarcodePrinter $barcodePrinter();
    barcodePrinter.$find();

    if(barcodePrinter.count() == 0) {
        PMMessageBox::$messageBox(text: "You have to add a printer in BarcodePrinter Table",
                                  icon: "picons/core/actions-128/stop.png");
        return;
    }


   
    PMPosDocument $posDocument();
    
    QString filename = posDocument.writeFile("barcode.bin", "BarcodeLabel", "");

    PEpsonTMT88* epson = new PEpsonTMT88(filename, "");
    
    PModelPtr product = PModel::model("product");
    product->setParent(this);

    if(barcode.isEmpty())
        product->$findBy_selected$(true);
    else
        product->$findBy_barcode$(barcode);

    QByteArray data;

    epson->reset();
    $product->forEach(PVariant p) {

        if(p.barcode$s.isEmpty()) {
            QString barcode = p.barcode$s;
            QString text = $"${p.name$s} without barcode";
            PMMessageBox::$messageBox(text: text,
                                      icon: "picons/core/actions-128/stop.png");

        }

        epson->setCharSize(barcodePrinter.font_size$i);
        epson->setAlignment(barcodePrinter.alignment$i);
        if(barcodePrinter.print_name$b) {
            epson->print(0, barcodePrinter.prefix$s);
            epson->print(0, p.name$s);
        }
        if(barcodePrinter.print_price$b) { 
            epson->print(3, p.final_price$s);
            epson->print(0, barcodePrinter.suffix$s);
        }
        if(barcodePrinter.print_barcode$b) 
            epson->$printBarcode(barcode: p.barcode$,
                                 type: barcodePrinter.barcode_type$, 
                                 width: barcodePrinter.barcode_width$, height: barcodePrinter.barcode_height$,
                                 font: barcodePrinter.font$);
        epson->fullCut();
    }

    QString copyNumber = "1";

    delete epson;

    PEpsonTMT88Lan::send(barcodePrinter.ip_address$s, barcodePrinter.port$i, filename, copyNumber.toInt());

}


PVariant PMBarcodeManager::action(PVariant button) {

    if(button.action$s == "setToPrint") {
        
        PTranslator::generateTranslationFile(); 
        
        PVariant ids = this->sqlView->idSelectionList();
        if(ids.count() == 0)
            return nil;
        
        $PSql().update("product", ${selected: true}, ${id: ids});

    }
    
    if(button.action$s == "print") {

        this->printBarcodeLabel(); 
        return nil;

    }
    
    if(button.action$s == "reset") {

        if(PMMessageBox::$messageBox(text: "All records will be unselected, do You Want to continue ?",
                                     icon: "picons/core/actions-128/stop.png", cancel: true)
            == QDialog::Accepted) {
            $PSql().update("product", ${selected: false}, ${selected: true});
            return ${type: "action", action: "reload_table"};
        }

        return nil;

    }



    return ${type: "action", action: "reload_table"};

}


void PMBarcodeManager::barcodeOnReturnPressed() {

    printBarcodeLabel(barcodeLineEdit->text());
    barcodeLineEdit->setText("");

}
