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



   #include "widgets/ptablewidget.h"

   
   

PTableWidget::PTableWidget(QWidget* parent) : QTableWidget(parent) {


}

void PTableWidget::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {

    QTableWidget::selectionChanged(selected, deselected);

    QModelIndexList selectedRowsList = selected.indexes();

    if(selectedRowsList.count() == 0)
        return;

    if(selectedRowsList[0].data(Qt::UserRole) == "noSelect")
        this->selectionModel()->select(selected, QItemSelectionModel::Deselect);

}


void PTableWidget::setNoSelectRow(int row) {

    for(int col = 0; col < this->columnCount(); col++)
        this->item(row, col)->setData(Qt::UserRole, "noSelect");

}

void PTableWidget::setBackgroundRow(int row) {

    for(int col = 0; col < this->columnCount(); col++) {
        QTableWidgetItem* item = this->item(row, col);
        item->setBackground(QBrush(Qt::lightGray, Qt::Dense1Pattern));
        item->setFont(QFont("Arial", 10, QFont::Bold));
    }

}

void PTableWidget::swapRows(int row1, int row2) {

    for(int i = 0; i < this->columnCount(); i++) {
        QTableWidgetItem* item1 = this->takeItem(row1, i);
        QTableWidgetItem* item2 = this->takeItem(row2, i);
        this->setItem(row1, i, item2);
        this->setItem(row2, i, item1);
    }

}
