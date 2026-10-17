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



   #include "misc/pprofilemanager.h"

   
   

PProFileManager::PProFileManager(const QString& varName) {

    this->varName = varName;

    this->values = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    plusqode_proContent = QString::fromUtf8(PDir::fileContent(plusqodePath() + "/plusqode.pro"));

    this->header = plusqode_proContent.split(varName)[0];
    PString value = plusqode_proContent.split(varName)[1];

    value = value.split("+=")[1].toString();

    PVariant lines = value.split("\n");for(int _i_0_ = 0; _i_0_ < lines.count(); _i_0_++) {
QString line = lines.operator[](_i_0_).toString();
        QString fileName = line;
        this->values << fileName.remove("\\").simplified();
        if(line.indexOf("\\") == -1) {
            this->footer = this->plusqode_proContent.split(line)[1];
            break;
        }
    }


}


QString PProFileManager::plusqodePath() {

    return QDir::currentPath(); 

}


bool PProFileManager::add(const QString value) {

    this->values.appendIfNotExists(value);
    return true;

}

bool PProFileManager::remove(const QString value) {

    this->values.removeByValue(value);
    return true;

}

bool PProFileManager::save() {

    QString newValue = this->values.join("\\\n");

    this->plusqode_proContent = PString(QString("%1%2 += %3%4").arg(this->header).arg(this->varName).arg(newValue).arg(this->footer));

    PDir::fileWrite(plusqodePath() + "/plusqode.pro", this->plusqode_proContent.toUtf8());

    return true;

}
