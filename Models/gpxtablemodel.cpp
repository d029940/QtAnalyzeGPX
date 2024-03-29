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
#include "gpxtablemodel.h"

GpxTableModel::GpxTableModel(ContentType content, const QString &header, QObject *parent)
    : m_contentType(content), m_header(header), QAbstractTableModel(parent)
{
}

QVariant GpxTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section != 0) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    return m_header;
}

int GpxTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_items.size();
}

int GpxTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 1;
}

QVariant GpxTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    if (row < 0 || row >= m_items.size()) {
        return QVariant();
    }

    // Currently, we only use the "name" role for QML and DisplayRole for Widgets
    if (role != NameRole && role != Qt::DisplayRole) {
        return QVariant();
    }
    // A model can return data for different roles.
    // The default role is the display role.
    // it can be accesses in QML with "model.display"

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        // Return the item name for the particular row
        return m_items.at(row);
    }

    return QVariant();
}

void GpxTableModel::upDateModel(const QStringList &newItems)
{
    beginResetModel();
    m_items = newItems;
    endResetModel();
}

// ----- Roles to display the model -----
QHash<int, QByteArray> GpxTableModel::roleNames() const
{
    static QHash<int, QByteArray> mapping{ { NameRole, "name" } };
    return mapping;
}

// ----- Debugging -----
void GpxTableModel::debug() const
{
    qDebug() << m_items;
}
