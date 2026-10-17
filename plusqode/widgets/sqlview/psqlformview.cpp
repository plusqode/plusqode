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



   #include "widgets/sqlview/psqlformview.h"

   
   
   #include "app/modules/pmodules.h"

   
   
   
   
   
 

PSqlFormView::PSqlFormView(PModelPtr recordPtr,
                             QString mode,
                             PMandatoryField* mandatoryField,
                             PVariant viewAttrs,
                             QWidget* parent) :
        recordPtr(recordPtr),
        mode(mode),
        mandatoryField(mandatoryField),
        PSqlView(parent) {

    this->recordPtr->lockedDataChanged = true;

    this->recordPtr->setCacheMode(true);

    this->recordPtr = recordPtr;

    this->recordPtr->onBeforeWidget();
    if(mode == "new")
        this->recordPtr->onNewBeforeWidget();
    else if(mode == "edit")
        this->recordPtr->onEditBeforeWidget();

    PVariant formView = recordPtr->formViewFields(viewAttrs);

    QGridLayout* mainGridLayout = new QGridLayout(this);
    mainGridLayout->setContentsMargins(0,0,0,0);

    QGridLayout* gridLayout = new QGridLayout();
    mainGridLayout->addLayout(gridLayout, 0, 0);

    edits = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    recordPtr->toWidget(formView, this, gridLayout, mandatoryField, mode);
    recordPtr->initTabOrder();

    this->recordPtr->onAfterWidget();
    if(mode == "new")
        this->recordPtr->onNewAfterWidget();
    else if(mode == "edit")
        this->recordPtr->onEditAfterWidget();

    this->recordPtr->lockedDataChanged = false;

    PSinglUserManager::instance()->applyProfile(this, recordPtr->modelName);

}

PVariant PSqlFormView::data() {

    return nil;

}

void PSqlFormView::setData(PVariant data) {

    

}

void PSqlFormView::setBackgroundColor(QString color) {

}


bool PSqlFormView::isEmpty() {

    
    return true;

}


void PSqlFormView::onEditingFinished() {

    
}


PVariant PSqlFormView::idSelectionList() {

    return nil;

}


PVariant PSqlFormView::selectedRows() {

    return nil;

}

void PSqlFormView::selectItem(int row) {

}

void PSqlFormView::selectLastItem() {

}

int PSqlFormView::count() {

    return 1;

}

void PSqlFormView::onChangeRecord(int row) {

    recordPtr->operator()(row);
    reload();


}

void PSqlFormView::reload() {

    recordPtr->reloadFieldWidget();

}
