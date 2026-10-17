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



   #include "misc/pwindow.h"

   
   

PWindow:: PWindow(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PWindow:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
int h = source_args.value<PVariantMapPtr>()->include("h") ? source_args.value<PVariantMapPtr>()->operator[]("h").toInt() : QVariant(0).toInt();args.removeByKey("h");
int w = source_args.value<PVariantMapPtr>()->include("w") ? source_args.value<PVariantMapPtr>()->operator[]("w").toInt() : QVariant(0).toInt();args.removeByKey("w");
QString style = source_args.value<PVariantMapPtr>()->include("style") ? source_args.value<PVariantMapPtr>()->operator[]("style").toString() : QVariant(QString("dl")).toString();args.removeByKey("style");
int bgc = source_args.value<PVariantMapPtr>()->include("bgc") ? source_args.value<PVariantMapPtr>()->operator[]("bgc").toInt() : QVariant(0).toInt();args.removeByKey("bgc");
int fgc = source_args.value<PVariantMapPtr>()->include("fgc") ? source_args.value<PVariantMapPtr>()->operator[]("fgc").toInt() : QVariant(1).toInt();args.removeByKey("fgc");


    this->sl = QString::fromUtf8("─│┌┐┘└[]");
    this->dl = QString::fromUtf8("═║╔╗╝╚[]");

    this->s = this->dl;
    if(style == "sl")
        this->s = this->sl;

    this->h = h;
    this->w = w;

    this->x = 0;
    this->y = 0;

    this->bgc = bgc;
    this->fgc = fgc;

    for(int i = 0; i < w; i++) {
        (*this)[i] = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
        for(int j = 0; j < h; j++)
            (*this)[i][j] = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("char", QString(" "))->append("bgc", bgc)->append("fgc", fgc))));

    }

}


PVariant& PWindow::data(int x, int y) {

    if((*this)[x] == nil)
        (*this)[x] = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    if((*this)[x][y] == nil)
        (*this)[x][y] = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("char", QString(" "))->append("bgc", 0)->append("fgc", 1))));

    return (*this)[x][y];

}


void PWindow::gotoxy(int x, int y) {

  this->x = x;
  this->y = y;

}

void PWindow::gotoyx(int y, int x) {

  this->x = x;
  this->y = y;

}

void PWindow::setColor(int bgc, int fgc) {

  this->bgc = bgc;
  this->fgc = fgc;

}

void PWindow::setBackgroundColor(int bgc) {

  this->bgc = bgc;

}

void PWindow::setForegroundColor(int fgc) {

  this->fgc = fgc;

}

void PWindow:: putColor(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "putColor:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
int bgc = source_args.value<PVariantMapPtr>()->include("bgc") ? source_args.value<PVariantMapPtr>()->operator[]("bgc").toInt() : QVariant(this->bgc).toInt();args.removeByKey("bgc");
int fgc = source_args.value<PVariantMapPtr>()->include("fgc") ? source_args.value<PVariantMapPtr>()->operator[]("fgc").toInt() : QVariant(this->fgc).toInt();args.removeByKey("fgc");
int x = source_args.value<PVariantMapPtr>()->include("x") ? source_args.value<PVariantMapPtr>()->operator[]("x").toInt() : QVariant(this->x).toInt();args.removeByKey("x");
int y = source_args.value<PVariantMapPtr>()->include("y") ? source_args.value<PVariantMapPtr>()->operator[]("y").toInt() : QVariant(this->y).toInt();args.removeByKey("y");


  data(x,y)["bgc"] = bgc;
  data(x,y)["fgc"] = fgc;

}

void PWindow:: put(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "put:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString str = source_args.value<PVariantMapPtr>()->include("str") ? source_args.value<PVariantMapPtr>()->operator[]("str").toString() : QVariant(QString(" ")).toString();args.removeByKey("str");
int x = source_args.value<PVariantMapPtr>()->include("x") ? source_args.value<PVariantMapPtr>()->operator[]("x").toInt() : QVariant(this->x).toInt();args.removeByKey("x");
int y = source_args.value<PVariantMapPtr>()->include("y") ? source_args.value<PVariantMapPtr>()->operator[]("y").toInt() : QVariant(this->y).toInt();args.removeByKey("y");


    if (x >= this->w)
        this->w = x + 1;
    if (y >= this->h)
        this->h = y + 1;

    data(x,y)["char"] = PVariant(str[0]);

    this->   putColor(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("x", x)->append("y", y)))));

    if(str.length() > 1)
               put(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("str", 
         str.mid(1))->append("x", x+1)->append("y", y)))));

}

