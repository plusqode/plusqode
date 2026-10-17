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



   #include "widgets/widgetedit/pimageedit.h"

   
   

PImageEdit::PImageEdit(QWidget *parent) :
        PFieldWidget(parent) {

    lineEdit = new QLineEdit(this);
    lineEdit->setMinimumHeight(PGlobal::fieldMinimumHeight());
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged(QString)));
    connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(onEditingFinished()));

    toolButton = new QToolButton(this);
    toolButton->setText("...");
    connect(toolButton, SIGNAL(clicked()), this, SLOT(selectionFile()));

    zoomImageToolButton = new QToolButton(this);
    zoomImageToolButton->setText("...");
    connect(zoomImageToolButton, SIGNAL(clicked()), this, SLOT(zoomImage()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);

    layout->addWidget(lineEdit, 0, 0);
    layout->addWidget(toolButton, 0, 1);
    layout->addWidget(zoomImageToolButton, 0, 2);

}

QWidget* PImageEdit::mainWidget() {

    return lineEdit;

}


PVariant PImageEdit::data() {

    return lineEdit->text();

}

void PImageEdit::setData(PVariant data) {

    lineEdit->setText(data.toString());

}

void PImageEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    lineEdit->setPalette(pal);

}

void PImageEdit::setReadOnly(bool value) {

    lineEdit->setReadOnly(value);
    setBackgroundColor(PGlobal::readOnlyFieldColor());

    toolButton->setHidden(value);
    zoomImageToolButton->setHidden(value);

}


void PImageEdit::textChanged(QString text) {

    emit dataChanged(fieldName, data());

}

bool PImageEdit::isEmpty() {

    return lineEdit->text().isEmpty();

}



void PImageEdit::selectionFile() {

    PImageFileDialog fileDialog(this);

    QString basedir = "~";
    fileDialog.setDirectory(basedir);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setViewMode(QFileDialog::Detail);
    fileDialog.setFileMode(QFileDialog::AnyFile);

    if( fileDialog.exec() == QDialog::Accepted ) {
        lineEdit->setText(fileDialog.selectedFiles()[0]);
        onEditingFinished();
    }


}


void PImageEdit::zoomImage() {

    PImageZoomDialog izd(data().toString());
    izd.exec();

}


void PImageEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
