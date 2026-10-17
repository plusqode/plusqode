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

   #include "misc/pgembridge.h"      

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)


PGemBridge::PGemBridge(quint16 port, QObject *parent)
    : QObject(parent), m_tcpServer(new QTcpServer(this)) {

    connect(m_tcpServer, &QTcpServer::newConnection, this, &PGemBridge::onNewConnection);

    if (!m_tcpServer->listen(QHostAddress::LocalHost, port)) {
        qCritical() << "[QT SERVER] Errore avvio server:" << m_tcpServer->errorString();
    } else {
        qDebug() << "[QT SERVER] Server Qt in ascolto su 127.0.0.1:" << port;
    }
}

void PGemBridge::onNewConnection() {
    QTcpSocket *clientSocket = m_tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &PGemBridge::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &PGemBridge::onClientDisconnected);

    qDebug() << "\n[QT SERVER] Nuova connessione da:" << clientSocket->peerAddress().toString();
}

void PGemBridge::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    
    while (clientSocket->canReadLine()) {
        QByteArray lineData = clientSocket->readLine().trimmed();

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(lineData, &parseError);

        if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
            qWarning() << "[QT SERVER] JSON non valido:" << parseError.errorString();

            QJsonObject errResp;
            errResp["status"] = "error";
            errResp["message"] = "Formato JSON non valido";

            clientSocket->write(QJsonDocument(errResp).toJson(QJsonDocument::Compact) + "\n");
            continue;
        }

        PVariant request = PVariant::fromJson(doc.object());
        qDebug() << "[QT SERVER] Richiesta ricevuta:" << request.toString();

        
        PVariant response = PModel   ::mainHandleRequest(request);

        QJsonObject responseObj = response.toMap().toJson();

        qDebug() << "[QT SERVER] Send request:" << responseObj;

        
        QByteArray responseBytes = QJsonDocument(responseObj).toJson(QJsonDocument::Compact) + "\n";
        clientSocket->write(responseBytes);
        clientSocket->flush();
    }
}

void PGemBridge::onClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        qDebug() << "[QT SERVER] Client disconnesso.";
        clientSocket->deleteLater();
    }
}


#endif



