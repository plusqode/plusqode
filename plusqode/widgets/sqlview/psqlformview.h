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

#ifndef PSQLFORMVIEW_H
#define PSQLFORMVIEW_H

   #include <QtWidgets/QDialog>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QLabel>
   #include <QtWidgets/QTabWidget>
   #include <QtWidgets/QLineEdit>
   #include <QtWidgets/QTextEdit>
   #include <QtWidgets/QPlainTextEdit>
   #include <QtWidgets/QDateEdit>
   #include <QtWidgets/QTimeEdit>
   #include <QtWidgets/QDateTimeEdit>
   #include <QtWidgets/QCheckBox>
   #include <QIntValidator>
   #include <QDoubleValidator>

   #include "sql/pmodel.h"
   #include "widgets/pmandatoryfield.h"
   #include "widgets/sqlview/psqlview.h"

class PSqlFormView : public PSqlView
{
    Q_OBJECT
public:
    explicit PSqlFormView(PModelPtr recordPtr,
                          QString mode,
                          PMandatoryField* mandatoryField,
                          PVariant viewAttrs,
                          QWidget* parent = 0);
    virtual PVariant data();
    virtual bool isEmpty();
    virtual PVariant idSelectionList();
    virtual PVariant selectedRows();
    virtual int count();

signals:

public slots:
    void setData(PVariant data);
    void setBackgroundColor(QString color);
    virtual void onEditingFinished();
    virtual void selectItem(int index);
    virtual void selectLastItem();
    void onChangeRecord(int row);
    void reload();

public:
    PModelPtr recordPtr;
    QString mode;
    PMandatoryField* mandatoryField;

    PVariant edits;

};


Q_DECLARE_METATYPE(QLineEdit*)

#endif 



