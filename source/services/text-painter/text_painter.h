#pragma once

#include <QImage>
#include <QPainter>

#include <services/database/models/font_settings_model.h>

class TextPainter {
public:

    struct ContentTemplate : public Models::FontSettings{
        QString content;

        ContentTemplate() = default;

        explicit ContentTemplate(const FontSettings& other) : FontSettings(other) {}

        ContentTemplate(const ContentTemplate& other) : FontSettings(other) {
            content = other.content;
        }

        ContentTemplate& operator=(const ContentTemplate& other) {
            ContentTemplate copy(other);
            swap(copy);
        }
        ContentTemplate& operator=(const Models::FontSettings& other) {
            ContentTemplate copy(other);
            swap(copy);
        }

        void swap(ContentTemplate& other){
            std::swap(position, other.position);
            std::swap(font, other.font);
            std::swap(color, other.color);
            std::swap(content, other.content);
        }
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
    QImage original_image_;
    QImage editing_image_;
    QPainter painter_;
};

