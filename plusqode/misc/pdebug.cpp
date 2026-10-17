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




   #include "misc/pdebug.h"


   

   

PVariant PDebug::p_stdout = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
bool PDebug::bufferize = false;

PDebug::PDebug() {

}

PDebug::PDebug(const char* format) : format(format) {

    _noEndl = false;
    _noSpace = false;

}

PDebug& PDebug::noEndl() {

    _noEndl = true;
    return *this;

}


PDebug& PDebug::noSpace() {

    _noSpace = true;
    return *this;

}


void PDebug::p_printf(const char* format, const char* str) {

    if(bufferize) {
        char dest[512];
        snprintf(dest, 512, format, str);
        p_stdout << QString(dest);
    }
    else
        printf(format, str);

}

void PDebug::p_printf(const char* str) {

    if(bufferize) {
        if(str[0] == '\n') {
            p_stdout << "\n";
            return;
        }
        char dest[512];
        snprintf(dest, 512, str);
        p_stdout << QString(dest);
    }
    else
        printf(str);

}

QString PDebug::setBufferize(bool bufferize) {

    PDebug::bufferize = bufferize;
    QString result = PDebug::p_stdout.join("");
    PDebug::p_stdout = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    return result;

}


PDebug& PDebug::operator<<(const char* msg) {

#if defined (NODEBUG)
    return *this;
#endif

    if(format)
        p_printf(format, msg);
    else if(_noSpace)
        p_printf(msg);
    else
        p_printf("%s ", msg);

    return *this;

}

PDebug::~PDebug() {

#if defined (NODEBUG)
    return;
#endif

    if(!_noEndl)
        p_printf("\n");

}

PDebug& PDebug::operator<<(const QString& str) {

#if defined (NODEBUG)
    return *this;
#endif


    *this << (const char*)str.toUtf8();
    return *this;

}

PDebug& PDebug::operator<<(const QByteArray& byteArray) {

#if defined (NODEBUG)
    return *this;
#endif

    p_printf(byteArray.data());
    return *this;

}

PDebug& PDebug::operator<<(int n) {

#if defined (NODEBUG)
    return *this;
#endif

    *this << QVariant(n).toString();
    return *this;

}

PDebug& PDebug::operator<<(QChar c) {

#if defined (NODEBUG)
    return *this;
#endif

    *this << QVariant(c).toString().toUtf8();
    return *this;

}


PDebug& PDebug::operator<<(const QDate& d) {

#if defined (NODEBUG)
    return *this;
#endif

    *this << QVariant(d).toDate().toString();
    return *this;

}

PDebug& PDebug::operator<<(const QTime& t) {

#if defined (NODEBUG)
    return *this;
#endif

    *this << QVariant(t).toTime().toString();
    return *this;

}

PDebug& PDebug::operator<<(const QDateTime& dt) {

#if defined (NODEBUG)
    return *this;
#endif

    *this << QVariant(dt).toDateTime().toString();
    return *this;

}


PDebug& PDebug::operator<<(const PVariant& var) {

#if defined (NODEBUG)
    return *this;
#endif

    *this << QVariant(var.QVariant::toString()).toString().toUtf8().constData(); 
    return *this;

}


PDebug pDebug(const char* format) {

    return PDebug(format);

}
