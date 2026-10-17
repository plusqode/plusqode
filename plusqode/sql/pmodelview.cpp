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



   #include "sql/pmodel.h"

   
   
   #include "app/modules/pmodules.h"

   
   
   
   
   
 

QString PModel   ::currentFileName() {

    return QString();

}




QString PModel   ::getModuleName() {

  if(!this->moduleName.isNull())
      return this->moduleName;

  QDir sf(currentFileName());
  PString sourceFile = sf.path();
  sourceFile = sourceFile.split("/").value<PVariantListPtr>()->mid2(0, -2 + 1).join("/");
  QString basePath = "app/modules/";
  moduleName = sourceFile.split(basePath)[1].toString();
  moduleName = moduleName.replace("/", ".");

  return moduleName;

}


void PModel   ::destroy() {

       fieldWidgets.forEachQString_PVariant([&] (QString fieldName,PVariant widgetList) mutable {
         widgetList.forEachPVariant([&] (PVariant fieldWidget) mutable {
            PFieldWidget* fw = fieldWidget.value<PFieldWidget*>();
            delete fw;
        });
    });

    fieldWidgets = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
}


void PModel   ::initTableView() {PVariant _keys_0_ = pFields.keys();
for(int _i_0_ = 0; _i_0_ < _keys_0_.count(); _i_0_++) {
PString fieldName = _keys_0_[_i_0_].toString();
PVariant fieldAttrs = pFields.operator[](fieldName);
        if(fieldAttrs.include("system")) continue;
        fieldAttrs["tableView"].  undefined("visible=", false);
    }

}


void PModel   ::initFormView() {

       pFields.forEachQString_PVariant([&] (QString fieldName,PVariant fieldAttrs) mutable {
        fieldAttrs["tableView"].  undefined("visible=", false);
    });

}

PVariant PModel   ::newField(PVariant fieldAttrs) {

    QString fieldName = fieldAttrs.undefined("name", nil).toString();
    PVariant attrs = fieldAttr(fieldName);

    PVariant mask = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("totalizable", nil))));

    
    
    

    fieldAttrs.  undefined("label=", fieldAttrs.include("label") ? fieldAttrs.undefined("label", nil).toString() : fieldAttrs.undefined("name", nil).toString());

    fieldAttrs.  undefined("label=", fieldAttrs.undefined("label", nil).toString().capitalize(" "));

    if(!fieldAttrs.include("position")) fieldAttrs.  undefined("position=", this->fieldPosition++);

    fieldAttrs += (attrs & mask);

    return fieldAttrs;

}


void PModel   :: reduce(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "reduce:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant xmlViewRoot = source_args.value<PVariantMapPtr>()->include("xmlViewRoot") ? source_args.value<PVariantMapPtr>()->operator[]("xmlViewRoot") : nil;args.removeByKey("xmlViewRoot");
PVariant parent = source_args.value<PVariantMapPtr>()->include("parent") ? source_args.value<PVariantMapPtr>()->operator[]("parent") : nil;args.removeByKey("parent");
int childIndex = source_args.value<PVariantMapPtr>()->include("childIndex") ? source_args.value<PVariantMapPtr>()->operator[]("childIndex").toInt() : QVariant(-1).toInt();args.removeByKey("childIndex");


    PVariant newAttrs = nil;

    if(xmlViewRoot == nil) return;

    PString tag = xmlViewRoot.undefined("name", nil).toString();
    QString attrName = xmlViewRoot["attrs"]("name").toString();
    QString overload = xmlViewRoot["attrs"]("overload").toString();
    PVariant children = xmlViewRoot.undefined("children", nil);

    if(tag == "partial") {

        PVariant pathAndType = xmlViewRoot["attrs"]["ptr"].toString().split(":");
        QString path, type;
        path = pathAndType[0].toString();
        type = pathAndType[1].toString();

        PVariant partialNokogiriView = PViewLoader().viewByPath(path)->partialByType(type)->toVariant();

        this->   reduce(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("xmlViewRoot", partialNokogiriView)->append("parent", xmlViewRoot)))));

        PVariant partialChildren = partialNokogiriView.undefined("children", nil);
        int childIndex = parent.undefined("children", nil).indexOf(xmlViewRoot);
        parent["children"] = parent["children"].value<PVariantListPtr>()->mid2(0, childIndex) + partialChildren + parent["children"].value<PVariantListPtr>()->mid(childIndex+1, -1);

        return;
    }
    else if (!overload.isNull()) {

        PVariant parentChildren = parent.undefined("children", nil);

        PView view;
        PVariant children = view.     
                                           findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", tag)->append("attrs", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", attrName)))))))))->append("root", parentChildren)))));for(int _i_1_ = 0; _i_1_ < children.count(); _i_1_++) {
PVariant& child = children.operator[](_i_1_);
            if(child.undefined("attrs", nil). undefined("overload", nil)!= nil) continue;
            child["attrs"] += xmlViewRoot["attrs"];
            if(overload == "before") {
                child.  undefined("children=", xmlViewRoot. undefined("children", nil)+ PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append( child.dup())))));
                child.  undefined("name=", "to_collapse");
            }
            else if(overload == "after") {
                child.  undefined("children=",  PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(child.dup())))) + xmlViewRoot.undefined("children", nil));
                child.  undefined("name=", "to_collapse");
            }
            else if(overload == "remove") {
                child.  undefined("children=", nil);
                child.  undefined("name=", "to_collapse");
            }
            else if(overload == "inside") {
                child.  undefined("children=", xmlViewRoot.undefined("children", nil));
            }
            else if(overload == "replace") {
                child.  undefined("children=", xmlViewRoot.undefined("children", nil));
                child.  undefined("name=", "to_collapse");
            }
        }

        xmlViewRoot.  undefined("name=", "to_delete");
        return;

    }


       children.forEachWithIndexPVariant_int([&] (PVariant child,int i) mutable {
             reduce(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("xmlViewRoot", child)->append("parent", xmlViewRoot)->append("childIndex", i)))));
    });

    return;

}


