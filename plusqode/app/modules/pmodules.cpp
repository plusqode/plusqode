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

#include "app/modules/pmodules.h"
PVariant PModules::models() {
PVariant _models = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
_models << "sale_order";
_models << "sale_credit_note";
_models << "sale_invoice";
_models << "sale_quotation";
_models << "sale_removed";
_models << "booking";
_models << "contact_address";
_models << "payment";
_models << "message_box";
_models << "profile_model_widget";
_models << "product_type";
_models << "user_authentication";
_models << "document_item_copy";
_models << "module_manager";
_models << "module_repository";
_models << "contact_type";
_models << "payment_copy";
_models << "product";
_models << "document_copy";
_models << "profile";
_models << "transaction";
_models << "contact";
_models << "user_state";
_models << "setting";
_models << "payment_mode";
_models << "user_manager";
_models << "document";
_models << "document_type";
_models << "sequence";
_models << "document_state";
_models << "profile_module";
_models << "icon";
_models << "category";
_models << "product_discount";
_models << "tax_rate";
_models << "plus4_log";
_models << "document_item";
_models << "profile_model";
_models << "notes";
_models << "document_attrs";
_models << "pbx_phone_number";
_models << "pbx_voice_agent";
_models << "pbx_phone_number_join";
_models << "pbx_setting";
_models << "database_authentication";
_models << "database_import";
_models << "database_connection_table_field";
_models << "database_connection_table";
_models << "database_import_field_map";
_models << "database_connection";
_models << "database_manager";
_models << "database_import_table_map";
_models << "backup";
_models << "barcode_printer";
_models << "barcode_manager";
_models << "scale_setting";
_models << "scheduler_manager";
_models << "pos_document_item";
_models << "pos_printer";
_models << "pos_category";
_models << "pos_product";
_models << "pos";
_models << "pos_printer_driver";
_models << "pos_print_manager";
_models << "pos_product_printer";
_models << "pos_document";
_models << "activation";
_models << "statistic";
_models << "purchase_quotation";
_models << "purchase_order";
_models << "purchase_credit_note";
_models << "purchase_removed";
_models << "purchase_invoice";
return _models;
}


