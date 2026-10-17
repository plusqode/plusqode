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

#include "app/modules/pos/pmpos_document/pmpos_document.h"
#include "app/modules/pmodules.h"

PMPosDocument::$PMPosDocument() {

    init(args);

}

PMPosDocument& PMPosDocument::init(PVariant args) {

    this->totalLabel = 0;

    args.domain$ += ${document_type_id.name: 'Pos Document'};
    
    PMDocument::init(args);

    document_state_id_attrs$ = $(readOnly: true);

    contact_id_attrs$ = ${mandatory: false};
    
    QString posDocumentID = $PMDocumentType().$find(name: "Pos Document")->id$s;
    
    document_type_id_attrs$ = ${default: posDocumentID};
    
    showField = "serial";
    showField = $["serial", "contact_id.contact_surname", "contact_id.contact_name"];
    showFullScreen = true;
    writeOnDialog = true; // It performes the db writing pushing ok button also with level > 0
    stateIdFieldName = "document_state_id";
   
    category_table$ = $pa(fieldType: "button_table");
    product_table$ = $pa(fieldType: "button_table");

    pos_document_item_table$ = $pa();

    return *this;

}

void PMPosDocument::onChangeField(QString fieldName, PVariant data) {

    if(fieldName == "pos_document_item_table")
        onChangePosDocumentItemTable();

    PMDocument::onChangeField(fieldName, data);

}


void PMPosDocument::onChangePosDocumentItemTable() {

    PVariant documentItems = $[];

    PModelPtr model = pos_document_item_table$;
    $model->forEach(PVariant documentItem) {
        documentItems << ${tax_rate: model->tax_rate_id$->value$, qt_price_with_discount: documentItem.total_with_discount$};
    }


    PAccounting acc;

    PVariant vs = acc.vatSummaryTotals(documentItems, discount_rate$f);

    PVariant vs_no_discont = acc.vatSummaryTotals(documentItems);

    taxable_no_discount$ = vs_no_discont.taxable$;
    taxable$ = acc.round(vs.taxable$f);
    tax$ = acc.round(vs.rounded_tax$f);
    total_no_discount$  = vs_no_discont.total$f;

    total$ = acc.round(vs_no_discont.total$f) - acc.round(discount_value_with_tax$f);

    vat_summary$ = acc.vatSummary(documentItems, discount_rate$f).toString();

}


PVariant PMPosDocument::actionPad() {

    PVariant buttons = $[];

    PModelPtr documentType = PModel::model("document_type");
    documentType->setParent(this);
    documentType->$find(print_button: true);

    if(documentType->document_attrs_id$ == 0) {
        PLog().error() << $"PMPosDocument::actionPad(): documentType(${documentType->name$s})->document_attrs_id must have a value";
        exit(0);
    }

    int hue = 0;
    int autoCol = 0;
    $documentType->forEach(PModelPtr documentType) {
        int row = documentType->document_attrs_id$->row$i;
        int col = documentType->document_attrs_id$->col$i;
        if(col == -1) { 
            row = 0;
            col = autoCol++;
        }
        hue += 70;
        PVariant icon = ${name: "picons/core/actions/print.png", hue: hue, width: 32, height: 32};
        if(documentType->icon_id$) {
            icon = documentType->icon_id$->current();
            icon.name$ = icon.icon$;
            if(icon.hue$i == -1) { 
                icon.hue$ = hue;
                icon.saturation$ = 0;
            }
        }
        buttons << ${name: documentType->name$, toolTip: documentType->name$,
                     row: row, col: col, minimumWidth: 100, minimumHeight: 60, icon: icon};
    }

    return buttons;

}

void PMPosDocument::setFieldWidget(const QString& fieldName) {
    
    PLineEdit* fieldWidget = dynamic_cast<PLineEdit*>(getFieldWidget(fieldName));
    QFont font = fieldWidget->lineEdit->font();
    font.setPixelSize(20);
    //font.setBold(true);
    fieldWidget->lineEdit->setFont(font);
    fieldWidget->lineEdit->setEnabled(false);
    
    QLabel* fieldLabel = dynamic_cast<QLabel*>(getFieldLabel(fieldName));
    fieldLabel->setFont(font);

}



