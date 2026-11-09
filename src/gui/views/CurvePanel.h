#pragma once
#include <QWidget>

namespace ecc::gui {

class CurvePanel : public QWidget {
    Q_OBJECT
public:
    explicit CurvePanel(QWidget* parent = nullptr);

};

} // namespace ecc::gui