void PModel   :: clean(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "clean:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant parent = source_args.value<PVariantMapPtr>()->include("parent") ? source_args.value<PVariantMapPtr>()->operator[]("parent") : nil;args.removeByKey("parent");


    PVariant children = parent.undefined("children", nil);
    for(int i = 0; i < children.count(); i++) {
        PVariant child = children[i];
        if(!child.include("name")) continue;
        if(child["name"] == "to_delete") children.removeByIndex(i--);

        if(child["name"] == "to_collapse") {

            PVariant grandChildren = child.undefined("children", nil);
            children.removeByIndex(i--);

             grandChildren.forEachPVariant([&] (PVariant grandChild) mutable {
                children.toList().insert(++i, grandChild);
            });


        }

    }

     children.forEachPVariant([&] (PVariant child) mutable {
         clean(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("parent", child)))));
    });

}






PVariant PModel   ::viewBy(PVariant attrs) {

    PViewLoader viewLoader;

    PView* view;

    if(attrs. undefined("path", nil)!= nil)
        view = viewLoader.viewByPath(attrs.undefined("path", nil).toString());
    else
        view = viewLoader.view(getModuleName(), toModelName());

    if(!view) return nil;

    if(attrs. undefined("type", nil)!= nil)
        view = view->partialByType(attrs.undefined("type", nil).toString());

    if(attrs. undefined("name", nil)!= nil)
        view = view->partialByName(attrs.undefined("name", nil).toString());

    if(!view) return nil;

    PVariant viewVariant = view->toVariant();

    if(viewVariant == nil) return nil;

     reduce(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("xmlViewRoot", viewVariant)))));
      clean(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("parent", viewVariant)))));

    QString viewStr = PView().variantToString(viewVariant );

    view->initByViewStr(viewStr);

    PLog().info() << view->toString();

    return viewVariant;

}


PVariant PModel   :: getView(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "getView:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString type = source_args.value<PVariantMapPtr>()->include("type") ? source_args.value<PVariantMapPtr>()->operator[]("type").toString() : QVariant(QString("form")).toString();args.removeByKey("type");


    PViewLoader viewLoader;

    PView* view = viewLoader.view(getModuleName(), toModelName());

    if(!view) return nil;

    view = view->partialByType(type);

    if(!view) return nil;

    PVariant viewVariant = view->toVariant();

    if(viewVariant == nil) return nil;

     reduce(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("xmlViewRoot", viewVariant)))));
      clean(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("parent", viewVariant)))));

    QString viewStr = PView().variantToString(viewVariant );

    view->initByViewStr(viewStr);

    PLog().info() << view->toString();

    return viewVariant;

}


bool PModel   ::isNumber(QString fieldType) {

  return ((fieldType == "integer" or fieldType == "float" or fieldType == "double"));

}


PVariant PModel   ::tableViewFields(const QString& viewType) {

    this->fieldPosition = 0;
    PVariant tableFields = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    PVariant viewVariant = this-> getView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", viewType)))));

    if(viewVariant != nil and !this->autoView) {
        PView view;
        view.initByViewVariant(viewVariant);
        PVariant xmlFields = view.  findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("field"))))))))));
         xmlFields.forEachPVariant([&] (PVariant xmlField) mutable {
            QString xmlFieldName = xmlField.undefined("attrs", nil).undefined("name", nil).toString();
            tableFields << newField(xmlField.undefined("attrs", nil));
        });
    }

    else { 
           pFields.forEachQString_PVariant([&] (QString fieldName,PVariant fieldAttrs) mutable {
            if(!systemFields().include(fieldName)) {
                if(!(fieldName.endsWith("_id") && isSubTable(fieldName))) { 
                   if(fieldName.endsWith("_id")) fieldName += ".name";
                   fieldAttrs.  undefined("name=", fieldName);
                   tableFields << newField(fieldAttrs);
                }
            }
        });
    }

    return    tableFields.sortPVariant_PVariant([&] (PVariant fieldA,PVariant fieldB) mutable { return fieldA.undefined("position", nil).toInt() < fieldB.undefined("position", nil).toInt(); });

}



bool PModel   ::isSubTable(QString fieldName) {

    bool result = domain.include(fieldName) || fieldAttr(fieldName).undefined("modelNameReference", nil).toString() == this->modelName;

    if(this->source)
        return result || this->source->isSubTable(fieldName);

    return result;

}


