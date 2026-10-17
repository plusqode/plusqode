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

#include "app/modules/core/pmicon/pmicon.h"
#include "widgets/sqlview/psqlformviewdialog.h"
#include "misc/pimage.h"
#include "widgets/widgetedit/pspinbox.h"

PMIcon::$PMIcon() {

    init(args);

}

PMIcon& PMIcon::init(PVariant args) {

    PModel::init(args);
    
    dataChangedConnection = true; // Enable SIGNAL on dataChanged on fieldEdit

    name$ = $pt(mandatory: true);
    icon$ = $pt(fieldType: "image_edit");
    hue$ = $pi(default: 0, fieldType: "spinbox", minimum: -1, maximum: 300);
    saturation$ = $pi(default: 255, fieldType: "spinbox");
    scale$ = $pi(default: 100, fieldType: "spinbox", singleStep: 5);

    preview$ = $pw();

    return *this;

}


void PMIcon::onAfterWidget() {

    previewWidget = $<QWidget*>("previewWidget");
    previewGridLayout = $<QGridLayout*>("previewGridLayout");

    if(previewGridLayout) {
        previewLabel = new QLabel(previewWidget);
        previewGridLayout->addWidget(previewLabel, 0, 0);
        onChangeField("icon", nil);
    }

    QSpinBox* hueSpinBox = dynamic_cast<PSpinBox*>(hue$w)->spinBox;
    hueSpinBox->setMaximum(359);
    hueSpinBox->setSingleStep(10);
    
    QSpinBox* saturationSpinBox = dynamic_cast<PSpinBox*>(saturation$w)->spinBox;
    saturationSpinBox->setMaximum(255);
    saturationSpinBox->setSingleStep(10);
    
    QSpinBox* scaleSpinBox = dynamic_cast<PSpinBox*>(scale$w)->spinBox;
    scaleSpinBox->setMinimum(20);

}  

void PMIcon::onDataChanged(QString fieldName, PVariant data) {

    onChangeField(fieldName, data);

}


void PMIcon::onChangeField(QString fieldName, PVariant fieldValue) {

    if(fieldName == "hue" || fieldName == "saturation" || fieldName == "icon" || fieldName == "scale") {
        if(previewGridLayout) {
            PImage image(icon$s);
            if(hue$i || saturation$i) image.setHS(hue$i, saturation$i);
            if(scale$i) image = image.scaled(image.width() * 100 / scale$i,
                                              image.height() * 100 / scale$i, 
                                              Qt::KeepAspectRatio);
            previewLabel->setPixmap(image.toPixmap());
        }
    }

}

