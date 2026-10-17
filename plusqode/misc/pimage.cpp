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



   #include "misc/pimage.h"

   
   

PImage::PImage(const QString& fileName) : QImage(fileName) {
}

PImage::PImage(const QImage& image) : QImage(image) {

}

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    void PImage::setHS(int h, int s) {

        QImage alphaChannel = this->alphaChannel();

        for(int i = 0; i < this->width(); i++)
            for(int j = 0; j < this->height(); j++) {
                QColor color = this->pixel(i, j);
                if(s)
                    color.setHsv(color.hue() + h, s, color.value());
                else
                    color.setHsv(color.hue() + h, color.saturation(), color.value());
                this->setPixel(i, j, color.rgb());
            }

        this->setAlphaChannel(alphaChannel);

    }
#else
    void PImage::setHS(int h, int s) {

        for(int i = 0; i < this->width(); i++)
            for(int j = 0; j < this->height(); j++) {
                QColor color = this->pixelColor(i, j);
                int a = color.alpha();
                if(s)
                    color.setHsv(color.hue() + h, s, color.value());
                else
                    color.setHsv(color.hue() + h, color.saturation(), color.value());

                color.setAlpha(a);
                this->setPixelColor(i, j, color);
            }

    }
#endif



QPixmap PImage::toPixmap() {

    return QPixmap::fromImage(*this);

}


QIcon PImage::toIcon() {

    return QIcon(this->toPixmap());

}


QString PImage::randomHtmlColor() {

    PMath::initRandSequence();

    QColor color(PMath::rand() % 255, PMath::rand() % 255, PMath::rand() % 255);

    return color.name();

}
