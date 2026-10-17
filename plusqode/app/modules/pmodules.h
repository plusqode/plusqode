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

#ifndef PMODULES_H
#define PMODULES_H
#include "app/modules/sale/pmsale_order/pmsale_order.h"
#include "app/modules/sale/pmsale_credit_note/pmsale_credit_note.h"
#include "app/modules/sale/pmsale_invoice/pmsale_invoice.h"
#include "app/modules/sale/pmsale_quotation/pmsale_quotation.h"
#include "app/modules/sale/pmsale_removed/pmsale_removed.h"
#include "app/modules/booking/pmbooking/pmbooking.h"
#include "app/modules/core/pmcontact_address/pmcontact_address.h"
#include "app/modules/core/pmpayment/pmpayment.h"
#include "app/modules/core/pmmessage_box/pmmessage_box.h"
#include "app/modules/core/pmprofile_model_widget/pmprofile_model_widget.h"
#include "app/modules/core/pmproduct_type/pmproduct_type.h"
#include "app/modules/core/pmuser_authentication/pmuser_authentication.h"
#include "app/modules/core/pmdocument_item_copy/pmdocument_item_copy.h"
#include "app/modules/core/module_manager/pmmodule_manager/pmmodule_manager.h"
#include "app/modules/core/module_manager/pmmodule_repository/pmmodule_repository.h"
#include "app/modules/core/pmcontact_type/pmcontact_type.h"
#include "app/modules/core/pmpayment_copy/pmpayment_copy.h"
#include "app/modules/core/pmproduct/pmproduct.h"
#include "app/modules/core/pmdocument_copy/pmdocument_copy.h"
#include "app/modules/core/pmprofile/pmprofile.h"
#include "app/modules/core/pmtransaction/pmtransaction.h"
#include "app/modules/core/pmcontact/pmcontact.h"
#include "app/modules/core/pmuser_state/pmuser_state.h"
#include "app/modules/core/pmsetting/pmsetting.h"
#include "app/modules/core/pmpayment_mode/pmpayment_mode.h"
#include "app/modules/core/pmuser_manager/pmuser_manager.h"
#include "app/modules/core/pmdocument/pmdocument.h"
#include "app/modules/core/pmdocument_type/pmdocument_type.h"
#include "app/modules/core/pmsequence/pmsequence.h"
#include "app/modules/core/pmdocument_state/pmdocument_state.h"
#include "app/modules/core/pmprofile_module/pmprofile_module.h"
#include "app/modules/core/pmicon/pmicon.h"
#include "app/modules/core/pmcategory/pmcategory.h"
#include "app/modules/core/pmproduct_discount/pmproduct_discount.h"
#include "app/modules/core/pmtax_rate/pmtax_rate.h"
#include "app/modules/core/pmplus4_log/pmplus4_log.h"
#include "app/modules/core/pmdocument_item/pmdocument_item.h"
#include "app/modules/core/pmprofile_model/pmprofile_model.h"
#include "app/modules/core/pmnotes/pmnotes.h"
#include "app/modules/core/pmdocument_attrs/pmdocument_attrs.h"
#include "app/modules/pbx/pmpbx_phone_number/pmpbx_phone_number.h"
#include "app/modules/pbx/pmpbx_voice_agent/pmpbx_voice_agent.h"
#include "app/modules/pbx/pmpbx_phone_number_join/pmpbx_phone_number_join.h"
#include "app/modules/pbx/pmpbx_setting/pmpbx_setting.h"
#include "app/modules/database_manager/pmdatabase_authentication/pmdatabase_authentication.h"
#include "app/modules/database_manager/pmdatabase_import/pmdatabase_import.h"
#include "app/modules/database_manager/pmdatabase_connection_table_field/pmdatabase_connection_table_field.h"
#include "app/modules/database_manager/pmdatabase_connection_table/pmdatabase_connection_table.h"
#include "app/modules/database_manager/pmdatabase_import_field_map/pmdatabase_import_field_map.h"
#include "app/modules/database_manager/pmdatabase_connection/pmdatabase_connection.h"
#include "app/modules/database_manager/pmdatabase_manager/pmdatabase_manager.h"
#include "app/modules/database_manager/pmdatabase_import_table_map/pmdatabase_import_table_map.h"
#include "app/modules/database_manager/pmbackup/pmbackup.h"
#include "app/modules/warehouse/pmbarcode_printer/pmbarcode_printer.h"
#include "app/modules/warehouse/pmbarcode_manager/pmbarcode_manager.h"
#include "app/modules/warehouse/pmscale_setting/pmscale_setting.h"
#include "app/modules/scheduler_manager/pmscheduler_manager/pnotificationmanager.h"
#include "app/modules/scheduler_manager/pmscheduler_manager/pmscheduler_manager.h"
#include "app/modules/pos/pmpos_document_item/pmpos_document_item.h"
#include "app/modules/pos/pmpos_printer/pmpos_printer.h"
#include "app/modules/pos/pmpos_category/pmpos_category.h"
#include "app/modules/pos/pmpos_product/pmpos_product.h"
#include "app/modules/pos/pmpos/pmpos.h"
#include "app/modules/pos/pmpos_payment/ppaymentdialog.h"
#include "app/modules/pos/pmpos_printer_driver/pmpos_printer_driver.h"
#include "app/modules/pos/pmpos_print_manager/pmpos_print_manager.h"
#include "app/modules/pos/pmpos_product_printer/pmpos_product_printer.h"
#include "app/modules/pos/pmpos_document/pmpos_document.h"
#include "app/modules/telemetry/pmactivation/pmactivation.h"
#include "app/modules/telemetry/pmactivation/pactivationserver.h"
#include "app/modules/telemetry/pmstatistic/pmstatistic.h"
#include "app/modules/purchase/pmpurchase_quotation/pmpurchase_quotation.h"
#include "app/modules/purchase/pmpurchase_order/pmpurchase_order.h"
#include "app/modules/purchase/pmpurchase_credit_note/pmpurchase_credit_note.h"
#include "app/modules/purchase/pmpurchase_removed/pmpurchase_removed.h"
#include "app/modules/purchase/pmpurchase_invoice/pmpurchase_invoice.h"
class PModules {
public:

  static PModel* newPModel(PVariant);
  static PModel* variantToModel(PVariant modelVariant);
  static PVariant modelToVariant(PModel* model);
  static PVariant models();
};

#endif // PMODULES_H
