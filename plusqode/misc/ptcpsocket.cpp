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




   #include "misc/ptcpsocket.h"


   

   

PTcpSocket::PTcpSocket(bool asyncMode, QObject *parent) :
    QTcpSocket(parent)
{
    
    this->asyncMode = asyncMode;
    if(asyncMode)
        connect(this, SIGNAL(readyRead()), this, SLOT(_receive()));

}


PTcpSocket::~PTcpSocket() {

    this->disconnectFromHost();
    this->close();

}


void PTcpSocket::changeMode(bool asyncMode) {

    if(asyncMode == this->asyncMode)
        return;

    this->asyncMode = asyncMode;
    if(asyncMode)
        connect(this, SIGNAL(readyRead()), this, SLOT(_receive()));
    else {
        this->disconnect(SIGNAL(readyRead()));
        this->waitForReadyRead();
        this->readAll(); 
    }

}


bool PTcpSocket::connectToHost(const QString& hostName, quint16 port, OpenMode openMode) {

    this->hostName = hostName;
    this->port = port;

    int i = 2; 
    while(--i > 0) {
        qDebug() << "Connetting to ... " << hostName << port;
        QTcpSocket::connectToHost(hostName, port, openMode);
        if (this->state() == QAbstractSocket::ConnectedState || this->waitForConnected()) {
            qDebug() << "Connected to" << hostName << port;
            break;
        }
    }

    if(i == 0) {
        qDebug() << "Cannot Connect to" << hostName << port;
        return false;
    }

    return true;

}

void PTcpSocket::disconnectFromHost() {

    QTcpSocket::disconnectFromHost();
    if (this->state() == QAbstractSocket::UnconnectedState || this->waitForDisconnected())
        qDebug() << "Disconnected !!!" << "\n";

}


void PTcpSocket::reconnectToLastHost() {

    connectToHost(hostName, port);

}

void PTcpSocket::stop() {

    this->waitForReadyRead();
    this->readAll(); 
    this->disconnect();

}


void PTcpSocket::send(const char* data, quint32 dataLen) {

    this->write(data, dataLen);

}

void PTcpSocket::send(const char* str) {

    this->send(str, strlen(str));

}

void PTcpSocket::send(QByteArray& data) {

    this->send(data.data(), data.count());

}

void PTcpSocket::send(QString& str) {

    this->send(str.toUtf8(), str.count());

}


QByteArray* PTcpSocket::_receive() {

    static quint32 counter = 0;
    static QByteArray* bufferAccumulator = 0;

    if(!bufferAccumulator)
        bufferAccumulator = new QByteArray();

    QByteArray byteArray = this->readAll();
    if(counter == 0) {
        quint32 size = ((quint32*)byteArray.data())[0];
        quint32 sizeCks = ((quint32*)byteArray.data())[1];

        if(size == 0 || sizeCks + size != 0xFFFFFFFF)
            return 0;
        counter = size - byteArray.count();
        bufferAccumulator->append(byteArray.mid(sizeof(quint32) + 4)); 
    }
    else {
        counter -= byteArray.count();
        bufferAccumulator->append(byteArray);
    }

    if(counter <= 0) {
        
        counter = 0;

        char ends[] = "xxxx";
        memcpy(ends, bufferAccumulator->data() + bufferAccumulator->count() - 4, 4);

        bufferAccumulator->resize(bufferAccumulator->count() - 4);

        QByteArray* result = bufferAccumulator;
        bufferAccumulator = 0;

        if(QString(ends) == "ends") {
            if(this->asyncMode)
                emit readyData(result);
            return result;
        }

        qDebug() << "======================< ERROR: PTcpSocket::receive >========================";
        this->waitForReadyRead(2000); 
        this->readAll(); 
        delete result;
        return 0;

    }

    return 0;

}

QByteArray* PTcpSocket::receive() {

    QByteArray* result = 0;

    while(!result) {
        if(this->waitForReadyRead() == 0)
            return 0; 
        result = this->_receive();
    }

    return result;

}

QByteArray PTcpSocket::receive2() {

    QByteArray* tmp = this->receive();
    QByteArray result(tmp->data(), tmp->count());
    delete tmp;
    return result;

}


bool PTcpSocket::checkInternetConnection() {

    PTcpSocket* socket = new PTcpSocket();
    bool result = socket->connectToHost("www.hyperteleport.com", 80);
    delete socket;

    return result;

}
