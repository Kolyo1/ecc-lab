#pragma once
#include <QObject>

namespace ecc::gui {

class LogModel : public QObject {
    Q_OBJECT
public:
    explicit LogModel(QObject* parent = nullptr);
signals:
    void changed();
};

} // namespace ecc::gui
