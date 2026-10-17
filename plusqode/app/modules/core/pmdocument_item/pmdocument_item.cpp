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

#include "app/modules/core/pmdocument_item/pmdocument_item.h"
#include "app/modules/pmodules.h"

PMDocumentItem::$PMDocumentItem() {

    init(args);

}

PMDocumentItem& PMDocumentItem::init(PVariant args) {

    PModel::init(args);

    product_id$ = $pa(mandatory: true, newButton: false, editButton: false, editable: false);
    name$ = $pt(mandatory: true);
    description$ = $pt(mandatory: false, fieldType: "plain_text_edit");
    document_id$ = $pm2o(modelName: "document", onDelete: true);
    quantity$ = $pf();
    price$ = $pf();
    discount_rate$ = $pf();
    discount_value$ = $pf();
    price_with_discount$ = $pf();

    tax_rate_id$ = $pm2o(newButton: false, editButton: false, modelName: "tax_rate", editable: false, mandatory: true);
    tax_value$ = $pf(readOnly: true);
    price_with_tax$ = $pf();
    discount_value_with_tax$ = $pf(readOnly: true);
    price_with_discount_and_tax$ = $pf();

    tax_total$ = $pf(readOnly: true);
    discount_total$ = $pf(readOnly: true);
    amount$ = $pf();
    total$ = $pf();
    
    amount_with_discount$ = $pf();
    total_with_discount$ = $pf();

    return *this;

}


void PMDocumentItem::initAccounting() {
    
    if(tax_rate_id$ == 0) 
        return;

    double tax_rate = tax_rate_id$->value$f;
    acc.init(price_with_tax$f, discount_rate$f, tax_rate, quantity$f);

}



void PMDocumentItem::updateAccounting() {

    quantity$ = acc.round(acc.quantity);
    price$ = acc.round(acc.price);
    discount_rate$ = acc.round(acc.discount_rate);
    discount_value$ = acc.round(acc.discount_value);
    price_with_discount$ = acc.round(acc.price_with_discount);

    tax_value$ = acc.round(acc.rounded_tax_value);
    price_with_tax$ = acc.round(acc.t_price);
    discount_value_with_tax$ = acc.round(acc.rounded_t_discount_value);
    price_with_discount_and_tax$ = acc.round(acc.t_price_with_discount);

    tax_total$ = acc.round(acc.rounded_q_tax_value);
    discount_total$ = acc.round(acc.rounded_qt_discount_value);
    amount$ = acc.round(acc.q_price);
    total$ = acc.round(acc.qt_price);

    amount_with_discount$ = acc.round(acc.q_price_with_discount);
    total_with_discount$ = acc.round(acc.qt_price_with_discount);

}




bool PMDocumentItem::onOkDialog() {

    if(product_id$ == 0) { 
        QMessageBox msgBox;
        msgBox.setText("You Must Select Product Id");
        msgBox.exec();
        return false;
    }

    return true;

}


PVariant PMDocumentItem::currency() {

    return QString("€ %1 - %2").arg(total$s).arg(tax_rate_id$->name$s);
}


