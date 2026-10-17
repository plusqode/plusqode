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

#ifndef PIMAGEFILEDIALOG_H
#define PIMAGEFILEDIALOG_H

   #include <QtCore/QString>
   #include <QtCore/QStringList>
   #include <QtCore/QEvent>
   #include <QtWidgets/QWidget>
   #include <QtWidgets/QFileDialog>
   #include <QtWidgets/QLabel>
   #include <QtWidgets/QGridLayout>
   #include <iostream>

using namespace std;

class PImageFileDialog : public QFileDialog
{
    Q_OBJECT

public:
    explicit PImageFileDialog(QWidget *parent = 0);

signals:


public slots:
    void setImage(const QString& path);

private:

    QLabel* previewLabel;

};

#endif 



