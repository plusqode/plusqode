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

#ifndef PVARIANT_H
#define PVARIANT_H

   #include <QtCore/QVariant>
   #include <QtCore/QDebug>
   #include <QtCore/QDateTime>
   #include <QtCore/QtGlobal>
   #include <QtCore/QVariantHash>
   #include <QtCore/QStringList>
   #include <QtCore/QSharedData>
   #include <QtCore/QVariantList>
   #include <QtCore/QtGlobal>
   #include <QPoint>


#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
       #include <QtCore/QJsonObject>
       #include <QtCore/QJsonArray>
#endif


#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
       #include <QtCore/QRegExp>
#else
       #include <QtCore/QRegularExpression>
#endif





class PString;
class PVariant;
class PVariantList;
class PVariantMap;
class PModelPtr;

class PString : public QString
{
public:
    PString();
    PString (const char* str);
    PString(QString str);
    bool include(PString str);
    PVariant split(PString separator);
    PString replace_(QString before, QString after);
    QString capitalize(QString separator = "");
    QString uncapitalize();
    static PString justify(QString str, int fieldWidth, QString justify = "left");
    static QString space(int len, char ch = ' ');
    const QChar operator[](int index) const;
    PString fromTo(int a, int b = 0);
    QString colorize(int colorCode);
    QString colorize(PVariant);
    QString gray();
    QString white();
    QString red();
    QString green();
    QString yellow();
    QString blue();
    QString pink();
    QString high_red();
    QString high_green();
    QString high_yellow();
    QString high_blue();
    QString high_purple();
    QString high_cyan();
    QString high_white();
    QString color(QString color);
    bool exactMatch(const QString& pattern);

};


class PVariantList : public QVariantList, public QSharedData
{
public:
    PVariantList();
    ~PVariantList();
    PVariantList* append(QVariant value);
    PVariantList* append(QVariantList values);
    PVariantList* appendIfNotExists(QVariant value);
    PVariantList* insertBefore(QVariant elem, QVariant value);
    PVariantList* insertAfter(QVariant elem, QVariant value);
    bool removeByValue(QVariant value);
    QStringList toStringList();
    QString join(QString separator = ",");
    QString toString(QString separator = ",");
    PVariant& operator[](int i);
    PVariant& operator()(int i);
    bool operator==(PVariant var);
    int indexOf(PVariant value);
    int indexPointerOf(PVariant value);
    PVariant mid(int pos, int length = -1);
    PVariant mid2(int pos, int length = -1);
    PVariant quicksort(PVariant values, QVariant sortFields = QVariant());
    PVariant max();
    PVariant min();
    PVariant filter(PVariant fields);
    PVariantList& sortByPositionList(PVariant);
    PVariant column(QString fieldName);
    PVariant undefined(QString index, PVariant value);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    static PVariant fromJson(const QJsonArray&);
    QJsonArray toJson();
#endif


};

Q_DECLARE_METATYPE(PVariantList*);

typedef QExplicitlySharedDataPointer<PVariantList> PVariantListPtr;
Q_DECLARE_METATYPE(PVariantListPtr)


class PVariantMap : public QVariantHash, public QSharedData {

public:
    PVariantMap();
    ~PVariantMap();
    PVariantMap* append(QString key, QVariant value);
    bool operator==(PVariant var);
    bool operator!=(PVariant var);
    PVariant& operator[](QString key);
    PVariant operator()(QString key);
    PVariant& operator[](int index);
    PVariantMap& set(QString key, PVariant value, bool overwrite = true);
    PVariantMap& set(PVariant);
    PVariantMap& operator+=(PVariant var);
    bool include(PVariant var);
    QString join(QString separator = ",", int indent = 0);
    QString toString(QString separator = ", ", int indent = 0);
    PVariant toVariant();
    QStringList keys();
    int remove(QString key);
    QVariant take(QString key);
    void clear();
    PVariant undefined(QString key, PVariant value);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    static PVariant fromJson(const QJsonObject&);
    QJsonObject toJson();
#endif


    QStringList _keys;

    QVariant defaultValue;

};

Q_DECLARE_METATYPE(PVariantMap*)

