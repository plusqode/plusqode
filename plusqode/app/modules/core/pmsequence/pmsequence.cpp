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

#include "app/modules/core/pmsequence/pmsequence.h"
#include "app/modules/pmodules.h"

PMSequence::$PMSequence() {

    init(args);

}

PMSequence& PMSequence::init(PVariant args) {

    PModel::init(args);
    
    name$ = $pt(mandatory: true);
    value$ = $pi(default: 0);
    length$ = $pi(default: 4);
    fill_char$ = $pt(default: "0");
    mask$ = $pt(default: "#-yyyy");

    return *this;

}

QString PMSequence::getValue(const QString& value) {

    QString result = QDateTime::currentDateTime().toString(mask$s);
    QString val = QString("%1").arg(value.toLong(), length$i, 10, QChar(fill_char$s[0]));
    return result.replace("#", val);

}


QString PMSequence::nextValue(bool increment) {

    if(getTableCursor() == nil)
        return QString();
   
    if(increment) {
        value$ = value$i + 1;
        this->saveRecord();
        return this->getValue(value$s);
    }

    return this->getValue( QVariant(value$i + 1).toString() );

}


// Controlla se gia' esiste il numero seriale della nuovo documento oppure se manca quello precedente

bool PMSequence::check(const QString& documentTypeId) {

    QString currVal = this->getValue(value$s);
    QString nextVal = this->getValue( QVariant(value$i + 1).toString() );

    PMDocument $document();
    bool current = document.$find(document_type_id: documentTypeId, serial: currVal)->count() > 0;
    bool next = document.$find(document_type_id: documentTypeId, serial: nextVal)->count() > 0;

    if(current == false or next) {
        QString text;

        if(current == false)
            text = $"Serial ${currVal} doesn't exist !!!";
        if(next)
            text = $"Serial ${nextVal} Already Exist !!!";

        PMMessageBox::$messageBox(text: text, icon: "picons/core/actions-128/ko.png");
    }

    return (current == true and next == false) ;

}
