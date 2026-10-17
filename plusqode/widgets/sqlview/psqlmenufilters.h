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

#ifndef PSQLMENUFILTERS_H
#define PSQLMENUFILTERS_H

   #include <QtWidgets/QWidget>

   #include "variant/pvariant.h"
   #include "widgets/sqlview/psqlmenufilter.h"

class PSqlMenuFilters : public QWidget
{
    Q_OBJECT
public:
    explicit PSqlMenuFilters(PVariant);
    PVariant getFilter();

signals:
    void changeFilter(PVariant);

public slots:
    void removeSqlFilter(PSqlMenuFilter* sqlMenuFilter);
    void setConditionLabel(PVariant filter);
    void setAllOperators(QString op);
    void onChangeFilter(PSqlMenuFilter*);
    void onClickNewButton();
    void onClickDeleteButton(PSqlMenuFilter*);


public:
    QString modelName;
    QGridLayout* gridLayout;
    QLabel* conditionLabel;
    QList<PSqlMenuFilter*> sqlMenuFilters;
    PVariant globalFilter;

};

#endif 



