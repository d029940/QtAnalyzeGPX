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
#include "garminfiles.h"

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
            this, &Controller::garminNodeSelected);
    connect(m_window.fitListView()->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &Controller::garminTableItemSelected);

    // Binding model changes to view
    connect(this, &Controller::onTrkModelChanged, &m_trks, &GpxTableModel::upDateModel);
    connect(this, &Controller::onRteModelChanged, &m_rtes, &GpxTableModel::upDateModel);
    connect(this, &Controller::onWptModelChanged, &m_wpts, &GpxTableModel::upDateModel);
    connect(this, &Controller::onFitModelChanged, &m_fits, &GpxTableModel::upDateModel);

    // Connect all actions of main window
    connect(m_window.exitButton(), &QPushButton::clicked, &QCoreApplication::exit);
    connect(m_window.openGpxButton(), &QPushButton::clicked, this, &Controller::openGpxFile);
    connect(m_window.deleteGpxButton(), &QPushButton::clicked, this, &Controller::deleteGpxFile);
    connect(m_window.deleteFitButton(), &QPushButton::clicked, this, &Controller::deleteFitFile);
    connect(m_window.loadGpxButton(), &QPushButton::clicked, this, &Controller::loadGarminDirs);

    connect(m_window.actionAbout(), &QAction::triggered, this, &Controller::showAboutDialog);

    m_window.show();
}

void Controller::loadGarminDirs()
{
    m_drives.loadGarminDevices();
    reset();

    updateUI();

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
    if (QFile::moveToTrash(gpxFile->fullPath())) {
        loadGarminDirs();
    }
}

void Controller::deleteFitFile()
{
    // Get current selection is different in QMS and Widgets
    QModelIndexList indices = m_window.fitListView()->selectionModel()->selectedIndexes();
    if (indices.isEmpty())
        return;

    QString filename = m_fitFiles.dirName() + "/" + indices.front().data().toString();
    if (QFile::moveToTrash(filename)) {
        loadGarminDirs();
        newCoursesModelsUpdate(m_fitFiles.dirName());
    }
}

// Widget dependant
void Controller::garminNodeSelected(const QItemSelection &selected,
                                    const QItemSelection &deselected)
{
    if (selected.indexes().isEmpty())
        m_window.deleteGpxButton()->setDisabled(true);
    else {
        auto node = static_cast<GarminTreeNode *>(selected.indexes().front().internalPointer());
        if (node->childCount() == 0) {
            // Could be the node for the courses directory or a gpx file
            if (node->fullPath().toLower().endsWith("/" + GarminFiles::kCoursesPath.toLower())) {
                // course node
                newCoursesModelsUpdate(node->fullPath());
            } else {
                // Existing GPX file selected
                newGpxFileModelsUpdate(node->fullPath());
            }
        } else {
            reset();
            updateUI();
        }
    }
}

void Controller::garminTableItemSelected(const QItemSelection &selected,
                                         const QItemSelection &deselected)
{
    // Check also if a fit file is selected
    QModelIndexList indices = m_window.fitListView()->selectionModel()->selectedIndexes();
    if (indices.isEmpty())
        m_window.deleteFitButton()->setDisabled(true);
    else
        m_window.deleteFitButton()->setDisabled(false);
}

void Controller::showAboutDialog()
{
    ABoutDialog dlg{};
    dlg.exec();
}

void Controller::reset()
{
    m_gpxFile.resetGpxFile();
    m_fitFiles.resetCourses();
}

void Controller::updateUI()
{
    // update the table views
    emit onTrkModelChanged(m_gpxFile.trkList());
    emit onWptModelChanged(m_gpxFile.wptList());
    emit onRteModelChanged(m_gpxFile.rteList());
    emit onFitModelChanged(m_fitFiles.fitList());

    // Check status of "Delete GPX" button
    if (!m_gpxFile.trkList().isEmpty() || !m_gpxFile.rteList().isEmpty()
        || !m_gpxFile.wptList().isEmpty()) {
        m_window.deleteGpxButton()->setDisabled(false);
    } else {
        m_window.deleteGpxButton()->setDisabled(true);
    }

    // Check status of "Delete FIT" button
    if (m_fitFiles.fitList().isEmpty()) {
        m_window.deleteFitButton()->setDisabled(true);
    } else {
        // Check also if a fit file is selected
        QModelIndexList indices = m_window.fitListView()->selectionModel()->selectedIndexes();
        if (indices.isEmpty())
            m_window.deleteFitButton()->setDisabled(true);
        else
            m_window.deleteFitButton()->setDisabled(false);
    }
}

// UI independent
void Controller::newGpxFileModelsUpdate(const QString &filename)
{
    reset();
    m_gpxFile.parseGpxFile(filename);
    // either use signal and slot to update the tableviews (bindings)
    updateUI();
    // or update the tableviews directly
    //    m_trks.upDateModel(m_gpxFile.trkList());
    //    m_wpts.upDateModel(m_gpxFile.wptList());
    //    m_rtes.upDateModel(m_gpxFile.rteList());
}

void Controller::newCoursesModelsUpdate(const QString &dirName)
{
    reset();
    m_fitFiles.readCourses(dirName);
    updateUI();
}
