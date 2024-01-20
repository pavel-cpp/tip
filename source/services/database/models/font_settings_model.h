#pragma once

#include <QPointF>
#include <QFont>
#include <QColor>

namespace Models {
    struct FontSettings {
        QPointF text_position;
        QFont font;
        QColor color;
    };
}