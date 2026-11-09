#pragma once
#include <QObject>

namespace ecc::gui {

class KeyModel : public QObject {
    Q_OBJECT
public:
    explicit KeyModel(QObject* parent = nullptr);
signals:
    void changed();
};

} // namespace ecc::gui
