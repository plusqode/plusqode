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

#ifndef PVIEW_H
#define PVIEW_H

   #include <QtXml/QDomElement>
   #include <QtCore/QFile>
   #include <QtCore/QMap>

   #include "core/plogger.h"
   #include "misc/pdebug.h"
   #include "misc/pdir.h"
   #include "variant/pvariant.h"
   #include "misc/pstring.h"

class PView
{

public:
    PView();
    ~PView();
    QString variantToString(PVariant var, int indent = 0);
    void initByFileName(QString fileName);
    void initByViewStr(QString viewStr);
    void initByViewVariant(PVariant viewVariant);
    PVariant toVariant();
    PString toString();
    PVariant findBy(PVariant);
    PView* partialByType(QString type);
    PView* partialByName(QString name);

private:
    PVariant toVariant(const QString& view);
    PVariant toVariant(QDomElement* root);


public:
    QString fileName;
    QString viewStr;
    PVariant viewVariant;

    QMap<QString, PView*> views;

};

#endif 



