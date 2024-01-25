#include "text_painter.h"
#include <QDebug>
#include <QGraphicsTextItem>

TextPainter::TextPainter(const QImage &image)
        : image_(image) {
    scene_.setSceneRect(0, 0, image_.width(), image_.height());
    scene_.addPixmap(QPixmap::fromImage(image_));
}

void TextPainter::DrawText(const TextPainter::ContentTemplate &text) {
    std::unique_ptr<QGraphicsTextItem> item = std::make_unique<QGraphicsTextItem>(text.content);
    item->setFont(text.options.font);
    item->setDefaultTextColor(text.options.color);
    QPoint top_left = text.options.position;
    top_left.setX(top_left.x() - QFontMetrics(text.options.font).boundingRect(text.content).width() / 2);
    item->setPos(top_left);
    items_.push_back(std::move(item));
    scene_.addItem(items_.back().get());
}

void TextPainter::SetImage(const QImage &image) {
    image_ = image;
    scene_.addPixmap(QPixmap::fromImage(image_));
    for (auto &item: items_) {
        scene_.removeItem(item.get());
        scene_.addItem(item.get());
    }
}

void TextPainter::Clear() {
    for (auto &item: items_) {
        scene_.removeItem(item.get());
    }
    items_.clear();
}

QPixmap TextPainter::GetResultPixmap() {
    QPixmap pixmap(scene_.sceneRect().size().toSize());
    pixmap.fill(Qt::white);  // Заполняем фон белым цветом
    QPainter painter(&pixmap);
    scene_.render(&painter);
    return pixmap;
}

QImage TextPainter::GetResultImage() {
    QPixmap pixmap(scene_.sceneRect().size().toSize());
    pixmap.fill(Qt::white);  // Заполняем фон белым цветом
    QPainter painter(&pixmap);
    scene_.render(&painter);
    return pixmap.toImage();
}

QImage TextPainter::GetOriginalImage() {
    return image_;
}
