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

#ifndef PMPBX_VOICE_AGENT_H
#define PMPBX_VOICE_AGENT_H

#include <QProcess>

#include "sql/pmodel.h"
#include "misc/popenurl.h"
#include "misc/pprocessdialog.h"
#include "misc/pgembridge.h"

class PMPbxVoiceAgent : public PModel {

    Q_OBJECT

public:
#include "dom/phtml_header.h"

    PMPbxVoiceAgent() {};
    PMPbxVoiceAgent(PVariant args);
    PMPbxVoiceAgent& init(PVariant);
    ~PMPbxVoiceAgent();
    PVariant hotel();
    PVariant tables();
    PVariant voices();
    PVariant languages();


public slots:
    void onCurrentRecordChanged(const QString& id);
    PVariant action(PVariant action);
    void onChangeField(QString fieldName, PVariant fieldValue);
    bool onOkDialog();

public:
    PGemBridge* gemBridge;
    QMap<QString, PProcessDialog*> processDialogMap;

};

Q_DECLARE_METATYPE(PMPbxVoiceAgent*)

#endif // PMPBX_VOICE_AGENT_H
