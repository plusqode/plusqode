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

#ifndef HDEBUG_H
#define HDEBUG_H

   #include <QtCore/QDebug>
   #include <QtCore/QString>

   #include "variant/pvariant.h"

   #include <iostream>

class PDebug
{
public:
    PDebug();
    PDebug(const char* format);
    ~PDebug();
    void p_printf(const char* format, const char* str);
    void p_printf(const char* str);
    PDebug& operator<<(const char* msg);
    PDebug& operator<<(const QString& str);
    PDebug& operator<<(const QByteArray& byteArray);
    PDebug& operator<<(int n);
    PDebug& operator<<(QChar c);
    PDebug& operator<<(const QDate& d);
    PDebug& operator<<(const QTime& t);
    PDebug& operator<<(const QDateTime& dt);
    PDebug& operator<<(const PVariant& var);

    PDebug& noEndl();
    PDebug& noSpace();

    static QString setBufferize(bool bufferize = true);

    bool _noEndl;
    bool _noSpace;

    const char* format;

    static PVariant p_stdout;
    static bool bufferize;

};

PDebug pDebug(const char* format = 0);

#endif 



