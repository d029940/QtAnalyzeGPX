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
#include <QDir>

#include "garminfitfile.h"
#include "garminfiles.h"

GarminFitFile::GarminFitFile()
{
    // look for all files with extension "fit" in directory and collect them
}

void GarminFitFile::resetCourses()
{
    m_fitList.clear();
}

void GarminFitFile::readCourses(const QString &dirname)
{
    m_fitList.clear();
    QDir coursesDir = QDir(dirname);
    if (!coursesDir.exists()) {
        return;
    }

    QString ext{ GarminFiles::kCoursesExt.toLower() };
    m_dirName = dirname;
    coursesDir.setFilter(QDir::Files | QDir::NoDotDot | QDir::NoDot | QDir::NoSymLinks);
    QFileInfoList coursesList = coursesDir.entryInfoList();
    for (const QFileInfo &fitFile : coursesList) {
        if (fitFile.suffix().toLower() == ext) {
            m_fitList.push_back(fitFile.fileName());
            ;
        }
    }
}

void GarminFitFile::appendCourses(const QString &course)
{
    m_fitList.append(course);
}

QStringList GarminFitFile::fitList() const
{
    return m_fitList;
}

void GarminFitFile::setFitList(const QStringList &newFitList)
{
    m_fitList = newFitList;
}

QString GarminFitFile::dirName() const
{
    return m_dirName;
}
