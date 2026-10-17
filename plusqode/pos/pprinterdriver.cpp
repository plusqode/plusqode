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







   #include "pos/pprinterdriver.h"





   




   
   #include "app/modules/core/pmcontact/pmcontact.h"





   




   
   




   
   
 
   #include "app/modules/core/pmdocument_type/pmdocument_type.h"





   




   
   




   
   
 
   




   
   
 
   
 
 
   #include "app/modules/core/pmdocument_attrs/pmdocument_attrs.h"





   




   
   




   
   
 
   




   
   
 
   
 
 
   




   
   
 
   
 
 
   
 
 
 
   #include "misc/pmath.h"





   




   
   




   
   
 
   




   
   
 
   
 
 
   




   
   
 
   
 
 
   
 
 
 
   




   
   
 
   
 
 
   
 
 
 
   
 
 
 
 


PPrinterDriver::PPrinterDriver(const QString& destFileName, PVariant data)
    : fileName(destFileName), data(data) {

    file = new QFile(destFileName);

    if (!file->open(QIODevice::WriteOnly)) {
        qDebug() << "PPrinterDriver::PPrinterDriver(...): Unable To Open File" << "\n";
        return;
    }

    stream = new QTextStream(file);

    PLog().debug() << data.toString();

}


PPrinterDriver::~PPrinterDriver() {

    if(!file) return;

    file->close();
    delete stream;
    delete file;

}

