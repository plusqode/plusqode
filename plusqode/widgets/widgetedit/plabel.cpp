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



   #include "widgets/widgetedit/plabel.h"

   
   

PLabel::PLabel(QWidget *parent) :
    PFieldWidget(parent) {

    label = new QLabel(this);
    label->setFont(PGlobal::widgetFont());

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(label, 0, 0);

}


void PLabel::setAttrs(PVariant fieldAttrs) {

    PFieldWidget::setAttrs(fieldAttrs);

    if(fieldAttrs.undefined("link", nil).toBool() == true)
        label->setOpenExternalLinks(true);

    if(fieldAttrs.undefined("pdf", nil).toBool() == true)
        connect(label, SIGNAL(linkActivated(QString)), this, SLOT(onClicked(QString)));

}


QWidget* PLabel::mainWidget() {

    return label;

}


PVariant PLabel::data() {

    return this->value;

}

void PLabel::setData(PVariant data) {

    this->value = data;

    if(attrs.undefined("link", nil).toBool() == true and !data.toString().startsWith("<a"))
        label->setText(PString(QString("<a href='%1'>%2</a>").arg(data.toString()).arg(data.toString())));
    else if(attrs.undefined("pdf", nil).toBool() == true)
        label->setText(PString(QString("<a href='%1'>pdf</a>").arg(data.toString())));
    else
        label->setText(data.toString());

}

void PLabel::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    label->setPalette(pal);

}


bool PLabel::isEmpty() {

    return label->text().isEmpty();

}

void PLabel::onClicked(QString str) {

    POpenUrl::byPdf(data().toString());

}
