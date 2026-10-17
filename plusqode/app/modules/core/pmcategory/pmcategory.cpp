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

#include "app/modules/core/pmcategory/pmcategory.h"
#include "app/modules/core/pmproduct/pmproduct.h"
#include "app/modules/core/pmtax_rate/pmtax_rate.h"
#include "app/modules/core/pmmessage_box/pmmessage_box.h"

PMCategory::$PMCategory() {

    init(args);

}

PMCategory& PMCategory::init(PVariant args) {

    PModel::init(args);

    name$ = $pt(mandatory: true, main: true);
    tax_rate_id$ = $pa(mandatory: false);
    category_id$ = $pa();
    //category_table$ = $pa();
    category_table$ = $pa(fieldType: 'tab_table', subModelName: 'product_table', subViewType: 'icon');
    icon$ = $pt(fieldType: "image_edit");
    product_table$ = $pa();

    QString applyTaxRateToCategoryButton =     
    "<menusection name='ApplyToCategory'>"
       "<menuitem action='ApplyTaxRateToCategory' icon=\"{name: 'picons/core/actions-128/ok.png', width:48, height: 48}\"/>"
    "</menusection>";

    apply_tax_rate_to_category_button$ = $pw(xml: applyTaxRateToCategoryButton);
    
    QString applyTaxRateToPartialProductButton =     
    "<menusection name='ApplyToPartialProduct'>"
       "<menuitem action='ApplyTaxRateToPartialProduct' icon=\"{name: 'picons/core/actions-128/ok.png', width:48, height: 48}\"/>"
    "</menusection>";

    apply_tax_rate_to_partial_product_button$ = $pw(xml: applyTaxRateToPartialProductButton);

    return *this;

}


void PMCategory::applyTaxRateToAllProduct() {

    PVariant categoryWitohutTaxRate = $[];

    PMCategory $category();
    category.$findBy();

    $category.forEach(PVariant categoryVariant) {

        if(category.tax_rate_id$ != 0) 
        $category.product_table$->forEach(PVariant product) {
                category.product_table$->tax_rate_id$ = category.tax_rate_id$->id$s;
                category.product_table$->onChangeTaxRate();
        }
        else
            categoryWitohutTaxRate << category.name$; 
            
        category.product_table$->saveAllRecords();

    }

    if(categoryWitohutTaxRate.isEmpty())
        return;

    QString text = $"Categories witout taxrate ${categoryWitohutTaxRate.toString()}";
    PMMessageBox::$messageBox(text: text,
                              icon: "picons/core/actions-128/stop.png");
}



void PMCategory::applyTaxRateToCategory() {

    $this->product_table$->forEach(PVariant product) {
        product_table$->tax_rate_id$ = tax_rate_id$->id$s;
        product_table$->onChangeTaxRate();
    }

    
    editingFinished("product_table", nil);

}


void PMCategory::applyTaxRateToPartialProduct() {

    $this->product_table$->forEach(PVariant product) {
        if(product_table$->tax_rate_id$ == 0) {
            product_table$->tax_rate_id$ = tax_rate_id$->id$s;
            product_table$->onChangeTaxRate();
        }
    }

    
    editingFinished("product_table", nil);

}


PVariant PMCategory::action(PVariant action) {

    if(action.action$ == "ApplyTaxRateToCategory")
        this->applyTaxRateToCategory();
    else if(action.action$ == "ApplyTaxRateToPartialProduct")
        this->applyTaxRateToPartialProduct();
    else if(action.action$ == "applyTaxRateToAllProduct")
        this->applyTaxRateToAllProduct();

    
    return ${type: "message_box", description: "apply successfully"};

}
