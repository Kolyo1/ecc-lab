#pragma once
#include <QWidget>

namespace ecc::gui {

class KeyPanel : public QWidget {
    Q_OBJECT
public:
    explicit KeyPanel(QWidget* parent = nullptr);

};

} // namespace ecc::gui