void PMPosDocument::setBarcodeFieldWidget() {
    
    QLineEdit* barcodeLineEdit = (QLineEdit*)barcode$w->mainWidget();

    setFieldWidget("barcode");
    barcodeLineEdit->setEnabled(true);

    barcode$w->disconnect();
    connect(barcode$w->mainWidget(), SIGNAL(returnPressed()), this, SLOT(barcodeOnReturnPressed()));
    connect(barcode$w->mainWidget(), SIGNAL(textEdited(const QString&)), this, SLOT(barcodeOnTextEdited(const QString&)));
    connect(barcode$w->mainWidget(), SIGNAL(editingFinished()), this, SLOT(barcodeOnLostFocus()));

}



void PMPosDocument::onAfterWidget() {

    user_manager_id$ = PSinglUserManager::instance()->userId; 

    connect(category_table$w, SIGNAL(click(PVariant)), this, SLOT(category_table_onClick(PVariant))); 
    connect(product_table$w, SIGNAL(click(PVariant)), this, SLOT(product_table_onClick(PVariant)));

    PSqlButtonView* categoryTable = dynamic_cast<PSqlButtonView*>(category_table$w);
    if(categoryTable->buttonList.count())
        categoryTable->buttonList.first()->onClick();


    QWidget* numberPadGridWidget = $<QWidget*>("number_padWidget");
    QGridLayout* numberPadGridLayout = $<QGridLayout*>("number_padGridLayout");

    if(numberPadGridLayout) {
        PActionButtons* actionButtons = new PActionButtons(numberPadGridWidget);
        PVariant buttons = actionButtons->numberPad2();
        PActionButtons::setButtonSize(buttons, 30, 40);
        actionButtons->initByVariant(buttons);
        connect(actionButtons, SIGNAL(click(PVariant)), this, SLOT(numberPad_onClick(PVariant)));
        numberPadGridLayout->addWidget(actionButtons, 0, 0);
    }
    
    
    QWidget* printPadGridWidget = $<QWidget*>("print_padWidget");
    QGridLayout* printPadGridLayout = $<QGridLayout*>("print_padGridLayout");

    if(printPadGridLayout) {
        PActionButtons* actionButtons = new PActionButtons(printPadGridWidget);
        actionButtons->initByVariant(actionPad());
        connect(actionButtons, SIGNAL(click(PVariant)), this, SLOT(printFromTableView(PVariant)));
        printPadGridLayout->addWidget(actionButtons, 0, 0);

        PActionButtons* variantButtons = new PActionButtons(printPadGridWidget);
        PVariant buttons = variantButtons->numberPad5();
        PActionButtons::setButtonSize(buttons, 30, 60);
        PActionButtons::setFontSize(buttons, 30);
        variantButtons->initByVariant(buttons);
        connect(variantButtons, SIGNAL(click(PVariant)), this, SLOT(extraPad_onClick(PVariant)));
        printPadGridLayout->addWidget(variantButtons, 1, 0);

    }

    setFieldWidget("taxable");
    setFieldWidget("tax");
    setFieldWidget("total");
    setBarcodeFieldWidget();

    QWidget* controlPanelGridWidget = $<QWidget*>("control-panelWidget");
    QGridLayout* controlPanelGridLayout = $<QGridLayout*>("control-panelGridLayout");

    if(controlPanelGridLayout) {
        PActionButtons* actionButtons = new PActionButtons(controlPanelGridWidget);
        actionButtons->initByVariant(actionPad());
        connect(actionButtons, SIGNAL(click(PVariant)), this, SLOT(printFromTableView(PVariant)));
        controlPanelGridLayout->addWidget(actionButtons, 0, 2);
    }

}  

void PMPosDocument::onEditAfterWidget() {
    
    serial$w->setDisabled(true);

}

void PMPosDocument::category_table_onClick(PVariant actionButton) {

    PSqlButtonView* productTable = (PSqlButtonView*)product_table$w;

    qDebug() << actionButton.toString() << "\n";
    int categoryId = actionButton.id$i;
    productTable->$applyFilter(category_id: categoryId);

}

void PMPosDocument::product_table_onClick(PVariant product) {

    PVariant mask = ${name:, price:, discount_rate:, tax_rate_id:, price_with_discount_and_tax:, total_with_discount:, pos_printer_id:};

    PVariant item = product & mask;

    item.product_id$ = product.id$;

    item.quantity$ = 1;

    QString lastQty = pos_document_item_table$->quantity$s;
    QString posPrinterId;
    if(pos_document_item_table$->count())
        posPrinterId = pos_document_item_table$->pos_printer_id$->id$s;

    pos_document_item_table$->create(item);

    if(pos_document_item_table$->isModifier()) { // la modifica deve avere la stessa quantita dell'prodotto corrente
        pos_document_item_table$->quantity$ = lastQty;
        if(!posPrinterId.isNull()) pos_document_item_table$->pos_printer_id$ = posPrinterId;
    }

    pos_document_item_table$->onChangeField("price", nil);
    editingFinished("pos_document_item_table", nil);

    pos_document_item_table$->setModifier("+");

}

