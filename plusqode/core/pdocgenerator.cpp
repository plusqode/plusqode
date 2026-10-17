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



   #include "core/pdocgenerator.h"

   
   

PDocGenerator:: PDocGenerator(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PDocGenerator:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString fileName = source_args.value<PVariantMapPtr>()->include("fileName") ? source_args.value<PVariantMapPtr>()->operator[]("fileName").toString() : QVariant(nil).toString();args.removeByKey("fileName");
QString style = source_args.value<PVariantMapPtr>()->include("style") ? source_args.value<PVariantMapPtr>()->operator[]("style").toString() : QVariant(QString("Atomic")).toString();args.removeByKey("style");
QString category = source_args.value<PVariantMapPtr>()->include("category") ? source_args.value<PVariantMapPtr>()->operator[]("category").toString() : QVariant(nil).toString();args.removeByKey("category");


    this->fileName = fileName;
    this->style = style;
    this->category = category;
    this->source_location = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    baseFileName = PDir::fileNameFromFullFileName(this->fileName);

    fileContent = PDir::fileContent(fileName);

    lines = PDir::fileLines(fileName);

    

    int currentLine = 0;
     lines.forEachQString([&] (QString line) mutable {
        currentLine++;
        int i1 = line.indexOf("$DEMO");
        int i2 = line.indexOf("{");
        if(i1 != -1 && i2 != -1 )
            source_location << currentLine;
    });

    qDebug() << source_location.toString();

    qtPlusPath = PGlobal::basePath();

    this->fromLine = source_location[0].toInt() - 1;

    htmlFileName =  PString(QString("%1/app/docs/%2.html").arg(qtPlusPath).arg(baseFileName));

    QFile::remove(htmlFileName);
    QFile::copy(PString(QString("%1/app/docs/header.html").arg(qtPlusPath)), htmlFileName);

    htmlFile = new QFile(htmlFileName);
    if (!htmlFile->open(QIODevice::Append | QIODevice::Text))
        return;

    htmlStream = new QTextStream(htmlFile);

}

PDocGenerator::~PDocGenerator() {


    htmlFile->close();

    delete htmlStream;

    delete htmlFile;


}

PVariant PDocGenerator:: sourceCode(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "sourceCode:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
int fromLine = source_args.value<PVariantMapPtr>()->include("fromLine") ? source_args.value<PVariantMapPtr>()->operator[]("fromLine").toInt() : QVariant(0).toInt();args.removeByKey("fromLine");
int toLine = source_args.value<PVariantMapPtr>()->include("toLine") ? source_args.value<PVariantMapPtr>()->operator[]("toLine").toInt() : QVariant(     this->lines.count()).toInt();args.removeByKey("toLine");
bool toEndSection = source_args.value<PVariantMapPtr>()->include("toEndSection") ? source_args.value<PVariantMapPtr>()->operator[]("toEndSection").toBool() : QVariant(false).toBool();args.removeByKey("toEndSection");
bool firstAndLastLine = source_args.value<PVariantMapPtr>()->include("firstAndLastLine") ? source_args.value<PVariantMapPtr>()->operator[]("firstAndLastLine").toBool() : QVariant(false).toBool();args.removeByKey("firstAndLastLine");
bool strip = source_args.value<PVariantMapPtr>()->include("strip") ? source_args.value<PVariantMapPtr>()->operator[]("strip").toBool() : QVariant(false).toBool();args.removeByKey("strip");
bool eol = source_args.value<PVariantMapPtr>()->include("eol") ? source_args.value<PVariantMapPtr>()->operator[]("eol").toBool() : QVariant(true).toBool();args.removeByKey("eol");
bool lineNumber = source_args.value<PVariantMapPtr>()->include("lineNumber") ? source_args.value<PVariantMapPtr>()->operator[]("lineNumber").toBool() : QVariant(false).toBool();args.removeByKey("lineNumber");


    int spaceNumber = -1;

    this->fromLine = fromLine;
    if(toEndSection) {
        QString firstLine = lines[fromLine].toString();
        #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
            spaceNumber = firstLine.indexOf(QRegExp("[^ ]"));
        #else
            spaceNumber = firstLine.indexOf(QRegularExpression("[^ ]"));
        #endif
    }


    PVariant _lines = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    for(int i = fromLine; i < toLine; i++) {
        PString line = lines[i].toString();
        if(strip) line = line.trimmed();

        if(!eol)
            line = line.mid(0, -2);

        if(lineNumber) {
             QString tmpLine = line.mid(4, -1);
             line = PString(QString("%1 %2").arg(i + 1).arg(tmpLine));
         }

        _lines << line.fromTo(0, -1); 

        

        #if (QT_VERSION < 0x060000)
        if(toEndSection && i > fromLine && lines[i].toString().indexOf(QRegExp("[^\\s]+")) == spaceNumber)
            break;
        #else
        if(toEndSection && i > fromLine && lines[i].toString().indexOf(QRegularExpression("[^\\s]+")) == spaceNumber)
            break;
        #endif


    }

    if(firstAndLastLine)
        return _lines;
    else
        return _lines.value<PVariantListPtr>()->mid2(1, -2 + 1);


}



