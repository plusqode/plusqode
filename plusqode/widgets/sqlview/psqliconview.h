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

#ifndef PSQLICONVIEW_H
#define PSQLICONVIEW_H

   #include <QtWidgets/QListWidget>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QTableWidgetItem>
   #include <QtWidgets/QHeaderView>

   #include "sql/pmodel.h"
   #include "misc/pimage.h"
   #include "widgets/sqlview/psqlview.h"
   #include "widgets/pactionbuttons.h"
   #include "widgets/sqlview/psqlformview.h"

class PSqlIconView : public PSqlView
{
    Q_OBJECT

public:
    explicit PSqlIconView(PVariant);
    ~PSqlIconView();
    PVariant idSelectionList();
    PVariant selectedRows();
    int count();
    virtual PVariant data();
    virtual bool isEmpty();

signals:

public slots:
    void itemSelectionChanged();
    void selectItem(int index);
    void selectItemById(QString id);
    void selectLastItem();
    void onDoubleClicked(QListWidgetItem*);
    void setWidgetItem(QListWidgetItem* widgetItem);
    void reload();
    virtual void reloadCurrentRecord();

    void setData(PVariant data);
    void setBackgroundColor(QString color);
    virtual void onEditingFinished();


public:

    QListWidget* listWidget;

    QString modelName;

    PModelPtr model;

    PVariant sortField;

};

#endif 