void PMPosDocument::setPrice(PVariant price) {

    bool taxInclusiveMode = PSinglConfigurationManager::instance()->value("settings", "tax_inclusive_mode").toBool();

    if(taxInclusiveMode) {
        pos_document_item_table$->price_with_tax$ = price;
        pos_document_item_table$->onChangeField("price_with_tax", nil);
    }
    else {
        pos_document_item_table$->price$ = price;
        pos_document_item_table$->onChangeField("price", nil);
    }

    editingFinished("pos_document_item_table", nil);

}


void PMPosDocument::numberPad_onClick(PVariant button) {

    if(button.name$ == "$") {
        PNumberPad np;
        if(np.exec() == QDialog::Accepted) 
            setPrice(np.getValue());
        return;
    }

    if(button.name$ == "qty") {
        PNumberPad np;
        if(np.exec() == QDialog::Accepted)  
            this->changeQuantity(QVariant(np.getValue()).toString());
    }
    else
        this->changeQuantity(button.name$s);
    
    editingFinished("pos_document_item_table", nil);

}

void PMPosDocument::changeQuantity(const QString& qty) {

    if(pos_document_item_table$->isModifier())
        return;

    PVariant cr = pos_document_item_table$->getTableCursor();

    do {
        pos_document_item_table$->changeQuantity(qty);
    } while(pos_document_item_table$->next() != nil and pos_document_item_table$->isModifier());

    pos_document_item_table$->setTableCursor(cr);

}


void PMPosDocument::extraPad_onClick(PVariant button) {

//    qDebug() << " - - - ->" << button.name$s << pos_document_item_table$->product_id$;

    if(!pos_document_item_table$->isModifier()) {
        PMMessageBox::$messageBox(text: "This product is not a modifier !!!", icon: "picons/core/actions-128/ko.png");
        return;
    }

    if(button.name$s == "clean") {
        cleanActionButton_onClick(button);
        return;
    }

    pos_document_item_table$->setModifier(button.name$s);

}


QString PMPosDocument::writeFile(const QString& fileName, const QString& documentType, PVariant data) { 
   
    QString dt = documentType;
    dt.replace(" ", "");

    QString documentPath = $"${PGlobal::dataPath()}/pos/documents/${dt}";

    if(!QDir().exists(documentPath))
        QDir().mkdir(documentPath);

    PDir::fileWrite($"${documentPath}/${fileName}", data.toString().toUtf8());

    return $"${documentPath}/${fileName}";

}


void PMPosDocument::$print(PVariant button:, bool payment: false, bool order: false) {

    if(pos_document_item_table$->count() == 0)
        return;

    QString documentType = button.name$s;
    QString printType = button.print_type$s;
    QString printerId =  button["printer_id"].toString();
    QString printerName =  button.printer_name$s;

    QString fileName = PDir::currentDateTime();
    
    PVariant currentDocument = ${};

    PVariant items = $[];

    $pFields.forEach(QString fieldName, PVariant field) {
        currentDocument[fieldName] = fieldValue(fieldName);
    }

    currentDocument.date$ = QDate::currentDate().toString("yyyy-MM-dd");
    currentDocument.time$ = QTime::currentTime().toString("hh.mm.ss");
    currentDocument.user$ = user_manager_id$->name$;


    PPaymentDialog pd;
    pd.setTotal(currentDocument.total$s);
    if(payment and pd.exec() != QDialog::Accepted)
        return;

    currentDocument.payments$ = pd.payments();

    PVariant data = ${document_type: documentType,
                      print_type: printType,
                      printer_id: printerId,
                      printer_name: printerName,
                      document_name: fileName,
                      document: currentDocument,
                      document_items: items};

    $this->pos_document_item_table$->forEach(PVariant documentItem) {
        PVariant item = ${};
        $documentItem.forEach(QString fieldName, QString fieldValue) {
            item[fieldName] = fieldValue;
            if(fieldName == "tax_rate_id") {
                item["tax_rate_value"] = pos_document_item_table$->tax_rate_id$->value$s;
                item["department"] = pos_document_item_table$->tax_rate_id$->department$s;
            }

        }
        items << item;
    }

    fileName = writeFile(fileName, documentType, data);

    PLog().debug() << "= = = = = = >" << fileName;

    PMPosPrintManager $posPrintManager();

    QString myIpAddress = PSinglConfigurationManager::instance()->value("settings", "ip_address").toString();

    PMPosPrinter $posPrinter();
    posPrinter.$find(document_type_id.name: documentType);
    int  i = 0;
    $posPrinter.forEach(PModelPtr posPrinterModel) {

        QString copyNumber = posPrinterModel->document_type_id$->document_attrs_id$->copy_number$s;

        if(!(order and i++ >= 1)) // se si tratta di un ordine esegue una volta sola
        posPrintManager.$create(filename: fileName,
                                name: documentType,
                                machine_ip_address: myIpAddress,
                                ip_address: posPrinterModel->ip_address$,
                                port: posPrinterModel->port$,
                                copy_number: copyNumber,
                                printed: false);

        posPrintManager.writeAllRecords();

    }

    PModelPtr modelCopy = this->copy();

    modelCopy->paid$ = modelCopy->total$;

    PVariant payments = pd.payments();
    $payments.forEach(PVariant record) {
        modelCopy->payment_copy_table$->create(record);
    }

    modelCopy->writeAllRecords();

}


