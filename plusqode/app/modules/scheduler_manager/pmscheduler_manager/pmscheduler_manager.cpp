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

#include "app/modules/scheduler_manager/pmscheduler_manager/pmscheduler_manager.h"
#include "app/modules/pmodules.h"

PMSchedulerManager::$PMSchedulerManager() {

    init(args);

}

PMSchedulerManager& PMSchedulerManager::init(PVariant args) {

    PModel::init(args);

    this->autoView = false; // false if you want to use pmscheduler_manager_view.xml

    name$ = $pt();

    service$ = $pt(fieldType: "combobox");
    service_ptr$.itemsAndValues$ = ${database: "Database",
                                     notification: "Notification",
                                     script: "Script Command",
                                     sql: "Sql Command"};

    state$ = $pb(fieldType: "switch_edit");
    type$ = $pt(fieldType: "combobox", default: "Once");
    type_ptr$.itemsAndValues$ = ${Once: "Once",
                                  EveryMinute: "EveryMinute",
                                  Daily: "Daily",
                                  Weekly: "Weekly"};

    time$ = $pt(fieldType: "time", default: psql->current('time'), enabled: false);
    interval$ = $pi(default: 10);

    day$ = $pt(fieldType: "combobox", default: "Monday", enabled: false);
    day_ptr$.itemsAndValues$ = ${Monday: "Monday",
                                 Tuesday: "Tuesday",
                                 Wednesday: "Wednesday",
                                 Thursday: "Thursday",
                                 Friday: "Friday",
                                 Saturday: "Saturday",
                                 Sunday: "Sunday"};

    description$ = $pt(fieldType: 'plain_text_edit');

    return *this;

}


PVariant PMSchedulerManager::action(PVariant action) {

    if(action.action$s == "print") {
       POpenUrl::writeHtml($"pos/generic", "xxx", this->html());
       return true;
    }
    else if(action.action$s == "action_name1")
        ;
    else if(action.action$s == "action_name2")
        ;
    return ${type: "message_box", description: "apply successfully", icon: "picons/core/actions-128/ok.png"};

}


void PMSchedulerManager::onChangeField(QString fieldName, PVariant fieldValue) {

    this->time$w->setEnabled(false);
    this->interval$w->setEnabled(false);
    this->day$w->setEnabled(false);

    qDebug() << fieldName << fieldValue.toString();

    if(fieldName == "type") {
        if(fieldValue == "EveryMinute")
            this->interval$w->setEnabled();
        if(fieldValue == "Daily" or fieldValue == "Weekly")
            this->time$w->setEnabled();
        if(fieldValue == "Weekly")
            this->day$w->setEnabled();
    }


}


PScheduleType PMSchedulerManager::scheduleType(const QString& type) {

    if(type == "Once")
        return PScheduleType::Once;
    if(type == "EveryMinute")
        return PScheduleType::EveryMinute;
    if(type == "Daily")
        return PScheduleType::Daily;
    if(type == "Weekly")
        return PScheduleType::Weekly;

    return PScheduleType::Once;

}

Qt::DayOfWeek PMSchedulerManager::dayOfWeek(const QString& day) {

    if(day == "Monday")
        return Qt::Monday;
    if(day == "Tuesday")
        return Qt::Tuesday;
    if(day == "Wednesday")
        return Qt::Wednesday;
    if(day == "Thursday")
        return Qt::Thursday;
    if(day == "Friday")
        return Qt::Friday;
    if(day == "Saturday")
        return Qt::Saturday;
    if(day == "Sunday")
        return Qt::Sunday;

    return Qt::Monday;

}


void PMSchedulerManager::start() {

    PJobScheduler* scheduler = PSinglJobScheduler::instance();

    $PLog(color: "red").debug()  << "PMSchedulerManager::start() ... Ok" ;

    PMSchedulerManager $sm();
    sm.$find();

    $sm.forEach(PVariant job) {
        if(job.state$b) {
            PJob* j = new PJob(job.name$s, scheduleType(job.type$s));
            j->interval = job.interval$i;
            j->time = job.time$t;
            j->day = dayOfWeek(job.day$s);

            if(job.service$s == "database")
                connect(j, SIGNAL(timeout()), PSinglSqlGenerator::instance().sqlGenerator, SLOT(dump()));
            else if(job.service$s == "notification") {
                PNotificationManager* notification = new PNotificationManager(j);
                notification->text = job.description$s;
                connect(j, SIGNAL(timeout()), notification, SLOT(showNotification()));
            }
            else if(job.service$s == "script") {
                PSystem* system = new PSystem(j);
                system->initByScriptCommand(job.description$s);
                connect(j, SIGNAL(timeout()), system, SLOT(runDetached()));
            }
            else if(job.service$s == "sql") {
                PSystem* system = new PSystem(j);
                system->initBySqlCommand(job.description$s);
                connect(j, SIGNAL(timeout()), system, SLOT(runDetached()));
            }

            scheduler->addJob(j);
            $PLog(color: "high_cyan").debug()  << $"  --> ${job.name$s} ... ok" ;
        }
    }

    scheduler->processJobs();

}
