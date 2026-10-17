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

#include "app/modules/pbx/pmpbx_phone_number/pmpbx_phone_number.h"
#include "app/modules/pmodules.h"

PMPbxPhoneNumber::$PMPbxPhoneNumber() {

    init(args);

}

QString PMPbxPhoneNumber::internalConf() {

QStringList lines;

lines
<< $"[${phone_number$s}-auth]"
<< "type=auth"
<< $"username=${username$s}"
<< $"password=${password$s}"
<< ""
<< $"[${phone_number$s}]"
<< "type=endpoint"
<< "context=from-internal"
<< "allow=!all"
<< "allow=ulaw"
<< $"auth=${phone_number$s}-auth"
<< $"aors=${phone_number$s}"
<< ""
<< $"[${phone_number$s}]"
<< "type=aor"
<< "max_contacts=5"
<< "";

return lines.join("\n");

}

/*
telnyx: "Telnyx",
twilio: "Twilio",
vonage: "Vonage",
plivo: "Plivo",
signal_wire: "SignalWire",
messagenet: "Messagenet"
*/


PVariant PMPbxPhoneNumber::voipProviders() {

    QStringList voipProviders = PDir($"${PGlobal::modulePath()}/pbx/voip_providers").$onlyFiles("*.conf");

    PVariant result = ${};

    $$voipProviders.foreach(PString fileName) {
        fileName.replace(".conf", "");
        result[fileName] = fileName.capitalize();
    }

    return result;

}


PMPbxPhoneNumber& PMPbxPhoneNumber::init(PVariant args) {

    PModel::init(args);

    this->autoView = false; // false if you want to use pmpbx_phone_number_view.xml

    this->mainField = "phone_number";
    this->showField = "phone_number";
    this->sortField = "phone_number";

    phone_number$ = $pt(mandatory: true, main: true);
    type$ = $pt(itemsAndValues: {server: "Server",
                                 internal: "Internal",
                                 'Voip Providers': this->voipProviders(),
                                 manual: "Manual"}, default: 'server', fieldType: "combobox_plus", mandatory: true);

    destination_type$ = $pt(itemsAndValues: {phone_number: "Phone Number",
                                             voice_agent: "Voice Agent",
                                             destination: "Destination",
                                             outbound: "Outbound",
                                             outbound_agent: "Outbound Agent",
                                             queue: "Queue",
                                             ivr: "IVR (Interactive Voice Response)"}, default: 'phone_number', fieldType: "combobox", mandatory: true);

    username$ = $pt();
    password$ = $pt();
    pbx_phone_number_id$ = $pa(newButton: false, editButton: false, editable: true);
    pbx_voice_agent_id$ = $pa(newButton: false, editButton: false, editable: true);
    pjsip_conf$ = $pt(fieldType: 'plain_text_edit');
    extensions_conf$ = $pt(fieldType: 'plain_text_edit');
    pbx_phone_number_join_table$ = $pa();

    ivr_sound_file_loader$ = $pt(default: 'demo-congrats', toolTip: 'you can change it in /var/lib/asterisk/sounds', fieldType: "file_dialog_edit", filter: "Audio File (*.wav)");

    ivr_sound_file$ = $pt(default: 'demo-congrats');

    return *this;

}