void PMPosDocument::printPad_onClick(PVariant button) {

    QString documentType = button.name$s;

    PMPosPrinter $posPrinter();
    posPrinter.$find(document_type_id.name: documentType);

    if(button.name$s.include("Order")) {
        if(pos_document_item_table$->$find(to_print: true)->count() == 0)
            return;
        $posPrinter.forEach(PModelPtr posPrinterModel) {
            button.print_type$ = posPrinterModel->document_type_id$->document_attrs_id$->print_type$$s;
            button.printer_id$ = posPrinterModel->id$s;
            button.printer_name$ = posPrinterModel->name$s;
            $print(button: button, payment: false, order: true);
        }
        return;
    }

    $print(button: button, payment: true);

}


void PMPosDocument::printFromTableView(PVariant button) {

    printPad_onClick(button);

    if(!button.name$s.include("Order"))
        cleanActionButton_onClick(${});

}


void PMPosDocument::barcodeOnReturnPressed() {

    if(this->ifScaleBarcode())
        return;

    QLineEdit* barcodeLineEdit = (QLineEdit*)barcode$w->mainWidget();

    PMProduct $product();
    product.$find(barcode: barcodeLineEdit->text());

    if(product.count() == 1) 
        product_table_onClick(product.current());
    else if(product.count() == 0)
        PMMessageBox::$messageBox(text: "Article not Found !!!", icon: "picons/core/actions-128/ko.png");
    else if(product.count() > 1)
        PMMessageBox::$messageBox(text: "Barcode duplicated !!!", icon: "picons/core/actions-128/ko.png");

    barcodeLineEdit->setText("");

}

void PMPosDocument::barcodeOnTextEdited(const QString& str) {

    qDebug() << "focus in";
    barcode$w->setBackgroundColor("yellow");

}

void PMPosDocument::barcodeOnLostFocus() {
    
    qDebug() << "focus out";
    barcode$w->setBackgroundColor("white");

}



bool PMPosDocument::ifScaleBarcode() {

    // Per far funzionare il barcode con la bilancia aggiungere un prefisso nella tabella scale_setting" 
    // Aggiungere il prodotto generico con barcode "0123"

    QLineEdit* barcodeLineEdit = (QLineEdit*)barcode$w->mainWidget();

    PMScaleSetting $scaleSetting();
    scaleSetting.$findBy();

    if(scaleSetting.count() == 0)
        return false;
   
   
    PVariant setting; 
    $scaleSetting.forEach(PVariant s) {
        if(barcodeLineEdit->text().startsWith(setting.prefix$s))
            setting = s;
    }

    QString scaleBarcode = setting.prefix$s;

    if(scaleBarcode != "" && barcodeLineEdit->text().startsWith(scaleBarcode)) {

        PMProduct $product();
        product.$find(barcode: scaleBarcode);
        if(product.count() == 0) 
            return false;

        product_table_onClick(product.current());
        QString price = barcodeLineEdit->text().mid(scaleBarcode.length() + 1);
        int price_int = price.toInt() / 10;
        double price_double = ((double)price_int) / 100;
        this->setPrice(price_double); 
        barcodeLineEdit->setText("");       

        return true;

    }

    return false;

}


