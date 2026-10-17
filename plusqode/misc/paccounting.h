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

#ifndef PACCOUNTING_H
#define PACCOUNTING_H

   #include "variant/pvariant.h"
   #include "core/pglobal.h"

   #include <cmath>


class PAccounting
{
public:
    PAccounting();

    double round(double value);
    double taxFromTaxable(double taxable, double tax_rate);
    double totalFromTaxable(double taxable, double tax_rate);
    double taxableFromTotal(double total, double tax_rate);
    double discountRate(PVariant discountRateList);
    PVariant vatSummary(PVariant documentItems, double discount_rate = 0);
    PVariant vatSummaryTotals(PVariant documentItems, double discount_rate = 0);

    void init(double t_price, double discount_rate, double tax_rate, double quantity);
    void initByPrice(PVariant); 
    void onChange_q_price(double);
    void onChange_t_price(double);
    void onChange_t_price_with_discount(double);
    void onChange_q_price_with_discount(double q_price_with_discount);
    void onChange_qt_price_with_discount(double qt_price_with_discount);
    void onChange_qt_price(double qt_price);
    void onChange_discount_rate(double discount_rate);
    void onChange_discount_value(double discount_value);
    void onChange_tax_rate(double tax_rate);
    void onChange_price_with_discount(double price_with_discount);

    static QString toString(PVariant map);
    void show();

    static void test();

    double quantity;

    double price;
    double discount_rate;
    double discount_value;
    double price_with_discount;

    double q_price;
    double q_discount_value;
    double q_price_with_discount;

    double tax_rate;
    double tax_value;

    double t_price;
    double t_discount_value;
    double t_price_with_discount;

    double qt_price;
    double qt_discount_value;
    double qt_price_with_discount;

    double q_tax_value;
    double rounded_tax_value;
    double rounded_q_tax_value;

    double rounded_t_discount_value;
    double rounded_qt_discount_value;


};

#endif 



