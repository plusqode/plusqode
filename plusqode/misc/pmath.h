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

#ifndef PMATH_H
#define PMATH_H

   #include <QtGlobal>
   #include <QtCore/qmath.h>

#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
       #include <QRandomGenerator>
#endif

class PMath {

public:
    PMath();
    static void initRandSequence();
    static int rand();
    static double round(double value);
    static double taxFromTaxable(double taxable, double tax_rate);
    static double totalFromTaxable(double taxable, double tax_rate);
    static double taxableFromTotal(double total, double tax_rate);
    static double degreesToRadians(int degrees);
    static double sin(int degrees);
    static double cos(int degrees);
    static double valueByPercentage(int value, int percentage);

};

#endif 



