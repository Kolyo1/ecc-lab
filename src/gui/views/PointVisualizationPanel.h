#pragma once
#include <QWidget>

namespace ecc::gui {

class PointVisualizationPanel : public QWidget {
    Q_OBJECT
public:
    explicit PointVisualizationPanel(QWidget* parent = nullptr);

};

} // namespace ecc::gui
