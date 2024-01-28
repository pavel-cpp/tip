#pragma once

#include <QUrl>

namespace Models {
    struct Image {
        QUrl url;
        QString format;
    };
}
