/********************************************************************************
 * Author    :  Damir Bakiev                                                    *
 * Version   :  na                                                              *
 * Date      :  03 October 2022                                                 *
 * Website   :  na                                                              *
 * Copyright :  Damir Bakiev 2016-2022                                          *
 * License   :                                                                  *
 * Use, modification & distribution is subject to Boost Software License Ver 1. *
 * http://www.boost.org/LICENSE_1_0.txt                                         *
 ********************************************************************************/
#pragma once

#include "utils.h"
#include <QDialog>
#include <QSyntaxHighlighter>

class QTextDocument;

class Dialog : public QDialog {
    Q_OBJECT
public:
    Dialog(const QString& text, const QString& windowTitle, QWidget* parent = nullptr);
    virtual ~Dialog();
};

class GCHighlighter final : public QSyntaxHighlighter {
    Q_OBJECT

public:
    explicit GCHighlighter(QTextDocument* parent);

protected:
    // QSyntaxHighlighter interface
    void highlightBlock(const QString& text) override final;
};
