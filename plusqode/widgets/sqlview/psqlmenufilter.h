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

#ifndef PSQLMENUFILTER_H
#define PSQLMENUFILTER_H

   #include <QtWidgets/QWidget>
   #include <QtWidgets/QLineEdit>
   #include <QtWidgets/QComboBox>

   #include "variant/pvariant.h"
   #include "sql/pmodel.h"
   #include "widgets/widgetedit/pcheckboxedit.h"
   #include "widgets/pactionbutton.h"

class PSqlMenuFilter : public QWidget
{
    Q_OBJECT
public:
    explicit PSqlMenuFilter(PVariant);

signals:
    void clickNewButton();
    void clickDeleteButton(PSqlMenuFilter*);
    void changeFilter(PSqlMenuFilter*);

public slots:
    void onClick(PVariant actionItem);
    void onEditingFinished();
    void clear();
    void onClickNewButton();
    void onClickDeleteButton();

public:
    QString modelName;
    QGridLayout* gridLayout;
    PVariant filters;
    PVariant globalFilter;

    QLineEdit* lineEdit;
    QComboBox* comboBox;
    PActionButton* actionButton;

    PVariant lastActionItem;

    QString fieldName;
    QString op;
    QString fieldValue;

};

Q_DECLARE_METATYPE(PSqlMenuFilter*);

#endif 



