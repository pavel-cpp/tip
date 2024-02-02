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

int ImagePrinter::FromCentimetersToPixels(int centimeters) {
    return centimeters * (300 / 2.54);
}