QWidget* PMPosDocument::controlPanelWidget() {

    QWidget* printPadGridWidget = new QWidget();
    QGridLayout* printPadGridLayout = new QGridLayout(printPadGridWidget);

    totalLabel = new QLabel("Total: 0.00");
    totalLabel->setObjectName("totalLabel");
    QFont font = totalLabel->font();
    font.setPixelSize(30);
    font.setBold(true);
    totalLabel->setFont(font);
    totalLabel->setStyleSheet("color: gray;");
    printPadGridLayout->addWidget(totalLabel, 0, 0);


    PActionButtons* actionButtons = new PActionButtons(printPadGridWidget);
    actionButtons->initByVariant(actionPad());
    connect(actionButtons, SIGNAL(click(PVariant)), this, SLOT(printPad_onClick(PVariant)));
    printPadGridLayout->addWidget(actionButtons, 0, 1);

    return printPadGridWidget;

}



void PMPosDocument::onCurrentRecordChanged(const QString& id) {

    if(totalLabel)
        totalLabel->setText(PTranslator::tr(PTranslator::tr("Total: "))  + this->total$s);

}


bool PMPosDocument::onOkDialog() {

    QString freeStateId = $PMDocumentState().$find(name: 'free')->id$s;

    if(this->document_state_id$ == 0)
        this->document_state_id$ = freeStateId;

    if(this->document_state_id$->id$s == freeStateId)
        this->document_state_id$ = $PMDocumentState().$find(name: 'busy')->id$s;;

    this->apply();

    this->printPad_onClick(${name: "Pos Order"});

    $this->pos_document_item_table$->forEach(PModelPtr documentItem) {
        documentItem->saveRecord(${to_print: false});
    }

    return true;

}


PVariant PMPosDocument::action(PVariant button) {

    if(button.action$s == "exit")
        qApp->quit();
    else if(button.action$s == "remove")
        return this->remove();
    else if(button.action$s == "setToPay")
        return this->setToPay();
    else if(button.action$s == "setBooked")
        return this->setBooked();
    else if(button.action$s == "clean") {
        PMPosPrintManager $ppm();
        ppm.$removeOnDB();
    }
    else
        return PMDocument::action(button);

    this->sqlView->reloadCurrentRecord();

    return true;

}


PVariant PMPosDocument::remove() {

    QString freeStateId = $PMDocumentState().$find(name: 'free')->id$s;

    if(this->document_state_id$ == 0)
        this->document_state_id$ = freeStateId;

    if(this->document_state_id$->name$s == "free")
        return false;

    this->document_state_id$ = freeStateId;
    this->contact_id$ = "$null";
    this->discount_rate$ = 0;
    this->discount_value$ = 0;
    this->pos_document_item_table$->remove("all");
    this->apply();
    this->onChangeDocumentItemTable();

    if(totalLabel)
        totalLabel->setText(PTranslator::tr("Total: 0.00"));

    this->sqlView->reloadCurrentRecord();

    return true;

}


PVariant PMPosDocument::setToPay() {

    QString busyStateId = $PMDocumentState().$find(name: 'busy')->id$s;
    QString toPayStateId = $PMDocumentState().$find(name: 'to-pay')->id$s;

    if(this->document_state_id$->name$s == "busy")
        this->document_state_id$ = toPayStateId;
    else if(this->total$f > 0)
        this->document_state_id$ = busyStateId;


    this->apply();

    this->sqlView->reloadCurrentRecord();
    return true;


}


PVariant PMPosDocument::setBooked() {

    if(this->document_state_id$->name$s == "booked") {
        this->document_state_id$ = $PMDocumentState().$find(name: 'free')->id$s;
        this->apply();
        this->sqlView->reloadCurrentRecord();
        return true;
    }

    if(this->document_state_id$->name$s != "free")
        return false;

    this->document_state_id$ = $PMDocumentState().$find(name: 'booked')->id$s;
    this->apply();
    this->sqlView->reloadCurrentRecord();
    return true;

}



void PMPosDocument::cleanActionButton_onClick(PVariant) {

    pos_document_item_table$->remove("all");
    this->reloadFieldWidget("pos_document_item_table");
    onChangePosDocumentItemTable();

}
