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





   #include "widgets/widgetedit/pxmlwidget.h"



   


   

PXmlWidget::PXmlWidget(PModel* model, PMandatoryField* mandatoryField, QString mode, PVariant fieldAttrs, QWidget *parent) :
    PFieldWidget(parent) {

    QString xml = fieldAttrs.undefined("xml", nil).toString();

    PView view;
    view.initByViewStr(xml);

    this->setObjectName(PString(QString("%1Widget").arg(fieldAttrs.undefined("name", nil).toString())));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setObjectName(PString(QString("%1GridLayout").arg(fieldAttrs.undefined("name", nil).toString())));

    model->toWidget(view.toVariant(), this, layout, mandatoryField, mode);

}


PVariant PXmlWidget::data() {

    return "";

}

void PXmlWidget::setData(PVariant data) {



}

void PXmlWidget::setBackgroundColor(QString color) {

}


bool PXmlWidget::isEmpty() {

    return false;

}
