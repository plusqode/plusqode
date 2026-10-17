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



   #include "widgets/pstateprogressbar.h"

   
   
   #include "sql/pmodel.h"

   
   
   
   
   
 

PStateProgressBar::PStateProgressBar(QWidget *parent) : QWidget(parent) {

    buttons = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    arcs = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(0,0,0,0);

    stateGridLayout = new QGridLayout(this);
    stateGridLayout->setContentsMargins(0,0,0,0);

    actionGridLayout = new QGridLayout(this);
    actionGridLayout->setContentsMargins(0,0,0,0);

    gridLayout->addLayout(stateGridLayout, 0, 0);
    gridLayout->addLayout(actionGridLayout, 1, 0);

}


void PStateProgressBar::init(PVariant states) {

    this->states = states;

    PVariant extraButtons = states.removeByKey("buttons");

         states.forEachWithIndexQString_PVariant_int([&] (QString stateName,PVariant state,int i) mutable {
        state. undefined("arcs", nil)+= extraButtons.undefined("arcs", nil);
        arcs += state.undefined("arcs", nil).fromListToMap();
        PPushButton* pushButton = new PPushButton(this);
        buttons[stateName] = PVariant::fromValue(pushButton);
        pushButton->setText(PTranslator::tr(PString(stateName).capitalize(" ")));
        
        pushButton->setFlat(true);
        pushButton->setTextAlignment("center");
        QString iconFileName = (attrs. undefined("iconFile", nil)!= nil) ? attrs.undefined("iconFile", nil).toString() : "picons/core/actions-128/state.png";
        PImage icon(iconFileName);
        icon.setHS(state.undefined("hue", nil).toInt(), state.undefined("saturation", nil).toInt());
        pushButton->setIcon(icon.toIcon());
        PVariant iconSize = PVariant::fromString(attrs.undefined("iconSize", nil).toString());
        pushButton->setIconSize(QSize(iconSize.undefined("0", nil).toInt(), iconSize.undefined("1", nil).toInt()));
        pushButton->setEnabled(false);
        pushButton->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        stateGridLayout->addWidget(pushButton, 0, i * 2);
        if(i < states.count() - 1) {
            QFrame* line = new QFrame(this);
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);
            line->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
            stateGridLayout->addWidget(line, 0, i * 2 + 1);
        }
    });

         arcs.forEachWithIndexQString_PVariant_int([&] (QString stateName,PVariant value,int i) mutable {
        PActionButton* actionButton = new PActionButton(stateName, this);
        actionButton->textLabel->setWordWrap(true);
        this->arcs[stateName] = PVariant::fromValue(actionButton);
        actionButton->setText(PTranslator::tr(PString(stateName).capitalize(" ")));
        if(states[stateName]. undefined("label", nil)!= nil)
            actionButton->setText(states[stateName].undefined("label", nil).toString());
        actionButton->textLabel->setAlignment(Qt::AlignCenter);
        actionButton->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
        connect(actionButton, SIGNAL(click(PVariant)), this, SLOT(onClick(PVariant)));
        actionGridLayout->addWidget(actionButton, 1, i);
    });

}


void PStateProgressBar::setCurrentState(const QString& newState) {

    if(buttons[newState] == nil) {
        qDebug() << "Error in PStateProgressBar::setCurrentState" << newState << "doesn't exists" << "\n";
        return;
    }

    if(!currentState.isNull()) buttons[currentState].value<PPushButton*>()->setEnabled(false);
    buttons[newState].value<PPushButton*>()->setEnabled(true);

    this->currentState = newState;

       arcs.forEachQString_PVariant([&] (QString stateName,PVariant value) mutable {
        arcs[stateName].value<PActionButton*>()->setVisible(false);
    });

    PVariant arcs = this->states[newState].undefined("arcs", nil);

     arcs.forEachQString([&] (QString stateName) mutable {
        this->arcs[stateName].value<PActionButton*>()->setVisible(true);
    });

}

void PStateProgressBar::onClick(PVariant actionItem) {

    if(!model->action(actionItem).toBool())
        return;

    setCurrentState(actionItem.toString());
    emit changeCurrentState(actionItem);

}
