#pragma once
#include <QObject>

namespace ecc::gui {

class DefenseModel : public QObject {
    Q_OBJECT
public:
    explicit DefenseModel(QObject* parent = nullptr);
signals:
    void changed();
};

} // namespace ecc::gui
