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

#ifndef PMDOCUMENTITEM_H
#define PMDOCUMENTITEM_H

#include "sql/pmodel.h"
#include "misc/pmath.h"
#include "misc/paccounting.h"

class PMDocumentItem : public PModel {

    Q_OBJECT

public:
    PMDocumentItem() {}
    PMDocumentItem(PVariant args);
    PMDocumentItem& init(PVariant);
    Q_INVOKABLE PVariant currency();

    void initAccounting();

    void resetValues();
    void checkValues();
    void updateAccounting();

public slots:
    void onChangeField(QString fieldName, PVariant data);
    bool onOkDialog();

    void onChangeProduct();
    void onChangePrice();
    void onChangePriceWithTax();

public:
    PAccounting acc;

};

Q_DECLARE_METATYPE(PMDocumentItem*)

#endif // PMDOCUMENTITEM_H
