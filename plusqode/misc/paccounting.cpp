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




   #include "misc/paccounting.h"


   

   

PAccounting::PAccounting() {

    this->price = 0;
    this->discount_rate = 0;
    this->tax_rate = 0;
    this->quantity = 1;

}

double PAccounting::round(double value) {

    

    value = std::round(value * 100.0) / 100.0;

    return QString::number(value, 'f', PGlobal::decimalPrecision()).toDouble();

}

double PAccounting::taxFromTaxable(double taxable, double tax_rate) {

    return taxable * tax_rate / 100;

}

double PAccounting::totalFromTaxable(double taxable, double tax_rate) {

    return taxable + this->taxFromTaxable(taxable, tax_rate);

}

double PAccounting::discountRate(PVariant discountRateList) {

    double dr = 1;

     discountRateList.forEachdouble([&] (double discount) mutable {
        dr *= 1 - (discount / 100);
    });

    return (1 - dr) * 100;

}




PVariant PAccounting::vatSummary(PVariant documentItems, double discount_rate) {

    QMap<QString, double> groupByVAT;

     documentItems.forEachPVariant([&] (PVariant documentItem) mutable {
        groupByVAT[documentItem.undefined("tax_rate", nil).toString()] = 0;
    });

     documentItems.forEachPVariant([&] (PVariant documentItem) mutable {
        groupByVAT[documentItem.undefined("tax_rate", nil).toString()] += documentItem.undefined("qt_price_with_discount", nil).toDouble();
    });

    PVariant vats = PVariant::fromQStringList(groupByVAT.keys());

    PVariant vatSummary = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

     vats.forEachQString([&] (QString vat) mutable {

        double total = groupByVAT[vat];
        double taxable = this->taxableFromTotal(total, vat.toDouble());

        if(discount_rate) {
            taxable = this->totalFromTaxable(taxable, -discount_rate);
            total = this->totalFromTaxable(total, -discount_rate);
        }

        double tax = total - taxable;

        double rounded_tax = this->round(total) - this->round(taxable);

        vatSummary[vat] = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tax_rate",   vat.toDouble())->append("taxable", taxable)->append("tax", tax)->append("total", total)->append("rounded_tax", rounded_tax))));

    });


    return vatSummary;

}

PVariant PAccounting::vatSummaryTotals(PVariant documentItems, double discount_rate) {

    double taxable = 0;
    double tax = 0;
    double total = 0;

    PVariant vs = this->vatSummary(documentItems, discount_rate);

     vs.forEachPVariant([&] (PVariant vat) mutable {
        taxable += vat.undefined("taxable", nil).toDouble();
        total += vat.undefined("total", nil).toDouble();
    });

    tax = total - taxable;

    double rounded_tax = this->round(total) - this->round(taxable);

    return PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("taxable", taxable)->append("tax", tax)->append("total", total)->append("rounded_tax", rounded_tax))));

}


double PAccounting::taxableFromTotal(double total, double tax_rate) {

    return total * (100 / (tax_rate + 100));

}

void PAccounting::init(double t_price, double discount_rate, double tax_rate, double quantity) {

    price = taxableFromTotal(t_price, tax_rate);
    this->       initByPrice(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("price", price)->append("discount_rate", discount_rate)->append("tax_rate", tax_rate)->append("quantity", quantity)))));

}


void PAccounting:: initByPrice(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "initByPrice:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
double price = source_args.value<PVariantMapPtr>()->include("price") ? source_args.value<PVariantMapPtr>()->operator[]("price").toDouble() : QVariant(this->price).toDouble();args.removeByKey("price");
double discount_rate = source_args.value<PVariantMapPtr>()->include("discount_rate") ? source_args.value<PVariantMapPtr>()->operator[]("discount_rate").toDouble() : QVariant(this->discount_rate).toDouble();args.removeByKey("discount_rate");
double tax_rate = source_args.value<PVariantMapPtr>()->include("tax_rate") ? source_args.value<PVariantMapPtr>()->operator[]("tax_rate").toDouble() : QVariant(this->tax_rate).toDouble();args.removeByKey("tax_rate");
double quantity = source_args.value<PVariantMapPtr>()->include("quantity") ? source_args.value<PVariantMapPtr>()->operator[]("quantity").toDouble() : QVariant(this->quantity).toDouble();args.removeByKey("quantity");


    this->price = price;
    this->discount_rate = discount_rate;
    this->tax_rate = tax_rate;
    this->quantity = quantity;

    this->discount_value = this->taxFromTaxable(this->price, this->discount_rate);
    this->price_with_discount = this->price - this->discount_value;

    this->q_price = this->quantity * this->price;
    this->q_discount_value = this->quantity * this->discount_value;
    this->q_price_with_discount = this->quantity * this->price_with_discount;

    this->tax_value = this->taxFromTaxable(this->price_with_discount, this->tax_rate);

    this->t_price = this->price + this->taxFromTaxable(this->price, this->tax_rate);
    this->t_discount_value = this->taxFromTaxable(this->t_price, this->discount_rate);
    this->t_price_with_discount = this->price_with_discount + this->tax_value;

    this->qt_price = this->quantity * this->t_price;
    this->qt_discount_value = this->quantity * this->t_discount_value;
    this->qt_price_with_discount = this->quantity * this->t_price_with_discount;

    this->q_tax_value = this->quantity * this->tax_value;

    this->rounded_tax_value = this->round(t_price) - this->round(price);
    this->rounded_q_tax_value = this->round(qt_price) - this->round(q_price);

    this->rounded_t_discount_value = this->round(t_price) - this->round(t_price_with_discount);
    this->rounded_qt_discount_value = this->round(qt_price) - this->round(qt_price_with_discount);

}


