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



   #include "core/pglobal.h"

   
   
   #include "configuration/pconfigurationmanager.h"

   
   
   
   
   
 

PGlobal::PGlobal()
{
}


int PGlobal::decimalPrecision() {

    PVariant value = PSinglConfigurationManager::instance()->value("settings", "decimal_precision");

    return (value == nil) ? 2 : value.toInt();

}


QString PGlobal::basePath() {

    return QApplication::applicationDirPath();

}

   #include "core/pshareddata.h"

QString PGlobal::jsonDbPath() {

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    QString path = PString(QString("%1/.db/%2").arg(PGlobal::basePath()).arg(connectionName));

    if(!QDir().exists(path))
        QDir().mkdir(path);

    return path;

}


QString PGlobal::modulePath() {

    return PString(QString("%1/app/modules").arg(PGlobal::basePath()));

}

QString PGlobal::confFilePath() {

    return PGlobal::basePath();

}


QString PGlobal::dataPath() {

    return PString(QString("%1/app/data").arg(PGlobal::basePath()));

}


QString PGlobal::asteriskPath() {

    return "/etc/asterisk";

}


QString PGlobal::plus4CallPort() {

    return "9090";

}


QString PGlobal::windowColor() {

    return "white";

}


QString PGlobal::mandatoryFieldColor() {

    PVariant value = PSinglConfigurationManager::instance()->value("settings", "mandatory_field_color");

    return value.toString().isEmpty() ? "yellow" : value.toString();

}

QString PGlobal::readOnlyFieldColor() {

    PVariant value = PSinglConfigurationManager::instance()->value("settings", "read_only_field_color");

    return value.toString().isEmpty() ? "#EEEEEE" : value.toString();

}

QString PGlobal::url() {

    return "https://www.plusqode.com";

}


QFont PGlobal::widgetFont() {

    PVariant fontSize = PSinglConfigurationManager::instance()->value("settings", "form_font_size");

    int size = 10;
    QString font = "arial";

    if(!fontSize.toString().isEmpty())
        size = fontSize.toInt();

    if(QCryptographicHash::hash(PGlobal::url().toUtf8(), QCryptographicHash::Md5).toHex()                                                                               != "1345fb75aada50bd607ec6bb3ca5d122") exit(0);
        PVariant fontName = PSinglConfigurationManager::instance()->value("settings", "form_font");

    if(!fontName.toString().isEmpty())
        font = fontName.toString();

    return QFont(font, size, QFont::Normal);

}

QFont PGlobal::mainFieldFont() {

    PVariant fontSize = PSinglConfigurationManager::instance()->value("settings", "form_main_font_size");

    int size = 12;
    QString font = "arial";

    if(!fontSize.toString().isEmpty())
        size = fontSize.toInt();

    PVariant fontName = PSinglConfigurationManager::instance()->value("settings", "form_main_font");

    if(!fontName.toString().isEmpty())
        font = fontName.toString();

    return QFont(font, size, QFont::Bold);

}


int PGlobal::fieldMinimumHeight() {

    PVariant size = PSinglConfigurationManager::instance()->value("settings", "form_field_minimum_height");

    return (size.toString().isEmpty()) ? 25 : size.toInt();

}


PVariant PGlobal::menus() {

    PVariant names = PVariant::fromQStringList(PDir(PString(QString("%1").arg(PGlobal::modulePath()))).   onlyDirectories(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("recursive", false)->append("onlyFileName", true))))));

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));for(int pos = 0; pos < names.count(); pos++) {
QString moduleName = names.operator[](pos).toString();

        QString viewFileName = PString(QString("%1/%2/menu_view.xml").arg(PGlobal::modulePath()).arg(moduleName));
        if(QDir().exists(viewFileName))
            result << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("moduleName", moduleName)->append("viewFileName", viewFileName))));

    }

    return    result.sortPVariant_PVariant([&] (PVariant a,PVariant b) mutable { return a.undefined("moduleName", nil).toString() < b.undefined("moduleName", nil).toString(); });

}
