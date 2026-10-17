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

#ifndef PMPOSPRINTER_H
#define PMPOSPRINTER_H

#include "sql/pmodel.h"
#include "widgets/widgetedit/plineedit.h"

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    #include <QtCore/QRegExp>
    #include <QRegExpValidator>
#else
    #include <QtCore/QRegularExpression>
    #include <QRegularExpressionValidator>
#endif

class PMPosPrinter : public PModel {

    Q_OBJECT

public:
    PMPosPrinter(PVariant args);
    PMPosPrinter& init(PVariant);

public slots:
    void onAfterWidget();

};

Q_DECLARE_METATYPE(PMPosPrinter*)

#endif // PMPOSPRINTER_H
