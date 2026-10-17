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

#ifndef PSQLGROUPTABLEVIEW_H
#define PSQLGROUPTABLEVIEW_H

   #include "widgets/sqlview/psqltableview.h"

class PSqlGroupTableView : public PSqlTableView {

    Q_OBJECT
public:
    explicit PSqlGroupTableView(PVariant);
    ~PSqlGroupTableView();
    QList<QTreeWidgetItem*> sqlTotalizerFields(PVariant groupBy, PVariant filter = nil);
    PVariant groupByFieldName(PVariant);

signals:

public slots:
    void resizeColumnsToContents();
    void onGroupChanged(PVariant groupBy);
    void reload();

public:

};

#endif 



