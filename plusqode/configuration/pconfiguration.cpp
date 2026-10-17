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



   #include "configuration/pconfiguration.h"

   
   

PConfiguration::PConfiguration(const QString& fileName) :
    fileName(fileName) {

    qDebug() << " - PConfiguration ===>" << fileName;

    PConfigParser parser(fileName);
    ch = parser.startParsing();

    if(ch == nil) {
        qDebug() << "PConfiguration::PConfiguration() ... syntax error in the file " << fileName;
        exit(0);
    }

}


PConfiguration::PConfiguration(PVariant ch) {

    this->ch = ch;

}


PVariant PConfiguration::cfg() {

    return ch;

}


QString PConfiguration::toString() {

    return ch.toString(",\n");

}

void PConfiguration::save() {

    QFile file(fileName);
    if ( !file.open( QIODevice::WriteOnly ) )
        return;

    QTextStream stream( &file );

    stream << this->toString();

    file.close();


}


PVariant PConfiguration::value(const QString& varName) {

    PVariant tree = ch;
    QStringList vars = varName.split(".");

    for(int i = 0; i < vars.count() - 1; i++)
        tree = tree[vars[i]];

    return tree[vars.last()];

}

void PConfiguration::setValue(const QString& varName, const PVariant& value) {

    PVariant tree = ch;
    QStringList vars = varName.split(".");

    for(int i = 0; i < vars.count() - 1; i++)
        tree = tree[vars[i]];

    tree[vars.last()] = value;

}
