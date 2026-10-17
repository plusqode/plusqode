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

#ifndef PSQLPAGINATION_H
#define PSQLPAGINATION_H

   #include <QtWidgets/QWidget>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QLabel>
   #include <QtWidgets/QLineEdit>
   #include <QtWidgets/QComboBox>
   #include <QtWidgets/QPushButton>
   #include "variant/pvariant.h"
   #include "sql/pmodel.h"

class PSqlPagination : public QWidget
{
    Q_OBJECT
public:
    explicit PSqlPagination(PVariant);

signals:
    void currentPageChanged(int currentPage);
    void pageSizeChanged(QString pageSize);

public slots:
    void rowsAndPages();
    void onCurrentPageChanged();
    void onPageSizeChanged(int);
    void onPrevPage();
    void onNextPage();

public:
    PModelPtr modelPtr;
    int currentPage;
    QString pageSize;
    PVariant rowsForPage;

    QLineEdit* currentPageLineEdit;
    QComboBox* pageSizeComboBox;
    QLabel* ofRowsLabel;
    QLabel* ofPagesLabel;

    PVariant rows;
    PVariant pages;

};

#endif 



