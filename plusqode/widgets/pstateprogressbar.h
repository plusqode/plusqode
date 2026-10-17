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

#ifndef PSTATEPROGRESSBAR_H
#define PSTATEPROGRESSBAR_H

   #include <QWidget>
   #include <QGridLayout>
   #include <QFrame>

   #include "variant/pvariant.h"
   #include "widgets/ppushbutton.h"
   #include "widgets/pactionbutton.h"
   #include "misc/pimage.h"

class PModel ;

class PStateProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit PStateProgressBar(QWidget* parent = 0);
    void init(PVariant states);

signals:
    void changeCurrentState(PVariant newState);

public slots:
    void setCurrentState(const QString& newState);
    void onClick(PVariant actionItem);

public:
    QGridLayout* gridLayout;
    QGridLayout* stateGridLayout;
    QGridLayout* actionGridLayout;

    QString currentState;

    PModel* model;
    PVariant attrs;
    PVariant states;
    PVariant arcs;
    PVariant buttons;

};

Q_DECLARE_METATYPE(PPushButton*)
Q_DECLARE_METATYPE(PActionButton*)

#endif 



