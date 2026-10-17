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

#ifndef PSTATEPROGRESSBAREDIT_H
#define PSTATEPROGRESSBAREDIT_H

   #include <QtWidgets/QWidget>

   #include <QtCore/QVariant>
   #include "widgets/widgetedit/pfieldwidget.h"
   #include "widgets/pstateprogressbar.h"

class PStateProgressBarEdit : public PFieldWidget
{
    Q_OBJECT
public:
    explicit PStateProgressBarEdit(QWidget* parent = 0);
    void setAttrs(PVariant);
    virtual QWidget* mainWidget();
    PVariant data();
    bool isEmpty();

signals:

public slots:
    void setData(PVariant data);
    void setBackgroundColor(QString color);
    virtual void setReadOnly(bool = true);
    void stateChanged(int state);
    void onEditingFinished();

public:
    PStateProgressBar* stateProgressBar;

};

#endif 



