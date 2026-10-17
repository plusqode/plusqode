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

#ifndef PPRINTERDRIVER_H
#define PPRINTERDRIVER_H

   #include <QFile>
   #include "variant/pvariant.h"
   #include "core/plogger.h"

class PPrinterDriver {

public:
    PPrinterDriver(const QString& destFileName, PVariant data);
    ~PPrinterDriver();
    QString descriptionRow(QString quantity,
                           QString description,
                           QString price,
                           QString totalPrice,
                           QString fillStr,
                           QString style);

    void loadValues();
    virtual int getPaperWidth() = 0;
    virtual void reset() {}
    virtual void setBold() {}
    virtual void setCharSize() {}
    virtual void setCharSize(int) {}
    virtual void setCenterJustify() {}
    virtual void fullCut() {}
    virtual void generatePulse() {}
    virtual void printSeparatorLine();
    virtual bool beginDocument();
    virtual bool endDocument();
    virtual void printLogo() {}
    virtual void startSection() {};
    virtual void endSection() {};
    virtual void initPrinter() {}   
    virtual void print(uint margin, const QString& str) {}
    virtual void println(uint margin, const QString& str) {}
    virtual void println(const QString& str) {}
    virtual void printFiscal(PVariant& document) {}

    virtual void printDocumentNumberFiscal(const QString& str) {}
    virtual void printCustomerFiscal(const QString& str) {}
    virtual void endCustomerHeader() {}

    virtual void printGeometry();
    virtual void printPrinterInfo();
    virtual void printHeader();
    virtual void printFooter();

    void printSections();
    virtual void printColumnsHeader(const QString& col1 = QObject::tr("Qty"),
                                    const QString& col2 = QObject::tr("Description"),
                                    const QString& col3 = QObject::tr("Price"),
                                    const QString& col4 = QObject::tr("Amount"));

    void printDocumentInfo();
    QString contactSection();
    QString discountSection();
    QString invoiceDiscountSection();
    QString paymentSection();
    void printMultiLinesSection(const QString& lines);
    QString documentInfo();
    void printPrefiscal();
    void printFiscal();
    void printInvoice();
    void printOrderFull();
    void printOrderFull2();
    void printOrderPartial();
    void printOrder();


public:

    PVariant data;

    QString methodName;
    QString fileName;
    QFile* file;
    QTextStream* stream;

    PVariant docAttrs;

    QString printerName;
    int charSize;
    QString ipAddress;
    QString port;

    int quantityFieldWidth;
    int priceFieldWidth;
    int totalPriceFieldWidth;
    int paperWidth;

};

#endif 



