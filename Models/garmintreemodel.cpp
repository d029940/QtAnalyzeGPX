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
#include <QStorageInfo>
#include <QDebug>

#include "garmintreemodel.h"
#include "garminfiles.h"

using namespace std;

GarminTreeModel::GarminTreeModel(const QString &header, QObject *parent)
    : m_header(header), QAbstractItemModel(parent)
{
    m_root = make_unique<GarminTreeNode>(tr("name"), "/");

    // Display roles
    m_roles[NameRole] = "name";
    m_roles[FullPathRole] = "fullPath";
}

void GarminTreeModel::loadGarminDevices()
{
    beginResetModel();

    // First remove info from last "Load Garmin devices"
    m_root->resetTreeNode();

    // Find all mounted volumes
    QList<QStorageInfo> mountedVolumes{ QStorageInfo::mountedVolumes() };
    for (const auto &vol : mountedVolumes) {
        GarminFiles files{ vol.rootPath() };
        files.find();

        // Process courses
        if (!files.courseFiles().empty()) {
            auto volTreeNode =
                    make_shared<GarminTreeNode>(vol.name() + tr(" (Courses)"), files.coursesPath());
            m_root->appendChild(volTreeNode);
        }

        // Process GPX files
        if (!files.gpxFiles().empty()) {
            shared_ptr<GarminTreeNode> volTreeNode =
                    make_shared<GarminTreeNode>(vol.name(), files.gpxPath());
            m_root->appendChild(volTreeNode);
            // for every gpx file, a tree node needs to be created
            for (const QString &file : files.gpxFiles()) {
                QFileInfo fileInfo{ QFileInfo(file) };
                shared_ptr<GarminTreeNode> gpxFileNode = make_shared<GarminTreeNode>(
                        fileInfo.baseName(), fileInfo.absoluteFilePath(), volTreeNode);
                volTreeNode->appendChild(gpxFileNode);
            }
        }
    }

    //    m_root->dumpTree();
    endResetModel();
}

const QString GarminTreeModel::getPathFromTreeNodeFromIndex(QModelIndex index) const
{
    if (index.parent().isValid()) {
        // A gpx file has been selected
        GarminTreeNode *node = static_cast<GarminTreeNode *>(index.internalPointer());
        return node->fullPath();
    }
    return QString();
}

QVariant GarminTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section != 0) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    return m_header;
}

// ----- Debugging & Test ------
void GarminTreeModel::createTestData()
{
    beginResetModel();

    auto node = make_shared<GarminTreeNode>("GPSMap", "/GPSMap", m_root);
    m_root->appendChild(node);
    node = make_shared<GarminTreeNode>("Weser.GPX", "/Edge/Garmin/GPX/Weser.GPX", m_root);
    m_root->child(0)->appendChild(node);
    node = make_shared<GarminTreeNode>("Edge", "/Edge", m_root);
    m_root->appendChild(node);
    node = make_shared<GarminTreeNode>("Leine.GPX", "/Edge/Garmin/GPX/Leine.GPX", m_root);
    m_root->child(1)->appendChild(node);
    m_root->dumpTree();

    endResetModel();
}

void GarminTreeModel::dumpTree() const
{
    m_root->dumpTree();
}

// ----- QAbstractItemModel interface -------
// The index always stores row, column, current item, i.e. not the parent item
// The item for the root is thus (row, column, item) = (0, 0, null) = null

QModelIndex GarminTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    // There is only one column, so column = 0
    if (column > 0)
        return QModelIndex();

    if (!hasIndex(row, column, parent))
        return QModelIndex();

    GarminTreeNode *parentItem;

    if (!parent.isValid())
        // assume the parent is the root
        parentItem = m_root.get();
    else
        parentItem = static_cast<GarminTreeNode *>(parent.internalPointer());

    GarminTreeNode *childItem = (parentItem->child(static_cast<size_t>(row))).get();
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex GarminTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    GarminTreeNode *childItem = static_cast<GarminTreeNode *>(child.internalPointer());
    weak_ptr<GarminTreeNode> parentItem = childItem->parent();

    if (parentItem.expired())
        return QModelIndex();

    // root
    if (parentItem.lock() == m_root)
        return QModelIndex();
    else
        return createIndex(parentItem.lock()->row(), 0, parentItem.lock().get());
}

int GarminTreeModel::rowCount(const QModelIndex &parent) const
{
    GarminTreeNode *parentItem;
    if (!parent.isValid())
        // root
        parentItem = m_root.get();
    else {
        if (parent.column() != 0)
            return 0;
        parentItem = static_cast<GarminTreeNode *>(parent.internalPointer());
    }

    return static_cast<int>(parentItem->childCount());
}

int GarminTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant GarminTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // Currently, we only use the "name" role for QML and DisplayRole for Widgets
    if (role != NameRole && role != Qt::DisplayRole)
        return QVariant();

    GarminTreeNode *item = static_cast<GarminTreeNode *>(index.internalPointer());

    return item->name();
}

// ----- Roles to display the model -----
QHash<int, QByteArray> GarminTreeModel::roleNames() const
{
    return m_roles;
}

QString GarminTreeModel::pathName() const
{
    return m_pathName;
}

void GarminTreeModel::setPathName(const QString &newPathName)
{
    if (m_pathName == newPathName)
        return;
    m_pathName = newPathName;
    emit pathNameChanged();
}
