#pragma once

#include <QString>
#include <QUrl>

class ImageDownloader {
public:
    static bool FetchImage(const QString &path, const QUrl &url);
};