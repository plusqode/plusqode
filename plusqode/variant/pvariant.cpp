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

   
   
   #include "configuration/pconfigparser.h"

   
   
   
   
   
 
   #include "app/modules/pmodules.h"

   
   
   
   
   
 
   
   
   
 
   
 
 

PVariant::PVariant() {
}

PVariant::PVariant(QString str) : QVariant(str) {
}

PVariant::PVariant(QByteArray byteArray) : QVariant(byteArray) {
}

PVariant::PVariant(QChar chr) : QVariant(chr) {
}

PVariant::PVariant(QDate date) : QVariant(date) {
}

PVariant::PVariant(QDateTime dateTime) : QVariant(dateTime) {
}


PVariant::PVariant(const char* str) : QVariant(str) {
}

PVariant::PVariant(int value) : QVariant(value) {
}

PVariant::PVariant(float value) : QVariant(value) {
}

PVariant::PVariant(double value) : QVariant(value) {
}

PVariant::PVariant(bool value) : QVariant(value) {
}

PVariant::PVariant(QVariant var) : QVariant(var) {
}



int PVariant::toInt() { 

    return QString::number(this->toDouble(), 'f', 0).toInt();

}


PVariant PVariant::dup() {

    if(this->typeName() == "Hash") {
        PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
           this->forEachQString_PVariant([&] (QString fieldName,PVariant elem) mutable {
            if(elem.typeName() == "Array" || elem.typeName() == "Hash") {
                
                if(!fieldName.endsWith("Ptr")) result[fieldName] = elem.dup();
            }
            else
                result[fieldName] = elem;
        });
        return result;
    }

    if(this->typeName() == "Array") {
        PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
         this->forEachPVariant([&] (PVariant elem) mutable {
            if(elem.typeName() == "Array" || elem.typeName() == "Hash")
                result << elem.dup();
            else
                result << elem;
        });
        return result;
    }

    return nil;

}


PVariant PVariant::reverse() {

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    for(int i = count() - 1; i >= 0; i--)
            result << this->operator()(i);

    return result;

}


PVariant PVariant::fromString(QString str) {

    PConfigParser parser(str, false);

    return parser.startParsing();

}


PVariant PVariant::fromQStringList(QStringList list) {

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));for(int _i_0_ = 0; _i_0_ < list.count(); _i_0_++) {
PVariant value = list.operator[](_i_0_);
        result.append(value);
    }

    return result;

}

PVariant PVariant::fromQMap(QMap<QString, QVariant>& map) {

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    foreach(QString key, map.keys())
        result[key] = map[key];

    return result;

}

PVariant PVariant::fromItemsAndValues(PVariant items, PVariant values) {

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    if(items.count() != values.count())
        return result;

       items.forEachWithIndexQString_int([&] (QString item,int i) mutable {
        result[item] = values[i];
    });

    return result;

}


#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)

PVariant PVariant::fromJson(const QJsonValue& jsonValue) {

    switch (jsonValue.type()) {
        case QJsonValue::Object:
            return PVariantMap::fromJson(jsonValue.toObject());

        case QJsonValue::Array:
            return PVariantList::fromJson(jsonValue.toArray());

        case QJsonValue::String: {
            QString jsonString = jsonValue.toString();

            
            QDateTime dt = QDateTime::fromString(jsonString, Qt::ISODate);
            if (dt.isValid()) {
                return QVariant::fromValue(dt);
            }

            
            QDate d = QDate::fromString(jsonString, Qt::ISODate);
            if (d.isValid()) {
                return QVariant::fromValue(d);
            }

            
            QTime t = QTime::fromString(jsonString, Qt::ISODate);
            if (t.isValid()) {
                return QVariant::fromValue(t);
            }

            return PVariant(jsonValue.toString());
        }

        case QJsonValue::Double:
            return PVariant(jsonValue.toDouble());

        case QJsonValue::Bool:
            return PVariant(jsonValue.toBool());

        case QJsonValue::Null:
        case QJsonValue::Undefined:
        default:
            return nil;
    }

}


QJsonValue PVariant::toJson() {

    if(this->typeName() == "double")
        return QJsonValue(QString::number(toDouble(), 'f', PGlobal::decimalPrecision()));

    QVariant* ptr = (QVariant*)this;

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->value<PVariantListPtr>()->toJson();
    else if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return (*this->value<PVariantMapPtr>()).toJson();

    return QJsonValue(ptr->toString());

}


