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

#ifndef PMPAYMENTCOPY_H
#define PMPAYMENTCOPY_H

#include "app/modules/core/pmdocument/pmdocument.h"

class PMPaymentCopy : public PMPayment {

    Q_OBJECT
    $P_MODEL_COPY

public:
    PMPaymentCopy() {}
    PMPaymentCopy(PVariant args);
    PMPaymentCopy& init(PVariant);

public slots:
    
public:    

};

Q_DECLARE_METATYPE(PMPaymentCopy*)

#endif // PMPAYMENTCOPY_H
