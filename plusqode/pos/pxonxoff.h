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

#ifndef PXONXOFF_H
#define PXONXOFF_H

   #include "pos/pprinterdriver.h"

class PXonXoff : public PPrinterDriver
{
public:
    PXonXoff(const QString& destFileName, PVariant data);

    virtual int getPaperWidth();

    virtual void startSection();
    virtual void endSection();

    virtual void reset();
    virtual void setCharSize();
    virtual void setCharSize(int);
    virtual void setCenterJustify();

    virtual void print(uint margin, const QString& str);
    virtual void println(uint margin, const QString& str);
    virtual void println(const QString& str);
    virtual void printFiscal(PVariant& elem);

    QString buffer;
    QString fiscalCode;
    QString alignment;


};

#endif 



