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

#include "app/modules/pbx/pmpbx_setting/pmpbx_setting.h"
#include "app/modules/pmodules.h"

PMPbxSetting::$PMPbxSetting() {

    init(args);

}

QString PMPbxSetting::http_conf() {

§
enabled = yes
bindaddr = 0.0.0.0
bindport = 8088
§


}


QString PMPbxSetting::extensions_conf() {

    return "";

}

QString PMPbxSetting::pjsip_conf() {

§
[global]
type=global

[transport-udp]
type=transport
protocol=udp
bind=0.0.0.0:5060
§

}


QString PMPbxSetting::queues_conf() {

§
[general]
persistentmembers = yes
autofill = yes
§


}


QString PMPbxSetting::manager_conf() {

§
[plusqode]
secret = plusqode
read =
write = config,system
; read = system,call,log,verbose,command,agent,user,config
; write = system,call,log,verbose,command,agent,user,config
; permit = 0.0.0.0/0.0.0.0  ; (Opzionale: sblocca l'accesso da qualsiasi IP se l'app gira su un PC diverso)
§

}


PMPbxSetting& PMPbxSetting::init(PVariant args) {

    PModel::init(args);

    this->autoView = false; // false if you want to use pmpbx_setting_view.xml

    name$ = $pt(default: 'Settings');

    http$ = $pt(default: http_conf(), fieldType: 'plain_text_edit');
    extensions$ = $pt(default: extensions_conf(), fieldType: 'plain_text_edit');
    pjsip$ = $pt(default: pjsip_conf(), fieldType: 'plain_text_edit');
    queues$ = $pt(default: queues_conf(), fieldType: 'plain_text_edit');

    return *this;

}


PVariant PMPbxSetting::action(PVariant action) {

    if(action.action$s == "print") {
       POpenUrl::writeHtml($"pos/generic", "xxx", this->html());
       return true;
    }
    else if(action.action$s == "action_name1")
        ;
    else if(action.action$s == "action_name2")
        ;
    return ${type: "message_box", description: "apply successfully", icon: "picons/core/actions-128/ok.png"};

}


void PMPbxSetting::onChangeField(QString fieldName, PVariant fieldValue) {

    qDebug() << fieldName << fieldValue.toString();

}


PVariant PMPbxSetting::$handleRequest(QString command:, PVariant payload:) {

    qDebug() << "PModel::$handleRequest - > " << command << payload.toString();
    return ${available: true, message: 'Congratulation by PlusQode'};

}


void PMPbxSetting::write_pjsip() {

    QStringList lines;

    PMPbxPhoneNumber $phoneNumber();

    lines << pjsip$s;

    lines << phoneNumber.pjsip_conf();

    PDir::fileWrite($"${PGlobal::asteriskPath()}/pqconf/pjsip.conf", lines.join("\n").toUtf8());

}


void PMPbxSetting::write_extensions() {

    PMPbxSetting $setting();
    setting.$findBy();

    QStringList lines;

    PMPbxPhoneNumber $phoneNumber();

    lines << setting.extensions$s;

    lines << phoneNumber.extensions_conf();

    PDir::fileWrite($"${PGlobal::asteriskPath()}/pqconf/extensions.conf", lines.join("\n").toUtf8());

}

void PMPbxSetting::write_queues() {

    PMPbxSetting $setting();
    setting.$findBy();

    QStringList lines;

    PMPbxPhoneNumber $phoneNumber();

    lines << setting.queues$s;

    lines << phoneNumber.queues_conf();

    PDir::fileWrite($"${PGlobal::asteriskPath()}/pqconf/queues.conf", lines.join("\n").toUtf8());

}


void PMPbxSetting::reloadAsteriskConf() {

    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 5038); // Cambia l'IP se Asterisk si trova su un altro server

    if (!socket.waitForConnected(3000)) {
        qDebug() << "Impossibile connettersi:" << socket.errorString();
        return;
    }

    // Leggi il banner iniziale di Asterisk (es. "Asterisk Call Manager/...")
    socket.waitForReadyRead(2000);
    qDebug() << "Banner:" << socket.readAll();

    // 1. Invio Login (Assicurati che username e secret coincidano esattamente con manager.conf)
    QString loginCmd = "Action: Login\r\n"
                       "Username: plusqode\r\n"
                       "Secret: plusqode\r\n\r\n";

    socket.write(loginCmd.toUtf8());
    socket.waitForBytesWritten(1000);
    socket.waitForReadyRead(2000);

    QByteArray loginResponse = socket.readAll();
    qDebug() << "Risposta Login:\n" << loginResponse;

    if (!loginResponse.contains("Success")) {
        qDebug() << "Autenticazione Fallita! Controlla username, password o indirizzo IP autorizzato.";
        socket.close();
        return;
    }

    // 2. Invio Reload
    QString reloadCmd = "Action: Reload\r\n\r\n";
    socket.write(reloadCmd.toUtf8());
    socket.waitForBytesWritten(1000);
    socket.waitForReadyRead(2000);

    qDebug() << "Risposta Reload:\n" << socket.readAll();
    
    // 3. Invio module load pbx_config.so
    QString loadCmd = "Action: ModuleLoad\r\n"
                      "Module: pbx_config.so\r\n"
                      "LoadType: load\r\n\r\n";
    socket.write(loadCmd.toUtf8());
    socket.waitForBytesWritten(1000);
    socket.waitForReadyRead(2000);

    qDebug() << "Risposta Module:\n" << socket.readAll();

    // 4. Logoff
    socket.write("Action: Logoff\r\n\r\n");
    socket.close();

}


bool PMPbxSetting::onOkDialog() {

    bool firstTime = (QDir().exists($"${PGlobal::asteriskPath()}/pqconf/manager.conf")) ? false : true;

    PDir::fileWrite($"${PGlobal::asteriskPath()}/pqconf/http.conf", http$s.toUtf8());
    //PDir::fileWrite($"${PGlobal::asteriskPath()}/pqconf/manager.conf", this->manager_conf().toUtf8());

    this->write_pjsip();
    this->write_extensions();
    this->write_queues();

    this->reloadAsteriskConf();

    if(firstTime)
        PMMessageBox::$messageBox(text: "You need to restart computer !!!", icon: "picons/core/actions-128/ko.png");

    return true;

}

