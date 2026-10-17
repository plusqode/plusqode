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

#ifndef PSQLFIELD_H
#define PSQLFIELD_H

   #include "variant/pvariant.h"

class PSqlField : public PVariant
{
public:
    PSqlField();
    PVariant& operator=(QVariant var);
    static PVariant autoComplete(const QString& modelName, QString fieldName, PVariant args);
    static PVariant pAuto(PVariant args);
    static PVariant pa(PVariant args);
    static PVariant pText(PVariant args);
    static PVariant pt(PVariant args);
    static PVariant pInteger(PVariant args);
    static PVariant pi(PVariant args);
    static PVariant pFloat(PVariant args);
    static PVariant pf(PVariant args);
    static PVariant pDate(PVariant args);
    static PVariant pd(PVariant args);
    static PVariant pTime(PVariant args);
    static PVariant pDateTime(PVariant args);
    static PVariant pdt(PVariant args);
    static PVariant pBool(PVariant args);
    static PVariant pb(PVariant args);
    static PVariant pOneToOne(PVariant args);
    static PVariant pOneToMany(PVariant args);
    static PVariant pManyToOne(PVariant args);
    static PVariant pManyToMany(PVariant args);
    static PVariant pVirtual(PVariant args);
    static PVariant pv(PVariant args);
    static PVariant pWidget(PVariant args);
    static PVariant pw(PVariant args);
    static PVariant primaryKey(PVariant args);
    static PVariant serial(PVariant args, QString tableName);

};

#endif 



