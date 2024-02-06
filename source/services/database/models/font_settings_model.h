#pragma once

// Qt
#include <QColor>
#include <QFont>
#include <QPointF>

namespace Models {
    struct FontSettings {
        QPoint position;
        QFont font;
        QColor color;
    };
}