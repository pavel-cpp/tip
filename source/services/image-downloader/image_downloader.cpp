#include "image_downloader.h"

// Qt
#include <QEventLoop>
#include <QFile>

// QtNetwork
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

bool ImageDownloader::FetchImage(const QString &path, const QUrl &url) {
    QNetworkAccessManager manager;
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QFile file(path);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
        } else {
            return false;
        }
    } else {
        return false;
    }

    reply->deleteLater();
    return true;
}