PVariant PDocGenerator::info() { 

    int i = fromLine - 1;

    while(lines[i].toString().trimmed() == "" || lines[i].toString().trimmed()[0] == '/')
        i--;

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    int left = i + 1;

    PVariant l = lines.value<PVariantListPtr>()->mid2(left, fromLine-left);

     l.forEachQString([&] (QString line) mutable {
        if(line.trimmed()[0] == '/')
            result << line;
    });

    return result;

}




PVariant PDocGenerator::valueOf(QString variable) {

    PVariant lines = this->info();

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

     lines.forEachQString([&] (QString line) mutable {
        int index = line.indexOf(variable);
        if(index != -1)
            result << line.mid(index + variable.length() + 1).trimmed();
    });

    return result;

}


void PDocGenerator:: writeOnHtmlFile(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "writeOnHtmlFile:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString title = source_args.value<PVariantMapPtr>()->include("title") ? source_args.value<PVariantMapPtr>()->operator[]("title").toString() : QVariant(nil).toString();args.removeByKey("title");
PVariant descriptions = source_args.value<PVariantMapPtr>()->include("descriptions") ? source_args.value<PVariantMapPtr>()->operator[]("descriptions") : nil;args.removeByKey("descriptions");
PVariant sourceCode = source_args.value<PVariantMapPtr>()->include("sourceCode") ? source_args.value<PVariantMapPtr>()->operator[]("sourceCode") : nil;args.removeByKey("sourceCode");
int fromLine = source_args.value<PVariantMapPtr>()->include("fromLine") ? source_args.value<PVariantMapPtr>()->operator[]("fromLine").toInt() : QVariant(-1).toInt();args.removeByKey("fromLine");
bool showLineNumber = source_args.value<PVariantMapPtr>()->include("showLineNumber") ? source_args.value<PVariantMapPtr>()->operator[]("showLineNumber").toBool() : QVariant(true).toBool();args.removeByKey("showLineNumber");
QString style = source_args.value<PVariantMapPtr>()->include("style") ? source_args.value<PVariantMapPtr>()->operator[]("style").toString() : QVariant(this->style).toString();args.removeByKey("style");


    if(fromLine == -1)
        fromLine++;

  QString html = "";
  if(title != nil) html = PString(QString("<h3>%1</h3>\n").arg(title));

  if(descriptions != nil) {
      QString tmp = descriptions.join("<br>");
      html += PString(QString("<h4>%1</h4>\n").arg(tmp));
  }

  QString showLineNumberStr = (showLineNumber) ? "true" : "false";

  html += PString(QString("<pre class='language-cpp'><code class='language-cpp'>"));

  if(!title.isNull()) *htmlStream << html;

  if(sourceCode.typeName() != "Array")
    *htmlStream << PString(QString("%1\n").arg(sourceCode.toString()));
  else {
    QString s = sourceCode.join("\n");
    *htmlStream << PString(QString("%1\n").arg(s));
  }
  if(title != nil) *htmlStream << PString(QString("</code></pre>\n"));

}



void PDocGenerator::run(PDemo& demos) {

    QString mainTitle = valueOf("$mainTitle")[0].toString();
    PVariant mainDescription = valueOf("$mainDescription");
    


    if(mainTitle != nil) *htmlStream << PString(QString("<h2>%1</h2>").arg(mainTitle));

    qDebug() << mainDescription.toString();

    if(mainDescription != nil) {
        QString tmp = mainDescription.join("<br>");
        *htmlStream << PString(QString("<h4>%1</h2>").arg(tmp));
    }

    int i = 0;
     source_location.forEachQString([&] (QString sl) mutable {
        PVariant source =    
                                        
                                        
                                        
                                        
                                        sourceCode(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("fromLine",   sl.toInt()-1)->append("toEndSection", true)->append("firstAndLastLine", false)->append("strip", false)->append("eol", false)->append("lineNumber", true)))));

        QString title = valueOf("$title")[0].toString();
        if(title.isNull())
            title = PString(QString("Demo %1").arg(i));

        PVariant description = valueOf("$description");

        PVariant content = description + PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(QString(" "))))) + source;

        PWindow window(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
        int bg = rand() % 32;
        window.setColor(bg, bg + 8);
        window.gotoyx(1, 0);
        title = PString(QString("%1 (%2)").arg(title).arg(baseFileName));
        window.   window(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("title", title)->append("content", content)))));
        window.render();
             writeOnHtmlFile(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("title", title)->append("description", description)->append("sourceCode", content)))));


        PDebug::setBufferize(true);
        demos.demos[i]();
        QString result = PDebug::setBufferize(false);


        PWindow outWindow(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
        outWindow.setColor(9, 15);
        outWindow.gotoyx(1, 0);
        title = PString(QString("Output: %1").arg(title));

        QStringList l = result.split("\n");

        PVariant list = PVariant::fromQStringList(l);

        outWindow.   window(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("title", title)->append("content",    list.value<PVariantListPtr>()->mid2(0, -2 + 1))))));
        outWindow.render();

        result = PString(QString("[plusqode]$ ./%1\n").arg(baseFileName)) + result;

         
                         
                         
                         writeOnHtmlFile(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("title", QString(""))->append("sourceCode", result)->append("style", QString("Atomic"))->append("showLineNumber", false)))));


        i++;
    });


}
