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

#ifndef PDIRECTORYDIALOGEDIT_H
#define PDIRECTORYDIALOGEDIT_H

   #include <QtCore/QVariant>
   #include <QtCore/QString>
   #include <QtWidgets/QToolButton>
   #include <QtWidgets/QLineEdit>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QWidget>
   #include <QtWidgets/QFileDialog>
   #include <QtWidgets/QGridLayout>

   #include "widgets/widgetedit/pfieldwidget.h"

class PDirectoryDialogEdit : public PFieldWidget
{
    Q_OBJECT

public:
    explicit PDirectoryDialogEdit(QWidget *parent = 0);
    virtual QWidget* mainWidget();
    PVariant data();
    bool isEmpty();

public slots:
    void setData(PVariant data);
    void setBackgroundColor(QString color);
    virtual void setReadOnly(bool = true);
    void textChanged(QString text);
    QString selectionFile();
    void onEditingFinished();

private:
    QLineEdit* lineEdit;
    QToolButton* toolButton;

};

#endif 



