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

#include "image_printer.h"

ImagePrinter::ImagePrinter(QSize size_of_images, QPrinter *printer) :
        frame_(SPACING, SPACING, size_of_images.width(), size_of_images.height()),
        printer_(printer),
        painter_(printer_) {
    if (printer == nullptr) {
        throw std::invalid_argument("printer is nullptr");
    }
}

void ImagePrinter::AddImage(const QImage &image) {
    AddPixmap(QPixmap::fromImage(image));
}

#include <QDebug>

void ImagePrinter::AddPixmap(const QPixmap &pixmap) {
    painter_.drawPixmap(frame_, pixmap);
    frame_.moveLeft(frame_.left() + frame_.width() + SPACING);
    if (frame_.left() + SPACING >= painter_.device()->width()) {
        frame_.moveLeft(SPACING);
        frame_.moveTop(frame_.top() + frame_.height() + SPACING);
    }
    if (frame_.top() + frame_.height() + SPACING >= painter_.device()->height()) {
        printer_->newPage();
        frame_.moveLeft(SPACING);
        frame_.moveTop(SPACING);
    }
}

int ImagePrinter::FromCentimetersToPixels(int centimeters, int dpi) {
    return centimeters * (dpi / 2.54);
}
