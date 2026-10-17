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

#ifndef PGET_H
#define PGET_H

   #include <QObject>
   #include <QProgressDialog>
   #include <QEventLoop>
   #include <QUrl>
   #include <QNetworkRequest>
   #include <QNetworkReply>
   #include <QFile>
   #include <QDebug>

class PGet : public QProgressDialog
{
    Q_OBJECT
public:
    explicit PGet(const QString& labelText,
                  const QString& cancelButtonText,
                  int minimum, int maximum,
                  bool rewriteMode = false,
                  QWidget * parent = 0, int f = 0);

    void get(const QString& url, const QString& fileName);

signals:
    void finished();

public slots:
    void downloadProgress(qint64 bytesRead, qint64 totalBytes);
    void cancelDownload();


private:
    QNetworkReply *reply;

};

#endif 



