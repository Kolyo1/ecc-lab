#pragma once
#include <QObject>

namespace ecc::gui {

class DemoController : public QObject {
    Q_OBJECT
public:
    explicit DemoController(QObject* parent = nullptr);
public slots:
    void runAttack(const QString& name);
    void toggleDefense(const QString& name, bool on);
    void runBenchmark();
signals:
    void progress(int percent);
    void finished();
};

} // namespace ecc::gui
