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

#ifndef PCOMBOBOXPLUS_H
#define PCOMBOBOXPLUS_H

   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QComboBox>
   #include <QtWidgets/QLineEdit>

   #include "widgets/widgetedit/pfieldwidget.h"
   #include "widgets/pactionbutton.h"



class PComboBoxPlus : public PFieldWidget {

    Q_OBJECT
public:
    PComboBoxPlus(PVariant itemsAndValues, QWidget* widget = 0);
    virtual QWidget* mainWidget();
    PVariant convert(PVariant itemsAndValues);
    PVariant data();
    bool isEmpty();
    QString currentText();

public slots:
    void setData(PVariant data);
    void setBackgroundColor(QString color);
    virtual void setReadOnly(bool = true);
    void textChanged(QString text);
    void onEditingFinished(PVariant);
    void populateList();

public:
    PActionButton* actionButton;
    PVariant itemsAndValues;
    PVariant linearItemsAndValues;
    QString currentData;

};

#endif 



