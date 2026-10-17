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

#ifndef PSQLBUTTONVIEW_H
#define PSQLBUTTONVIEW_H

   #include <QtWidgets/QTableWidget>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QScrollArea>
   #include <QtWidgets/QTableWidgetItem>
   #include <QtWidgets/QHeaderView>

   #include "sql/pmodel.h"
   #include "widgets/widgetedit/pfieldwidget.h"
   #include "widgets/pactionbuttons.h"
   #include "widgets/sqlview/psqlformview.h"

class PSqlButtonView : public PFieldWidget
{
    Q_OBJECT

public:
    explicit PSqlButtonView(PVariant);
    ~PSqlButtonView();
    PVariant idSelectionList();
    virtual PVariant data();
    virtual bool isEmpty();
    void initGeometry();
    void showEvent(QShowEvent* event);
    void paintEvent(QPaintEvent*);
    PVariant dbTableToVariant(PModelPtr modelPtrRoot);

signals:
    void click(PVariant);

public slots:
    void onClick(PVariant);
    void onDoubleClicked(int, int);
    void reload();

    void setData(PVariant data);
    void setBackgroundColor(QString color);

    void clear();
    void applyFilter(PVariant filter);

public:

    QGridLayout* buttonGridLayout;

    QWidget* buttonWidget;

    QScrollArea* scrollArea;

    QString modelName;

    PModelPtr model;

    PVariant sortField;

    int rows, cols, btnHeight, btnWidth;

    QString alignment;

    PVariant buttons;

    QList<PActionButton*> buttonList;

};

#endif 



