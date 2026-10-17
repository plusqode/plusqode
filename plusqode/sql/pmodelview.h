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

 PModel 
  
   {
  
   
   

    virtual QString currentFileName();
    QString getModuleName();
    void destroy();
    void initTableView();
    void initFormView();
    PVariant newField(PVariant fieldAttrs);
    void reduce(PVariant);
    void clean(PVariant);
    PVariant viewBy(PVariant attrs);
    PVariant getView(PVariant);
    static bool isNumber(QString fieldType);
    PVariant tableViewFields(const QString& viewType = "table");
    PVariant formViewFields(PVariant viewAttrs);
    PFieldWidget* getFieldWidget(const QString& fieldName);
    QLabel* getFieldLabel(const QString& fieldName);
    PFieldWidget* fieldWidget(QString fieldName, QString fieldType, PVariant fieldAttrs, QWidget *parent,
                               PMandatoryField* mandatoryField, QString mode);
    void toWidget(PVariant parentView, QWidget* parentWidget, QGridLayout* parentGridLayout,
                  PMandatoryField* mandatoryField, QString mode,
                  int row = 0, int col = 0,
                  Qt::Orientation arrangement = Qt::Horizontal,
                  Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter);
    void initTabOrder();
    void reloadParentFieldWidget();
    void reloadFieldWidget(QString fieldName);
    void reloadFieldWidget();

    void setFieldWidget(PVariant);
    void initDialog();
    int exec();
    virtual QWidget* controlPanelWidget();

    bool lockedDataChanged;
    int fieldPosition;;
