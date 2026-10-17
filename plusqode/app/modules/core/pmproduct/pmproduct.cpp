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

#include "app/modules/core/pmproduct/pmproduct.h"
#include "app/modules/pmodules.h"

PMProduct::$PMProduct() {

    init(args);

}

PMProduct& PMProduct::init(PVariant args) {

    PModel::init(args);

    this->autoView = false;

    name$ = $pt(mandatory: true, main: true);

    QString goodId = $PMProductType().$find(name: 'good')->id$s;
    product_type_id$ = $pa(default: goodId, newButton: false, editButton: false, toTranslate: true);

    bool taxInclusiveMode = PSinglConfigurationManager::instance()->value("settings", "tax_inclusive_mode").toBool();
    bool notTaxInclusiveMode = !taxInclusiveMode;

    category_id$ = $pa();
    product_id$ = $pa();
    price$ = $pf(default: 0, readOnly: taxInclusiveMode);
    tax_rate_id$ = $pa();
    tax$ = $pf();
    price_with_tax$ = $pf(default: 0, readOnly: notTaxInclusiveMode);
    icon$ = $pt(fieldType: "image_edit");
    barcode$ = $pt();
    product_table$ = $pa();
    product_discount_table$ = $pa();
    description$ = $pt();
    selected$ = $pb(fieldType: "switch_edit"); 
    discount_rate$ = $pv(readOnly: true);
    discount_value$ = $pv(readOnly: true);
    price_with_discount$ = $pv(readOnly: true);
    final_price$ = $pv(readOnly: true);

    return *this;

}


void PMProduct::onChangeField(QString fieldName, PVariant data) {

    if(fieldName == "tax_rate_id")
        onChangeTaxRate();
    else if(fieldName == "price")
        onChangePrice();
    else if(fieldName == "price_with_tax")
        onChangePriceWithTax();
    else if(fieldName == "tax")
        onChangePrice();
    else if(fieldName == "product_discount_table")
        onChangePrice();

}

void PMProduct::checkValues() {

    if(price$s.simplified() == "")
        price$ = 0;
    if(price_with_tax$s.simplified() == "")
        price_with_tax$ = 0;
    if(tax$s.simplified() == "")
        tax$ = 0;

}


void PMProduct::onChangePrice() {

    if(!tax_rate_id$) return; // if not valorized

    checkValues();


    if(price$f == 0 and price_with_tax$f) // yousefull to database import to start from price_with_tax value
        price$ = PMath::taxableFromTotal(price_with_tax$f, tax_rate_id$->value$f);


    tax$ = PMath::taxFromTaxable(price$f, tax_rate_id$->value$f);
    price_with_tax$ = PMath::totalFromTaxable(price$f, tax_rate_id$->value$f);

    discount_rate$ = this->discount_rate();
    discount_value$ = this->discount_value();
    price_with_discount$ = this->price_with_discount();
    final_price$ = this->final_price();

    //currency$ = currency

}

void PMProduct::onChangePriceWithTax() {

    price$ = PMath::taxableFromTotal(price_with_tax$f, tax_rate_id$->value$f);
    onChangePrice();


}

void PMProduct::onChangeTaxRate() {

    onChangePrice();

}


PVariant PMProduct::discount_rate() {

    double tdr = 1;

    $this->product_discount_table$->forEach(PVariant discount) {
        if(QDate::currentDate() >= discount.begin_date$d and
           QDate::currentDate() <= discount.end_date$d)
            tdr *= 1 - (discount.rate$f / 100);
    }

    return (1 - tdr) * 100;

}



PVariant PMProduct::discount_value() {

    return price$f * discount_rate$f / (double)100;

}


PVariant PMProduct::price_with_discount() {

    return price$f - this->discount_value().toDouble();

}


PVariant PMProduct::final_price() {

    if(tax_rate_id$ == 0)
        return 0;

    return PMath::totalFromTaxable(price_with_discount$f, tax_rate_id$->value$f);

}
