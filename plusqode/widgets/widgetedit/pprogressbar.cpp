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





   #include "widgets/widgetedit/pprogressbar.h"



   


   

PProgressBar::PProgressBar(QWidget *parent) :
    PFieldWidget(parent) {

    progressBar = new QProgressBar(this);

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(progressBar, 0, 0);

}

QWidget* PProgressBar::mainWidget() {

    return progressBar;

}

PVariant PProgressBar::data() {

    return progressBar->text();

}

void PProgressBar::setData(PVariant data) {

    progressBar->setValue(data.toInt());

}

void PProgressBar::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    progressBar->setPalette(pal);

}


bool PProgressBar::isEmpty() {

    return progressBar->text().isEmpty();

}