typedef QExplicitlySharedDataPointer<PVariantMap> PVariantMapPtr;
Q_DECLARE_METATYPE(PVariantMapPtr)


#define nil PVariant()


class PVariant : public QVariant {

public:
    PVariant();
    PVariant(QString);
    PVariant(QByteArray);
    PVariant(QChar);
    PVariant(QDate);
    PVariant(QDateTime);
    PVariant(const char*);
    PVariant(int);
    PVariant(float);
    PVariant(double);
    PVariant(bool);
    PVariant(QVariant var);
    PVariantList& toList();
    PVariantMap& toMap();
    PVariant toMap(PVariant list);
    int toInt();

    PVariant dup();
    PVariant reverse();

    PModelPtr toModelPtr();

    static PVariant fromString(QString str); 
    static PVariant fromQStringList(QStringList list);
    static PVariant fromQMap(QMap<QString, QVariant>& map);
    static PVariant fromItemsAndValues(PVariant items, PVariant values);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    static PVariant fromJson(const QJsonValue&);
    QJsonValue toJson();
#endif

    PVariant& append(QVariant value);
    PVariant& appendIfNotExists(QVariant value);
    PVariant& append(QString key, QVariant value);
    PVariant removeByIndex(int index);
    PVariant removeByKey(QString key);
    bool removeByValue(QVariant value);
    bool operator<(PVariant var);
    bool equal(PVariant var);
    bool lessThan(PVariant var, PVariant sortFields = nil);
    PVariant& operator[](int index);
    PVariant& operator[](char* key);
    PVariant& operator[](const QString key);
    PVariant& set(QString key, PVariant value, bool overwrite = true);
    PVariant& set(PVariant);
    PVariant undefined(PString key, PVariant value);

    
    
    PVariant operator()(char* key);
    PVariant operator()(const QString key);


    
    
    PVariant operator()(int i);

    int count();
    PVariant& operator=(QVariant var);
    PVariant& operator=(QString str);
    PVariant& operator=(const char* str);
    PVariant& operator=(int value);
    PVariant& operator=(double value);
    PVariant& operator=(float value);
    PVariant& operator=(bool value);
    PVariant& operator+=(PVariant var);
    PVariant operator+(PVariant var);
    PVariant operator-(PVariant var);
    PVariant operator&(PVariant var);

    PVariant& operator<<(QVariant value);
    bool operator==(PVariant var);
    bool operator!=(PVariant var);

    PVariant keys();
    PVariant values();
    PVariant fromListToMap();

    int indexOf(QVariant value);
    PVariant mid(int pos, int length = -1);
    bool include(QVariant value);

    bool isEmpty();
    bool any();

    PVariant& clear();

    PVariant split(QString separator);
    PString join(QString separator = ",");
    PString join(QString separator, QString quoteChar, QString assignChar = ": ");
    PString toString(QString separator = ", ", int indent = 0);
    QString toStringStoreFormat();
    QStringList toStringList();
    void setDefaultValue(QVariant defaultValue);

    QString typeName();

    PVariant quicksort(QVariant sortFields = QVariant());
    PVariant min();
    PVariant max();


      template <typename F>
void forEachPVariant(F f) {

        for(int i = 0; i < this->count(); i++)
                f(this->operator[](i));
    }

      template <typename F>
void forEachQString(F f) {

         this->forEachPVariant([&] (PVariant value) mutable {
                f(value.toString());
        });

    }

      template <typename F>
void forEachPString(F f) {

         this->forEachPVariant([&] (PVariant value) mutable {
                f(value.toString());
        });

    }


      template <typename F>
void forEachint(F f) {

         this->forEachPVariant([&] (PVariant value) mutable {
                f(value.toInt());
        });

    }

      template <typename F>
void forEachdouble(F f) {

         this->forEachPVariant([&] (PVariant value) mutable {
                f(value.toDouble());
        });

    }


       template <typename F>
void forEachWithIndexPVariant_int(F f) {

        int i = 0;
         this->forEachPVariant([&] (PVariant value) mutable {
                f(value, i++);
        });

    }


