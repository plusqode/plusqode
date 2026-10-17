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




   #include "misc/pmath.h"


   

   
   #include "core/pglobal.h"


   

   
   

   
   
 



PMath::PMath() {
}

void PMath::initRandSequence() {

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    qsrand(QDateTime::currentMSecsSinceEpoch());
#endif

}

int PMath::rand() {

#if QT_VERSION > QT_VERSION_CHECK(6, 0, 0)
    return QRandomGenerator::global()->generate();
#else
    return qrand();
#endif

}

double PMath::round(double value) {

    return QString::number(value, 'f', PGlobal::decimalPrecision()).toDouble();

}

double PMath::taxFromTaxable(double taxable, double tax_rate) {

    return taxable * tax_rate / 100;

}

double PMath::totalFromTaxable(double taxable, double tax_rate) {

    return taxable + PMath::taxFromTaxable(taxable, tax_rate);

}

double PMath::taxableFromTotal(double total, double tax_rate) {

    return total * (100 / (tax_rate + 100));

}


double PMath::degreesToRadians(int degrees) {

    return degrees * M_PI / 180;

}


double PMath::sin(int degrees) {


    return qSin(degreesToRadians(degrees));


}

double PMath::cos(int degrees) {


    return qCos(degreesToRadians(degrees));


}


double PMath::valueByPercentage(int value, int percentage) {

    return value * percentage / 100;

}