void PWindow::put(QString str) {

     put(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("str", str)))));

}

int PWindow::getBackgroundColor() {

    return data(this->x, this->y)["bgc"].toInt();

}

int PWindow::getBackgroundColor(int x, int y) {

  return data(x,y)["bgc"].toInt();

}

int PWindow::getForegroundColor() {

    return data(this->x, this->y)["fgc"].toInt();

}

int PWindow::getForegroundColor(int x, int y) {

  return data(x,y)["fgc"].toInt();

}

QChar PWindow::getChar(int x, int y) {

  return data(x,y)["char"].toChar();

}

void PWindow:: rectangle(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "rectangle:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
int x = source_args.value<PVariantMapPtr>()->include("x") ? source_args.value<PVariantMapPtr>()->operator[]("x").toInt() : QVariant(this->x).toInt();args.removeByKey("x");
int y = source_args.value<PVariantMapPtr>()->include("y") ? source_args.value<PVariantMapPtr>()->operator[]("y").toInt() : QVariant(this->y).toInt();args.removeByKey("y");
int h = source_args.value<PVariantMapPtr>()->include("h") ? source_args.value<PVariantMapPtr>()->operator[]("h").toInt() : QVariant(0).toInt();args.removeByKey("h");
int w = source_args.value<PVariantMapPtr>()->include("w") ? source_args.value<PVariantMapPtr>()->operator[]("w").toInt() : QVariant(0).toInt();args.removeByKey("w");
QString chr = source_args.value<PVariantMapPtr>()->include("chr") ? source_args.value<PVariantMapPtr>()->operator[]("chr").toString() : QVariant(QString(" ")).toString();args.removeByKey("chr");
int bgc = source_args.value<PVariantMapPtr>()->include("bgc") ? source_args.value<PVariantMapPtr>()->operator[]("bgc").toInt() : QVariant(this->bgc).toInt();args.removeByKey("bgc");
int fgc = source_args.value<PVariantMapPtr>()->include("fgc") ? source_args.value<PVariantMapPtr>()->operator[]("fgc").toInt() : QVariant(this->fgc).toInt();args.removeByKey("fgc");


    for(int i = x; i < x + w; i++)
        for(int j = y; j < y + h; j++) {
            setColor(bgc, fgc);
                 put(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("str", chr)->append("x", i)->append("y", j)))));
    }

}


void PWindow:: frame(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "frame:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
int x = source_args.value<PVariantMapPtr>()->include("x") ? source_args.value<PVariantMapPtr>()->operator[]("x").toInt() : QVariant(this->x).toInt();args.removeByKey("x");
int y = source_args.value<PVariantMapPtr>()->include("y") ? source_args.value<PVariantMapPtr>()->operator[]("y").toInt() : QVariant(this->y).toInt();args.removeByKey("y");
int w = source_args.value<PVariantMapPtr>()->include("w") ? source_args.value<PVariantMapPtr>()->operator[]("w").toInt() : QVariant(0).toInt();args.removeByKey("w");
int h = source_args.value<PVariantMapPtr>()->include("h") ? source_args.value<PVariantMapPtr>()->operator[]("h").toInt() : QVariant(0).toInt();args.removeByKey("h");
QString style = source_args.value<PVariantMapPtr>()->include("style") ? source_args.value<PVariantMapPtr>()->operator[]("style").toString() : QVariant(QString("dl")).toString();args.removeByKey("style");


           rectangle(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("x", x)->append("y", y)->append("h", 1)->append("w", w)->append("chr", 

           s.at(0))))));
               rectangle(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("x", x+w-1)->append("y", y)->append("h", h)->append("w", 1)->append("chr", 
               s.at(1))))));
           rectangle(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("x", x)->append("y", y)->append("h", h)->append("w", 1)->append("chr", 
           s.at(1))))));
               rectangle(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("x", x)->append("y", y+h-1)->append("h", 1)->append("w", w)->append("chr", 
               s.at(0))))));

       put(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("str", 

   s.at(2))->append("x", x)->append("y", y)))));
           put(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("str", 
   s.at(3))->append("x", x+w-1)->append("y", y)))));
               put(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("str", 
   s.at(4))->append("x", x+w-1)->append("y", y+h-1)))));
           put(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("str", 
   s.at(5))->append("x", x)->append("y", y+h-1)))));

}


