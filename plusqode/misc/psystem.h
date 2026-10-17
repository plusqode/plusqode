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

#ifndef PSYSTEM_H
#define PSYSTEM_H

   #include <QtCore/QProcess>

   #include "core/plogger.h"
   #include "sql/psql.h"

class PSystem : public QProcess {

    Q_OBJECT

public:
    PSystem(QObject* parent = 0);
    PSystem(QString command, QObject* parent = 0);
    ~PSystem();
    void init(QString command);
    void initByScriptCommand(QString command);
    void initBySqlCommand(QString command);

public slots:
    void readStandardOutput();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void runDetached();
    void runDetached(QString command);

private:
    QString scriptCommand;
    QString sqlCommand;

};

#endif 



