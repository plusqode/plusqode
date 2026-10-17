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

#ifndef PTELEMETRY_H
#define PTELEMETRY_H

   #include <QObject>
   #include <QtWidgets/QApplication>
   #include <QtCore/QElapsedTimer>
   #include <QtCore/QTimer>
   #include <QtCore/QDateTime>
   #include <QtCore/QSettings>
   #include <QtCore/QUuid>
   #include <QtCore/QSysInfo>

   #include "variant/pvariant.h"
   #include "misc/pjsonhttpservice.h"

class QJsonObject;

class PTelemetry : public QObject
{
    Q_OBJECT
public:
    explicit PTelemetry(QObject *parent = 0);
    ~PTelemetry();
    void startSession(const QString& moduleName);
    void endSession();
    void add(const QString& key, qint64 value);
    QString initInstallationId();
    void show();
    void send();

signals:

public slots:
    void update();
    void onChangeModule(const QString& moduleName);
    void postFinished(const QByteArray& response);
    void postError(const QString&);

private:

    QSettings settings;
    QElapsedTimer sessionTimer;
    QElapsedTimer moduleTimer;
    QTimer* timer;

    QString currentModuleName;

    QString th;

    PJsonHttpService* jhService;

};


class PSinglTelemetry {

public:
    static PTelemetry* instance() {
        static PTelemetry instance;
        return &instance;
    }
};


#endif 