PModel* PModules::$newPModel(QString modelName: QString(), PVariant parents: $[], QString connectionName: nil, PVariant connectionParams: nil, PVariant domain: ${}, bool generate: true) {
if(connectionName.isNull())    connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();if(modelName == "sale_order") {
PMSaleOrder* sale_order = new $PMSaleOrder(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return sale_order;
}
if(modelName == "sale_credit_note") {
PMSaleCreditNote* sale_credit_note = new $PMSaleCreditNote(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return sale_credit_note;
}
if(modelName == "sale_invoice") {
PMSaleInvoice* sale_invoice = new $PMSaleInvoice(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return sale_invoice;
}
if(modelName == "sale_quotation") {
PMSaleQuotation* sale_quotation = new $PMSaleQuotation(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return sale_quotation;
}
if(modelName == "sale_removed") {
PMSaleRemoved* sale_removed = new $PMSaleRemoved(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return sale_removed;
}
if(modelName == "booking") {
PMBooking* booking = new $PMBooking(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return booking;
}
if(modelName == "contact_address") {
PMContactAddress* contact_address = new $PMContactAddress(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return contact_address;
}
if(modelName == "payment") {
PMPayment* payment = new $PMPayment(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return payment;
}
if(modelName == "message_box") {
PMMessageBox* message_box = new $PMMessageBox(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return message_box;
}
if(modelName == "profile_model_widget") {
PMProfileModelWidget* profile_model_widget = new $PMProfileModelWidget(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return profile_model_widget;
}
if(modelName == "product_type") {
PMProductType* product_type = new $PMProductType(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return product_type;
}
if(modelName == "user_authentication") {
PMUserAuthentication* user_authentication = new $PMUserAuthentication(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return user_authentication;
}
if(modelName == "document_item_copy") {
PMDocumentItemCopy* document_item_copy = new $PMDocumentItemCopy(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return document_item_copy;
}
if(modelName == "module_manager") {
PMModuleManager* module_manager = new $PMModuleManager(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return module_manager;
}
if(modelName == "module_repository") {
PMModuleRepository* module_repository = new $PMModuleRepository(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return module_repository;
}
if(modelName == "contact_type") {
PMContactType* contact_type = new $PMContactType(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return contact_type;
}
if(modelName == "payment_copy") {
PMPaymentCopy* payment_copy = new $PMPaymentCopy(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return payment_copy;
}
if(modelName == "product") {
PMProduct* product = new $PMProduct(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return product;
}
if(modelName == "document_copy") {
PMDocumentCopy* document_copy = new $PMDocumentCopy(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return document_copy;
}
if(modelName == "profile") {
PMProfile* profile = new $PMProfile(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return profile;
}
if(modelName == "transaction") {
PMTransaction* transaction = new $PMTransaction(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return transaction;
}
if(modelName == "contact") {
PMContact* contact = new $PMContact(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return contact;
}
if(modelName == "user_state") {
PMUserState* user_state = new $PMUserState(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return user_state;
}
if(modelName == "setting") {
PMSetting* setting = new $PMSetting(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return setting;
}
if(modelName == "payment_mode") {
PMPaymentMode* payment_mode = new $PMPaymentMode(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return payment_mode;
}
if(modelName == "user_manager") {
PMUserManager* user_manager = new $PMUserManager(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return user_manager;
}
if(modelName == "document") {
PMDocument* document = new $PMDocument(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return document;
}
if(modelName == "document_type") {
PMDocumentType* document_type = new $PMDocumentType(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return document_type;
}
if(modelName == "sequence") {
PMSequence* sequence = new $PMSequence(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return sequence;
}
if(modelName == "document_state") {
PMDocumentState* document_state = new $PMDocumentState(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return document_state;
}
if(modelName == "profile_module") {
PMProfileModule* profile_module = new $PMProfileModule(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return profile_module;
}
if(modelName == "icon") {
PMIcon* icon = new $PMIcon(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return icon;
}
if(modelName == "category") {
PMCategory* category = new $PMCategory(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return category;
}
if(modelName == "product_discount") {
PMProductDiscount* product_discount = new $PMProductDiscount(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return product_discount;
}
if(modelName == "tax_rate") {
PMTaxRate* tax_rate = new $PMTaxRate(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return tax_rate;
}
if(modelName == "plus4_log") {
PMPlus4Log* plus4_log = new $PMPlus4Log(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return plus4_log;
}
if(modelName == "document_item") {
PMDocumentItem* document_item = new $PMDocumentItem(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return document_item;
}
if(modelName == "profile_model") {
PMProfileModel* profile_model = new $PMProfileModel(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return profile_model;
}
if(modelName == "notes") {
PMNotes* notes = new $PMNotes(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return notes;
}
if(modelName == "document_attrs") {
PMDocumentAttrs* document_attrs = new $PMDocumentAttrs(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return document_attrs;
}
if(modelName == "pbx_phone_number") {
PMPbxPhoneNumber* pbx_phone_number = new $PMPbxPhoneNumber(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pbx_phone_number;
}
if(modelName == "pbx_voice_agent") {
PMPbxVoiceAgent* pbx_voice_agent = new $PMPbxVoiceAgent(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pbx_voice_agent;
}
if(modelName == "pbx_phone_number_join") {
PMPbxPhoneNumberJoin* pbx_phone_number_join = new $PMPbxPhoneNumberJoin(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pbx_phone_number_join;
}
if(modelName == "pbx_setting") {
PMPbxSetting* pbx_setting = new $PMPbxSetting(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pbx_setting;
}
if(modelName == "database_authentication") {
PMDatabaseAuthentication* database_authentication = new $PMDatabaseAuthentication(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return database_authentication;
}
if(modelName == "database_import") {
PMDatabaseImport* database_import = new $PMDatabaseImport(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return database_import;
}
if(modelName == "database_connection_table_field") {
PMDatabaseConnectionTableField* database_connection_table_field = new $PMDatabaseConnectionTableField(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return database_connection_table_field;
}
if(modelName == "database_connection_table") {
PMDatabaseConnectionTable* database_connection_table = new $PMDatabaseConnectionTable(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return database_connection_table;
}
if(modelName == "database_import_field_map") {
PMDatabaseImportFieldMap* database_import_field_map = new $PMDatabaseImportFieldMap(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return database_import_field_map;
}
if(modelName == "database_connection") {
PMDatabaseConnection* database_connection = new $PMDatabaseConnection(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return database_connection;
}
if(modelName == "database_manager") {
PMDatabaseManager* database_manager = new $PMDatabaseManager(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return database_manager;
}
if(modelName == "database_import_table_map") {
PMDatabaseImportTableMap* database_import_table_map = new $PMDatabaseImportTableMap(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return database_import_table_map;
}
if(modelName == "backup") {
PMBackup* backup = new $PMBackup(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return backup;
}
if(modelName == "barcode_printer") {
PMBarcodePrinter* barcode_printer = new $PMBarcodePrinter(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return barcode_printer;
}
if(modelName == "barcode_manager") {
PMBarcodeManager* barcode_manager = new $PMBarcodeManager(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return barcode_manager;
}
if(modelName == "scale_setting") {
PMScaleSetting* scale_setting = new $PMScaleSetting(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return scale_setting;
}
if(modelName == "scheduler_manager") {
PMSchedulerManager* scheduler_manager = new $PMSchedulerManager(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return scheduler_manager;
}
if(modelName == "pos_document_item") {
PMPosDocumentItem* pos_document_item = new $PMPosDocumentItem(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pos_document_item;
}
if(modelName == "pos_printer") {
PMPosPrinter* pos_printer = new $PMPosPrinter(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pos_printer;
}
if(modelName == "pos_category") {
PMPosCategory* pos_category = new $PMPosCategory(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pos_category;
}
if(modelName == "pos_product") {
PMPosProduct* pos_product = new $PMPosProduct(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pos_product;
}
if(modelName == "pos") {
PMPos* pos = new $PMPos(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pos;
}
if(modelName == "pos_printer_driver") {
PMPosPrinterDriver* pos_printer_driver = new $PMPosPrinterDriver(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pos_printer_driver;
}
if(modelName == "pos_print_manager") {
PMPosPrintManager* pos_print_manager = new $PMPosPrintManager(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pos_print_manager;
}
if(modelName == "pos_product_printer") {
PMPosProductPrinter* pos_product_printer = new $PMPosProductPrinter(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pos_product_printer;
}
if(modelName == "pos_document") {
PMPosDocument* pos_document = new $PMPosDocument(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return pos_document;
}
if(modelName == "activation") {
PMActivation* activation = new $PMActivation(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return activation;
}
if(modelName == "statistic") {
PMStatistic* statistic = new $PMStatistic(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return statistic;
}
if(modelName == "purchase_quotation") {
PMPurchaseQuotation* purchase_quotation = new $PMPurchaseQuotation(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return purchase_quotation;
}
if(modelName == "purchase_order") {
PMPurchaseOrder* purchase_order = new $PMPurchaseOrder(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return purchase_order;
}
if(modelName == "purchase_credit_note") {
PMPurchaseCreditNote* purchase_credit_note = new $PMPurchaseCreditNote(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return purchase_credit_note;
}
if(modelName == "purchase_removed") {
PMPurchaseRemoved* purchase_removed = new $PMPurchaseRemoved(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return purchase_removed;
}
if(modelName == "purchase_invoice") {
PMPurchaseInvoice* purchase_invoice = new $PMPurchaseInvoice(connectionName: connectionName, connectionParams: connectionParams, domain: domain);
return purchase_invoice;
}
return 0;
}

PModel* PModules::variantToModel(PVariant modelVariant) {
if(modelVariant.typeName() == "PMSaleOrder*") {
return modelVariant.value<PMSaleOrder*>();
}
if(modelVariant.typeName() == "PMSaleCreditNote*") {
return modelVariant.value<PMSaleCreditNote*>();
}
if(modelVariant.typeName() == "PMSaleInvoice*") {
return modelVariant.value<PMSaleInvoice*>();
}
if(modelVariant.typeName() == "PMSaleQuotation*") {
return modelVariant.value<PMSaleQuotation*>();
}
if(modelVariant.typeName() == "PMSaleRemoved*") {
return modelVariant.value<PMSaleRemoved*>();
}
if(modelVariant.typeName() == "PMBooking*") {
return modelVariant.value<PMBooking*>();
}
if(modelVariant.typeName() == "PMContactAddress*") {
return modelVariant.value<PMContactAddress*>();
}
if(modelVariant.typeName() == "PMPayment*") {
return modelVariant.value<PMPayment*>();
}
if(modelVariant.typeName() == "PMMessageBox*") {
return modelVariant.value<PMMessageBox*>();
}
if(modelVariant.typeName() == "PMProfileModelWidget*") {
return modelVariant.value<PMProfileModelWidget*>();
}
if(modelVariant.typeName() == "PMProductType*") {
return modelVariant.value<PMProductType*>();
}
if(modelVariant.typeName() == "PMUserAuthentication*") {
return modelVariant.value<PMUserAuthentication*>();
}
if(modelVariant.typeName() == "PMDocumentItemCopy*") {
return modelVariant.value<PMDocumentItemCopy*>();
}
if(modelVariant.typeName() == "PMModuleManager*") {
return modelVariant.value<PMModuleManager*>();
}
if(modelVariant.typeName() == "PMModuleRepository*") {
return modelVariant.value<PMModuleRepository*>();
}
if(modelVariant.typeName() == "PMContactType*") {
return modelVariant.value<PMContactType*>();
}
if(modelVariant.typeName() == "PMPaymentCopy*") {
return modelVariant.value<PMPaymentCopy*>();
}
if(modelVariant.typeName() == "PMProduct*") {
return modelVariant.value<PMProduct*>();
}
if(modelVariant.typeName() == "PMDocumentCopy*") {
return modelVariant.value<PMDocumentCopy*>();
}
if(modelVariant.typeName() == "PMProfile*") {
return modelVariant.value<PMProfile*>();
}
if(modelVariant.typeName() == "PMTransaction*") {
return modelVariant.value<PMTransaction*>();
}
if(modelVariant.typeName() == "PMContact*") {
return modelVariant.value<PMContact*>();
}
if(modelVariant.typeName() == "PMUserState*") {
return modelVariant.value<PMUserState*>();
}
if(modelVariant.typeName() == "PMSetting*") {
return modelVariant.value<PMSetting*>();
}
if(modelVariant.typeName() == "PMPaymentMode*") {
return modelVariant.value<PMPaymentMode*>();
}
if(modelVariant.typeName() == "PMUserManager*") {
return modelVariant.value<PMUserManager*>();
}
if(modelVariant.typeName() == "PMDocument*") {
return modelVariant.value<PMDocument*>();
}
if(modelVariant.typeName() == "PMDocumentType*") {
return modelVariant.value<PMDocumentType*>();
}
if(modelVariant.typeName() == "PMSequence*") {
return modelVariant.value<PMSequence*>();
}
if(modelVariant.typeName() == "PMDocumentState*") {
return modelVariant.value<PMDocumentState*>();
}
if(modelVariant.typeName() == "PMProfileModule*") {
return modelVariant.value<PMProfileModule*>();
}
if(modelVariant.typeName() == "PMIcon*") {
return modelVariant.value<PMIcon*>();
}
if(modelVariant.typeName() == "PMCategory*") {
return modelVariant.value<PMCategory*>();
}
if(modelVariant.typeName() == "PMProductDiscount*") {
return modelVariant.value<PMProductDiscount*>();
}
if(modelVariant.typeName() == "PMTaxRate*") {
return modelVariant.value<PMTaxRate*>();
}
if(modelVariant.typeName() == "PMPlus4Log*") {
return modelVariant.value<PMPlus4Log*>();
}
if(modelVariant.typeName() == "PMDocumentItem*") {
return modelVariant.value<PMDocumentItem*>();
}
if(modelVariant.typeName() == "PMProfileModel*") {
return modelVariant.value<PMProfileModel*>();
}
if(modelVariant.typeName() == "PMNotes*") {
return modelVariant.value<PMNotes*>();
}
if(modelVariant.typeName() == "PMDocumentAttrs*") {
return modelVariant.value<PMDocumentAttrs*>();
}
if(modelVariant.typeName() == "PMPbxPhoneNumber*") {
return modelVariant.value<PMPbxPhoneNumber*>();
}
if(modelVariant.typeName() == "PMPbxVoiceAgent*") {
return modelVariant.value<PMPbxVoiceAgent*>();
}
if(modelVariant.typeName() == "PMPbxPhoneNumberJoin*") {
return modelVariant.value<PMPbxPhoneNumberJoin*>();
}
if(modelVariant.typeName() == "PMPbxSetting*") {
return modelVariant.value<PMPbxSetting*>();
}
if(modelVariant.typeName() == "PMDatabaseAuthentication*") {
return modelVariant.value<PMDatabaseAuthentication*>();
}
if(modelVariant.typeName() == "PMDatabaseImport*") {
return modelVariant.value<PMDatabaseImport*>();
}
if(modelVariant.typeName() == "PMDatabaseConnectionTableField*") {
return modelVariant.value<PMDatabaseConnectionTableField*>();
}
if(modelVariant.typeName() == "PMDatabaseConnectionTable*") {
return modelVariant.value<PMDatabaseConnectionTable*>();
}
if(modelVariant.typeName() == "PMDatabaseImportFieldMap*") {
return modelVariant.value<PMDatabaseImportFieldMap*>();
}
if(modelVariant.typeName() == "PMDatabaseConnection*") {
return modelVariant.value<PMDatabaseConnection*>();
}
if(modelVariant.typeName() == "PMDatabaseManager*") {
return modelVariant.value<PMDatabaseManager*>();
}
if(modelVariant.typeName() == "PMDatabaseImportTableMap*") {
return modelVariant.value<PMDatabaseImportTableMap*>();
}
if(modelVariant.typeName() == "PMBackup*") {
return modelVariant.value<PMBackup*>();
}
if(modelVariant.typeName() == "PMBarcodePrinter*") {
return modelVariant.value<PMBarcodePrinter*>();
}
if(modelVariant.typeName() == "PMBarcodeManager*") {
return modelVariant.value<PMBarcodeManager*>();
}
if(modelVariant.typeName() == "PMScaleSetting*") {
return modelVariant.value<PMScaleSetting*>();
}
if(modelVariant.typeName() == "PMSchedulerManager*") {
return modelVariant.value<PMSchedulerManager*>();
}
if(modelVariant.typeName() == "PMPosDocumentItem*") {
return modelVariant.value<PMPosDocumentItem*>();
}
if(modelVariant.typeName() == "PMPosPrinter*") {
return modelVariant.value<PMPosPrinter*>();
}
if(modelVariant.typeName() == "PMPosCategory*") {
return modelVariant.value<PMPosCategory*>();
}
if(modelVariant.typeName() == "PMPosProduct*") {
return modelVariant.value<PMPosProduct*>();
}
if(modelVariant.typeName() == "PMPos*") {
return modelVariant.value<PMPos*>();
}
if(modelVariant.typeName() == "PMPosPrinterDriver*") {
return modelVariant.value<PMPosPrinterDriver*>();
}
if(modelVariant.typeName() == "PMPosPrintManager*") {
return modelVariant.value<PMPosPrintManager*>();
}
if(modelVariant.typeName() == "PMPosProductPrinter*") {
return modelVariant.value<PMPosProductPrinter*>();
}
if(modelVariant.typeName() == "PMPosDocument*") {
return modelVariant.value<PMPosDocument*>();
}
if(modelVariant.typeName() == "PMActivation*") {
return modelVariant.value<PMActivation*>();
}
if(modelVariant.typeName() == "PMStatistic*") {
return modelVariant.value<PMStatistic*>();
}
if(modelVariant.typeName() == "PMPurchaseQuotation*") {
return modelVariant.value<PMPurchaseQuotation*>();
}
if(modelVariant.typeName() == "PMPurchaseOrder*") {
return modelVariant.value<PMPurchaseOrder*>();
}
if(modelVariant.typeName() == "PMPurchaseCreditNote*") {
return modelVariant.value<PMPurchaseCreditNote*>();
}
if(modelVariant.typeName() == "PMPurchaseRemoved*") {
return modelVariant.value<PMPurchaseRemoved*>();
}
if(modelVariant.typeName() == "PMPurchaseInvoice*") {
return modelVariant.value<PMPurchaseInvoice*>();
}
return 0;
}
PVariant PModules::modelToVariant(PModel* model) {
if(model->modelName == "sale_order") {
PMSaleOrder* sale_order = (PMSaleOrder*)model;
return QVariant::fromValue(sale_order);
}
if(model->modelName == "sale_credit_note") {
PMSaleCreditNote* sale_credit_note = (PMSaleCreditNote*)model;
return QVariant::fromValue(sale_credit_note);
}
if(model->modelName == "sale_invoice") {
PMSaleInvoice* sale_invoice = (PMSaleInvoice*)model;
return QVariant::fromValue(sale_invoice);
}
if(model->modelName == "sale_quotation") {
PMSaleQuotation* sale_quotation = (PMSaleQuotation*)model;
return QVariant::fromValue(sale_quotation);
}
if(model->modelName == "sale_removed") {
PMSaleRemoved* sale_removed = (PMSaleRemoved*)model;
return QVariant::fromValue(sale_removed);
}
if(model->modelName == "booking") {
PMBooking* booking = (PMBooking*)model;
return QVariant::fromValue(booking);
}
if(model->modelName == "contact_address") {
PMContactAddress* contact_address = (PMContactAddress*)model;
return QVariant::fromValue(contact_address);
}
if(model->modelName == "payment") {
PMPayment* payment = (PMPayment*)model;
return QVariant::fromValue(payment);
}
if(model->modelName == "message_box") {
PMMessageBox* message_box = (PMMessageBox*)model;
return QVariant::fromValue(message_box);
}
if(model->modelName == "profile_model_widget") {
PMProfileModelWidget* profile_model_widget = (PMProfileModelWidget*)model;
return QVariant::fromValue(profile_model_widget);
}
if(model->modelName == "product_type") {
PMProductType* product_type = (PMProductType*)model;
return QVariant::fromValue(product_type);
}
if(model->modelName == "user_authentication") {
PMUserAuthentication* user_authentication = (PMUserAuthentication*)model;
return QVariant::fromValue(user_authentication);
}
if(model->modelName == "document_item_copy") {
PMDocumentItemCopy* document_item_copy = (PMDocumentItemCopy*)model;
return QVariant::fromValue(document_item_copy);
}
if(model->modelName == "module_manager") {
PMModuleManager* module_manager = (PMModuleManager*)model;
return QVariant::fromValue(module_manager);
}
if(model->modelName == "module_repository") {
PMModuleRepository* module_repository = (PMModuleRepository*)model;
return QVariant::fromValue(module_repository);
}
if(model->modelName == "contact_type") {
PMContactType* contact_type = (PMContactType*)model;
return QVariant::fromValue(contact_type);
}
if(model->modelName == "payment_copy") {
PMPaymentCopy* payment_copy = (PMPaymentCopy*)model;
return QVariant::fromValue(payment_copy);
}
if(model->modelName == "product") {
PMProduct* product = (PMProduct*)model;
return QVariant::fromValue(product);
}
if(model->modelName == "document_copy") {
PMDocumentCopy* document_copy = (PMDocumentCopy*)model;
return QVariant::fromValue(document_copy);
}
if(model->modelName == "profile") {
PMProfile* profile = (PMProfile*)model;
return QVariant::fromValue(profile);
}
if(model->modelName == "transaction") {
PMTransaction* transaction = (PMTransaction*)model;
return QVariant::fromValue(transaction);
}
if(model->modelName == "contact") {
PMContact* contact = (PMContact*)model;
return QVariant::fromValue(contact);
}
if(model->modelName == "user_state") {
PMUserState* user_state = (PMUserState*)model;
return QVariant::fromValue(user_state);
}
if(model->modelName == "setting") {
PMSetting* setting = (PMSetting*)model;
return QVariant::fromValue(setting);
}
if(model->modelName == "payment_mode") {
PMPaymentMode* payment_mode = (PMPaymentMode*)model;
return QVariant::fromValue(payment_mode);
}
if(model->modelName == "user_manager") {
PMUserManager* user_manager = (PMUserManager*)model;
return QVariant::fromValue(user_manager);
}
if(model->modelName == "document") {
PMDocument* document = (PMDocument*)model;
return QVariant::fromValue(document);
}
if(model->modelName == "document_type") {
PMDocumentType* document_type = (PMDocumentType*)model;
return QVariant::fromValue(document_type);
}
if(model->modelName == "sequence") {
PMSequence* sequence = (PMSequence*)model;
return QVariant::fromValue(sequence);
}
if(model->modelName == "document_state") {
PMDocumentState* document_state = (PMDocumentState*)model;
return QVariant::fromValue(document_state);
}
if(model->modelName == "profile_module") {
PMProfileModule* profile_module = (PMProfileModule*)model;
return QVariant::fromValue(profile_module);
}
if(model->modelName == "icon") {
PMIcon* icon = (PMIcon*)model;
return QVariant::fromValue(icon);
}
if(model->modelName == "category") {
PMCategory* category = (PMCategory*)model;
return QVariant::fromValue(category);
}
if(model->modelName == "product_discount") {
PMProductDiscount* product_discount = (PMProductDiscount*)model;
return QVariant::fromValue(product_discount);
}
if(model->modelName == "tax_rate") {
PMTaxRate* tax_rate = (PMTaxRate*)model;
return QVariant::fromValue(tax_rate);
}
if(model->modelName == "plus4_log") {
PMPlus4Log* plus4_log = (PMPlus4Log*)model;
return QVariant::fromValue(plus4_log);
}
if(model->modelName == "document_item") {
PMDocumentItem* document_item = (PMDocumentItem*)model;
return QVariant::fromValue(document_item);
}
if(model->modelName == "profile_model") {
PMProfileModel* profile_model = (PMProfileModel*)model;
return QVariant::fromValue(profile_model);
}
if(model->modelName == "notes") {
PMNotes* notes = (PMNotes*)model;
return QVariant::fromValue(notes);
}
if(model->modelName == "document_attrs") {
PMDocumentAttrs* document_attrs = (PMDocumentAttrs*)model;
return QVariant::fromValue(document_attrs);
}
if(model->modelName == "pbx_phone_number") {
PMPbxPhoneNumber* pbx_phone_number = (PMPbxPhoneNumber*)model;
return QVariant::fromValue(pbx_phone_number);
}
if(model->modelName == "pbx_voice_agent") {
PMPbxVoiceAgent* pbx_voice_agent = (PMPbxVoiceAgent*)model;
return QVariant::fromValue(pbx_voice_agent);
}
if(model->modelName == "pbx_phone_number_join") {
PMPbxPhoneNumberJoin* pbx_phone_number_join = (PMPbxPhoneNumberJoin*)model;
return QVariant::fromValue(pbx_phone_number_join);
}
if(model->modelName == "pbx_setting") {
PMPbxSetting* pbx_setting = (PMPbxSetting*)model;
return QVariant::fromValue(pbx_setting);
}
if(model->modelName == "database_authentication") {
PMDatabaseAuthentication* database_authentication = (PMDatabaseAuthentication*)model;
return QVariant::fromValue(database_authentication);
}
if(model->modelName == "database_import") {
PMDatabaseImport* database_import = (PMDatabaseImport*)model;
return QVariant::fromValue(database_import);
}
if(model->modelName == "database_connection_table_field") {
PMDatabaseConnectionTableField* database_connection_table_field = (PMDatabaseConnectionTableField*)model;
return QVariant::fromValue(database_connection_table_field);
}
if(model->modelName == "database_connection_table") {
PMDatabaseConnectionTable* database_connection_table = (PMDatabaseConnectionTable*)model;
return QVariant::fromValue(database_connection_table);
}
if(model->modelName == "database_import_field_map") {
PMDatabaseImportFieldMap* database_import_field_map = (PMDatabaseImportFieldMap*)model;
return QVariant::fromValue(database_import_field_map);
}
if(model->modelName == "database_connection") {
PMDatabaseConnection* database_connection = (PMDatabaseConnection*)model;
return QVariant::fromValue(database_connection);
}
if(model->modelName == "database_manager") {
PMDatabaseManager* database_manager = (PMDatabaseManager*)model;
return QVariant::fromValue(database_manager);
}
if(model->modelName == "database_import_table_map") {
PMDatabaseImportTableMap* database_import_table_map = (PMDatabaseImportTableMap*)model;
return QVariant::fromValue(database_import_table_map);
}
if(model->modelName == "backup") {
PMBackup* backup = (PMBackup*)model;
return QVariant::fromValue(backup);
}
if(model->modelName == "barcode_printer") {
PMBarcodePrinter* barcode_printer = (PMBarcodePrinter*)model;
return QVariant::fromValue(barcode_printer);
}
if(model->modelName == "barcode_manager") {
PMBarcodeManager* barcode_manager = (PMBarcodeManager*)model;
return QVariant::fromValue(barcode_manager);
}
if(model->modelName == "scale_setting") {
PMScaleSetting* scale_setting = (PMScaleSetting*)model;
return QVariant::fromValue(scale_setting);
}
if(model->modelName == "scheduler_manager") {
PMSchedulerManager* scheduler_manager = (PMSchedulerManager*)model;
return QVariant::fromValue(scheduler_manager);
}
if(model->modelName == "pos_document_item") {
PMPosDocumentItem* pos_document_item = (PMPosDocumentItem*)model;
return QVariant::fromValue(pos_document_item);
}
if(model->modelName == "pos_printer") {
PMPosPrinter* pos_printer = (PMPosPrinter*)model;
return QVariant::fromValue(pos_printer);
}
if(model->modelName == "pos_category") {
PMPosCategory* pos_category = (PMPosCategory*)model;
return QVariant::fromValue(pos_category);
}
if(model->modelName == "pos_product") {
PMPosProduct* pos_product = (PMPosProduct*)model;
return QVariant::fromValue(pos_product);
}
if(model->modelName == "pos") {
PMPos* pos = (PMPos*)model;
return QVariant::fromValue(pos);
}
if(model->modelName == "pos_printer_driver") {
PMPosPrinterDriver* pos_printer_driver = (PMPosPrinterDriver*)model;
return QVariant::fromValue(pos_printer_driver);
}
if(model->modelName == "pos_print_manager") {
PMPosPrintManager* pos_print_manager = (PMPosPrintManager*)model;
return QVariant::fromValue(pos_print_manager);
}
if(model->modelName == "pos_product_printer") {
PMPosProductPrinter* pos_product_printer = (PMPosProductPrinter*)model;
return QVariant::fromValue(pos_product_printer);
}
if(model->modelName == "pos_document") {
PMPosDocument* pos_document = (PMPosDocument*)model;
return QVariant::fromValue(pos_document);
}
if(model->modelName == "activation") {
PMActivation* activation = (PMActivation*)model;
return QVariant::fromValue(activation);
}
if(model->modelName == "statistic") {
PMStatistic* statistic = (PMStatistic*)model;
return QVariant::fromValue(statistic);
}
if(model->modelName == "purchase_quotation") {
PMPurchaseQuotation* purchase_quotation = (PMPurchaseQuotation*)model;
return QVariant::fromValue(purchase_quotation);
}
if(model->modelName == "purchase_order") {
PMPurchaseOrder* purchase_order = (PMPurchaseOrder*)model;
return QVariant::fromValue(purchase_order);
}
if(model->modelName == "purchase_credit_note") {
PMPurchaseCreditNote* purchase_credit_note = (PMPurchaseCreditNote*)model;
return QVariant::fromValue(purchase_credit_note);
}
if(model->modelName == "purchase_removed") {
PMPurchaseRemoved* purchase_removed = (PMPurchaseRemoved*)model;
return QVariant::fromValue(purchase_removed);
}
if(model->modelName == "purchase_invoice") {
PMPurchaseInvoice* purchase_invoice = (PMPurchaseInvoice*)model;
return QVariant::fromValue(purchase_invoice);
}
return nil;
}
