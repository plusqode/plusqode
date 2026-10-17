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

#include "app/modules/pos/pmpos_print_manager/pmpos_print_manager.h"
#include "app/modules/pmodules.h"

PMPosPrintManager::$PMPosPrintManager() {

    init(args);

}

PMPosPrintManager& PMPosPrintManager::init(PVariant args) {

    PModel::init(args);

    name$ = $pt();
    machine_ip_address$ = $pt();
    printer_name$ = $pt();
    print_command$ = $pt();
    ip_address$ = $pt();
    port$ = $pt();
    filename$ = $pt();
    copy_number$ = $pi();
    printed$ = $pb(default: false);

    return *this;

}

QString PMPosPrintManager::prefiscalTemplate(PVariant rec) {
§



§
}


void PMPosPrintManager::print() {

    PConfiguration config(filename$s);
    PVariant data = config.cfg();

    PLog().debug() << "Document Type:" << data.documnt_type$s;

    if($["Pos Prefiscal", "Pos Invoice", "Pos Order"].include(data.document_type$s)) {
        PEpsonTMT88* epson = new PEpsonTMT88(filename$s + ".out", data);
        epson->loadValues();
        delete epson;
    }
    else if(data.document_type$s == "Pos Fiscal") {
        PXonXoff* epson = new PXonXoff(filename$s + ".out", data);
        epson->loadValues();
        delete epson;
    }


    qDebug() << ip_address$s << port$i << filename$s + ".out" << copy_number$i << "\n";

    if(PEpsonTMT88Lan::send(ip_address$s, port$i, filename$s + ".out", copy_number$i)) {
        this->printed$ = true;
    }

}


void PMPosPrintManager::check() {

    //PSleeper sleeper;

    QString myIpAddress = $PMSetting().$find()->ip_address$s;

    while(true) {
        sleep(1);
        this->$find(machine_ip_address: myIpAddress, printed: false);

        $this->forEach(PVariant rec) {
            qDebug() << rec.toString() << "\n";
            //qDebug() << PDir::fileContent(rec.filename$s) << "\n";
            print();
        }
        apply();
    }

}

