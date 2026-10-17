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



   #include "misc/psystem.h"

   
   

PSystem::PSystem(QObject* parent) : QProcess (parent) {

}

PSystem::PSystem(QString command, QObject* parent) :
        QProcess (parent) {

    init(command);

}


PSystem::~PSystem() {

    
    

    
    qDebug() << "==========================================>" << "PSystem Destroy";

}

void PSystem::initByScriptCommand(QString scriptCommand) {

    this->scriptCommand = scriptCommand;

}

void PSystem::initBySqlCommand(QString sqlCommand) {

    this->sqlCommand = sqlCommand;

}


void PSystem::init(QString command) {

    
    QStringList commands = command.simplified().split(';');
    if(commands.count() > 1) {
        for(int i = 0; i < commands.count(); i++)
            PSystem(commands[i].toUtf8());
        return;
    }

    QStringList args = command.simplified().split(' ');

    QString cmd = args.takeFirst();

    connect( this, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()) );
    connect( this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFinished(int, QProcess::ExitStatus)) );

    qDebug() << cmd << args;

    this->start(cmd, args);
    if (!this->waitForStarted())
        return;

    if (!this->waitForFinished())
        return;

}


void PSystem::readStandardOutput() {

    
    qDebug() << this->readAllStandardOutput() << "\n";

}

void PSystem::onFinished(int exitCode, QProcess::ExitStatus exitStatus) {

    
    qDebug() <<  "Process Finished" << "\n";

}

void PSystem::runDetached(QString command) {

    
    QStringList commands = command.simplified().split(';');
    if(commands.count() > 1) {
        for(int i = 0; i < commands.count(); i++)
            PSystem(commands[i].toUtf8());
        return;
    }

    QStringList args = command.simplified().split(' ');

    QString cmd = args.takeFirst();

    connect( this, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()) );
    connect( this, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFinished(int, QProcess::ExitStatus)) );

    qDebug() << cmd << args;

    this->startDetached(cmd, args);

}

void PSystem::runDetached() {

    if(!this->scriptCommand.isEmpty())
        this->runDetached(this->scriptCommand);

    if(!this->sqlCommand.isEmpty())
        PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))))).execute(sqlCommand);

}
