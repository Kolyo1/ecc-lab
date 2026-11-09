#pragma once
#include <QObject>

namespace ecc::gui {

class BenchmarkModel : public QObject {
    Q_OBJECT
public:
    explicit BenchmarkModel(QObject* parent = nullptr);
signals:
    void changed();
};

} // namespace ecc::gui
