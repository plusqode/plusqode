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

#ifndef PXMLWIDGET_H
#define PXMLWIDGET_H

   #include <QtCore/QVariant>
   #include <QtWidgets/QWidget>
   #include <QtWidgets/QLabel>
   #include <QtWidgets/QGridLayout>

   #include "widgets/widgetedit/pfieldwidget.h"
   #include "core/pview.h"
   #include "sql/pmodel.h"

class PModel ;

class PXmlWidget : public PFieldWidget
{
    Q_OBJECT
public:
    explicit PXmlWidget(PModel* model, PMandatoryField* mandatoryField, QString mode, PVariant fieldAttrs, QWidget *parent = 0);
    PVariant data();
    bool isEmpty();


signals:

public slots:
    void setData(PVariant data);
    void setBackgroundColor(QString color);

public:

};

#endif 



