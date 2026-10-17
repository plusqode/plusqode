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



   #include "widgets/paction.h"

   
   
   #include "core/ptranslator.h"

   
   
   
   
   
 

PAction::PAction(PVariant actionItem, QObject* parent) :
    QAction(parent),
    actionItem(actionItem) {

    QString objectName = PString(QString("%1Button").arg(actionItem.undefined("name", nil).toString()));
    setObjectName(objectName);

    if(PSinglUserManager::instance()->developerMode)
        setToolTip(objectName);

    setText(PTranslator::tr(actionItem.undefined("name", nil).toString()));
    if(actionItem.include("icon"))
        this->setIcon(QIcon(actionItem.undefined("icon", nil).toString()));

    connect(this, SIGNAL(triggered()), this, SLOT(onClick()));


}


void PAction::onClick() {

    emit click(actionItem);

}
