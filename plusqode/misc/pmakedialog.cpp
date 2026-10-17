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



   #include "misc/pmakedialog.h"

   
   

PMakeDialog::PMakeDialog(QWidget *parent) :
    QDialog(parent), process(new QProcess(this)) {

    QVBoxLayout* layout = new QVBoxLayout(this);
    progressBar = new PProgressBarPlus(this);
    PMath::initRandSequence();
    int color = PMath::rand() % 345;
    progressBar->   setAttrs(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("hue", color)->append("style", QString("mac"))))));

    closePushButon = new QPushButton("Close", this);
    outputTextEdit = new QTextEdit(this);
    outputTextEdit->setReadOnly(true);

    outputTextEdit->setStyleSheet(R"(
    QTextEdit {
        background-color: "black";
        color: #dcdcdc;
        border: 1px solid #3c3f41;
        selection-background-color: #4b6eaf;
        selection-color: white;
        font-family: Consolas, "Courier New", monospace;
        font-size: 10pt;
    }
    )");


    layout->addWidget(progressBar);
    layout->addWidget(outputTextEdit);
    layout->addWidget(closePushButon);

    connect(closePushButon, SIGNAL(clicked()), this, SLOT(close()));
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdout()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readStdErr()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(onFinished(int,QProcess::ExitStatus)));

}

void PMakeDialog::startMake(bool turbo) {

    QProcess dryProcess;
    dryProcess.start("make", QStringList() << "-n");
    dryProcess.waitForFinished(-1);

    QString out = dryProcess.readAllStandardOutput();
    QString err = dryProcess.readAllStandardError();

    PVariant statements = PString(out).split("\n");

    sc = 0;
    steps = 0;

     statements.forEachPString([&] (PString s) mutable {
        if(!s.include("=>")) steps++;
    });

    progressBar->setRange(0, steps);
    progressBar->setValue(0);

    outputTextEdit->clear();
    closePushButon->setEnabled(false);

    if(turbo) {
        qDebug() << "=> turbo make -> make -j4";
        process->start("make -j4");
    }
    else {
        qDebug() << "=> make";
        process->start("make");
    }

}

void PMakeDialog::readStdout() {
    
    progressBar->setValue(sc++);
    PLog() << sc << " on " << steps;
    outputTextEdit->append(process->readAllStandardOutput());
}


void PMakeDialog::readStdErr() {
    outputTextEdit->append(process->readAllStandardError());
}


void PMakeDialog::onFinished(int code, QProcess::ExitStatus status) {
    Q_UNUSED(status);
    progressBar->setValue(steps);
    outputTextEdit->append(QString("\n---\nProcess Finished (exit code %1)").arg(code));
    closePushButon->setEnabled(true);
}
