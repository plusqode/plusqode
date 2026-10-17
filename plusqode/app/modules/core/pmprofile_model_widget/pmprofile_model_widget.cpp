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

#include "app/modules/core/pmprofile_model_widget/pmprofile_model_widget.h"
#include "app/modules/pmodules.h"
#include "widgets/widgetedit/pcombobox.h"
#include "widgets/sqlview/psqlformviewdialog.h"

PMProfileModelWidget::$PMProfileModelWidget() {

    init(args);

}

PMProfileModelWidget& PMProfileModelWidget::init(PVariant args) {

    PModel::init(args);
    
    profile_model_id$ = $pa();

    widget_name$ = $pa(main: true, editable: true, fieldType: "combobox", itemsAndValues: ${});

    name$ = $pt();
    
    visible$ = $pb(default: true, fieldType: "switch_edit", color: "random");
    
    enabled$ = $pb(default: true, fieldType: "switch_edit", color: "random");

    return *this;

}

void PMProfileModelWidget::onChangeField(QString fieldName, PVariant data) {


    if(fieldName == "widget_name")
        name$ = widget_name$s;

}


void PMProfileModelWidget::onAfterWidget() {

    PComboBox* widgetNameComboBox = dynamic_cast<PComboBox*>(getFieldWidget("widget_name"));

    widgetNameComboBox->itemsAndValues = widgets();

    widgetNameComboBox->populateList();

}


PVariant PMProfileModelWidget::widgets(QWidget* parent) {
    
    PVariant result = $[];

    if(parent == 0)
        return result;

    QList<QWidget*> widgetList = parent->findChildren<QWidget*>();
    for(int i = 0; i < widgetList.count(); i++) 
        result << widgetList[i]->objectName();

    return result;
}


PVariant PMProfileModelWidget::widgets() {

    QString modelName = profile_model_id$->model_name$s;

    PModelPtr m = PModel::model(modelName);
    m->setParent(this);
   
    PSqlFormViewDialog formViewDialog(m->toRecordPtr(), "edit");

    PVariant result = widgets(&formViewDialog);

    result << "NewButton" << "EditButton" << "DeleteButton" << $"${modelName}SqlTableView";

    result = result.quicksort();

    return PVariant::fromItemsAndValues(result, result);

}
