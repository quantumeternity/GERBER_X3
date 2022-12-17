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
#pragma once

#include "topor_types.h"

#include "file.h"

namespace TopoR {

class File : public FileInterface {
    friend class Parser;

public:
    explicit File();
    ~File() override;

    FileType type() const override { return FileType::TopoR; }

    // FileInterface interface
public:
    void createGi() override;
    void initFrom(FileInterface* file) override;
    FileTree::Node* node() override;

protected:
    void write(QDataStream& stream) const override;
    void read(QDataStream& stream) override;
    Paths merge() const override;
};

} // namespace TopoR
