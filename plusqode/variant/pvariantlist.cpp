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

PVariantList::PVariantList() : QVariantList(), QSharedData() {

}


PVariantList::~PVariantList() {



}


PVariantList* PVariantList::append(QVariant value) {

    QVariantList::append(value);
    return this;

}

PVariantList* PVariantList::append(QVariantList values) {

    for(int i = 0; i < values.count(); i++)
        this->append(values[i]);

    return this;

}


PVariantList* PVariantList::appendIfNotExists(QVariant value) {

    int i = this->indexOf(value);

    if(i != -1)
        return this;

    return append(value);

}


PVariantList* PVariantList::insertBefore(QVariant elem, QVariant value) {

    int i = this->indexOf(elem);

    if(i != -1)
        insert(i, value);

    return this;

}


PVariantList* PVariantList::insertAfter(QVariant elem, QVariant value) {

    int i = this->indexOf(elem);

    if(i != -1)
        insert(i + 1, value);

    return this;


}

bool PVariantList::removeByValue(QVariant value) {

    int i = this->indexOf(value);

    if(i != -1)
        this->removeAt(i);

    return i != -1;

}



PVariant& PVariantList::operator[](int i) {

    for(int j = this->length(); j <= i; j++)
        (*this) << nil;

    if(i < 0)
        return (PVariant&)((QVariantList*)this)->operator[](this->length() + i);

    return (PVariant&)((QVariantList*)this)->operator[](i);

}



PVariant& PVariantList::operator()(int i) {

    if(i < 0)
        return (PVariant&)((QVariantList*)this)->operator[](this->length() + i);

    return (PVariant&)((QVariantList*)this)->operator[](i);

}

bool PVariantList::operator==(PVariant var) {

    if(var.userType() != qMetaTypeId<PVariantListPtr>())
        return false;

    if(this->count() != var.count())
        return false;for(int i = 0; i < this->count(); i++) {
PVariant elem = this->operator[](i);
        if(elem != var[i])
            return false;
    }

    return true;

}



int PVariantList::indexOf(PVariant value) {for(int i = 0; i < this->count(); i++) {
PVariant elem = this->operator[](i);
        if(elem == value)
            return i;
    }

    return -1;

}




int PVariantList::indexPointerOf(PVariant value) {for(int i = 0; i < this->count(); i++) {
PVariant elem = this->operator[](i);
        if(elem.typeName() == "Array") {
            if(elem.value<PVariantListPtr>() == value.value<PVariantListPtr>())
                return i;
        }
        else if(elem.typeName() == "Hash") {
            if(elem.value<PVariantMapPtr>() == value.value<PVariantMapPtr>())
                return i;
        }

    }

    return -1;

}


PVariant PVariantList::mid(int pos, int length) {


    if(length < 0)
        length = this->length() + length - pos + 1;

    if(pos + length > this->length()) {
        qDebug() << PString(QString("Error in PVariantList::mid(%1, %2) - length: %3").arg(pos).arg(length).arg(this->length()));
        exit(0);
    }

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    for(int i = 0; i < length; i++)
        result << (*this)[pos + i];

    return result;

}


PVariant PVariantList::mid2(int pos, int length) {


    if(length < 0)
        length = this->length() + length - pos;

    if(pos + length > this->length()) {
        qDebug() << PString(QString("Error in PVariantList::mid(%1, %2) - length: %3").arg(pos).arg(length).arg(this->length()));
        exit(0);
    }

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));
    for(int i = 0; i < length; i++)
        result << (*this)[pos + i];

    return result;

}


QStringList PVariantList::toStringList() {

    QStringList result;for(int _i_3_ = 0; _i_3_ < this->count(); _i_3_++) {
PVariant elem = this->operator[](_i_3_);
        result << ((PVariant)elem).toString();
    }


    return result;
}


QString PVariantList::join(QString separator) {

    return toStringList().join(separator);

}

QString PVariantList::toString(QString separator) {

    return QString("[%1]").arg(join(separator));

}

PVariant PVariantList::quicksort(PVariant values, QVariant sortFields) {

    if(values.count() <= 1)
        return values;

    PVariant leftValues = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())))), rightValues = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    PVariant pivot = values.removeByIndex(values.count() / 2);for(int _i_4_ = 0; _i_4_ < values.count(); _i_4_++) {
PVariant elem = values.operator[](_i_4_);
        if(elem.lessThan(pivot, sortFields))
            leftValues.append(elem);
        else
            rightValues.append(elem);
    }

    return quicksort(leftValues, sortFields) + PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(pivot)))) + quicksort(rightValues, sortFields);

}


PVariant PVariantList::max() {

    PVariant max = (*this)[0];for(int _i_5_ = 0; _i_5_ < this->count(); _i_5_++) {
PVariant elem = this->operator[](_i_5_);
        if(elem.toInt() > max.toInt())
            max = elem;
    }

    return max;

}

PVariant PVariantList::min() {


    PVariant min = (*this)[0];for(int _i_6_ = 0; _i_6_ < this->count(); _i_6_++) {
PVariant elem = this->operator[](_i_6_);
        if(elem.toInt() < min.toInt())
            min = elem;
    }

    return min;

}






PVariant PVariantList::filter(PVariant fields) {

  if(fields.typeName() == "Array")
      fields = fields.fromListToMap();

  PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));for(int _i_7_ = 0; _i_7_ < this->count(); _i_7_++) {
PVariant row = this->operator[](_i_7_);
      result << (row & fields);
  }

  return result;

}


PVariantList& PVariantList:: sortByPositionList(PVariant source_args) {
if(source_args.typeName() != "Hash") qDebug() << "sortByPositionList:  invalid type";
PVariantMapPtr source_args_ptr = source_args.value<PVariantMapPtr>();
PVariant args = PVariant(QVariant::fromValue(PVariantMapPtr(new PVariantMap())));
foreach(QString key, source_args_ptr->keys())
 args[key] = (*source_args_ptr)[key];
PVariant list = source_args.value<PVariantMapPtr>()->include("list") ? source_args.value<PVariantMapPtr>()->operator[]("list") : nil;args.removeByKey("list");


    if(list == nil) return *this;

    PVariant tableCopy = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));for(int i = 0; i < this->count(); i++) {
PVariant row = this->operator[](i); tableCopy[i] = row; }for(int i = 0; i < list.count(); i++) {
PVariant& id = list.operator[](i); id = tableCopy[list[i].toString()]; }
    return *this;

}

PVariant PVariantList::column(QString fieldName) {

    PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    if(fieldName.isNull()) return result;for(int _i_10_ = 0; _i_10_ < this->count(); _i_10_++) {
PVariant row = this->operator[](_i_10_);
        result << row[fieldName];
    }

    return result;

}

PVariant PVariantList::undefined(QString index, PVariant value) {

    if(index.endsWith('=')) {
        index.chop(1);
        (*this)[index.toInt()] = value;
    }

    return (*this)(index.toInt());

}

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)

PVariant PVariantList::fromJson(const QJsonArray &jsonArray) {

    PVariant listResult = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

    for(int i = 0; i < jsonArray.count(); i++) {
        const QJsonValue val = jsonArray.at(i);
        listResult << PVariant::fromJson(val);
    }

    return listResult;

}


QJsonArray PVariantList::toJson() {

    QJsonArray jsonArray;for(int _i_11_ = 0; _i_11_ < this->count(); _i_11_++) {
PVariant elem = this->operator[](_i_11_);
        jsonArray.append(elem.toJson());
    }

    return jsonArray;
}


#endif




