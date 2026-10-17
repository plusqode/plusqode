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

#ifndef PFIELDSELECTOR_H
#define PFIELDSELECTOR_H

   #include <QDialog>
   #include <QPushButton>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QLabel>
   #include <QtWidgets/QDialogButtonBox>
   #include <QtWidgets/QListWidget>

   #include "variant/pvariant.h"
   #include "sql/pmodel.h"
   #include "widgets/pactionbutton.h"

class PModel ;
class PFieldSelector : public QDialog
{
    Q_OBJECT
public:
    explicit PFieldSelector(QWidget* parent = 0);
    void initListWidget(PModel* model);
    PVariant selectedFields();

signals:

public slots:
    void onClick(PVariant fieldName);

private:
    QGridLayout* gridLayout;
    QLabel* label;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QListWidget* listWidget;
    PActionButton* actionButton;

};

#endif 



