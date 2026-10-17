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



   #include "misc/pget.h"

   
   


PGet::PGet(const QString& labelText,
           const QString& cancelButtonText,
           int minimum,
           int maximum,
           bool rewriteMode,
           QWidget* parent,
           int f) :

QProgressDialog(labelText, cancelButtonText, minimum, maximum, parent, (Qt::WindowFlags)f) {

}


void PGet::get(const QString& url, const QString& fileName) {

    QNetworkAccessManager manager;
    reply = manager.get(QNetworkRequest(QUrl("http://" + url)));
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    connect(this, SIGNAL(canceled()), this, SLOT(cancelDownload()));
    eventLoop.exec();

    QFile file(fileName);
    file.remove();
    if (file.open(QIODevice::WriteOnly)) {
        QByteArray result = reply->readAll();
        qDebug() << "Update Completed => bytes written" << result.count();
        file.write(result);
        file.close();
    }
    delete reply;

}


void PGet::downloadProgress(qint64 bytesRead, qint64 totalBytes) {

    qDebug() << bytesRead << "/" << totalBytes;
    this->setMaximum(totalBytes);
    this->setValue(bytesRead);

}


void PGet::cancelDownload() {

    reply->abort();
    delete reply;
    reply = 0;

}
