#pragma once

#include <array>
#include <cstddef>

#include <QString>
#include <QPointF>
#include <QFont>
#include <QColor>

struct TextSettings {
    QPointF text_position_;
    QFont font_;
    QColor color;
};

class SettingsLoader {
private:

    struct Settings {
        QString input_image_path_;
        std::array<TextSettings, 3> text_options_;
        QString output_folder_;
    };

public:

    void Load();

    Settings GetSettings();

    void SetSettings(const Settings& settings);

    void Save();

private:

    Settings settings_;

    const std::string settings_file_path_ = "./settings/settings.ini";

};


