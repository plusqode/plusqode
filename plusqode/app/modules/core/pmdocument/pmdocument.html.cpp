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
#include "app/modules/pmodules.h"
#include "dom/pdomtable.h"


QString PMDocument::$style(QString color: "gray") {

§

<style>

    .plus {

        left: 50%;
        top: 35%;
        transform: translate(-50%, -50%) rotate(-45deg);
        position: fixed;
        font-size: 110px;
        font-weight: bold;
        color: rgba(0, 0, 0, 0.08);
        z-index: 1;

    }

    body {
        font-family: 'Helvetica Neue', Helvetica, Arial, sans-serif;
        background-color: #f4f6f8;
        color: #333;
        margin: 0;
        padding: 0;
    }

    .invoice {
        width: 210mm;
        heigth: 297mm;
        margin: auto;
        background: white;
        padding 20mm;
        box-sizing: border-box;
        border: 1px solid #ccc;
    }

    .invoice-layout {
        text-align: justify;
        font-size: 14px;
        border-bottom: 3px solid #e0e0e0;
        padding: 10px 0px;
    }

    .invoice-layout .logo {
        float: right;
        background-image: url('../../../../../picons/plusqode/plusqode-logo.png');
        background-size: contain;
        background-repeat: no-repeat;
        width: 200px;
        height: 100px;
        background-color: hsl(<$=color$>, 100%, 40%);
    }

    .invoice-layout .block {
        text-align: center;
        vertical-align: top;
        display: inline-block;
        padding-left: 30px;
        color: #555;
    }

    .invoice-layout .dx {
        float: right;
        padding-left: 30px;
        color: #555;
    }



    .invoice-table {
        width: 90%;
        border-collapse: collapse;
        margin-bottom: 30px;
        font-size: 14px;
    }

    .invoice-table th, .invoice-table td {
        padding: 12px 15px;
        text-align: left;
    }

    .invoice-table th {
        background-color: #f1f5f9;
        color: #555;
        text-transform: uppercase;
    }

    .invoice-table tbody tr:nth-child(even) {
        background-color: #f9fafb;
    }


</style>
</head>

§

}

QString PMDocument::$head(QString title: 'Document') {

§

<head>
  <title><$= title $></title>
  <$= PDom::$inlinetag(tag: 'link', rel: 'stylesheet', media: , 'data-turbolinks-track': true) $>

  <meta charset='UTF-8'>
  <meta name='viewport' content='width=device-width, initial-scale=1'>

§

}


