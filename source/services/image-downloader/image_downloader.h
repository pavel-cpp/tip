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

#pragma once

// Qt
#include <QString>
#include <QUrl>

/**
 * @class ImageDownloader
 * @brief The ImageDownloader class provides a static method for downloading images.
 *
 * This class provides a static method for downloading images from a given URL and saving them to a specified path.
 */
class ImageDownloader {
public:
    /**
     * @brief Fetch an image from a URL and save it to a specified path.
     *
     * @param path The path where the image will be saved.
     * @param url The URL from which the image will be downloaded.
     * @return true if the image was successfully downloaded and saved, false otherwise.
     */
    static bool FetchImage(const QString &path, const QUrl &url);
};