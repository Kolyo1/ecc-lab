#pragma once
#include <QWidget>

namespace ecc::gui {

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

};

} // namespace ecc::gui