QString PMDocument::html() {

§

<$ QString color = QString("%1").arg(PMath::rand() % 345); $>

<!DOCTYPE html>
<html>

<$= PMDocument::$head() $>
<$= PMDocument::$style(color: color) $>

<body>

<$  
    PMContact $cc(); // company contact
    cc.$find(contact_type: 'company');

    PModelPtr ba = cc.undefined("billing_address_id", nil).value<PModelPtr>();
    PModelPtr da = cc.undefined("delivery_address_id", nil).value<PModelPtr>();

    if(ba == nil or da == nil) {
        PMMessageBox::$messageBox(text: "Company without addresses !!!", icon: "picons/core/actions-128/ko.png");
        return "";
    }

    PModelPtr cba = contact_id$->undefined("billing_address_id", nil).value<PModelPtr>();
    PModelPtr cda = contact_id$->undefined("delivery_address_id", nil).value<PModelPtr>();
    
    if(cba == nil or cda == nil) {
        PMMessageBox::$messageBox(text: "Customer without addresses !!!", icon: "picons/core/actions-128/ko.png");
        return "";
    }

    //PModelPtr cba = ba;
    //PModelPtr cda = da;

    
$>    

<div class='plus'>P L U S</div>
<div class='invoice'>
    <div class='invoice-layout'>
        <div class='block'>
            <h1 style='font-size: 32px; color: hsl(<$=color$>, 100%, 40%)'><$= cc.name$s $></h1>
        </div>

        <div class='block' style='font-size: 10px; color: #999'>
            <p>
            <strong><$=PTranslator::tr("BILLING ADDRESS")$></strong>
            <br><$=ba->street_name$s$> <$=ba->street_number$s$>
            <br><$=ba->postal_code$s$> <$=ba->city$s$> (<$=ba->state_province$s$>)
            <br><$=ba->phone$s$>
            <br><$=ba->mobile$s$>
            <br><$=ba->email$s$>
            </p>
        </div>
        <div class='block' style='font-size: 10px; color: #999'>
            <p>
            <strong><$=PTranslator::tr("DELIVERY ADDRESS")$></strong>
            <br><$=da->street_name$s$> <$=da->street_number$s$>
            <br><$=da->postal_code$s$> <$=da->city$s$> (<$=da->state_province$s$>)
            <br><$=da->phone$s$>
            <br><$=da->mobile$s$>
            <br><$=da->email$s$>
            </p>
        </div>
        <div class='logo'>
        </div>
    </div>

    <div class='invoice-layout'>
        <div class='block' style='font-size: 18px;'>
            <p>
            <h3 style='line-height: 0'>Invoice</h3>
            <$=PTranslator::tr("Number: ") + serial$s $> 
            <br><$=PTranslator::tr("Date: ") + date$s $>
            </p>
        </div>
        <div class='block' style='font-size: 12px'>
            <div class='invoice-layout' style='text-align: center; border-bottom: none'>
            <h3 style='line-height: 0'>Customer</h3>
            <div class='block' style='font-size: 12px'>
                <p>
                <strong><$=PTranslator::tr("BILLING ADDRESS")$></strong>
                <br><$=ba->street_name$s$> <$=ba->street_number$s$>
                <br><$=cba->postal_code$s$> <$=ba->city$s$> (<$=ba->state_province$s$>)
                <br><$=cba->phone$s$>
                <br><$=cba->mobile$s$>
                <br><$=cba->email$s$>
                </p>    
            </div>
            <div class='block' style='font-size: 12px'>
                <p>
                <strong><$=PTranslator::tr("DELIVERY ADDRESS")$></strong>
                <br><$=da->street_name$s$> <$=da->street_number$s$>
                <br><$=cda->postal_code$s$> <$=da->city$s$> (<$=da->state_province$s$>)
                <br><$=cda->phone$s$>
                <br><$=cda->mobile$s$>
                <br><$=cda->email$s$>
                </p>
            </div>
        </div>
    </div>


<$
    PDomTable table(document_item_table$->get_psql()->table,
                    $['quantity',
                      'name',
                      'price',
                      'discount_rate',
                      ${fieldName: 'price_with_discount', fieldLabel: 'price%'},
                      ${fieldName: 'amount_with_discount', fieldLabel: 'amount%'}]);
    table.$set(class: 'invoice-table');
$>

<$= table.toHtml() $>

<$
    PDomTable vsTable(PVariant::fromString(vat_summary$s).values());
    vsTable.$set(class: 'invoice-table')->$setStyle("font-size": "12px", width: "50%");
$>

<div class='block'>
    <$= vsTable.toHtml() $>
</div>

    <div class='dx'>
        <p><$=PTranslator::tr("Discount Rate: ") + discount_rate$s $></p>
        <p><$=PTranslator::tr("Discount Value: ") + discount_value$s $></p>
        <h3><$=PTranslator::tr("INVOICE TOTALS")$></h3>
        <p><$=PTranslator::tr("Taxable: ") + taxable$s $></p>
        <p><$=PTranslator::tr("Tax: ") + tax$s $></p>
        <p><strong><$=PTranslator::tr("TOTAL: ") + total$s $> </strong></p>
    </div>

</div>
    
<div class='invoice-layout'>
    <div class='block' style='font-size: 10px; text-align: left'>
        <p>
        <strong><$=PTranslator::tr("PAYMENT MODE")$></strong>
        <br><$=PTranslator::tr("Account Holder: ") + ba->account_holder$s$>
        <br>IBAN: <$=ba->iban$s$>
        <br>BIC/SWIFT: <$=ba->bic_swift$s$>
        </p>
    </div>
    <div class='block' style='font-size: 10px; text-align: left'>
        <p>
        <strong><$=PTranslator::tr("NOTES")$></strong>
        <$
            PVariant items = this->notes$.split(",");
            $items.forEach(QString item) {
        $>
            <br><$=item$> 
        <$}$>
        </p>
    </div>
    <div class='block' style='font-size: 10px; text-align: left'>
        <p><strong><$=PTranslator::tr("TO PAY:") + this->to_pay$s $></strong></p>
        <p>
        <strong><$=PTranslator::tr("PAID")$></strong>
        <$ 
           $this->payment_table$->forEach(PVariant p) { 
           QString name = this->payment_table$->payment_mode_id$->name$s; 
           QString amount = PVariant(p.amount$f).toString(); 
        $> 
        <br><$= $"${PString(PTranslator::tr(name)).capitalize(` `)}: ${amount}" $>
        <$ } $>
        </p>
    </div>
</div>

</body>
</html>


§


}
