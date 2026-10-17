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




   #include "widgets/widgetedit/pswitchedit.h"


   

   

PSwitchEdit::PSwitchEdit(QWidget *parent) :
    PFieldWidget(parent) {

    readOnly = false;
    this->color.setHsv(PMath::rand() % 255, 250, 200);

}

void PSwitchEdit:: setAttrs(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "setAttrs:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString color = source_args.value<PVariantMapPtr>()->include("color") ? source_args.value<PVariantMapPtr>()->operator[]("color").toString() : QVariant(QString("green")).toString();args.removeByKey("color");


    if(color != "random")
        this->color.setNamedColor(color);

}


void PSwitchEdit::showEvent(QShowEvent* event) {

    setMinimumSize(25, 25);
    QWidget::showEvent(event);

}



void PSwitchEdit::mousePressEvent(QMouseEvent* event) {

    if(readOnly) return;

    state = !state;
    repaint();
    QWidget::mousePressEvent(event);
    onEditingFinished();

}


void PSwitchEdit::paintEvent(QPaintEvent* event) {

   QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QPen pen(Qt::gray, 1);

    if(state)
        painter.setBrush(QBrush(color));
    else
        painter.setBrush(QBrush(Qt::gray));

    painter.setPen(pen);

    painter.drawRoundedRect(0, 0, 40, 24, 80, 90);

   QPainterPath path;

    if(state)
        path.addEllipse(18, 2, 20, 20);
    else
        path.addEllipse(1, 2, 20, 20);

    painter.setBrush(QLinearGradient());
    painter.drawPath(path);


    QWidget::paintEvent(event);

}


PVariant PSwitchEdit::data() {

    return state;

}

void PSwitchEdit::setData(PVariant data) {

    this->state = data.toBool();
    repaint();

}

void PSwitchEdit::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);

}


void PSwitchEdit::setReadOnly(bool value) {

    readOnly = value;

}

bool PSwitchEdit::isEmpty() {

    return false;

}

void PSwitchEdit::onEditingFinished() {

    emit editingFinished(fieldName, data());

}
