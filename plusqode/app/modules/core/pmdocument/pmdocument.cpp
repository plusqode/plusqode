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

#include "app/modules/core/pmdocument/pmdocument.h"
#include "widgets/sqlview/psqlformviewdialog.h"
#include "app/modules/pmodules.h"

PMDocument::$PMDocument() {

    init(args);

}

PMDocument& PMDocument::init(PVariant args) {

    PModel::init(args);

    sortField = "serial";
    showField = "serial";

    states = ${};

    states.draft$ =      ${arcs: ['confirmed'],         label: 'Draft',  hue: 1};
    states.confirmed$ =  ${arcs: ['cancelled'],         label: 'Confim', hue: 1};
    states.paid$ =       ${arcs: [],                    label: 'Pay',    hue: 140};
    states.cancelled$ =  ${arcs: [],                    label: 'Cancel', hue: 1};
    
    //    states.other$ =      ${name: 'Other', action: 'setOther', args: {value: 'otherState'}, style: 'background-color: blue'};

    state$ = $pt(fieldType: "state_progress_bar", states: states, default: "draft");

    selected$ = $pb(fieldType: "switch_edit");
    pos_id$ = $pa();
    document_id$ = $pa(readOnly: true, fieldType: 'text');
    document_type_id$ = $pa(readOnly: false, toTranslate: true);
    document_state_id$ = $pa(newButton: false, editButton: false, label: "Document State", toTranslate: true);
    serial$ = $pt(readOnly: true);
    date$ = $pd();
    user_manager_id$ = $pa(readOnly: true);
    contact_id$ = $pa(sortField: ["contact_name", "contact_surname"], mandatory: true);
    taxable_no_discount$ = $pf(readOnly: true);
    total_no_discount$ = $pf(readOnly: true);
    discount_rate$ = $pf();
    discount_value$ = $pf();
    discount_value_with_tax$ = $pf();
    taxable$ = $pf(totalizable: true);
    tax$ = $pf(readOnly: true, totalizable: true);
    total$ = $pf(totalizable: true);
    to_pay_progress$ = $pv(readOnly: true, fieldType: "progress_bar_plus", style: 'mac');
    paid_progress$ = $pv(readOnly: true, fieldType: "progress_bar_plus", style: 'mac');
    to_pay$ = $pf(readOnly: true);
    paid$ = $pf(readOnly: true);

    document_item_table$ = $pa();
    payment_table$ = $pa();

    notes$ = $pt(modelName: "notes", fieldType: "sqltextcombobox");

    vat_summary$ = $pt();

    return *this;

}

PVariant PMDocument::to_pay_progress() {

    return 100 - paid_progress().toInt();

}


PVariant PMDocument::paid_progress() {

    if(total$i == 0)
        return 100;

    return paid$i * 100 / total$i;

}


void PMDocument::onChangeField(QString fieldName, PVariant data) {

    if(fieldName == "discount_rate")
        onChangeDiscountRate();
    else if(fieldName == "discount_value")
        onChangeDiscountValue();
    else if(fieldName == "discount_value_with_tax")
        onChangeDiscountValueWithTax();
    else if(fieldName == "document_item_table")
        onChangeDocumentItemTable();
    else if(fieldName == "taxable")
        onChangeTaxable();
    else if(fieldName == "total")
        onChangeTotal();
    else if(fieldName == "payment_table")
        onChangePaymentTable();

}



void PMDocument::onChangeDiscountRate() {

    discount_value$ = PMath::taxFromTaxable(taxable_no_discount$f, discount_rate$f);
    discount_value_with_tax$ = PMath::totalFromTaxable(discount_value$f, discount_rate$f);
    onChangeDocumentItemTable();

}



void PMDocument::onChangeDiscountValue() {

    discount_rate$ = discount_value$f * 100 / taxable_no_discount$f;
    onChangeDocumentItemTable();

}

void PMDocument::onChangeDiscountValueWithTax() {

    discount_rate$ = discount_value_with_tax$f * 100 / total_no_discount$f;
    onChangeDocumentItemTable();

}


void PMDocument::onChangeTaxable() {
    
    discount_value$ = taxable_no_discount$f - taxable$f;
    onChangeDiscountValue();

}