void PWindow:: window(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "window:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
int x = source_args.value<PVariantMapPtr>()->include("x") ? source_args.value<PVariantMapPtr>()->operator[]("x").toInt() : QVariant(this->x).toInt();args.removeByKey("x");
int y = source_args.value<PVariantMapPtr>()->include("y") ? source_args.value<PVariantMapPtr>()->operator[]("y").toInt() : QVariant(this->y).toInt();args.removeByKey("y");
int w = source_args.value<PVariantMapPtr>()->include("w") ? source_args.value<PVariantMapPtr>()->operator[]("w").toInt() : QVariant(0).toInt();args.removeByKey("w");
int h = source_args.value<PVariantMapPtr>()->include("h") ? source_args.value<PVariantMapPtr>()->operator[]("h").toInt() : QVariant(0).toInt();args.removeByKey("h");
QString style = source_args.value<PVariantMapPtr>()->include("style") ? source_args.value<PVariantMapPtr>()->operator[]("style").toString() : QVariant(QString("dl")).toString();args.removeByKey("style");
QString title = source_args.value<PVariantMapPtr>()->include("title") ? source_args.value<PVariantMapPtr>()->operator[]("title").toString() : QVariant(                 QString()).toString();args.removeByKey("title");
bool shadow = source_args.value<PVariantMapPtr>()->include("shadow") ? source_args.value<PVariantMapPtr>()->operator[]("shadow").toBool() : QVariant(false).toBool();args.removeByKey("shadow");
PVariant content = source_args.value<PVariantMapPtr>()->include("content") ? source_args.value<PVariantMapPtr>()->operator[]("content") : nil;args.removeByKey("content");



    if(content != nil) {
        if(content.typeName() == "QString")
            content = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(content))));
        PVariant l = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
         content.forEachPVariant([&] (PVariant line) mutable {
            l << line.toString().length();
        });
        w = l.max().toInt() + 4;
        h = content.toList().length() + 4;
    }

    w = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(w)->append(  title.length()+4)))).max().toInt();

           rectangle(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("x", x)->append("y", y)->append("w", w)->append("h", h)))));
             frame(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("x", x)->append("y", y)->append("w", w)->append("h", h)->append("style", style)))));
    gotoxy(x + (w - title.length() - 4) / 2, y);

    put(PString(QString("%1 %2 %3").arg(s[6]).arg(title).arg(s[7])));

    int i = 0;
    if(content != nil)
         content.forEachPVariant([&] (PVariant line) mutable {
        gotoxy(x + 2, y + 2 + i);
        if(!line.toString().isEmpty())
            put(line.toString());
        i++;
    });

    if(shadow) {
        bgc = getBackgroundColor(x, y);
        setBackgroundColor(0);
                     rectangle(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("x", x+w)->append("y", y+1)->append("h", h)->append("w", 1)->append("chr", QString(" "))))));
                     rectangle(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("x", x+1)->append("y", y+h)->append("h", 1)->append("w", w)->append("chr", QString(" "))))));
        setBackgroundColor(bgc);
    }

    gotoxy(x, y + h);

}


void PWindow::render() {

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            PVariant cell = data(j, i);
            pDebug().noEndl().noSpace() << PString(cell["char"].toString()).   colorize(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("bgc",  cell["bgc"])->append("fgc",    cell["fgc"])))));
        }
        printf("\n");
    }

}

void PWindow::demo() {


    PWindow window(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    window.setColor(10, 1);
    window.gotoyx(1, 1);
    window.       window(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("h", 5)->append("w", 30)->append("style", QString("dl"))->append("title", QString("Q T P L U S"))))));
    window.         window(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("h", 5)->append("w", 30)->append("style", QString("dl"))->append("title", QString("Q T P L U S S"))->append("content", QString("New Platform"))))));
    window.gotoyx(3, 35);
    window.setColor(1, 7);
    window.    window(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("title", QString("Q T P L U S"))->append("content", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("La nova piattaforma"))->append(QString("per lo sviluppo Object Oriented"))))))))));
    window.    window(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("title", QString("Q T P L U S"))->append("content", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString("La nova piattaforma"))->append(QString("per lo sviluppo Object Oriented"))))))))));
    window.render();


}
