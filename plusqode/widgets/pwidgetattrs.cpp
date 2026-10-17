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





   #include "widgets/pwidgetattrs.h"



   


   

Qt::Alignment PWidgetAttrs::alignmentFromString(const QString& alignment) {

    if(!alignment.isNull()) {
        if(alignment.toLower() == "left")
            return Qt::AlignLeft | Qt::AlignVCenter;
        else if(alignment.toLower() == "right")
            return Qt::AlignRight | Qt::AlignVCenter;
        else if(alignment.toLower() == "center")
            return Qt::AlignCenter | Qt::AlignVCenter;
    }

    return Qt::AlignLeft | Qt::AlignVCenter;

}


void PWidgetAttrs::setLayout(QLayout* layout, PVariant attrs) {

    if(attrs. undefined("margins", nil)!= nil) {
        int m = attrs.undefined("margins", nil).toInt();
        layout->setContentsMargins(m,m,m,m);
    }
    else
        layout->setContentsMargins(0,0,0,0);

    if(attrs. undefined("spacing", nil)!= nil)
        layout->setSpacing(attrs.undefined("spacing", nil).toInt());

    if(attrs. undefined("alignment", nil)!= nil)
        layout->setAlignment(PWidgetAttrs::alignmentFromString(attrs.undefined("alignment", nil).toString()));

}


void PWidgetAttrs::setBackgroundColor(QWidget* widget, const QString& color) {

    QPalette pal(widget->palette());
    pal.setColor(QPalette::Window, color);
    widget->setPalette(pal);
    widget->setAutoFillBackground(true);

}

void PWidgetAttrs::setWidget(QWidget* widget, PVariant attrs) {

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QDesktopWidget screen;
    QSize resolution = screen.screenGeometry(0).size();
#else
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize resolution = screen->size();
#endif

    if(attrs. undefined("minimumWidth", nil)!= nil) {
        int screenWidth = resolution.width();
        QString minimumWidth = attrs.undefined("minimumWidth", nil).toString();
        if(minimumWidth.endsWith("%")) {
            minimumWidth.chop(1);
            int w = screenWidth * minimumWidth.toInt() / 100;
            widget->setMinimumWidth(w);
        }
        else
            widget->setMinimumWidth(minimumWidth.toInt());
    }

    if(attrs. undefined("maximumWidth", nil)!= nil) {
        int screenWidth = resolution.width();
        QString maximumWidth = attrs.undefined("maximumWidth", nil).toString();
        if(maximumWidth.endsWith("%")) {
            maximumWidth.chop(1);
            int w = screenWidth * maximumWidth.toInt() / 100;
            widget->setMaximumWidth(w);
        }
        else
            widget->setMaximumWidth(maximumWidth.toInt());
    }


    if(attrs. undefined("minimumHeight", nil)!= nil) {
        int screenHeight = resolution.height();
        QString minimumHeight = attrs.undefined("minimumHeight", nil).toString();
        if(minimumHeight.endsWith("%")) {
            minimumHeight.chop(1);
            int h = screenHeight * minimumHeight.toInt() / 100;
            widget->setMinimumHeight(h);
        }
        else
            widget->setMinimumHeight(minimumHeight.toInt());
    }

    if(attrs. undefined("maximumHeight", nil)!= nil) {
        int screenHeight = resolution.height();
        QString maximumHeight = attrs.undefined("maximumHeight", nil).toString();
        if(maximumHeight.endsWith("%")) {
            maximumHeight.chop(1);
            int h = screenHeight * maximumHeight.toInt() / 100;
            widget->setMaximumHeight(h);
        }
        else
            widget->setMaximumHeight(maximumHeight.toInt());
    }

}
