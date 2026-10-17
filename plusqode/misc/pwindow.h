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

#ifndef PWINDOW_H
#define PWINDOW_H

   #include "variant/pvariantlist.h"
   #include "core/plogger.h"

class PWindow : public PVariantList
{

public:
    PWindow() {};
    PWindow(PVariant);

    PVariant& data(int x, int y);
    void render();
    void gotoxy(int x, int y);
    void gotoyx(int y, int x);
    void setColor(int bgc, int fgc);
    void setBackgroundColor(int bgc);
    void setForegroundColor(int fgc);
    void putColor(PVariant);
    void put(PVariant);
    void put(QString);
    int getBackgroundColor();
    int getBackgroundColor(int x, int y);
    int getForegroundColor();
    int getForegroundColor(int x, int y);
    QChar getChar(int x, int y);
    void rectangle(PVariant);
    void frame(PVariant);
    void window(PVariant);
    static void demo();

    QString sl, dl, s;

    int h, w, x, y, bgc, fgc;

};

#endif 



