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
#include <QLibraryInfo>
#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "AnalyzeGPX_Widgets_config.h"

ABoutDialog::ABoutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ABoutDialog)
{
    ui->setupUi(this);
    QString qtVer{ "Qt version: " + QLibraryInfo::version().toString()
                   + "a <a href=https://www.qt.io>www.qt.io</a>" };
    QString appVer{
        "AnalyzeGPX Version " + QString::number(AnalyzeGPX_Widgets_VERSION_MINOR) + "."
                + QString::number(AnalyzeGPX_Widgets_VERSION_MINOR),
    };

    //    QVector<QString> aboutText{ "AnalyzeGPX Version ",
    QStringList aboutText{ appVer,
                           "<br>AnalyzeGPX is a free application for analyzing Contents of",
                           "Garmin GPX files",
                           "<br>License: BSD-4",
                           "<br>System Information",
                           qtVer };

    ui->aboutText->setTextFormat(Qt::RichText);
    ui->aboutText->setOpenExternalLinks(true);
    // TODO: Include Licence text
    ui->aboutText->setText(aboutText.join("<br>"));
}

ABoutDialog::~ABoutDialog()
{
    delete ui;
}
