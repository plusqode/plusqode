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



   #include "widgets/pactionbuttons.h"

   
   

PActionButtons::PActionButtons(QWidget *parent) :
        QWidget(parent) {

    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(0);

}

PVariant PActionButtons::toVariant(PVariant variantView) {

    PVariant menuVariant = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
     variantView.forEachPVariant([&] (PVariant actionItem) mutable {
        if(actionItem. undefined("name", nil) ==  "menuitem")
            menuVariant << actionItem.undefined("attrs", nil);
        else if(actionItem. undefined("name", nil) ==  "menusection") {
            PVariant children = toVariant(actionItem.undefined("children", nil));
            menuVariant << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("menu", children)))) + actionItem.undefined("attrs", nil);
        }
    });

    return menuVariant;
}

QWidget* PActionButtons::initByVariant(PVariant root) {

    int row = 0, col = 0;
     root.forEachPVariant([&] (PVariant button) mutable {
        QString newLine = (button.include("newline")) ?  button.undefined("newline", nil).toString() : "false";
        PActionButton* btn = new PActionButton(button, this);
        connect(btn, SIGNAL(click(PVariant)), this, SLOT(onClick(PVariant)));
        if(button. undefined("row", nil)!= nil and button.undefined("row", nil).toInt() != -1) row = button.undefined("row", nil).toInt();
        if(button. undefined("col", nil)!= nil and button.undefined("col", nil).toInt() != -1) col = button.undefined("col", nil).toInt();
        gridLayout->addWidget(btn, row, col);
        if(newLine != "true") col++;
        else { row++, col = 0; }
    });

    return this;

}

QWidget* PActionButtons::initByXml(PVariant parentView) {

    initByVariant(toVariant(parentView));
    return this;

}


void PActionButtons::onClick(PVariant actionButton) {

    emit click(actionButton);

}


void PActionButtons::setButtonSize(PVariant buttons, int width, int height) {

     buttons.forEachPVariant([&] (PVariant button) mutable {
        button.  undefined("minimumWidth=", width);
        button.  undefined("minimumHeight=", height);
        button.  undefined("alignment=", "center");
    });

}


void PActionButtons::setFontSize(PVariant buttons, int fontSize) {

     buttons.forEachPVariant([&] (PVariant button) mutable {
        button.  undefined("fontSize=", fontSize);
    });

}


PVariant PActionButtons::numberPad1() {

    PVariant buttons = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("7"))->append("row", 0)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("8"))->append("row", 0)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("9"))->append("row", 0)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("4"))->append("row", 1)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("5"))->append("row", 1)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("6"))->append("row", 1)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("1"))->append("row", 2)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("2"))->append("row", 2)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("3"))->append("row", 2)->append("col", 2))));

    return buttons;

}

PVariant PActionButtons::numberPad2() {

    PVariant decimals = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    decimals << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.1")))));
    decimals << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.2")))));
    decimals << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.3")))));
    decimals << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.4")))));
    decimals << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.5")))));
    decimals << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.6")))));
    decimals << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.7")))));
    decimals << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.8")))));
    decimals << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.9")))));

    PVariant buttons = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("7"))->append("row", 0)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("8"))->append("row", 0)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("9"))->append("row", 0)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("4"))->append("row", 1)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("5"))->append("row", 1)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("6"))->append("row", 1)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("1"))->append("row", 2)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("2"))->append("row", 2)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("3"))->append("row", 2)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0.x"))->append("row", 3)->append("col", 0)->append("menu", decimals))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("qty"))->append("row", 3)->append("col", 1))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("$"))->append("row", 3)->append("col", 2))));

    return buttons;

}

PVariant PActionButtons::numberPad3() {

    PVariant buttons = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("7"))->append("row", 0)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("8"))->append("row", 0)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("9"))->append("row", 0)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("4"))->append("row", 1)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("5"))->append("row", 1)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("6"))->append("row", 1)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("1"))->append("row", 2)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("2"))->append("row", 2)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("3"))->append("row", 2)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0"))->append("row", 3)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString(","))->append("row", 3)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("C"))->append("row", 3)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("Cancel"))->append("row", 4)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("Ok"))->append("row", 4)->append("col", 2))));

    return buttons;

}


PVariant PActionButtons::numberPad4() {

    PVariant buttons = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("7"))->append("row", 0)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("8"))->append("row", 0)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("9"))->append("row", 0)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("4"))->append("row", 1)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("5"))->append("row", 1)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("6"))->append("row", 1)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("1"))->append("row", 2)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("2"))->append("row", 2)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("3"))->append("row", 2)->append("col", 2))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("0"))->append("row", 3)->append("col", 0))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString(","))->append("row", 3)->append("col", 1))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("C"))->append("row", 3)->append("col", 2))));

    return buttons;

}


PVariant PActionButtons::numberPad5() {

    PVariant buttons = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("clean"))->append("row", 0)->append("col", 0)->append("icon", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("picons/core/actions/paintbrush.png"))->append("toolTip", QString("Clean")))))))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("-"))->append("row", 0)->append("col", 1)->append("icon", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("picons/core/actions/minus.png"))->append("hue", 30))))))));
    buttons << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("+"))->append("row", 0)->append("col", 2)->append("icon", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("picons/core/actions/new.png"))->append("hue", 50))))))));

    return buttons;

}
