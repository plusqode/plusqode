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



   #include "core/pjobscheduler.h"

   
   

PJobScheduler::PJobScheduler(QObject *parent) : QObject(parent) {

    connect(&timer, SIGNAL(timeout()), this, SLOT(processJobs()));

}


PJobScheduler::~PJobScheduler() {

    timer.stop();
    timer.disconnect();

    foreach(PJob* job, this->jobList)
        delete job;

}


void PJobScheduler::addJob(PJob* job) {

    this->jobList << job;
    this->jobs << PVariant::fromValue(job);
    this->sortJobs();

}


void PJobScheduler::sortJobs() {

    this->jobs =    jobs.sortPVariant_PVariant([&] (PVariant j1,PVariant j2) mutable {

        return j1.value<PJob*>()->nextRun < j2.value<PJob*>()->nextRun;

    });

}

QDateTime PJobScheduler::computeNext(PJob* job) {

    QDateTime now = QDateTime::currentDateTime();

    if(job->type == PScheduleType::Once)
        return now.addSecs(job->interval);
    if(job->type == PScheduleType::EveryMinute) {
        return now.addSecs(job->interval);
    }
    if(job->type == PScheduleType::Daily) {
        QDateTime next(now.date(), job->time);
        if(next <= now)
            next = next.addDays(1);
        return next;
    }

    if(job->type == PScheduleType::Weekly) {
        QDateTime next(now.date(), job->time);
        int diff = job->day - next.date().dayOfWeek();
        if(diff < 0 or (diff == 0 and next <= now))
            diff += 7;

        return next.addDays(diff);
    }

    return now;

}

void PJobScheduler::processJobs() {

    QDateTime now = QDateTime::currentDateTime();

     jobs.forEachPVariant([&] (PVariant variantJob) mutable {
        PJob* job = variantJob.value<PJob*>();
        if(!job->nextRun.isValid())
            job->nextRun = computeNext(job);
        else if(job->type == PScheduleType::Once) {
            job->emitTimeOut();
            jobs.removeByValue(variantJob);
        }
        else if(job->nextRun <= now) {
            PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))))).info() << " Run job - - > " << job->name;
            job->emitTimeOut();
            job->nextRun = computeNext(job);
        }
    });

    this->sortJobs();

    if(jobs.count() > 0) {
        PJob* job = jobs[0].value<PJob*>();
        qint64 msToNextRun = QDateTime::currentDateTime().msecsTo(job->nextRun);
        if(msToNextRun < 0) msToNextRun = 0;
        PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))))).info() <<  " msToNextRun ~ ~ ~ ~ >" << msToNextRun;
        timer.start(msToNextRun);
    }

}
