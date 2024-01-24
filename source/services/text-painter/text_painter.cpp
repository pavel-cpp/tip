#include "text_painter.h"
#include <QDebug>

TextPainter::TextPainter(const QImage &image)
        : original_image_(image),
          editing_image_(image)
          {
              painter_.begin(&editing_image_);
          }

void TextPainter::DrawText(const TextPainter::ContentTemplate &text) {
    painter_.setFont(text.options.font);
    painter_.setPen(text.options.color);
    QRect rect(text.options.position, QFontMetrics(text.options.font).boundingRect(text.content).size());
    QPoint top_left = text.options.position;
    top_left.setX(top_left.x() - QFontMetrics(text.options.font).boundingRect(text.content).width() / 2);
    painter_.drawText(top_left, text.content);
}

void TextPainter::SetImage(const QImage &image) {
    editing_image_ = original_image_ = image;
    painter_.begin(&editing_image_);
}

void TextPainter::Clear() {
    if(painter_.isActive()){
        painter_.end();
    }
    editing_image_ = original_image_;
    painter_.begin(&editing_image_);
}

QPixmap TextPainter::GetResultPixmap() {
    return QPixmap::fromImage(editing_image_);
}

QImage TextPainter::GetResultImage() {
    return editing_image_;
}

QImage TextPainter::GetOriginalImage() {
    return original_image_;
}
