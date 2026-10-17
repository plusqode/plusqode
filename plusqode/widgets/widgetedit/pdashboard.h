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

#ifndef PDASHBOARD_H
#define PDASHBOARD_H

   #include <QtCore/QVariant>
   #include <QtWidgets/QWidget>
   #include <QtWidgets/QLabel>
   #include <QtWidgets/QGridLayout>
   #include <QPen>
   #include <QPainter>
   #include <QPainterPath>

   #include "widgets/widgetedit/pfieldwidget.h"
   #include "misc/pmath.h"
   #include "misc/pimage.h"


class PDashboard : public PFieldWidget
{
    Q_OBJECT
public:
    explicit PDashboard(QWidget *parent = 0);
    PVariant data();
    bool isEmpty();
    void showEvent(QShowEvent* event);
    void paintEvent(QPaintEvent* event);

    void initBySizeRate(int sizeRate);

    void initByDegrees(int degrees);
    void initByPercentage(int percentage);
    void initByValue(int value, int max);


signals:

public slots:
    void setAttrs(PVariant);
    void setData(PVariant data);
    void setBackgroundColor(QString color);

public:
    QPixmap pixmap;
    QLabel* dashboard;
    QLabel* label;
    int sizeRate, radius, x, y, hue, saturation, fontSize, circleSize;
    QString fontFamily;
    QString style;

};

#endif 



