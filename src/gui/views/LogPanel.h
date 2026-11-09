#pragma once
#include <QWidget>

namespace ecc::gui {

class LogPanel : public QWidget {
    Q_OBJECT
public:
    explicit LogPanel(QWidget* parent = nullptr);

};

} // namespace ecc::gui
