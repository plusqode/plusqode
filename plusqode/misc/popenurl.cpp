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




   #include "misc/popenurl.h"


   

   

POpenUrl::POpenUrl() {

}

void POpenUrl::byPdf(const QString& pdfUrl) {

    QString pdfFileName = PString(QString("%1/tmp.pdf").arg(QDir::currentPath()));

    PGet g("Downloading...", "Abort", 0, 100);
    g.get(pdfUrl, pdfFileName);
    QDesktopServices::openUrl(QUrl::fromLocalFile(pdfFileName));

}


void POpenUrl::byBrowser(const QString& url) {

    QDesktopServices::openUrl(QUrl(url));

}


void POpenUrl::writeHtml(const QString& relativePathName, const QString& fileName, const QString& htmlContent) {

    QString filePath = PString(QString("%1/%2").arg(PGlobal::dataPath()).arg(relativePathName));

    QString htmlFileName = PString(QString("%1/%2.html").arg(filePath).arg(fileName));
    QString pdfFileName = PString(QString("%1/%2.pdf").arg(filePath).arg(fileName));

    PDir::fileWrite(htmlFileName, htmlContent.toUtf8());

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)

    QDesktopServices::openUrl(QUrl::fromLocalFile(htmlFileName));

#elif defined (Q_OS_WIN) && QT_VERSION < QT_VERSION_CHECK(6, 0, 0)

    QDesktopServices::openUrl(QUrl::fromLocalFile(htmlFileName));

#else
    QWebEngineView *view = new QWebEngineView();
    view->page()->load(QUrl::fromLocalFile(htmlFileName));

    QObject::connect(view->page(), &QWebEnginePage::loadFinished, [view, pdfFileName](bool){
            view->page()->printToPdf([&](const QByteArray &pdfData){
                QFile file(pdfFileName);
                if(file.open(QIODevice::WriteOnly)) {
                    file.write(pdfData);
                    file.close();
                    QDesktopServices::openUrl(QUrl::fromLocalFile(pdfFileName));
                    PLog().debug() << PString(QString("PDF salvato con successo in %1").arg(pdfFileName));
                }
                else
                    PLog().debug() << "Errore: impossibile scrivere il file PDF.";
                });
            });
#endif

}
