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

#include <algorithm>
#include "garmintreenode.h"

using namespace std;

GarminTreeNode::GarminTreeNode(const QString& name,
                               const QString& fullPath,
                               shared_ptr<GarminTreeNode> parent) :
    m_name{name}, m_fullPath{fullPath}, m_parent{parent}
{
}

void GarminTreeNode::appendChild(shared_ptr<GarminTreeNode> child)
{
    m_children.push_back(child);
}

size_t GarminTreeNode::childCount() const
{
    return m_children.size();
}

void GarminTreeNode::resetTreeNode()
{
    m_name = "";
    m_fullPath = "";
    m_children.clear();
    m_parent.reset();
}

// ----- Getters -----

QString GarminTreeNode::name() const
{
    return m_name;
}

QString GarminTreeNode::fullPath() const
{
    return m_fullPath;
}

// ----- Qt model helpers -----
weak_ptr<GarminTreeNode> GarminTreeNode::parent() const
{
    return m_parent;
}

shared_ptr<GarminTreeNode> GarminTreeNode::child(size_t index)
{
    if (index < m_children.size())
        return m_children.at(index);
    else
        return nullptr;
}

vector<shared_ptr<GarminTreeNode> > GarminTreeNode::children() const
{
    return m_children;
}

int GarminTreeNode::row() const
{
    if (!m_parent.expired()) {
        shared_ptr<GarminTreeNode> parent = m_parent.lock();
        auto itr = find_if(parent->m_children.cbegin(),
                           parent->m_children.cend(),
        [this](const shared_ptr<GarminTreeNode> node) {
            if (node.get() == this)
                return true;
            else
                return false;
        });
        if (itr != parent->m_children.cend()) {
            return static_cast<int>(distance(parent->m_children.cbegin(), itr));
        }
    }
    return 0;
}

// ----- Debug helpers -----

void GarminTreeNode::dumpTree() const
{
    qDebug() << "Name: " << m_name << " Path: " << m_fullPath << " Children: " << m_children.size();
    for (shared_ptr<GarminTreeNode> child : m_children) {
        qDebug() << "---- Children: -----";
        child->dumpTree();
    }
}

