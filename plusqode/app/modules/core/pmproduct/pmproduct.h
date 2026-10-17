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

#ifndef PMPRODUCT_H
#define PMPRODUCT_H

#include "sql/pmodel.h"
#include "misc/pmath.h"

class PMProduct : public PModel {

    Q_OBJECT

public:
    PMProduct() {}
    PMProduct(PVariant args);
    PMProduct& init(PVariant);
    
    void checkValues();
    Q_INVOKABLE PVariant discount_rate();
    Q_INVOKABLE PVariant discount_value();
    Q_INVOKABLE PVariant price_with_discount();
    Q_INVOKABLE PVariant final_price();

public slots:
    void onChangeField(QString fieldName, PVariant data);

    void onChangePrice();
    void onChangePriceWithTax();
    void onChangeTaxRate();
        
};

Q_DECLARE_METATYPE(PMProduct*)

#endif // PMPRODUCT_H
