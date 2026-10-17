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

#include "app/modules/core/pmmessage_box/pmmessage_box.h"

PMMessageBox::$PMMessageBox() {

    init(args);

}

PMMessageBox& PMMessageBox::init(PVariant args) {
    
    PModel::init(args);

    
    return *this;

}

void PMMessageBox::onAfterWidget() {

    sqlFormViewDialog->cancelButton->setHidden(true);

}


void PMMessageBox::setPixmap(const QString& iconFile) {

    $<QLabel*>("headerLabel")->setPixmap(QPixmap(iconFile));

}


void PMMessageBox::setText(const QString& text) {

    $<QLabel*>("messageLabel")->setText(PTranslator::tr(text));

}


bool PMMessageBox::onOkDialog() {

    return true;

}


bool PMMessageBox::onWrite() {
    
    // avoid the writing on db
    
    return false;

}

// PMMessageBox::$messageBox(text: "Wrong Password !!!", icon: "picons/core/actions-128/stop.png", ok: true, cancel: true);

int PMMessageBox::$messageBox(QString description:,
                                     QString text: description,
                                    QString  icon: "picons/core/actions-128/ok",
                                          bool ok: true,
                                      bool cancel: false) {

    PMMessageBox $messageBox();
    messageBox.initDialog();
    messageBox.setText(text);
    if(icon != nil) messageBox.setPixmap(icon);

    messageBox.sqlFormViewDialog->okButton->setVisible(ok);
    messageBox.sqlFormViewDialog->cancelButton->setVisible(cancel);

    return messageBox.exec();

    //QMessageBox::warning(0, message.text$s, message.description$s, QMessageBox::Ok);

}
