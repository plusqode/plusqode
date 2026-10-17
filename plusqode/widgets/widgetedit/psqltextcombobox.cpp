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





   #include "widgets/widgetedit/psqltextcombobox.h"



   


   
   #include "app/modules/pmodules.h"



   


   
   


   
   
 



PSqlTextComboBox:: PSqlTextComboBox(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PSqlTextComboBox:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PModelPtr model = source_args.value<PVariantMapPtr>()->operator[]("model").value<PModelPtr>();
args.removeByKey("model");
PVariant fieldAttrs = source_args.value<PVariantMapPtr>()->include("fieldAttrs") ? source_args.value<PVariantMapPtr>()->operator[]("fieldAttrs") : nil;args.removeByKey("fieldAttrs");
QString label = source_args.value<PVariantMapPtr>()->include("label") ? source_args.value<PVariantMapPtr>()->operator[]("label").toString() : QVariant(nil).toString();args.removeByKey("label");
int dialogLevel = source_args.value<PVariantMapPtr>()->include("dialogLevel") ? source_args.value<PVariantMapPtr>()->operator[]("dialogLevel").toInt() : QVariant(0).toInt();args.removeByKey("dialogLevel");
QWidget* parent = source_args.value<PVariantMapPtr>()->include("parent") ? source_args.value<PVariantMapPtr>()->operator[]("parent").value<QWidget*>() : 0;
args.removeByKey("parent");


    setParent(parent);

    this->fieldAttrs = fieldAttrs;

    PVariant showField = fieldAttrs.undefined("showField", nil);
    PVariant sortField = fieldAttrs.undefined("sortField", nil);
    int selectedItemId = fieldAttrs.undefined("value", nil).toInt();

    this->model = model;

    if(showField.isNull()) showField = model->showField;
    this->showField = PVariant::fromString(showField.toString());

    
    this->sortField = (sortField == nil) ? model->sortField : PVariant::fromString(sortField.toString()); 

    this->label = label;
    this->selectedItemId = selectedItemId;
    this->dialogLevel = dialogLevel;

    comboBoxLock = false;

    comboBox = new QComboBox(this);
    comboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    comboBox->setMinimumHeight(PGlobal::fieldMinimumHeight());
    comboBox->setFont(PGlobal::widgetFont());
    if(fieldAttrs.undefined("editable", nil).toString() != "false") comboBox->setEditable(true);
    
    
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onEditingFinished(int)));
    connect(comboBox, SIGNAL(editTextChanged(QString)), this, SLOT(onEditingFinished_QString(QString)));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(comboBox, 0, 0);

    PModelPtr modelProfile = PSinglUserManager::instance()->modelProfile(model->modelName);

    newButton = 0;
    editButton = 0;

    if(fieldAttrs.undefined("editButton", nil).toString() != "false")
    if(modelProfile == nil or modelProfile->undefined("edit_record", nil).toBool()) {
        editButton = new QToolButton(this);
        PSinglUserManager::instance()->setObjectName(editButton, PString(QString("%1EditButton").arg(fieldAttrs.undefined("name", nil).toString())));
        editButton->setIcon(QIcon(":/picons/core/actions/edit.png"));
        connect(editButton, SIGNAL(clicked()), this, SLOT(onEdit()));
        layout->addWidget(editButton, 0, 1);
    }

    if(fieldAttrs.undefined("newButton", nil).toString() != "false")
    if(modelProfile == nil or modelProfile->undefined("new_record", nil).toBool()) {
        newButton = new QToolButton(this);
        PSinglUserManager::instance()->setObjectName(newButton, PString(QString("%1NewButton").arg(fieldAttrs.undefined("name", nil).toString())));
        newButton->setIcon(QIcon(":/picons/core/actions/new.png"));
        connect(newButton, SIGNAL(clicked()), this, SLOT(onNew()));
        layout->addWidget(newButton, 0, 2);
    }

    populateList();

}


QWidget* PSqlTextComboBox::mainWidget() {

    return comboBox;

}


PSqlTextComboBox::~PSqlTextComboBox() {


}


PVariant PSqlTextComboBox::data() {

    return comboBox->currentText();

}

void PSqlTextComboBox::setData(PVariant data) {

    comboBox->setEditText(data.toString());

}

void PSqlTextComboBox::setBackgroundColor(QString color) {

    

    QPalette pal = comboBox->palette();
    pal.setColor(comboBox->backgroundRole(), color);
    comboBox->setPalette(pal);

    

}

void PSqlTextComboBox::setReadOnly(bool value) {

    comboBox->setEnabled(!value);
    comboBox->setStyleSheet(PString(QString("QComboBox {color: black;}")));
    if(newButton) newButton->setHidden(value);
    if(editButton) editButton->setHidden(value);

}

bool PSqlTextComboBox::isEmpty() {

    return comboBox->currentText().isEmpty();

}


void PSqlTextComboBox::textChanged(int) {

    emit dataChanged(fieldName, data());

}

void PSqlTextComboBox::onEditingFinished(int) {

    emit editingFinished(fieldName, data());

}

void PSqlTextComboBox::onEditingFinished_QString(QString) {

    emit editingFinished(fieldName, data());

}

QString PSqlTextComboBox::showFieldValue(PModelPtr model) {

    if(showField.typeName() == "QString" || showField.typeName() == "QByteArray") {
        QString item = this->fieldAttrs.undefined("toTranslate", nil).toBool() ? PTranslator::tr(model->fieldValue(showField.toString()).toString()) : model->fieldValue(showField.toString()).toString();
        return item;
    }
    else if(showField.typeName() == "Array") {
        PVariant item = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
         showField.forEachQString([&] (QString fieldName) mutable {
            if(this->fieldAttrs.undefined("toTranslate", nil).toBool())
                item << PTranslator::tr(model->fieldValue(fieldName).toString());
            else
                item << model->fieldValue(fieldName).toString();
        });
        return item.join(" - ");
    }

    return QString();
}


void PSqlTextComboBox::populateList() {

    comboBox->clear();

    PVariant filter = this->fieldAttrs.undefined("filter", nil);
    model->   findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", filter)->append("orderBy", this->sortField)))));

       model->forEachPVariant_int([&] (PVariant record,int i) mutable {
        QString fieldValue = this->showFieldValue(model);
        comboBox->insertItem(i, fieldValue, record);
        comboBox->setItemData(i, record["id"]);
    });
    comboBox->insertItem(0, "", nil);
    comboBox->setCurrentIndex(0);

}


void PSqlTextComboBox::applyFilter(PVariant fieldAttrs) {

    this->fieldAttrs = fieldAttrs;

    comboBox->disconnect();

    populateList();

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onEditingFinished(int)));

}



void PSqlTextComboBox::onNew() {

    PModelPtr nvr = model->create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));  
    PSqlFormViewDialog formViewDialog(model->toRecordPtr(), "new");
    if(formViewDialog.exec() == QDialog::Accepted) {
        QString fieldValue = model->fieldValue(model->showField.toString()).toString();
        populateList();
        setData(fieldValue);
    }
    else
        model->remove(QVariant::fromValue(nvr));


}


void PSqlTextComboBox::onEdit() {

    model-> find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name",  comboBox->currentText())))));

    if(model->count() == 0)
        return;

    PSqlFormViewDialog formViewDialog(model->toRecordPtr(), "edit");
    if(formViewDialog.exec() == QDialog::Accepted) {
        QString name = model->undefined("name", nil).toString();
        populateList();
        comboBox->setEditText(name);
    }


}
