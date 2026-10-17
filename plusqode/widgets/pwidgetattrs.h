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

#ifndef PWIDGETATTRS_H
#define PWIDGETATTRS_H

   #include <QtWidgets/QWidget>
   #include <QtWidgets/QLayout>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
       #include <QtWidgets/QDesktopWidget>
#else
       #include <QGuiApplication>
       #include <QScreen>
#endif

   #include "variant/pvariant.h"

class PWidgetAttrs
{
public:
    static void setBackgroundColor(QWidget* widget, const QString& color);
    static void setWidget(QWidget* widget, PVariant attrs);
    static void setLayout(QLayout* layout, PVariant attrs);
    static Qt::Alignment alignmentFromString(const QString& alignment);
};

#endif 



