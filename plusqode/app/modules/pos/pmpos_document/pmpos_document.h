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

#ifndef PMPOSDOCUMENT_H
#define PMPOSDOCUMENT_H

#include "app/modules/core/pmdocument/pmdocument.h"
#include "widgets/sqlview/psqlbuttonview.h"
#include "widgets/pnumberpad.h"

class PMPosDocument : public PMDocument {

    Q_OBJECT
    $P_PARENT_VIEW

public:
    PMPosDocument() {}
    PMPosDocument(PVariant args);
    PMPosDocument& init(PVariant);
    PVariant actionPad();

public slots:
    void onChangeField(QString fieldName, PVariant data);
    void onChangePosDocumentItemTable();

    void setFieldWidget(const QString& fieldName); 
    void setBarcodeFieldWidget(); 
    void onAfterWidget();
    void onEditAfterWidget();
    void category_table_onClick(PVariant actionButton);
    void product_table_onClick(PVariant actionButton);

    void setPrice(PVariant price);
    void numberPad_onClick(PVariant button);
    void cleanActionButton_onClick(PVariant button);
    QString writeFile(const QString& fileName, const QString& documentType, PVariant data); 
    void print(PVariant);
    void printPad_onClick(PVariant button); 
    void changeQuantity(const QString& qty);
    void extraPad_onClick(PVariant button);
    void printFromTableView(PVariant button);
    void barcodeOnReturnPressed();
    void barcodeOnTextEdited(const QString& str);
    void barcodeOnLostFocus();
    bool ifScaleBarcode(); 

    virtual QWidget* controlPanelWidget();
    virtual void onCurrentRecordChanged(const QString& id);
    bool onOkDialog();
    virtual PVariant action(PVariant button);
    PVariant remove();
    PVariant setToPay();
    PVariant setBooked();

    
public:    
    QLabel* totalLabel;

};

Q_DECLARE_METATYPE(PMPosDocument*)

#endif // PMPOSDOCUMENT_H
