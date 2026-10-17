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

#ifndef PSQLVIEW_H
#define PSQLVIEW_H

   #include "widgets/widgetedit/pfieldwidget.h"

class PSqlView : public PFieldWidget {

    Q_OBJECT
public:
    explicit PSqlView(QWidget* parent = 0);
    virtual PVariant idSelectionList() = 0;
    virtual PVariant selectedRows() = 0;
    virtual int count() = 0;
    virtual void swapItems(int item1, int item2) { }

signals:

public slots:
    virtual void onEditingFinished() = 0;
    virtual void selectItem(int index) = 0;
    virtual void selectLastItem() = 0;
    virtual void selectItemById(QString id) { }
    virtual void reloadCurrentRecord() { }
    virtual void addCurrentRecord(int row = -1) {}
    virtual bool removeItem(int row) { return false; }
    virtual void reload() = 0;


public:

};

Q_DECLARE_METATYPE(PSqlView*)

#endif 



