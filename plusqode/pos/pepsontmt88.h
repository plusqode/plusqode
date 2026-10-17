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

#ifndef PEPSONTMT88_H
#define PEPSONTMT88_H

   #include "pos/pprinterdriver.h"

class PEpsonTMT88 : public PPrinterDriver
{
public:
    PEpsonTMT88(const QString& destFileName, PVariant data);

    virtual int getPaperWidth();

    virtual void startSection();
    virtual void endSection();

    virtual void reset();
    virtual void setBold();
    virtual void setCharSize();
    virtual void setCharSize(int);

    virtual void setCenterJustify();
    virtual void fullCut();
    virtual void generatePulse();
    virtual void openCashDrawer();

    virtual void print(uint margin, const QString& str);
    virtual void println(uint margin, const QString& str);
    virtual void println(const QString& str);
    virtual void printLogo();
    virtual void printRowFiscal(const QString& department, const QString& quantity, const QString& description, const QString& price);

    void setAlignment(int align);
    void printBarcode(PVariant);

    QString buffer;


};

#endif 