#endif

PVariantList& PVariant::toList() {

    return *this->value<PVariantListPtr>();

}



PVariantMap& PVariant::toMap() {

    return *this->value<PVariantMapPtr>();

}



PVariant PVariant::toMap(PVariant list) {

    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        qDebug() << "PVariant::toMap(...): this variant is " << this->typeName() << " instead than a List";

    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    int i = 0;
     this->forEachQString([&] (QString fieldName) mutable {
        result[fieldName] = list[i++];
    });

    return result;

}

PModelPtr PVariant::toModelPtr() {

    return this->value<PModelPtr>();

}

bool PVariant::operator<(PVariant var) {

    if(this->typeName() == "int")
        return ((*this).toInt() < var.toInt());
    if(this->typeName() == "float")
        return ((*this).toFloat() < var.toFloat());
    if(this->typeName() == "double")
        return ((*this).toDouble() < var.toDouble());
    if(this->typeName() == "QString")
        return ((*this).toString() < var.toString());
    if(this->typeName() == "date")
        return ((*this).toDate() < var.toDate());
    if(this->typeName() == "time")
        return ((*this).toTime() < var.toTime());
    if(this->typeName() == "time")
        return ((*this).toDateTime() < var.toDateTime());

    return false;

}


bool PVariant::equal(PVariant var) {

    if(this->typeName() == "int")
        return ((*this).toInt() == var.toInt());
    if(this->typeName() == "float")
        return ((*this).toFloat() == var.toFloat());
    if(this->typeName() == "double")
        return ((*this).toDouble() == var.toDouble());
    if(this->typeName() == "QString")
        return ((*this).toString() == var.toString());
    if(this->typeName() == "date")
        return ((*this).toDate() == var.toDate());
    if(this->typeName() == "time")
        return ((*this).toTime() == var.toTime());
    if(this->typeName() == "time")
        return ((*this).toDateTime() == var.toDateTime());

    return false;

}


bool PVariant::lessThan(PVariant var, PVariant sortFields) {

    if(sortFields == nil) sortFields = this->keys();

    if(this->typeName() == "Hash") {for(int _i_1_ = 0; _i_1_ < sortFields.count(); _i_1_++) {
QString fieldName = sortFields.operator[](_i_1_).toString(); 
            if(!((*this)[fieldName].equal(var[fieldName])))
                return ((*this)[fieldName] < var[fieldName]);
        }
        return false;
    }
    if(this->typeName() == "Array")for(int i = 0; i < this->count(); i++) {
PVariant elem = this->operator[](i);
            if(!elem.equal(var[i]))
                return elem < var[i];
        }

    return (*this) < var;

}

PVariant& PVariant::operator[](int index) {

    if(this->typeName() == "Hash")
        return this->toMap()[index];
    if(this->typeName() == "Array")
        return this->toList()[index];

    qDebug() << "Fatal Error -> PVariant::operator[](int index)";
    exit(0);

}

PVariant& PVariant::operator[](char* key) {

    return this->toMap()[key];

}

PVariant& PVariant::operator[](const QString key) {

    return this->toMap()[key];

}

PVariant& PVariant::set(QString key, PVariant value, bool overwrite) {

    this->toMap().set(key, value, overwrite);

    return *this;

}


PVariant& PVariant:: set(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "set:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
bool overwrite = source_args.value<PVariantMapPtr>()->include("overwrite") ? source_args.value<PVariantMapPtr>()->operator[]("overwrite").toBool() : QVariant(false).toBool();args.removeByKey("overwrite");
PVariant values = source_args.value<PVariantMapPtr>()->include("values") ? source_args.value<PVariantMapPtr>()->operator[]("values") : PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));args.removeByKey("values");


    this->toMap().   set(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("overwrite", overwrite)->append("values", values)))));

    return *this;

}


PVariant PVariant::undefined(PString key, PVariant value) {

    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return this->toMap().undefined(key, value);

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->toList().undefined(key, value);

    if(value != nil)
        qDebug() << "PVariant::undefined: Error Type for " << this->typeName();

    return nil;

}


PVariant PVariant::operator()(char* key) {

    return this->toMap()(key);

}

PVariant PVariant::operator()(const QString key) {

    return this->toMap()(key);

}

