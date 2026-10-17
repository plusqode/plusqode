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

#ifndef PPROFILEMANAGER_H
#define PPROFILEMANAGER_H

   #include <QString>
   #include "variant/pvariant.h"
   #include "misc/pdir.h"

class PProFileManager
{
public:
    PProFileManager(const QString& varName);
    QString plusqodePath();
    bool add(const QString value);
    bool remove(const QString value);
    bool save();

    QString varName;
    PVariant values;

    QString plusqode_proContent;
    PString header;
    PString footer;

};

#endif 



