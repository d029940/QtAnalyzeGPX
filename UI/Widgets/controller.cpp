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
#include <QFileDialog>
#include <QStandardpaths>
#include "controller.h"
#include "./ui_mainwindow.h"

Controller::Controller()
{
    connect(m_window.getUi()->exitButton, &QPushButton::clicked, &QCoreApplication::exit);
    connect(m_window.getUi()->openGpxButton, &QPushButton::clicked, this, &Controller::openGpxFile);
    m_window.getUi()->trkListView->setModel(&m_trks);
    m_window.getUi()->rteListView->setModel(&m_rtes);
    m_window.getUi()->wptListView->setModel(&m_wpts);
    m_window.show();
}

void Controller::loadGarminDirs() { }

void Controller::openGpxFile()
{
    QStringList lst = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    QString filename =
            QFileDialog::getOpenFileName(nullptr, QFileDialog::tr("Open GPX file"), lst.front(),
                                         QFileDialog::tr("GPX (*.gpx *.GPX)"));

    m_gpxFile.reset();
    m_gpxFile.parse(filename);
    m_trks.upDateModel(m_gpxFile.trkList());
    m_wpts.upDateModel(m_gpxFile.wptList());
    m_rtes.upDateModel(m_gpxFile.rteList());
}

void Controller::deleteGpxFile() { }
