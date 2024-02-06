#pragma once

// Qt
#include <QUrl>

namespace Models {
    struct Image {
        QUrl url;
        QString format;
    };
}