       template <typename F>
void forEachWithIndexQString_int(F f) {

           this->forEachWithIndexPVariant_int([&] (PVariant value,int i) mutable {
                f(value.toString(), i);
        });

    }


       template <typename F>
void forEachWithIndexPString_int(F f) {

           this->forEachWithIndexPVariant_int([&] (PVariant value,int i) mutable {
                f(value.toString(), i);
        });


    }

       template <typename F>
void forEachWithIndexint_int(F f) {

           this->forEachWithIndexPVariant_int([&] (PVariant value,int i) mutable {
                f(value.toInt(), i);
        });

    }


       template <typename F>
void forEachWithIndexdouble_int(F f) {

           this->forEachWithIndexPVariant_int([&] (PVariant value,int i) mutable {
                f(value.toDouble(), i);
        });

    }


       template <typename F>
void forEachQString_PVariant(F f) {

        PVariant keys = this->keys();
        for(int i = 0; i < keys.count(); i++) {
            QString key = keys[i].toString();
            PVariant value = this->operator[](key);
            f(key, value);
        }

    }


       template <typename F>
void forEachQString_QString(F f) {

           this->forEachQString_PVariant([&] (QString key,PVariant value) mutable {
            f(key, value.toString());
        });

    }


       template <typename F>
void forEachQString_PString(F f) {

           this->forEachQString_PVariant([&] (QString key,PVariant value) mutable {
            f(key, value.toString());
        });

    }


       template <typename F>
void forEachQString_int(F f) {

           this->forEachQString_PVariant([&] (QString key,PVariant value) mutable {
            f(key, value.toInt());
        });

    }


       template <typename F>
void forEachQString_double(F f) {

           this->forEachQString_PVariant([&] (QString key,PVariant value) mutable {
            f(key, value.toDouble());
        });

    }


        template <typename F>
void forEachWithIndexQString_PVariant_int(F f) {

        int i = 0;
           this->forEachQString_PVariant([&] (QString key,PVariant value) mutable {
            f(key, value, i++);
        });

    }


        template <typename F>
void forEachWithIndexQString_QString_int(F f) {

        int i = 0;
           this->forEachQString_PVariant([&] (QString key,PVariant value) mutable {
            f(key, value.toString(), i++);
        });

    }


        template <typename F>
void forEachWithIndexQString_PString_int(F f) {

             this->forEachWithIndexQString_PVariant_int([&] (QString key,PVariant value,int i) mutable {
            f(key, value.toString(), i++);
        });

    }


        template <typename F>
void forEachWithIndexQString_int_int(F f) {

             this->forEachWithIndexQString_PVariant_int([&] (QString key,PVariant value,int i) mutable {
            f(key, value.toInt(), i++);
        });

    }


        template <typename F>
void forEachWithIndexQString_double_int(F f) {

             this->forEachWithIndexQString_PVariant_int([&] (QString key,PVariant value,int i) mutable {
            f(key, value.toDouble(), i++);
        });

    }


      template <typename F>
PVariant mapPVariant(F f) {

        PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

         this->forEachPVariant([&] (PVariant value) mutable {
            result << f(value);
        });

        return result;

    }

      template <typename F>
PVariant selectPVariant(F f) {


        PVariant result = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

         this->forEachPVariant([&] (PVariant value) mutable {
            if(f(value))
                result << value;
        });

        return result;

    }

    template <typename F>
    PVariant sort(PVariant values, F f) {

        if(values.count() <= 1)
            return values;

        PVariant leftValues = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())))), rightValues = PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList()))));

        PVariant pivot = values.removeByIndex(values.count() / 2);for(int _i_0_ = 0; _i_0_ < values.count(); _i_0_++) {
PVariant elem = values.operator[](_i_0_);
            if(f(elem, pivot))
                leftValues.append(elem);
            else
                rightValues.append(elem);
        }

        return sort(leftValues, f) + PVariant(QVariant::fromValue(PVariantListPtr((new PVariantList())->append(pivot)))) + sort(rightValues, f);

    }

    template <typename F>
    PVariant sortPVariant_PVariant(F f) {

        return sort(*this, f);

    }


    static void demo();

};

Q_DECLARE_METATYPE(PVariant*)


#endif 



