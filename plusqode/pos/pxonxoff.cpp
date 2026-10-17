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



   #include "pos/pxonxoff.h"

   
   

PXonXoff::PXonXoff(const QString& destFileName, PVariant data)
    : PPrinterDriver(destFileName, data) {
}


int PXonXoff::getPaperWidth() {

    return 32;

}


void PXonXoff::startSection() {

    *stream << QString("\n");

    

}


void PXonXoff::endSection() {

    

}

void PXonXoff::reset() {

    char reset[] = {27,  '@', 29, '!', 8, '\0'};
    print(0, reset);

}

void PXonXoff::setCharSize() {

    alignment = "left";

}


void PXonXoff::setCharSize(int size) {

    alignment = "left";

}


void PXonXoff::setCenterJustify() {

    alignment = "center";

}


void PXonXoff::print(uint margin, const QString& str) {

    QString newStr = str;

    buffer += QString("").leftJustified(margin)  + newStr;

}


void PXonXoff::println(uint margin, const QString& str) {

    uint leftMargin = 0;

    print(margin, str);
    print(0, QString("\"@\n"));

    if (alignment == "center")
        leftMargin = (7 + getPaperWidth() - buffer.length()) / 2;

    *stream << buffer.insert(1, QString("").leftJustified(leftMargin));
    buffer = "\"";


}

void PXonXoff::println(const QString& str) {

    println(0, str);

}

void PXonXoff::printFiscal(PVariant& data) {

    PVariant documentItems = data.undefined("document_items", nil);

     documentItems.forEachPVariant([&] (PVariant item) mutable {

        
        double price_with_tax = item.undefined("price_with_tax", nil).toDouble() * 100;

        if (price_with_tax == 0)
            return;

        QString department = item.undefined("department", nil).toString();

        QString line = PString(QString("%1*%2H%3R\r\n").arg(item.undefined("quantity", nil).toString()).arg(price_with_tax).arg(department)).replace(',','.');
        *stream << PString(QString("\"%1\"%2").arg(item.undefined("name", nil).toString()).arg(line));

        if (item.undefined("discount_value_with_tax", nil).toDouble()) {
            double discount_total = item.undefined("discount_total", nil).toDouble() * 100;
            
            *stream << "=" << PString(QString("%1H3M\r\n").arg(discount_total)).replace(',','.');
        }


    });


    if (data.undefined("document", nil).undefined("discount_value_with_tax", nil).toDouble()) {
        double discount_value_with_tax = data.undefined("document", nil).undefined("discount_value_with_tax", nil).toDouble() * 100;
        *stream << "=" << PString(QString("%1H4M\r\n").arg(discount_value_with_tax)).replace(',','.');
    }


     data.


    undefined("document", nil).


    undefined("payments", nil).forEachPVariant([&] (PVariant p) mutable {
        double amount = p.undefined("amount", nil).toDouble() * 100;
        *stream << PString(QString("%1%2\r\n").arg(amount).arg(p.undefined("tender", nil).toString())).replace(',','.');
    });


}
