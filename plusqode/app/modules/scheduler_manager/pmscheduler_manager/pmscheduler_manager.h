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

#ifndef PMSCHEDULER_MANAGER_H
#define PMSCHEDULER_MANAGER_H

#include "sql/pmodel.h"
#include "misc/popenurl.h"
#include "core/pjobscheduler.h"
#include "app/modules/scheduler_manager/pmscheduler_manager/pnotificationmanager.h"

class PMSchedulerManager : public PModel {

    Q_OBJECT

public:
#include "dom/phtml_header.h"

    PMSchedulerManager() {};
    PMSchedulerManager(PVariant args);
    PMSchedulerManager& init(PVariant);
    static PScheduleType scheduleType(const QString& type);
    static Qt::DayOfWeek dayOfWeek(const QString& day);
    static void start();

public slots:
    PVariant action(PVariant action);
    void onChangeField(QString fieldName, PVariant data);

};

Q_DECLARE_METATYPE(PMSchedulerManager*)

#endif // PMSCHEDULER_MANAGER_H
