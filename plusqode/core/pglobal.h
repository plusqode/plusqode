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

#ifndef PGLOBAL_H
#define PGLOBAL_H

   #include <QtWidgets/QApplication>
   #include <QtCore/QCryptographicHash>
   #include <QtCore/QDir>
   #include <QFont>

   #include "misc/pdir.h"
   #include "variant/pvariant.h"

class PGlobal {

public:
    PGlobal();

    static int decimalPrecision();

    static QString confFilePath();
    static QString basePath();
    static QString jsonDbPath();
    static QString modulePath();
    static QString dataPath();
    static QString asteriskPath();
    static QString plus4CallPort();

    static QString windowColor();
    static QString mandatoryFieldColor();
    static QString readOnlyFieldColor();
    static QString url();

    static QFont widgetFont();
    static QFont mainFieldFont();
    static int fieldMinimumHeight();
    static PVariant menus();

};

#endif 



