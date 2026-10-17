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

#ifndef PDATETIMEEDIT_H
#define PDATETIMEEDIT_H

   #include <QtWidgets/QDateTimeEdit>
   #include <QtWidgets/QGridLayout>
   #include <QtCore/QVariant>

   #include "widgets/widgetedit/pfieldwidget.h"

class PDateTimeEdit : public PFieldWidget
{
    Q_OBJECT

public:
    PDateTimeEdit(QWidget *parent = 0);
    virtual QWidget* mainWidget();
    PVariant data();
    bool isEmpty();

public slots:
    void setData(PVariant data);
    void setBackgroundColor(QString color);
    virtual void setReadOnly(bool = true);
    void dateTimeChanged(QDateTime date);
    void onEditingFinished();

private:
    QDateTimeEdit* dateTimeEdit;

};

#endif 



