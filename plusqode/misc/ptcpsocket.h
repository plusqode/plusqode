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

#ifndef PTCPSOCKET_H
#define PTCPSOCKET_H

   #include <QTcpSocket>
   #include <QByteArray>
   #include <QNetworkAccessManager>
   #include <QDebug>

class PTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit PTcpSocket(bool asyncMode = true, QObject *parent = 0);
    ~PTcpSocket();
    bool connectToHost(const QString& hostName, quint16 port, OpenMode openMode = ReadWrite);
    void changeMode(bool asyncMode = true);
    void disconnectFromHost();
    void reconnectToLastHost();
    static bool checkInternetConnection();

signals:
    void readyData(QByteArray*);

public slots:
    void send(const char* str);
    void send(const char* data, quint32 dataLen);
    void send(QByteArray& data);
    void send(QString& str);
    void stop();
    QByteArray* _receive();
    QByteArray* receive();
    QByteArray receive2();

private:
    QString hostName;
    quint16 port;
    bool asyncMode;

};

#endif 





