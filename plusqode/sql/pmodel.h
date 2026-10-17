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

#ifndef PModel_H
#define PModel_H

   #include "core/pglobal.h"
   #include "sql/psqlfield.h"
   #include "misc/pdebug.h"
   #include "misc/pstring.h"
   #include "sql/psql.h"
   #include "core/plogger.h"
   #include "core/pviewloader.h"
   #include "core/ptranslator.h"
   #include "dom/pdom.h"
   #include "widgets/pfieldselector.h"

   #include "widgets/pmandatoryfield.h"
   #include "widgets/pactionbuttons.h"
   #include "widgets/pwidgetattrs.h"

   #include <QtCore/QObject>
   #include <QtCore/QSharedData>
   #include <QtWidgets/QLabel>
   #include <QtWidgets/QFrame>
   #include <QtWidgets/QGroupBox>
   #include <QtWidgets/QMessageBox>
   #include <QScreen>

   #include <functional>
   #include <iostream>

class PSqlView;
class PSqlFormViewDialog;
class PModelPtr;

typedef std::function<PVariant()> PFunc;
Q_DECLARE_METATYPE(PFunc)

typedef std::function<PVariant(PVariant)> PFuncPVariant;
Q_DECLARE_METATYPE(PFuncPVariant)

typedef std::function<PVariant(QString, PVariant)> PFuncQStringPVariant;
Q_DECLARE_METATYPE(PFuncQStringPVariant)

class PModel    : public QObject {

    Q_OBJECT

public:

       #include "sql/pmodelview.h"

    PVariant autoComplete(const QString& modelName, QString fieldName, PVariant args);
    PVariant pAuto(PVariant args);
    PVariant pa(PVariant args);
    PVariant pText(PVariant args);
    PVariant pt(PVariant args);
    PVariant pInteger(PVariant args);
    PVariant pi(PVariant args);
    PVariant pFloat(PVariant args);
    PVariant pf(PVariant args);
    PVariant pDate(PVariant args);
    PVariant pd(PVariant args);
    PVariant pTime(PVariant args);
    PVariant pDateTime(PVariant args);
    PVariant pdt(PVariant args);
    PVariant pBool(PVariant args);
    PVariant pb(PVariant args);
    PVariant pOneToOne(PVariant args);
    PVariant po2o(PVariant args);
    PVariant pOneToMany(PVariant args);
    PVariant po2m(PVariant args);
    PVariant pManyToOne(PVariant args);
    PVariant pm2o(PVariant args);
    PVariant pManyToMany(PVariant args);
    PVariant pm2m(PVariant args);
    PVariant pVirtual(PVariant args);
    PVariant pv(PVariant args);
    PVariant pv(PFunc f);
    PVariant pv(PVariant args, PFunc f);
    PVariant pv(PVariant args, PFuncPVariant f);
    PVariant pv(PVariant args, PFuncQStringPVariant f);
    PVariant pWidget(PVariant args);
    PVariant pw(PVariant args);
    PVariant primaryKey(PVariant args);
    PVariant serial(PVariant args, QString tableName); PModel   ();
    ~ PModel   ();
    PModel* init(PVariant);
    QString defaultConnectionName();
    virtual QString getModelName();
    QString getClassName();
    static QString toClassName(QString modelName);
    QString toModelName(QString className = "");
    PSql* get_psql();
    PModelPtr toRecordPtr(QString type = QString());
    PModelPtr toModelPtr(PVariant tableCursor = nil, QString type = QString());
    PVariant getTableCursor();
    void  setCacheMode(bool mode = true);

