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

#ifndef PGEMBRIDGE_H
#define PGEMBRIDGE_H

   #include <QtCore/QtGlobal>


   #include "sql/pmodel.h"

   #include <QObject>
   #include <QTcpServer>
   #include <QTcpSocket>
   #include <QDebug>


#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
   #include <QtCore/QJsonObject>
   #include <QtCore/QJsonDocument>
   #include <QtCore/QJsonArray>
#endif

class QJsonObject;

class PGemBridge : public QObject {
    Q_OBJECT

public:
    explicit PGemBridge(quint16 port = 8888, QObject *parent = nullptr);

private slots:
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();
#else  
    void onNewConnection() {}
    void onReadyRead() {}
    void onClientDisconnected() {}
#endif

private:
    QTcpServer *m_tcpServer;

};


#endif 



