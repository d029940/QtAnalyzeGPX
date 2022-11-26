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
#ifndef GARMINTREENODE_H
#define GARMINTREENODE_H

#include <QString>
#include <vector>
using std::vector;
#include <memory>
using std::shared_ptr;
using std::weak_ptr;

///
/// \brief Represents a Garmin tree node
/// A tree node is either a Volume/Garmin/GPX folder or a gpx file
/// Per node, the name and the full path is stored
/// Tree nodes are linked using shared pointers
///
class GarminTreeNode : std::enable_shared_from_this<GarminTreeNode>
{
public:
    explicit GarminTreeNode(const QString& name,
                            const QString& fullPath,
                            shared_ptr<GarminTreeNode> parent = nullptr);

    // ----- Manaage the children of a node ----
    void appendChild(shared_ptr<GarminTreeNode> child);
    size_t childCount() const;

    // reset GarminTreeNode to its initial values
    void resetTreeNode();

    // ----- Getters -----
    QString name() const;
    QString fullPath() const;
    weak_ptr<GarminTreeNode> parent() const;
    shared_ptr<GarminTreeNode> child(size_t index);
    vector<shared_ptr<GarminTreeNode>> children() const;
    int row() const;

    // ----- Debug ----
    void dumpTree() const;

private:
    QString m_name;
    QString m_fullPath;
    weak_ptr<GarminTreeNode> m_parent;
    vector<shared_ptr<GarminTreeNode>> m_children;
};

#endif // GARMINTREENODE_H
