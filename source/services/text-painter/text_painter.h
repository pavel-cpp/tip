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

#pragma once

// QImage
#include <QImage>
#include <QPainter>

// QtGraphics
#include <QGraphicsScene>
#include <QGraphicsTextItem>

// STDLIB
#include <deque>
#include <memory>

// Services
#include <services/database/models/font_settings_model.h>

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

