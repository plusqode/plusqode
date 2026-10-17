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

#ifndef PMPOSPRODUCT_H
#define PMPOSPRODUCT_H

#include "app/modules/core/pmproduct/pmproduct.h"

class PMPosProduct : public PMProduct {

    Q_OBJECT
    
    $P_PARENT_VIEW

public:
    PMPosProduct(PVariant args);
    PMPosProduct& init(PVariant);

public slots:

};

Q_DECLARE_METATYPE(PMPosProduct*)

#endif // PMPOSPRODUCT_H
