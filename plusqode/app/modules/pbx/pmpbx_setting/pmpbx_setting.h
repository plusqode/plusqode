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

#ifndef PMPBX_SETTING_H
#define PMPBX_SETTING_H

#include "sql/pmodel.h"
#include "misc/popenurl.h"

#include <QTcpSocket>

class PMPbxSetting : public PModel {

    Q_OBJECT

public:
#include "dom/phtml_header.h"

    PMPbxSetting() {};
    PMPbxSetting(PVariant args);
    PMPbxSetting& init(PVariant);
    virtual PVariant handleRequest(PVariant request);
    QString http_conf();
    QString extensions_conf();
    QString pjsip_conf();
    QString queues_conf();
    QString manager_conf();

    void write_pjsip();
    void write_extensions();
    void write_queues();

public slots:
    PVariant action(PVariant action);
    void onChangeField(QString fieldName, PVariant fieldValue);
    bool onOkDialog();
    void reloadAsteriskConf();

};

Q_DECLARE_METATYPE(PMPbxSetting*)

#endif // PMPBX_SETTING_H