PVariant PModel   ::formViewFields(PVariant viewAttrs) {

    PVariant formView = viewBy(viewAttrs);

    if(formView != nil and !this->autoView)
        return formView;

    PVariant panels = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    PVariant tableFields = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    PVariant fields = pFields.dup();  

       fields.forEachQString_PVariant([&] (QString fieldName,PVariant fieldAttrs) mutable {
        if(!systemFields().include(fieldName)) {
            
            fieldAttrs.  undefined("name=", fieldName);
            if(fieldAttrs.undefined("type", nil).toString() == "oneToMany")
                panels << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("panel"))->append("attrs", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name",      fieldAttrs["label"])))))->append("children", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("field"))->append("attrs", fieldAttrs))))))))))));
            else if(!isSubTable(fieldName)) 
                tableFields << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("field"))->append("attrs", fieldAttrs))));
        }
    });

    PVariant layout = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("layout"))->append("children", tableFields))));

    PVariant tab = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("tab"))->append("children", panels))));

    PVariant children = panels.count() ? PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(layout)->append(tab)))) : PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(layout))));

    PVariant attrs = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("model", modelName)->append("type", QString("form"))->append("name", PString(QString("%1_form").arg(modelName))))));

    formView = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("view"))->append("attrs", attrs)->append("children", children))));

    return formView;



}


   #include "widgets/widgetedit/plineedit.h"
   #include "widgets/widgetedit/ptextedit.h"
   #include "widgets/widgetedit/pspinbox.h"
   #include "widgets/widgetedit/pplaintextedit.h"
   #include "widgets/widgetedit/pfiledialogedit.h"
   #include "widgets/widgetedit/pdirectorydialogedit.h"
   #include "widgets/widgetedit/pcoloredit.h"
   #include "widgets/widgetedit/pcombobox.h"
   #include "widgets/widgetedit/pcomboboxplus.h"
   #include "widgets/widgetedit/psqltextcombobox.h"
   #include "widgets/widgetedit/pcolorcombobox.h"
   #include "widgets/widgetedit/pdateedit.h"
   #include "widgets/widgetedit/ptimeedit.h"
   #include "widgets/widgetedit/pdatetimeedit.h"
   #include "widgets/widgetedit/pimageedit.h"
   #include "widgets/widgetedit/pcurrencyedit.h"
   #include "widgets/widgetedit/pbooledit.h"
   #include "widgets/widgetedit/psqlcombobox.h"
   #include "widgets/widgetedit/plabel.h"
   #include "widgets/widgetedit/pprogressbar.h"
   #include "widgets/widgetedit/pprogressbarplus.h"
   #include "widgets/widgetedit/pdashboard.h"
   #include "widgets/widgetedit/pswitchedit.h"
   #include "widgets/widgetedit/pxmlwidget.h"
   #include "widgets/sqlview/psqltableview.h"
   #include "widgets/sqlview/psqlgrouptableview.h"
   #include "widgets/sqlview/psqliconview.h"
   #include "widgets/sqlview/psqltabview.h"
   #include "widgets/sqlview/psqlbuttonview.h"
   #include "widgets/sqlview/psqlformviewdialog.h"
   #include "widgets/widgetedit/pcheckboxedit.h"
   #include "widgets/widgetedit/pradiobuttonedit.h"
   #include "widgets/widgetedit/pstateprogressbaredit.h"

PFieldWidget* PModel   ::getFieldWidget(const QString& fieldName) {

    return fieldWidgets[fieldName][0].value<PFieldWidget*>();

}

QLabel* PModel   ::getFieldLabel(const QString& fieldName) {

    return fieldLabels[fieldName];

}