void PPrinterDriver::loadValues() {

    PMDocumentType documentType(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    QString documentTypeName = data.undefined("document_type", nil).toString();
    documentType. find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", documentTypeName)))));

    docAttrs = documentType.undefined("document_attrs_id", nil).value<PModelPtr>().value<PMDocumentAttrs*>()->current();

    quantityFieldWidth = docAttrs.undefined("quantity_field_width", nil).toInt();
    priceFieldWidth = docAttrs.undefined("price_field_width", nil).toInt();
    totalPriceFieldWidth = docAttrs.undefined("total_price_field_width", nil).toInt();
    paperWidth = docAttrs.undefined("paper_width", nil).toInt();

    charSize = docAttrs.undefined("char_size", nil).toInt();

    if(paperWidth == 0)
        paperWidth = getPaperWidth();

    if(data.undefined("document_type", nil).toString() == "Pos Prefiscal")
        printPrefiscal();
    else if(data.undefined("document_type", nil).toString() == "Pos Fiscal")
        printFiscal();
    else if(data.undefined("document_type", nil).toString() == "Pos Invoice")
        printInvoice();
    else if(data.undefined("document_type", nil).toString() == "Pos Order")
        printOrder();


}


QString PPrinterDriver::descriptionRow(QString quantity,
                                        QString description,
                                        QString price,
                                        QString totalPrice,
                                        QString fillStr,
                                        QString style) {

    QChar fillChar = fillStr[0];

    QString result;
    int descriptionFieldWidth;

    if (style == "qdpt") {

        descriptionFieldWidth = paperWidth - quantityFieldWidth -  priceFieldWidth - totalPriceFieldWidth - 1;

        result = QString(quantity).rightJustified ( quantityFieldWidth, ' ' ) + " " +
                 QString(description.leftJustified ( descriptionFieldWidth, fillChar ).left(descriptionFieldWidth )) +
                 QString(price.rightJustified ( priceFieldWidth, fillChar )) +
                 QString(totalPrice.rightJustified ( totalPriceFieldWidth, ' ' ));
    }


    else if (style == "qxdpt") {

        descriptionFieldWidth = paperWidth - quantityFieldWidth -  priceFieldWidth - totalPriceFieldWidth - 3;

        result = QString(quantity).rightJustified ( quantityFieldWidth, ' ' ) + " x " +
                 QString(description.leftJustified ( descriptionFieldWidth, fillChar ).left(descriptionFieldWidth )) +
                 QString(price.rightJustified ( priceFieldWidth, fillChar )) +
                 QString(totalPrice.rightJustified ( totalPriceFieldWidth, ' ' ));

    }


    else if (style == "qxdtDoubleLine") {

        descriptionFieldWidth = paperWidth - totalPriceFieldWidth;

        result =  quantity + " x " +
                        price + "\n" +
                        QString(description.leftJustified ( descriptionFieldWidth, fillChar ).left(descriptionFieldWidth )) +
                        QString(totalPrice.rightJustified ( totalPriceFieldWidth, fillChar ));

    }

    else if (style == "qxd") {

        descriptionFieldWidth = paperWidth - quantityFieldWidth - 3;

        result = QString(quantity).rightJustified ( quantityFieldWidth, ' ' ) + " x " +
                 QString(description.leftJustified ( descriptionFieldWidth, fillChar ).left(descriptionFieldWidth ));

    }

    else if (style == "qd") {

        descriptionFieldWidth = paperWidth - quantityFieldWidth - 3;

        result = QString(quantity).rightJustified ( quantityFieldWidth, ' ' ) + " " +
                 QString(description.leftJustified ( descriptionFieldWidth, ' ' ).left(descriptionFieldWidth ));
    }


    else if (style == "date-amount-type") {

        QString date = quantity;

        int dateFieldWidth = 15;

        descriptionFieldWidth = paperWidth - dateFieldWidth - priceFieldWidth - 3;

        result = QString(date).leftJustified ( dateFieldWidth, ' ' ) +
                 QString(description.leftJustified ( descriptionFieldWidth, fillChar ).left(descriptionFieldWidth )) +
                 QString(price.rightJustified ( priceFieldWidth, fillChar ));

    }

    return result;

}


void PPrinterDriver::printSeparatorLine() {

        println(QString("").leftJustified ( paperWidth, '=' ));

}

bool PPrinterDriver::beginDocument() {

        reset();
        return true;

}


bool PPrinterDriver::endDocument() {

        endSection();

        return true;

}


void PPrinterDriver::printGeometry() {

    if(!docAttrs.undefined("printGeometryValue", nil).toBool())
        return;

    for(int i = 0; i < docAttrs.undefined("top_margin", nil).toInt(); i++)
        println("");

}


void PPrinterDriver::printPrinterInfo() {

    setCenterJustify();
    println(docAttrs.undefined("name", nil).toString());

    if(!data.undefined("printer_name", nil).toString().isEmpty())
        println(data.undefined("printer_name", nil).toString());

    printSeparatorLine();

}


void PPrinterDriver::printHeader() {

    if(!docAttrs.undefined("print_header", nil).toBool())
        return;

    PVariant headerLines = docAttrs.undefined("header", nil).split(",");

    setCenterJustify();
     headerLines.forEachQString([&] (QString line) mutable {
            println(line);
    });

    printSeparatorLine();

}


void PPrinterDriver::printFooter() {

    if(!docAttrs.undefined("print_footer", nil).toBool())
        return;

    printSeparatorLine();

    PVariant footerLines = docAttrs.undefined("footer", nil).split(",");

    setCenterJustify();
     footerLines.forEachQString([&] (QString line) mutable {
            println(line);
    });

}


void PPrinterDriver::printSections() {

    printGeometry();
    printLogo();
    printHeader();
    printPrinterInfo();
    printDocumentInfo();
    printMultiLinesSection(contactSection());

}

void PPrinterDriver::printColumnsHeader(const QString& col1,
                                         const QString& col2,
                                         const QString& col3,
                                         const QString& col4) {


        setBold();
        println(descriptionRow(col1, col2, col3, col4, " ", "qdpt"));
        setCharSize(charSize);


}

QString PPrinterDriver::contactSection() {

    if(!docAttrs.undefined("print_customer", nil).toBool())
        return "";

    QString contactId = data["document"]["contact_id"].toString();
    PMContact contact(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    contact. find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", contactId)))));QStringList lines;
lines << "CUSTOMER";
 PVariant row = contact.current(); 
    row.forEachQString_QString([&] (QString fieldName,QString fieldValue) mutable { 
 if(docAttrs(PString(QString("print_%1").arg(fieldName))).toBool()) 
lines << "" +  PString(QString(" - %1: %2").arg(PString(PTranslator::tr(fieldName)).capitalize(" ")).arg(fieldValue))  + "";
 }); 
lines << "${=}";
lines << "";
return lines.join("\n");

}

QString PPrinterDriver::discountSection() {

 


QString discountRate =  data.undefined("document", nil).undefined("discount_rate", nil).toString();
QString discountValue = data.undefined("document", nil).undefined("discount_value_with_tax", nil).toString();

if(!discountValue.toDouble()) return "";QStringList lines;
lines << "DISCOUNT";
lines << "" +  PString(QString(" - %1: %2%").arg(PString(PTranslator::tr("Discount Rate")).capitalize(" ")).arg(discountRate))  + "";
lines << "" +  PString(QString(" - %1: %2").arg(PString(PTranslator::tr("Discount Value")).capitalize(" ")).arg(discountValue))  + "";
lines << "";
return lines.join("\n");

}

QString PPrinterDriver::invoiceDiscountSection() {

 


QString discountRate =  data.undefined("document", nil).undefined("discount_rate", nil).toString();
QString discountValue = data.undefined("document", nil).undefined("discount_value", nil).toString();

if(!discountValue.toDouble()) return "";QStringList lines;
lines << "DISCOUNT";
lines << "" +  PString(QString(" - %1: %2%").arg(PString(PTranslator::tr("Discount Rate")).capitalize(" ")).arg(discountRate))  + "";
lines << "" +  PString(QString(" - %1: %2").arg(PString(PTranslator::tr("Discount Value")).capitalize(" ")).arg(discountValue))  + "";
lines << "";
return lines.join("\n");

}


QString PPrinterDriver::paymentSection() {QStringList lines;
lines << "";
lines << "${=}";
lines << "PAYMENTS";
  data.
 undefined("document", nil).
 undefined("payments", nil).forEachPVariant([&] (PVariant p) mutable { 
 QString amount = PVariant(p.undefined("amount", nil).toDouble()).toString();  
lines << "" +  PString(QString(" - %1: %2").arg(PString(PTranslator::tr(p.undefined("name", nil).toString())).capitalize(" ")).arg(amount))  + "";
 }); 
lines << "${=}";
lines << "";
return lines.join("\n");

}


void PPrinterDriver::printMultiLinesSection(const QString& section) {

    PVariant lines = PString(section).split("\n");

     lines.forEachQString([&] (QString line) mutable {
        if(line.startsWith("${") and line.endsWith("}")) line = QString("").leftJustified ( paperWidth, line[2] );
        println(0, line);
    });

}

QString PPrinterDriver::documentInfo() {QStringList lines;
lines << "Document Info";
    data.
 undefined("document", nil).forEachQString_QString([&] (QString fieldName,QString fieldValue) mutable { 
 if(docAttrs(PString(QString("print_%1").arg(fieldName))).toBool()) 
lines << "" +  PString(QString(" - %1: %2").arg(PString(PTranslator::tr(fieldName)).capitalize(" ")).arg(fieldValue))  + "";
 }); 
lines << "${=}";
return lines.join("\n");

}


void PPrinterDriver::printDocumentInfo() {

    setCharSize(charSize);

    PVariant lines = PString(documentInfo()).split("\n");

     lines.forEachQString([&] (QString line) mutable {
        if(line.startsWith("${") and line.endsWith("}")) line = QString("").leftJustified ( paperWidth, line[2] );
        println(0, line);
    });

}


void PPrinterDriver::printPrefiscal() {

    printSections();

    PVariant documentItems = data.undefined("document_items", nil);
    printColumnsHeader();
     documentItems.forEachPVariant([&] (PVariant documentItem) mutable {
        println(descriptionRow(documentItem.undefined("quantity", nil).toString(), documentItem.undefined("name", nil).toString(), documentItem.undefined("price_with_tax", nil).toString(), documentItem.undefined("total", nil).toString(),  ".", "qdpt"));
        if(documentItem.undefined("discount_value", nil).toDouble()) {
            QString discount = PTranslator::tr("Discount");
            println(descriptionRow("", PString(QString("%1 %2% %3").arg(discount).arg(documentItem.undefined("discount_rate", nil).toString()).arg(documentItem.undefined("discount_value_with_tax", nil).toString())), documentItem.undefined("price_with_discount_and_tax", nil).toString(), documentItem.undefined("total_with_discount", nil).toString(),  " ", "qdpt"));
        }
    });

    println("");
    setBold();
    printMultiLinesSection(discountSection());
    println(descriptionRow("", "TOTAL", "", data.undefined("document", nil).undefined("total", nil).toString(), ".", "qdpt"));
    printMultiLinesSection(paymentSection());

    printFooter();
    endDocument();

}


void PPrinterDriver::printFiscal() {

    beginDocument();

    printFiscal(data);

    endDocument();

}


void PPrinterDriver::printInvoice() {

    printSections();

    PVariant documentItems = data.undefined("document_items", nil);
    printColumnsHeader();
     documentItems.forEachPVariant([&] (PVariant documentItem) mutable {
        println(descriptionRow(documentItem.undefined("quantity", nil).toString(), documentItem.undefined("name", nil).toString(), documentItem.undefined("price", nil).toString(), documentItem.undefined("amount", nil).toString(),  ".", "qdpt"));
        if(documentItem.undefined("discount_value", nil).toDouble()) {
            QString discount = PTranslator::tr("Discount");
            println(descriptionRow("", PString(QString("%1 %2% - %3").arg(discount).arg(documentItem.undefined("discount_rate", nil).toString()).arg(documentItem.undefined("discount_value", nil).toString())), documentItem.undefined("price_with_discount", nil).toString(), documentItem.undefined("amount_with_discount", nil).toString(),  " ", "qdpt"));
        }
    });

    println("");
    setBold();
    printMultiLinesSection(invoiceDiscountSection());

    PVariant vs = PVariant::fromString(data.undefined("document", nil).undefined("vat_summary", nil).toString());

    println(descriptionRow("VAT", "TAXABLE", "TAX", "TOTAL", ".", "qdpt"));

       vs.forEachQString_PVariant([&] (QString key,PVariant vat) mutable {
        println(descriptionRow(PString(QString("%1%").arg(key)), vat.undefined("taxable", nil).toString(), vat.undefined("rounded_tax", nil).toString(), vat.undefined("total", nil).toString(), ".", "qdpt"));
    });

    println(descriptionRow("", data.undefined("document", nil).undefined("taxable", nil).toString(), data.undefined("document", nil).undefined("tax", nil).toString(), data.undefined("document", nil).undefined("total", nil).toString(), ".", "qdpt"));

    printMultiLinesSection(paymentSection());

    printFooter();
    endDocument();

}


void PPrinterDriver::printOrderFull() {

    QString printerId = data["printer_id"].toString();

    PVariant documentItems = data.undefined("document_items", nil);

    printSections();

    println(descriptionRow(PTranslator::tr("Qty"), PTranslator::tr("Description"), "", "", " ", "qd"));
     documentItems.forEachPVariant([&] (PVariant documentItem) mutable {

        if(documentItem["pos_printer_id"] == printerId)
            setCharSize(1);
        else
            setCharSize();

        println(descriptionRow(documentItem.undefined("quantity", nil).toString(), documentItem.undefined("name", nil).toString(), documentItem.undefined("price_with_tax", nil).toString(), documentItem.undefined("total", nil).toString(),  " ", "qd"));

    });

    println("");
    printFooter();
    endDocument();

}


void PPrinterDriver::printOrderFull2() {

    QString printerId = data["printer_id"].toString();

    PVariant documentItems = data.undefined("document_items", nil);


    
    
    
    bool result = false;
     documentItems.forEachPVariant([&] (PVariant documentItem) mutable {
        if(documentItem["pos_printer_id"] == printerId)
            result = true;
    });
    if(!result) return;
    


    printSections();

    println(descriptionRow(PTranslator::tr("Qty"), PTranslator::tr("Description"), "", "", " ", "qd"));
     documentItems.forEachPVariant([&] (PVariant documentItem) mutable {

        if(documentItem["pos_printer_id"] == printerId)
            setCharSize(1);
        else
            setCharSize();

        println(descriptionRow(documentItem.undefined("quantity", nil).toString(), documentItem.undefined("name", nil).toString(), documentItem.undefined("price_with_tax", nil).toString(), documentItem.undefined("total", nil).toString(),  " ", "qd"));

    });

    println("");
    printFooter();
    endDocument();

}


void PPrinterDriver::printOrderPartial() {

    QString printerId = data["printer_id"].toString();

    PVariant documentItems = data.undefined("document_items", nil);

    bool result = false;
     documentItems.forEachPVariant([&] (PVariant documentItem) mutable {
        if(documentItem["pos_printer_id"] == printerId)
            result = true;
    });
    if(!result) return;


    printSections();

    println(descriptionRow(PTranslator::tr("Qty"), PTranslator::tr("Description"), "", "", " ", "qd"));
     documentItems.forEachPVariant([&] (PVariant documentItem) mutable {
        if(documentItem["pos_printer_id"] == printerId)
            println(descriptionRow(documentItem.undefined("quantity", nil).toString(), documentItem.undefined("name", nil).toString(), documentItem.undefined("price_with_tax", nil).toString(), documentItem.undefined("total", nil).toString(),  " ", "qd"));
    });

    println("");
    printFooter();
    endDocument();


}


void PPrinterDriver::printOrder() {

    QString printType = data.undefined("print_type", nil).toString();

    if(printType == "full")
        this->printOrderFull();
    else if(printType == "full2")
        this->printOrderFull2();
    else if(printType == "partial")
        this->printOrderPartial();
    else
        PLog().error() << "PPrinterDriver::printOrder():" << printType  << " not found";

}
