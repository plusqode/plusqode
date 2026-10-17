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

#ifndef PMPOSPRINTMANAGER_H
#define PMPOSPRINTMANAGER_H

#include "sql/pmodel.h"
#include "core/psleeper.h"
#include "pos/pepsontmt88lan.h"
#include "pos/pepsontmt88.h"
#include "pos/pxonxoff.h"

class PMPosPrintManager : public PModel {

    Q_OBJECT

public:
    PMPosPrintManager(PVariant args);
    PMPosPrintManager& init(PVariant);

public slots:
    QString prefiscalTemplate(PVariant rec);
    void print();
    void check();

};

Q_DECLARE_METATYPE(PMPosPrintManager*)

#endif // PMPOSPRINTMANAGER_H
