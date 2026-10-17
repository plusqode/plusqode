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



   #include "misc/ptelemetry.h"

   
   
   #include "app/modules/pmodules.h"

   
   
   
   
   
 

PTelemetry::PTelemetry(QObject* parent) :
    QObject(parent),
    settings("plusqode", "plusqode") {

    

    jhService = new PJsonHttpService(this);

    connect(jhService, SIGNAL(postFinished(const QByteArray&)), this, SLOT(postFinished(const QByteArray&)));

    connect(jhService, SIGNAL(postError(const QString&)), this, SLOT(postError(const QString&)));

    this->initInstallationId();

    this->th = PMSetting(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))))).find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))))->undefined("telemetry", nil).toString();

    timer = new QTimer(this);
    timer->start(5 * 60 * 1000);

    this->startSession("main");

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

}


PTelemetry::~PTelemetry() {

    this->endSession();

}


void PTelemetry::add(const QString& key, qint64 value) {

    qint64 currentValue = this->settings.value(key, 0).toLongLong();
    settings.setValue(key, currentValue + value);
    settings.sync();

}


void PTelemetry::startSession(const QString& moduleName) {

    int sessions = this->settings.value("usage/sessions").toInt();
    QString selection = this->settings.value("selection").toString();

    

    if(selection.isEmpty() and sessions > 5) {
        PMStatistic statistic(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
        statistic.initDialog();
        statistic.exec();
        this->settings.setValue("selection", statistic.undefined("selection", nil).toString());
    }


    this->currentModuleName = moduleName;

    sessionTimer.start();
    moduleTimer.start();

    this->settings.setValue(PString(QString("usage/last_start_date")), QDateTime::currentDateTimeUtc());
    this->settings.setValue(PString(QString("usage/version")), qApp->applicationVersion());
    this->add("usage/sessions", 1);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    this->settings.setValue(PString(QString("system/os_type")), QSysInfo::productType());
    this->settings.setValue(PString(QString("system/os_name")), QSysInfo::prettyProductName());
    this->settings.setValue(PString(QString("system/os_version")), QSysInfo::productVersion());
    this->settings.setValue(PString(QString("system/architecture")), QSysInfo::currentCpuArchitecture());
    this->settings.setValue(PString(QString("system/language")), QLocale::system().name());
#endif

    this->update();

}


void PTelemetry::endSession() {

    this->update();

}

void PTelemetry::update() {

    qint64 minutes = sessionTimer.elapsed() / 1000 / 60;

    this->add("usage/total_minutes", minutes);

    sessionTimer.restart();

    if(!(this->settings.value("selection") == "false"))
        this->send();

}



void PTelemetry::onChangeModule(const QString& moduleName) {

    qint64 minutes = moduleTimer.elapsed() / 1000 / 60;

    this->add(PString(QString("modules/%1/total_minutes").arg(currentModuleName)), minutes);

    moduleTimer.restart();

    this->currentModuleName = moduleName;

}

QString PTelemetry::initInstallationId() {

    QString id = settings.value("activationId").toString();

    if(id.isEmpty()) {
        id = QUuid::createUuid().toString();
        id.remove('{');
        id.remove('}');
        settings.setValue("activationId", id);
        settings.setValue("client_id", QUuid::createUuid().toString());
        settings.setValue("activation_date", QDateTime::currentDateTimeUtc());
    }

    QString activationDate = settings.value("activation_date").toString();
    if(activationDate.isEmpty())
        settings.setValue("activation_date", QDateTime::currentDateTimeUtc());

    return id;

}

void PTelemetry::show() {



}


void PTelemetry::send() {

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)

    QStringList moduleUsages;

    QJsonObject json;

    for(const QString &key : settings.allKeys()) {
        if(key.startsWith("modules"))
            moduleUsages << PString(QString("%1: %2").arg(key).arg(settings.value(key).toString()));
        else
            json[key] = settings.value(key).toString();
    }

    json["module_usages"] = moduleUsages.join("\n");

    this->show();

    jhService->postJson(th, json);

#endif

}


void PTelemetry::postFinished(const QByteArray& response) {

    

}

void PTelemetry::postError(const QString& errorStr) {


    


}
