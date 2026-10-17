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

#ifndef PVIRTUALKEYBOARD_H
#define PVIRTUALKEYBOARD_H

   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QDialog>
   #include <QIcon>
   #include <QDoubleValidator>
   #include <QtWidgets/QPushButton>
   #include <QtWidgets/QLineEdit>
   #include <QtWidgets/QDialogButtonBox>

   #include "core/plogger.h"
   #include "widgets/pactionbuttons.h"

class PVirtualKeyboard : public QDialog
{
    Q_OBJECT
public:
    explicit PVirtualKeyboard(QWidget* parent = 0);
    void init();

signals:

public slots:
    void keyboardOnClick(PVariant);
    void accept();
    void reject();

public:
    QGridLayout* gridLayout;
    QLineEdit* lineEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;

};

#endif 



