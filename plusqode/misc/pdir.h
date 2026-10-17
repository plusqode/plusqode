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

#ifndef PDIR_H
#define PDIR_H

   #include <QtCore/QString>
   #include <QtCore/QStringList>
   #include <QtCore/QFileInfo>
   #include <QtCore/QDirIterator>
   #include <QtCore/QDate>
   #include <QtCore/QTime>

   #include "variant/pvariant.h"
   #include "misc/pdebug.h"

class PDir
{
public:
    PDir(QString pathName);

    static QStringList get(const QString& path, QDir::Filters filters = QDir::NoFilter);
    static QStringList get(const QString& path,
                           const QStringList& nameFilters,
                           QDir::Filters filters = QDir::NoFilter,
                           QDirIterator::IteratorFlags flags = QDirIterator::Subdirectories);
    QStringList onlyDirectories(bool recursive = true, bool onlyFileName = false);
    QStringList onlyDirectories(PVariant);
    QStringList onlyFullFiles(PVariant args);
    QStringList onlyFiles(QStringList nameFilters = QStringList());
    QStringList onlyFiles(PVariant filters);
    static QString fileNameFromFullFileName(QString fullFileName);
    static  QByteArray fileContent(const QString& fileName);
    static  PVariant fileLines(const QString& fileName);
    static bool filecmp(QString filename1, QString filename2);
    static bool fileWrite(const QString& fileName, QByteArray data, bool createPath = true);
    static QString currentDateTime();
    static bool remove(const QString& pathName);
    static bool _copy(QString src, QString dest);
    static bool copy(QString src, QString dest);

    QString pathName;

};

#endif 