    void addField(const QString& fieldName, PVariant args);
    void setSystemFields();
    PVariant fieldAttr(PString fieldName);
    PVariant fieldValue(PString fieldName);
    void resetIfModelNameReference(QString fieldName);
    bool setFieldValue(QString fieldName, PVariant fieldValue);
    PVariant undefined(PString methodName, PVariant args);
    bool isModelPtr(QString fieldName);
    QString modelPtr(QString fieldName);
    PModelPtr newPModel(QString modelName, QString type = QString(), PVariant domain = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    static PModelPtr newModel(PVariant);
    static PModelPtr model(QString modelName, QString connectionName = QString(), PVariant connectionParams = nil, PVariant domain = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    bool isSubTable(QString fieldName);
    PModelPtr manyToOne(QString modelName, QString referenceFieldName, QString type = "manyToOne");
    PModelPtr oneToMany(QString fieldName, QString modelName, QString referenceFieldName, bool automaticReference = false);
    PVariant sqlQueryByFieldName(PString fieldName);
    QString fieldNameIdToSql(PVariant);
    PModelPtr find(PVariant sql);
    PModelPtr findBy(PVariant args);
    void findBy();
    PModelPtr all();
    bool include(PVariant record = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    PVariant findByOffLine(PVariant record = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    PVariant defaultVariantValue(const QString& fieldType);
    PVariant defaultValue(const QString& fieldName);
    PVariant defaultRecord(PVariant record);
    PModelPtr create(PVariant record = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    PModelPtr dup();
    PModelPtr copy(const QString& suffixModelName = "copy");
    PModel* createOnDb(PVariant record = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    PModel* writeRecord(PVariant values = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    PModel* writeAllRecords(PVariant values = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    PModel* save(PVariant values = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))), PVariant record = nil);
    PModel* saveRecord(PVariant values = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    PModel* saveAllRecords(PVariant values = PVariant(QVariant::fromValue(PVariantMapPtr((new PVariantMap())))));
    PModel* saveOnDB(PVariant);
    bool _deleteOnDB(PVariant);
    virtual void onReloadView();
    virtual void onCreate();
    virtual void onSave();
    virtual void onRemove(PVariant record);
    virtual void onNewBeforeWidget();
    virtual void onNewAfterWidget();
    virtual void onEditBeforeWidget();
    virtual void onEditAfterWidget();
    virtual void onBeforeWidget();
    virtual void onAfterWidget();
    virtual void onAfterTable();
    virtual bool onWrite();
    virtual void onDelete(PVariant id = nil);
    PModel* setRecord(PVariant values);

    virtual bool onOkDialog();
    virtual void onAfterOkDialog();
    virtual bool onCancelDialog();

    bool deleteOnDB(PVariant);
    PModel* _removeRecord(PVariant record);
    PModelPtr removeOnDB(PVariant);
    PModel* remove(PVariant record = nil);
    virtual void apply();
    virtual PVariant action(PVariant action);
    void messageBox(PVariant message);
    PVariant getTableFields();
    PVariant systemFields();
    int count();
    PModel* setTableCursor(PVariant tableCursor = nil);
    PModel* setTableCursorBy(PVariant values);
    void resetCursor();
    PVariant current();
    PVariant first();
    PVariant last();
    PVariant prev();
    PVariant next();
    PVariant operator[](int row);
    PVariant operator[](QString fieldName);
    PVariant operator()(int row);
    PVariant keys();

      template <typename F>
void forEachPModelPtr(F f) {

        psql->pushCursor();

        if(psql->table == nil)
            this->findBy();

        this->resetCursor();
        for(int i = 0; i < this->count(); i++) {
            next();
            f(this);
        }

        psql->popCursor();

    }

       template <typename F>
void forEachPModelPtr_int(F f) {

        psql->pushCursor();

        if(psql->table == nil)
            this->findBy();

        this->resetCursor();
        for(int i = 0; i < this->count(); i++) {
            next();
            f(this, i);
        }

        psql->popCursor();

    }

      template <typename F>
void forEachPVariant(F f) {

        psql->pushCursor();

        for(int i = 0; i < this->count(); i++)
                f(this->operator[](i));

        psql->popCursor();

    }

       template <typename F>
void forEachPVariant_int(F f) {

        psql->pushCursor();

        for(int i = 0; i < this->count(); i++)
                f(this->operator[](i), i);

        psql->popCursor();

    }

    int columnWidth(QString fieldName);
    void showValue(PVariant);
    void showSeparator(PVariant);
    void show(PVariant);
    void showBy(PVariant fields);
    QString dump();
    QString exportCSV(PVariant);
    QString apiSpec();
    static PVariant mainHandleRequest(PVariant request);
    virtual PVariant findByTableViewFieldsCurrent(PVariant payload);
    virtual PVariant handleRequest(PVariant request);

public slots:
    void onClick(PVariant button);
    void dataChanged(QString fieldName, PVariant data);
    void editingFinished(QString fieldName, PVariant fieldValue);
    virtual void onChangeField(QString fieldName, PVariant fieldValue);
    virtual void onDataChanged(QString fieldName, PVariant data);
    virtual void onCurrentRecordChanged(const QString& id);

public:

    bool generate;
    QString mainField; 
    PVariant showField;
    PVariant sortField;
    PVariant rootWidget;

    QString type;
    PModel* source;
    QString sourceFieldName; 

    PVariant domain;
    QString modelName;
    QString moduleName;
    QString className;
    QString connectionName;
    PVariant connectionParams;
    PSql* psql;
    PVariant parents;
    PSqlField pFields;
    PVariant tableFields;
    PVariant modelFields;
    PVariant allParents;

    QList<PModel*> visited;
    PVariant toWrite;
    PVariant toChange;
    PVariant toDelete;

    PVariant colWidth;

    int vid; 

    bool cacheMode;
    PVariant cacheValues;
    PVariant lastChangedFields;

    PSqlView* sqlView;
    PSqlFormViewDialog* sqlFormViewDialog;
    QString mode; 
    bool dataChangedConnection;
    PVariant fieldWidgets;
    QMap<QString, QLabel*> fieldLabels;
    int level; 
    bool writeOnDialog; 
    bool showFullScreen;
    Qt::LayoutDirection tabLayoutDirection;
    bool tabOrderFromCpp; 
    QString stateIdFieldName; 
    bool dialogMode;
    bool autoView; 

    static int sysModelCounter;
    static QList<PModel*> sysModelList;

};

Q_DECLARE_METATYPE(PModel*)


class PModelPtr {

public:

    PModel* model;
    PVariant tableCursor;
    QString type;

    PModelPtr()  {

        this->model = 0;
        tableCursor = nil;

    }

    PModelPtr(PModel* model, PVariant tableCursor = nil, QString type = QString()) {

        this->model = model;
        this->tableCursor = tableCursor;
        this->type = type;

    }


    PVariant toVariant() {

        return QVariant::fromValue(*this);

    }

    PModel* toModel() {

        if(tableCursor != nil)
            this->model->setTableCursor(tableCursor);

        return this->model;

    }

    PModel* operator->() {

        return toModel();

    }

    
    bool operator==(PVariant variant) {

        if(this->model == 0 && variant == nil)
            return true;

        return false;

    }

    
    bool operator!=(PVariant variant) {

        if(this->model != 0 || variant != nil)
            return true;

        return false;

    }


    template <typename T>
    T value() {

        return (T)toModel();

    }

    bool isNull() {

        return this->model == 0;

    }

};

Q_DECLARE_METATYPE(PModelPtr)


#endif 



