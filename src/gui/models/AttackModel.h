#pragma once
#include <QObject>

namespace ecc::gui {

class AttackModel : public QObject {
    Q_OBJECT
public:
    explicit AttackModel(QObject* parent = nullptr);
signals:
    void changed();
};

} // namespace ecc::gui
