#include "image_printer.h"

ImagePrinter::ImagePrinter(QSize size_of_images, QPrinter *printer) :
        frame_(0, 0, size_of_images.width(), size_of_images.height()),
        printer_(printer),
        painter_(printer_) {
    if (printer == nullptr) {
        throw std::invalid_argument("printer is nullptr");
    }
    painter_.setRenderHint(QPainter::SmoothPixmapTransform);
}

void ImagePrinter::AddImage(const QImage &image) {
    AddPixmap(QPixmap::fromImage(image));
}

void ImagePrinter::AddPixmap(const QPixmap &pixmap) {
    // TODO(Pavel): Fix warp bug
    painter_.drawPixmap(frame_, pixmap);
    if (frame_.x() + frame_.width() + 5 >= painter_.device()->width()) {
        frame_.setX(0);
        frame_.setY( frame_.y() + frame_.height() + 5);
//        frame_.setHeight(frame_.y() + frame_.height());
    }else{
        frame_.setX(frame_.x() + frame_.width() + 5);
//        frame_.setWidth(frame_.x() + frame_.width());
    }
    if (frame_.y() >= painter_.device()->height()) {
        printer_->newPage();
        frame_.setX(0);
        frame_.setY(0);
    }
}
