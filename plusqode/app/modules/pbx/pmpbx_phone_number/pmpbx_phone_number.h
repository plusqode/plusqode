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

#ifndef PMPBX_PHONE_NUMBER_H
#define PMPBX_PHONE_NUMBER_H

#include "sql/pmodel.h"
#include "misc/popenurl.h"

class PMPbxPhoneNumber : public PModel {

    Q_OBJECT

public:
#include "dom/phtml_header.h"

    PMPbxPhoneNumber() {};
    PMPbxPhoneNumber(PVariant args);
    PMPbxPhoneNumber& init(PVariant);
    virtual PVariant handleRequest(PVariant request);
    bool isFromInternal();
    QString destinationStr(QString destinationType = QString());
    QString internalCalls();
    QString outboundStr();
    QString outboundAgentStr();
    QString context();
    QString ivrTable();
    QString pjsip_conf();
    QString extensions_conf();
    QString queue();
    QString queues_conf();
    QString internalConf();
    PVariant voipProviders();
    static void call(PVariant);

public slots:
    PVariant action(PVariant action);
    void onChangeField(QString fieldName, PVariant fieldValue);
    void onAfterOkDialog();

};

Q_DECLARE_METATYPE(PMPbxPhoneNumber*)

#endif // PMPBX_PHONE_NUMBER_H
