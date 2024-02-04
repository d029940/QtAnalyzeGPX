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
#include "mainwindow.h"
#include "garmingpxfile.h"
#include "gpxtablemodel.h"
#include "garmintreemodel.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();

public slots:
    /**
     * @brief loads the garmin tree, consisting of the mounted drives (with garmin folder).
     *        If available the tree contans nodes for the gpx files and for the courses folder.
     *        The tables tracks, routes, waypoints and courses are resetted (emptied)
     */
    void loadGarminDirs();
    /**
     * @brief open a file chooses to select a gpx file. The contents
     *        will be shown in the tracks, routes and waypoints tables.
     */
    void openGpxFile();
    /**
     * @brief deletes selected gpx file from disc.
     */
    void deleteGpxFile();
    /**
     * @brief deletes selected fit file from disc.
     */
    void deleteFitFile();
    /**
     * @brief if a gpx file is selected, the tables tracks, routes and waypoints are populated
     *        with resp. info from gpx file.
     *        if a course node is selected, the courses directory is read and the available
     *        courses are displayed in the courses table
     * @param selected - selected node in tree
     * @param deselected - node used
     */
    void garminNodeSelected(const QItemSelection &selected, const QItemSelection &deselected);
    void showAboutDialog();

signals:
    void onTrkModelChanged(const QStringList &newItems);
    void onRteModelChanged(const QStringList &newItems);
    void onWptModelChanged(const QStringList &newItems);
    void onFitModelChanged(const QStringList &newItems);

private:
    MainWindow m_window;
    GarminGpxFile m_gpxFile{}; // Current GPX file and courses shown in table views
    GpxTableModel m_trks{ tr("Tracks") }; // Table view for tracks
    GpxTableModel m_rtes{ tr("Routes") }; // Table view for routes
    GpxTableModel m_wpts{ tr("Waypoints") }; // Table view for waypoints (POIs)
    GpxTableModel m_fits{ tr("Courses") }; // Table view for waypoints (POIs)
    GarminTreeModel m_drives{ tr("Drives") }; // Drives recognized by Garmin gps

    void newGpxFileModelsUpdate(
            const QString &filename); // updates m_trks, m_rtes, m_wpts when new GPX file is loaded
    void
    newCoursesModelsUpdate(const QString &dirName); // updates m_fits when new courses are loaded
    void updateUI();
};