PVariant PVariant::operator()(int i) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->toList()(i);

    return nil;

}


PVariant& PVariant::append(QVariant value) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        this->toList().append(value);
    else
        qDebug() << "PVariant::append(...): this variant is " << this->typeName() << " instead than a List";

    return *this;

}

PVariant& PVariant::appendIfNotExists(QVariant value) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        this->toList().appendIfNotExists(value);

    else
        qDebug() << "PVariant::appendIfNotExists(...): this variant is " << this->typeName() << " instead than a List";

    return *this;

}

PVariant& PVariant::append(QString key, QVariant value) {

    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        this->toMap().append(key, value);
    else
        qDebug() << "PVariant::append(...): this variant is " << this->typeName() << " instead than a Map";

    return *this;

}


PVariant PVariant::removeByIndex(int index) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->toList().takeAt(index);

    return PVariant();

}

bool PVariant::removeByValue(QVariant value) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->toList().removeByValue(value);

    return false;
}

PVariant PVariant::removeByKey(QString key) {

    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return this->toMap().take(key);

    return PVariant();

}


int PVariant::count() {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->toList().count();
    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return this->toMap().count();

    return -1;

}


PVariant& PVariant::operator=(QVariant var) {

    return (PVariant&)((QVariant*)this)->operator=(var);

}

PVariant& PVariant::operator=(QString str) {

    return (PVariant&)((QVariant*)this)->operator=(str);

}

PVariant& PVariant::operator=(const char* str) {

    return (PVariant&)((QVariant*)this)->operator=(str);

}

PVariant& PVariant::operator=(int value) {

    return (PVariant&)((QVariant*)this)->operator=(value);

}

PVariant& PVariant::operator=(double value) {

    return (PVariant&)((QVariant*)this)->operator=(value);

}

PVariant& PVariant::operator=(float value) {

    return (PVariant&)((QVariant*)this)->operator=(value);

}

PVariant& PVariant::operator=(bool value) {

    return (PVariant&)((QVariant*)this)->operator=(value);

}


PVariant& PVariant::operator+=(PVariant var) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>()) {
         var.forEachPVariant([&] (PVariant value) mutable {
            this->append(value);
        });
    }

    else if(this->userType() == qMetaTypeId<PVariantMapPtr>()) {
           var.forEachQString_PVariant([&] (QString key,PVariant value) mutable {
            this->append(key, value);
        });

    }

    return *this;

}


PVariant PVariant::operator+(PVariant var) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>()) {
        PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
        PVariantList* vl1 = this->value<PVariantListPtr>().data();
        PVariantList* vl2 = var.value<PVariantListPtr>().data();

        for(int i = 0; i < vl1->count(); i++)
            result << (PVariant)vl1->value(i);

        for(int i = 0; i < vl2->count(); i++)
            result << (PVariant)vl2->value(i);

        return result;
    }

    else if(this->userType() == qMetaTypeId<PVariantMapPtr>()) {
        PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

        foreach(QString key, this->toMap().keys())
            result[key] = this->toMap()[key];

        foreach(QString key, var.toMap().keys())
            result[key] = var.toMap()[key];

        return result;
    }

    return nil;

}

PVariant PVariant::operator-(PVariant var) {

    PVariant result;
    PVariant& self = *this;

    if(this->userType() == qMetaTypeId<PVariantMapPtr>()) {

        result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));
           self.forEachQString_PVariant([&] (QString key,PVariant value) mutable {
            if(!var.toMap().contains(key) )
                result[key] = this->toMap()[key];
        });
    }

    else if(this->userType() == qMetaTypeId<PVariantListPtr>()) {
        result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
        PVariant& self = *this;
         self.forEachPVariant([&] (PVariant fieldValue) mutable {
            if(!var.include(fieldValue))
                result << fieldValue;
        });

    }

    return result;

}


PVariant PVariant::operator&(PVariant var) {

    PVariant result;

    if(this->userType() == qMetaTypeId<PVariantMapPtr>()) {
        PVariantMap* nvm = new PVariantMap();
        result = PVariant(QVariant::fromValue(PVariantMapPtr(nvm)));

        foreach(QString key, this->toMap().keys())
            if(var.toMap().contains(key) && this->toMap().contains(key))
                (*nvm)[key] = this->toMap()[key];
    }

    return result;

}



