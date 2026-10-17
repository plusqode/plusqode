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




   #include "widgets/sqlview/psqlformviewdialog.h"


   

   

PSqlFormViewDialog::PSqlFormViewDialog(PModelPtr recordPtr, QString mode, PVariant viewAttrs, QWidget* parent) :
        QDialog(parent) {

    PWidgetAttrs::setBackgroundColor(this, PGlobal::windowColor());

    this->setWindowTitle(recordPtr->toClassName(recordPtr->modelName));

    recordPtr->sqlFormViewDialog = this;

    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    buttonBox->setObjectName("dialogButtonBox");

    QDialogButtonBox::ButtonRole buttonRole = QDialogButtonBox::AcceptRole;

    if(viewAttrs.undefined("button_role", nil).toString() != "0")
        buttonRole = (QDialogButtonBox::ButtonRole)viewAttrs.undefined("button_role", nil).toInt();

    okButton = buttonBox->addButton("Ok", buttonRole);
    okButton->setMinimumHeight(40);
    okButton->setIcon(QIcon(":/picons/core/actions/ok.png"));

    cancelButton = buttonBox->addButton("Cancel", buttonRole);
    cancelButton->setMinimumHeight(40);
    cancelButton->setIcon(QIcon(":/picons/core/actions/delete.png"));


    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    
    buttonBox->setCenterButtons(true);


    PMandatoryField* mandatoryField = new PMandatoryField(this);
    mandatoryField->setOkButton(okButton);

    sqlFormView = new PSqlFormView(recordPtr, mode, mandatoryField, viewAttrs, this);
    recordPtr->sqlFormViewDialog = this;
    recordPtr->mode = mode;

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->addWidget(sqlFormView, 0, 0);
    gridLayout->addWidget(buttonBox, 1, 0);

}


void PSqlFormViewDialog::accept() {

    okButton->setFocus();

    if(!sqlFormView->recordPtr->onOkDialog())
        return;

    sqlFormView->recordPtr->setCacheMode(false);
    
    if(sqlFormView->recordPtr->undefined("id", nil).toString()[0] == '$' and sqlFormView->recordPtr->undefined("id", nil).toString()[-1] != '$')
        sqlFormView->recordPtr-> undefined("id", nil)+= "$";

       sqlFormView->recordPtr->cacheValues.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        sqlFormView->recordPtr->setFieldValue(fieldName, fieldValue);
    });

    if(sqlFormView->recordPtr->level == 0 or sqlFormView->recordPtr->writeOnDialog) {
        if(this->sqlFormView->recordPtr->onWrite())
            sqlFormView->recordPtr->apply();
    }

    sqlFormView->recordPtr->onAfterOkDialog();

    sqlFormView->recordPtr->destroy();
    QDialog::accept();

}

void PSqlFormViewDialog::reject() {

    if(!sqlFormView->recordPtr->onCancelDialog())
        return;

    sqlFormView->recordPtr->destroy();
    sqlFormView->recordPtr->setCacheMode(false);
    QDialog::reject();

}



void PSqlFormViewDialog::showFullScreen() {

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)

    QDialog::showFullScreen();

#else

    this->hide();

    
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setWindowState(Qt::WindowFullScreen);

    
    this->setAttribute(Qt::WA_WState_Created, false);

    
    this->show();

#endif

}
