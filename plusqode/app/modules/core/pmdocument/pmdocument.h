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

#ifndef PMDOCUMENT_H
#define PMDOCUMENT_H

#include "sql/pmodel.h"
#include "app/modules/core/pmdocument_type/pmdocument_type.h"
#include "app/modules/core/pmdocument_item/pmdocument_item.h"
#include "app/modules/core/pmpayment/pmpayment.h"
#include "app/modules/core/pmsequence/pmsequence.h"
#include "misc/popenurl.h"


class PMDocument : public PModel {

    Q_OBJECT

public:

#include "dom/phtml_header.h"

    PMDocument() {}
    PMDocument(PVariant args);
    PMDocument& init(PVariant);
    Q_INVOKABLE PVariant to_pay_progress();
    Q_INVOKABLE PVariant paid_progress();

    virtual bool onOkDialog();
    virtual void onBeforeWidget();
    virtual void onAfterWidget();
    virtual void confirm(bool increment = true);
    virtual void newDocument(const QString& documentTypeName);

public slots:
    virtual PVariant action(PVariant button);
    void onChangeField(QString fieldName, PVariant data);
    void onChangeDocumentItemTable();
    void onChangePaymentTable();
    void onChangeDiscountRate();
    void onChangeDiscountValue();
    void onChangeDiscountValueWithTax();
    void onChangeTaxable();
    void onChangeTotal();

public:
    PVariant states;
    QWidget* mainWidget;
    bool confirmed;

};

Q_DECLARE_METATYPE(PMDocument*)

#endif // PMDOCUMENT_H
