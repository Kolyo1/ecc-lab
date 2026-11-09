#pragma once
#include <QWidget>

namespace ecc::gui {

class BenchmarkPanel : public QWidget {
    Q_OBJECT
public:
    explicit BenchmarkPanel(QWidget* parent = nullptr);

};

} // namespace ecc::gui
