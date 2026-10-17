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






   #include "widgets/sqlview/psqlbuttonview.h"




   



   
   #include "app/modules/pmodules.h"




   



   
   



   
   
 

PSqlButtonView:: PSqlButtonView(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PSqlButtonView:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString modelName = source_args.value<PVariantMapPtr>()->include("modelName") ? source_args.value<PVariantMapPtr>()->operator[]("modelName").toString() : QVariant(nil).toString();args.removeByKey("modelName");
PVariant attrs = source_args.value<PVariantMapPtr>()->include("attrs") ? source_args.value<PVariantMapPtr>()->operator[]("attrs") : nil;args.removeByKey("attrs");
QString filter = source_args.value<PVariantMapPtr>()->include("filter") ? source_args.value<PVariantMapPtr>()->operator[]("filter").toString() : QVariant(QString("true")).toString();args.removeByKey("filter");
PVariant sortField = source_args.value<PVariantMapPtr>()->include("sortField") ? source_args.value<PVariantMapPtr>()->operator[]("sortField") : PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", QString("asc")))));args.removeByKey("sortField");
QString pageSize = source_args.value<PVariantMapPtr>()->include("pageSize") ? source_args.value<PVariantMapPtr>()->operator[]("pageSize").toString() : QVariant(QString("all")).toString();args.removeByKey("pageSize");
int page = source_args.value<PVariantMapPtr>()->include("page") ? source_args.value<PVariantMapPtr>()->operator[]("page").toInt() : QVariant(0).toInt();args.removeByKey("page");
QString connectionName = source_args.value<PVariantMapPtr>()->include("connectionName") ? source_args.value<PVariantMapPtr>()->operator[]("connectionName").toString() : QVariant(QString("default")).toString();args.removeByKey("connectionName");
bool totalizerPanel = source_args.value<PVariantMapPtr>()->include("totalizerPanel") ? source_args.value<PVariantMapPtr>()->operator[]("totalizerPanel").toBool() : QVariant(false).toBool();args.removeByKey("totalizerPanel");
QWidget* parent = source_args.value<PVariantMapPtr>()->include("parent") ? source_args.value<PVariantMapPtr>()->operator[]("parent").value<QWidget*>() : 0;
args.removeByKey("parent");


    QWidget::setParent(parent);
    this->attrs = attrs;
    this->modelName = modelName;
    this->sortField = sortField;
    this->rows = (attrs. undefined("rows", nil)!= nil) ? attrs.undefined("rows", nil).toInt() : 7;
    this->cols = (attrs. undefined("cols", nil)!= nil) ? attrs.undefined("cols", nil).toInt() : 10;
    this->buttons = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    this->btnWidth = 32;
    this->btnHeight = 32;

    this->alignment = (attrs. undefined("alignment", nil)!= nil) ? attrs.undefined("alignment", nil).toString() : "center";

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0,0,0,0);

    this->model = PModules:: newPModel(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("modelName", modelName)))));
    this->model->setParent(this);

    QString fieldNameReference = PString(QString("%1_id").arg(modelName));
    this->model->     findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append( fieldNameReference, QString("$null"))->append("op", QString("is"))))))))));

    buttonWidget = new QWidget(this);
    buttonGridLayout = new QGridLayout(buttonWidget);
    buttonGridLayout->setContentsMargins(0,0,0,0);
    buttonGridLayout->setSpacing(0);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(buttonWidget);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    gridLayout->addWidget(scrollArea, 3, 0);

}

PSqlButtonView::~PSqlButtonView() {

    this->clear();

}

void PSqlButtonView::initGeometry() {

    int scrollBarWidth = 20;

    this->btnHeight = height() / rows;
    this->btnWidth = width() / cols;

    if(cols == 1) this->btnWidth -= 2; 

    int remainder = (model->count() % cols) ? 1 : 0;
    int scrollAreaHeight = (model->count() / cols + remainder) * btnHeight;

    if(scrollAreaHeight > this->height())
        buttonWidget->setGeometry(0, 0, width() - scrollBarWidth, scrollAreaHeight);
    else
        buttonWidget->setGeometry(0, 0, width() - 3, scrollAreaHeight);

}

void PSqlButtonView::showEvent(QShowEvent* event) {

    initGeometry();

    reload();

    QWidget::showEvent(event);


}

void PSqlButtonView::paintEvent(QPaintEvent* event) {

    initGeometry();

    reload();

    QWidget::paintEvent(event);

}

PVariant PSqlButtonView::data() {

    return nil;

}

void PSqlButtonView::setData(PVariant data) {

    reload();

}

void PSqlButtonView::setBackgroundColor(QString color) {

}


bool PSqlButtonView::isEmpty() {

    return model->count() == 0;

}

void PSqlButtonView::onClick(PVariant actionButton) {

    emit click(actionButton);

}

void PSqlButtonView::onDoubleClicked(int row, int col) {

    model->onClick( PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("action", QString("edit"))))));

}


void PSqlButtonView::applyFilter(PVariant filter) {

    this->model-> findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("sql", filter)))));
    clear();
    repaint();

}

void PSqlButtonView::clear() {

    for(int i = 0; i < buttonList.count(); i++) {
        PActionButton* btn = buttonList.at(i);
        buttonGridLayout->removeWidget(btn);
        btn->hide();
        btn->deleteLater();
    }
    buttonList.clear();

}


PVariant PSqlButtonView::dbTableToVariant(PModelPtr modelPtrRoot) {

    PVariant menu = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
       modelPtrRoot->forEachPModelPtr_int([&] (PModelPtr modelPtr,int r) mutable {
        PVariant record = modelPtr->getTableCursor();
        menu << record;

        PModelPtr subTable = modelPtr->undefined(PString(QString("%1_table").arg(modelName)), nil).value<PModelPtr>();
        if(subTable->count()) record["menu"] = dbTableToVariant(subTable);

    });

    return menu;

}


void PSqlButtonView::reload() {

    this->clear();

    buttons = dbTableToVariant(model);

       buttons.forEachWithIndexPVariant_int([&] (PVariant button,int r) mutable {
        PActionButton* actionButton = new PActionButton(button);
        if(this->attrs. undefined("posStyle", nil)!= nil) actionButton->setPosStyle();
        if(this->attrs. undefined("fontSize", nil)!= nil) actionButton->setTextSize(this->attrs.undefined("fontSize", nil).toInt());
        actionButton->setText(button.undefined("name", nil).toString());
        buttonList << actionButton;
        connect(actionButton, SIGNAL(click(PVariant)), this, SLOT(onClick(PVariant)));
        actionButton->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        actionButton->setTextAlignment(this->alignment);
        actionButton->setMinimumHeight(this->btnHeight);
        actionButton->setIconSize(QSize(this->btnWidth, this->btnHeight));
        
        buttonGridLayout->addWidget(actionButton, r / cols, r % cols);
    });

}
