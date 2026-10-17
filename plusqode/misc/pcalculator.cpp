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




   #include "misc/pcalculator.h"


   

   

PCalculator::PCalculator()
{
}



QString PCalculator::randStr(int length) {

    PMath::initRandSequence();

    QString result;

    for(int i = 0; i < length; i++) {
        int randomValue = PMath::rand() % 36;
        result += QString("%1").arg(QVariant(randomValue).toInt() + 1, 0, 36 );
    }


    return result;

}




quint64 PCalculator::rand(quint64 min, quint64 max) {

    PMath::initRandSequence();

    quint64 num = PMath::rand() % (max - min);

    return num + min;

}

QList<quint64>  PCalculator::randList(quint64  min, quint64  max) {

    QList<quint64> list;
    for(quint64 i = min; i < max; i++)
        list << i;

    QList<quint64> result;
    while(list.count()) {
        quint64 i = PCalculator::rand(0, list.count());
        result << list.at(i);
        list.removeAt(i);
    }

    return result;

}

QString PCalculator::toBase(quint64 n, int base, int fieldWidth) {

    return QString("%1").arg(n, fieldWidth, base, QChar('0'));

}

QString PCalculator::toBase(QString n, int base, int fieldWidth) {

    return PCalculator::toBase(n.toLongLong(), base, fieldWidth);

}


QString PCalculator::toIPv(quint64 n, int version) {

    bool ok;

    QString hex = PCalculator::toBase(n, 16, version * 2);

    QStringList values;

    for(int i = 0; i < version; i++) {
        QString n;
        n += hex.mid(i * 2, 2);
        values << QString("%1").arg(n.toInt(&ok, 16), 3, 10, QChar('0'));
    }

    return values.join(".");

}


quint64 PCalculator::fromIPv(QString value) {

    QString result = "";

    QStringList values = value.split(".");
    for(int i = 0; i < values.count(); i++)
        result += PCalculator::toBase(values.at(i).toUInt(), 16, 2);

    bool ok;
    return result.toLongLong(&ok, 16);

}

QString PCalculator::macAddress() {

    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
        if(!(netInterface.flags() & QNetworkInterface::IsLoopBack))
            return netInterface.hardwareAddress();

    return QString();

}

void PCalculator::test() {

    for(int i = 0; i < 10; i++) {
        quint64 value = rand(0, 0xFFFFFFFF);
        qDebug() << PCalculator::toIPv(value);
    }


    qDebug() << PCalculator::toIPv(0xFF) << PCalculator::fromIPv("0.0.0.255");
    qDebug() << PCalculator::toIPv(0xFFFF) << PCalculator::fromIPv("0.0.255.255");
    qDebug() << PCalculator::toIPv(0xFFFFFF) << PCalculator::fromIPv("0.255.255.255");
    qDebug() << PCalculator::toIPv(0xFFFFFFFF) << PCalculator::fromIPv("255.255.255.255");

    QList<quint64> ids = randList(1025, 0xFFFF);
    qDebug() << ids;
    

}
