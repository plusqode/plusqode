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





   #include "widgets/widgetedit/pdashboard.h"



   


   

PDashboard::PDashboard(QWidget *parent) :
    PFieldWidget(parent) {

    dashboard = new QLabel(this);


    QGridLayout *layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignHCenter);

    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(dashboard, 0, 0);

    label = new QLabel(this);
    layout->addWidget(label, 1, 0);

    label->setAlignment(Qt::AlignHCenter);


}


void PDashboard:: setAttrs(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "setAttrs:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
int sizeRate = source_args.value<PVariantMapPtr>()->include("sizeRate") ? source_args.value<PVariantMapPtr>()->operator[]("sizeRate").toInt() : QVariant(100).toInt();args.removeByKey("sizeRate");
int fontSize = source_args.value<PVariantMapPtr>()->include("fontSize") ? source_args.value<PVariantMapPtr>()->operator[]("fontSize").toInt() : QVariant(28).toInt();args.removeByKey("fontSize");
QString fontFamily = source_args.value<PVariantMapPtr>()->include("fontFamily") ? source_args.value<PVariantMapPtr>()->operator[]("fontFamily").toString() : QVariant(QString("Helvetica")).toString();args.removeByKey("fontFamily");
int hue = source_args.value<PVariantMapPtr>()->include("hue") ? source_args.value<PVariantMapPtr>()->operator[]("hue").toInt() : QVariant(0).toInt();args.removeByKey("hue");
int saturation = source_args.value<PVariantMapPtr>()->include("saturation") ? source_args.value<PVariantMapPtr>()->operator[]("saturation").toInt() : QVariant(255).toInt();args.removeByKey("saturation");
QString style = source_args.value<PVariantMapPtr>()->include("style") ? source_args.value<PVariantMapPtr>()->operator[]("style").toString() : QVariant(QString("sprint")).toString();args.removeByKey("style");


    this->sizeRate = sizeRate;
    this->fontSize = fontSize;
    this->hue = hue;
    this->saturation = saturation;
    this->fontFamily = fontFamily;
    this->style = style;

}

void PDashboard::showEvent(QShowEvent* event) {

    PImage image(PString(QString("picons/widgets/dashboard/dashboard-%1.png").arg(style)));

    image.setHS(hue, saturation);

    pixmap = image.toPixmap();

    initBySizeRate(sizeRate);

    QWidget::showEvent(event);

}


void PDashboard::initBySizeRate(int sizeRate) {

    circleSize = 10;
    radius = 85;
    x = width() / 2;
    y = 70;

    radius = PMath::valueByPercentage(radius, sizeRate);
    y = PMath::valueByPercentage(y, sizeRate);
    fontSize = PMath::valueByPercentage(fontSize, sizeRate);
    circleSize = PMath::valueByPercentage(circleSize, sizeRate);

    int w = PMath::valueByPercentage(pixmap.width(), sizeRate);
    int h = PMath::valueByPercentage(pixmap.height(), sizeRate);

    pixmap = pixmap.scaled(w, h);

    dashboard->setPixmap(pixmap);

}



void PDashboard::initByDegrees(int degrees) {

   QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QPen pen(Qt::black, 3);
    painter.setPen(pen);

    degrees = 180 - degrees;

    QPointF points[3] = {
        QPointF(x + (radius * PMath::cos(degrees)), y + radius - (radius * PMath::sin(degrees))),
        QPointF(x - 5, y + radius),
        QPointF(x + 5, y + radius),
     };

     painter.drawPolygon(points, 3);

    QPainterPath path;
     path.addEllipse(x - circleSize, y + radius - circleSize, circleSize * 2, circleSize * 2);

     painter.setBrush(QLinearGradient());
     painter.drawPath(path);

     QFont font(fontFamily, fontSize, QFont::Bold);
     setFont(font);

 }


void PDashboard::initByPercentage(int percentage) {

   QPainter painter(this);

    QPen pen(Qt::black, 1);

    int degrees = percentage * 180 / 100;

    initByDegrees(degrees);

}


void PDashboard::initByValue(int value, int max) {

    int percentage = value * 100 / max;

    initByPercentage(percentage);


}


void PDashboard::paintEvent(QPaintEvent* event) {

    x = width() / 2;
    initByPercentage(data().toInt());
    QWidget::paintEvent(event);

}


PVariant PDashboard::data() {

    return label->text();

}

void PDashboard::setData(PVariant data) {

    label->setText(data.toString());
    repaint();

}

void PDashboard::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    label->setPalette(pal);

}


bool PDashboard::isEmpty() {

    return label->text().isEmpty();

}
