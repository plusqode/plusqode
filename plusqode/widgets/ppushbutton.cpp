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



   #include "widgets/ppushbutton.h"

   
   

PPushButton::PPushButton(QWidget* parent) :
       QPushButton(parent) {

    iconLabel = 0;

    gridLayout = new QGridLayout(this);
    this->setLayout(gridLayout);

    textLabel = new QLabel(this);

     gridLayout->addWidget(textLabel, 1, 0);

}

void PPushButton::setPosStyle() {

    gridLayout->setSpacing(0);
    iconLabel = new QLabel(this);
    iconLabel->setPixmap(this->icon().pixmap(size()));
    gridLayout->addWidget(iconLabel, 0, 0);

}

void PPushButton::setText(const QString& text) {

    textLabel->setText(text);

}

void PPushButton::setTextSize(int size) {

    QFont font = PGlobal::widgetFont();
    font.setPointSize(size);
    textLabel->setFont(font);

}

void PPushButton::setIcon(const QIcon& icon) {

    if(iconLabel)
        iconLabel->setPixmap(icon.pixmap(size()));
    else
        QPushButton::setIcon(icon);

}


void PPushButton::setIconSize(const QSize& size) {

    if(iconLabel)
        iconLabel->setScaledContents(true);
    else
        QPushButton::setIconSize(size);

}


QString PPushButton::text() {

    return textLabel->text();

}

void PPushButton::setTextAlignment(const QString& alignment) {

    if(alignment == "left")
        textLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    else if(alignment == "center")
        textLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    else if(alignment == "right")
        textLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    else
        textLabel->setAlignment(Qt::Alignment(alignment.toInt()));

    if(iconLabel) {
        if(alignment == "left")
            iconLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        else if(alignment == "center")
            iconLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        else if(alignment == "right")
            iconLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        else
            iconLabel->setAlignment(Qt::Alignment(alignment.toInt()));

    }

}
