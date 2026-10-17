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

#ifndef PCONFIGPARSER_H
#define PCONFIGPARSER_H

   #include <QObject>

   #include "configuration/pconfigurationheader.h"
   #include "configuration/pconfigurationscanner.h"
   #include "configuration/pconfigurationparser.h"

class PConfigParser : public QObject
{
    Q_OBJECT
public:
    explicit PConfigParser(const QString& filename, bool byFileName = true);

public:
    PVariant startParsing();

    QString _filename;
    bool _byFileName;

    PVariant result;

};

int parsing (PConfigParser*);

#endif 



