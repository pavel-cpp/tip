#pragma once

// Qt
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPrinter>
#include <QSize>

class ImagePrinter {
public:
    void AddImage(const QImage &image);

    void AddPixmap(const QPixmap &pixmap);

    explicit ImagePrinter(QSize size_of_images, QPrinter *printer);

    static int FromCentimetersToPixels(int centimeters, int dpi);

private:

    const short SPACING = 10;

    QRect frame_;
    QPrinter *printer_;
    QPainter painter_;

};
