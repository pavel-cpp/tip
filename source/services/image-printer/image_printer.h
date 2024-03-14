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
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPrinter>
#include <QSize>

/**
 * @class ImagePrinter
 * @brief The ImagePrinter class provides methods for adding images and pixmaps to a printer.
 *
 * This class provides methods for adding images and pixmaps to a printer. It also provides a method for converting centimeters to pixels.
 */
class ImagePrinter {
public:
    /**
     * @brief Add an image to the printer.
     *
     * @param image The image to be added.
     */
    void AddImage(const QImage &image);

    /**
     * @brief Add a pixmap to the printer.
     *
     * @param pixmap The pixmap to be added.
     */
    void AddPixmap(const QPixmap &pixmap);

    /**
     * @brief Construct a new Image Printer object
     *
     * @param size_of_images The size of the images to be added.
     * @param printer The printer to which the images will be added.
     */
    explicit ImagePrinter(QSize size_of_images, QPrinter *printer);

    /**
     * @brief Convert centimeters to pixels.
     *
     * @param centimeters The number of centimeters to be converted.
     * @param dpi The dots per inch (DPI) for the conversion.
     * @return The number of pixels equivalent to the given number of centimeters.
     */
    static int FromCentimetersToPixels(int centimeters, int dpi);

private:

    const short SPACING = 10; ///< The spacing between images.

    QRect frame_; ///< The frame for the images.
    QPrinter *printer_; ///< The printer to which the images will be added.
    QPainter painter_; ///< The painter for the images.
};