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



   #include "dom/pdom.h"

   
   

void PDom::init(const QString& tag, const QString& innerHTML) {

    this->tag = tag;
    this->innerHTML = innerHTML;
    this->attrs = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    this->placeholders = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
    this->enablePlaceholder = false; 

    this->parent = 0;
    this->styles = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    this->ct = true;

    this->indentSpace = 0;

}


PDom::PDom(const QString& tag, const QString& innerHTML) {

    this->init(tag, innerHTML);

}


PDom:: PDom(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "PDom:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString tag = source_args.value<PVariantMapPtr>()->include("tag") ? source_args.value<PVariantMapPtr>()->operator[]("tag").toString() : QVariant(QString("div")).toString();args.removeByKey("tag");
QString innerHTML = source_args.value<PVariantMapPtr>()->include("innerHTML") ? source_args.value<PVariantMapPtr>()->operator[]("innerHTML").toString() : QVariant(QString("")).toString();args.removeByKey("innerHTML");


    this->init(tag, innerHTML);

}

PDom::~PDom() {for(int _i_0_ = 0; _i_0_ < children.count(); _i_0_++) {
PDom* child = children.operator[](_i_0_);
        delete child;
    }

}

PDom* PDom::_set(QString attr, PVariant value, bool overwrite) {

    if(value == "delete")
        attrs.removeByKey(attr);

    attrs.set(attr, value, overwrite);

    return this;

}


PDom* PDom:: set(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "set:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
bool overwrite = source_args.value<PVariantMapPtr>()->include("overwrite") ? source_args.value<PVariantMapPtr>()->operator[]("overwrite").toBool() : QVariant(false).toBool();args.removeByKey("overwrite");


       args.forEachQString_PVariant([&] (QString attr,PVariant value) mutable {
        this->_set(attr, value, overwrite);
    });

    return this;

}

PDom* PDom::unset(const QString& attr) {

    this->attrs.removeByKey(attr);

    return this;

}


PDom* PDom:: setStyle(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "setStyle:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];


       args.forEachQString_PVariant([&] (QString attr,PVariant value) mutable {
        if(value == "delete")
            this->styles.removeByKey(attr);
        else
            this->styles[attr] = value;
    });

    return this;

}

PDom* PDom::setStyles(PVariant styles) {

    this->styles = styles;

    return this;

}

PDom* PDom::storeStyle() {

  if(this->styles.isEmpty())
    return this;

  QString result = this->styles.join("; ", "");

  this-> set(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("style", result)))));

  return this;

}

PDom* PDom::setParent(PDom* parent) {

    this->parent = parent;
    return this;

}

PDom& PDom::operator<<(PDom* child) {

    child->setParent(this);

    this->children << child;

    return *this;

}

PDom& PDom::operator<<(QList<PDom*> children) {for(int _i_1_ = 0; _i_1_ < children.count(); _i_1_++) {
PDom* child = children.operator[](_i_1_);
        *this << child;
    }

    return *this;

}




QList<PDom*> PDom::getElementBy(const QString& attr, const QString& value, int searchType) {

    QList<PDom*> result;

    if(this->attrs.include(attr) and this->attrs[attr] == value)
        result << this;for(int _i_2_ = 0; _i_2_ < children.count(); _i_2_++) {
PDom* child = children.operator[](_i_2_);
        if(this->attrs.include(attr) and this->attrs[attr] == value)
            result << child;
    }

    if(searchType == 1)for(int _i_3_ = 0; _i_3_ < children.count(); _i_3_++) {
PDom* child = children.operator[](_i_3_);
        result += child->getElementBy(attr, value, searchType);
    }

    return result;

}


PDom* PDom::setPlaceholder(const QString& placeholder, const QString& value) {

    this->enablePlaceholder = true;
    if(value.isNull()) {
        this->placeholders.removeByKey(placeholder);
        return this;
    }
    this->placeholders[placeholder] = value;
    return this;

}


PDom* PDom::setPlaceholders(PVariant placeholders) {

    this->placeholders = placeholders;

    return this;

}


QString PDom::replacePlaceHolder(const QString& value) {

    if(!this->enablePlaceholder)
        return value;

       placeholders.forEachQString_QString([&] (QString key,QString value) mutable {
        value = value.replace(key, value);
    });

    return value;

}


QString PDom::html() {

    PVariant attrsTmp = this->attrs.dup();

    
    this->storeStyle();

    if(this->attrs.isEmpty()) return "";

    QString result = "";

       this->attrs.forEachQString_QString([&] (QString key,QString value) mutable {
        if(!value.isNull()) {
            value = this->replacePlaceHolder(value);
            result += PString(QString("%1=\"%2\" ").arg(key).arg(value));
        }
        else
            result += PString(QString("%1 ").arg(key));
    });

    this->attrs = attrsTmp;
    return result;

}


QString PDom::openTag() {

    if(this->tag.isNull())
        return "";

    QString slash = (this->ct) ? "" : "/";

    QString result = this->html();

    return PString(QString("<%1 %2%3>").arg(this->tag).arg(result).arg(slash));

}

QString PDom::closeTag() {

    if(this->tag.isNull())
        return "";

    return (this->ct) ? PString(QString("</%1>").arg(this->tag)) : "";

}

PDom* PDom::setCloseTag(bool ct) {

    this->ct = ct;
    return this;

}


QString PDom::toHtml() {

    QStringList htmlList;
    htmlList << this->openTag();
    htmlList << this->innerHTML;for(int _i_4_ = 0; _i_4_ < children.count(); _i_4_++) {
PDom* child = children.operator[](_i_4_);
        htmlList << child->toHtml();
    }

    htmlList << this->closeTag();

    return htmlList.join("\n");

}


QString PDom:: inlinetag(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "inlinetag:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString tag = source_args.value<PVariantMapPtr>()->include("tag") ? source_args.value<PVariantMapPtr>()->operator[]("tag").toString() : QVariant(nil).toString();args.removeByKey("tag");


    return  PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", tag))))).set(args)->setCloseTag(false)->toHtml();

}

QString PDom:: htmltag(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "htmltag:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString tag = source_args.value<PVariantMapPtr>()->include("tag") ? source_args.value<PVariantMapPtr>()->operator[]("tag").toString() : QVariant(nil).toString();args.removeByKey("tag");


    return  PDom(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("tag", tag))))).set(args)->toHtml();

}
