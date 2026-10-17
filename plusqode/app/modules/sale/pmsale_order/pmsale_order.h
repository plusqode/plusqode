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

#ifndef PMSALEORDER_H
#define PMSALEORDER_H

#include "app/modules/core/pmdocument/pmdocument.h"

class PMSaleOrder : public PMDocument {

    Q_OBJECT
    $P_PARENT_VIEW

public:
    PMSaleOrder(PVariant args);
    PMSaleOrder& init(PVariant);
    virtual void onAfterWidget();

public slots:
    virtual PVariant action(PVariant button);

public slots:
    
public:    

};

Q_DECLARE_METATYPE(PMSaleOrder*)

#endif // PMSALEORDER_H
