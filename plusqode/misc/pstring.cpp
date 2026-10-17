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



   #include "variant/pvariant.h"

   
   

PString::PString() : QString()
{
}

PString::PString(const char* str) : QString(str) {

}

PString::PString(QString str): QString(str) {

}

bool PString::include(PString str) {

    return (this->indexOf(str) != -1);

}

PVariant PString::split(PString separator) {

    QStringList values = QString::split(separator);
    return PVariant::fromQStringList(values);

}

PString PString::justify(QString str, int fieldWidth, QString justify) {

    if(justify == "left")
        return QString("%1").arg(str, -fieldWidth);
    else if(justify == "center") {
        QString leftPadding = QString("%1").arg("", (fieldWidth - str.length()) / 2, ' ');
        return QString("%1").arg(leftPadding + str, -fieldWidth);
    }
    else if(justify == "right")
        return QString("%1").arg(str, fieldWidth);

    return str;

}


QString PString::space(int len, char ch) {

    return QString("%1").arg("", len, ch);

}



PString PString::replace_(QString before, QString after) {

    QString result(*this);

    return result.replace(before, after);

}

QString PString::capitalize(QString separator) {

    if(*this == "") return "";

    QStringList strs = QString::split("_");

    for(int i = 0; i < strs.count(); i++)
        strs[i][0] = strs[i].at(0).toTitleCase();

    return strs.join(separator);

}

QString PString::uncapitalize() {

    QStringList strs;
    PVariant il = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())))); 

    for(int i = 0; i < this->length(); i++)
        if(this->at(i).isUpper())
            il << i;

    int i;
    for(i = 0; i < il.count() - 1; i++) {
        int len = il[i + 1].toInt() - il[i].toInt();
        strs << this->mid(il[i].toInt(), len);
    }
    strs << this->mid(il[i].toInt());

    for(i = 0; i < strs.count(); i++)
        strs[i][0] = strs[i].at(0).toLower();

    return strs.join("_");

}


const QChar PString::operator[] (int index) const {

    if(index < 0)
        return QString::operator[](this->length() + index);

    return QString::operator[](index);

}

PString PString::fromTo(int a, int b) {

    return mid(a, this->length() - a + b);

}

QString PString::colorize(int colorCode) {

  return PString(QString("\e[1;%1m%2\e[0m").arg(colorCode).arg(*this));

}

QString PString:: colorize(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "colorize:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
int bgc = source_args.value<PVariantMapPtr>()->include("bgc") ? source_args.value<PVariantMapPtr>()->operator[]("bgc").toInt() : QVariant(16).toInt();args.removeByKey("bgc");
int fgc = source_args.value<PVariantMapPtr>()->include("fgc") ? source_args.value<PVariantMapPtr>()->operator[]("fgc").toInt() : QVariant(8).toInt();args.removeByKey("fgc");


    int background = 48;
    int foreground = 38;
    QString resetColor = "\033[m";

    QString backgroundColor = (bgc) ? PString(QString("\033[%1;5;%2m").arg(background).arg(bgc)) : "";
    QString foregroundColor = (fgc) ? PString(QString("\033[%1;5;%2m").arg(foreground).arg(fgc)) : "";
    return PString(QString("%1%2%3%4").arg(backgroundColor).arg(foregroundColor).arg((*this)).arg(resetColor));

}


QString PString::gray() {

    return colorize(0);

}

QString PString::white() {

    return colorize(37);

}

QString PString::red() {

    return colorize(31);

}

QString PString::green() {

    return colorize(32);

}

QString PString::yellow() {

    return colorize(33);

}

QString PString::blue() {

    return colorize(34);

}

QString PString::pink() {

    return colorize(35);

}

QString PString::high_red() {

    return colorize(91);

}

QString PString::high_green() {

    return colorize(92);

}

QString PString::high_yellow() {

    return colorize(93);

}

QString PString::high_blue() {

    return colorize(94);

}

QString PString::high_purple() {

    return colorize(95);

}

QString PString::high_cyan() {

    return colorize(96);

}

QString PString::high_white() {

    return colorize(97);

}

QString PString::color(QString color) {

    if(color.isNull())
        return *this;

    if(color.toLower() == "gray")
        return gray();
    if(color.toLower() == "white")
        return white();
    if(color.toLower() == "red")
        return red();
    if(color.toLower() == "green")
        return green();
    if(color.toLower() == "yellow")
        return yellow();
    if(color.toLower() == "blue")
        return pink();
    if(color.toLower() == "pink")
        return pink();
    if(color.toLower() == "high_red")
        return high_red();
    if(color.toLower() == "high_green")
        return high_green();
    if(color.toLower() == "high_yellow")
        return high_yellow();
    if(color.toLower() == "high_blue")
        return high_blue();
    if(color.toLower() == "high_purple")
        return high_purple();
    if(color.toLower() == "high_cyan")
        return high_cyan();
    if(color.toLower() == "high_white")
        return high_white();

    return *this;

}

bool PString::exactMatch(const QString& pattern) {

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QRegExp regex(pattern);
    return regex.exactMatch(*this);
#else
    QRegularExpression regex(pattern);
    return regex.match(*this).hasMatch();
#endif

}
