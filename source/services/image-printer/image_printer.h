#pragma once

#include <QImage>
#include <QPixmap>
#include <QSize>
#include <QPainter>

class ImagePrinter {
public:
    void AddImage(const QImage& image);

    void AddPixmap(const QPixmap& pixmap);

    ImagePrinter() = default;

    ImagePrinter(QSize size_of_images, QPaintDevice* printer);

    ImagePrinter(const ImagePrinter& other);

private:

    QSize size_of_images_;
    QPainter painter_;

};