void PMDocumentItem::onChangeField(QString fieldName, PVariant data) {
    
    if(product_id$ == 0) {
        resetValues();
        return;
    }

    this->initAccounting();
    

    if(fieldName == "product_id")
        onChangeProduct();
    else if(fieldName == "quantity") {
        double tax_rate = tax_rate_id$->value$f;
        acc.init(price_with_tax$f, discount_rate$f, tax_rate, quantity$f);
    }
    else if(fieldName == "discount_rate")
        acc.onChange_discount_rate(discount_rate$f);
    else if(fieldName == "discount_value")
        acc.onChange_discount_value(discount_value$f);
    else if(fieldName == "price_with_discount")
        acc.onChange_price_with_discount(price_with_discount$f);
    else if(fieldName == "price_with_discount_and_tax")
        acc.onChange_t_price_with_discount(price_with_discount_and_tax$f);
    else if(fieldName == "amount_with_discount")
        acc.onChange_q_price_with_discount(amount_with_discount$f);
    else if(fieldName == "total_with_discount")
        acc.onChange_qt_price_with_discount(total_with_discount$f);
    else if(fieldName == "tax_rate_id") {

        if(!tax_rate_id$) return; // if not valorized

        bool taxInclusiveMode = PSinglConfigurationManager::instance()->value("settings", "tax_inclusive_mode").toBool();
        double tax_rate = tax_rate_id$->value$f;
        if(taxInclusiveMode) 
            acc.init(price_with_tax$f, discount_rate$f, tax_rate, quantity$f);
        else 
            acc.$initByPrice(price: price$f, discount_rate: discount_rate$f, tax_rate: tax_rate, quantity: quantity$f);

    }
    else if(fieldName == "price") 
        this->onChangePrice();
    else if(fieldName == "price_with_tax") 
        this->onChangePriceWithTax();
    else if(fieldName == "tax_value")
        ;
    else if(fieldName == "tax_total")
        ;
    else if(fieldName == "amount")
        acc.onChange_q_price(amount$f);
    else if(fieldName == "total")
        acc.onChange_qt_price(total$f);

    this->updateAccounting();

}

void PMDocumentItem::resetValues() {
    
    name$ = "";
    description$ = "";
    quantity$ = 0;
    tax_rate_id$ = 0;
    price$ = 0;
    price_with_tax$ = 0;
    price_with_discount$ = 0;
    price_with_discount_and_tax$ = 0;
    tax_value$ = 0;
    tax_total$ = 0;
    amount$ = 0;
    total$ = 0;
    discount_rate$ = 0;
    discount_value$ = 0;
    discount_value_with_tax$ = 0;
    amount_with_discount$ = 0;
    total_with_discount$ = 0;

}

void PMDocumentItem::checkValues() {

    if(quantity$s.simplified() == "")
        quantity$ = 0;
    if(price$s.simplified() == "")
        price$ = 0;
    if(price_with_tax$s.simplified() == "")
        price_with_tax$ = 0;
    if(price_with_discount_and_tax$s.simplified() == "")
        price_with_discount_and_tax$ = 0;
    if(tax_value$s.simplified() == "")
        tax_value$ = 0;
    if(amount$s.simplified() == "")
        amount$ = 0;
    if(total$s.simplified() == "")
        total$ = 0;
    if(amount_with_discount$s.simplified() == "")
        amount_with_discount$ = 0;
    if(total_with_discount$s.simplified() == "")
        total_with_discount$ = 0;

    if(discount_rate$s.simplified() == "")
        discount_rate$ = 0;
    if(discount_value$s.simplified() == "")
        discount_value$ = 0;
    if(price_with_discount$s.simplified() == "")
        price_with_discount$ = 0;
}




void PMDocumentItem::onChangeProduct() {
    
    if(product_id$->tax_rate_id$ == 0) {
        QString text = $"Article ${product_id$->name$s} without VAT !!!";
        PMMessageBox::$messageBox(text: text, icon: "picons/core/actions-128/ko.png");
        return;
    }


    name$ = product_id$->name$;
    description$ = product_id$->description$;
    tax_rate_id$ = product_id$->tax_rate_id$->id$;
    discount_rate$ = product_id$->discount_rate();
    price_with_tax$ = product_id$->price_with_tax$;
    
    double tax_rate = tax_rate_id$->value$f;
    acc.init(price_with_tax$f, tax_rate, discount_rate$f, quantity$f);

}


void PMDocumentItem::onChangePrice() {

    if(!tax_rate_id$) return; // if not valorized
    checkValues();
    double tax_rate = tax_rate_id$->value$f;

    // It's fobidden, only for internal use
    acc.$initByPrice(price: price$f, 
                  tax_rate: tax_rate, 
             discount_rate: discount_rate$f, 
                  quantity: quantity$f);

}


void PMDocumentItem::onChangePriceWithTax() {

    acc.onChange_t_price(price_with_tax$f);

}