PVariant PMPbxPhoneNumber::action(PVariant action) {

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


void PMPbxPhoneNumber::onChangeField(QString fieldName, PVariant fieldValue) {

    qDebug() << fieldName << fieldValue.toString();

    bool enable = (this->type$s == "internal");
    this->destination_type$w->setDisabled(enable);
    this->pbx_phone_number_id$w->setDisabled(enable);
    this->pbx_voice_agent_id$w->setDisabled(enable);
    $<QWidget*>("tabWidget")->setDisabled(enable);

    this->pbx_phone_number_id$w->setEnabled(destination_type$s == "destination");
    this->pbx_voice_agent_id$w->setEnabled(destination_type$s == "voice_agent");

    $<QWidget*>("tabWidget")->setEnabled(destination_type$s == "queue" || destination_type$s == "ivr");


    if(fieldName == "ivr_sound_file_loader") {
        QString fileFullName = fieldValue.toString();
        QFileInfo fileInfo(fileFullName);
        QString fileName = fileInfo.fileName();
        PSystem($"sox ${fileFullName} -r 8000 -c 1 -b 16 /var/lib/asterisk/sounds/plusqode/${fileName}");
        fileName.replace(".wav", "");
        ivr_sound_file$ = $"/var/lib/asterisk/sounds/plusqode/${fileName}";
    }


}


PVariant PMPbxPhoneNumber::$handleRequest(QString command:, PVariant payload:) {

    qDebug() << "PModel::$handleRequest - > " << command << payload.toString();
    return ${available: true, message: 'Congratulation by PlusQode'};

}


QString PMPbxPhoneNumber::pjsip_conf() {

    QStringList lines;

    PMPbxPhoneNumber $phoneNumber();
    phoneNumber.$findBy();

    $phoneNumber.forEach(PVariant pn) {

        qDebug() << "phoneNumber type =>" << phoneNumber.type$s;

        lines << $"; -------------------------------------";
        lines << $"; -     ${phoneNumber.phone_number$s} ";
        lines << $"; -------------------------------------";
        lines << "";

        if(phoneNumber.type$s == "internal") {
            lines << phoneNumber.internalConf();
        }
        else if(this->voipProviders().include(phoneNumber.type$s)) {
            QString conf = PDir::fileContent($"${PGlobal::modulePath()}/pbx/voip_providers/${phoneNumber.type$s}.conf");
            conf.replace("${phone_number$s}", phoneNumber.phone_number$s);
            conf.replace("${username$s}", phoneNumber.username$s);
            conf.replace("${password$s}", phoneNumber.password$s);
            lines << conf;
        }

        lines << "";

        lines << phoneNumber.pjsip_conf$s;

        lines << "";

    }

    return lines.join("\n");

}

bool PMPbxPhoneNumber::isFromInternal() {

    PVariant list = $["telnyx", "twilio", "vonage", "plivo", "signalWire", "messagenet"];

    if(list.include(this->type$s))
        return false;

    return true;

}


QString PMPbxPhoneNumber::ivrTable() {

    if(this->destination_type$s != "ivr")
        return QString();

    QStringList lines;

    $this->pbx_phone_number_join_table$->forEach(PVariant none) {
        PModelPtr ptr = this->pbx_phone_number_join_table$->toModelPtr();
        PMPbxPhoneNumber* pn = ptr->undefined("pbx_phone_number_ptr_id", nil).value<PModelPtr>().value<PMPbxPhoneNumber*>();

        if(!ptr->ivr_key$s.isEmpty()) {
            lines
            <<$"; internal ${ptr->ivr_key$s} => ${pn->phone_number$s}"
            <<$"exten => ${ptr->ivr_key$s},1,NoOp(internal ${ptr->key$s} => ${pn->phone_number$s})"
            << pn->destinationStr()
            << "same => n,Hangup()"
            << "";
        }
    }

    return lines.join("\n");

}


QString PMPbxPhoneNumber::destinationStr(QString destinationType) {

    if(destinationType.isEmpty())
        destinationType = this->destination_type$s;

    QStringList lines;

    QString MYUUID = "${MYUUID}";
    QString EXTEN = "${EXTEN}";

    if(destinationType == "queue")
        return $"same => n,Queue(${phone_number$s},t,,,60)";

    if(destinationType == "ivr") {
        lines << $"same => n(menu),Background(${ivr_sound_file$s})";
        lines << $"same => n,WaitExten(5)";
        return lines.join("\n");
    }

    if(destinationType == "outbound")
        return $"same => n,Dial(PJSIP/${EXTEN}@${phone_number$s}-trunk,60)";

    if(destinationType == "outbound_agent") {
        QString exten = QString("${EXTEN:%1}").arg(username$s.length());
        return $"same => n,Dial(PJSIP/${exten}@${this->pbx_phone_number_id$->phone_number$s}-trunk,60,U(start-audiosocket^${MYUUID}))";
    }

    if(destinationType == "spy")
        return $"same => n,ChanSpy(PJSIP/${this->pbx_phone_number_id$->phone_number$s}-trunk,q)";

    if(destinationType == "destination") {
        QString ctxt = this->pbx_phone_number_id$->phone_number$s;
        if(this->pbx_phone_number_id$->isFromInternal())
            ctxt = "internal";
        return $"same => n,Goto(from-${ctxt},${this->pbx_phone_number_id$->username$s},1)";
    }

    if(destinationType == "voice_agent") {
        if(pbx_voice_agent_id$ == 0) {
            QString text = $"Phone Number ${phone_number$s} without agent";
            PMMessageBox::$messageBox(text: text, icon: "picons/core/actions-128/stop.png");
            return "";
        }

        QString port = pbx_voice_agent_id$->port$s;
        return $"same => n,AudioSocket(${MYUUID},127.0.0.1:${port})";
    }

    if(destinationType == "phone_number")
        return $"same => n,Dial(PJSIP/${phone_number$s},30)";

    return "";

}


QString PMPbxPhoneNumber::internalCalls() {


//    if(this->type$s != "server")
//        return QString();


§
; Internal Calls (es. componi 101, 102, ecc.)
exten => _1XX,1,NoOp(Internal call from ${CALLERID(num)} to ${EXTEN}) // _1XX sono tutti i numeri a 3 cifre che iniziano con 1 (101, 102 ...)
same => n,Dial(PJSIP/${EXTEN},30)
same => n,Hangup()
§

}



QString PMPbxPhoneNumber::context() {

    QString log = "from ${CALLERID(num)} => ${EXTEN})";

    QString gotoStr = $"exten => s,1,Goto(from-${phone_number$s$},${username$s$},1)";
    if(this->isFromInternal())
        gotoStr = "";

§

; -------------------------------------
; - - - - > <$= phone_number$s $> < ~ ~
; -------------------------------------

exten => <$= username$s $>,1,NoOp(Call on <$= phone_number$s $> <$= log $>
same => n,Answer()
same => n,PlayTones(ring)
same => n,Wait(2)
same => n,StopPlayTones()
same => n,Set(MYUUID=${SHELL(echo -n $(uuidgen))})
<$= destinationStr() $>
same => n,Hangup()

<$= ivrTable() $>
<$= gotoStr $>

<$= extensions_conf$s $>

§

}


QString PMPbxPhoneNumber::outboundStr() {

§
; -------------------------------------
; - ~ OUTBOUND => <$=phone_number$s$>
; -------------------------------------

exten => _X.,1,NoOp(Outbound call => ${EXTEN})
same => n,PlayTones(ring)
same => n,Wait(2)
same => n,StopPlayTones()
same => n,Set(CALLERID(num)=<$=username$s$>)
<$= destinationStr() $>
same => n,Hangup()

§

}



QString PMPbxPhoneNumber::outboundAgentStr() {

QString exten = $"{EXTEN:${QString::number(username$s.length())}}";

§
; -------------------------------------
; - ~ OUTBOUND AGENT => <$=phone_number$s$>
; -------------------------------------

exten => _<$=username$s$>.,1,NoOp(Outbound call => $<$=exten$>})
same => n,Answer()
same => n,Set(MYUUID=${SHELL(echo -n $(uuidgen))})
same => n,Set(CALLERID(num)=<$=this->pbx_phone_number_id$->username$s$>)
;same => n,MixMonitor(audiosocket_$<$=exten$>_${MYUUID}.wav)
<$= destinationStr() $>
same => n,Hangup()

exten => _*<$=username$s$>.,1,NoOp(Barge in internal)
same => n,Answer()
<$= destinationStr("spy") $>
same => n,Hangup()

[start-audiosocket]
exten => s,1,NoOp(PMPbxPhoneNumber::outboundAgentStr)
same => n,Set(MYUUID=${ARG1})
<$= destinationStr("voice_agent") $>
same => n,Return()

§

}


QString PMPbxPhoneNumber::extensions_conf() {

    QString MYUUID = "${MYUUID}";

    QStringList lines;

    PMPbxPhoneNumber $phoneNumber();
    phoneNumber.$findBy();

    $phoneNumber.forEach(PVariant pn) {
        qDebug() << "phoneNumber type =>" << phoneNumber.type$s << phoneNumber.phone_number$s;
        if(!phoneNumber.isFromInternal()) {
            lines << $"[from-${phoneNumber.phone_number$s}]";
            lines << phoneNumber.context();
        }

    }

    lines << $"[from-internal]";
    $phoneNumber.forEach(PVariant pn) {
        if(phoneNumber.type$s == "server" and phoneNumber.destination_type$s != "outbound_agent") {
            lines << phoneNumber.context();
        }
    }
    
    lines << this->internalCalls();

    $phoneNumber.forEach(PVariant pn) {
        if(phoneNumber.destination_type$s == "outbound")
            lines << phoneNumber.outboundStr();
        else if(phoneNumber.destination_type$s == "outbound_agent")
            lines << phoneNumber.outboundAgentStr();
    }

    return lines.join("\n");

}


QString PMPbxPhoneNumber::queue() {

    PVariant members = $[];

    if(this->destination_type$s != "queue")
        return QString();

    $this->pbx_phone_number_join_table$->forEach(PVariant none) {
        PModelPtr ptr = this->pbx_phone_number_join_table$->toModelPtr();
        PMPbxPhoneNumber* pn = ptr->undefined("pbx_phone_number_ptr_id", nil).value<PModelPtr>().value<PMPbxPhoneNumber*>();
        members << $"member => PJSIP/${pn->phone_number$s}";
    }

§

[<$= phone_number$s $>]
strategy = ringall
musicclass = default

<$= members.join("\n") $>

§

}


QString PMPbxPhoneNumber::queues_conf() {

    QStringList lines;

    PMPbxPhoneNumber $phoneNumber();
    phoneNumber.$findBy();

    $phoneNumber.forEach(PVariant pn) {
        if(phoneNumber.destination_type$s == "queue")
            lines << phoneNumber.queue();

    }

    return lines.join("\n");

}

// example: $call(internal: "198", phoneNumber: "392123465")

void PMPbxPhoneNumber::$call(QString internal:, QString phoneNumber:, int maxRetries: 0, int retryTime: 60, int waitTime: 30) {

    QString fileName = $"${PDir::currentDateTime()}.call";

    QStringList lines;

    lines << $"Channel: Local/${internal}${phoneNumber}@from-internal";
    //lines << $"CallerID: `101` <101>";
    //lines << $"Context: from-internal";
    lines << $"MaxRetries: ${maxRetries}";
    lines << $"RetryTime: ${retryTime}";
    lines << $"WaitTime: ${waitTime}";

    //qDebug() << lines.join("\n");

    PDir::fileWrite(fileName, lines.join("\n").toUtf8());

    QFile::setPermissions(fileName, QFile::ReadOwner | QFile::WriteOwner | QFile::ReadGroup | QFile::ReadOther);

    QFile::rename(fileName, $"/var/spool/asterisk/outgoing/${fileName}");

}


void PMPbxPhoneNumber::onAfterOkDialog() {

    PMPbxSetting $setting();
    setting.$find();
    if(setting.count() == 0) {
        setting.$create();
        setting.writeAllRecords();
    }

    setting.onOkDialog();

}
