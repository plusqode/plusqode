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

#ifndef PPUSHBUTTON_H
#define PPUSHBUTTON_H

   #include <QtWidgets/QPushButton>
   #include <QtWidgets/QMenu>
   #include <QtWidgets/QLayout>
   #include <QtWidgets/QLabel>
   #include <QFont>

   #include "core/pglobal.h"
   #include "variant/pvariant.h"
   #include "widgets/paction.h"

class PPushButton : public QPushButton {

    Q_OBJECT

public:
    explicit PPushButton(QWidget* parent = 0);
    void setPosStyle();
    void setTextAlignment(const QString& alignment);
    QString text();
    void setIcon(const QIcon& icon);
    void setIconSize(const QSize& size);

    void setText(const QString& text);
    void setTextSize(int size);

public slots:

public:
    QGridLayout* gridLayout;
    PVariant actionButton;
    QLabel* textLabel;
    QLabel* iconLabel;

};

#endif 



