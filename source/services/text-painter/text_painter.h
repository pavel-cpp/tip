#pragma once

#include <QImage>
#include <QPainter>
#include <deque>

#include <services/database/models/font_settings_model.h>
#include <QGraphicsScene>

class TextPainter {
public:

    struct ContentTemplate {
        Models::FontSettings options;
        QString content;
    };

    TextPainter() = default;

    explicit TextPainter(const QImage &image);

    TextPainter(const TextPainter &painter) = delete;

    TextPainter(TextPainter &&painter) = delete;

    void SetImage(const QImage &image);

    void DrawText(const ContentTemplate &text);

    void Clear();

    QPixmap GetResultPixmap();

    QImage GetResultImage();

    QImage GetOriginalImage();

private:
    QImage image_;
    QGraphicsScene scene_;
    std::deque<std::unique_ptr<QGraphicsTextItem>> items_;
};

