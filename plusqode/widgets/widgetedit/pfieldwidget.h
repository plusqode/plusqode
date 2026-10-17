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

#ifndef PFIELDWIDGET_H
#define PFIELDWIDGET_H

   #include <QtWidgets/QWidget>
   #include <QtCore/QString>

   #include "variant/pvariant.h"
   #include "core/pglobal.h"
   #include "widgets/ppwidget.h"

class PFieldWidget : public PWidget {

    Q_OBJECT
public:
    explicit PFieldWidget(QWidget* parent = 0);
    virtual bool isEmpty() = 0;
    virtual PVariant data() = 0;
    virtual QWidget* mainWidget();

signals:
    void dataChanged(QString fieldName, PVariant data);
    void editingFinished(QString fieldName, PVariant data);

public slots:
    virtual void setData(PVariant data) = 0;
    virtual void setBackgroundColor(QString color) = 0;
    virtual void setReadOnly(bool = true) {};
    virtual void setAttrs(PVariant attrs);
    void setEnabled(bool = true);

public:
    QString fieldName;
    PVariant attrs;

};

Q_DECLARE_METATYPE(PFieldWidget*)

#endif 