PFieldWidget* PModel   ::fieldWidget(QString fieldName, QString fieldType, PVariant fieldAttrs, QWidget *parent,
                                    PMandatoryField* mandatoryField, QString mode) {

    PLog().error() <<  PString(QString("fieldName =====> %1 - %2").arg(fieldName).arg(fieldType)) << fieldAttrs.undefined("toolTip", nil).toString();

    PFieldWidget* fieldWidget = 0;

    if(fieldType == "text") {
        PLineEdit* lineEdit = new PLineEdit(parent);
        fieldWidget = lineEdit;
    }
    else if(fieldType == "text_edit")
        fieldWidget = new PTextEdit(parent);
    else if(fieldType == "plain_text_edit")
        fieldWidget = new PPlainTextEdit(parent);
    else if(fieldType == "combobox") { 
        PVariant iav = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
        if(fieldAttrs. undefined("toTranslate", nil) ==  "true") {
               fieldAttrs.
            undefined("itemsAndValues", nil).forEachQString_QString([&] (QString key,QString value) mutable {
                iav[key] = PTranslator::tr(value);
            });
        }
        else
            iav = fieldAttrs.undefined("itemsAndValues", nil);
        PComboBox* comboBox = new PComboBox(iav, parent);
        if(fieldAttrs. undefined("editable", nil)!= nil) comboBox->comboBox->setEditable(fieldAttrs.undefined("editable", nil).toBool());
        fieldWidget = comboBox;
    }
    else if(fieldType == "combobox_plus") { 
        PVariant iav = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
        if(fieldAttrs. undefined("toTranslate", nil) ==  "true") {
               fieldAttrs.
            undefined("itemsAndValues", nil).forEachQString_QString([&] (QString key,QString value) mutable {
                iav[key] = PTranslator::tr(value);
            });
        }
        else
            iav = fieldAttrs.undefined("itemsAndValues", nil);
        PComboBoxPlus* comboBox = new PComboBoxPlus(iav, parent);
        fieldWidget = comboBox;
    }
    else if(fieldType == "sqltextcombobox") {
        PModelPtr model = this->newPModel(fieldAttrs.undefined("modelName", nil).toString());
        fieldWidget = new  
                                        
                                            PSqlTextComboBox(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("model",   model.toVariant())->append("fieldAttrs", fieldAttrs)->append("parent",   
                                        
                                            QVariant::fromValue(parent))))));
        model->setParent(fieldWidget); 
    }
    else if(fieldType == "checkbox") {
        PCheckBoxEdit* checkBoxEdit = new PCheckBoxEdit(fieldAttrs.undefined("itemsAndValues", nil), parent);
        checkBoxEdit->setMandatory(fieldAttrs.undefined("mandatory", nil).toInt());
        fieldWidget = checkBoxEdit;
    }
    else if(fieldType == "radiobutton")
        fieldWidget = new PRadioButtonEdit(fieldAttrs.undefined("itemsAndValues", nil), parent);
    else if(fieldType == "spinbox") {
        PSpinBox* spinBox = new PSpinBox(parent);
        fieldWidget = spinBox;
    }
    else if(fieldType == "file_dialog_edit")
        fieldWidget = new PFileDialogEdit(parent);
    else if(fieldType == "directory_dialog_edit")
        fieldWidget = new PDirectoryDialogEdit(parent);
    else if(fieldType == "color_edit")
        fieldWidget = new PColorEdit(parent);
    else if(fieldType == "color_combobox")
        fieldWidget = new PColorComboBox(parent);
    else if(fieldType == "image_edit")
        fieldWidget = new PImageEdit(parent);
    else if(fieldType == "currency_edit")
        fieldWidget = new PCurrencyEdit(parent);
    else if(fieldType == "integer")
        fieldWidget = new PLineEdit(parent);
    else if(fieldType == "float")
        fieldWidget = new PLineEdit(parent);
    else if(fieldType == "date")
        fieldWidget = new PDateEdit(parent);
    else if(fieldType == "time")
        fieldWidget = new PTimeEdit(parent);
    else if(fieldType == "datetime")
        fieldWidget = new PDateTimeEdit(parent);
    else if(fieldType == "bool") {
        PBoolEdit* boolEdit = new PBoolEdit(parent);
        fieldWidget = boolEdit;
    }
    else if(fieldType == "switch_edit") {
        PSwitchEdit* switchEdit = new PSwitchEdit(parent);
        fieldWidget = switchEdit;
    }
    else if(fieldType == "progress_bar")
        fieldWidget = new PProgressBar(parent);
    else if(fieldType == "progress_bar_plus") {
        PProgressBarPlus* progressBarPlus = new PProgressBarPlus(parent);
        fieldWidget = progressBarPlus;
    }
    else if(fieldType == "dashboard") {
        PDashboard* dashboard = new PDashboard(parent);
        fieldWidget = dashboard;
    }

    else if(fieldType == "state_progress_bar") {
        PStateProgressBarEdit* stateProgressBarEdit = new PStateProgressBarEdit(parent);
        stateProgressBarEdit->stateProgressBar->model = this;
        fieldWidget = stateProgressBarEdit;
    }

    else if(fieldType == "label" or fieldType == "virtual")
        fieldWidget = new PLabel(parent);

    else if(fieldType == "widget") {
        fieldWidget = new PXmlWidget(this, mandatoryField, mode, fieldAttrs, parent);
    }

    else if(fieldType == "manyToOne" || fieldType == "oneToOne") {
        PModelPtr model = this->newPModel(fieldAttrs.undefined("modelNameReference", nil).toString());
        fieldWidget = new  
                                   
                                   PSqlComboBox(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("model",   model.toVariant())->append("fieldAttrs", fieldAttrs)->append("parent",   
                                   
                                   QVariant::fromValue(parent))))));
        model->setParent(fieldWidget); 
    }

    else if(fieldType == "button_table") {

        QString modelName = fieldAttrs.undefined("modelNameReference", nil).toString();

        PSqlButtonView* sqlButtonView = new  
                                                               
                                                               PSqlButtonView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("attrs", fieldAttrs)->append("parent",   
                                                               
                                                               QVariant::fromValue(parent))))));
        
        fieldWidget = sqlButtonView;
    }

    else if(fieldType == "tab_table") {

        QString modelName = fieldAttrs.undefined("modelNameReference", nil).toString();

        PSqlTabView* sqlTabView = new  
                                                               
                                                               
                                                               PSqlTabView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("attrs", fieldAttrs)->append("parent",   
                                                               
                                                               QVariant::fromValue(parent))))));
        fieldWidget = sqlTabView;
    }

    else if(fieldType == "oneToMany") {
        QString modelName = fieldAttrs.undefined("modelNameReference", nil).toString();
        QString referenceFieldName = fieldAttrs.undefined("referenceFieldName", nil).toString();
        PLog().debug() << "- - - - - - ->" << fieldName << modelName << referenceFieldName;
        PModelPtr model = this->oneToMany(fieldName, modelName, referenceFieldName);
        PSqlTableView* sqlTableView = new  
                                                            
                                                            PSqlTableView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("model",   
                                                            model.toVariant())->append("parent",   
                                                            
                                                            QVariant::fromValue(parent))))));
        
        sqlTableView->setLayoutDirection(Qt::LeftToRight);
        
        fieldWidget = sqlTableView;
    }

    else if(fieldType == "icon_view") {
        QString modelName = fieldAttrs.undefined("modelNameReference", nil).toString();
        QString referenceFieldName = fieldAttrs.undefined("referenceFieldName", nil).toString();
        PLog().debug() << "- - - - - - ->" << fieldName << modelName << referenceFieldName;
        PModelPtr model = this->oneToMany(fieldName, modelName, referenceFieldName);
        PSqlIconView* sqlIconView = new  
                                                         
                                                         
                                                         PSqlIconView(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)->append("model",   
                                                         model.toVariant())->append("parent",   
                                                         
                                                         QVariant::fromValue(parent))->append("attrs", fieldAttrs)))));
        model->setParent(sqlIconView); 
        sqlIconView->setLayoutDirection(Qt::LeftToRight);
        fieldWidget = sqlIconView;
    }

    else {

        PLog().error() << "PModel::fieldWidget:" << fieldType << "doesn't exist";
        return 0;

    }

    fieldWidget->setToolTip(PTranslator::tr(fieldAttrs.undefined("toolTip", nil).toString()));
    fieldWidget->setAttrs(fieldAttrs);

    return fieldWidget;

}


