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

#ifndef PLOGGER_H
#define PLOGGER_H

   #include <QtCore/QFile>
   #include <QtCore/QDir>
   #include <QtCore/QTextStream>
   #include <QtCore/QDateTime>
   #include <QtCore/QMap>

   #include "configuration/pconfigurationmanager.h"
   #include "core/pglobal.h"

class PLogger {

public:

    enum Level {DEBUG, INFO, WARNING, SQL, ERROR, FATAL};

    PLogger(const QString& fileName, const QString& level = "error", const QString& type = "append");
    ~PLogger();
    void setLevel(const QString& levelStr);
    void setType(const QString& type);
    void write(Level level, const QVariant& msg,
               QString color = QString(), int bgc = -1, int fgc = -1,
               QString levelStr = QString());
    void debug(const QVariant& msg);
    void info(const QVariant& msg);
    void warning(const QVariant& msg);
    void sql(const QVariant& msg);
    void error(const QVariant& msg);
    void fatal(const QVariant& msg);



    QFile* file;
    QTextStream* outStreamFile;
    Level level;
    QString type;

};


class PLogManager {

    typedef QMap<QString, PLogger*> LogMap;

    LogMap logMap;

public:

    ~PLogManager();
    void init(const QString& logName, const QString& fileName, const QString& level = "error", const QString& type = "append");
    void initByConfigFileName(const QString& logName, const QString& configFileName);
    static void initByPlusQodeFile();
    PLogger* log(const QString& logName = "plusqode");
    void debug(const QString& logName, const QVariant& msg);
    void info(const QString& logName, const QVariant& msg);
    void warning(const QString& logName, const QVariant& msg);
    void sql(const QString& logName, const QVariant& msg);
    void error(const QString& logName, const QVariant& msg);
    void fatal(const QString& logName, const QVariant& msg);

    static void demo();
    static void demoByConfigFileName();

};

class PSinglLogManager {

public:
    static PLogManager* instance() {
        static PLogManager instance;
        return &instance;
    }
};


class PLog {

public:
    PLog(PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("logName", QString("plusqode"))))));
    PLog(const QString& logName, PLogger::Level level);
    ~PLog();
    PLog& debug(const QVariant& msg = "");
    PLog& info(const QVariant& msg = "");
    PLog& warning(const QVariant& msg = "");
    PLog& sql(const QVariant& msg = "");
    PLog& error(const QVariant& msg = "");
    PLog& fatal(const QVariant& msg = "");
    PLog& operator<<(const QVariant& str);
    PLog& setColor(PVariant);
    PLog& setLevelStr(QString);

    static void demo();

    QString logName;
    PLogger::Level level;
    QString buffer;
    QString color;
    int bgc, fgc;
    QString levelStr;

};


#endif 



