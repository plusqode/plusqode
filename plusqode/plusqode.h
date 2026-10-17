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

#ifndef PLUS4C_H
#define PLUS4C_H

   #include <QtWidgets/QMainWindow>
   #include <QtCore/QDebug>
   #include <QtCore/QDirIterator>
   #include <QtCore/QTranslator>
   #include <QtCore/QThread>



   #include "core/pglobal.h"
   #include "core/pshareddata.h"
   #include "variant/pvariant.h"
   #include "demo/variant/pvariantdemo.h"
   #include "sql/psql.h"
   #include "sql/pmodel.h"
   #include "demo/sql/pmodeldemo.h"
   #include "demo/sql/pmodelviewdemo.h"
   #include "demo/sql/psqldemo.h"
   #include "demo/core/pviewloaderdemo.h"
   #include "sql/ppgsqlgenerator.h"
   #include "misc/pdir.h"
   #include "configuration/pconfigurationmanager.h"
   #include "core/plogger.h"
   #include "core/pviewloader.h"
   #include "core/pdocgenerator.h"
   #include "core/ptranslator.h"
   #include "core/pjobscheduler.h"
   #include "misc/psystem.h"
   #include "misc/pwindow.h"
   #include "misc/paccounting.h"

   #include "app/modules/telemetry/pmactivation/pactivationserver.h"

   #include "widgets/ptabnavigation.h"

   #include "pos/pposprintmanagerthread.h"

   #include "misc/pusermanager.h"

   #include "misc/ptelemetry.h"


namespace Ui {
    class PlusQode;
}

class PlusQode : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlusQode(QWidget *parent = 0);
    ~PlusQode();
    void startUi();
    void initSettings();
    void initJobSheduler();
    void modelClassTableDemo();
    void init(PVariant);

private:
    Ui::PlusQode *ui;
    PPosPrintManagerThread* posPrintManagerThread;
    PActivationServer* as;

    PTabNavigation* tabNavigation;
    PTranslator* translator;

};

#endif 



