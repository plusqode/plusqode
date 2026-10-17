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

#ifndef PJOBSCHEDULER_H
#define PJOBSCHEDULER_H

   #include <QObject>
   #include <QtCore/QTimer>
   #include <QtCore/QDateTime>
   #include <QtCore/QList>
   #include <QtCore/QDebug>

   #include "core/plogger.h"
   #include "variant/pvariant.h"

enum class PScheduleType {

    Once,
    EveryMinute,
    Daily,
    Weekly

};


class PJob : public QObject {

    Q_OBJECT

public:

signals:
    void timeout();

public:

    void emitTimeOut() {
        emit timeout();
    }

    QString name;

    PScheduleType type;

    QTime time;         
    int interval = 0;   

    Qt::DayOfWeek day = Qt::Monday; 

    PJob(QString name, PScheduleType type) {
        this->name = name;
        this->type = type;
    }

    ~PJob() {

        qDebug() << " ~ ~ ~ - >" << name;

    }

    QDateTime nextRun;

};
Q_DECLARE_METATYPE(PJob*)


class PJobScheduler : public QObject {

    Q_OBJECT
public:
    explicit PJobScheduler(QObject *parent = 0);
    ~PJobScheduler();

    void addJob(PJob* job);

private:
    QList<PJob*> jobList;
    PVariant jobs = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    QTimer timer;

    void sortJobs();
    QDateTime computeNext(PJob* job);

signals:

public slots:
    void processJobs();

};

class PSinglJobScheduler {

public:
    static PJobScheduler* instance() {
        static PJobScheduler instance;
        return &instance;
    }
};

#endif 



