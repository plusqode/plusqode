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

#ifndef PMANDATORYFIELD_H
#define PMANDATORYFIELD_H

   #include <QtCore/QObject>
   #include <QtCore/QList>
   #include <QtCore/QDebug>
   #include <QtWidgets/QPushButton>
   #include <QtWidgets/QCheckBox>
   #include <QtWidgets/QLineEdit>
   #include <QtWidgets/QComboBox>
   #include <QtWidgets/QTextEdit>

   #include "widgets/widgetedit/pfieldwidget.h"

using namespace std;


class PMandatoryField : public QObject
{
    Q_OBJECT
public:
    explicit PMandatoryField(QObject *parent = 0);
    void add(PFieldWidget* fieldWidget);
    void remove(PFieldWidget* fieldWidget);
    void setOkButton(QPushButton *button);

signals:

public slots:
    void changed();

private:
   QPushButton *okButton;
   QList<PFieldWidget*> fieldWidgetList;
   QString color;

};


#endif 



