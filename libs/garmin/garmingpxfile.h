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
#include <QStringList>

// Referenced classes
class QDomElement;

///
/// \class GarminGpxFile
/// \brief Defines methods for analyzing the content of Garmin GPX files
///
class GarminGpxFile
{

public:
    explicit GarminGpxFile();

    /**
     * @brief  Parses Garmin GPX file for routes, tracks and waypoints
     * @param filename - an existing local filename with gpx/GPX extension
     */
    void parseGpxFile(const QString &filename);

    // Manipulate routes, tracks, waypoints, courses lists
    void appendRoute(const QString &route);
    void appendTrack(const QString &track);
    void appendWaypoint(const QString &waypoint);

    void resetGpxFile();

    // Getters and setters for tracks, routes and waypoints
    QStringList trkList() const;
    void setTrkList(const QStringList &trkList);

    QStringList rteList() const;
    void setRteList(const QStringList &rteList);

    QStringList wptList() const;
    void setWptList(const QStringList &wptList);

    QString fileName() const;

private:
    // Tag names in Garmin GPX files
    enum GpxContentType { rte = 0, trk, wpt };
    QStringList m_tagNames{ "rte", "trk", "wpt" };

    // fills trk, rte, wpt lists
    void listTrkRteWpt(QDomElement parent, GpxContentType type);

    // Content of gpx file
    QStringList m_trkList;
    QStringList m_rteList;
    // TOFO: delete
    // QStringList m_fitList;
    QStringList m_wptList;

    // Filename
    QString m_fileName;
};
