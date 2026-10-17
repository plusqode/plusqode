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

#ifndef PMAKEDIALOG_H
#define PMAKEDIALOG_H

   #include <QDialog>
   #include <QApplication>
   #include <QWidget>
   #include <QVBoxLayout>
   #include <QPushButton>
   #include <QTextEdit>
   #include <QProcess>
   #include <QDebug>

   #include "misc/pstring.h"
   #include "variant/pvariant.h"
   #include "core/plogger.h"
   #include "widgets/widgetedit/pprogressbarplus.h"

class PMakeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PMakeDialog(QWidget* parent = 0);

signals:

public slots:

    void startMake(bool turbo = false);
    void readStdout();
    void readStdErr();
    void onFinished(int code, QProcess::ExitStatus status);


private:
    QTextEdit* outputTextEdit;
    QProcess* process;
    QPushButton* closePushButon;
    PProgressBarPlus* progressBar;

    int steps;
    int sc; 


};

#endif 



