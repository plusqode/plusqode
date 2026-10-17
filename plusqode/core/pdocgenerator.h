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

#ifndef PDOCGENERATOR_H
#define PDOCGENERATOR_H

   #include <QtCore/QtGlobal>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
   #include <QRegularExpression>
#endif

   #include "core/pglobal.h"
   #include "variant/pvariant.h"
   #include "misc/pdir.h"

   #include "core/pdemo.h"
   #include "misc/pwindow.h"


class PDocGenerator
{
public:
    PDocGenerator(PVariant);
    ~PDocGenerator();
    PVariant sourceCode(PVariant);
    PVariant info();
    PVariant valueOf(QString variable);
    void writeOnHtmlFile(PVariant);
    void run(PDemo& demos);

    QString fileName;
    QString style;
    QString category;

    QString baseFileName;
    QString qtPlusPath;
    QString htmlFileName;
    QFile* htmlFile;
    QTextStream* htmlStream;

    QByteArray fileContent;

    PVariant lines;
    PVariant source_location;

    int fromLine;

};



#endif 



