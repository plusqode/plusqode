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

#ifndef PMAINVIEW_H
#define PMAINVIEW_H

   #include <QWidget>
   #include <QLabel>
   #include <QTextEdit>
   #include <QCoreApplication>

   #include "widgets/pactionbutton.h"
   #include "misc/popenurl.h"
   #include "app/modules/core/pmuser_authentication/pmuser_authentication.h"

class PMainView : public QWidget
{
    Q_OBJECT
public:
    explicit PMainView(PVariant& module, QWidget *parent = 0);

signals:

public slots:
    void authentication();
    void quit();

};

#endif 



