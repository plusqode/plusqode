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




   #include "misc/pdir.h"


   

   

PDir::PDir(QString pathName)
    : pathName(pathName) {

}

QStringList PDir::get(const QString& path, QDir::Filters filters) {

    QStringList result;
    QDirIterator it(path, filters);
    while (it.hasNext())
        result << it.next();

    return result;

}


QStringList PDir::get(const QString& path,
                       const QStringList& nameFilters,
                       QDir::Filters filters,
                       QDirIterator::IteratorFlags flags) {

    QStringList result;
    QDirIterator it(path, nameFilters, filters, flags);
    while (it.hasNext())
        result << it.next();

    return result;

}

QStringList PDir::onlyDirectories(bool recursive, bool onlyFileName) {

    QDirIterator::IteratorFlags flags = QDirIterator::Subdirectories;
    if(!recursive)
        flags = QDirIterator::NoIteratorFlags;

    QStringList result;
    QStringList fad = get(pathName, QStringList(), QDir::Dirs | QDir::NoDotAndDotDot, flags); 
    for(int i = 0; i < fad.count(); i++)
        if(onlyFileName)
            result << QFileInfo(fad[i]).fileName();
        else
            result << QFileInfo(fad[i]).filePath();

    return result;

}

QStringList PDir:: onlyDirectories(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "onlyDirectories:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
bool recursive = source_args.value<PVariantMapPtr>()->include("recursive") ? source_args.value<PVariantMapPtr>()->operator[]("recursive").toBool() : QVariant(true).toBool();args.removeByKey("recursive");
bool onlyFileName = source_args.value<PVariantMapPtr>()->include("onlyFileName") ? source_args.value<PVariantMapPtr>()->operator[]("onlyFileName").toBool() : QVariant(false).toBool();args.removeByKey("onlyFileName");


    return onlyDirectories(recursive, onlyFileName);

}



QStringList PDir::onlyFullFiles(PVariant args) {

    return get(pathName, args.toStringList(), QDir::Files);

}




QStringList PDir::onlyFiles(QStringList nameFilters) {

    QStringList result;
    QStringList fad = get(pathName, nameFilters, QDir::Files); 
    for(int i = 0; i < fad.count(); i++)
        result << QFileInfo(fad[i]).fileName();

    return result;

}



QStringList PDir::onlyFiles(PVariant args) {

    return onlyFiles(args.toStringList());

}


QString PDir::fileNameFromFullFileName(QString fullFileName) {

    return QFileInfo(fullFileName).fileName();

}


QByteArray PDir::fileContent(const QString& fileName) {

    QFile file(fileName);
    if ( !file.open(QIODevice::ReadOnly) ) {
        pDebug() << "PDir::fileContent: cannot open the file " << fileName;
        return "";
    }

    QByteArray result = file.readAll();

    file.close();

    return result;

}


PVariant PDir::fileLines(const QString& fileName) {

    PVariant lines = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    QFile file(fileName);
    if ( !file.open(QIODevice::ReadOnly) ) {
        pDebug() << "PDir::fileContent: cannot open the file " << fileName;
        return lines;
    }

    QByteArray line = file.readLine();
    for(; !line.isNull(); line = file.readLine())
        lines << line;

    file.close();

    return lines;

}


bool PDir::filecmp(QString filename1, QString  filename2) {

    QByteArray fileContent1 = fileContent(filename1);
    QByteArray fileContent2 = fileContent(filename2);

    return fileContent1 == fileContent2;

}


bool PDir::fileWrite(const QString& fileName, QByteArray data, bool createPath) {

    QFileInfo info(fileName);

    
    
    

    if(createPath and !QDir().exists(info.path()))
        QDir().mkpath(info.path());

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        pDebug() << "PDir::fileWrite: cannot open the file " << fileName;
        return false;
    }

    file.write(data);

    file.close();

    return true;

}


QString PDir::currentDateTime() {

    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("hh.mm.ss.zzz");

    return PString(QString("%1.%2").arg(date).arg(time));

}


bool PDir::remove(const QString& pathName) {

    bool result = true;
    QDir dir(pathName);

    if (dir.exists()) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir())
                result = PDir::remove(info.absoluteFilePath());
            else
                result = QFile::remove(info.absoluteFilePath());

            if (!result)
                return result;
        }
        result = QDir().rmdir(pathName);
    }
    return result;

}



bool PDir::_copy(QString src, QString dest) {

    QDir dir(src);
    if (!dir.exists()) return false;

    QDir().mkpath(dest);

    foreach(QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString destPath = dest + QDir::separator() + d;
        
        PDir::_copy(src + QDir::separator() + d, destPath);
    }

    foreach(QString f, dir.entryList(QDir::Files)) {
        
        QFile::copy(src + QDir::separator() + f, dest + QDir::separator() + f);
    }

    return true;

}


bool PDir::copy(QString src, QString dest) {

    qDebug() << "PDir::copy"  << src << dest << "\n";

    if(QFileInfo(src).isFile()) {
        QFile::copy(src, dest);
        return true;
    }

    QString dirName = QDir(src).dirName();

    return PDir::_copy(src, dest + QDir::separator() + dirName);

}