void PModel   ::toWidget(PVariant parentView, QWidget* parentWidget, QGridLayout* parentGridLayout,
                        PMandatoryField* mandatoryField, QString mode,
                        int row, int col,
                        Qt::Orientation arrangement, Qt::Alignment alignment) {

    if(parentView == nil) return;

    QString tagName = parentView.undefined("name", nil).toString();
    PVariant attrs = parentView.undefined("attrs", nil);
    PVariant children = parentView.undefined("children", nil);

    if(attrs. undefined("arrangement", nil)!= nil)
        arrangement = (attrs.undefined("arrangement", nil).toString().toLower() == "vertical") ? Qt::Vertical : Qt::Horizontal;

    alignment = PWidgetAttrs::alignmentFromString(attrs.undefined("alignment", nil).toString());

    if(tagName == "view") {
    }

    else if(tagName == "layout") {
        QWidget* blockWidget = new QWidget(parentWidget);
        QGridLayout* gridLayout = new QGridLayout(blockWidget);
        if(attrs. undefined("name", nil)!= nil) {
            blockWidget->setObjectName(attrs.undefined("name", nil).toString() + "Widget");
            gridLayout->setObjectName(attrs.undefined("name", nil).toString() + "GridLayout");
        }
        parentGridLayout->addWidget(blockWidget, row, col);
        parentGridLayout = gridLayout;
        PWidgetAttrs::setLayout(gridLayout, attrs);
        PWidgetAttrs::setWidget(blockWidget, attrs);
    }

    else if(tagName == "group") {
        QString label = attrs. undefined("label", nil)!= nil ? attrs.undefined("label", nil).toString() : " ";
        QGroupBox* groupBox = new QGroupBox(label, parentWidget);
        QGridLayout* groupGridLayout = new QGridLayout(groupBox);
        groupBox->setCheckable(true);
        groupBox->setChecked(attrs.undefined("checked", nil).toBool());

        QWidget* blockWidget = new QWidget(groupBox);
        groupGridLayout->addWidget(blockWidget);

        QGridLayout* gridLayout = new QGridLayout(blockWidget);
        if(attrs. undefined("name", nil)!= nil) {
            blockWidget->setObjectName(attrs.undefined("name", nil).toString() + "Widget");
            gridLayout->setObjectName(attrs.undefined("name", nil).toString() + "GridLayout");
        }
        parentGridLayout->addWidget(groupBox, row, col);
        parentGridLayout = gridLayout;
        PWidgetAttrs::setLayout(gridLayout, attrs);
        PWidgetAttrs::setWidget(groupBox, attrs);
    }

    else if(tagName == "tab") {
        parentWidget = new QTabWidget(parentWidget);
        
        parentWidget->setLayoutDirection(this->tabLayoutDirection);
        parentGridLayout->addWidget(parentWidget, row, col);

        if(attrs. undefined("name", nil)!= nil) {
            PSinglUserManager::instance()->setObjectName(parentWidget, PString(QString("%1Widget").arg(attrs.undefined("name", nil).toString())));
            parentGridLayout->setObjectName(attrs.undefined("name", nil).toString() + "GridLayout");
        }

    }
    else if(tagName == "panel") {
        QWidget* tabWidget = new QWidget(parentWidget);
        PWidgetAttrs::setBackgroundColor(tabWidget, PGlobal::windowColor());
        tabWidget->setMinimumHeight(250);
        ((QTabWidget*)parentWidget)->addTab(tabWidget, PTranslator::tr(attrs.undefined("name", nil).toString()));
        QGridLayout* gridLayout = new QGridLayout();
        tabWidget->setLayout(gridLayout);
        parentGridLayout = gridLayout;

        if(attrs. undefined("name", nil)!= nil) {
            PSinglUserManager::instance()->setObjectName(tabWidget, PString(QString("%1Widget").arg(attrs.undefined("name", nil).toString())));
            parentGridLayout->setObjectName(attrs.undefined("name", nil).toString() + "GridLayout");
        }

    }

    else if(tagName == "menusection") {
        
        int _col = col;
        int _row = row;
        if(attrs.include("label")) {
            QLabel* label = new QLabel(PTranslator::tr(attrs.undefined("label", nil).toString()), parentWidget);
            if(arrangement == Qt::Vertical) {
                parentGridLayout->addWidget(label, row * 2, col);
                _row = row * 2 + 1;
            }
            else {
                parentGridLayout->addWidget(label, row, col * 2);
                _col = col * 2 + 1;
            }
        }
        

        PActionButtons* buttons = new PActionButtons(parentWidget);
        connect(buttons, SIGNAL(click(PVariant)), this, SLOT(onClick(PVariant)));
        buttons->initByXml(parentView.undefined("children", nil));
        parentGridLayout->addWidget(buttons, _row, _col);
        PWidgetAttrs::setLayout(parentGridLayout, attrs);
        PWidgetAttrs::setWidget(buttons, attrs);
        return;
    }

    else if(tagName == "label") {
        if(attrs == nil) return;
        QWidget* blockWidget = new QWidget(parentWidget);
        QGridLayout* gridLayout = new QGridLayout(blockWidget);
        gridLayout->setContentsMargins(0,0,0,0);

        QString fieldName = attrs.undefined("name", nil).toString();
        QString fieldLabel = PTranslator::tr(attrs.undefined("label", nil).toString());
        QLabel* label = new QLabel(fieldLabel, blockWidget);

        if(attrs. undefined("icon", nil)!= nil) {
            PImage image(attrs.undefined("icon", nil).toString());
            if(attrs. undefined("size", nil)!= nil) {
                PVariant size = PVariant::fromString(attrs.undefined("size", nil).toString());
                image = image.scaled(QSize(size.undefined("0", nil).toInt(), size.undefined("1", nil).toInt()), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            }
            if(attrs. undefined("hs", nil)!= nil) {
                PVariant hs = PVariant::fromString(attrs.undefined("hs", nil).toString());
                image.setHS(hs.undefined("0", nil).toInt(), hs.undefined("1", nil).toInt());
            }

            label->setPixmap(image.toPixmap());

        }


        PWidgetAttrs::setWidget(label, attrs);
        label->setAlignment(alignment);
        gridLayout->addWidget(label, 0, 0);
        fieldLabels[fieldName] = label;
        label->setObjectName(PString(QString("%1Label").arg(fieldName)));

        if(arrangement == Qt::Vertical)
            parentGridLayout->addWidget(blockWidget, row * 2 + 1, col);
        else
            parentGridLayout->addWidget(blockWidget, row, col * 2 + 1);
    }

    
    else if(tagName == "separator") {
        QFrame* separatorFrame = new QFrame(parentWidget);
        separatorFrame->setFrameShape(QFrame::HLine);
        separatorFrame->setFrameShadow(QFrame::Sunken);
        int h = attrs.undefined("height", nil).toInt();
        if(h == 0) h = 20;
        separatorFrame->setFixedHeight(h);

        if(arrangement == Qt::Vertical)
            parentGridLayout->addWidget(separatorFrame, row * 2 + 1, col);
        else
            parentGridLayout->addWidget(separatorFrame, row, col * 2 + 1);
    }

    else if(tagName == "vseparator") {
        QFrame* separatorFrame = new QFrame(parentWidget);
        separatorFrame->setFrameShape(QFrame::VLine);
        separatorFrame->setFrameShadow(QFrame::Sunken);
        int w = attrs.undefined("width", nil).toInt();
        if(w == 0) w = 2;
        separatorFrame->setFixedWidth(w);

        if(arrangement == Qt::Vertical)
            parentGridLayout->addWidget(separatorFrame, row * 2 + 1, col);
        else
            parentGridLayout->addWidget(separatorFrame, row, col * 2 + 1);
    }

    else if(tagName == "field") {
        if(attrs == nil) return;
        QLabel* label;
        QString fieldName = attrs.undefined("name", nil).toString();
        
        
        PVariant fieldAttrs = fieldAttr(fieldName.split(".")[0]) + attrs;
        fieldAttrs = newField(fieldAttrs);
        QString fieldLabel = PTranslator::tr(fieldAttrs.undefined("label", nil).toString());
        QString fieldType = (fieldAttrs.include("fieldType")) ? fieldAttrs.undefined("fieldType", nil).toString() : fieldAttrs.undefined("type", nil).toString();
        bool mandatory = (fieldAttrs.include("mandatory") and fieldAttrs.undefined("mandatory", nil).toBool());

        if(fieldType != "oneToMany" &&
           fieldType != "icon_view" &&
           fieldLabel.toLower() != "false") { 
            label = new QLabel(fieldLabel, parentWidget);
            label->setToolTip(PTranslator::tr(fieldAttrs.undefined("toolTip", nil).toString()));
            label->setFont(PGlobal::widgetFont());
            label->setAlignment(alignment);
            fieldLabels[fieldName] = label;
            label->setObjectName(PString(QString("%1Label").arg(fieldName)));

            if(arrangement == Qt::Vertical)
                parentGridLayout->addWidget(label, row * 2, col);
            else
                parentGridLayout->addWidget(label, row, col * 2);
        }

        PFieldWidget* fieldEdit = fieldWidget(fieldName, fieldType, fieldAttrs, parentWidget, mandatoryField, mode);
        if(fieldAttrs. undefined("alignment", nil)!= nil)
            fieldEdit->layout()->setAlignment(PWidgetAttrs::alignmentFromString(attrs.undefined("alignment", nil).toString()));


        if(fieldAttrs("readOnly") != nil)
            if(fieldAttrs.undefined("readOnly", nil).toBool()) 
                fieldEdit->setReadOnly(fieldAttrs.undefined("readOnly", nil).toBool());

        if(fieldAttrs("enabled") != nil)
            fieldEdit->setEnabled(fieldAttrs.undefined("enabled", nil).toBool());

        if(fieldAttrs("visible") != nil) {
            label->setVisible(fieldAttrs.undefined("visible", nil).toBool());
            fieldEdit->setVisible(fieldAttrs.undefined("visible", nil).toBool());
        }

        
        if(fieldAttrs. undefined("main", nil)!= nil) {
            QWidget* lineEdit = dynamic_cast<QWidget*>(fieldEdit->mainWidget());
            QFont font = PGlobal::mainFieldFont();
            if(fieldAttrs.undefined("main", nil). undefined("fontSize", nil)!= nil)
                font.setPixelSize(fieldAttrs.undefined("main", nil).undefined("fontSize", nil).toInt());

            if(fieldAttrs.undefined("main", nil). undefined("bold", nil)!= nil)
                font.setBold(fieldAttrs.undefined("main", nil).undefined("bold", nil).toBool());

            if(fieldAttrs.undefined("main", nil). undefined("fontFamily", nil)!= nil)
                font.setFamily(fieldAttrs.undefined("main", nil).undefined("fontFamily", nil).toString());

            lineEdit->setFont(font);
            label->setFont(font);
        }

        PWidgetAttrs::setWidget(fieldEdit, attrs);

        QWidget* mw = fieldEdit->mainWidget() ? fieldEdit->mainWidget() : fieldEdit;
        PSinglUserManager::instance()->setObjectName(mw, PString(QString("%1FieldEdit").arg(fieldName)));

        if(!fieldWidgets.include(fieldName)) fieldWidgets[fieldName]= PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
        
        fieldWidgets[fieldName] << QVariant::fromValue(fieldEdit);
        if(!fieldEdit) return;
        fieldEdit->fieldName = fieldName;
        connect(fieldEdit, SIGNAL(dataChanged(QString, PVariant)), this, SLOT(dataChanged(QString, PVariant)));
        connect(fieldEdit, SIGNAL(editingFinished(QString, PVariant)), this, SLOT(editingFinished(QString, PVariant)));
        fieldEdit->setData(this->fieldValue(fieldName));
        if(mandatory) mandatoryField->add(fieldEdit);

        if(arrangement == Qt::Vertical)
            parentGridLayout->addWidget(fieldEdit, row * 2 + 1, col);
        else
            parentGridLayout->addWidget(fieldEdit, row, col * 2 + 1);

    }

    int r = 0, c = 0;
     children.forEachPVariant([&] (PVariant child) mutable {
        QString newLine;
        if(child. undefined("attrs", nil)!= nil) newLine = child.undefined("attrs", nil).undefined("newline", nil).toString();

        this->toWidget(child, parentWidget, parentGridLayout, mandatoryField, mode, r, c, arrangement, alignment);
        if(newLine != "false") r++, c = 0;
        else c++;
    });

}




void PModel   ::initTabOrder() {

    if(tabOrderFromCpp == false) return;

    PVariant widgets = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

         pFields.forEachWithIndexQString_PVariant_int([&] (QString fieldName,PVariant fieldValue,int i) mutable {
        PVariant widgetList = fieldWidgets[fieldName];
         widgetList.forEachPVariant([&] (PVariant fieldWidget) mutable {
            int tabOrder = (fieldValue("tabOrder") != nil) ? fieldValue.undefined("tabOrder", nil).toInt() : i;
            if(fieldValue("readOnly") == nil || fieldValue("readOnly") == false)  
                widgets << PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tabOrder", tabOrder)->append("fieldName", fieldName)->append("fw", fieldWidget))));
        });
    });

    widgets = widgets.quicksort( PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("tabOrder"))))));

    QWidget* prevFieldEdit = 0;
       widgets.forEachWithIndexPVariant_int([&] (PVariant elem,int i) mutable {
        

        QWidget* currentFieldEdit = elem.undefined("fw", nil).value<PFieldWidget*>()->mainWidget();

        if(i == 0)
            prevFieldEdit = currentFieldEdit;

        else if(prevFieldEdit && currentFieldEdit) {
            QWidget::setTabOrder(prevFieldEdit, currentFieldEdit);
            prevFieldEdit = currentFieldEdit;
        }

    });

}


