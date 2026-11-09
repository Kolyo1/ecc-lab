#pragma once
#include <QObject>

namespace ecc::gui {

class CurveModel : public QObject {
    Q_OBJECT
public:
    explicit CurveModel(QObject* parent = nullptr);
signals:
    void changed();
};

} // namespace ecc::gui
