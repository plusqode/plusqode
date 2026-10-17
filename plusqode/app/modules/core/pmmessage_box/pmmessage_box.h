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

#ifndef PMMESSAGEBOX_H
#define PMMESSAGEBOX_H

#include <QLabel>
#include <QGridLayout>

#include "sql/pmodel.h"
#include "widgets/sqlview/psqlformviewdialog.h"

class PMMessageBox : public PModel
{
    Q_OBJECT
public:
    PMMessageBox(PVariant);
    PMMessageBox& init(PVariant);

public slots:
    void onAfterWidget();
    void setText(const QString& text);
    void setPixmap(const QString& iconFile);
    bool onOkDialog();
    bool onWrite();
    static int messageBox(PVariant message);

public:

};

Q_DECLARE_METATYPE(PMMessageBox*)

#endif // PMMESSAGEBOX_H
