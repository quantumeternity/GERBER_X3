// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
/********************************************************************************
 * Author    :  Damir Bakiev                                                    *
 * Version   :  na                                                              *
 * Date      :  03 October 2022                                                 *
 * Website   :  na                                                              *
 * Copyright :  Damir Bakiev 2016-2022                                          *
 * License   :                                                                  *
 * Use, modification & distribution is subject to Boost Software License Ver 1. *
 * http://www.boost.org/LICENSE_1_0.txt                                         *
 *******************************************************************************/
#include "topor_file.h"

#include "topor_node.h"

namespace TopoR {

QDataStream& operator>>(QDataStream& s, Tools& c) {
    c.clear();
    quint32 n;
    s >> n;
    for (quint32 i = 0; i < n; ++i) {
        Tools::key_type key;
        Tools::mapped_type val;
        s >> key;
        s >> val;
        if (s.status() != QDataStream::Ok) {
            c.clear();
            break;
        }
        c.emplace(key, val);
    }
    return s;
}

QDataStream& operator<<(QDataStream& s, const Tools& c) {
    s << quint32(c.size());
    for (auto& [key, val] : c) {
        s << key << val;
    }
    return s;
}

File::File()
    : FileInterface() { }

File::~File() { }

Paths File::merge() const {
    for (GraphicsItem* item : *itemGroups_.back())
        mergedPaths_.append(item->paths());
    return mergedPaths_;
}

void File::write(QDataStream& stream) const {
}

void File::read(QDataStream& stream) {
}

void File::createGi() {
    itemGroup()->setVisible(true);
}

void File::initFrom(FileInterface* file) {
    FileInterface::initFrom(file);
}

FileTree::Node* File::node() {
    return node_ ? node_ : (node_ = new Node(this));
}

} //  namespace TopoR