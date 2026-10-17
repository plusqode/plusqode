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

#ifndef PACTIONBUTTON_H
#define PACTIONBUTTON_H

   #include <QtWidgets/QMenu>

   #include "variant/pvariant.h"
   #include "widgets/paction.h"
   #include "widgets/ppushbutton.h"
   #include "widgets/pwidgetattrs.h"
   #include "misc/pimage.h"
   #include "misc/pusermanager.h"

class PActionButton : public PPushButton {

    Q_OBJECT

public:
    explicit PActionButton(PVariant actionButton, QWidget* parent = 0);
    ~PActionButton();
    QMenu* initMenu(PVariant actionItems, QString menuTitle = "");

signals:
    void click(PVariant actionButton);
    void click(PActionButton*);

public slots:
    void onClick();
    void onClick(PVariant actionItem);

public:
    PVariant actionButton;
    PAction* action;

};

#endif 



