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

#include "app/modules/pbx/pmpbx_voice_agent/pmpbx_voice_agent.h"
#include "app/modules/pmodules.h"

PMPbxVoiceAgent::$PMPbxVoiceAgent() {

    init(args);

}


PVariant PMPbxVoiceAgent::hotel() {

§
Role: You are Vanessa, the voice assistant for Virtual Hotel. Your tone is warm, professional, and direct.

Voice Rules:

    Use natural, conversational language—no bullet points or complex phrasing.

    Confirm service requests immediately with estimated times.

Hotel Information:

    Wi-Fi: VirtualHotel_Guest (no password required).

    Breakfast: 1st Floor, 7:00 AM - 10:30 AM.

    Check-out: By 11:00 AM.

    Spa & Gym: Floor -1, 8:00 AM - 9:00 PM.

    Room Service: 11:00 AM - 11:00 PM.

    Front Desk: Press 9 or say 'Vanessa, transfer me to the front desk'.

Behavior:

    In-room services: Confirm the request has been dispatched ('Certainly, I've notified housecleaning. Fresh towels will be brought to your room in about 10 minutes.').

    Local recommendations: Provide a maximum of 2 quick options.

    Complex requests/Emergencies: Instantly transfer the call to the front desk.
§

}


PVariant PMPbxVoiceAgent::voices() {

    return ${

        'Natural Pitch': {
            'Aoede': 'Aoede',
            'Kore': 'Kore',
            'Leda': 'Leda',
            'Puck': 'Puck'
        },
        'Deep Pitch': {
            'Charon': 'Charon',
            'Fenrir': 'Fenrir'
        },
        'Bright Tone': {
            'Zephyr': 'Zephyr',
            'Autonoe': 'Autonoe',
            'Callirrhoe': 'Callirrhoe',
            'Despina': 'Despina',
            'Erinome': 'Erinome',
            'Gacrux': 'Gacrux',
            'Laomedeia': 'Laomedeia',
            'Sulafat': 'Sulafat',
            'Vindemiatrix': 'Vindemiatrix',
            'Achernar': 'Achernar'
        }

    };


}



PVariant PMPbxVoiceAgent::languages() {

    return ${

        en: 'English',

        Europe: {
          sq: 'Albanian',
          eu: 'Basque',
          be: 'Belarusian',
          bs: 'Bosnian',
          bg: 'Bulgarian',
          ca: 'Catalan',
          hr: 'Croatian',
          cs: 'Czech',
          da: 'Danish',
          nl: 'Dutch',
          et: 'Estonian',
          fo: 'Faroese',
          fi: 'Finnish',
          fr: 'French',
          gl: 'Galician',
          de: 'German',
          el: 'Greek',
          hu: 'Hungarian',
          is: 'Icelandic',
          ga: 'Irish',
          it: 'Italian',
          lv: 'Latvian',
          lt: 'Lithuanian',
          mk: 'Macedonian',
          mt: 'Maltese',
          no: 'Norwegian',
          pl: 'Polish',
          pt: 'Portuguese',
          ro: 'Romanian',
          rm: 'Romansh',
          ru: 'Russian',
          sr: 'Serbian',
          sk: 'Slovak',
          sl: 'Slovenian',
          es: 'Spanish',
          sv: 'Swedish',
          uk: 'Ukrainian',
          cy: 'Welsh',
          fy: 'Western Frisian'
        },

        'Asia and Midlle East': {
          ar: 'Arabic',
          hy: 'Armenian',
          as: 'Assamese',
          az: 'Azerbaijani',
          bn: 'Bengali',
          my: 'Burmese',
          ceb: 'Cebuano',
          zh: 'Chinese',
          fil: 'Filipino',
          ka: 'Georgian',
          gu: 'Gujarati',
          iw: 'Hebrew',
          hi: 'Hindi',
          id: 'Indonesian',
          ja: 'Japanese',
          kn: 'Kannada',
          kk: 'Kazakh',
          km: 'Khmer',
          ko: 'Korean',
          ku: 'Kurdish',
          ky: 'Kyrgyz',
          lo: 'Lao',
          ms: 'Malay',
          ml: 'Malayalam',
          mr: 'Marathi',
          mn: 'Mongolian',
          ne: 'Nepali',
          or: 'Odia',
          ps: 'Pashto',
          fa: 'Persian',
          pa: 'Punjabi',
          sd: 'Sindhi',
          si: 'Sinhala',
          tg: 'Tajik',
          ta: 'Tamil',
          te: 'Telugu',
          th: 'Thai',
          tr: 'Turkish',
          tk: 'Turkmen',
          ur: 'Urdu',
          uz: 'Uzbek',
          vi: 'Vietnamese'
        },

        Africa: {
          af: 'Afrikaans',
          ak: 'Akan',
          am: 'Amharic',
          ha: 'Hausa',
          rw: 'Kinyarwanda',
          om: 'Oromo',
          so: 'Somali',
          st: 'Southern Sotho',
          sw: 'Swahili',
          tn: 'Tswana',
          wo: 'Wolof',
          yo: 'Yoruba',
          zu: 'Zulu'
        },

        Other: {
              mi: 'Maori',
              qu: 'Quechua'
        }
    };
}



PMPbxVoiceAgent& PMPbxVoiceAgent::init(PVariant args) {

    PModel::init(args);

    this->gemBridge = 0;

    this->autoView = false; // false if you want to use pmpbx_voice_agent_view.xml

    name$ = $pt();
    model_name$ = $pt();
    model_name$ = $pa(main: true, editable: true, fieldType: "combobox", itemsAndValues: tables());
    language$ = $pt(fieldType: "combobox_plus", default: 'Aoede', mandatory: true, itemsAndValues: languages());
    voice_name$ = $pt(fieldType: "combobox_plus", default: 'Aoede', itemsAndValues: voices());
    gemini_api_key$ = $pt(mandatory: true);
    welcome_message$ = $pt(default: "Welcome to Virtual Hotel, I am Vanessa", fieldType: 'plain_text_edit');
    description$ = $pt(fieldType: 'plain_text_edit', default: hotel());
    function_declaration$ = $pt(fieldType: 'plain_text_edit');
    gemini_model_name$ = $pt(default: 'gemini-2.5-flash-native-audio-preview-12-2025', mandatory: true);
    host$ = $pt(default: '127.0.0.1', mandatory: true);
    port$ = $pt(default: '0000', mandatory: true, enabled: false);

    temperature$ = $pf(default: 1.0); // 0.0 essential .. 2.0
    max_output_tokens$ = $pi(default: 1000);

    return *this;

}


PMPbxVoiceAgent::~PMPbxVoiceAgent() {

    QStringList keys = processDialogMap.keys();
    for(int i = 0; i < keys.count(); i++) {
        QString processName = keys.at(i);
        PProcessDialog* processDialog = processDialogMap.value(processName);
        processDialog->stop();
        delete processDialog;
    }

}


void PMPbxVoiceAgent::onCurrentRecordChanged(const QString& id) {

    PActionButton* startAndStopPushButton = sqlView->findChild<PActionButton*>("StartAndStopButton");

    if(!processDialogMap.contains(name$s))
        startAndStopPushButton->setIcon(QIcon("picons/core/actions/player_play.png"));
    else
        startAndStopPushButton->setIcon(QIcon("picons/core/actions/player_stop.png"));

}


PVariant PMPbxVoiceAgent::action(PVariant action) {


    if(action.action$s == "print") {
       POpenUrl::writeHtml($"pos/generic", "xxx", this->html());
       return true;
    }
    else if(action.action$s == "startAndStop") {

        if(gemBridge == 0) {
            QProcess::execute("killall", QStringList() << "-9" << "gembridge/bin/python");
            #if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
            $PLog(color: 'red').warning() << "Gem Bridge Started ... ok";
            gemBridge = new PGemBridge(PGlobal::plus4CallPort().toInt(), this);
            #endif
        }


        if(!processDialogMap.contains(name$s)) {
            $PLog(color: "red").info()  << $"Start Voice Agent -> ${name$s} ${host$s} ${PGlobal::plus4CallPort()}";
            PProcessDialog* processDialog = new PProcessDialog();
            processDialogMap[this->name$s] = processDialog;
            processDialog->start("gembridge/bin/python", QStringList() << "-u" <<
                                 "gem/plus4agent.py" <<
                                 host$s <<
                                 PGlobal::plus4CallPort() <<
                                 this->name$s);
        }
        else {
            $PLog(color: "red") << $"Stop Voice Agente -> ${name$s}";
            processDialogMap[this->name$s]->stop();
            delete processDialogMap[this->name$s];
            processDialogMap.remove(this->name$s);
        }
        this->onCurrentRecordChanged(this->id$s);
    }
    else if(action.action$s == "showProcess") {
        if(processDialogMap.contains(name$s))
            processDialogMap[this->name$s]->showFullScreen();
    }
    else if(action.action$s == "action_name2")
        ;

    return true;

    return ${type: "message_box", description: "apply successfully", icon: "picons/core/actions-128/ok.png"};

}



void PMPbxVoiceAgent::onChangeField(QString fieldName, PVariant fieldValue) {

    qDebug() << fieldName << fieldValue.toString();

}


PVariant PMPbxVoiceAgent::tables() {

    PVariant tables = $PSql().tables();

    tables = tables.quicksort();

    return PVariant::fromItemsAndValues(tables, tables);

}


bool PMPbxVoiceAgent::onOkDialog() {

    this->writeRecord();
    if(this->port$s == "0000")
        this->port$ = PGlobal::plus4CallPort().toInt() + this->id$s.toInt();

    return true;

}


