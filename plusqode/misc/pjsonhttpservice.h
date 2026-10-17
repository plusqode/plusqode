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

#ifndef PJSONHTTPSERVICE_H
#define PJSONHTTPSERVICE_H

   #include <QObject>
   #include <QProgressDialog>
   #include <QEventLoop>
   #include <QUrl>
   #include <QNetworkRequest>
   #include <QNetworkReply>
   #include <QTcpServer>
   #include <QFile>
   #include <QDebug>

   #include "variant/pvariant.h"

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
   #include <QtCore/QJsonObject>
   #include <QtCore/QJsonDocument>
   #include <QtCore/QJsonArray>
#endif

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
   #include <QHttpServer>
#endif

class QJsonObject;
class QJsonDocument;

class PJsonHttpService : public QObject
{
    Q_OBJECT
public:
    explicit PJsonHttpService(QObject* parent = 0);

    int jsonServer(const QString& port, const QString& endpoint);

    void postJson(const QString& url, const QJsonObject&);


signals:
    
    void postFinished(const QByteArray &response);

    
    void postError(const QString &errorStr);

    void onReceived(const QJsonObject&);


public slots:
    void onRequestFinished(QNetworkReply*);


private:
    QNetworkAccessManager manager;

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    QHttpServer* server = nullptr;
#endif

};

#endif 



