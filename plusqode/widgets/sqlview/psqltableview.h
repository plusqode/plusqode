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

#ifndef PSQLTABLEVIEW_H
#define PSQLTABLEVIEW_H

   #include <QtWidgets/QTableWidget>
   #include <QtWidgets/QTreeWidget>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QTableWidgetItem>
   #include <QtWidgets/QHeaderView>
   #include <QtWidgets/QToolButton>

   #include "sql/pmodel.h"
   #include "widgets/sqlview/psqlview.h"
   #include "widgets/ptablewidget.h"
   #include "widgets/pactionbuttons.h"
   #include "widgets/sqlview/psqlpagination.h"
   #include "widgets/sqlview/psqlgrouppanel.h"
   #include "widgets/sqlview/psqlfilterpanel.h"
   #include "widgets/sqlview/psqlmenufilters.h"
   #include "widgets/sqlview/psqlformview.h"

class PSqlTableView : public PSqlView
{
    Q_OBJECT

public:
    explicit PSqlTableView() {}
    explicit PSqlTableView(PVariant);
    void init(PVariant);
    void initTreeWidget();
    ~PSqlTableView();
    virtual PVariant idSelectionList();
    virtual PVariant selectedRows();
    virtual int count();
    virtual PVariant data();
    virtual bool isEmpty();
    virtual void swapItems(int item1, int item2);

signals:

public slots:
    void itemSelectionChanged();
    virtual void selectItem(int row);
    virtual void selectLastItem();
    virtual void selectItemById(QString id);
    virtual void reloadCurrentRecord();
    virtual void addCurrentRecord(int row = -1);
    virtual bool removeItem(int row);
    void onDoubleClicked(int, int);
    void onDoubleClicled(QTreeWidgetItem* item, int column);
    void onSortIndicatorChanged(int logicalIndex, Qt::SortOrder order);
    void initTotalizerFields();
    void hideOrShow();
    void setAlignmentTableWidgetItem(QTableWidgetItem* widgetItem, QString type, QString alignment);
    void reload();
    void reloadTotalizers();

    void setData(PVariant data);
    void setBackgroundColor(QString color);
    virtual void onEditingFinished();
    void hideOrShowFilterPanel();


public:

    QGridLayout* gridLayout;

    PTableWidget* tableWidget;

    QTreeWidget* treeWidget;

    PSqlPagination* sqlPagination;

    PSqlFilterPanel* sqlFilterPanel;

    PSqlGroupPanel* sqlGroupPanel;

    PSqlMenuFilters* sqlMenuFilters;

    QString moduleName;

    QString modelName;

    PVariant filter;

    PModelPtr model;

    PVariant sortField;

    PVariant fields;

    PVariant totalizerFields;

    PVariant totalizers;

    bool showFilterPanel;

    QWidget* filterPanel;

    QToolButton* hideButton;

};

#endif 



