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



   #include <QtWidgets/QApplication>

   
   
   #include "plusqode.h"

   
   
   
   
   
 
   #include "dom/pdom.h"

   
   
   
   
   
 
   
   
   
 
   
 
 
   #include "app/modules/telemetry/pmactivation/pactivationserver.h"

   
   
   
   
   
 
   
   
   
 
   
 
 
   
   
   
 
   
 
 
   
 
 
 

bool argvFind(int argc, char *argv[], const QString& str) {

    for(int i = 0; i < argc; i++)
        if(str.compare(argv[i]) == 0)
            return true;

    return false;

}


   #include "app/modules/pbx/pmpbx_phone_number/pmpbx_phone_number.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    qApp->setApplicationVersion("206");

#if defined (Q_OS_LINUX)
#elif defined (Q_OS_WIN)
    a.addLibraryPath(a.applicationDirPath() + "lib");
    qDebug() << a.applicationDirPath() + "lib";
#else
    
#endif

    qDebug() << a.applicationDirPath();
    QStringList list = a.libraryPaths();
    QStringList::Iterator it = list.begin();
    qDebug() << "====================== ";
    while( it != list.end() ) {
            qDebug() << "libraryPath: "<< *it;
            ++it;
    }
    qDebug() << "====================== ";

#if defined (Q_OS_LINUX)
    QString language = "language/plusqode_";
#elif defined (Q_OS_WIN)
    QString language = ".bin/language/plusqode_";
#else
    QString language = qApp->applicationDirPath() + "/../language/plusqode_";
#endif

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    qDebug() << QLocale::system().name();
    QTranslator translator(0);
    translator.load(language + QLocale::system().name(), ".");
    a.installTranslator(&translator);

    if(!QDir().exists("plusqode.cfg")) {
        PDir::fileWrite("plusqode.cfg", PDir::fileContent("plusqode.cfg.model"));
        PDir::remove(PString(QString("%1/.db").arg(PGlobal::basePath())));
    }

    PSharedData* sharedData =  PSharedDataManager::instance();
    sharedData->set(PSql::defaultConnectionName, "defaultConnectionName");

    QString connectionName = PSharedDataManager::instance()->value("defaultConnectionName").toString();

    

    if(argvFind(argc, argv, "-v")) {
        qDebug() << "PlusQode Version: " << qApp->applicationVersion();
        return 1;
    }

    PlusQode w;

    if(argvFind(argc, argv, "-printserver")) {
        w. init(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("module", QString("PosPrintManager"))))));
        PLog().warning() << "Print Server Started ... ok";
        return a.exec();
    }
    else if(argvFind(argc, argv, "-database")) {
        int index = argvFind(argc, argv, "-database") + 1;
        qDebug() << argc << index;
        if(argc <= index) {
            PLog().warning() << "Syntax ./plusqode -database dbconf";
            return 1;
        }
        QString connectionName = argv[index];
        sharedData->set(connectionName, "defaultConnectionName");
        w. init(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("module", QString(""))))));
    }
    else if(argvFind(argc, argv, "-js")) {
        w. init(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("module", QString("JsonService"))))));
        return a.exec();
    }
    else
        w. init(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("module", QString(""))))));

    w.startUi();

    PDom  dom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("div"))))));
    dom.  setStyle(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red"))->append("font", QString("bold"))))));

    dom << new    PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("h1"))->append("innerHTML", QString("ciao"))))));
    dom << new    PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("h2"))->append("innerHTML", QString("ciao"))))));
    dom << new    PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("h3"))->append("innerHTML", QString("ciao"))))));
    dom << new    PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("h4"))->append("innerHTML", QString("ciao"))))));
    dom << new    PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", QString("h5"))->append("innerHTML", QString("ciao"))))));

    PLog().error() << dom.toHtml();


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0) 
    w.show();
#endif


#if not defined(Q_OS_MAC)
    w.showFullScreen();
#endif

    PSinglUserManager::instance()->authenticate();

#if defined (Q_OS_MAC)
    w.showFullScreen();
#endif

    



    
    
    


    
    


    return a.exec();

}