void PModel   ::dataChanged(QString fieldName, PVariant data) {

    if(!this->dataChangedConnection)
        return;

    if(!this->lockedDataChanged) {
        this->setFieldValue(fieldName, data);
        this->onDataChanged(fieldName, data);
        this->reloadFieldWidget(fieldName);
    }

}

void PModel   ::editingFinished(QString fieldName, PVariant fieldValue) {

    if(!this->lockedDataChanged) {
        this->setFieldValue(fieldName, fieldValue);
        this->onChangeField(fieldName, fieldValue);
        this->reloadFieldWidget(fieldName);
    }

}


void PModel   ::onChangeField(QString fieldName, PVariant fieldValue) {
}

void PModel   ::onDataChanged(QString fieldName, PVariant data) {

}

void PModel   ::onCurrentRecordChanged(const QString& id) {

}

void PModel   ::reloadParentFieldWidget() {

    if(!source) return;PVariant _keys_2_ = source->pFields.keys();
for(int _i_2_ = 0; _i_2_ < _keys_2_.count(); _i_2_++) {
PString fieldName = _keys_2_[_i_2_].toString();
PVariant field = source->pFields.operator[](fieldName);
        if(field.undefined("modelNameReference", nil).toString() == modelName) {
            source->reloadFieldWidget(fieldName);
            source->onChangeField(fieldName, nil);
        }
    }

}

