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

#ifndef PPROGRESSBARPLUS_H
#define PPROGRESSBARPLUS_H

   #include <QtCore/QVariant>
   #include <QtWidgets/QWidget>
   #include <QtWidgets/QLabel>
   #include <QtWidgets/QGridLayout>
   #include <QPen>
   #include <QPainter>
   #include <QPainterPath>

   #include "widgets/widgetedit/pfieldwidget.h"
   #include "misc/pmath.h"


class PProgressBarPlus : public PFieldWidget
{
    Q_OBJECT
public:
    explicit PProgressBarPlus(QWidget *parent = 0);
    ~PProgressBarPlus();
    virtual QWidget* mainWidget();
    PVariant data();
    bool isEmpty();
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);

    void initPixmap();
    void initByValue(int value, int max);

signals:

public slots:
    void setAttrs(PVariant);
    void setData(PVariant data);
    void setBackgroundColor(QString color);

    void setRange(int minimum, int maximum);
    void setValue(int value);

public:
    QString style;
    QString currentValue;
    QPixmap pixmap;
    QLabel* progressBar;
    QLabel* label;
    int hue, max;
    QString barType;
    PVariant colors;

};

#endif 




