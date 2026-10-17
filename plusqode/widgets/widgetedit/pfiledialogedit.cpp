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



   #include "widgets/widgetedit/pfiledialogedit.h"

   
   

PFileDialogEdit::PFileDialogEdit(QWidget *parent) :
        PFieldWidget(parent)  {

    lineEdit = new QLineEdit(this);
    lineEdit->setMinimumHeight(PGlobal::fieldMinimumHeight());
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

    toolButton = new QToolButton(this);
    toolButton->setText("...");
    connect(toolButton, SIGNAL(clicked()), this, SLOT(selectionFile()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);

    layout->addWidget(lineEdit, 0, 0);
    layout->addWidget(toolButton, 0, 1);

}

QWidget* PFileDialogEdit::mainWidget() {

    return lineEdit;

}


PVariant PFileDialogEdit::data() {

    return lineEdit->text();

}

void PFileDialogEdit::setData(PVariant data) {

    lineEdit->setText(data.toString());

}

void PFileDialogEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    lineEdit->setPalette(pal);

}

void PFileDialogEdit::setReadOnly(bool value) {

    lineEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());
    toolButton->setHidden(value);

}

void PFileDialogEdit::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PFileDialogEdit::isEmpty() {

    return lineEdit->text().isEmpty();

}


QString PFileDialogEdit::selectionFile() {

    QFileDialog fileDialog(this);

    QString basedir = "~";
    fileDialog.setDirectory(basedir);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setViewMode(QFileDialog::Detail);
    fileDialog.setFileMode(QFileDialog::AnyFile);

    if(this->attrs.include("filter"))
        fileDialog.setNameFilter(this->attrs.undefined("filter", nil).toString());

    if( fileDialog.exec() == QDialog::Accepted ) {
        lineEdit->setText(fileDialog.selectedFiles()[0]);
        onEditingFinished();
        return fileDialog.selectedFiles()[0];
    }

    return QString();

}

void PFileDialogEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
