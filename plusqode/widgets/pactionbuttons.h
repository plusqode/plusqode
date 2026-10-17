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

#ifndef PACTIONBUTTONS_H
#define PACTIONBUTTONS_H

   #include <QtWidgets/QWidget>
   #include <QtWidgets/QGridLayout>

   #include "variant/pvariant.h"
   #include "widgets/pactionbutton.h"

class PActionButtons : public QWidget
{
    Q_OBJECT

public:
    explicit PActionButtons(QWidget *parent = 0);
    PVariant toVariant(PVariant variantView);
    QWidget* initByVariant(PVariant root);
    QWidget* initByXml(PVariant parentView);
    static void setButtonSize(PVariant buttons, int width, int height);
    static void setFontSize(PVariant buttons, int fontSize);
    PVariant numberPad1();
    PVariant numberPad2();
    PVariant numberPad3();
    PVariant numberPad4();
    PVariant numberPad5();

signals:
    void click(PVariant button);

public slots:
    void onClick(PVariant button);

public:
    QGridLayout* gridLayout;

};

#endif 



