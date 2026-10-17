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



   #include "core/pviewloader.h"

   
   

PViewLoader::PViewLoader(QObject *parent) :
    QObject(parent)
{
}

PViewLoader::~PViewLoader() {


    PVariant names = PVariant::fromQStringList(views.keys());
     names.forEachQString([&] (QString viewName) mutable {

        delete views[viewName];
    });
}


PView* PViewLoader::view(const QString moduleName, const QString viewName) {

    PView* view = new PView();
    QString _moduleName = moduleName;
    _moduleName.replace(".", "/");
    QString path = PString(QString("app/modules/%1").arg(_moduleName));
    path = PString(QString("%1/%2").arg(PGlobal::basePath()).arg(path));
    QString fileName = PString(QString("%1/pm%2_view.xml").arg(path).arg(viewName));

    if(views.contains(fileName)) {
        PLog().debug() << "PViewLoader::view: cached view returned";
        return view;
    }

    view->initByFileName(fileName);
    views[fileName] = view;
    return view;

}

PView* PViewLoader::viewByPath(QString path) {

    PView* view = new PView();
    path = path.replace(".", "/");
    QString fileName = PString(QString("%1/app/modules/%2.xml").arg(PGlobal::basePath()).arg(path));

    if(views.contains(fileName)) {
        PLog().debug() << "PViewLoader::view: cached view returned";
        return view;
    }

    view->initByFileName(fileName);
    views[fileName] = view;
    return view;

}
