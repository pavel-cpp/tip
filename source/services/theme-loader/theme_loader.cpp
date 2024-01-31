#include "theme_loader.h"
#include <QFile>

QString Theme::Load(const QString &theme_name) {
    QFile style_file("./themes/" + theme_name + ".qss");
    style_file.open(QFile::ReadOnly);
    if (!style_file.isOpen()) {
        return {};
    }
    return QLatin1String(style_file.readAll());
}