PVariant& PVariant::operator<<(QVariant value) {

    this->append(value);

    return *this;

}

bool PVariant::operator==(PVariant var) {

    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return this->toMap() == var;

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->toList() == var;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return QVariant::operator==(var);
#else
    return QVariant::fromValue(*this) == QVariant::fromValue(var);
#endif

}


bool PVariant::operator!=(PVariant var) {

    return !((*this) == var);

}


PVariant PVariant::keys() {

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        foreach(QString key, this->toMap().keys())
            result << key;

    return result;

}

PVariant PVariant::values() {

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        foreach(QString key, this->toMap().keys())
            result << this->toMap()[key];

    return result;

}



PVariant PVariant::fromListToMap() {

    PVariant& self = *this;
    PVariant result = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap()))));

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
         self.forEachPVariant([&] (PVariant key) mutable {
            result[key.toString()] = nil;
        });

    return result;

}

int PVariant::indexOf(QVariant value) {


    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->toList().indexOf(value);

    return -1;

}

PVariant PVariant::mid(int pos, int length) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->toList().mid(pos, length);

    return nil;

}

bool PVariant::include(QVariant value) {

    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return this->toMap().include(value);

    return indexOf(value) != -1;

}


bool PVariant::isEmpty() {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->toList().isEmpty();
    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return this->toMap().isEmpty();

    return false;

}



bool PVariant::any() {

    return !isEmpty();

}


PVariant& PVariant::clear() {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        this->toList().clear();
    else if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        this->toMap().clear();

    return *this;

}


PVariant PVariant::split(QString separator) {

    return this->toString().split(separator);

}


PString PVariant::join(QString separator) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->value<PVariantListPtr>()->join(separator);
    else if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return this->value<PVariantMapPtr>()->join(separator);

    return PString();

}


PString PVariant::join(QString separator, QString quoteChar, QString assignChar) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>()) {
        PVariant arr = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
         this->forEachQString([&] (QString value) mutable {
            arr << PString(QString("%1%2%3").arg(quoteChar).arg(value).arg(quoteChar));
        });
        return arr.join(separator);
    }

    if(this->userType() == qMetaTypeId<PVariantMapPtr>()) {
        PVariant arr = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
           this->forEachQString_QString([&] (QString key,QString value) mutable {
            arr << PString(QString("%1%2%3%4%5").arg(key).arg(assignChar).arg(quoteChar).arg(value).arg(quoteChar));
        });
        return arr.join(separator);
    }

    return PString();

}


PString PVariant::toString(QString separator, int indent) {

    if(this->typeName() == "double")
        return QString::number(toDouble(), 'f', PGlobal::decimalPrecision());

    QVariant* ptr = (QVariant*)this;

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return this->value<PVariantListPtr>()->toString(separator);
    else if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return (*this->value<PVariantMapPtr>()).toString(separator, indent);

    return ptr->toString();

}


QStringList PVariant::toStringList() {

    if(this->typeName() == "Array")
        return toList().toStringList();
    else
        qDebug() << "PVariant::toStringList(): Error Type for " << this->typeName();

    return QStringList();

}



void PVariant::setDefaultValue(QVariant defaultValue) {

    if(this->typeName() == "Hash")
        toMap().defaultValue = defaultValue;

}


QString PVariant::toStringStoreFormat() {

    QVariant* ptr = (QVariant*)this;

    if(this->typeName() == "QString")
        return QString("\"%1\"").arg(ptr->toString());
    else if(this->typeName() == "QChar")
        return QString("'%1'").arg(ptr->toString());

    return this->toString();
}

QString PVariant::typeName() {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return "Array";
    if(this->userType() == qMetaTypeId<PVariantMapPtr>())
        return "Hash";

    return QVariant::typeName();

}

PVariant PVariant::quicksort(QVariant sortFields) {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return toList().quicksort(*this, sortFields);

    return nil;

}

PVariant PVariant::min() {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return toList().min();

    return nil;

}

PVariant PVariant::max() {

    if(this->userType() == qMetaTypeId<PVariantListPtr>())
        return toList().max();

    return nil;

}

int getIntegerDemo (int num = 5) {

    return num;

}

