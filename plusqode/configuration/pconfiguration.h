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

#ifndef PCONFIGURATION_H
#define PCONFIGURATION_H

   #include <QObject>
   #include <QFile>
   #include <QDir>

   #include "misc/pdebug.h"
   #include "configuration/pconfigparser.h"

class PConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit PConfiguration(const QString& fileName);
    PConfiguration(PVariant ch);
    PVariant cfg();
    void save();
    PVariant value(const QString& varName);
    void setValue(const QString& varName, const PVariant& value);
    QString toString();

public:

    QString fileName;

    PVariant ch; 

};

#endif 



