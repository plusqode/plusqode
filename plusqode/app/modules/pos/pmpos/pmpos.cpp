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

#include "app/modules/pos/pmpos/pmpos.h"

PMPos::$PMPos() {

    init(args);

}

PMPos& PMPos::init(PVariant args) {

    PModel::init(args);

    showFullScreen = true;
    tabLayoutDirection = Qt::RightToLeft;

    name$ = $pt(mandatory: true);
    icon$ = $pt(fieldType: "image_edit");
    pos_document_table$ = $pa(fieldType: "icon_view");
    pos_document_table2$ = $po2m(modelName: "pos_document", referenceFieldName: "pos_id");

    return *this;

}


