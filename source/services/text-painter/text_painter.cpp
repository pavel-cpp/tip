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
    painter_.drawText(text.options.position, text.content);
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

/*
 * TODO(Pavel): Перенести в mainwinow для подготовки изображения, отвечает за центрирование объекта
 * buff.setX(settings.point[i].x()
 *                   - (((items[i].length()) * 0.25) * (settings.font[i].pixelSize()))
 *                   );
 */
