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



   #include "misc/pprocessdialog.h"

   
   

PProcessDialog::PProcessDialog(QWidget* parent) :
        QDialog(parent), process(new QProcess(this)) {

    QVBoxLayout* layout = new QVBoxLayout(this);

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


    layout->addWidget(outputTextEdit);
    layout->addWidget(closePushButon);

    connect(closePushButon, SIGNAL(clicked()), this, SLOT(close()));
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(onFinished(int,QProcess::ExitStatus)));


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readStdout()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(readStdErr()));
#else
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, &QProcess::readyRead, this, &PProcessDialog::readStdout);
#endif

}

void PProcessDialog::start(const QString& program, const QStringList& arguments) {

    outputTextEdit->clear();
    

    process->start(program, arguments);

}


void PProcessDialog::stop() {

    if(this->process->state() != QProcess::NotRunning)
        process->terminate();

}


void PProcessDialog::readStdout() {

    outputTextEdit->append(process->readAllStandardOutput());

}


void PProcessDialog::readStdErr() {

    outputTextEdit->append(process->readAllStandardError());

}


void PProcessDialog::onFinished(int code, QProcess::ExitStatus status) {

    Q_UNUSED(status);
    outputTextEdit->append(QString("\n---\nProcess Finished (exit code %1)").arg(code));
    

}
