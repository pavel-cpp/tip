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

#include "text_painter.h"

// Qt
#include <QGraphicsTextItem>

TextPainter::TextPainter(const QImage &image)
        : image_(image) {
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
    scene_.setSceneRect(0, 0, image_.width(), image_.height());
    scene_.render(&painter);
    return pixmap;
}

QImage TextPainter::GetResultImage() {
    return GetResultPixmap().toImage();
}

QImage TextPainter::GetOriginalImage() {
    return image_;
}
