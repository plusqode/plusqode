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

#ifndef PVIEWLOADER_H
#define PVIEWLOADER_H

   #include <QtCore/QObject>
   #include <QtXml/QDomElement>
   #include <QtCore/QFile>

   #include "core/pglobal.h"
   #include "core/plogger.h"
   #include "core/pview.h"
   #include "variant/pvariant.h"
   #include "misc/pdebug.h"
   #include "misc/pdir.h"


class PViewLoader : public QObject
{
    Q_OBJECT
public:

    explicit PViewLoader(QObject *parent = 0);

    ~PViewLoader();
    PView* view(const QString moduleName, const QString viewName);
    PView* view(const QString viewName);
    PView* viewByPath(QString path);

    QMap<QString, PView*> views;

signals:

public slots:

};

#endif 



