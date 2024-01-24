#pragma once

#include <QPointF>
#include <QFont>
#include <QColor>

namespace Models {
    struct FontSettings {
        QPoint position;
        QFont font;
        QColor color;
    };
}