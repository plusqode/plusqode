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

#ifndef PSHAREDDATA_H
#define PSHAREDDATA_H

   #include "variant/pvariant.h"

class PSharedData {

public:
    PSharedData();

    void setValue(PVariant fieldValue, const QString& fieldName, const QString& sharedDataName = "plusqode");
    void set(PVariant fieldValue, const QString& fieldName, const QString& sharedDataName = "plusqode");
    PVariant value(const QString& fieldName, const QString& sharedDataName = "plusqode");

    PVariant sharedData;

};


class PSharedDataManager {

public:
    static PSharedData* instance() {
        static PSharedData instance;
        return &instance;
    }
};


#endif 



