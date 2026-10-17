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




   #include "widgets/widgetedit/pimagefiledialog.h"


   

   

PImageFileDialog::PImageFileDialog(QWidget* parent) :
        QFileDialog(parent) {

    setOption(QFileDialog::DontUseNativeDialog);

    previewLabel = new QLabel(tr("Image"), this);
    previewLabel->setObjectName("previewLabel");
    previewLabel->setFrameShape(QFrame::Box);
    previewLabel->setAlignment(Qt::AlignCenter);
    previewLabel->setMinimumWidth(128);

    QGridLayout* glayout = (QGridLayout*)layout();
    glayout->addWidget(previewLabel, glayout->rowCount() / 2 - 1,  glayout->columnCount());

    QString basedir = "~";
    
    setDirectory(basedir);
    setFileMode(QFileDialog::ExistingFile);
    setFilter(QDir::Files);
    setNameFilter( "Images (*.png *.xpm *.jpg *.gif)" );

    connect(this, SIGNAL(currentChanged(const QString&)), this, SLOT(setImage(const QString)) );

}

void PImageFileDialog::setImage(const QString& path) {


    previewLabel->setPixmap(QPixmap(path));


}