void PModel   ::reloadFieldWidget(QString fieldName) {

    if(fieldWidgets.include(fieldName)) {
        PVariant value = fieldValue(fieldName);
        PVariant widgetList = fieldWidgets[fieldName];
         widgetList.forEachPVariant([&] (PVariant fieldWidget) mutable {
            PFieldWidget* fw = fieldWidget.value<PFieldWidget*>();
            if(fw->data() != value)
                fw->setData(value);
        });
    }

    

}

void PModel   ::reloadFieldWidget() {

       pFields.forEachQString_PVariant([&] (QString fieldName,PVariant fieldValue) mutable {
        reloadFieldWidget(fieldName);
    });

}


void PModel   ::onClick(PVariant button) {

    PVariant formView = viewBy( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("form"))))));

    if(formView == nil)
        formView = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("attrs", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", QString("form")))))))));

    if(button.undefined("askConfirm", nil).toString() != "") {
        QString question = PTranslator::tr(button.undefined("askConfirm", nil).toString());
        if(PMMessageBox:: 
                                      
                                         messageBox(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("text", question)->append("icon", QString("picons/core/actions-128/stop.png"))->append("ok", true)->append("cancel", true)))))== QDialog::Rejected)
            return;
    }

    {
    PVariant ids = this->sqlView->idSelectionList();
    QString currentId = "0";
    if(ids.count()) currentId = ids[0].toString();
    Plus4LogManager:: 
                            
                            log(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("action", button. undefined("action", nil))->append("model_name", modelName)->append("id_value", currentId)))));
    }


    if(button.undefined("action", nil).toString() == "new") {
        PModelPtr nvr = create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));  
        PSqlFormViewDialog formViewDialog(this->toRecordPtr(), "new", formView.undefined("attrs", nil));
        if(showFullScreen) formViewDialog.showFullScreen();
        if(formViewDialog.exec() == QDialog::Accepted) {
            if(this->sqlView) {
                this->sqlView->addCurrentRecord();
                this->sqlView->onEditingFinished();
                this->sqlView->selectLastItem();
            }
        }
        else {
            remove(QVariant::fromValue(nvr));
            PVariant ids = this->sqlView->idSelectionList();
            if(ids.count() > 0)
                this->sqlView->selectItemById(ids.undefined("0", nil).toString());
        }

    }
    else if(button.undefined("action", nil).toString() == "edit") {

        PVariant ids = this->sqlView->idSelectionList();

        if(ids.count() == 0)
            return;

        PSqlFormViewDialog formViewDialog(this->toRecordPtr(), "edit", formView.undefined("attrs", nil));
        if(showFullScreen) formViewDialog.showFullScreen();
        formViewDialog.exec();
        this->sqlView->reloadCurrentRecord();
        this->sqlView->onEditingFinished();
        this->sqlView->selectItemById(ids.undefined("0", nil).toString());

    }

    else if(button.undefined("action", nil).toString() == "delete") {

        PVariant selectedRows = this->sqlView->selectedRows();

        if(selectedRows.count() == 0)
            return;

        int row = selectedRows[0].toInt();

        if(row == this->sqlView->count() - 1)
            row--;

        PVariant ids = this->sqlView->idSelectionList();
         remove(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", ids)))));
        this->onDelete(ids);

        if(this->level == 0)
            this->writeAllRecords();

        this->sqlView->removeItem(-1);

        this->sqlView->onEditingFinished();

        this->sqlView->selectItem(row);


    }

    else if(button.undefined("action", nil).toString() == "duplicate") {

        PVariant ids = this->sqlView->idSelectionList();

        if(ids.count() == 0)
            return;

        PModelPtr newRecord = this->dup()->writeAllRecords();

        this->psql->table << newRecord->current();

        this-> setTableCursorBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", newRecord-> undefined("id", nil))))));

        

        this->sqlView->addCurrentRecord(this->sqlView->selectedRows()[0].toInt() + 1);

        this->sqlView->onEditingFinished();

        this->sqlView->selectItemById(newRecord->undefined("id", nil).toString());

    }


    else if(button.undefined("action", nil).toString() == "up") {

        PVariant selectedRows = this->sqlView->selectedRows();

        if(selectedRows.count() == 0)
            return;

        int currentRow = psql->tableIndex;
        if(currentRow == 0)
            return;

        int row = selectedRows[0].toInt();

        this->sqlView->swapItems(row, row - 1);

        PVariant curr = psql->table[currentRow];
        PVariant prev = psql->table[currentRow - 1];

        PVariant tmp = this->undefined("ordering", nil);
        this->  undefined("ordering=", prev["ordering"]);
        this->sqlView->reloadCurrentRecord();
        this->prev();
        this->  undefined("ordering=", tmp);
        this->sqlView->reloadCurrentRecord();

        psql->table[currentRow] = prev;
        psql->table[currentRow - 1] = curr;

        if(this->level == 0)
            this->saveAllRecords();

        

        this->sqlView->onEditingFinished();

        this->sqlView->selectItemById(curr.undefined("id", nil).toString());

    }

    else if(button.undefined("action", nil).toString() == "down") {

        PVariant selectedRows = this->sqlView->selectedRows();

        if(selectedRows.count() == 0)
            return;

        int currentRow = psql->tableIndex;
        if(currentRow >= psql->table.count() - 1)
            return;

        int row = selectedRows[0].toInt();

        this->sqlView->swapItems(row, row + 1);

        PVariant curr = psql->table[currentRow];
        PVariant next = psql->table[currentRow + 1];

        PVariant tmp = this->undefined("ordering", nil);
        this->  undefined("ordering=", next["ordering"]);
        this->sqlView->reloadCurrentRecord();
        this->next();
        this->  undefined("ordering=", tmp);
        this->sqlView->reloadCurrentRecord();

        psql->table[currentRow] = next;
        psql->table[currentRow + 1] = curr;

        if(this->level == 0)
            this->saveAllRecords();

        

        this->sqlView->onEditingFinished();

        this->sqlView->selectItemById(curr.undefined("id", nil).toString());

    }

    else if(button.undefined("action", nil).toString() == "prev") {

        if(prev() == nil) first();
        this->sqlView->reload();

    }

    else if(button.undefined("action", nil).toString() == "next") {

        if(next() == nil) last();
        this->sqlView->reload();

    }

    else if(button.undefined("action", nil).toString() == "dump") {
        this->dump();
    }

    else if(button.undefined("action", nil).toString() == "exportCSV") {

        PFileDialogEdit fde;
        QString fileName = fde.selectionFile();
        if(!fileName.isNull() ) {
            PFieldSelector fieldSelectorDialog;
            fieldSelectorDialog.initListWidget(this);
            if(fieldSelectorDialog.exec() == QDialog::Accepted) {
                this->   exportCSV(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fileName", fileName)->append("fields",    fieldSelectorDialog.selectedFields())))));
            }
        }

    }

    
    else {
        PVariant result = this->action(button);

        if(result == nil) return;

        if(result.undefined("type", nil).toString() == "message_box") {
            messageBox(result);
            if(result.undefined("action", nil).toString() == "reload_table") this->sqlView->reload();
            if(result.undefined("action", nil).toString() == "reload_current") this->sqlView->reloadCurrentRecord();
        }
        else if(result.undefined("type", nil).toString() == "message_box") {
            messageBox(result);
            if(result.undefined("action", nil).toString() == "reload_curent") this->sqlView->reloadCurrentRecord();
        }
        else if(result.undefined("type", nil).toString() == "action" && result.undefined("action", nil).toString() == "reload") {
            reloadFieldWidget();
        }
        else if(result.undefined("type", nil).toString() == "action" && result.undefined("action", nil).toString() == "reload_table") {
            this->sqlView->reload();
        }
        else if(result.undefined("type", nil).toString() == "action" && result.undefined("action", nil).toString() == "reload_current") {
            this->sqlView->reloadCurrentRecord();
        }
    }

}

void PModel   ::initDialog() {

    this->dialogMode = true;
    PModelPtr nvr = create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));  
    new PSqlFormViewDialog(this->toRecordPtr(), "edit");

}