void PMDocument::onChangeTotal() {

    double _total = total$f;

    discount_rate$ = 0;
    onChangeDiscountRate();
    discount_rate$ = (1 - (_total / (taxable$f + tax$f))) * 100;
    onChangeDiscountRate();

}

/* La procedura prevede di raggruppare gli articoli per aliquote 
 * Il calcolo parte dal totale in modo da poter gestire i 2 casi (prezzo + iva e prezzo ivato) senza perdere centesimi
 * Una volta ottenura la sommatoria delle varie aliquote si passa al calcolo dello sconto seguendo la seguente procedura
 *
 * Ecco un es. notare che anche se il prezzo lordo è 2,70 il calcolo continua con 2,703 
 * - Articolo 1 (IVA 10%)
 *   Prezzo lordo: 3,00 Euro
 *   Sconto 9,9% = 3,00 x 0,099 = 0,297
 *   Prezzo lordo scontato = 3,00 - 0,297 = 2,703 ~ 2,70 
 *   Imponibile = 2,703 / 1,10 = 2,46
 *   IVA 10% = 0,24
 *   Totale = 2,70
 *
 */


void PMDocument::onChangeDocumentItemTable() {

    PVariant documentItems = $[];

    PModelPtr model = document_item_table$;
    $model->forEach(PVariant documentItem) {
        documentItems << ${tax_rate: model->tax_rate_id$->value$, qt_price_with_discount: documentItem.total_with_discount$};
    }
    
    
    PAccounting acc;

    PVariant vs = acc.vatSummaryTotals(documentItems, discount_rate$f);

    PVariant vs_no_discont = acc.vatSummaryTotals(documentItems);

    taxable_no_discount$ = vs_no_discont.taxable$;
    taxable$ = acc.round(vs.taxable$f);
    tax$ = acc.round(vs.rounded_tax$f);
    total_no_discount$  = vs_no_discont.total$f;

    total$ = acc.round(vs_no_discont.total$f) - acc.round(discount_value_with_tax$f);

    vat_summary$ = acc.vatSummary(documentItems, discount_rate$f).toString();

}


void PMDocument::onChangePaymentTable() {

    double paid = 0;

    PModelPtr model = payment_table$;
    $model->forEach(PVariant payment) {
        paid += payment.amount$f;
    }

    paid$ = paid;
    to_pay$ = total$f - paid;

    to_pay_progress$ = to_pay_progress();
    paid_progress$ = paid_progress();

    if(to_pay$f == 0)
        state$ = "paid";

}




PVariant PMDocument::action(PVariant button) {
   
    PLog().debug() << "action ==>" << button.toString();
    
    if(button.toString() == "draft") {
        return true;
    }
    else if(button.toString() == "confirmed") {
        confirm(false);
        this->confirmed = true;
        return true;
    }
    else if(button.toString() == "paid") {
        mainWidget->setDisabled(true);
        return true;
    }
    else if(button.toString() == "cancelled") {
        return true;
    }
    else if(button.action$s == "print") {
        QString documentType = document_type_id$->name$s;
        documentType.replace(" ", "");
        POpenUrl::writeHtml($"pos/documents/${documentType}", this->serial$s, this->html());
        return true;
    }

    return nil;

}
    
void PMDocument::confirm(bool increment) {

    document_type_id$->sequence_id$->check(document_type_id$->id$s);
    serial$ = document_type_id$->sequence_id$->nextValue(increment);
    date$ = $PSql().current("date");

    PLog().error() << "=  =  =  =  =  =  =>" << increment << serial$s;

}

void PMDocument::newDocument(const QString& documentTypeName) {
        
    PModelPtr newRecord = this->dup();

    newRecord->document_type_id$ = newRecord->document_type_id$->$find(name: documentTypeName)->id$s;
    newRecord->document_id$ = id$s;
    newRecord->state$ = "draft";
    newRecord->serial$ = "";

    newRecord->writeAllRecords();

}


void PMDocument::onBeforeWidget() {
    
    this->confirmed = false;

}  

void PMDocument::onAfterWidget() {
    
    date$w->setDisabled(state$s != "draft");
    mainWidget = $<QWidget*>("mainWidget");
    mainWidget->setDisabled(state$s == "paid");

}


bool PMDocument::onOkDialog() {
    
    if(serial$ != nil and this->confirmed) 
        this->confirm();  

    return true;

}


