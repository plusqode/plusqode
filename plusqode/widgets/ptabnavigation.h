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

#ifndef PTABNAVIGATION_H
#define PTABNAVIGATION_H

   #include <QtCore/QMap>
   #include <QtWidgets/QTabWidget>
   #include <QtWidgets/QTreeWidget>
   #include <QtWidgets/QGridLayout>
   #include <QtWidgets/QLabel>

   #include "core/pglobal.h"
   #include "misc/ptelemetry.h"
   #include "misc/pdir.h"
   #include "variant/pvariant.h"
   #include "core/pview.h"
   #include "core/pviewloader.h"
   #include "widgets/sqlview/psqlviewtabwidget.h"
   #include "widgets/pmainview.h"
   #include "widgets/pstateprogressbar.h"
   #include "widgets/ppwidget.h"


class PTabNavigation : public QTabWidget
{
    Q_OBJECT
public:
    explicit PTabNavigation(QWidget *parent = 0);
    ~PTabNavigation();
    QString currentModuleName();
    QTreeWidget* treeWidget(const QString& moduleName);
    QList<QTreeWidgetItem*> leftMenu(PVariant& menu);
    void paintEvent(QPaintEvent*);
    PVariant viewList(PVariant ref);
    void showSqlView(PVariant ref);
    void treeWidgetClean();

signals:

public slots:
    void onChangeTab(int);
    void onClickLeftMenu();

    void onWidgetDoubleClicked();

public:

    PVariant modules;

    PMainView* mainView;

    int leftMenuWidth;

    PVariant moduleNameMap;

    PVariant moduleNames;

};

Q_DECLARE_METATYPE(QWidget*)
Q_DECLARE_METATYPE(QTabWidget*)
Q_DECLARE_METATYPE(QTreeWidget*)
Q_DECLARE_METATYPE(QGridLayout*)
Q_DECLARE_METATYPE(PSqlTableView*)
Q_DECLARE_METATYPE(PSqlViewTabWidget*)

#endif 



