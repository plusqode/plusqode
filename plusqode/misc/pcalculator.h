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

#ifndef PCALCULATOR_H
#define PCALCULATOR_H

   #include "misc/pmath.h"

   #include <QObject>
   #include <QVariant>
   #include <QDateTime>
   #include <QStringList>
   #include <QList>
   #include <QNetworkInterface>
   #include <QDebug>

   #include <limits>

class PCalculator
{
public:
    PCalculator();
    static QString randStr(int length);
    static quint64 rand(quint64  min, quint64  max = std::numeric_limits<quint64>::max());
    static QList<quint64> randList(quint64  min, quint64  max = std::numeric_limits<quint64>::max());
    static QString toBase(quint64 n, int base, int fieldWidth = 0);
    static QString toBase(QString n, int base, int fieldWidth = 0);
    static QString toIPv(quint64 n, int version = 4);
    static quint64 fromIPv(QString value);
    static QString macAddress();
    static void test();

};

#endif 



