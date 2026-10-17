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

#include "app/modules/telemetry/pmactivation/pactivationserver.h"

PActivationServer::PActivationServer(const QString& port, const QString& endpoint, QObject *parent) :
    QObject(parent) {

    this->port = port;
    this->endpoint = endpoint;

    jhService = new PJsonHttpService(this);
    connect(jhService, SIGNAL(onReceived(QJsonObject)), this, SLOT(onReceived(QJsonObject)));

    jhService->jsonServer(port, endpoint);


}


void PActivationServer::onReceived(const QJsonObject& json) {

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)

//    QMap<QString, QVariant> json;

    qDebug() << " - - >"
            << json["system/os_name"].toString()
            << json["usage/sessions"].toString()
            << json["activation_date"].toString()
            << json["usage/last_start_date"].toString();

    PSql $activation();

    QString activationId = json["activationId"].toString();

    activation.$select("id")->
    $from("activation")->
    $where(name: activationId)->
    $execute();

    if(activation.count() == 0) {
        $PSql().insert("activation",
                     ${name: activationId,
                    version: json["usage/version"].toString(),
            activation_date: json["activation_date"].toString(),
            last_start_date: json["usage/last_start_date"].toString(),
                    os_name: json["system/os_name"].toString(),
                    os_type: json["system/os_type"].toString(),
                 os_version: json["system/os_version"].toString(),
               architecture: json["system/architecture"].toString(),
                   language: json["system/language"].toString(),
             total_sessions: json["usage/sessions"].toString(),
              total_minutes: json["usage/total_minutes"].toString(),
                  client_id: json["client_id"].toString(),
              module_usages: json["module_usages"].toString()});
    }
    else {
        $PSql().update("activation",
                  ${version: json["usage/version"].toString(),
            activation_date: json["activation_date"].toString(),
            last_start_date: json["usage/last_start_date"].toString(),
                    os_name: json["system/os_name"].toString(),
                    os_type: json["system/os_type"].toString(),
                 os_version: json["system/os_version"].toString(),
               architecture: json["system/architecture"].toString(),
                   language: json["system/language"].toString(),
             total_sessions: json["usage/sessions"].toString(),
              total_minutes: json["usage/total_minutes"].toString(),
                  client_id: json["client_id"].toString(),
              module_usages: json["module_usages"].toString()},
             ${name: activationId});
    }


#endif

}