void PAccounting::onChange_q_price(double q_price) {

   this->discount_rate = 0;
   this->q_price = q_price;
   this->price = this->q_price / this->quantity;
   this->initByPrice(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

}

void PAccounting::onChange_t_price(double t_price) {

    this->discount_rate = 0;
    this->t_price = t_price;
    this->price = this->taxableFromTotal(this->t_price, this->tax_rate);
    this->initByPrice(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));


}

void PAccounting::onChange_t_price_with_discount(double t_price_with_discount) {

    this->t_price_with_discount = t_price_with_discount;
    this->discount_rate = (1 - this->t_price_with_discount / this->t_price) * 100;
    this->initByPrice(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));


}


void PAccounting::onChange_q_price_with_discount(double q_price_with_discount) {

    this->q_price_with_discount = q_price_with_discount;
    this->price_with_discount = this->q_price_with_discount / this->quantity;
    onChange_price_with_discount(this->price_with_discount);

}


void PAccounting::onChange_qt_price_with_discount(double qt_price_with_discount) {

    this->qt_price_with_discount = qt_price_with_discount;
    this->t_price_with_discount = this->qt_price_with_discount / this->quantity;
    onChange_t_price_with_discount(this->t_price_with_discount);

}


void PAccounting::onChange_qt_price(double qt_price) {

    this->discount_rate = 0;
    this->qt_price = qt_price;
    this->price = this->taxableFromTotal(this->qt_price, this->tax_rate) / this->quantity;
    this->initByPrice(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

}


void PAccounting::onChange_discount_rate(double discount_rate) {

    this->discount_rate = discount_rate;
    this->initByPrice(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

}


void PAccounting::onChange_discount_value(double discount_value) {

    this->discount_value = discount_value;
    this->discount_rate = this->discount_value * 100 / this->price;
    this->initByPrice(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

}

void PAccounting::onChange_tax_rate(double tax_rate) {

    this->tax_rate = tax_rate;
    this->initByPrice(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

}

void PAccounting::onChange_price_with_discount(double price_with_discount) {

    this->price_with_discount = price_with_discount;
    this->discount_value = this->price - this->price_with_discount;
    this->onChange_discount_value(discount_value);

}


void PAccounting::show() {

   qDebug()

   << "quantity:" << quantity << "\n"

   << "price:" << price << "\n"
   << "discount_rate:" << discount_rate << "\n"
   << "discount_value:" << discount_value << "\n"
   << "price_with_discount:" << price_with_discount << "\n"

   << "q_price:" << q_price << "\n"
   << "q_discount_value:" << q_discount_value << "\n"
   << "q_price_with_discount:" << q_price_with_discount << "\n"

   << "tax_rate:" << tax_rate << "\n"
   << "tax_value:" << tax_value << "\n"

   << "t_price:" << t_price << "\n"
   << "t_discount_value:" << t_discount_value << "\n"
   << "t_price_with_discount:" << t_price_with_discount << "\n"

   << "qt_price:" << qt_price << "\n"
   << "qt_discount_value:" << qt_discount_value << "\n"
   << "qt_price_with_discount:" << qt_price_with_discount << "\n"

   << "q_tax_value:" << q_tax_value << "\n"

   << "rounded_t_discount_value:" << rounded_t_discount_value << "\n"
   << "rounded_qt_discount_value:" << rounded_qt_discount_value << "\n";


}

QString PAccounting::toString(PVariant map) {

    QStringList result;

       map.forEachQString_double([&] (QString key,double value) mutable {
        result << QString("%1: %2").arg(key).arg(value);
    });

    return result.join(", ");
}


void PAccounting::test() {

    PAccounting acc;

    acc.init(110, 10, 10, 2);
    acc.show();

    PVariant discounts = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(50)->append(10))));

    qDebug() << "Discout Rate Sum:" << acc.discountRate(discounts) << "\n";

    PVariant items     = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tax_rate", 10)->append("qt_price_with_discount", 110)))))->append(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tax_rate", 20)->append("qt_price_with_discount", 120)))))->append(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tax_rate", 10)->append("qt_price_with_discount", 220)))))->append(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tax_rate", 20)->append("qt_price_with_discount", 240))))))));

    qDebug() << "VAT summary: " << acc.vatSummary(items).toString() << "\n";

    qDebug() << "VAT summary with discount: " << acc.vatSummary(items, 10).toString() << "\n";

    qDebug() << "VAT Summary Totals " << acc.vatSummaryTotals(items).toString() << "\n";

    qDebug() << "VAT Summary Totals with Discount" << acc.vatSummaryTotals(items, 10).toString() << "\n";

}
