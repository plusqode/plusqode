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

#ifndef PUSERMANAGER_H
#define PUSERMANAGER_H

   #include <QWidget>
   #include <QString>

   #include "variant/pvariant.h"

class PTabNavigation;
class PModelPtr;

class PUserManager {

public:
    PUserManager();
    PModelPtr modelProfile(const QString& modelName);
    PModelPtr moduleProfile(const QString& moduleName);
    void applyProfile(QWidget* parent, const QString& modelName);
    void addTab(PVariant module, QWidget* tab);
    void applyModuleProfile();
    void setObjectName(QWidget* widget, const QString& objectName);
    void authenticate();


    QString userId;
    QString userName;
    QString userPassword;
    QString userProfileId;

    bool developerMode; 

    PTabNavigation* tabNavigation;

};

class PSinglUserManager {

public:
    static PUserManager* instance() {
        static PUserManager instance;
        return &instance;
    }
};

#endif 



