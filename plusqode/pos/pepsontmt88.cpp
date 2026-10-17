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




   #include "pos/pepsontmt88.h"


   

   

PEpsonTMT88::PEpsonTMT88(const QString& destFileName, PVariant data)
    : PPrinterDriver(destFileName, data) {
}


int PEpsonTMT88::getPaperWidth() {

    return 42;

}


void PEpsonTMT88::startSection() {

}


void PEpsonTMT88::endSection() {

    char verticalSpace[] = "\n\n\n\n\n\n\n\r";
    print(0, verticalSpace);

    fullCut();

    generatePulse();

    if(docAttrs.undefined("openCashDrawerValue", nil).toBool())
        openCashDrawer();


}

void PEpsonTMT88::reset() {

    char reset[] = {27,  '@', 29, '!', 8, '\0'};
    print(0, reset);

}

void PEpsonTMT88::setBold() {


    char setBold[] = {27, 'E', '\r', '\0'};
    print(0, setBold);

}

void PEpsonTMT88::setCharSize() {

    char GS = 29;

    char setNormal[] = {GS, '!', 10, '\0'};

    int size = charSize;

    if (size == 1)
        setNormal[2] = 8;
    else
        setNormal[2] = size - 1;

    print(0, setNormal);

    char setJustify[] = {0x1B, 'a', '0', 0x0};
    print(0, setJustify);


}


void PEpsonTMT88::setCharSize(int size) {

    char GS = 29;

    char setNormal[] = {GS, '!', 10, '\0'};

    reset();    

    if (size == 1)
        setNormal[2] = 8;
    else
        setNormal[2] = size - 1;

    print(0, setNormal);

    char setJustify[] = {0x1B, 'a', '0', 0x0};
    print(0, setJustify);

}


void PEpsonTMT88::setCenterJustify() {

    char setJustify[] = {0x1B, 'a', '1', 0x0};
    print(0, setJustify);

}

void PEpsonTMT88::setAlignment(int align) { 

    char setJustify[] = {0x1B, 'a', (char)('0' + align), 0x0};
    print(0, setJustify);

}


void PEpsonTMT88::fullCut() {

    char fullCut[] = {27, 'i', 0};
    print(0, fullCut);

}


void PEpsonTMT88::generatePulse() {


    char buf[] = {0x1E, 0x00};
    print(0, buf);

}


void PEpsonTMT88::openCashDrawer() {

    char buf[] = {0x1B, 0x70, 0x30, 0x37, 0x79, 0x0};
    print(0, buf);

}


void PEpsonTMT88::print(uint margin, const QString& str) {

    *stream << QString("").leftJustified( margin )  << str;

}


void PEpsonTMT88::println(uint margin, const QString& str) {

    print(margin, str);
    print(margin, "\n\r");


}

void PEpsonTMT88::println(const QString& str) {

    println(0, str);

}


void PEpsonTMT88::printLogo( ) {

    if(!docAttrs.undefined("print_logo", nil).toBool())
        return;

    char logo[] = {0x1C, 0x70, 0x01, 0x30, 0x0};
    setCenterJustify();
    print(0, logo);

    printSeparatorLine();

}




void PEpsonTMT88:: printBarcode(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "printBarcode:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString barcode = source_args.value<PVariantMapPtr>()->include("barcode") ? source_args.value<PVariantMapPtr>()->operator[]("barcode").toString() : QVariant(QString("8001234567897")).toString();args.removeByKey("barcode");
int type = source_args.value<PVariantMapPtr>()->include("type") ? source_args.value<PVariantMapPtr>()->operator[]("type").toInt() : QVariant(67).toInt();args.removeByKey("type");
int font = source_args.value<PVariantMapPtr>()->include("font") ? source_args.value<PVariantMapPtr>()->operator[]("font").toInt() : QVariant(0).toInt();args.removeByKey("font");
int width = source_args.value<PVariantMapPtr>()->include("width") ? source_args.value<PVariantMapPtr>()->operator[]("width").toInt() : QVariant(50).toInt();args.removeByKey("width");
int height = source_args.value<PVariantMapPtr>()->include("height") ? source_args.value<PVariantMapPtr>()->operator[]("height").toInt() : QVariant(60).toInt();args.removeByKey("height");
int verticalSpace = source_args.value<PVariantMapPtr>()->include("verticalSpace") ? source_args.value<PVariantMapPtr>()->operator[]("verticalSpace").toInt() : QVariant(2).toInt();args.removeByKey("verticalSpace");


    char GS = 29;
    char ESC = 27;

    char len = barcode.length();

    char enableHri[] = {GS, 'H', 0x02, 0x0}; 
    char barcodeCommand[] = {GS, 'k', (char)type, len, 0x0};

    char setFont[] = {ESC, 'm', (char)font, 0x0};
    print(0, setFont);

    char setWidth[] = {GS, 'w', (char)width, 0x0};
    char setHeight[] = {GS, 'h', (char)height, 0x0};
    println(setWidth);
    println(setHeight);



    print(0, enableHri);
    print(0, barcodeCommand);
    print(0, barcode);

    verticalSpace += 3;
    while(verticalSpace--) println("");

}


void PEpsonTMT88::printRowFiscal(const QString& department, const QString& quantity, const QString& description, const QString& price) {


}
