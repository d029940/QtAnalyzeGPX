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
#include <QDebug>
#include <QDomDocument>
#include <QFile>

#include "garmingpxfile.h"

GarminGpxFile::GarminGpxFile() { }

// NOTE: https://doc-snapshots.qt.io/qt6-6.4/xml-changes-qt6.html
void GarminGpxFile::parse(const QString &filename)
{
    QFile file{ filename };
    m_fileName = filename;
    QDomDocument gpxFileDOM;

    // Load the fike
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file " << file.fileName();
        qDebug() << "Error " << file.errorString();
        return;
    }

    if (!gpxFileDOM.setContent(&file)) {
        qDebug() << "Failed to load XML document " << file.fileName();
        file.close();
        return;
    }

    // Get the root element
    QDomElement root = gpxFileDOM.firstChildElement();
    // Get routes
    listTrkRteFitWpt(root, rte);
    // Get tracks
    listTrkRteFitWpt(root, trk);
    // Get waypoints
    listTrkRteFitWpt(root, wpt);
    // Get courses
    listTrkRteFitWpt(root, fit);

    file.close();
}

// ----- Manipulate routes, tracks, waypoints lists ----

void GarminGpxFile::appendRoute(const QString &route)
{
    m_rteList.append(route);
}

void GarminGpxFile::appendTrack(const QString &track)
{
    m_trkList.append(track);
}

void GarminGpxFile::appendCourses(const QString &course)
{
    m_fitList.append(course);
}

void GarminGpxFile::appendWaypoint(const QString &waypoint)
{
    m_wptList.append(waypoint);
}

void GarminGpxFile::reset()
{
    m_rteList.clear();
    m_trkList.clear();
    m_fitList.clear();
    m_wptList.clear();
}

// ----- Getters and setters  -----

QStringList GarminGpxFile::trkList() const
{
    return m_trkList;
}

void GarminGpxFile::setTrkList(const QStringList &trkList)
{
    m_trkList = trkList;
}

QStringList GarminGpxFile::rteList() const
{
    return m_rteList;
}

void GarminGpxFile::setRteList(const QStringList &rteList)
{
    m_rteList = rteList;
}

QStringList GarminGpxFile::wptList() const
{
    return m_wptList;
}

void GarminGpxFile::setWptList(const QStringList &wptList)
{
    m_wptList = wptList;
}

QStringList GarminGpxFile::fitList() const
{
    return m_fitList;
}

void GarminGpxFile::setFitList(const QStringList &newFitList)
{
    m_fitList = newFitList;
}

QString GarminGpxFile::fileName() const
{
    return m_fileName;
}

// ----- Role names for displaying in the model ---------

void GarminGpxFile::listTrkRteFitWpt(QDomElement parent, GpxContentType type)
{
    QString tagName;
    QStringList *list = nullptr;
    switch (type) {
    case rte: {
        tagName = m_tagNames[rte];
        list = &m_rteList;
        break;
    }
    case trk: {
        tagName = m_tagNames[trk];
        list = &m_trkList;
        break;
    }
    case wpt: {
        tagName = m_tagNames[wpt];
        list = &m_wptList;
        break;
    }
    case fit: {
        tagName = m_tagNames[fit];
        list = &m_fitList;
        break;
    }
    }

    QDomNodeList items = parent.elementsByTagName(tagName);

    list->clear();

    for (int i = 0; i < items.count(); ++i) {
        QDomNode node = items.at(i);
        if (node.isElement()) {
            QDomElement element = node.toElement();
            QDomElement name = element.firstChildElement("name");
            list->append(name.text());
        }
    }
}
