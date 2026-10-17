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



   #include "widgets/pmandatoryfield.h"

   
   

PMandatoryField::PMandatoryField(QObject* parent) :
    QObject(parent),
    okButton(0) {

    color = PGlobal::mandatoryFieldColor();

}

void PMandatoryField::add(PFieldWidget *fieldWidget) {

    if (!fieldWidgetList.contains(fieldWidget))
        connect(fieldWidget, SIGNAL(editingFinished(QString,PVariant)), this, SLOT(changed()));

    fieldWidgetList.append(fieldWidget);
    changed();

}


void PMandatoryField::remove(PFieldWidget* fieldWidget) {


    fieldWidgetList.removeAll(fieldWidget);


}

void PMandatoryField::setOkButton(QPushButton *button) {

    if(okButton)
        okButton->setEnabled(false);
    okButton = button;
    changed();

}


void PMandatoryField::changed() {

    if (!okButton)
        return;

    bool enable = true;
    QList<PFieldWidget*>::const_iterator i;
    for (i = fieldWidgetList.begin(); i != fieldWidgetList.end(); ++i) {
        PFieldWidget* fieldWidget = *i;
        if (fieldWidget->isEmpty()) {
            fieldWidget->setBackgroundColor(color);
            enable = false;
        }
        else
            fieldWidget->setBackgroundColor("white");
    }

    okButton->setEnabled(enable);

}
