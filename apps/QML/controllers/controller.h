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
#pragma once

#include <QObject>
// #include "mainwindow.h"
#include "garmingpxfile.h"
#include "gpxtablemodel.h"
#include "garmintreemodel.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(GarminTreeModel &drives, const GpxTableModel &trks, const GpxTableModel &rtes,
               const GpxTableModel &wpts, const GpxTableModel &fits);

public slots:
    Q_INVOKABLE void loadGarminDirs();
    Q_INVOKABLE void openGpxFile(const QUrl &url);
    Q_INVOKABLE void getSelectedRow(const QModelIndex &index);

    void deleteGpxFile();
    //    void gpxFileSelected(const QItemSelection &selected, const QItemSelection &deselected);
    void showAboutDialog();

signals:
    void onTrkModelChanged(const QStringList &newItems);
    void onRteModelChanged(const QStringList &newItems);
    void onWptModelChanged(const QStringList &newItems);
    void onFitModelChanged(const QStringList &newItems);

private:
    //    MainWindow m_window;
    GarminGpxFile m_gpxFile{}; // Current GPX file shown in table views
    const GpxTableModel *m_trks; // Table view for tracks
    const GpxTableModel *m_rtes; // Table view for routes
    const GpxTableModel *m_wpts; // Table view for waypoints (POIs)
    const GpxTableModel *m_fits; // Table view for courses
    GarminTreeModel *m_drives; // Drives recognized by Garmin gps

    void newGpxFileModelsUpdate(
            const QString &filename); // updates m_trks, m_rtes, m_wpts when new GPX file is loaded
};
