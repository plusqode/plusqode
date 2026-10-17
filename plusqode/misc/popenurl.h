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

#ifndef POPENURL_H
#define POPENURL_H

   #include "core/pglobal.h"
   #include "core/plogger.h"
   #include "misc/pget.h"

   #include <QtCore/QTimer>
   #include <QDesktopServices>
   #include <QUrl>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#if not defined (Q_OS_WIN) || QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
   #include <QWebEngineView>
   #include <QWebEnginePage>
#endif
#endif

class POpenUrl {

public:
    POpenUrl();
    static void byPdf(const QString& pdfUrl);
    static void byBrowser(const QString& url);
    static void writeHtml(const QString& relativePathName, const QString& fileName, const QString& htmlContent);

};

#endif 



