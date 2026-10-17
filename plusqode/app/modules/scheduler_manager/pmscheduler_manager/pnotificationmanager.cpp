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

#include "app/modules/scheduler_manager/pmscheduler_manager/pnotificationmanager.h"

PNotificationManager::PNotificationManager(QObject *parent) :
    QObject(parent)
{
}


PNotificationManager::~PNotificationManager() {

    // qDebug() << "~ ~ ~ ~ ~ ~ ~PNotificationManager()";

}


void PNotificationManager::showNotification() {

    QWidget* window = new QWidget();
    window->setWindowTitle("Notification");
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->resize(300, 100);
    window->setStyleSheet("background-color: white;");
    QVBoxLayout *layout = new QVBoxLayout(window);


    QLabel* imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setPixmap(QPixmap("picons/core/models/scheduler.png"));
    layout->addWidget(imageLabel);


    QLabel* label = new QLabel(text, window);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QPushButton* button = new QPushButton("Ok");
    button->setIcon(QIcon("picons/core/actions-128/ok.png"));
    button->setMinimumHeight(50);
    layout->addWidget(button);

    QObject::connect(button, SIGNAL(clicked()), window, SLOT(close()));

    window->show();

//    PMMessageBox::$messageBox(text: this->text, icon: "picons/core/actions-128/ok.png");

}

