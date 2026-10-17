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



   #include "widgets/widgetedit/pstateprogressbaredit.h"

   
   

PStateProgressBarEdit::PStateProgressBarEdit(QWidget* parent) :
    PFieldWidget(parent) {

    stateProgressBar = new PStateProgressBar(this);

    connect(stateProgressBar, SIGNAL(changeCurrentState(PVariant)), this, SLOT(onEditingFinished()));

    QGridLayout *layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignHCenter);

    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(stateProgressBar, 0, 0);

}

void PStateProgressBarEdit::setAttrs(PVariant attrs) {

    this->attrs = stateProgressBar->attrs = attrs;
    stateProgressBar->init(attrs.undefined("states", nil));

}


QWidget* PStateProgressBarEdit::mainWidget() {

    return 0;

}


PVariant PStateProgressBarEdit::data() {

    return stateProgressBar->currentState;

}

void PStateProgressBarEdit::setData(PVariant data) {

    stateProgressBar->setCurrentState(data.toString());

}

void PStateProgressBarEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    stateProgressBar->setPalette(pal);

}

void PStateProgressBarEdit::setReadOnly(bool value) {

}

void PStateProgressBarEdit::stateChanged(int state) {

    emit dataChanged(fieldName, data());

}

bool PStateProgressBarEdit::isEmpty() {

    return false;

}

void PStateProgressBarEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
