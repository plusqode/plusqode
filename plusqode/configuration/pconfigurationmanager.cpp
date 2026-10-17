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



   #include "configuration/pconfigurationmanager.h"

   
   

PConfigurationManager::PConfigurationManager()
{
}

PConfigurationManager::~PConfigurationManager() {

    foreach(PConfiguration* config, configMap.values())
        delete config;

}

void PConfigurationManager::init(const QString& configName, const QString& fileName) {

    if(configMap.find(configName) == configMap.end())
        configMap[configName] = new PConfiguration(fileName);

}


void PConfigurationManager::initByVariant(const QString& configName, PVariant configuration) {

    if(configMap.find(configName) == configMap.end())
        configMap[configName] = new PConfiguration(configuration);

}


PVariant PConfigurationManager::value(const QString& configName, const QString& varName) {

    if(configMap.find(configName) != configMap.end())
        return configMap[configName]->value(varName);



    return nil;

}


bool PConfigurationManager::setValue(const QString& configName, const QString& varName, const PVariant& value) {

    if(configMap.find(configName) != configMap.end()) {
        configMap[configName]->setValue(varName, value);
        return true;
    }


    return false;

}


void PConfigurationManager::show(const QString& configName) {

    if(configMap.find(configName) != configMap.end()) {
        pDebug() << configMap[configName]->toString();
        return;
    }

    pDebug() << "PConfigurationManager::value" << configName << "not found";

}


void PConfigurationManager::save(const QString& configName) {

    if(configMap.find(configName) != configMap.end())
        configMap[configName]->save();
    else
        pDebug() << "PConfigurationManager::value" << configName << "not found";

}


void PConfigurationManager::demo() {

    PConfigurationManager* config = PSinglConfigurationManager::instance();
    config->init("plusqode", "plusqode.cfg");
    config->show("plusqode");

    pDebug() << config->value("plusqode", "d.d.e");
    config->setValue("plusqode", "d.d.e", "pippo2");

    config->show("plusqode");


}


PConf::PConf(const QString& configName) : configName(configName) {
}

PVariant PConf::value(const QString& varName) {

    return PSinglConfigurationManager::instance()->value(configName, varName);

}

QString PConf::strValue(const QString& varName) {

    return PSinglConfigurationManager::instance()->value(configName, varName).toString();

}

bool PConf::setValue(const QString& varName, const PVariant& value) {

    return PSinglConfigurationManager::instance()->setValue(configName, varName, value);

}

void PConf::save(const QString& configName) {

    PSinglConfigurationManager::instance()->save(configName);

}
