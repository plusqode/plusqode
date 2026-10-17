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

#ifndef PLINEEDIT_H
#define PLINEEDIT_H

   #include <QtCore/QVariant>
   #include <QtWidgets/QWidget>
   #include <QtWidgets/QLineEdit>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QLabel>

   #include "widgets/widgetedit/pfieldwidget.h"
   #include "misc/popenurl.h"


class PLineEdit : public PFieldWidget
{
    Q_OBJECT
public:
    explicit PLineEdit(QWidget *parent = 0);
    virtual QWidget* mainWidget();
    virtual PVariant data();
    virtual bool isEmpty();

signals:

public slots:
    virtual void setData(PVariant data);
    virtual void setBackgroundColor(QString color);
    virtual void setReadOnly(bool = true);
    void textChanged(QString text);
    void onEditingFinished();
    void setAttrs(PVariant);

public:
    QGridLayout *layout;
    QLineEdit* lineEdit;

};

#endif 



