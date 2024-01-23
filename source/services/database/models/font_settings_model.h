#pragma once

#include <QPointF>
#include <QFont>
#include <QColor>

namespace Models {
    struct FontSettings {
        QPointF position;
        QFont font;
        QColor color;
    };
}