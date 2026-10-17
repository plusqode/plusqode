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

#ifndef PSQLTEXTCOMBOBOX_H
#define PSQLTEXTCOMBOBOX_H

   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QComboBox>
   #include <QtWidgets/QToolButton>

   #include "sql/pmodel.h"
   #include "widgets/widgetedit/pfieldwidget.h"
   #include "widgets/sqlview/psqlformviewdialog.h"

class PSqlFormView;
class PModel ;

class PSqlTextComboBox : public PFieldWidget {

    Q_OBJECT
public:
    PSqlTextComboBox(PVariant);
    ~PSqlTextComboBox();
    virtual QWidget* mainWidget();
    PVariant data();
    bool isEmpty();

signals:

public slots:
    void setData(PVariant data);
    void setBackgroundColor(QString color);
    virtual void setReadOnly(bool = true);
    void textChanged(int);
    void onEditingFinished(int);
    void onEditingFinished_QString(QString);
    QString showFieldValue(PModelPtr model);
    void populateList();
    void applyFilter(PVariant fieldAttrs);

    void onNew();
    void onEdit();


private:
    QComboBox* comboBox;
    QToolButton* newButton;
    QToolButton* editButton;
    bool comboBoxLock;

    PModelPtr model;
    PVariant fieldAttrs;
    PVariant showField;
    PVariant sortField;
    QString label;
    int selectedItemId;
    int dialogLevel;

};

#endif 



