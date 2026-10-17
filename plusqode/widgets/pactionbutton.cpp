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




   #include "widgets/pactionbutton.h"


   

   
   #include "core/ptranslator.h"


   

   
   

   
   
 

PActionButton::PActionButton(PVariant actionButton, QWidget* parent) :
        PPushButton(parent),
        actionButton(actionButton) {

    PSinglUserManager::instance()->setObjectName(this, PString(QString("%1Button").arg(actionButton.undefined("name", nil).toString())));

    if(actionButton.include("fontSize"))
        this->setTextSize(actionButton.undefined("fontSize", nil).toInt());

    if(actionButton.include("toolTip"))
        this->setToolTip(PTranslator::tr(actionButton.undefined("toolTip", nil).toString()));

    if(actionButton.include("alignment"))
        this->setTextAlignment(actionButton.undefined("alignment", nil).toString());

    if(actionButton.include("icon")) {
        if(actionButton.undefined("icon", nil).typeName() == "QString" && actionButton.undefined("icon", nil).toString().startsWith("{"))
            actionButton.  undefined("icon=", PVariant::fromString(actionButton.undefined("icon", nil).toString()));

        if(actionButton.undefined("icon", nil).typeName() == "QString")
            this->setIcon(QIcon(actionButton.undefined("icon", nil).toString()));
        else if(actionButton.undefined("icon", nil).typeName() == "Hash") {
            int w = actionButton.undefined("icon", nil).undefined("width", nil).toInt() | 32;
            int h = actionButton.undefined("icon", nil).undefined("height", nil).toInt() | 32;
            setIconSize(QSize(w, h));
            this->setToolTip(PTranslator::tr(actionButton.undefined("icon", nil).undefined("toolTip", nil).toString()));
            PImage image(actionButton.undefined("icon", nil).undefined("name", nil).toString());
            image.setHS(actionButton.undefined("icon", nil).undefined("hue", nil).toInt(), actionButton.undefined("icon", nil).undefined("saturation", nil).toInt());
            this->setIcon(image.toIcon());
        }
    }
    else
        setText(PTranslator::tr(actionButton.undefined("name", nil).toString()));

    PWidgetAttrs::setWidget(this, actionButton);

    if(actionButton.include("menu"))
        setMenu(initMenu(actionButton.undefined("menu", nil)));

    connect(this, SIGNAL(clicked()), this, SLOT(onClick()));

}

PActionButton::~PActionButton() {

}

QMenu* PActionButton::initMenu(PVariant actionItems, QString menuTitle) {

    QMenu* menu = new QMenu(menuTitle, (QWidget*)this->parent());

     actionItems.forEachPVariant([&] (PVariant actionItem) mutable {
        if(actionItem.undefined("name", nil).toString().startsWith("="))
            menu->addSeparator();
        else if(actionItem.include("menu")) {
            QMenu* subMenu = initMenu(actionItem.undefined("menu", nil), actionItem.undefined("name", nil).toString());
            menu->addMenu(subMenu);

            
            if(actionItem.include("icon")) {
                if(actionItem.undefined("icon", nil).typeName() == "QString" && actionItem.undefined("icon", nil).toString().startsWith("{"))
                    actionItem.  undefined("icon=", PVariant::fromString(actionItem.undefined("icon", nil).toString()));

                if(actionItem.undefined("icon", nil).typeName() == "QString")
                    subMenu->setIcon(QIcon(actionItem.undefined("icon", nil).toString()));
                else if(actionItem.undefined("icon", nil).typeName() == "Hash") {
                    int w = actionItem.undefined("icon", nil).undefined("width", nil).toInt() | 32;
                    int h = actionItem.undefined("icon", nil).undefined("height", nil).toInt() | 32;
                    setIconSize(QSize(w, h));
                    PImage image(actionItem.undefined("icon", nil).undefined("name", nil).toString());
                    image.setHS(actionItem.undefined("icon", nil).undefined("hue", nil).toInt(), actionItem.undefined("icon", nil).undefined("saturation", nil).toInt());
                    subMenu->setIcon(image.toIcon());
                }
            }
            

        }
        else {
            action = new PAction(actionItem, menu);
            connect(action, SIGNAL(click(PVariant)), this, SLOT(onClick(PVariant)));
            menu->addAction(action);
        }
    });


    return menu;

}

void PActionButton::onClick() {

    emit click(actionButton);
    emit click(this);

}


void PActionButton::onClick(PVariant actionItem) {

    emit click(actionItem);
    emit click(this);

}
