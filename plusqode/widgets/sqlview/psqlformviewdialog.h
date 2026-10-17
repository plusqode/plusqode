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

#ifndef PSQLFORMVIEWDIALOG_H
#define PSQLFORMVIEWDIALOG_H

   #include <QDialog>
   #include <QtWidgets/QDialogButtonBox>

   #include "widgets/pmandatoryfield.h"
   #include "widgets/sqlview/psqlformview.h"

class PSqlFormView;
class PSqlFormViewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PSqlFormViewDialog(PModelPtr recordPtr,
                                QString mode,
                                PVariant viewAttrs = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("form"))))),
                                QWidget* parent = 0);

signals:

public slots:

    void accept();
    void reject();
    void showFullScreen();

public:
    PSqlFormView* sqlFormView;
    QPushButton* okButton;
    QPushButton* cancelButton;

};

#endif 