int PModel   ::exec() {

    if(sqlFormViewDialog == 0) {
        PLog().error() << "PModel::exec() - correct syntax: call messageBox.initDialog();";
        return 0;
    }

    if(showFullScreen) sqlFormViewDialog->showFullScreen();
    int result = sqlFormViewDialog->exec();
    delete sqlFormViewDialog;
    return result;

}

void PModel   ::messageBox(PVariant message) {

    PMMessageBox::messageBox(message);

}


void PModel   :: setFieldWidget(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "setFieldWidget:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString fieldName = source_args.value<PVariantMapPtr>()->include("fieldName") ? source_args.value<PVariantMapPtr>()->operator[]("fieldName").toString() : QVariant(nil).toString();args.removeByKey("fieldName");
int fontSize = source_args.value<PVariantMapPtr>()->include("fontSize") ? source_args.value<PVariantMapPtr>()->operator[]("fontSize").toInt() : QVariant(-1).toInt();args.removeByKey("fontSize");
bool bold = source_args.value<PVariantMapPtr>()->include("bold") ? source_args.value<PVariantMapPtr>()->operator[]("bold").toBool() : QVariant(false).toBool();args.removeByKey("bold");
QString fontFamily = source_args.value<PVariantMapPtr>()->include("fontFamily") ? source_args.value<PVariantMapPtr>()->operator[]("fontFamily").toString() : QVariant(nil).toString();args.removeByKey("fontFamily");


    PLineEdit* fieldWidget = dynamic_cast<PLineEdit*>(getFieldWidget(fieldName));
    QFont font = fieldWidget->lineEdit->font();

    if(!fontFamily.isNull())
        font.setFamily(fontFamily);
    if(fontSize != -1)
        font.setPixelSize(fontSize);
    if(bold)
        font.setBold(true);

    fieldWidget->lineEdit->setFont(font);

    QLabel* fieldLabel = dynamic_cast<QLabel*>(getFieldLabel(fieldName));
    fieldLabel->setFont(font);

}


QWidget* PModel   ::controlPanelWidget() {

    return 0;

}
