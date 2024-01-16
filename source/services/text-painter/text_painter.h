#pragma once

#include <QImage>
#include <QPainter>

class TextPainter {
public:

    struct TextTemplate {
        QString content;
        QFont font;
        QColor color;
    };

    TextPainter() = default;

    TextPainter(const QImage &image);

    TextPainter(const TextPainter &painter) = delete;

    TextPainter(TextPainter &&painter) = delete;

    void SetImage(const QImage &image);

    void DrawText(const TextTemplate &text, QPointF position);

    void Clear();

    QPixmap GetResultPixmap();

    QImage GetResultImage();

private:
    QImage original_image_;
    QImage editing_image_;
    QPainter painter_;
};

