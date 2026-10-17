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




   #include "plusqode.h"


   

   
   #include "ui_plusqode.h"


   

   
   

   
   
 
   #include "app/modules/pmodules.h"


   

   
   

   
   
 
   

   
   
 
   
 
 

   #include "app/views/test.html.cpp"


   

   
   

   
   
 
   

   
   
 
   
 
 

   

   
   
 
   
 
 

   
 
 

 

PlusQode::PlusQode(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlusQode)
{
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet(PString(QString("background-color: '%1'").arg(PGlobal::windowColor())));
    this->posPrintManagerThread = 0;
    this->as = 0;

    
    
    
    


    
    

    
    

}

void PlusQode::startUi() {

    tabNavigation = new PTabNavigation(this);

}

PlusQode::~PlusQode() {

    PLog().debug() << "PlusQode::~PlusQode";

    if(this->posPrintManagerThread) {
        posPrintManagerThread->quit();
        posPrintManagerThread->wait();
        delete posPrintManagerThread;
        posPrintManagerThread = 0;
    }

    if(this->as) {
        delete this->as;
        this->as = 0;
    }

    PSql::closeAllConnections();
    delete ui;

    delete translator;

}


void PlusQode::initSettings() {

    PMSetting setting(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    setting.find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));

    if(setting.count() == 0) {
        PLog().error() << "PlusQode::initSettings(): Setting record not found\n";
        PLog().error() << "Creation Default Record ...";
        setting. create(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("id", QString("$default"))))));
        setting.writeAllRecords();
        setting.find(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    }

    PConfigurationManager* config = PSinglConfigurationManager::instance();
    config->initByVariant("settings", setting.current());

    PVariant onExit = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("browser"))->append(QString("www.plusqode.com")))));

    PMSchedulerManager::start();

}






void PlusQode::modelClassTableDemo() {

    PMProduct product(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    
     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "modelName:" << product.modelName; 
     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "className:" << product.className; 
     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "className:" << product.toModelName(); 


    PMPosProduct posProduct(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    
     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "modelName:" << posProduct.modelName; 
     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "className:" << posProduct.className; 
     PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "className:" << posProduct.toModelName(); 

    exit(0);

}


void PlusQode:: init(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "init:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString module = source_args.value<PVariantMapPtr>()->include("module") ? source_args.value<PVariantMapPtr>()->operator[]("module").toString() : QVariant(nil).toString();args.removeByKey("module");
QString port = source_args.value<PVariantMapPtr>()->include("port") ? source_args.value<PVariantMapPtr>()->operator[]("port").toString() : QVariant(nil).toString();args.removeByKey("port");


    PConfigurationManager* config = PSinglConfigurationManager::instance();
    config->init("plusqode", PString(QString("%1/plusqode.cfg").arg(PGlobal::confFilePath())));

    PLogManager::initByPlusQodeFile();

    PLog().debug() << "Start" << "PlusQode";

    pDebug() << PConf().value("logger.level");

    PSinglSqlGenerator::instance();

    this->initSettings();

    translator = new PTranslator();

    if(module == "PosPrintManager") {
        PLog().warning() << "Print Server Started ... ok";
        posPrintManagerThread = new PPosPrintManagerThread();
        posPrintManagerThread->start();
    }
    if(module == "JsonService") {
        PLog().warning() << "Json Service ... ok";
        this->as = new PActivationServer("9089", "/api/telemetry");
    }


    
    

}
