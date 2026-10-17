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



   #include "widgets/sqlview/psqlpagination.h"

   
   

PSqlPagination:: PSqlPagination(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PSqlPagination:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PModelPtr modelPtr = source_args.value<PVariantMapPtr>()->operator[]("modelPtr").value<PModelPtr>();
args.removeByKey("modelPtr");
int currentPage = source_args.value<PVariantMapPtr>()->include("currentPage") ? source_args.value<PVariantMapPtr>()->operator[]("currentPage").toInt() : QVariant(1).toInt();args.removeByKey("currentPage");
PVariant rowsForPage = source_args.value<PVariantMapPtr>()->include("rowsForPage") ? source_args.value<PVariantMapPtr>()->operator[]("rowsForPage") : PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(10)->append(50)->append(100)->append(250)->append(QString("all")))));args.removeByKey("rowsForPage");
int defaultIndex = source_args.value<PVariantMapPtr>()->include("defaultIndex") ? source_args.value<PVariantMapPtr>()->operator[]("defaultIndex").toInt() : QVariant(1).toInt();args.removeByKey("defaultIndex");
QWidget* parent = source_args.value<PVariantMapPtr>()->include("parent") ? source_args.value<PVariantMapPtr>()->operator[]("parent").value<QWidget*>() : 0;
args.removeByKey("parent");


    QWidget::setParent(parent);
    this->modelPtr = modelPtr;
    this->currentPage = currentPage;
    this->pageSize = rowsForPage[defaultIndex].toString();
    this->rowsForPage = rowsForPage;
    this->pages = 1;

    setMaximumWidth(400);
    setLayoutDirection(Qt::RightToLeft);

    QGridLayout* paginationGridLayout = new QGridLayout(this);
    paginationGridLayout->setContentsMargins(0,0,0,0);
    QWidget* paginationWidget = new QWidget(this);
    paginationWidget->setLayoutDirection(Qt::LeftToRight);
    paginationGridLayout->addWidget(paginationWidget, 0, 0);


    QGridLayout* gridLayout = new QGridLayout(paginationWidget);
    gridLayout->setContentsMargins(0,0,0,0);

    QLabel* pageLabel = new QLabel("Page:", this);
    gridLayout->addWidget(pageLabel, 0, 0);

    currentPageLineEdit = new QLineEdit(this);
    currentPageLineEdit->setText(QVariant(currentPage).toString());
    connect(currentPageLineEdit, SIGNAL(editingFinished()), this, SLOT(onCurrentPageChanged()));

    gridLayout->addWidget(currentPageLineEdit, 0, 1);

    ofPagesLabel = new QLabel(PString(QString("of %1").arg(pages.toString())), this);
    gridLayout->addWidget(ofPagesLabel, 0, 2);

    QLabel* rowsLabel = new QLabel("Rows:", this);
    gridLayout->addWidget(rowsLabel, 0, 3);

    ofRowsLabel = new QLabel(PString(QString("of %1").arg(rows.toString())), this);
    gridLayout->addWidget(ofRowsLabel, 0, 5);

    pageSizeComboBox = new QComboBox(this);
    pageSizeComboBox->setEditable(true);
    pageSizeComboBox->addItems(rowsForPage.toStringList());
    connect(pageSizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onPageSizeChanged(int)));
    pageSizeComboBox->setCurrentIndex(defaultIndex);
    gridLayout->addWidget(pageSizeComboBox, 0, 4);

   QPushButton* prevPushButton = new QPushButton("<", this);
    connect(prevPushButton, SIGNAL(clicked(bool)), this, SLOT(onPrevPage()));
    gridLayout->addWidget(prevPushButton, 0, 6);

   QPushButton* nextPushButton = new QPushButton(">", this);
    connect(nextPushButton, SIGNAL(clicked(bool)), this, SLOT(onNextPage()));
    gridLayout->addWidget(nextPushButton, 0, 7);

    rowsAndPages();

}


void PSqlPagination::rowsAndPages() {

    rows =  PSql(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("connectionName", modelPtr->connectionName))))).
           select(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("count(*)"))))))->
           from(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(modelPtr->modelName)))))->
           execute(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))))->data(0, "count");

    pages = 1;

    if(pageSize == "all")
        pageSize = rows.toString();

    pages = rows.toInt() / pageSize.toInt();
    if(rows.toInt() % pageSize.toInt() > 0)
        pages = pages.toInt() + 1;

    ofRowsLabel->setText(PString(QString("of %1").arg(rows.toString())));
    ofPagesLabel->setText(PString(QString("of %1").arg(pages.toString())));

}



void PSqlPagination::onCurrentPageChanged() {

    int cp = currentPageLineEdit->text().toInt();

    if(cp <= 0 || cp > pages.toInt()) {
        currentPageLineEdit->setText(PVariant(currentPage).toString());
        return;
    }
    currentPage = currentPageLineEdit->text().toInt();
    emit currentPageChanged(currentPageLineEdit->text().toInt());

}


void PSqlPagination::onPageSizeChanged(int index) {

    pageSize = pageSizeComboBox->itemText(index);
    rowsAndPages();
    emit pageSizeChanged(pageSize);

}

void PSqlPagination::onPrevPage() {

    if(currentPage == 1) return;

    currentPage--;
    currentPageLineEdit->setText(PVariant(currentPage).toString());

    emit currentPageChanged(currentPage - 1);

}


void PSqlPagination::onNextPage() {

    if(currentPage == pages) return;

    currentPage++;
    currentPageLineEdit->setText(PVariant(currentPage).toString());

    emit currentPageChanged(currentPage - 1);

}
