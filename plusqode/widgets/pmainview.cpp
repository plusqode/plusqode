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



   #include "widgets/pmainview.h"

   
   

PMainView::PMainView(PVariant& module, QWidget *parent) :
    QWidget(parent) {

    

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(100,100,100,100);

    QGridLayout* buttonLayout = new QGridLayout();
    gridLayout->addLayout(buttonLayout, 0, 0);

    PActionButton* exitButton = new PActionButton( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("exit"))->append("icon", QString("picons/core/actions-128/exit.png"))))), this);
    exitButton->setIconSize(QSize(128, 128));
    buttonLayout->addWidget(exitButton, 0, 0);
    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(quit()));

    PActionButton* authenticationButton = new PActionButton( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("auth"))->append("icon", QString("picons/core/actions-128/lock.png"))))), this);
    authenticationButton->setIconSize(QSize(128, 128));
    buttonLayout->addWidget(authenticationButton, 0, 1);
    QObject::connect(authenticationButton, SIGNAL(clicked()), this, SLOT(authentication()));

    QLabel* plusqodeLabel = new QLabel(this);
    plusqodeLabel->setAlignment(Qt::AlignCenter);
    plusqodeLabel->setScaledContents(true);

    QString iconFile = "picons/plusqode/plusqode-logo.png";
    if(module.undefined("attrs", nil). undefined("mainIcon", nil)!= nil) iconFile = module.undefined("attrs", nil).undefined("mainIcon", nil).toString();
    QPixmap pixmap(iconFile);
    if(module.undefined("attrs", nil). undefined("iconSize", nil)!= nil) {
        PVariant iconSize = PVariant::fromString(module.undefined("attrs", nil).undefined("iconSize", nil).toString());
        plusqodeLabel->setScaledContents(false);
        pixmap = pixmap.scaled(QSize(iconSize.undefined("0", nil).toInt(), iconSize.undefined("1", nil).toInt()));
    }
    plusqodeLabel->setPixmap(pixmap);
    gridLayout->addWidget(plusqodeLabel, 1, 0);

    QGridLayout* infoLayout = new QGridLayout();
    gridLayout->addLayout(infoLayout, 2, 0);

    if(module.undefined("attrs", nil). undefined("author", nil)!= nil) {
        QTextEdit* authorTextEdit = new QTextEdit(this);
        infoLayout->addWidget(authorTextEdit, 0, 0);
        authorTextEdit->setReadOnly(true);
        authorTextEdit->setDisabled(true);
        PVariant author = PVariant::fromString(module.undefined("attrs", nil).undefined("author", nil).toString());
        authorTextEdit->setAlignment(Qt::AlignCenter);
        authorTextEdit->append(PString(QString("==> %1 <==").arg(module.undefined("moduleLabel", nil).toString())));
        authorTextEdit->append(author.undefined("name", nil).toString());
        authorTextEdit->append(author.undefined("address", nil).toString().replace(',', '\n'));
        authorTextEdit->append(module.undefined("attrs", nil).undefined("website", nil).toString());
    }

    if(module.undefined("attrs", nil). undefined("description", nil)!= nil) {
        QTextEdit* descriptionTextEdit = new QTextEdit(this);
        infoLayout->addWidget(descriptionTextEdit, 0, 1);
        descriptionTextEdit->setReadOnly(true);
        descriptionTextEdit->setDisabled(true);
        descriptionTextEdit->setAlignment(Qt::AlignCenter);
        descriptionTextEdit->append(PString(QString("==> DESCRIPTION <==")));
        descriptionTextEdit->append(module.undefined("attrs", nil).undefined("description", nil).toString());
    }


}

void PMainView::quit() {

    PMath::initRandSequence(); if(PMath::rand() % 20 == 0) POpenUrl::byBrowser(QString("%1/main/examples").arg(PGlobal::url()));
    qApp->quit();

}



void PMainView::authentication() {

    PSinglUserManager::instance()->authenticate();


}
