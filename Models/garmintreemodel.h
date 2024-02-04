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

#include <memory>
#include <QAbstractItemModel>
#include "garmintreenode.h"

class GarminTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    // Connection to QML
    Q_PROPERTY(QString pathName READ pathName WRITE setPathName NOTIFY pathNameChanged)

public:
    explicit GarminTreeModel(const QString &header, QObject *parent = nullptr);

    enum DirRoles { NameRole = Qt::UserRole + 1, FullPathRole };
    Q_ENUM(DirRoles)

    /**
     * @brief  Search all connected volumes/devices for
     * 1. Garmin/GPX folder (lower or upper case) and
     * 2. GPX files (files with extension GPX - lower or upper case)
     * 3. Load the devices and the files in the tree model
     *
     * At start the tree model (children of the root) is cleared
     */
    void loadGarminDevices();

    /**
     * @brief  Extracts the full path of the GPX file selected in the treeview
     * @param index = QModelIndex returned by click event of the treeview
     * @return the full path of the selected GPX file
     *         or QString() if a directory/volume has been selected
     */
    const QString getPathFromTreeNodeFromIndex(QModelIndex index) const;

    // ----- QAbstractItemModel interface ----
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    // ----- Define Roles ----
    QHash<int, QByteArray> roleNames() const override;

    // Debug
    void createTestData();
    void dumpTree() const;

    QString pathName() const;
    void setPathName(const QString &newPathName);

signals:
    void modelChanged();
    void pathNameChanged();

private:
    // Roles for displaying
    QHash<int, QByteArray> m_roles;

    /**
     * @brief read all gpx files (extension gpx) of a given directory
     *        and create GarminTreeNode for each gpx file
     * @param vol - GarminTreeNode with full path of a directory
     * @return true if gpx file is found, otherwise false
     */
    bool readGpxFilesInFolder(const std::shared_ptr<GarminTreeNode> vol);
    /**
     * @brief read all fit files (extension fit) of a given directory
     * @param vol - GarminTreeNode with full path of a directory
     * @return true if fit file is found, otherwise false
     */
    bool readFitFilesInFolder(const std::shared_ptr<GarminTreeNode> vol) const;

    /**
     * @brief points to the root of GarminTreeNodes
     *        which store volumes with their gpx files in "Garmin/GPX" folder
     */
    std::shared_ptr<GarminTreeNode> m_root;

    QString m_header; // Tree column header
    QString m_pathName;
};
