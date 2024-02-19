/*
    "Text Insertion Program (TIP)" is a software
    for client management and generating unique images for each client.
    Copyright (C) 2024  Pavel Remdenok

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "theme_loader.h"

// Qt
#include <QFile>

QString Theme::Load(const QString &theme_name) {
    QFile style_file("./themes/" + theme_name + ".qss");
    style_file.open(QFile::ReadOnly);
    if (!style_file.isOpen()) {
        return {};
    }
    return QLatin1String(style_file.readAll());
}
