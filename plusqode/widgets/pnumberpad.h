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

#ifndef PNUMBERPAD_H
#define PNUMBERPAD_H

   #include <QtWidgets/QDialog>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QLabel>

   #include "widgets/pactionbuttons.h"
   #include "variant/pvariant.h"

class PNumberPad : public QDialog {

    Q_OBJECT

public:
    explicit PNumberPad(QWidget* parent = 0);
    ~PNumberPad();

signals:

public slots:
    void numberPad_onClick(PVariant button);
    void setValue(QString value);
    double getValue();

public:
    QGridLayout* buttonGridLayout;
    QLabel* display;
    PActionButtons* actionButtons;

    QString value;

};

#endif 



