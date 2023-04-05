/********************************************************************************4
 * Author    :  Damir Bakiev                                                    *
 * Version   :  na                                                              *
 * Date      :  March 25, 2023                                                  *
 * Website   :  na                                                              *
 * Copyright :  Damir Bakiev 2016-2023                                          *
 * License   :                                                                  *
 * Use, modification & distribution is subject to Boost Software License Ver 1. *
 * http://www.boost.org/LICENSE_1_0.txt                                         *
 ********************************************************************************/
#pragma once

#include "depthform.h"
#include "gcode.h"

#include <QButtonGroup>
#include <QThread>
#include <QtWidgets>

namespace GCode {

class File;

class BaseForm : public QWidget {
    Q_OBJECT

public:
    explicit BaseForm(Plugin* plugin, Creator* tpc, QWidget* parent = nullptr);
    ~BaseForm() override;
    virtual void editFile(File* file) = 0;

    Creator* creator() const { return creator_; }

    void setCreator(Creator* newCreator) {
        if (newCreator) {
            creator_ = newCreator;
            connect(this, &BaseForm::createToolpath, this, &BaseForm::startProgress);
            connect(this, &BaseForm::createToolpath, creator_, &Creator::createGc);
            connect(creator_, &Creator::canceled, this, &BaseForm::stopProgress);
            connect(creator_, &Creator::errorOccurred, this, &BaseForm::errorHandler);
            connect(creator_, &Creator::fileReady, this, &BaseForm::fileHandler);
            creator_->moveToThread(&thread);
            connect(&thread, &QThread::finished, creator_, &QObject::deleteLater);
            thread.start(QThread::LowPriority /*HighestPriority*/);
        } else if (creator_) {
            thread.quit();
            thread.wait();
        }
    }

signals:
    void createToolpath();

protected:
    void fileHandler(File* file);
    void updateButtonIconSize() {
        for (auto* button : findChildren<QPushButton*>())
            button->setIconSize({16, 16});
    }

    // QObject interface
    virtual void timerEvent(QTimerEvent* event) override;
    // BaseForm interface
    virtual void сomputePaths() = 0;
    virtual void updateName() = 0;

    Direction direction = Climb;
    SideOfMilling side = Outer;
    UsedItems usedItems_;
    Side boardSide = Top;
    void addUsedGi(class ::GraphicsItem* gi);

    QString fileName_;

    QString trOutside {tr("Outside")};
    QString trDepth {tr("Depth:")};
    QString trTool {tr("Tool:")};

    bool editMode_ = false;
    int fileId {-1};

    int fileCount {1};
    Plugin* const plugin;

    DepthForm* dsbxDepth;
    //    QLabel* label;
    QLineEdit* leName;
    QPushButton* pbClose;
    QPushButton* pbCreate;
    QWidget* content;
    QGridLayout* grid;

private:
    Creator* creator_;

    QDialogButtonBox* errBtnBox;
    class TableView* errTable;

    QWidget* ctrWidget;
    QWidget* errWidget;

    void errContinue();
    void errBreak();

    void cancel();
    void errorHandler(int = 0);

    void startProgress();
    void stopProgress();

    QThread thread;
    File* file_;
    class ::QProgressDialog* progressDialog;
    int progressTimerId = 0;
};

} // namespace GCode