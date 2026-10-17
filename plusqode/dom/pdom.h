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

#ifndef PDOM_H
#define PDOM_H

   #include <QtCore/QMap>
   #include <QtCore/QList>

   #include "variant/pvariant.h"
   #include "core/plogger.h"

class PDom {

public:
    void init(const QString& tag, const QString& innerHTML);
    PDom(PVariant);
    PDom(const QString& tag, const QString& innerHTML);
    ~PDom();

    PDom* setParent(PDom* parent);
    PDom& operator<<(PDom* child);
    PDom& operator<<(QList<PDom*> children);
    QList<PDom*> getElementBy(const QString& attr, const QString& value, int searchType);
    PDom* setPlaceholder(const QString& placeholder, const QString& value);
    PDom* setPlaceholders(PVariant placeholders);
    QString replacePlaceHolder(const QString& value);
    QString html();
    QString openTag();
    QString closeTag();
    PDom* _set(QString attr, PVariant value, bool overwrite = false);
    PDom* set(PVariant);
    PDom* unset(const QString& attr);
    PDom* setStyle(PVariant);
    PDom* setStyles(PVariant styles);
    PDom* storeStyle();
    PDom* setCloseTag(bool = true);
    virtual QString toHtml();

    static QString inlinetag(PVariant);
    static QString htmltag(PVariant);

    QString tag;
    PVariant attrs;
    PVariant placeholders;
    PDom* parent;
    QList<PDom*> children;

    PVariant styles;
    bool enablePlaceholder; 


    QString innerHTML;

    bool ct; 

    int indentSpace;

};

#endif 



