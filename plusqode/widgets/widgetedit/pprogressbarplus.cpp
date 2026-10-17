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



   #include "widgets/widgetedit/pprogressbarplus.h"

   
   

PProgressBarPlus::PProgressBarPlus(QWidget *parent) :
    PFieldWidget(parent) {

    progressBar = new QLabel(this);

    
    

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(progressBar, 0, 0);

    label = new QLabel(this);
    label->setFrameShape(QFrame::Panel);
    label->setFrameShadow(QFrame::Sunken);
    layout->addWidget(label, 0, 0);

    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    this->setAttrs(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    this->max = 100;

}

PProgressBarPlus::~PProgressBarPlus() {



}

QWidget* PProgressBarPlus::mainWidget() {

    return progressBar;

}



















void PProgressBarPlus:: setAttrs(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "setAttrs:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString barType = source_args.value<PVariantMapPtr>()->include("barType") ? source_args.value<PVariantMapPtr>()->operator[]("barType").toString() : QVariant(QString("default")).toString();args.removeByKey("barType");
int hue = source_args.value<PVariantMapPtr>()->include("hue") ? source_args.value<PVariantMapPtr>()->operator[]("hue").toInt() : QVariant(0).toInt();args.removeByKey("hue");
QString style = source_args.value<PVariantMapPtr>()->include("style") ? source_args.value<PVariantMapPtr>()->operator[]("style").toString() : QVariant(QString("lion")).toString();args.removeByKey("style");
PVariant colors = source_args.value<PVariantMapPtr>()->include("colors") ? source_args.value<PVariantMapPtr>()->operator[]("colors") : PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(50)->append(100)->append(150)->append(200)->append(250))));args.removeByKey("colors");


    this->barType = barType;
    this->style = style;
    this->hue = hue;
    this->colors = colors;

}

void PProgressBarPlus::initPixmap() {

    int rate = this->data().toInt() * 100 / this->max;

    if(this->barType == "color-bar") {  
        this->label->hide();
        this->hue = data().toInt();
        rate = 100;
    }
    if(this->barType == "icon-bar") {
        progressBar->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        this->label->hide();
        QImage sourceImage = QImage(data().toString());
        pixmap = QPixmap::fromImage(sourceImage);
        progressBar->setPixmap(pixmap);
        return;
    }
    else if(!this->hue) {
        int tmp = 100 / colors.count();
        if(tmp == 0) tmp = 1;
        this->hue = colors[data().toInt() / tmp].toInt();
    }

    QImage sourceImage = QImage(PString(QString("picons/widgets/progress-bar/%1.png").arg(style)));

    QImage destImage(rate * width() / 100, sourceImage.height(), sourceImage.format());

    for(int i = 0; i < destImage.width(); i++)
        for(int j = 0; j < destImage.height(); j++) {
            QColor color = sourceImage.pixel(i % sourceImage.width(), j);
            color.setHsv(color.hue() + hue, color.saturation(), color.value());
            destImage.setPixel(i, j, color.rgb());
        }

    pixmap = QPixmap::fromImage(destImage);

    progressBar->setPixmap(pixmap);

    label->setText(PString(QString("%1%").arg(rate)));

}


void PProgressBarPlus::initByValue(int value, int max) {

    this->max = max;
    setValue(value);
    initPixmap();

}

void PProgressBarPlus::resizeEvent(QResizeEvent* event) {

    initPixmap();

}


void PProgressBarPlus::paintEvent(QPaintEvent* event) {



}


PVariant PProgressBarPlus::data() {

    return currentValue;

}

void PProgressBarPlus::setData(PVariant data) {

    currentValue = data.toString();
    this->initPixmap();

}

void PProgressBarPlus::setBackgroundColor(QString color) {

    QPalette pal(color);
    pal.setColor(QPalette::Base, color);
    label->setPalette(pal);

}


bool PProgressBarPlus::isEmpty() {

    return label->text().isEmpty();

}


void PProgressBarPlus::setRange(int minimum, int maximum) {

    this->initByValue(0, maximum);

}


void PProgressBarPlus::setValue(int value) {

    this->setData(value);

}
