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



   #include "core/ptranslator.h"

   
   

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
       #include <QRegExpValidator>
#endif

PTranslator::PTranslator() {

    QString language = PSinglConfigurationManager::instance()->value("settings", "language").toString();

    if(language.isEmpty()) language = "en";

     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << PString(QString("Language:")) << language;

    PVariant files = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    QDirIterator dirIt(PGlobal::modulePath(), QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        QString dirPath = dirIt.next();
        QDir dir(dirPath);
        if (dir.dirName().compare("locales", Qt::CaseInsensitive) == 0) {
            QStringList ymlFiles = dir.entryList(QStringList() << PString(QString("%1.yml").arg(language)), QDir::Files);
            for (const QString& file : ymlFiles)
                files << dir.filePath(file);
        }
    }


    PVariant locales = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    PVariant toTranslate = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

     files.forEachQString([&] (QString filename) mutable {
        PLog().debug() << "Load locale file ..." << filename;
        PConfiguration config(filename);
        PVariant words = config.cfg();
        locales += words;
    });

    PSharedDataManager::instance()->setValue(locales, "locales");
    PSharedDataManager::instance()->setValue(toTranslate, "toTranslate");

     

}

PTranslator::~PTranslator() {

    generateTranslationFile();

}


QString PTranslator::tr(const QString& str) {

    PVariant locales = PSharedDataManager::instance()->value("locales");
    PVariant toTranslate = PSharedDataManager::instance()->value("toTranslate");

    if(locales == nil)
        return str;

    if(locales(str) == nil and str != "")
        if(PString(str).exactMatch("^[A-Za-z][A-Za-z0-9.\\- ]*$"))
            toTranslate[str] = nil;

    return locales(str) != nil ? locales[str].toString() : str;

}




void PTranslator::generateTranslationFile() {

    QString language = PSinglConfigurationManager::instance()->value("settings", "language").toString();

    QString filename = PString(QString("%1/locales/%2_empty.yml").arg(PGlobal::modulePath()).arg(language));

    if(!QDir().exists(filename))
        PDir::fileWrite(filename, "{}");

    PVariant toTranslate = PSharedDataManager::instance()->value("toTranslate");

    PConfigParser parser(filename);
    PVariant newWords = parser.startParsing();

    if(newWords == nil) {
        PLog().error() << "Configuration file error ... " << filename;
        return;
    }

     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("yellow")))))).debug() << "New words to translate ..." << toTranslate.toString();

    toTranslate += newWords;

    PDir::fileWrite(filename, toTranslate.toString().replace(": ,", ": ,\n").toUtf8());

    PLog().debug() << "Translation File on " << filename;

}
