#pragma once
#include <QThread>

namespace ecc::gui {

class WorkerThread : public QThread {
    Q_OBJECT
protected:
    void run() override;
signals:
    void progress(int percent);
    void resultReady();
};

} // namespace ecc::gui
