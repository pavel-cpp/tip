#pragma once

#include <array>
#include <cstddef>

#include <QString>
#include <QPointF>
#include <QFont>
#include <QColor>

struct TextSettings
{
    QPointF text_position_;
    QFont font_;
    QColor color;
};


class Settings {
    public:
    


    private:

    QString input_image_path_;
    std::array<TextSettings, 3> text_options_;
    QString output_folder_;

};