int helloDemo(PVariant = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
int helloDemo(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "helloDemo:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
QString str = source_args.value<PVariantMapPtr>()->include("str") ? source_args.value<PVariantMapPtr>()->operator[]("str").toString() : QVariant(nil).toString();args.removeByKey("str");
QPoint point = source_args.value<PVariantMapPtr>()->operator[]("point").value<QPoint>();
args.removeByKey("point");
PVariant array = source_args.value<PVariantMapPtr>()->include("array") ? source_args.value<PVariantMapPtr>()->operator[]("array") : PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(1)->append(2)->append(3)->append(4)->append(5))));args.removeByKey("array");
PVariant hash = source_args.value<PVariantMapPtr>()->include("hash") ? source_args.value<PVariantMapPtr>()->operator[]("hash") : PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("a", 1)->append("b", array))));args.removeByKey("hash");


    if(str.isNull())
        qDebug() << "nil str";

    qDebug() << point;
    qDebug() << array.toString();
    qDebug() << hash.toString();


    return 999;

}

void PVariant::demo() {


    qDebug() << PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(5)->append(4)->append(6)->append(3)->append(7)->append(2)->append(8)->append(1)->append(9)))).quicksort().toString(); 

    PVariant arr0 = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(1)->append(2.2)->append(QString("ciao"))->append(QString("a")))));

    qDebug() << arr0.toString();

    qDebug() << arr0.toList().toStringList();


    PVariant arr1 = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(1)->append(2)->append(3))));

    PVariant arr2 = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(4)->append(5)->append(6))));

    PVariant arr3 = arr1 + arr2;

    qDebug() << arr3.toString(); 

    qDebug() << (arr3 + PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(7)->append(8)->append(9))))).toString(); 

    arr1 += arr2;

    qDebug() << arr1.toString(); 


    PVariant arr4 = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(1)->append(2)->append(PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(3)->append(4)->append(5)->append(6)))))->append(7)->append(8))));

    qDebug() << arr4.toString(); 

    arr4[0] = 11;

    arr4[-1] = 88;

    qDebug() << arr4.toString(); 


    PVariant arr5 = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(1)->append(2)->append(3)->append(4)->append(5)->append(6))));

    qDebug() << arr5.value<PVariantListPtr>()->mid2(1, 3 + 1).toString(); 

    qDebug() << arr5.value<PVariantListPtr>()->mid2(1, -2 + 1).toString(); 


    PVariant arr6 = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(arr1)->append(99))));

    qDebug() << arr6.toString(); 

    int i = 0;

    arr6[i] = 88;

    qDebug() << arr6.toString(); 

    arr6 << 100 << 101;

    qDebug() << arr6.toString(); 

    arr6 << PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(102)->append(103)))); 

    qDebug() << arr6.toString();



    PVariant hash1 = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("a", 1)->append("b", 2)->append("c", 3))));

    PVariant hash2 = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("c", 4)->append("d", 5)->append("e", 6))));

    qDebug() << hash1.toString(); 

    qDebug() << hash2.toString(); 

    PVariant hash3 = hash1 + hash2;

    qDebug() << hash3.toString(); 

    PVariant hash4 = hash1 - hash2;

    qDebug() << hash4.toString(); 

    hash1["a"] = 11;

    qDebug() << hash1.toString();

    qDebug() << hash1.keys().toString(); 

    qDebug() << hash1.values().toString(); 

    hash1.clear();

    qDebug() << hash1.toString(); 

    QPoint p(10, 20);

    PVariant hash = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("array", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(1)->append(2)->append(3)))))->append("hash", PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("b", 1)->append("c", 2)->append("d", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(4)->append(5)->append(p))))))))))));

    qDebug() << hash.toString();


    qDebug() << hash["hash"]["d"][2].toPoint();

    PVariant arr = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append( arr1[1])->append(   QPoint(0,   getIntegerDemo()))->append(    getIntegerDemo())->append(     getIntegerDemo(1))->append(hash1)->append(       helloDemo())->append(QString("xxx"))->append(            helloDemo(PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("array", PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(2)->append(1)->append(0)))))))))))));

    qDebug() << arr.toString();

    PVariant hashDemo = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())->append("c", 1)->append("b", 2)->append("a", 3))));

    qDebug() << hashDemo.toString();
    qDebug() << hashDemo.keys().toString();
    qDebug() << hashDemo.values().toString();

    hashDemo.clear();
    qDebug() << hashDemo.toString();



}
