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

PVariantMap::PVariantMap() : QVariantHash(), QSharedData() {

    defaultValue = nil;

}


PVariantMap::~PVariantMap() {

    

}


PVariantMap* PVariantMap::append(QString key, QVariant value) {

    (*this)[key] = value;
    return this;

}

QStringList PVariantMap::keys() {

    return _keys;

}

int PVariantMap::remove(QString key) {

    _keys.removeOne(key);

    return QVariantHash::remove(key);

}

QVariant PVariantMap::take(QString key) {

    _keys.removeOne(key);

    return QVariantHash::take(key);

}

void PVariantMap::clear() {

    QVariantHash::clear();
    _keys.clear();

}

bool PVariantMap::operator==(PVariant var) {

    if(var.userType() != qMetaTypeId<PVariantMapPtr>())
        return false;

    if(this->count() != var.count())
        return false;PVariant _keys_0_ = var.keys();
for(int _i_0_ = 0; _i_0_ < _keys_0_.count(); _i_0_++) {
PString key = _keys_0_[_i_0_].toString();
QString value = var.operator[](key).toString();
        if((*this)[key].toString() !=  value)
            return false;
    }

    return true;

}

bool PVariantMap::operator!=(PVariant var) {

    return !((*this) == var);

}

PVariant& PVariantMap::operator[](QString key) {

    if(!this->contains(key)) {
        _keys << key;
        QVariantHash::operator[](key) = defaultValue;
    }

    return (PVariant&)((QVariantHash*)this)->operator[](key);

}

PVariant PVariantMap::operator()(QString key) {

    if(!this->contains(key))
        return (PVariant&)defaultValue;

    return ((QVariantHash*)this)->operator[](key);

}


PVariant& PVariantMap::operator[](int index) {

    QString key = this->keys()[index];
    return (*this)[key];

}


PVariantMap& PVariantMap::set(QString key, PVariant value, bool overwrite) {

    if (!this->include(key) || overwrite) (*this)[key] = value;
    return (*this);

}


PVariantMap& PVariantMap:: set(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "set:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
bool overwrite = source_args.value<PVariantMapPtr>()->include("overwrite") ? source_args.value<PVariantMapPtr>()->operator[]("overwrite").toBool() : QVariant(false).toBool();args.removeByKey("overwrite");
PVariant values = source_args.value<PVariantMapPtr>()->include("values") ? source_args.value<PVariantMapPtr>()->operator[]("values") : PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));args.removeByKey("values");
PVariant _keys_1_ = values.keys();
for(int _i_1_ = 0; _i_1_ < _keys_1_.count(); _i_1_++) {
PString key = _keys_1_[_i_1_].toString();
PVariant value = values.operator[](key);
        this->set(key, value, overwrite);
    }
    return (*this);

}



PVariantMap& PVariantMap::operator+=(PVariant var) {PVariant _keys_2_ = var.keys();
for(int _i_2_ = 0; _i_2_ < _keys_2_.count(); _i_2_++) {
PString key = _keys_2_[_i_2_].toString();
PVariant value = var.operator[](key);
        this->append(key, value);
    }

    return *this;

}

bool PVariantMap::include(PVariant var) {

    if(var.isNull()) return true;

    if(var.typeName() == "QString")
        return (this->keys().indexOf(var.toString()) != - 1);
    if(var.typeName() == "Hash") {
        PVariant intersection = (this->toVariant() & var);
        return (intersection == var);
    }

    qDebug() << PString("Error: PVariantMap::include:").red() << this->toString() << " - " << var.toString().red();

    return true;

}

QString PVariantMap::join(QString separator, int indent) {

    QString prefix = PString::space(indent);

    QStringList result;

    foreach(QString key, this->keys()) {
        QString typeName = this->operator[](key).typeName();
        if(typeName == "QString" || typeName == "QDate" || typeName == "QTime")
            result << QString("%1%3: \"%2\"").arg(prefix).arg(this->operator[](key).toString()).arg(key);
        else if(this->operator[](key).typeName() == "QChar")
            result << QString("%1%3: \"%2\"").arg(prefix).arg(this->operator[](key).toString()).arg(key);
        else if(key.endsWith("Ptr")) 
            result << QString("%1%3: %2").arg(prefix).arg("#ptr").arg(key);
        else
            result << QString("%1%3: %2").arg(prefix).arg(this->operator[](key).toString(separator, indent)).arg(key);
    }

    return result.join(separator);
}


QString PVariantMap::toString(QString separator, int indent) {

    return QString("{%1}").arg(join(separator));
    QString prefix = PString::space(indent);
    return QString("{\n%2\n%1}").arg(prefix).arg(join(separator, indent + 3));


}

PVariant PVariantMap::toVariant() {

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    PVariant keys = PVariant().fromQStringList(this->keys());for(int _i_3_ = 0; _i_3_ < keys.count(); _i_3_++) {
QString key = keys.operator[](_i_3_).toString();
        result[key] = (*this)[key];
    }

    return result;

}

PVariant PVariantMap::undefined(QString key, PVariant value) {

    if(key.endsWith('=')) {
        key.chop(1);
        (*this)[key] = value;
    }

    return (*this)(key);

}

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)

PVariant PVariantMap::fromJson(const QJsonObject& jsonObject) {

    
    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    for (auto it = jsonObject.constBegin(); it != jsonObject.constEnd(); ++it) {
        QString key = it.key();
        key = key.remove('"');
        
        result[key] = PVariant::fromJson(it.value());
    }

    return result;
}


QJsonObject PVariantMap::toJson() {

    QJsonObject jsonObject;

    foreach(QString key, this->keys()) {
        jsonObject.insert(key, this->operator[](key).toJson());
    }

    return jsonObject;

}


#endif



