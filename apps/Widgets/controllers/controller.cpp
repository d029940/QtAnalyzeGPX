/****************************************************************************
**
** Copyright (C) 2020 Manfred Kern. All rights reserved.
** Contact: manfred.kern@gmail.com
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** 3. All advertising materials mentioning features or use of this software
**    must display the following acknowledgement:
**    This product includes software developed by the the organization.
**
** 4. Neither the name of the copyright holder nor the names of its
**    contributors may be used to endorse or promote products derived from
**    this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/
#include "controller.h"

#include <QCoreApplication>
#include <QFileDialog>
#include <QStandardPaths>

#include "aboutdialog.h"

Controller::Controller()
{
    // connect models to table / tree views
    m_window.trkListView()->setModel(&m_trks);
    m_window.rteListView()->setModel(&m_rtes);
    m_window.wptListView()->setModel(&m_wpts);
    m_window.fitListView()->setModel(&m_fits);
    m_window.devicesTreeView()->setModel(&m_drives);

    // setup selection in table / tree views (Attention: models have to be
    // assigned before)
    connect(m_window.devicesTreeView()->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &Controller::gpxFileSelected);

    // Binding model changes to view
    connect(this, &Controller::onTrkModelChanged, &m_trks, &GpxTableModel::upDateModel);
    connect(this, &Controller::onRteModelChanged, &m_rtes, &GpxTableModel::upDateModel);
    connect(this, &Controller::onWptModelChanged, &m_wpts, &GpxTableModel::upDateModel);
    connect(this, &Controller::onFitModelChanged, &m_fits, &GpxTableModel::upDateModel);

    // Connect all actions of main window
    connect(m_window.exitButton(), &QPushButton::clicked, &QCoreApplication::exit);
    connect(m_window.openGpxButton(), &QPushButton::clicked, this, &Controller::openGpxFile);
    connect(m_window.deleteGpxButton(), &QPushButton::clicked, this, &Controller::deleteGpxFile);
    connect(m_window.loadGpxButton(), &QPushButton::clicked, this, &Controller::loadGarminDirs);

    connect(m_window.actionAbout(), &QAction::triggered, this, &Controller::showAboutDialog);

    m_window.show();
}

void Controller::loadGarminDirs()
{
    m_drives.loadGarminDevices();
    m_gpxFile.reset();
    emit onTrkModelChanged(m_gpxFile.trkList());
    emit onWptModelChanged(m_gpxFile.wptList());
    emit onRteModelChanged(m_gpxFile.rteList());
    emit onFitModelChanged(m_gpxFile.fitList());

    // expand garmin device tree
    QTreeView *deviceTree = m_window.devicesTreeView();
    deviceTree->setExpandsOnDoubleClick(true);
    if (deviceTree->itemsExpandable()) {
        deviceTree->expandToDepth(2);
    }
}

// Widget dependant
void Controller::openGpxFile()
{
    QStringList lst = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString filename =
            QFileDialog::getOpenFileName(nullptr, QFileDialog::tr("Open GPX file"), lst.front(),
                                         QFileDialog::tr("GPX (*.gpx *.GPX)"));

    newGpxFileModelsUpdate(filename);
}

// Widget dependant
void Controller::deleteGpxFile()
{
    // Get current selection is different in QMS and Widgets
    QModelIndexList indices = m_window.devicesTreeView()->selectionModel()->selectedIndexes();
    if (indices.isEmpty())
        return;

    auto gpxFile = static_cast<GarminTreeNode *>(indices.front().internalPointer());
    if (QFile::remove(gpxFile->fullPath())) {
        loadGarminDirs();
    }
}

// Widget dependant
void Controller::gpxFileSelected(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (selected.indexes().isEmpty())
        m_window.deleteGpxButton()->setDisabled(true);
    else {
        auto gpxFile = static_cast<GarminTreeNode *>(selected.indexes().front().internalPointer());
        if (gpxFile->childCount() == 0) {
            // Existing GPX file selected
            m_window.deleteGpxButton()->setDisabled(false);
            newGpxFileModelsUpdate(gpxFile->fullPath());

        } else {
            m_window.deleteGpxButton()->setDisabled(true);
        }
    }
}

void Controller::showAboutDialog()
{
    ABoutDialog dlg{};
    dlg.exec();
}

// UI independent
void Controller::newGpxFileModelsUpdate(const QString &filename)
{
    m_gpxFile.reset();
    m_gpxFile.parse(filename);
    // either use signal and slot to update the tableviews (bindings)
    emit onTrkModelChanged(m_gpxFile.trkList());
    emit onWptModelChanged(m_gpxFile.wptList());
    emit onRteModelChanged(m_gpxFile.rteList());
    emit onFitModelChanged(m_gpxFile.fitList());
    // or update the tableviews directly
    //    m_trks.upDateModel(m_gpxFile.trkList());
    //    m_wpts.upDateModel(m_gpxFile.wptList());
    //    m_rtes.upDateModel(m_gpxFile.rteList());
}
