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

#ifndef PSWITCHEDIT_H
#define PSWITCHEDIT_H

   #include "widgets/widgetedit/pfieldwidget.h"
   #include "misc/pmath.h"

   #include <QtCore/QVariant>
   #include <QtWidgets/QWidget>
   #include <QtWidgets/QLabel>
   #include <QtWidgets/QGridLayout>
   #include <QPen>
   #include <QPainter>
   #include <QPainterPath>

class PSwitchEdit : public PFieldWidget
{
    Q_OBJECT
public:
    explicit PSwitchEdit(QWidget *parent = 0);
    PVariant data();
    bool isEmpty();
    void mousePressEvent(QMouseEvent* event);
    void showEvent(QShowEvent* event);
    void paintEvent(QPaintEvent* event);


signals:

public slots:
    void setAttrs(PVariant);
    void setData(PVariant data);
    void setBackgroundColor(QString color);
    virtual void setReadOnly(bool = true);
    void onEditingFinished();

public:
    bool state;
    QColor color;
    QString style;
    bool readOnly;

};

#endif 



