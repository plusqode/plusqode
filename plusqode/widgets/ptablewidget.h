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

#ifndef PTABLEWIDGET_H
#define PTABLEWIDGET_H

   #include <QTableWidget>

class PTableWidget : public QTableWidget {

    Q_OBJECT

public:
    explicit PTableWidget(QWidget* parent = 0);
    void setNoSelectRow(int row);
    void setBackgroundRow(int row);
    void swapRows(int row1, int row2);

signals:

public slots:
    virtual void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

};

#endif 



