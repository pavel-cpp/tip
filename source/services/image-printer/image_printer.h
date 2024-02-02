#pragma once

#include <QImage>
#include <QPixmap>
#include <QSize>
#include <QPainter>
#include <QPrinter>

class ImagePrinter {
public:
    void AddImage(const QImage &image);

    void AddPixmap(const QPixmap &pixmap);

    explicit ImagePrinter(QSize size_of_images, QPrinter *printer);

    static int FromCentimetersToPixels(int centimeters);

private:

    const short SPACING = 10;

    QRect frame_;
    QPrinter *printer_;
    QPainter painter_;

};
