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



   #include "core/pview.h"

   
   

PView::PView() {

    this->fileName = QString();

}

PView::~PView() {


    PVariant names = PVariant::fromQStringList(views.keys());
     names.forEachQString([&] (QString viewName) mutable {

        delete views[viewName];
    });

}


QString PView::variantToString(PVariant var, int indent) {

    if(var.typeName() == "Array") {
        PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
         var.forEachPVariant([&] (PVariant child) mutable {
            result << variantToString(child);
        });
        return result.join("\n");
    }

    QString name = var["name"].toString();
    QString value = var["value"].toString();
    PVariant attrs = var["attrs"];
    PVariant children = var["children"];

    QString vals = attrs.join(" ", "\"", "=");
    PVariant tag = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    QString space = QString().fill(' ', indent);

    if(children.count() == 0)
        return PString(QString("%1<%2 %3/>").arg(space).arg(name).arg(vals));;

    tag << PString(QString("%1<%2 %3>").arg(space).arg(name).arg(vals));
     children.forEachPVariant([&] (PVariant child) mutable {
        tag << QString("%1").arg(variantToString(child, indent + 4));
    });
    tag << PString(QString("%1</%2>").arg(space).arg(name));
    return tag.join("\n");

}


void PView::initByFileName(QString fileName) {

    this->fileName = fileName;

    if(!QFile().exists(fileName))
        return;

    viewStr = PDir::fileContent(fileName);
    viewVariant = toVariant(viewStr);

}

void PView::initByViewStr(QString viewStr) {

    this->viewStr = viewStr;
    viewVariant = toVariant(viewStr);

}

void PView::initByViewVariant(PVariant viewVariant) {

    this->viewStr = variantToString(viewVariant);
    this->viewVariant = viewVariant;

}

PVariant PView::toVariant() {

    return viewVariant;

}


PString PView::toString() {

    return viewStr;

}

PVariant PView:: findBy(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "findBy:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant tag = source_args.value<PVariantMapPtr>()->include("tag") ? source_args.value<PVariantMapPtr>()->operator[]("tag") : nil;args.removeByKey("tag");
PVariant root = source_args.value<PVariantMapPtr>()->include("root") ? source_args.value<PVariantMapPtr>()->operator[]("root") : viewVariant;args.removeByKey("root");


    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    if(root.typeName() == "Hash") {
        if(root.undefined("name", nil).toString() == tag.undefined("name", nil).toString() &&
            root.undefined("attrs", nil).include(tag.undefined("attrs", nil)))
            return PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(root))));
        else
            return    findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", tag)->append("root",     root["children"])))));
    }

    if(root.typeName() == "Array")
     root.forEachPVariant([&] (PVariant child) mutable {
        result +=    findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", tag)->append("root", child)))));
    });

    return result;

}


PView* PView::partialByType(QString type) {

    if(views.contains(type)) {
         PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "PView::partialByType: cached view returned";
        return views[type];
    }

    PVariant result = this->     findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("view"))->append("attrs", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("type", type)))))))))))));

    if(result.isEmpty())
        return 0;

    PView* view = new PView();
    view->initByViewVariant(result[0]);
    views[type] = view;
    return view;

}

PView* PView::partialByName(QString name) {

    if(views.contains(name)) {
         PLog(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("color", QString("red")))))).debug() << "PView::partialByName: cached view returned";
        return views[name];
    }

    PVariant result = this->     findBy(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", QString("view"))->append("attrs", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name", name)))))))))))));

    if(result.isEmpty())
        return 0;

    PView* view = new PView();
    view->initByViewVariant(result[0]);
    views[name] = view;
    return view;

}


PVariant PView::toVariant(const QString& view) {

    QDomDocument xmlDocument;

    if(view.startsWith("<?xml"))
        xmlDocument.setContent(view);
    else 
        xmlDocument.setContent(PString(QString("<root> %1 </root>").arg(view)));

    QDomElement root = xmlDocument.documentElement();

    PVariant result = this->toVariant(&root)["children"];

    

    if(result.count() == 1)
        return result[0];
    else
        return result;

}


PVariant PView::toVariant(QDomElement* root) {

    

    PVariant elem = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("name",   root->nodeName())->append("value",     root->text()))));

    PVariant attrs = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    elem["attrs"] = attrs;

    
    QDomNamedNodeMap _attrs = root->attributes();
    for(int j = 0; j < _attrs.count(); j++)
        attrs[_attrs.item(j).nodeName()] = _attrs.item(j).nodeValue();
        

    PVariant children = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    elem["children"] = children;

    QDomNodeList nodeList = root->childNodes();
    for(int i = 0; i < nodeList.count(); i++) {
        QDomNode domNode = nodeList.at(i);
        QDomElement domElem = domNode.toElement();
        PVariant child = this->toVariant(&domElem);
        child["parentPtr"] = elem; 
        children << child;
    }

    return elem;

}
