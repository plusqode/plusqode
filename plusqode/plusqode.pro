message(Qt Version: $${QT_MAJOR_VERSION})

QT       += core gui widgets network sql xml

lessThan(QT_MAJOR_VERSION, 6): QT += xmlpatterns script
versionAtLeast(QT_MAJOR_VERSION, 6): QT += widgets webenginewidgets
# sudo apt-get install qt6-websockets-dev qt6-httpserver-dev
versionAtLeast(QT_VERSION, "6.5.0"): QT += httpserver

!win32 {
    QT += webenginewidgets
}


TARGET = plusqode
TEMPLATE = app

isEmpty(PLUSQODE_LIB) {
    message()
    message(- To Build Library $QT_PATH/bin/pmake \"PLUSQODE_LIB=true\" plusqode.pro.build)
    message()
}
else {
    TEMPLATE = lib
    message()
    message(Creation of PlusQode Library libplusqode.so.1.0.0)
    message( - How to use:)
    message( -----------> in your .pro file LIBS += -L. -lplusqode and DEFINES += PLUSQODE_LIBRARY)
    message( -----------> in your .bash_profile: export LD_LIBRARY_PATH=\"/usr/local/lib;.\")
    message()
}

mac {

    TARGET = PlusQode

}

unix { # Mac and Linux
    CONFIG  += qt warn_on debug console
}

win32 {
    CONFIG  += qt warn_on console
}

QMAKE_CXXFLAGS += -w # disable all warnings
#QMAKE_CXXFLAGS += -Werror=return-type
QMAKE_CXXFLAGS += 

CONFIG  -= debug_and_release # evita la crezione di Makefile.Debug and Makefile.Release

    
SOURCES += main.cpp\
plusqode.cpp\
variant/pvariantmap.cpp\
variant/pvariantlist.cpp\
variant/pvariant.cpp\
sql/psql.cpp\
misc/pdebug.cpp\
misc/pstring.cpp\
app/modules/core/pmdocument/pmdocument.cpp\
app/modules/core/pmdocument_item/pmdocument_item.cpp\
app/modules/pmodules.cpp\
misc/pdir.cpp\
configuration/pconfigparser.cpp\
configuration/pconfigurationscanner.cpp\
configuration/pconfigurationparser.cpp\
configuration/pconfiguration.cpp\
configuration/pconfigurationmanager.cpp\
core/plogger.cpp\
core/pviewloader.cpp\
misc/psystem.cpp\
sql/psqlgenerator.cpp\
sql/ppgsqlgenerator.cpp\
sql/psqldataloader.cpp\
app/modules/core/pmcontact/pmcontact.cpp\
app/modules/core/pmcontact_type/pmcontact_type.cpp\
app/modules/core/pmcontact_address/pmcontact_address.cpp\
sql/psqlfield.cpp\
app/modules/core/pmtax_rate/pmtax_rate.cpp\
core/pdocgenerator.cpp\
core/pdemo.cpp\
misc/pwindow.cpp\
demo/variant/pvariantdemo.cpp\
sql/pmodel.cpp\
demo/sql/pmodeldemo.cpp\
demo/sql/psqldemo.cpp\
widgets/ptabnavigation.cpp\
sql/pmodelview.cpp\
demo/core/pviewloaderdemo.cpp\
core/pview.cpp\
demo/sql/pmodelviewdemo.cpp\
widgets/sqlview/psqltableview.cpp\
widgets/pactionbuttons.cpp\
widgets/pactionbutton.cpp\
widgets/paction.cpp\
widgets/sqlview/psqlformview.cpp\
widgets/widgetedit/pfiledialogedit.cpp\
widgets/widgetedit/pcoloredit.cpp\
widgets/widgetedit/pdateedit.cpp\
widgets/widgetedit/ptimeedit.cpp\
widgets/widgetedit/pdatetimeedit.cpp\
widgets/widgetedit/pimagefiledialog.cpp\
widgets/widgetedit/pimageedit.cpp\
widgets/widgetedit/pcurrencyedit.cpp\
widgets/widgetedit/pdirectorydialogedit.cpp\
widgets/widgetedit/pcolorcombobox.cpp\
widgets/widgetedit/pimagezoomdialog.cpp\
widgets/pmandatoryfield.cpp\
widgets/widgetedit/pfieldwidget.cpp\
widgets/widgetedit/plineedit.cpp\
widgets/widgetedit/ptextedit.cpp\
widgets/widgetedit/pbooledit.cpp\
widgets/widgetedit/pplaintextedit.cpp\
core/pglobal.cpp\
widgets/widgetedit/psqlcombobox.cpp\
misc/pmath.cpp\
app/modules/core/pmcategory/pmcategory.cpp\
app/modules/core/pmproduct/pmproduct.cpp\
widgets/widgetedit/plabel.cpp\
widgets/widgetedit/pprogressbar.cpp\
widgets/widgetedit/pcombobox.cpp\
app/modules/database_manager/pmdatabase_connection/pmdatabase_connection.cpp\
app/modules/database_manager/pmdatabase_connection_table/pmdatabase_connection_table.cpp\
app/modules/database_manager/pmdatabase_connection_table_field/pmdatabase_connection_table_field.cpp\
app/modules/database_manager/pmdatabase_import/pmdatabase_import.cpp\
app/modules/database_manager/pmdatabase_import_table_map/pmdatabase_import_table_map.cpp\
app/modules/database_manager/pmdatabase_import_field_map/pmdatabase_import_field_map.cpp\
widgets/widgetedit/pdashboard.cpp\
widgets/widgetedit/pprogressbarplus.cpp\
widgets/widgetedit/pswitchedit.cpp\
app/modules/database_manager/pmdatabase_manager/pmdatabase_manager.cpp\
widgets/widgetedit/pxmlwidget.cpp\
app/modules/core/pmpayment/pmpayment.cpp\
app/modules/core/pmpayment_mode/pmpayment_mode.cpp\
app/modules/core/pmtransaction/pmtransaction.cpp\
app/modules/core/pmdocument_state/pmdocument_state.cpp\
widgets/sqlview/psqlbuttonview.cpp\
app/modules/pos/pmpos_document/pmpos_document.cpp\
app/modules/core/pmuser_manager/pmuser_manager.cpp\
widgets/ppushbutton.cpp\
widgets/sqlview/psqliconview.cpp\
app/modules/pos/pmpos/pmpos.cpp\
misc/pimage.cpp\
app/modules/pos/pmpos_printer/pmpos_printer.cpp\
app/modules/pos/pmpos_printer_driver/pmpos_printer_driver.cpp\
widgets/sqlview/psqlview.cpp\
app/modules/pos/pmpos_category/pmpos_category.cpp\
app/modules/pos/pmpos_product/pmpos_product.cpp\
widgets/sqlview/psqlviewtabwidget.cpp\
widgets/sqlview/psqlformviewdialog.cpp\
widgets/sqlview/psqlpagination.cpp\
app/modules/pos/pmpos_product_printer/pmpos_product_printer.cpp\
widgets/pnumberpad.cpp\
widgets/pwidgetattrs.cpp\
widgets/widgetedit/pspinbox.cpp\
app/modules/core/pmicon/pmicon.cpp\
app/modules/pos/pmpos_print_manager/pmpos_print_manager.cpp\
pos/pprinterdriver.cpp\
pos/pepsontmt88.cpp\
pos/pposprintmanagerthread.cpp\
core/psleeper.cpp\
misc/ptcpsocket.cpp\
pos/pepsontmt88lan.cpp\
widgets/pcheckbox.cpp\
widgets/widgetedit/pcheckboxedit.cpp\
widgets/pradiobutton.cpp\
widgets/widgetedit/pradiobuttonedit.cpp\
widgets/sqlview/psqlfilterpanel.cpp\
widgets/sqlview/psqlmenufilter.cpp\
widgets/sqlview/psqlmenufilters.cpp\
widgets/sqlview/psqlgrouptableview.cpp\
widgets/sqlview/psqlgrouppanel.cpp\
widgets/sqlview/psqltableviewdialog.cpp\
app/modules/core/pmprofile/pmprofile.cpp\
app/modules/core/pmprofile_model/pmprofile_model.cpp\
misc/pusermanager.cpp\
app/modules/core/pmuser_authentication/pmuser_authentication.cpp\
widgets/pmainview.cpp\
app/modules/core/pmprofile_model_widget/pmprofile_model_widget.cpp\
widgets/pstateprogressbar.cpp\
widgets/widgetedit/pstateprogressbaredit.cpp\
app/modules/core/pmprofile_module/pmprofile_module.cpp\
app/modules/core/pmmessage_box/pmmessage_box.cpp\
widgets/ptablewidget.cpp\
app/modules/core/pmuser_state/pmuser_state.cpp\
widgets/sqlview/psqltabview.cpp\
widgets/ppwidget.cpp\
widgets/ptabwidget.cpp\
app/modules/database_manager/pmbackup/pmbackup.cpp\
app/modules/sale/pmsale_invoice/pmsale_invoice.cpp\
app/modules/core/pmdocument_type/pmdocument_type.cpp\
app/modules/core/pmdocument_attrs/pmdocument_attrs.cpp\
app/modules/core/pmsequence/pmsequence.cpp\
app/modules/core/module_manager/pmmodule_manager/pmmodule_manager.cpp\
app/modules/sale/pmsale_quotation/pmsale_quotation.cpp\
app/modules/sale/pmsale_order/pmsale_order.cpp\
app/modules/sale/pmsale_credit_note/pmsale_credit_note.cpp\
app/modules/sale/pmsale_removed/pmsale_removed.cpp\
app/modules/purchase/pmpurchase_quotation/pmpurchase_quotation.cpp\
app/modules/purchase/pmpurchase_credit_note/pmpurchase_credit_note.cpp\
app/modules/purchase/pmpurchase_invoice/pmpurchase_invoice.cpp\
app/modules/purchase/pmpurchase_order/pmpurchase_order.cpp\
app/modules/purchase/pmpurchase_removed/pmpurchase_removed.cpp\
app/modules/core/pmdocument_copy/pmdocument_copy.cpp\
app/modules/core/pmdocument_item_copy/pmdocument_item_copy.cpp\
app/modules/core/pmpayment_copy/pmpayment_copy.cpp\
pos/pxonxoff.cpp\
widgets/pvirtualkeyboard.cpp\
widgets/pklineedit.cpp\
app/modules/pos/pmpos_payment/ppaymentdialog.cpp\
dom/pdom.cpp\
app/views/test.html.cpp\
app/modules/core/pmdocument/pmdocument.html.cpp\
dom/pdomtable.cpp\
misc/pcalculator.cpp\
sql/pmysqlgenerator.cpp\
core/pshareddata.cpp\
sql/psqlitegenerator.cpp\
app/modules/database_manager/pmdatabase_authentication/pmdatabase_authentication.cpp\
app/modules/core/module_manager/pmmodule_repository/pmmodule_repository.cpp\
app/modules/warehouse/pmbarcode_manager/pmbarcode_manager.cpp\
app/modules/warehouse/pmbarcode_printer/pmbarcode_printer.cpp\
core/ptranslator.cpp\
app/modules/core/pmsetting/pmsetting.cpp\
app/modules/warehouse/pmscale_setting/pmscale_setting.cpp\
app/modules/core/pmproduct_discount/pmproduct_discount.cpp\
misc/paccounting.cpp\
widgets/widgetedit/psqltextcombobox.cpp\
app/modules/core/pmnotes/pmnotes.cpp\
misc/pget.cpp\
misc/pprofilemanager.cpp\
misc/pmakedialog.cpp\
misc/popenurl.cpp\
core/pjobscheduler.cpp\
app/modules/scheduler_manager/pmscheduler_manager/pmscheduler_manager.cpp\
app/modules/scheduler_manager/pmscheduler_manager/pmscheduler_manager_html.cpp\
app/modules/scheduler_manager/pmscheduler_manager/pnotificationmanager.cpp\
app/modules/core/pmplus4_log/pmplus4_log.cpp\
app/modules/core/pmplus4_log/pmplus4_log_html.cpp\
app/modules/pos/pmpos_document_item/pmpos_document_item.cpp\
app/modules/core/pmproduct_type/pmproduct_type.cpp\
widgets/pfieldselector.cpp\
misc/pgembridge.cpp\
app/modules/booking/pmbooking/pmbooking.cpp\
app/modules/booking/pmbooking/pmbooking_html.cpp\
widgets/widgetedit/pcomboboxplus.cpp\
app/modules/pbx/pmpbx_setting/pmpbx_setting.cpp\
app/modules/pbx/pmpbx_setting/pmpbx_setting_html.cpp\
app/modules/pbx/pmpbx_phone_number/pmpbx_phone_number.cpp\
app/modules/pbx/pmpbx_phone_number/pmpbx_phone_number_html.cpp\
app/modules/pbx/pmpbx_voice_agent/pmpbx_voice_agent.cpp\
app/modules/pbx/pmpbx_voice_agent/pmpbx_voice_agent_html.cpp\
app/modules/pbx/pmpbx_phone_number_join/pmpbx_phone_number_join.cpp\
app/modules/pbx/pmpbx_phone_number_join/pmpbx_phone_number_join_html.cpp\
misc/pprocessdialog.cpp\
misc/ptelemetry.cpp\
misc/pjsonhttpservice.cpp\
app/modules/telemetry/pmactivation/pmactivation.cpp\
app/modules/telemetry/pmactivation/pmactivation_html.cpp\
app/modules/telemetry/pmactivation/pactivationserver.cpp\
app/modules/telemetry/pmstatistic/pmstatistic.cpp\
app/modules/telemetry/pmstatistic/pmstatistic_html.cpp

HEADERS += plusqode.h\
variant/pvariantmap.h\
variant/pvariantlist.h\
variant/pvariant.h\
sql/psql.h\
misc/pdebug.h\
misc/pstring.h\
app/modules/core/pmdocument/pmdocument.h\
app/modules/core/pmdocument_item/pmdocument_item.h\
app/modules/pmodules.h\
misc/pdir.h\
configuration/pconfigurationheader.h\
configuration/pconfigparser.h\
configuration/pconfigurationscanner.h\
configuration/pconfigurationparser.h\
configuration/pconfiguration.h\
configuration/pconfigurationmanager.h\
core/plogger.h\
core/pviewloader.h\
misc/psystem.h\
sql/psqlgenerator.h\
sql/ppgsqlgenerator.h\
sql/psqldataloader.h\
app/modules/core/pmcontact/pmcontact.h\
app/modules/core/pmcontact_type/pmcontact_type.h\
app/modules/core/pmcontact_address/pmcontact_address.h\
sql/psqlfield.h\
app/modules/core/pmtax_rate/pmtax_rate.h\
core/pdocgenerator.h\
core/pdemo.h\
misc/pwindow.h\
demo/variant/pvariantdemo.h\
sql/pmodel.h\
demo/sql/pmodeldemo.h\
demo/sql/psqldemo.h\
widgets/ptabnavigation.h\
sql/pmodelview.h\
demo/core/pviewloaderdemo.h\
core/pview.h\
demo/sql/pmodelviewdemo.h\
widgets/sqlview/psqltableview.h\
widgets/pactionbuttons.h\
widgets/pactionbutton.h\
widgets/paction.h\
widgets/sqlview/psqlformview.h\
widgets/widgetedit/pfiledialogedit.h\
widgets/widgetedit/pcoloredit.h\
widgets/widgetedit/pdateedit.h\
widgets/widgetedit/ptimeedit.h\
widgets/widgetedit/pdatetimeedit.h\
widgets/widgetedit/pimagefiledialog.h\
widgets/widgetedit/pimageedit.h\
widgets/widgetedit/pcurrencyedit.h\
widgets/widgetedit/pdirectorydialogedit.h\
widgets/widgetedit/pcolorcombobox.h\
widgets/widgetedit/pimagezoomdialog.h\
widgets/pmandatoryfield.h\
widgets/widgetedit/pfieldwidget.h\
widgets/widgetedit/plineedit.h\
widgets/widgetedit/pbooledit.h\
widgets/widgetedit/pplaintextedit.h\
widgets/widgetedit/ptextedit.h\
core/pglobal.h\
widgets/widgetedit/psqlcombobox.h\
misc/pmath.h\
app/modules/core/pmcategory/pmcategory.h\
app/modules/core/pmproduct/pmproduct.h\
widgets/widgetedit/plabel.h\
widgets/widgetedit/pprogressbar.h\
widgets/widgetedit/pcombobox.h\
app/modules/database_manager/pmdatabase_connection/pmdatabase_connection.h\
app/modules/database_manager/pmdatabase_connection_table/pmdatabase_connection_table.h\
app/modules/database_manager/pmdatabase_connection_table_field/pmdatabase_connection_table_field.h\
app/modules/database_manager/pmdatabase_import/pmdatabase_import.h\
app/modules/database_manager/pmdatabase_import_table_map/pmdatabase_import_table_map.h\
app/modules/database_manager/pmdatabase_import_field_map/pmdatabase_import_field_map.h\
widgets/widgetedit/pdashboard.h\
widgets/widgetedit/pprogressbarplus.h\
widgets/widgetedit/pswitchedit.h\
app/modules/database_manager/pmdatabase_manager/pmdatabase_manager.h\
widgets/widgetedit/pxmlwidget.h\
app/modules/core/pmpayment/pmpayment.h\
app/modules/core/pmpayment_mode/pmpayment_mode.h\
app/modules/core/pmtransaction/pmtransaction.h\
app/modules/core/pmdocument_state/pmdocument_state.h\
widgets/sqlview/psqlbuttonview.h\
app/modules/pos/pmpos_document/pmpos_document.h\
app/modules/core/pmuser_manager/pmuser_manager.h\
widgets/ppushbutton.h\
widgets/sqlview/psqliconview.h\
app/modules/pos/pmpos/pmpos.h\
misc/pimage.h\
app/modules/pos/pmpos_printer/pmpos_printer.h\
app/modules/pos/pmpos_printer_driver/pmpos_printer_driver.h\
widgets/sqlview/psqlview.h\
app/modules/pos/pmpos_category/pmpos_category.h\
app/modules/pos/pmpos_product/pmpos_product.h\
widgets/sqlview/psqlviewtabwidget.h\
widgets/sqlview/psqlformviewdialog.h\
widgets/sqlview/psqlpagination.h\
app/modules/pos/pmpos_product_printer/pmpos_product_printer.h\
widgets/pnumberpad.h\
widgets/pwidgetattrs.h\
widgets/widgetedit/pspinbox.h\
app/modules/core/pmicon/pmicon.h\
app/modules/pos/pmpos_print_manager/pmpos_print_manager.h\
pos/pprinterdriver.h\
pos/pepsontmt88.h\
pos/pposprintmanagerthread.h\
core/psleeper.h\
misc/ptcpsocket.h\
pos/pepsontmt88lan.h\
widgets/pcheckbox.h\
widgets/widgetedit/pcheckboxedit.h\
widgets/pradiobutton.h\
widgets/widgetedit/pradiobuttonedit.h\
widgets/sqlview/psqlfilterpanel.h\
widgets/sqlview/psqlmenufilter.h\
widgets/sqlview/psqlmenufilters.h\
widgets/sqlview/psqlgrouptableview.h\
widgets/sqlview/psqlgrouppanel.h\
widgets/sqlview/psqltableviewdialog.h\
app/modules/core/pmprofile/pmprofile.h\
app/modules/core/pmprofile_model/pmprofile_model.h\
misc/pusermanager.h\
app/modules/core/pmuser_authentication/pmuser_authentication.h\
widgets/pmainview.h\
app/modules/core/pmprofile_model_widget/pmprofile_model_widget.h\
widgets/pstateprogressbar.h\
widgets/widgetedit/pstateprogressbaredit.h\
app/modules/core/pmprofile_module/pmprofile_module.h\
app/modules/core/pmmessage_box/pmmessage_box.h\
widgets/ptablewidget.h\
app/modules/core/pmuser_state/pmuser_state.h\
widgets/sqlview/psqltabview.h\
widgets/ppwidget.h\
widgets/ptabwidget.h\
app/modules/database_manager/pmbackup/pmbackup.h\
app/modules/sale/pmsale_invoice/pmsale_invoice.h\
app/modules/core/pmdocument_type/pmdocument_type.h\
app/modules/core/pmdocument_attrs/pmdocument_attrs.h\
app/modules/core/pmsequence/pmsequence.h\
app/modules/core/module_manager/pmmodule_manager/pmmodule_manager.h\
app/modules/sale/pmsale_quotation/pmsale_quotation.h\
app/modules/sale/pmsale_order/pmsale_order.h\
app/modules/sale/pmsale_credit_note/pmsale_credit_note.h\
app/modules/sale/pmsale_removed/pmsale_removed.h\
app/modules/purchase/pmpurchase_quotation/pmpurchase_quotation.h\
app/modules/purchase/pmpurchase_credit_note/pmpurchase_credit_note.h\
app/modules/purchase/pmpurchase_invoice/pmpurchase_invoice.h\
app/modules/purchase/pmpurchase_order/pmpurchase_order.h\
app/modules/purchase/pmpurchase_removed/pmpurchase_removed.h\
app/modules/core/pmdocument_copy/pmdocument_copy.h\
app/modules/core/pmdocument_item_copy/pmdocument_item_copy.h\
app/modules/core/pmpayment_copy/pmpayment_copy.h\
pos/pxonxoff.h\
widgets/pvirtualkeyboard.h\
widgets/pklineedit.h\
app/modules/pos/pmpos_payment/ppaymentdialog.h\
dom/pdom.h\
dom/pdomtable.h\
misc/pcalculator.h\
sql/pmysqlgenerator.h\
core/pshareddata.h\
sql/psqlitegenerator.h\
app/modules/database_manager/pmdatabase_authentication/pmdatabase_authentication.h\
app/modules/core/module_manager/pmmodule_repository/pmmodule_repository.h\
app/modules/warehouse/pmbarcode_manager/pmbarcode_manager.h\
app/modules/warehouse/pmbarcode_printer/pmbarcode_printer.h\
core/ptranslator.h\
app/modules/core/pmsetting/pmsetting.h\
app/modules/warehouse/pmscale_setting/pmscale_setting.h\
app/modules/core/pmproduct_discount/pmproduct_discount.h\
misc/paccounting.h\
widgets/widgetedit/psqltextcombobox.h\
app/modules/core/pmnotes/pmnotes.h\
misc/pget.h\
misc/pprofilemanager.h\
misc/pmakedialog.h\
misc/popenurl.h\
dom/phtml_header.h\
core/pjobscheduler.h\
app/modules/scheduler_manager/pmscheduler_manager/pmscheduler_manager.h\
app/modules/scheduler_manager/pmscheduler_manager/pnotificationmanager.h\
app/modules/core/pmplus4_log/pmplus4_log.h\
app/modules/pos/pmpos_document_item/pmpos_document_item.h\
app/modules/core/pmproduct_type/pmproduct_type.h\
widgets/pfieldselector.h\
misc/pgembridge.h\
app/modules/booking/pmbooking/pmbooking.h\
widgets/widgetedit/pcomboboxplus.h\
app/modules/pbx/pmpbx_setting/pmpbx_setting.h\
app/modules/pbx/pmpbx_phone_number/pmpbx_phone_number.h\
app/modules/pbx/pmpbx_voice_agent/pmpbx_voice_agent.h\
app/modules/pbx/pmpbx_phone_number_join/pmpbx_phone_number_join.h\
misc/pprocessdialog.h\
misc/ptelemetry.h\
misc/pjsonhttpservice.h\
app/modules/telemetry/pmactivation/pmactivation.h\
app/modules/telemetry/pmactivation/pactivationserver.h\
app/modules/telemetry/pmstatistic/pmstatistic.h

FORMS    += plusqode.ui

FLEXSOURCES = configuration/pconfigurationscanner.l
BISONSOURCES = configuration/pconfigurationparser.y

OTHER_FILES +=  \
    $$FLEXSOURCES \
    $$BISONSOURCES \
    plusqode.cfg \
    app/modules/3rdparty/menu_view.xml

RESOURCES += \
    picons.qrc

#INCLUDEPATH +=

#LIBS +=

mac {
    ICON = picons/plusqode/plusqode.icns
}
