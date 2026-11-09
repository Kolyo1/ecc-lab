#pragma once
#include <QWidget>

namespace ecc::gui {

class DashboardView : public QWidget {
    Q_OBJECT
public:
    explicit DashboardView(QWidget* parent = nullptr);

};

} // namespace ecc::gui
