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

#ifndef PSQLTABVIEW_H
#define PSQLTABVIEW_H

   #include <QtWidgets/QTabWidget>
   #include <QtWidgets/QGridLayout>

   #include "sql/pmodel.h"
   #include "widgets/sqlview/psqlview.h"
   #include "widgets/sqlview/psqliconview.h"
   #include "widgets/sqlview/psqlgrouptableview.h"
   #include "widgets/ptabwidget.h"

class PSqlTabView : public PSqlView
{
    Q_OBJECT
public:
    explicit PSqlTabView(PVariant);
    ~PSqlTabView();
    void init(PVariant);
    void initSubModelFromView();

    virtual PVariant idSelectionList();
    virtual PVariant selectedRows();
    virtual int count();
    virtual PVariant data();
    virtual bool isEmpty();

signals:

public slots:
    virtual void itemSelectionChanged();
    virtual void selectItem(int index);
    virtual void selectLastItem();
    virtual void onDoubleClicked();
    virtual void reload();

    virtual void setData(PVariant data);
    virtual void setBackgroundColor(QString color);
    virtual void onEditingFinished();

public:

    PTabWidget* tabWidget;

    QString modelName;

    QString subModelName;

    QString subViewType;

    PModelPtr model;

    PVariant sortField;

    bool showControlPanel;

};

#endif 



